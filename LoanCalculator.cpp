#include <cmath>
#include <stdexcept>
#include <sstream>
#include <string>
#include <iomanip>

#include "LoanCalculator.h"

using namespace std;

LoanCalculator::LoanCalculator() :
  amountSet_(false),
  initialPayment_(0.0L),
  interestSet_(false),
  paymentSet_(false),
  periodTotalSet_(false),
  periodElapsedSet_(false),
  openingFee_(0.0L),
  openingPercent_(0.0L),
  interestPeriodic_(0.0L)
{
}

// Setters
void LoanCalculator::setInterest(long double interest)
{
    if(interest < 0.0L) throw invalid_argument("Interest cannot be negative");
    interest_ = interest;
    interestSet_ = true;
    interestPeriodic_ = interest_ / 12.0L / 100.0L;
}

void LoanCalculator::setAmount(long double amount)
{
    if(amount <= 0.0L) throw invalid_argument("Amount must be positive");
    amount_ = amount;
    amountSet_ = true;
}

void LoanCalculator::setPayment(long double payment)
{
    if(payment <= 0.0L) throw invalid_argument("Payment must be positive");
    payment_ = payment;
    paymentSet_ = true;
}

void LoanCalculator::setPeriodTotal(long double months)
{
    if(months <= 0.0L) throw invalid_argument("Total period must be positive");
    periodTotal_ = months;
    periodTotalSet_ = true;
}

void LoanCalculator::setPeriodElapsed(long double months)
{
    if(months < 0.0L) throw invalid_argument("Elapsed period cannot be negative");
    periodElapsed_ = months;
    periodElapsedSet_ = true;
}

void LoanCalculator::setInitialPayment(long double initialPayment)
{
    if(initialPayment < 0.0L) throw invalid_argument("Initial payment cannot be negative");
    initialPayment_ = initialPayment;
}

void LoanCalculator::setOpeningFee(long double fee)
{
    if(fee < 0.0L) throw invalid_argument("Opening fee cannot be negative");
    openingFee_ = fee;
}

void LoanCalculator::setOpeningPercent(long double percent)
{
    if(percent < 0.0L) throw invalid_argument("Opening percent cannot be negative");
    openingPercent_ = percent;
}

// Calculate loan balance
long double LoanCalculator::calculateLoanBalance()
{
  if(!amountSet_ || !interestSet_ || !periodElapsedSet_ || !paymentSet_)
    throw invalid_argument("Must set loan amount, interest, and elapsed period for this calculation");

  return (amount_ * pow(1.0L + interestPeriodic_, periodElapsed_)) -
         (payment_ / interestPeriodic_) * (pow(1.0L + interestPeriodic_, periodElapsed_) - 1.0L);
}

// Calculate monthly payment
long double LoanCalculator::calculatePayment()
{
  if(!amountSet_ || !interestSet_ || !periodTotalSet_)
    throw invalid_argument("Must set loan amount, interest, and total period for this calculation");

  long double totalAmount = amount_ - initialPayment_;
  if(totalAmount <= 0.0L) throw invalid_argument("Base loan amount must be positive");

  totalAmount = totalAmount + openingFee_ + (totalAmount * (openingPercent_/100.0L));

  return (interestPeriodic_*totalAmount) /
         (1.0L - pow(1.0L + interestPeriodic_, -periodTotal_));
}

// Calculate number of payments
long double LoanCalculator::calculateNumberPayments()
{
  if(!amountSet_ || !interestSet_ || !paymentSet_)
    throw invalid_argument("Must set loan amount, interest, and payment for this calculation");

  long double ratio = 1.0L - (interestPeriodic_ * amount_ / payment_);
  if(ratio <= 0.0L) throw invalid_argument("Payment too small to cover interest");

  return (-1.0L*log10(ratio)) / log10(1.0L + interestPeriodic_);
}

// Calculate original loan amount
long double LoanCalculator::calculateLoanAmount()
{
  if(!paymentSet_ || !interestSet_ || !periodTotalSet_)
    throw invalid_argument("Must set payment, interest, and total period for this calculation");

  return (payment_/interestPeriodic_) * (1.0L - pow(1.0L + interestPeriodic_, -periodTotal_));
}

// Calculate yearly interest rate (approximate)
long double LoanCalculator::calculateInterestRate()
{
  if(!amountSet_ || !paymentSet_ || !periodTotalSet_)
    throw invalid_argument("Must set amount, payment, and total period for this calculation");

  long double q = log10(1.0L + 1.0L/periodTotal_) / log10(2.0L);
  long double monthlyInterest = pow((pow((1.0L + payment_/amount_), 1.0L/q) - 1.0L), q) - 1.0L;

  return monthlyInterest*12.0L*100.0L;
}

// Calculate effective interest rate
long double LoanCalculator::calculateEffectiveInterestRate()
{
  if(!amountSet_ || !periodTotalSet_)
    throw invalid_argument("Must set amount and total period for this calculation");

  long double payment = calculatePayment();
  long double totalAmount = amount_ - initialPayment_;

  long double q = log10(1.0L + 1.0L/periodTotal_) / log10(2.0L);
  long double monthlyInterest = pow((pow((1.0L + payment/totalAmount), 1.0L/q) - 1.0L), q) - 1.0L;

  return monthlyInterest*12.0L*100.0L;
}

// Format calculator values as string
std::string LoanCalculator::toString()
{
  std::stringstream ss;
  ss << std::fixed << std::setprecision(2);

  if(amountSet_) ss << "Initial Amount:      " << amount_ << "\n";
  if(initialPayment_ != 0.0L)
  {
    ss << "Initial Payment:     " << initialPayment_ << "\n";
    ss << "Actual Loan Amount:  " << (amount_ - initialPayment_) << "\n";
  }
  if(interestSet_) ss << "Yearly Interest:     " << interest_ << "%\n";
  if(paymentSet_) ss << "Monthly payment:     " << payment_ << "\n";
  if(periodTotalSet_) ss << "Loan Period:         " << periodTotal_ << " months\n";
  if(periodElapsedSet_) ss << "Elapsed Period:      " << periodElapsed_ << " months\n";
  if(openingFee_ != 0.0L) ss << "Opening Fee:       " << openingFee_ << "\n";
  if(openingPercent_ != 0.0L)
    ss << "Opening Fee %:       " << openingPercent_ << "% = "
       << openingPercent_/100.0L*(amount_ - initialPayment_) << "\n";

  return ss.str();
}
