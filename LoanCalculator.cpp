#include <iostream>
#include <cmath>
#include <stdexcept>
#include <sstream>
#include <iomanip>

#include "LoanCalculator.h"

using namespace std;

/**
 * @brief Construct a new LoanCalculator object.
 *
 * Initializes all loan parameters to default values.
 */
LoanCalculator::LoanCalculator() :
    amountSet_(false),
    initialPayment_(0.0),
    interestSet_(false),
    paymentSet_(false),
    periodTotalSet_(false),
    periodElapsedSet_(false),
    openingFee_(0.0),
    openingPercent_(0.0),
    interestPeriodic_(0.0)
{
}

// ================= Setters and Getters =================

/**
 * @brief Set the total loan amount.
 * @param A The principal loan amount.
 */
void LoanCalculator::setAmount(long double A) { amount_ = A; amountSet_ = true; }

/**
 * @brief Get the total loan amount.
 * @return Principal loan amount.
 */
long double LoanCalculator::getAmount() const { return amount_; }

/**
 * @brief Set the initial down payment.
 * @param initialA The initial payment amount.
 */
void LoanCalculator::setInitialPayment(long double initialA) { initialPayment_ = initialA; }

/**
 * @brief Get the initial down payment.
 * @return Initial payment amount.
 */
long double LoanCalculator::getInitialPayment() const { return initialPayment_; }

/**
 * @brief Set yearly interest rate.
 * @param i Yearly interest in percent (e.g., 6.75)
 *
 * Sets the internal monthly interest rate automatically.
 */
void LoanCalculator::setInterest(long double i) { interest_ = i; interestSet_ = true; interestPeriodic_ = i/100.0/12.0; }

/**
 * @brief Get the yearly interest rate.
 * @return Yearly interest in percent.
 */
long double LoanCalculator::getInterest() const { return interest_; }

/**
 * @brief Get monthly periodic interest rate.
 * @return Monthly interest rate as decimal.
 */
long double LoanCalculator::getPeriodicInterest() const { return interestPeriodic_; }

/**
 * @brief Set monthly payment (EMI).
 * @param P Monthly payment amount.
 */
void LoanCalculator::setPayment(long double P) { payment_ = P; paymentSet_ = true; }

/**
 * @brief Get monthly payment (EMI).
 * @return Monthly payment amount.
 */
long double LoanCalculator::getPayment() const { return payment_; }

/**
 * @brief Set total number of payment periods (months).
 * @param N Total loan period in months.
 */
void LoanCalculator::setPeriodTotal(int N) { periodTotal_ = N; periodTotalSet_ = true; }

/**
 * @brief Get total number of payment periods.
 * @return Total loan period in months.
 */
int LoanCalculator::getPeriodTotal() const { return periodTotal_; }

/**
 * @brief Set number of elapsed payments (months).
 * @param n Number of months elapsed.
 */
void LoanCalculator::setPeriodElapsed(int n) { periodElapsed_ = n; periodElapsedSet_ = true; }

/**
 * @brief Get number of elapsed payments (months).
 * @return Months elapsed.
 */
int LoanCalculator::getPeriodElapsed() const { return periodElapsed_; }

/**
 * @brief Set fixed loan opening fee.
 * @param fee Opening fee amount.
 */
void LoanCalculator::setOpeningFee(long double fee) { openingFee_ = fee; }

/**
 * @brief Get fixed loan opening fee.
 * @return Opening fee amount.
 */
long double LoanCalculator::getOpeningFee() const { return openingFee_; }

/**
 * @brief Set percentage-based loan opening fee.
 * @param percent Percentage of loan amount as opening fee.
 */
void LoanCalculator::setOpeningPercent(long double percent) { openingPercent_ = percent; }

/**
 * @brief Get percentage-based opening fee.
 * @return Opening fee percentage.
 */
long double LoanCalculator::getOpeningPercent() const { return openingPercent_; }

/**
 * @brief Reset all loan parameters to defaults.
 */
void LoanCalculator::reset() {
    amount_ = initialPayment_ = interest_ = interestPeriodic_ = payment_ = openingFee_ = openingPercent_ = 0.0;
    periodTotal_ = periodElapsed_ = 0;
    amountSet_ = interestSet_ = paymentSet_ = periodTotalSet_ = periodElapsedSet_ = false;
}

// ================= Calculation Methods =================

/**
 * @brief Calculate remaining loan balance after elapsed payments.
 * @return Loan balance.
 * @throws std::invalid_argument if amount, interest, payment, or elapsed period is not set.
 */
long double LoanCalculator::calculateLoanBalance() {
    if(!amountSet_ || !interestSet_ || !periodElapsedSet_ || !paymentSet_)
        throw invalid_argument("Must set loan amount, interest, payment, and elapsed period");
    return (amount_*pow(1+interestPeriodic_, periodElapsed_)) - (payment_/interestPeriodic_)*(pow(1+interestPeriodic_, periodElapsed_)-1);
}

/**
 * @brief Calculate monthly payment (EMI) including fees.
 * @return Monthly payment amount.
 * @throws std::invalid_argument if amount, interest, or total period is not set.
 */
long double LoanCalculator::calculatePayment() {
    if(!amountSet_ || !interestSet_ || !periodTotalSet_)
        throw invalid_argument("Must set loan amount, interest, and total period");

    long double baseAmount = amount_ - initialPayment_;
    long double feeAmount = openingFee_ + baseAmount * (openingPercent_/100.0);
    long double totalAmount = baseAmount + feeAmount;

    return (interestPeriodic_ * totalAmount) / (1 - pow(1+interestPeriodic_, -periodTotal_));
}

/**
 * @brief Calculate the number of payments needed to repay the loan.
 * @return Number of payments.
 * @throws std::invalid_argument if amount, interest, or payment is not set.
 */
long double LoanCalculator::calculateNumberPayments() {
    if(!amountSet_ || !interestSet_ || !paymentSet_)
        throw invalid_argument("Must set loan amount, interest, and payment");

    return (-log10(1.0 - (interestPeriodic_ * amount_ / payment_))) / log10(1.0 + interestPeriodic_);
}

/**
 * @brief Calculate the original loan amount based on payment, interest, and period.
 * @return Loan amount.
 * @throws std::invalid_argument if payment, interest, or total period is not set.
 */
long double LoanCalculator::calculateLoanAmount() {
    if(!paymentSet_ || !interestSet_ || !periodTotalSet_)
        throw invalid_argument("Must set payment, interest, and total period");

    return (payment_/interestPeriodic_) * (1 - pow(1+interestPeriodic_, -periodTotal_));
}

/**
 * @brief Estimate yearly interest rate (approximate) based on loan parameters.
 * @return Yearly interest rate in percent.
 * @throws std::invalid_argument if amount, payment, or total period is not set.
 */
long double LoanCalculator::calculateInterestRate() {
    if(!amountSet_ || !paymentSet_ || !periodTotalSet_)
        throw invalid_argument("Must set amount, payment, and total period");

    long double months = static_cast<long double>(periodTotal_);
    long double q = log10(1.0 + 1.0 / months) / log10(2.0);
    long double monthlyInterest = pow((pow(1.0 + payment_/amount_, 1.0/q) -1.0), q) -1.0;
    return monthlyInterest*12*100;
}

/**
 * @brief Calculate effective yearly interest rate including fees.
 * @return Effective interest rate in percent.
 * @throws std::invalid_argument if amount or total period is not set.
 */
long double LoanCalculator::calculateEffectiveInterestRate() {
    if(!amountSet_ || !periodTotalSet_)
        throw invalid_argument("Must set amount and total period");

    long double payment = calculatePayment();
    long double baseAmount = amount_ - initialPayment_;
    long double months = static_cast<long double>(periodTotal_);
    long double q = log10(1.0 + 1.0/ months) / log10(2.0);
    long double monthlyInterest = pow((pow(1.0 + payment/baseAmount, 1.0/q) -1.0), q) -1.0;
    return monthlyInterest*12*100;
}

/**
 * @brief Return a string summary of the loan details.
 * @return Formatted string containing all loan parameters.
 */
string LoanCalculator::toString() {
    stringstream ss;
    ss << fixed << setprecision(2);

    if(amountSet_) ss << "Initial Amount: " << amount_ << "\n";
    if(initialPayment_ != 0.0) {
        ss << "Initial Payment: " << initialPayment_ << "\n";
        ss << "Actual Loan Amount: " << (amount_ - initialPayment_) << "\n";
    }
    if(interestSet_) ss << "Yearly Interest: " << interest_ << "%\n";
    if(paymentSet_) ss << "Monthly payment: " << payment_ << "\n";
    if(periodTotalSet_) ss << "Loan Period: " << periodTotal_ << " months\n";
    if(periodElapsedSet_) ss << "Elapsed Period: " << periodElapsed_ << " months\n";
    if(openingFee_ != 0.0) ss << "Opening Fee: " << openingFee_ << "\n";
    if(openingPercent_ != 0.0) ss << "Opening Fee %: " << openingPercent_ << "% = " << openingPercent_/100*(amount_ - initialPayment_) << "\n";

    return ss.str();
}
