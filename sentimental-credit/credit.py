card = input("Enter a credit card number: ")

digit_index = 1
luhn_sum = 0
for digit in reversed(card):
    if digit_index % 2 == 0:
        tmp = int(digit) * 2
        while tmp != 0:
            luhn_sum += tmp % 10
            tmp = tmp // 10
    else:
        luhn_sum += int(digit)
    digit_index += 1

if luhn_sum % 10 != 0:
    print("INVALID")
else:
    firstTwoDigits = int(card[0:2])
    if (len(card) == 15):
        if (firstTwoDigits == 34 or firstTwoDigits == 37):
            print("AMEX")
    elif (len(card) == 16):
        if (firstTwoDigits >= 51 and firstTwoDigits <= 55):
            print("MASTERCARD")
        elif (firstTwoDigits // 10 == 4):
            print("VISA")
    elif (len(card) == 13 and firstTwoDigits // 10 == 4):
        print("VISA")
    else:
        print("INVALID")