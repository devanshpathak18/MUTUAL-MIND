// ──────────────────────────────────────────
// SIPPredictor.cpp — Stateful SIP projection engine implementation
// ──────────────────────────────────────────

#include "SIPPredictor.h"
#include "FinanceMath.h"
#include "InputUtils.h"

#include <iostream>
#include <iomanip>
#include <string>

using std::cout;
using std::left;
using std::setw;
using std::fixed;
using std::setprecision;
using std::string;
using std::to_string;
using std::vector;

// ── Constructors ─────────────────────────────

SIPPredictor::SIPPredictor()
    : monthlyInvestment(0.0), annualRate(0.0), years(0) {}

SIPPredictor::SIPPredictor(double monthly, double rate, int yrs)
    : monthlyInvestment(monthly), annualRate(rate), years(yrs) {}

// ── Pure domain calculations (no I/O) ────────

int SIPPredictor::getTotalMonths() const {
    return years * 12;
}

double SIPPredictor::getTotalInvested() const {
    return monthlyInvestment * getTotalMonths();
}

double SIPPredictor::getEstimatedValue() const {
    return calculateFutureValue(monthlyInvestment, annualRate, getTotalMonths());
}

double SIPPredictor::getWealthGained() const {
    return getEstimatedValue() - getTotalInvested();
}

vector<SIPGrowthRow> SIPPredictor::generateSchedule() const {
    return generateSchedule(Config::MAX_SCHEDULE_ROWS);
}

vector<SIPGrowthRow> SIPPredictor::generateSchedule(int maxRows) const {
    vector<SIPGrowthRow> schedule;
    int totalMonths = getTotalMonths();
    int rowsToShow  = (totalMonths <= maxRows) ? totalMonths : maxRows;

    schedule.reserve(rowsToShow);

    for (int n = 1; n <= rowsToShow; n++) {
        double invested     = monthlyInvestment * n;
        double valueAtMonth = calculateFutureValue(monthlyInvestment, annualRate, n);
        double gain         = valueAtMonth - invested;

        int totalMonth = Config::START_MONTH + n - 1;
        int year       = Config::START_YEAR + (totalMonth - 1) / 12;
        int month      = ((totalMonth - 1) % 12) + 1;
        string period  = getMonthName(month) + " " + to_string(year);

        schedule.push_back({period, invested, valueAtMonth, gain});
    }

    return schedule;
}

// ── Presentation / CLI helpers ───────────────

void SIPPredictor::displaySummary() const {
    cout << fixed << setprecision(2);
    cout << "\n============================================\n";
    cout << "               SIP SUMMARY                  \n";
    cout << "============================================\n";
    cout << left << setw(24) << "Monthly SIP"            << ": " << formatRupees(monthlyInvestment) << "\n";
    cout << left << setw(24) << "Expected Return (p.a.)" << ": " << annualRate << "%\n";
    cout << left << setw(24) << "Investment Duration"    << ": " << years << " years\n";
    cout << "--------------------------------------------\n";
    cout << left << setw(24) << "Invested Amount"        << ": " << formatRupees(getTotalInvested()) << "\n";
    cout << left << setw(24) << "Estimated Returns"      << ": " << formatRupees(getWealthGained()) << "\n";
    cout << left << setw(24) << "Total Value"            << ": " << formatRupees(getEstimatedValue()) << "\n";
    cout << "--------------------------------------------\n";
}

void SIPPredictor::displaySchedule() const {
    vector<SIPGrowthRow> schedule = generateSchedule();
    int totalMonths = getTotalMonths();

    cout << "\n============================================\n";
    cout << "      MONTH-BY-MONTH SIP GROWTH VIEW        \n";
    cout << "============================================\n";
    cout << left
         << setw(14) << "Period"
         << setw(20) << "Invested"
         << setw(20) << "Est. Value"
         << setw(20) << "Est. Gain" << "\n";
    cout << "------------------------------------------------------------\n";

    for (const auto& row : schedule) {
        cout << left
             << setw(14) << row.period
             << setw(20) << formatRupees(row.invested)
             << setw(20) << formatRupees(row.estimatedValue)
             << setw(20) << formatRupees(row.gain)
             << "\n";
    }

    if (totalMonths > static_cast<int>(schedule.size())) {
        cout << "...\n";
        cout << "(Showing first " << schedule.size()
             << " months only for readability. Final value is included in summary.)\n";
    }

    cout << "------------------------------------------------------------\n";
    cout << "* Estimated values, not guaranteed market returns.\n";
}

// ── Interactive tab ──────────────────────────

void SIPPredictor::openPredictorTab() {
    cout << "\n============================================\n";
    cout << "              SIP PREDICTOR TAB             \n";
    cout << "============================================\n";

    //read validated template used
    monthlyInvestment = readValidated<double>("Monthly investment (Rs.) : ", Config::MIN_AMOUNT, Config::MAX_AMOUNT);

    //read validated template used
    annualRate = readValidated<double>("Expected annual return (%) : ", 0.0, 40.0);

    //read validated template used
    years = readValidated<int>("Time period (years) : ", 1, 40);

    displaySummary();
    displaySchedule();
}
