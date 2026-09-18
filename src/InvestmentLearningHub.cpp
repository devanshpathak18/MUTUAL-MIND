// ──────────────────────────────────────────
// InvestmentLearningHub.cpp — Learning tab implementation
// ──────────────────────────────────────────

#include "InvestmentLearningHub.h"
#include "InputUtils.h"

#include <iostream>
#include <vector>

using std::cout;
using std::string;
using std::vector;

const vector<GlossaryTerm>& InvestmentLearningHub::getAllTerms() {
    static const vector<GlossaryTerm> terms = {
        {
            "Rolling Returns",
            "Returns calculated for many overlapping periods (for example every 1-year window).",
            "Helps check consistency of performance instead of only one start-end date."
        },
        {
            "Sharpe Ratio",
            "Measures return earned per unit of risk taken.",
            "Higher Sharpe generally means better risk-adjusted performance."
        },
        {
            "CAGR (Compounded Annual Growth Rate)",
            "The annualized growth rate over multiple years.",
            "Used to compare long-term fund growth in a simple yearly format."
        },
        {
            "Expense Ratio",
            "The annual fee charged by a fund to manage your money.",
            "Lower expense ratio can improve net returns over long periods."
        },
        {
            "NAV (Net Asset Value)",
            "Per-unit value of a mutual fund, calculated daily.",
            "You buy or redeem units based on NAV."
        },
        {
            "Exit Load",
            "A small penalty if you redeem your investment before a specified time.",
            "Discourages very short-term exits from certain funds."
        },
        {
            "Diversification",
            "Spreading investments across assets/sectors to reduce concentration risk.",
            "Protects portfolio when one asset class performs poorly."
        }
    };
    return terms;
}

void InvestmentLearningHub::showTerm(const GlossaryTerm& term) {
    cout << "\n--------------------------------------------\n";
    cout << term.title << "\n";
    cout << "Meaning : " << term.meaning << "\n";
    cout << "Use     : " << term.quickUse << "\n";
    cout << "--------------------------------------------\n";
}

void InvestmentLearningHub::openLearningTab() {
    const auto& terms = getAllTerms();
    const int exitChoice = static_cast<int>(terms.size()) + 1;

    while (true) {
        cout << "\n============================================\n";
        cout << "        LEARNING TAB (INVESTMENT TERMS)     \n";
        cout << "============================================\n";

        for (size_t i = 0; i < terms.size(); ++i) {
            cout << "  " << (i + 1) << ". " << terms[i].title << "\n";
        }
        cout << "  " << exitChoice << ". Back to Main Menu\n";

        //read validated template used
        int choice = readValidated<int>("Choose (1-" + std::to_string(exitChoice) + "): ", 1, exitChoice);

        if (choice >= 1 && choice <= static_cast<int>(terms.size())) {
            showTerm(terms[choice - 1]);
        } else if (choice == exitChoice) {
            break;
        }
    }
}
