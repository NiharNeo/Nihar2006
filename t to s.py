from googletrans import Translator
import pyttsx3

def translate_text(text, target_language):
    try:
        translator = Translator()
        translation = translator.translate(text, dest=target_language)
        return translation.text
    except Exception as e:
        print(f"Error in translation: {e}")
        return None

def text_to_speech(text):
    try:
        engine = pyttsx3.init()
        engine.say(text)
        engine.runAndWait()
    except Exception as e:
        print(f"Error in text-to-speech: {e}")

def main():
    print("Welcome to the Text to Speech Translator!")

    text = input("Enter the text to translate: ")
    target_language = input("Enter the target language code (e.g., 'es' for Spanish): ")

    translated_text = translate_text(text, target_language)

    if translated_text:
        print(f"Translated text: {translated_text}")
        print("Playing translated text...")
        text_to_speech(translated_text)
    else:
        print("Translation failed.")

if __name__ == "__main__":
    main()

