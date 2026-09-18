#pragma once

// ──────────────────────────────────────────
// InputUtils.h — Generic validated input template & I/O cleanup
// ──────────────────────────────────────────

#include <iostream>
#include <limits>
#include <string>

// Clear cin error state and discard leftover input from the stream buffer
inline void clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// Generic validated-input template function
template<typename T>
T readValidated(const std::string& prompt, T minVal, T maxVal) {
    T val;
    while (true) {
        std::cout << prompt;
        if (std::cin >> val && val >= minVal && val <= maxVal) {
            return val;
        }
        std::cout << "  Invalid input. Please enter a valid value.\n";
        clearInput();
    }
}
