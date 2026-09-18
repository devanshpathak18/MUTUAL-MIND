#pragma once

// ──────────────────────────────────────────
// RiskProfile.h — struct bundling profile data
//   name, funds[], equityPct, debtPct, goldPct, rate
//
//   Also provides a static lookup table so
//   adding a new category = adding one row.
// ──────────────────────────────────────────

#include "Config.h"
#include "MutualFund.h"
#include <array>
#include <string>

struct RiskProfile {
    std::string categoryName;
    std::array<MutualFund, Config::FUND_COUNT> funds;
    double      equityPct;
    double      debtPct;
    double      goldPct;
    double      annualRate;

    // ── Data‑driven lookup ──────────────────
    // Returns the profile for a given RiskCategory.
    // To add a new category: add an enum value and one row here.
    static const RiskProfile& getProfile(RiskCategory category) {
        static const RiskProfile profiles[] = {

            // ── Conservative ──
            {   "Conservative",
                {{  MutualFund("HDFC Short Term Debt Fund",     "Debt Fund"),
                    MutualFund("SBI Liquid Fund",               "Liquid Fund"),
                    MutualFund("ICICI Prudential Savings Fund", "Debt Fund")  }},
                0.20, 0.60, 0.20, 8.0
            },

            // ── Moderate ──
            {   "Moderate",
                {{  MutualFund("HDFC Balanced Advantage Fund",   "Hybrid Fund"),
                    MutualFund("Mirae Asset Hybrid Equity Fund", "Hybrid Fund"),
                    MutualFund("SBI Equity Hybrid Fund",         "Hybrid Fund") }},
                0.50, 0.40, 0.10, 12.0
            },

            // ── Aggressive ──
            {   "Aggressive",
                {{  MutualFund("Parag Parikh Flexi Cap Fund", "Flexi Cap Fund"),
                    MutualFund("Nippon India Large Cap Fund",  "Large Cap Fund"),
                    MutualFund("Bandhan Small Cap Fund",       "Small Cap Fund") }},
                0.70, 0.20, 0.10, 16.0
            }
        };

        return profiles[static_cast<int>(category)];
    }
};
