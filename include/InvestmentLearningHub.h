#pragma once

// ──────────────────────────────────────────
// InvestmentLearningHub.h — Learning tab for terms
// ──────────────────────────────────────────

#include <string>
#include <vector>

struct GlossaryTerm {
    std::string title;
    std::string meaning;
    std::string quickUse;
};

class InvestmentLearningHub {
private:
    void showTerm(const GlossaryTerm& term);

public:
    static const std::vector<GlossaryTerm>& getAllTerms();

    void openLearningTab();

    ~InvestmentLearningHub() = default;
};
