# MutualMind — Architectural Changes & Evolution Log

> This document tracks every codebase modification, architectural decision, and feature enhancement implemented across each level of the learning progression.

---

## 📑 Changelog Index

- [Level 1: Modern C++ Idioms, Memory Safety & RAII](#-level-1-modern-c-idioms-memory-safety--raii) — *Completed*
- [Level 2: Testing Rigor, ASan & CI/CD Pipeline](#-level-2-testing-rigor-asan--cicd-pipeline) — *Upcoming*
- [Level 3: GoF Design Patterns & Decoupled Architecture](#-level-3-gof-design-patterns--decoupled-architecture) — *Pending*
- [Level 4: Quantitative Math & Monte Carlo Simulation](#-level-4-quantitative-math--monte-carlo-simulation) — *Pending*
- [Level 5: Cryptography & Relational Persistence (SQLite3)](#-level-5-cryptography--relational-persistence-sqlite3) — *Pending*
- [Level 6: Networking, REST APIs & Offline Caching](#-level-6-networking-rest-apis--offline-caching) — *Pending*
- [Level 7: Serialization & Reporting Subsystem](#-level-7-serialization--reporting-subsystem) — *Pending*
- [Level 8: Interactive Desktop GUI (Dear ImGui)](#-level-8-interactive-desktop-gui-dear-imgui) — *Pending*

---

## 🟢 Level 1: Modern C++ Idioms, Memory Safety & RAII

* **Status:** `Completed`
* **Focus:** Eliminating raw pointer risks, enforcing automatic resource cleanup (RAII), preventing string copies, and introducing type-safe return types.

### 1. Summary of Changes

| Target File | Change Introduced | Problem Solved | Modern C++ Feature Used |
| :--- | :--- | :--- | :--- |
| [`include/User.h`](file:///c:/Users/A/OneDrive/Desktop/MUTUAL%20MIND/include/User.h) | **Created** dedicated `User` domain model. | User info was split across disparate variables; constructors copied strings unnecessarily. | Domain Model, Move Semantics (`std::move`) |
| [`include/Compat.h`](file:///c:/Users/A/OneDrive/Desktop/MUTUAL%20MIND/include/Compat.h) | **Created** cross-compiler portability header. | Compatibility differences between GCC 6.3 and modern C++17/20 compilers for `<optional>` and `<string_view>`. | Feature test macros (`__has_include`), type aliasing |
| [`include/UserAuth.h`](file:///c:/Users/A/OneDrive/Desktop/MUTUAL%20MIND/include/UserAuth.h)<br>[`src/UserAuth.cpp`](file:///c:/Users/A/OneDrive/Desktop/MUTUAL%20MIND/src/UserAuth.cpp) | • `loginUser()` returns `std_compat::optional<User>`<br>• `userExists()` takes `std_compat::string_view` | • Boolean return required awkward 2-step queries to retrieve user data.<br>• Every record check invoked `.substr()`, causing heap allocations. | `std::optional<T>`, `std::string_view` |
| [`src/main.cpp`](file:///c:/Users/A/OneDrive/Desktop/MUTUAL%20MIND/src/main.cpp) | • Replaced `bool loggedIn` loop with `optional<User>` check.<br>• Investor session managed via `std::unique_ptr<Investor>`. | Stack variable lifetime was rigid; lacked dynamic lifecycle management for user sessions. | `std::unique_ptr<T>`, `std::make_unique`, RAII |

---

### 2. Deep-Dive: What Changed & Why

#### A. Created Domain Model (`User.h`) with Move Semantics
* **Old Behavior:** User credentials and active session info were tracked as loose strings inside `UserAuth`.
* **New Behavior:** A clean `User` struct models the authenticated identity.
* **Why:** Enables passing an encapsulated entity. `std::move(n)` transfers string buffer ownership directly into the struct, avoiding redundant heap copies.

#### B. Safe Returns with `std::optional<User>`
* **Old Behavior:**
  ```cpp
  bool loggedIn = auth.loginUser(); // Step 1
  string name = auth.getLoggedInName(); // Step 2 (risk of calling before login)
  ```
* **New Behavior:**
  ```cpp
  std_compat::optional<User> currentUser = auth.loginUser();
  if (currentUser) {
      cout << "Welcome " << currentUser->name;
  }
  ```
* **Why:** Replaces magic return values and separate state queries with a single, type-safe optional container.

#### C. Zero-Copy String Inspection (`std::string_view`)
* **Old Behavior:**
  ```cpp
  string storedEmail = line.substr(pos1 + 1, pos2 - pos1 - 1); // Copies chars onto heap
  ```
* **New Behavior:**
  ```cpp
  std_compat::string_view lineView(line);
  std_compat::string_view storedEmail = lineView.substr(pos1 + 1, pos2 - pos1 - 1); // Zero copy
  ```
* **Why:** `string_view` points directly into the existing buffer without allocating new heap memory on every line of `users.txt`.

#### D. Dynamic Ownership with Smart Pointers (`std::unique_ptr`)
* **Old Behavior:**
  ```cpp
  Investor investor(name, age, amount); // Fixed stack allocation
  ```
* **New Behavior:**
  ```cpp
  auto investor = std::make_unique<Investor>(currentUser->name, age, amount);
  // Accessed cleanly via: investor->getName(), investor->getAmount()
  ```
* **Why:** Introduces RAII and sole-ownership semantics. When the session ends, memory reclamation is completely automated with zero risk of leaks.

---

### 3. Verification & Build Confirmation
* **Build Command:** `cmake --build build/windows-mingw-debug`
* **Status:** Passed with **0 errors, 0 warnings**.
* **Smoke Test:** Interactive login, risk quiz, and SIP calculations verified functional.

---

## 🟡 Level 2: Testing Rigor, ASan & CI/CD Pipeline
* **Status:** `Ready to Start`
* **Planned Changes:**
  - Integrate **Catch2 v3** test framework using CMake `FetchContent`.
  - Add unit test targets for `FinanceMath` formulas and `RiskAssessor` boundary conditions.
  - Enable **AddressSanitizer (ASan)** flags in Debug builds.
  - Construct `.github/workflows/ci.yml` for automated multi-platform builds.
