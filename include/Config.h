#pragma once

// ──────────────────────────────────────────
// Config.h — constexpr constants, namespace Config
// ──────────────────────────────────────────

namespace Config {

    constexpr const char* APP_NAME   = "MutualMind - Fund Advisor";
    constexpr int         MIN_AGE    = 18;
    constexpr int         MAX_AGE    = 100;
    constexpr int         FUND_COUNT = 3;
    constexpr const char* USER_FILE  = "data/users.txt";
    constexpr double      MIN_AMOUNT = 500.0;
    constexpr double      MAX_AMOUNT = 1000000.0;  // Rs. 10,00,000

    // Risk-quiz score thresholds (3 questions, 1-3 each → range 3-9)
    constexpr int CONSERVATIVE_MAX_SCORE = 5;   // score <= 5 → Conservative
    constexpr int MODERATE_MAX_SCORE     = 7;   // score <= 7 → Moderate
                                                // score >  7 → Aggressive

    // SIP projection timeline defaults
    constexpr int START_MONTH        = 4;       // April
    constexpr int START_YEAR         = 2026;
    constexpr int MAX_SCHEDULE_ROWS  = 120;     // Cap month-by-month display

}  // namespace Config

// Risk‐category enum used across the project
enum class RiskCategory {
    Conservative,
    Moderate,
    Aggressive
};
