# Legacy Loan Calculator (Refactored Version)

## Requirements
- g++ compiler (MinGW or Linux g++)
- Git installed
- Doxygen (for documentation)
- GoogleTest (for unit testing)
- A terminal or Git Bash

## How to Build
To compile the program, open Git Bash or terminal in the project folder and run:

g++ -std=c++11 src/*.cpp -o calc

This will produce an executable file named "calc".

## How to Run
Run the program using:

./calc -cp -a 100000 -i 12 -n 360

Where:
- `-a` = loan amount
- `-i` = interest rate
- `-n` = number of months

Example:
./calc -cp -a 200000 -i 10 -n 240

## Project Structure
legacy-calc-2009/
│── src/
│   ├── main.cpp
│   ├── Loan.h
│   └── Loan.cpp
│── test/
│   └── test_emi.cpp
│── config.txt
│── docs/
│── Doxyfile
│── README.md
│── REPORT.pdf

## Contributors
- Zaim Ahmed Siddiqui
- Muhammad Waqar Wali Khan


