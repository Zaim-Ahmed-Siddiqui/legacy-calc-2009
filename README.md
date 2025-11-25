# Loan Calculator

## Description
This is a **console-based Loan Calculator** written in C++. It allows you to calculate various loan-related values, including:

- Monthly payment
- Loan balance after a certain number of payments
- Total number of payments
- Original loan amount
- Yearly interest rate (approximate)
- Effective interest rate including fees

The program uses command-line arguments and does not require a GUI.

---

## Project Files

- `LoanCalculator.h` / `LoanCalculator.cpp` – Implements the `LoanCalculator` class with all loan calculation methods.  
- `LoanUtils.h` / `LoanUtils.cpp` – Utility functions for parsing command-line arguments and printing results.  
- `LoanCalculatorMain.cpp` – Main program that ties together the calculator and utilities.  
- `README.md` – This file with usage instructions.

---

## Compilation

Make sure you have a C++ compiler (like `g++`) that supports C++17.  

To compile:

```bash
g++ -std=c++17 LoanCalculatorMain.cpp LoanCalculator.cpp LoanUtils.cpp -o LoanCalc
This will create an executable named LoanCalc.

## Usage

Run the program with the following command-line arguments:

bash
Copy code
./LoanCalc -a <amount> -p <payment> -N <months> -i <interest> [options]

## Required Arguments:

-a : Total loan amount

-p : Monthly payment

-N : Total number of months (loan period)

-i : Yearly interest rate (e.g., 6.75)

## Optional Arguments:

-cb : Calculate loan balance after elapsed payments

-cp : Calculate monthly payment

-cn : Calculate number of payments

-ca : Calculate loan amount

-ci : Calculate yearly interest rate

-ai : Initial down payment (default 0)

-of : Opening fee (default 0)

-op : Opening fee percentage (default 0)

## Examples
Calculate monthly payment:

bash
Copy code
./LoanCalc -a 10000 -N 60 -i 5 -cp
Calculate loan balance after 12 payments:

bash
Copy code
./LoanCalc -a 15000 -p 300 -N 48 -i 6 -cb -n 12
Calculate effective interest with opening fees:

bash
Copy code
./LoanCalc -a 20000 -p 400 -N 72 -i 7 -of 100 -op 2.5 -cp
Output
The program prints:

Requested calculation (e.g., monthly payment, loan balance, etc.)

Loan details including amount, payment, interest, period, and fees

Example:

sql
Copy code
Monthly Payment = 193.34
Total amount paid = 11600.40
Effective Interest Rate with fees = 5.12%

-- Loan Details --
Initial Amount:      10000.00
Monthly payment:     193.34
Loan Period:         60 months

## Notes

The program validates input and will show usage if required arguments are missing.

All calculations use standard loan formulas with monthly compounding interest.

Code is modular: main program, utility functions, and loan calculator class.

## Author
Zaim Ahmed Siddiqui
Software Engineering Student
FAST NUCES Peshawar