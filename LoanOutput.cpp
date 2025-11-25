#include "LoanUtils.h"
#include "LoanCalculator.h"
#include <iostream>
using namespace std;

/**
 * @file LoanUtils.cpp
 * @brief Utility functions for Loan Calculator command-line application.
 */

/**
 * @brief Prints the result of a loan calculation based on the calculation type.
 *
 * This function takes the calculation type and a LoanCalculator object,
 * performs the requested calculation, and prints the results to standard output.
 *
 * @param ct The calculation type (CALC_BALANCE, CALC_PAYMENT, CALC_NUMPAYMENTS, CALC_AMOUNT, CALC_INTEREST, or CALC_UNKNOWN)
 * @param calculator The LoanCalculator object containing loan parameters
 *
 * The function displays:
 * - Loan balance
 * - Monthly payment and total amount paid
 * - Effective interest rate including fees
 * - Number of payments
 * - Loan amount
 * - Yearly interest rate
 * - Full loan details using calculator.toString()
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
