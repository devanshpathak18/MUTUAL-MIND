#pragma once

// ──────────────────────────────────────────
// Investor.h — Derived class (inherits Person)
// ──────────────────────────────────────────

#include "Person.h"

class Investor : public Person {
private:
    double amount;

public:
    Investor(const std::string& n, int a, double amt)
        : Person(n, a), amount(amt) {}

    double getAmount() const { return amount; }

    ~Investor() override = default;
};
