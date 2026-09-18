// ──────────────────────────────────────────
// main.cpp — Application entry point
//   All I/O (cout / cin) lives here.
//   Logic classes return data; main prints it.
// ──────────────────────────────────────────

#include "Config.h"
#include "Compat.h"
#include "User.h"
#include "UserAuth.h"
#include "Investor.h"
#include "RiskAssessor.h"
#include "RiskProfile.h"
#include "InvestmentLearningHub.h"
#include "SIPPredictor.h"
#include "FinanceMath.h"
#include "InputUtils.h"

#include <iostream>
#include <iomanip>
#include <string>
#include <memory>

using std::cout;
using std::endl;
using std::left;
using std::setw;
using std::fixed;
using std::setprecision;
using std::string;

// ── Display helpers (free functions in main.cpp) ──

static void displayProfile(const RiskProfile& profile, double amount) {
    cout << "\n============================================\n";
    cout << "       RECOMMENDED FUNDS FOR YOU            \n";
    cout << "============================================\n";

    cout << "Your Risk Profile : " << profile.categoryName << "\n\n";
    cout << "Suggested Funds:\n";

    for (int i = 0; i < Config::FUND_COUNT; i++) {
        cout << "  -> " << profile.funds[i].fundName
             << " (" << profile.funds[i].fundType << ")" << endl;
    }

    cout << fixed << setprecision(2);
    cout << "\n--------------------------------------------\n";
    cout << "        RECOMMENDED ALLOCATION              \n";
    cout << "--------------------------------------------\n";
    cout << "  Equity Funds  -> " << (int)(profile.equityPct * 100) << "%"
         << "  (Rs. " << amount * profile.equityPct << " / month)\n";
    cout << "  Debt Funds    -> " << (int)(profile.debtPct * 100) << "%"
         << "  (Rs. " << amount * profile.debtPct   << " / month)\n";
    cout << "  Gold / Liquid -> " << (int)(profile.goldPct * 100) << "%"
         << "  (Rs. " << amount * profile.goldPct   << " / month)\n";
    cout << "--------------------------------------------\n";
}

// ── Main ──

int main() {

    cout << "============================================\n";
    cout << "       " << Config::APP_NAME << "\n";
    cout << "         For Young Investors                \n";
    cout << "============================================\n";

    // ── Register / Login Menu ──
    UserAuth auth;
    std_compat::optional<User> currentUser;

    while (!currentUser) {
        cout << "\n  1. Register (New User)\n";
        cout << "  2. Login    (Existing User)\n";
        cout << "  3. Exit\n";

        //read validated template used
        int choice = readValidated<int>("  Choose (1/2/3): ", 1, 3);

        if (choice == 1) {
            auth.registerUser();
        } else if (choice == 2) {
            currentUser = auth.loginUser();
        } else if (choice == 3) {
            cout << "\nGoodbye!\n";
            return 0;
        }
    }

    // ── After successful login, continue to the app ──
    cout << "\n============================================\n";
    cout << "  Welcome, " << currentUser->name << "! Let's set up your profile.\n";
    cout << "============================================\n";

    //read validated template used
    int age = readValidated<int>("Enter your age : ", Config::MIN_AGE, Config::MAX_AGE);

    //read validated template used
    double amount = readValidated<double>("Enter monthly investment amount (Rs.): ", Config::MIN_AMOUNT, Config::MAX_AMOUNT);

    // Modern C++: Manage active investor profile dynamically via smart pointer
    auto investor = std::make_unique<Investor>(currentUser->name, age, amount);
    InvestmentLearningHub learningHub;
    SIPPredictor          sipPredictor;

    while (true) {
        cout << "\n============================================\n";
        cout << "                 MAIN TABS                  \n";
        cout << "============================================\n";
        cout << "  1. Fund Advisor (Risk Quiz + Suggestion)\n";
        cout << "  2. Learning Purpose (Investment Terms)\n";
        cout << "  3. SIP Predictor\n";
        cout << "  4. Exit\n";

        //read validated template used
        int tabChoice = readValidated<int>("Choose tab (1/2/3/4): ", 1, 4);

        if (tabChoice == 1) {
            RiskAssessor assessor;
            assessor.runQuiz();
            RiskCategory category = assessor.getCategory();

            cout << fixed << setprecision(2);
            cout << "\nHello, " << investor->getName() << "!\n";
            cout << "Age            : " << investor->getAge() << "\n";
            cout << "Monthly Amount : Rs. " << investor->getAmount() << "\n";

            // Direct data lookup from the static table — no middleman class
            const RiskProfile& profile = RiskProfile::getProfile(category);

            // Display fund recommendations
            displayProfile(profile, investor->getAmount());

            // Reuse the SIPPredictor engine for the 5-year growth table
            SIPPredictor advisor(investor->getAmount(), profile.annualRate, 5);
            advisor.displaySummary();
            advisor.displaySchedule();

        } else if (tabChoice == 2) {
            learningHub.openLearningTab();
        } else if (tabChoice == 3) {
            sipPredictor.openPredictorTab();
        } else if (tabChoice == 4) {
            break;
        }
    }

    cout << "\n* Disclaimer: For educational purposes only.\n";
    cout << "  Not real financial advice. Do your own research.\n\n";

    return 0;
}
