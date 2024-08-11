from translate import Translator

def translate_text(text, target_language):
    try:
        translator = Translator(to_lang=target_language)
        translation = translator.translate(text)
        return translation
    except Exception as e:
        print(f"Error: {e}")
        return None

def main():
    print("Welcome to the Translator!")

    text = input("Enter the text to translate: ")
    target_language = input("Enter the target language code (e.g., 'es' for Spanish): ")

    translated_text = translate_text(text, target_language)

    if translated_text:
        print(f"Translated text: {translated_text}")
    else:
        print("Translation failed.")

if __name__ == "__main__":
    main()
