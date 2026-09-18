#pragma once

// ──────────────────────────────────────────
// FinanceMath.h — pure helper functions
//   getMonthName, calculateFutureValue,
//   formatIndianNumber, formatRupees
// ──────────────────────────────────────────

#include <string>

// Returns abbreviated month name for 1‑based month number
std::string getMonthName(int month);

// SIP Future‑Value: FV = P × [((1+r)^n − 1) / r] × (1+r)
double calculateFutureValue(double monthlyInvestment, double annualRate, int months);

// Format a double into Indian‑style "Rs. X,XX,XXX"
std::string formatIndianNumber(double value);
std::string formatRupees(double value);
