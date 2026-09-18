#pragma once

// ──────────────────────────────────────────
// RiskAssessor.h — Risk‑assessment quiz
// ──────────────────────────────────────────

#include "Config.h"   // RiskCategory

class RiskAssessor {
private:
    int score;

public:
    RiskAssessor() : score(0) {}

    // Real logic — defined in RiskAssessor.cpp
    void         runQuiz();
    RiskCategory getCategory() const;

    ~RiskAssessor() {}
};
