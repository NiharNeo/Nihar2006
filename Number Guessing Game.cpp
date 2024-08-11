#include <iostream>
#include <cstdlib>  // For rand() and srand()
#include <ctime>    // For time()
#include <chrono>   // For timing in Timed Mode

// Function to display game instructions and difficulty levels
void displayInstructions() {
    std::cout << "Welcome to the Number Guessing Game!" << std::endl;
    std::cout << "Choose a mode:" << std::endl;
    std::cout << "1. Classic Mode" << std::endl;
    std::cout << "2. Timed Mode" << std::endl;
    std::cout << "3. Challenge Mode" << std::endl;
    std::cout << "Enter your choice (1-3): ";
}

// Function to determine the maximum number of attempts based on difficulty level
int getMaxAttempts(int difficulty) {
    switch (difficulty) {
        case 1: return 10; // Easy
        case 2: return 7;  // Medium
        case 3: return 5;  // Hard
        case 4: return 3;  // Expert
        default: return 7; // Default to Medium
    }
}

// Function to provide a hint
void giveHint(int secretNumber, int attempts, int minRange, int maxRange) {
    if (attempts == 3) {
        if (secretNumber % 2 == 0) {
            std::cout << "Hint: The number is even." << std::endl;
        } else {
            std::cout << "Hint: The number is odd." << std::endl;
        }
    } else if (attempts == 5) {
        int midPoint = (minRange + maxRange) / 2;
        std::cout << "Hint: The number is " << (secretNumber <= midPoint ? "less" : "greater") << " than " << midPoint << "." << std::endl;
    }
}

// Function to calculate score
int calculateScore(int maxAttempts, int attempts, int difficulty) {
    int baseScore = (maxAttempts - attempts) * 10;  // Base score based on remaining attempts
    return baseScore * difficulty;  // Higher difficulty levels multiply the score
}

int main() {
    char playAgain = 'y';
    int totalScore = 0;

    while (playAgain == 'y' || playAgain == 'Y') {
        // Seed the random number generator with the current time
        std::srand(std::time(0));

        // Choose mode
        int mode;
        displayInstructions();
        std::cin >> mode;

        // Input for custom range
        int minRange, maxRange;
        std::cout << "Enter the minimum value for the range: ";
        std::cin >> minRange;
        std::cout << "Enter the maximum value for the range: ";
        std::cin >> maxRange;

        // Validate the range
        if (minRange >= maxRange) {
            std::cerr << "Invalid range. Please enter a valid range where the minimum is less than the maximum." << std::endl;
            continue;
        }

        int difficulty;
        std::cout << "Choose a difficulty level:" << std::endl;
        std::cout << "1. Easy (10 attempts)" << std::endl;
        std::cout << "2. Medium (7 attempts)" << std::endl;
        std::cout << "3. Hard (5 attempts)" << std::endl;
        std::cout << "4. Expert (3 attempts)" << std::endl;
        std::cout << "Enter your choice (1-4): ";
        std::cin >> difficulty;

        int maxAttempts = getMaxAttempts(difficulty);
        int secretNumber = std::rand() % (maxRange - minRange + 1) + minRange;
        int guess = 0;
        int attempts = 0;

        auto start = std::chrono::steady_clock::now();
        std::cout << "You have " << maxAttempts << " attempts to guess the number." << std::endl;

        // Game loop
        while (guess != secretNumber && attempts < maxAttempts) {
            std::cout << "Enter your guess: ";
            std::cin >> guess;
            attempts++;

            if (guess > secretNumber) {
                std::cout << "Too high! Try again." << std::endl;
            } else if (guess < secretNumber) {
                std::cout << "Too low! Try again." << std::endl;
            }

            giveHint(secretNumber, attempts, minRange, maxRange);

            if (guess == secretNumber) {
                std::cout << "Congratulations! You guessed the number in " << attempts << " attempts." << std::endl;
                int score = calculateScore(maxAttempts, attempts, difficulty);
                std::cout << "You earned " << score << " points!" << std::endl;
                totalScore += score;
            } else if (attempts == maxAttempts) {
                std::cout << "Sorry, you've run out of attempts. The secret number was " << secretNumber << "." << std::endl;
            }

            // Timed Mode: Check if the time limit has been exceeded
            if (mode == 2) {
                auto end = std::chrono::steady_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start).count();
                if (duration > 30) {  // 30 seconds time limit for Timed Mode
                    std::cout << "Time's up! The secret number was " << secretNumber << "." << std::endl;
                    break;
                }
            }
        }

        std::cout << "Your total score is: " << totalScore << std::endl;
        std::cout << "Do you want to play again? (y/n): ";
        std::cin >> playAgain;
    }

    std::cout << "Thank you for playing! Your final score is: " << totalScore << std::endl;
    return 0;
}
