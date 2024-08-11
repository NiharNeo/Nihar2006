import speech_recognition as sr
from gtts import gTTS
import os
from nltk.chat.util import Chat, reflections

# Speech to Text
def recognize_speech():
    recognizer = sr.Recognizer()
    with sr.Microphone() as source:
        print("Listening...")
        audio = recognizer.listen(source)
        try:
            text = recognizer.recognize_google(audio)
            print(f"You said: {text}")
            return text
        except sr.UnknownValueError:
            print("Sorry, I did not understand that.")
            return None
        except sr.RequestError:
            print("Could not request results from Google Speech Recognition service.")
            return None

# Text to Speech
def speak_text(text):
    tts = gTTS(text=text, lang='en')
    tts.save("response.mp3")
    os.system("start response.mp3")  # Use 'afplay response.mp3' on macOS or 'mpg321 response.mp3' on Linux

# Chatbot Logic
pairs = [
    [
        r"hi|hello|hey",
        ["Hello, how can I help you?", "Hi there! How can I assist you today?"]
    ],
    [
        r"what is your name\??",
        ["I am a chatbot created to assist you with your queries.", "You can call me Chatbot."]
    ],
    [
        r"how are you\??",
        ["I'm a bot, I don't have feelings, but thank you for asking! How can I help you?"]
    ],
    [
        r"quit|exit",
        ["Goodbye! Have a nice day!", "See you later!"]
    ],
]

chatbot = Chat(pairs, reflections)

def chatbot_response(user_input):
    response = chatbot.respond(user_input)
    return response if response else "I'm sorry, I didn't understand that."

# Main Function
def main():
    print("Say 'quit' or 'exit' to end the conversation.")
    while True:
        user_input = recognize_speech()
        if user_input:
            if user_input.lower() in ["quit", "exit"]:
                speak_text("Goodbye! Have a nice day!")
                break
            response = chatbot_response(user_input)
            print(f"Chatbot: {response}")
            speak_text(response)

if __name__ == "__main__":
    main()
