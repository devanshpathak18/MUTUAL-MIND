# MutualMind — Fund Advisor

An OOP-based C++ console application that helps young investors understand mutual funds, assess their risk profile, and get personalised fund recommendations with SIP projections.

## Features

| Tab | Description |
|-----|-------------|
| **Fund Advisor** | 3-question risk quiz → Conservative / Moderate / Aggressive profile → fund suggestions + allocation breakdown + 5-year SIP growth table |
| **Learning Hub** | Browse key investment terms (Rolling Returns, Sharpe Ratio, CAGR, NAV, etc.) |
| **SIP Predictor** | Enter monthly SIP, expected return, and duration → detailed month-by-month growth view |

## OOP & Modern C++ Concepts

- **Inheritance** — `Investor` derives from `Person`
- **Encapsulation** — private data + public const getters across classes
- **Polymorphism** — virtual default destructor in base `Person`
- **Templates** — generic `readValidated<T>()` input validation helper
- **Data-Driven Architecture** — static tables for `RiskProfile` and `GlossaryTerm`
- **Separation of Concerns** — domain logic / pure math separated from console I/O
- **Enum class & Namespaces** — `RiskCategory` and `Config` namespace (`constexpr` constants)
- **File I/O** — `UserAuth` persistence in `data/users.txt`

## Project Structure

```
MutualMind/
├── include/
│   ├── Config.h                  // constexpr constants, namespace Config
│   ├── FinanceMath.h             // getMonthName, calculateFutureValue, formatRupees
│   ├── InputUtils.h              // clearInput(), generic readValidated<T>() template
│   ├── Person.h                  // base class with virtual destructor
│   ├── Investor.h                // derived class
│   ├── MutualFund.h              // plain struct
│   ├── RiskProfile.h             // struct & static lookup table (data-driven)
│   ├── UserAuth.h
│   ├── RiskAssessor.h
│   ├── InvestmentLearningHub.h
│   └── SIPPredictor.h            // stateful SIP projection engine + SIPGrowthRow
├── src/
│   ├── FinanceMath.cpp
│   ├── UserAuth.cpp
│   ├── RiskAssessor.cpp
│   ├── InvestmentLearningHub.cpp
│   ├── SIPPredictor.cpp
│   └── main.cpp
├── data/
│   └── users.txt
├── CMakeLists.txt
├── CMakePresets.json
└── README.md
```

## Build & Run

### 1. Using CMake Presets (Recommended in VS Code / Modern CMake)
```bash
cd MutualMind

# Configure with preset (e.g. default-debug or default-release)
cmake --preset default-debug

# Build
cmake --build --preset default-debug

# Run
./build/default-debug/MutualMind.exe
```

### 2. Standard CMake Build
```bash
cd MutualMind
mkdir build && cd build
cmake ..
cmake --build .
.\MutualMind.exe
```

### 3. Direct G++ Compilation
```bash
cd MutualMind
g++ -std=c++17 -I include src/*.cpp -o MutualMind.exe
.\MutualMind.exe
```

## Conventions

- **Header guards**: `#pragma once` on every header
- **Headers (.h)**: class declarations + `const`-marked short getters (inline)
- **Template functions**: defined in header (`InputUtils.h`)
- **No `using namespace std;`** in headers — explicit `std::` prefixes
- **Config namespace**: replaces `#define` macros with `constexpr`

---

> **Disclaimer**: For educational purposes only. Not real financial advice.
