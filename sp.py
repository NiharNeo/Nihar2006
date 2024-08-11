import speech_recognition as sr
import pyttsx3
from translate import Translator

def translate_text(text, target_language):
    try:
        translator = Translator(to_lang=target_language)
        translation = translator.translate(text)
        return translation
    except Exception as e:
        print(f"Error: {e}")
        return None

def speech_to_text():
    recognizer = sr.Recognizer()
    with sr.Microphone() as source:
        print("Listening for input...")
        audio = recognizer.listen(source)
        try:
            text = recognizer.recognize_google(audio)
            print(f"You said: {text}")
            return text
        except sr.UnknownValueError:
            print("Sorry, I could not understand the audio.")
            return None
        except sr.RequestError:
            print("Sorry, there was an error with the speech recognition service.")
            return None

def text_to_speech(text):
    engine = pyttsx3.init()
    engine.say(text)
    engine.runAndWait()

def main():
    print("Welcome to the Translator with Speech!")

    print("Speak the text to translate...")
    text = speech_to_text()
    if not text:
        return

    target_language = input("Enter the target language code (e.g., 'es' for Spanish): ")

    translated_text = translate_text(text, target_language)

    if translated_text:
        print(f"Translated text: {translated_text}")
        text_to_speech(translated_text)
    else:
        print("Translation failed.")

if __name__ == "__main__":
    main()
