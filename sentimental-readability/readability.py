from cs50 import get_string

def main():
    text = get_string()
    nLetters = nWords = nSentences = 0

    nLetters = CountLetters(text)
    nWords = CountWords(text)
    nSentences = CountSentences(text)

    L = (nLetters / nWords) * 100
    S = (nSentences / nWords) * 100
    grade = round(0.0588 * L - 0.296 * S - 15.8)

    if grade < 1:
        print("Before Grade 1")
    elif grade > 16:
        print("Grade 16+")
    else:
        print(f"Grade {grade}")

    exit(0)

def CountLetters(text: str) -> int:
    count = 0
    for letter in text:
        if letter.isalpha():
            count += 1
    return count

def CountWords(text: str) -> int:
    count = 0
    for letter in text:
        if letter.isspace():
            count += 1
    count += 1 # Because every word has a space before it except the first one
    return count

def CountSentences(text: str) -> int:
    count = 0
    for letter in text:
        if letter in [".", "?", "!"]:
            count += 1
    return count

main()