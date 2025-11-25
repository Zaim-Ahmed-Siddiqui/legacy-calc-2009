#include <iostream>
#include <string>
#include <cstdlib>
#include <stdexcept>
#include "LoanCalculator.h"

using namespace std;

enum CALC_TYPE
{
    CALC_UNKNOWN = 0,
    CALC_BALANCE = 100,
    CALC_PAYMENT,
    CALC_NUMPAYMENTS,
    CALC_AMOUNT,
    CALC_INTEREST
};

// Simple helper to print usage
void printUsage()
{
    cout << "Usage: LoanCalc [calculation type] options\n";
    cout << "Calculation types:\n";
    cout << "  -cb   Calculate Loan Balance\n";
    cout << "  -cp   Calculate Payment\n";
    cout << "  -cn   Calculate Number of Payments\n";
    cout << "  -ca   Calculate Initial Loan Amount\n";
    cout << "  -ci   Calculate Interest Rate\n";
    cout << "\nOptions:\n";
    cout << "  -a <amount>      Loan Amount\n";
    cout << "  -p <payment>     Monthly Payment\n";
    cout << "  -N <months>      Total Period\n";
    cout << "  -n <months>      Elapsed Period\n";
    cout << "  -i <interest>    Interest Rate (yearly %)\n";
    cout << "  -ai <payment>    Initial Payment\n";
    cout << "  -of <fee>        Opening Fee\n";
    cout << "  -op <percent>    Opening Fee %\n";
}

// Helper to parse long double from argument
long double getArgValue(int argc, char **argv, const string &flag, long double defaultVal = 0.0L)
{
    for (int i = 1; i < argc - 1; ++i)
    {
        if (argv[i] == flag)
        {
            return strtold(argv[i + 1], nullptr);
        }
    }
    return defaultVal;
}

// Main program
int main(int argc, char **argv)
{
    if (argc < 2)
    {
        printUsage();
        return 1;
    }

    LoanCalculator calculator;
    string calcType = argv[1];

    // Set values from arguments
    calculator.setAmount(getArgValue(argc, argv, "-a"));
    calculator.setInitialPayment(getArgValue(argc, argv, "-ai"));
    calculator.setInterest(getArgValue(argc, argv, "-i"));
    calculator.setPayment(getArgValue(argc, argv, "-p"));
    calculator.setPeriodTotal(getArgValue(argc, argv, "-N"));
    calculator.setPeriodElapsed(getArgValue(argc, argv, "-n"));
    calculator.setOpeningFee(getArgValue(argc, argv, "-of"));
    calculator.setOpeningPercent(getArgValue(argc, argv, "-op"));

    try
    {
        if (calcType == "-cb")
        {
            cout << "Loan Balance = " << calculator.calculateLoanBalance() << endl;
        }
        else if (calcType == "-cp")
        {
            long double payment = calculator.calculatePayment();
            cout << "Monthly Payment = " << payment << endl;
            cout << "Total Amount Paid = " << (payment * calculator.getPeriodTotal()) << endl;
            if (calculator.getOpeningFee() != 0.0L || calculator.getOpeningPercent() != 0.0L)
                cout << "Effective Interest Rate with fees = " << calculator.calculateEffectiveInterestRate() << "%" << endl;
        }
        else if (calcType == "-cn")
        {
            cout << "Number of Payments = " << calculator.calculateNumberPayments() << endl;
        }
        else if (calcType == "-ca")
        {
            cout << "Initial Loan Amount = " << calculator.calculateLoanAmount() << endl;
        }
        else if (calcType == "-ci")
        {
            cout << "Yearly Interest Rate = " << calculator.calculateInterestRate() << "%" << endl;
        }
        else
        {
            cout << "Unknown calculation type." << endl;
            printUsage();
            return 1;
        }

        // Print set values
        cout << "\n--- Loan Details ---\n";
        cout << calculator.toString() << endl;
    }
    catch (const exception &e)
    {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    return 0;
}
