-- Keep a log of any SQL queries you execute as you solve the mystery.

-- SELECT * FROM crime_scene_reports
-- WHERE year = 2021 AND month = 7 AND day = 28 AND street = "Humphrey Street";

-- 10:15am, Humphrey Street bakery, three witnesses

--SELECT * FROM interviews
--WHERE year = 2021 AND month = 7 AND day = 28 AND transcript LIKE "%bakery%";

/* Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking
   lot and drive away. If you have security footage from the bakery parking lot, you might want to look
   for cars that left the parking lot in that time frame. */

/* I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at
   Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money. */

/* As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the call,
   I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief
   then asked the person on the other end of the phone to purchase the flight ticket. */


-- SELECT license_plate FROM bakery_security_logs
-- WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND activity = "exit"
-- AND minute BETWEEN 15 AND 25;

/*
SELECT phone_number FROM people
WHERE name IN
(
    SELECT name FROM people
    WHERE id IN
    (
        SELECT person_id FROM bank_accounts
        WHERE account_number IN
        (
            SELECT DISTINCT account_number FROM atm_transactions
            WHERE atm_location = "Leggett Street"
            AND year = 2021 AND month = 7 AND day = 28
            AND transaction_type = "withdraw"
        )
    )
    AND license_plate IN
    (
        SELECT license_plate FROM bakery_security_logs
        WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND activity = "exit"
        AND minute BETWEEN 15 AND 25
    )
);
*/

SELECT name FROM people
WHERE id IN
(
    SELECT person_id FROM bank_accounts
    WHERE account_number IN
    (
        SELECT DISTINCT account_number FROM atm_transactions
        WHERE atm_location = "Leggett Street"
        AND year = 2021 AND month = 7 AND day = 28
        AND transaction_type = "withdraw"
    )
)
AND license_plate IN
(
    SELECT license_plate FROM bakery_security_logs
    WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND activity = "exit"
    AND minute BETWEEN 15 AND 25
);

SELECT name FROM people
WHERE phone_number IN
(
    SELECT receiver FROM phone_calls
    WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60
    AND caller IN
    (
        SELECT phone_number FROM people
        WHERE name IN
        (
            SELECT name FROM people
            WHERE id IN
            (
                SELECT person_id FROM bank_accounts
                WHERE account_number IN
                (
                    SELECT DISTINCT account_number FROM atm_transactions
                    WHERE atm_location = "Leggett Street"
                    AND year = 2021 AND month = 7 AND day = 28
                    AND transaction_type = "withdraw"
                )
            )
            AND license_plate IN
            (
                SELECT license_plate FROM bakery_security_logs
                WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND activity = "exit"
                AND minute BETWEEN 15 AND 25
            )
        )
    )
);

SELECT * FROM flights
WHERE origin_airport_id IN
(
    SELECT id FROM airports
    WHERE abbreviation = "CSF"
)
AND year = 2021 AND month = 7 AND day = 29;

-- 36

SELECT name FROM people WHERE
passport_number IN
(
    SELECT passport_number FROM passengers
    WHERE passport_number IN
    (
        SELECT passport_number FROM people
        WHERE name IN ('Iman', 'Luca', 'Diana', 'Bruce')
    )
    AND flight_id = 36
);

SELECT name FROM people
WHERE phone_number IN
(
    SELECT receiver FROM phone_calls
    WHERE caller IN
    (
        SELECT phone_number FROM people
        WHERE name = "Bruce"
    )
    AND year = 2021 AND month = 7 AND day = 28 AND duration < 60
);

SELECT * FROM airports;