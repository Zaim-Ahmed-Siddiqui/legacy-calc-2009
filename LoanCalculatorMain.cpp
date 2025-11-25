#include "LoanCalculator.h"
#include "LoanUtils.h"
#include <iostream>

using namespace std;

/**
 * @file LoanCalculatorMain.cpp
 * @brief Main entry point for the Loan Calculator command-line application.
 *
 * This program parses command-line arguments, sets up the LoanCalculator object,
 * and calls the appropriate calculation based on user input.
 */

/**
 * @brief Main function for the loan calculator program.
 *
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line argument strings.
 * @return Returns 0 on success, 1 if invalid or insufficient arguments were provided.
 *
 * The function performs the following steps:
 * 1. Creates a LoanCalculator object.
 * 2. Parses command-line arguments using parseCommandLine().
 * 3. If the calculation type is unknown, exits with code 1.
 * 4. Otherwise, calls printResult() to display the calculation output.
 */
int main(int argc, char **argv) {
    LoanCalculator calculator;

    // Parse command-line arguments and determine calculation type
    CALC_TYPE ct = parseCommandLine(argc, argv, calculator);

    // Exit if invalid or insufficient arguments
    if(ct == CALC_UNKNOWN) return 1;

    // Print the calculation results based on the parsed type
    printResult(ct, calculator);

    return 0;
}
