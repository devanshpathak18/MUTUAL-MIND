// ──────────────────────────────────────────
// FinanceMath.cpp — pure helper function implementations
// ──────────────────────────────────────────

#include "FinanceMath.h"
#include <cmath>
#include <string>

using std::string;
using std::to_string;

// Returns abbreviated month name for 1‑based month number (1 = Jan … 12 = Dec)
string getMonthName(int month) {
    string months[] = {"Jan","Feb","Mar","Apr","May","Jun",
                       "Jul","Aug","Sep","Oct","Nov","Dec"};
    return months[month - 1];
}

// SIP Future‑Value formula:
//   FV = P × [((1+r)^n − 1) / r] × (1+r)
// where r = annualRate / 12 / 100, n = number of months

double calculateFutureValue(double monthlyInvestment, double annualRate, int months) {
    double r = annualRate / 12.0 / 100.0; 
    if (r == 0.0) return monthlyInvestment * months;
    return monthlyInvestment * ((pow(1 + r, months) - 1) / r) * (1 + r);
}

// Format a double into Indian‑style comma grouping (e.g. 12,34,567)
string formatIndianNumber(double value) {
    long long rounded = static_cast<long long>(value + 0.5);
    string digits = to_string(rounded);

    if (digits.length() <= 3) return digits;

    string lastThree  = digits.substr(digits.length() - 3);
    string rest       = digits.substr(0, digits.length() - 3);
    string grouped    = "";

    while (rest.length() > 2) {
        grouped = "," + rest.substr(rest.length() - 2) + grouped;
        rest    = rest.substr(0, rest.length() - 2);
    }

    grouped = rest + grouped;
    return grouped + "," + lastThree;
}

// Convenience wrapper: "Rs. X,XX,XXX"
string formatRupees(double value) {
    return "Rs. " + formatIndianNumber(value);
}
