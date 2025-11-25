#ifndef LOANUTILS_H
#define LOANUTILS_H

#include "LoanCalculator.h"

/**
 * @file LoanUtils.h
 * @brief Header for utility functions for command-line parsing and result printing.
 */

/**
 * @enum CALC_TYPE
 * @brief Enumeration of the different types of loan calculations.
 */
enum CALC_TYPE
{
    CALC_UNKNOWN = 0,   /**< Unknown or invalid calculation type */
    CALC_BALANCE = 100, /**< Calculate loan balance after payments */
    CALC_PAYMENT,       /**< Calculate monthly loan payment */
    CALC_NUMPAYMENTS,   /**< Calculate number of payments */
    CALC_AMOUNT,        /**< Calculate original loan amount */
    CALC_INTEREST       /**< Calculate yearly interest rate */
};

/**
 * @brief Parses command-line arguments and sets the corresponding values in a LoanCalculator object.
 *
 * This function reads the program arguments, sets the values in the LoanCalculator object,
 * and determines which calculation type was requested.
 *
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line argument strings.
 * @param calculator Reference to a LoanCalculator object where parsed values will be stored.
 * @return CALC_TYPE The selected calculation type, or CALC_UNKNOWN if the arguments are invalid.
 */
CALC_TYPE parseCommandLine(int argc, char **argv, LoanCalculator &calculator);

/**
 * @brief Prints the result of a loan calculation to the console.
 *
 * Based on the selected calculation type, this function performs the appropriate calculation
 * using the LoanCalculator object and prints the results, including detailed loan information.
 *
 * @param ct Calculation type (CALC_BALANCE, CALC_PAYMENT, CALC_NUMPAYMENTS, CALC_AMOUNT, CALC_INTEREST, CALC_UNKNOWN)
 * @param calculator Reference to the LoanCalculator object containing loan parameters
 */
void printResult(CALC_TYPE ct, LoanCalculator &calculator);

#endif // LOANUTILS_H
