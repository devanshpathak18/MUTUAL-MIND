#pragma once

// ──────────────────────────────────────────
// MutualFund.h — plain struct (no cout inside)
// ──────────────────────────────────────────

#include <string>

struct MutualFund {
    std::string fundName;
    std::string fundType;

    MutualFund() : fundName(""), fundType("") {}
    MutualFund(const std::string& name, const std::string& type)
        : fundName(name), fundType(type) {}
};
