#pragma once

// ──────────────────────────────────────────
// User.h — Authenticated User Domain Model
//   Leverages move semantics (std::move) for efficient construction.
// ──────────────────────────────────────────

#include <string>
#include <utility>

struct User {
    std::string name;
    std::string email;

    User() = default;
    User(std::string n, std::string e)
        : name(std::move(n)), email(std::move(e)) {}
};
