#pragma once

// ──────────────────────────────────────────
// UserAuth.h — Register & Login with Modern C++
// ──────────────────────────────────────────

#include "Compat.h"
#include "User.h"
#include <string>

class UserAuth {
private:
    std::string loggedInName;
    std::string loggedInEmail;

    bool userExists(std_compat::string_view email);

public:
    UserAuth() : loggedInName(""), loggedInEmail("") {}

    // Short const getters — inline, return by const reference
    const std::string& getLoggedInName()  const { return loggedInName; }
    const std::string& getLoggedInEmail() const { return loggedInEmail; }

    // Real logic — defined in UserAuth.cpp
    bool registerUser();
    
    // Returns std_compat::optional<User>:
    // Contains User on successful authentication, or empty if invalid
    std_compat::optional<User> loginUser();

    ~UserAuth() = default;
};
