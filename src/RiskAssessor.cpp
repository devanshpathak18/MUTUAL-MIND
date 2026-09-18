// ──────────────────────────────────────────
// RiskAssessor.cpp — Risk‑assessment quiz implementation
// ──────────────────────────────────────────

#include "RiskAssessor.h"
#include "InputUtils.h"

#include <iostream>

using std::cout;

void RiskAssessor::runQuiz() {
    score = 0;  // Reset for safety if runQuiz() is called again on the same instance

    cout << "\n============================================\n";
    cout << "         RISK ASSESSMENT QUIZ               \n";
    cout << "============================================\n";

    cout << "\nQ1. If your investment drops 20%, you:\n";
    cout << "  1. Panic and sell\n";
    cout << "  2. Wait and watch\n";
    cout << "  3. Invest more\n";
    //read validated template used
    int ans1 = readValidated<int>("Your choice (1/2/3): ", 1, 3);
    score += ans1;

    cout << "\nQ2. When do you need this money back?\n";
    cout << "  1. Within a year\n";
    cout << "  2. In 2-4 years\n";
    cout << "  3. No rush, long term\n";
    //read validated template used
    int ans2 = readValidated<int>("Your choice (1/2/3): ", 1, 3);
    score += ans2;

    cout << "\nQ3. Your investment goal is:\n";
    cout << "  1. Keep money safe\n";
    cout << "  2. Steady growth\n";
    cout << "  3. Maximum returns, risk doesn't scare me\n";
    //read validated template used
    int ans3 = readValidated<int>("Your choice (1/2/3): ", 1, 3);
    score += ans3;
}

RiskCategory RiskAssessor::getCategory() const {
    if (score <= Config::CONSERVATIVE_MAX_SCORE)  return RiskCategory::Conservative;
    else if (score <= Config::MODERATE_MAX_SCORE)  return RiskCategory::Moderate;
    else                                           return RiskCategory::Aggressive;
}
