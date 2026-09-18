#pragma once

// ──────────────────────────────────────────
// SIPPredictor.h — Stateful SIP projection engine
//   Separates domain calculations from console I/O.
// ──────────────────────────────────────────

#include "Config.h"
#include <string>
#include <vector>

// One row of the month-by-month growth schedule
struct SIPGrowthRow {
    std::string period;         // e.g. "Apr 2026"
    double      invested;       // cumulative amount put in
    double      estimatedValue; // compounded future value at this month
    double      gain;           // estimatedValue − invested
};

class SIPPredictor {
private:
    double monthlyInvestment;
    double annualRate;
    int    years;

public:
    // Default constructor — for interactive use (openPredictorTab fills state)
    SIPPredictor();

    // Parameterized constructor — for programmatic / reuse (e.g. displayReturns)
    SIPPredictor(double monthly, double rate, int yrs);

    // ── Pure domain calculations (no I/O) ────────────
    int    getTotalMonths()    const;
    double getTotalInvested()  const;
    double getEstimatedValue() const;
    double getWealthGained()   const;

    // Generate a structured month-by-month schedule
    std::vector<SIPGrowthRow> generateSchedule() const;
    std::vector<SIPGrowthRow> generateSchedule(int maxRows) const;

    // ── Presentation / CLI helpers ───────────────────
    void displaySummary()  const;
    void displaySchedule() const;

    // Interactive tab — prompts user for input, then displays results
    void openPredictorTab();

    ~SIPPredictor() = default;
};
