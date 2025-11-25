#ifndef LOANCALCULATOR_H_INCLUDED
#define LOANCALCULATOR_H_INCLUDED

#include <string>

/**
 * @class LoanCalculator
 * @brief A simple loan calculator for computing loan balance, EMI, number of payments, and interest rates.
 *
 * This class supports calculating:
 * - Loan balance after n payments
 * - Monthly payment (EMI)
 * - Number of payments required to pay off a loan
 * - Original loan amount
 * - Yearly interest rate (approximate)
 * - Effective interest rate including fees
 */
class LoanCalculator
{
public:
    /**
     * @brief Constructs a new LoanCalculator object with default values.
     */
    LoanCalculator();

    /**
     * @brief Destructor.
     */
    ~LoanCalculator() {}

    // ================= Setters and Getters =================

    /**
     * @brief Set the total loan amount.
     * @param A The principal loan amount.
     */
    void setAmount(long double A);

    /**
     * @brief Get the total loan amount.
     * @return The principal loan amount.
     */
    long double getAmount() const;

    /**
     * @brief Set the initial down payment for the loan.
     * @param initialA The initial payment amount.
     */
    void setInitialPayment(long double initialA);

    /**
     * @brief Get the initial down payment.
     * @return The initial payment amount.
     */
    long double getInitialPayment() const;

    /**
     * @brief Set the yearly interest rate.
     * @param i Yearly interest rate in percent (e.g., 6.75).
     *
     * Internally, the monthly interest will be calculated as i / 12 / 100.
     */
    void setInterest(long double i);

    /**
     * @brief Get the yearly interest rate.
     * @return Yearly interest rate in percent.
     */
    long double getInterest() const;

    /**
     * @brief Get the monthly periodic interest rate.
     * @return Monthly interest as decimal (e.g., 0.0056 for 6.75% yearly).
     */
    long double getPeriodicInterest() const;

    /**
     * @brief Set the monthly payment (EMI).
     * @param P Monthly payment amount.
     */
    void setPayment(long double P);

    /**
     * @brief Get the monthly payment (EMI).
     * @return Monthly payment amount.
     */
    long double getPayment() const;

    /**
     * @brief Set the total number of payment periods.
     * @param N Total loan period in months.
     */
    void setPeriodTotal(int N);

    /**
     * @brief Get the total number of payment periods.
     * @return Total loan period in months.
     */
    int getPeriodTotal() const;

    /**
     * @brief Set the number of elapsed payment periods.
     * @param n Number of months elapsed.
     */
    void setPeriodElapsed(int n);

    /**
     * @brief Get the number of elapsed payment periods.
     * @return Number of months elapsed.
     */
    int getPeriodElapsed() const;

    /**
     * @brief Set a fixed fee charged when opening the loan.
     * @param fee Opening fee amount.
     */
    void setOpeningFee(long double fee);

    /**
     * @brief Get the fixed opening fee.
     * @return Opening fee amount.
     */
    long double getOpeningFee() const;

    /**
     * @brief Set a percentage-based fee for opening the loan.
     * @param percent Percentage of loan amount as opening fee.
     */
    void setOpeningPercent(long double percent);

    /**
     * @brief Get the percentage-based opening fee.
     * @return Opening fee percentage.
     */
    long double getOpeningPercent() const;

    /**
     * @brief Reset all loan parameters to zero/defaults.
     */
    void reset();

    // ================= Calculation Methods =================

    /**
     * @brief Calculate the loan balance after n payments.
     * @return Remaining loan balance.
     * @throws std::invalid_argument if required parameters are not set.
     */
    long double calculateLoanBalance();

    /**
     * @brief Calculate the monthly payment (EMI).
     * @return Monthly payment amount.
     * @throws std::invalid_argument if required parameters are not set.
     */
    long double calculatePayment();

    /**
     * @brief Calculate the number of payments needed to pay off the loan.
     * @return Number of payments.
     * @throws std::invalid_argument if required parameters are not set.
     */
    long double calculateNumberPayments();

    /**
     * @brief Calculate the original loan amount given payment, interest, and total period.
     * @return Loan amount.
     * @throws std::invalid_argument if required parameters are not set.
     */
    long double calculateLoanAmount();

    /**
     * @brief Estimate the yearly interest rate given amount, payment, and total period.
     * @return Yearly interest rate in percent.
     * @throws std::invalid_argument if required parameters are not set.
     */
    long double calculateInterestRate();

    /**
     * @brief Calculate effective interest rate including opening fees.
     * @return Effective yearly interest rate in percent.
     * @throws std::invalid_argument if required parameters are not set.
     */
    long double calculateEffectiveInterestRate();

    /**
     * @brief Return a string summary of all loan parameters.
     * @return Formatted loan details as a string.
     */
    std::string toString();

private:
    long double amount_;        ///< Loan amount
    bool amountSet_;            ///< Flag if amount is set

    long double initialPayment_; ///< Initial down payment

    long double interest_;        ///< Yearly interest rate in percent
    long double interestPeriodic_;///< Monthly periodic interest rate
    bool interestSet_;            ///< Flag if interest is set

    long double payment_;        ///< Monthly payment
    bool paymentSet_;            ///< Flag if payment is set

    int periodTotal_;            ///< Total number of months
    bool periodTotalSet_;        ///< Flag if total period is set

    int periodElapsed_;          ///< Number of elapsed months
    bool periodElapsedSet_;      ///< Flag if elapsed period is set

    long double openingFee_;     ///< Fixed opening fee
    long double openingPercent_; ///< Opening fee as percentage
};

#endif // LOANCALCULATOR_H_INCLUDED
