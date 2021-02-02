-- Keep a log of any SQL queries you execute as you solve the mystery.

--get description of crime scene
SELECT description 
FROM crime_scene_reports 
WHERE month = 7 AND day = 28 AND year = 2020
AND street = "Chamberlin Street";

--access witness transcripts
SELECT name, transcript 
FROM interviews 
WHERE year = 2020 AND month = 7 AND day = 28;

--access courthouse security logs
SELECT hour, minute, activity, license_plate
FROM courthouse_security_logs
WHERE year = 2020 AND month = 7 AND day = 28 AND hour = 10 AND minute < 30;

--access phone records
SELECT caller, receiver, duration 
FROM phone_calls
WHERE year = 2020 AND month = 7 AND day = 28 AND duration < 60;

--check ATM logs
SELECT transaction_type, amount, account_number
FROM atm_transactions
WHERE year = 2020 AND month = 7 AND day = 28 AND atm_location = "Fifer Street";

--check flights
SELECT flights.id, airports.full_name, airports.city, flights.hour, flights.minute
FROM airports JOIN flights ON flights.destination_airport_id = airports.id
WHERE year = 2020 AND month = 7 AND day = 29 AND origin_airport_id = 
(SELECT airports.id FROM airports JOIN flights on flights.origin_airport_id = airports.id
WHERE airports.city = "Fiftyville");

--check passengers
SELECT passengers.passport_number, passengers.seat
FROM passengers JOIN flights ON passengers.flight_id = flights.id
WHERE flights.id = 36;

--check people
SELECT name, phone_number, passport_number, license_plate FROM people
WHERE phone_number IN ("(130) 555-0289", "(499) 555-9472", "(367) 555-5533", "(499) 555-9472", "(286) 555-6063", "(770) 555-1861", "(031) 555-6622", "(826) 555-1652", "(338) 555-6650 ")
AND passport_number IN (7214083635, 1695452385, 5773159633, 1540955065, 8294398571, 1988161715, 9878712108, 8496433585)
AND license_plate IN ("5P2BI95", "94KL13X", "6P58WS2", "4328GD8", "G412CB7", "L93JTIZ", "322W7JE", "0NTHK55");

--check bank_accounts
SELECT people.name
FROM people JOIN bank_accounts ON bank_accounts.person_id = people.id
WHERE bank_accounts.account_number IN (28500762, 28296815, 76054385, 49610011, 16153065, 25506511, 81061156, 26013199);

--having checked my phone log I copied to word doc, the receiver of Ernest's phone call had phone number (375) 555-8161 

--check people to find accomplice
SELECT name, phone_number FROM people
WHERE phone_number = ("(375) 555-8161");