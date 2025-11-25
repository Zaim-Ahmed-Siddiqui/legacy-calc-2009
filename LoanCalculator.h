#ifndef LOANCALCULATOR_H_INCLUDED
#define LOANCALCULATOR_H_INCLUDED

#include <string>

class LoanCalculator
{
public:
  LoanCalculator();
  ~LoanCalculator() {}

  //
  // Setters and Getters
  //

  // Total loan amount A
  void setAmount(long double A);
  long double getAmount() const { return amount_; }

  // Initial down payment
  void setInitialPayment(long double initialA);
  long double getInitialPayment() const { return initialPayment_; }

  // Yearly interest rate i
  void setInterest(long double i);
  long double getInterest() const { return interest_; }
  long double getPeriodicInterest() const { return interestPeriodic_; }

  void setPayment(long double P);
  long double getPayment() const { return payment_; }

  void setPeriodTotal(long double N);
  long double getPeriodTotal() const { return periodTotal_; }

  void setPeriodElapsed(long double n);
  long double getPeriodElapsed() const { return periodElapsed_; }

  void setOpeningFee(long double fee);
  long double getOpeningFee() const { return openingFee_; }

  void setOpeningPercent(long double percent);
  long double getOpeningPercent() const { return openingPercent_; }

  inline void reset() {
    amount_ = initialPayment_ = interest_ = interestPeriodic_ = payment_ = openingFee_ = openingPercent_ = 0.0L;
    periodTotal_ = periodElapsed_ = 0.0L;
    amountSet_ = interestSet_ = paymentSet_ = periodTotalSet_ = periodElapsedSet_ = false;
  }

  //
  // The actual calculation methods
  //
  long double calculateLoanBalance();
  long double calculatePayment();
  long double calculateNumberPayments();
  long double calculateLoanAmount();
  long double calculateInterestRate();
  long double calculateEffectiveInterestRate();

  std::string toString();

private:
  long double amount_;        // loan amount
  bool amountSet_;

  long double initialPayment_;     // initial down payment

  long double interest_;          // interest rate, something like 6.75
  long double interestPeriodic_;  // monthly interest rate
  bool interestSet_;

  long double payment_;       // payment amount
  bool paymentSet_;

  long double periodTotal_;     // total payment periods
  bool periodTotalSet_;

  long double periodElapsed_;   // number of elapsed payment periods
  bool periodElapsedSet_;

  // Fees
  long double openingFee_;
  long double openingPercent_;
};

#endif // LOANCALCULATOR_H_INCLUDED
