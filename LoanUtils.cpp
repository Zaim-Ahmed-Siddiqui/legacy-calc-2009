#include "LoanUtils.h"
#include "LoanCalculator.h"
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

/**
 * @file LoanUtils.cpp
 * @brief Utility functions for parsing command-line arguments and printing results.
 */

/**
 * @brief Parses command-line arguments and sets values in LoanCalculator.
 *
 * This function reads the arguments provided to the program, sets
 * the appropriate values in the LoanCalculator object, and determines
 * the calculation type (balance, payment, number of payments, amount, or interest).
 *
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line argument strings.
 * @param calculator Reference to a LoanCalculator object where values will be set.
 * @return CALC_TYPE The calculation type selected, or CALC_UNKNOWN if arguments are invalid.
 *
 * Supported options:
 * - `-a <amount>`: Loan amount
 * - `-p <payment>`: Monthly payment
 * - `-N <months>`: Total loan period in months
 * - `-i <interest>`: Yearly interest rate
 * - `-ai <initialPayment>`: Initial down payment (optional)
 * - `-of <openingFee>`: Opening fee (optional)
 * - `-op <openingPercent>`: Opening fee percent (optional)
 * - `-cb`, `-cp`, `-cn`, `-ca`, `-ci`: Calculation type
 */
CALC_TYPE parseCommandLine(int argc, char **argv, LoanCalculator &calculator) {
    if(argc < 9) {
        cout << "Usage: ./LoanCalc -a <amount> -p <payment> -N <months> -i <interest> "
             << "[-ai <initialPayment>] [-of <openingFee>] [-op <openingPercent>] "
             << "[-cb|-cp|-cn|-ca|-ci]\n";
        return CALC_UNKNOWN;
    }

    CALC_TYPE ct = CALC_PAYMENT; // default calculation type

    for(int i = 1; i < argc; i++) {
        string arg = argv[i];

        if(arg == "-a" && i+1 < argc) {
            calculator.setAmount(stold(argv[++i]));
        }
        else if(arg == "-p" && i+1 < argc) {
            calculator.setPayment(stold(argv[++i]));
        }
        else if(arg == "-N" && i+1 < argc) {
            calculator.setPeriodTotal(stoi(argv[++i]));
        }
        else if(arg == "-i" && i+1 < argc) {
            calculator.setInterest(stold(argv[++i]));
        }
        else if(arg == "-ai" && i+1 < argc) {
            calculator.setInitialPayment(stold(argv[++i]));
        }
        else if(arg == "-of" && i+1 < argc) {
            calculator.setOpeningFee(stold(argv[++i]));
        }
        else if(arg == "-op" && i+1 < argc) {
            calculator.setOpeningPercent(stold(argv[++i]));
        }
        else if(arg == "-cb") { ct = CALC_BALANCE; }
        else if(arg == "-cp") { ct = CALC_PAYMENT; }
        else if(arg == "-cn") { ct = CALC_NUMPAYMENTS; }
        else if(arg == "-ca") { ct = CALC_AMOUNT; }
        else if(arg == "-ci") { ct = CALC_INTEREST; }
        else {
            cout << "Unknown option: " << arg << "\n";
        }
    }

    return ct;
}

/**
 * @brief Prints the result of a loan calculation.
 *
 * Based on the calculation type, this function performs the requested
 * calculation using the LoanCalculator object and prints the results
 * to the console. It also prints the detailed loan parameters using
 * the LoanCalculator::toString() method.
 *
 * @param ct Calculation type (CALC_BALANCE, CALC_PAYMENT, CALC_NUMPAYMENTS, CALC_AMOUNT, CALC_INTEREST, CALC_UNKNOWN)
 * @param calculator Reference to the LoanCalculator object containing loan parameters
 */
void printResult(CALC_TYPE ct, LoanCalculator &calculator)
{
    cout << endl;

    if(ct == CALC_BALANCE)
    {
        cout << "Loan Balance = " << calculator.calculateLoanBalance() << endl;
    }
    else if(ct == CALC_PAYMENT)
    {
        long double payment = calculator.calculatePayment();
        cout << "Monthly Payment = " << payment << "\n"
             << "Total amount paid = " << payment * calculator.getPeriodTotal() << endl;

        if(calculator.getOpeningPercent() != 0.0 || calculator.getOpeningFee() != 0.0)
        {
            cout << "Effective Interest Rate with fees = "
                 << calculator.calculateEffectiveInterestRate() << "%" << endl;
        }
    }
    else if(ct == CALC_NUMPAYMENTS)
    {
        cout << "Number of Payments = " << calculator.calculateNumberPayments() << endl;
    }
    else if(ct == CALC_AMOUNT)
    {
        cout << "Loan Amount = " << calculator.calculateLoanAmount() << endl;
    }
    else if(ct == CALC_INTEREST)
    {
        cout << "Yearly Interest Rate = " << calculator.calculateInterestRate() << "%" << endl;
    }
    else if(ct == CALC_UNKNOWN)
    {
        cout << "Invalid calculation type." << endl;
    }

    cout << "\n-- Loan Details --\n";
    cout << calculator.toString() << endl;
}
