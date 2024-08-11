
#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <cctype>
#include <sstream>

struct Word {
    std::string word;
    std::string meaning;
    int familiarity; // 0: Not known, 1: Somewhat known, 2: Well known

    Word(std::string w, std::string m, int f = 0) : word(w), meaning(m), familiarity(f) {}
};

class LanguageApp {
private:
    std::vector<Word> vocabulary;
    const std::string filename = "vocabulary.txt";

    void loadVocabulary() {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Failed to open vocabulary file.\n";
            return;
        }

        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string word, meaning;
            int familiarity;

            if (!(iss >> word >> std::ws)) continue; // Read the word
            if (!std::getline(iss, meaning, ',')) continue; // Read the meaning
            if (!(iss >> familiarity)) continue; // Read the familiarity

            vocabulary.push_back(Word(word, meaning, familiarity));
        }

        file.close();
    }

    void saveVocabulary() {
        std::ofstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Failed to save vocabulary file.\n";
            return;
        }

        for (const auto& word : vocabulary) {
            file << word.word << " " << word.meaning << "," << word.familiarity << "\n";
        }
        file.close();
    }

    bool wordExists(const std::string& word) {
        for (const auto& w : vocabulary) {
            if (w.word == word) {
                return true;
            }
        }
        return false;
    }

    static bool caseInsensitiveCompare(const std::string& str1, const std::string& str2) {
        return std::equal(str1.begin(), str1.end(), str2.begin(), str2.end(),
            [](char a, char b) { return tolower(a) == tolower(b); });
    }

public:
    LanguageApp() {
        loadVocabulary();
    }

    ~LanguageApp() {
        saveVocabulary();
    }

    void addWord() {
        std::string word, meaning;
        std::cout << "Enter the word: ";
        std::cin >> word;
        std::cin.ignore(); // To ignore the newline character left by std::cin

        if (wordExists(word)) {
            std::cout << "Word already exists.\n";
            return;
        }

        std::cout << "Enter the meaning: ";
        std::getline(std::cin, meaning);
        vocabulary.push_back(Word(word, meaning));
        std::cout << "Word added successfully.\n";
    }

    void practiceQuiz() {
        if (vocabulary.empty()) {
            std::cout << "No words to practice.\n";
            return;
        }

        int correctAnswers = 0;
        for (auto& word : vocabulary) {
            std::string answer;
            std::cout << "What is the meaning of " << word.word << "? ";
            std::getline(std::cin, answer);

            if (caseInsensitiveCompare(answer, word.meaning)) {
                std::cout << "Correct!\n";
                word.familiarity = std::min(word.familiarity + 1, 2);
                correctAnswers++;
            } else {
                std::cout << "Wrong! The correct meaning is " << word.meaning << ".\n";
                word.familiarity = std::max(word.familiarity - 1, 0);
            }
        }
        std::cout << "You got " << correctAnswers << " out of " << vocabulary.size() << " correct.\n";
    }

    void displayProgress() {
        if (vocabulary.empty()) {
            std::cout << "No words added yet.\n";
            return;
        }

        std::cout << "Vocabulary Progress:\n";
        for (const auto& word : vocabulary) {
            std::cout << "Word: " << word.word << ", Meaning: " << word.meaning << ", Familiarity: " << word.familiarity << "\n";
        }
    }
};

int main() {
    LanguageApp app;
    int choice;

    while (true) {
        std::cout << "\nLanguage Learning App\n";
        std::cout << "1. Add New Word\n";
        std::cout << "2. Practice Quiz\n";
        std::cout << "3. Display Progress\n";
        std::cout << "4. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cin.ignore(); // To ignore the newline character left by std::cin

        switch (choice) {
            case 1:
                app.addWord();
                break;
            case 2:
                app.practiceQuiz();
                break;
            case 3:
                app.displayProgress();
                break;
            case 4:
                return 0;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
