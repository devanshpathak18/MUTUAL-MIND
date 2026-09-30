# MutualMind — Change Log

What changed in the codebase, task by task, and why — including the alternatives I considered and the mistakes I made. The plan these tasks come from is in [roadmap.md](roadmap.md).

**Entry format for every task:** files changed · old vs new behaviour · why · alternatives considered · mistakes I made · verification.

---

## Index

- [Level 1: Modern C++ Idioms, Memory Safety & RAII](#level-1-modern-c-idioms-memory-safety--raii) — in progress (first pass done, polish ongoing)
- [Level 2: Testing, Tooling & CI](#level-2-testing-tooling--ci) — CI build workflow exists
- Level 3: Design Patterns & Architecture — not started
- Level 4: Persistence & Password Security — not started
- Level 5: Simulation Engine & Concurrency — not started
- Level 6: Live Data & Networking — not started
- Level 7: REST API Server — not started
- Level 8: Desktop Dashboard (Dear ImGui) — not started

---

## Level 1: Modern C++ Idioms, Memory Safety & RAII

* **Status:** `In progress` — first pass done; polish tasks below
* **Focus:** Eliminating raw pointer risks, enforcing automatic resource cleanup (RAII), preventing string copies, and introducing type-safe return types.

### 1. Summary of Changes

| Target File | Change Introduced | Problem Solved | Modern C++ Feature Used |
| :--- | :--- | :--- | :--- |
| [`include/User.h`](include/User.h) | **Created** dedicated `User` domain model. | User info was split across disparate variables; constructors copied strings unnecessarily. | Domain Model, Move Semantics (`std::move`) |
| [`include/Compat.h`](include/Compat.h) | **Created** cross-compiler portability header. | Compatibility differences between GCC 6.3 and modern C++17/20 compilers for `<optional>` and `<string_view>`. | Feature test macros (`__has_include`), type aliasing |
| [`include/UserAuth.h`](include/UserAuth.h)<br>[`src/UserAuth.cpp`](src/UserAuth.cpp) | • `loginUser()` returns `std_compat::optional<User>`<br>• `userExists()` takes `std_compat::string_view` | • Boolean return required awkward 2-step queries to retrieve user data.<br>• Every record check invoked `.substr()`, causing heap allocations. | `std::optional<T>`, `std::string_view` |
| [`src/main.cpp`](src/main.cpp) | • Replaced `bool loggedIn` loop with `optional<User>` check.<br>• Investor session managed via `std::unique_ptr<Investor>`. | Stack variable lifetime was rigid; lacked dynamic lifecycle management for user sessions. | `std::unique_ptr<T>`, `std::make_unique`, RAII |

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
* **Review note:** this reasoning doesn't hold up — a stack object is also RAII and was never "rigid" here. To be revisited in polish Task 7.

---

### 3. Verification & Build Confirmation
* **Build Command:** `cmake --build build/windows-mingw-debug`
* **Status:** Passed with **0 errors, 0 warnings**.
* **Smoke Test:** Interactive login, risk quiz, and SIP calculations verified functional.
* **Note (found in Level 1 Polish review):** No warning flags were enabled at the time, so "0 warnings" only reflected GCC's defaults. Fixed in Task 1 below.

---

### 4. Level 1 Polish — Review Follow-ups

A review of Level 1 found gaps (Rule of Zero, manual `close()` calls, half-finished `optional` refactor, etc.). They are being fixed one small task at a time.

| # | Task | Status |
| :---: | :--- | :---: |
| 1 | Enable compiler warnings | Done |
| 2 | Upgrade toolchain (MinGW.org GCC 6.3 → MSYS2 GCC), update presets, remove `Compat.h` | To do |
| 3 | Rule of Zero — remove user-declared destructors | To do |
| 4 | Let RAII close file streams | To do |
| 5 | Remove leftover `UserAuth` state; consistent `string_view` + `const`; correct `main.cpp` header comment | To do |
| 6 | Sink-parameter move pattern in `Person` / `Investor` / `MutualFund` | To do |
| 7 | Stack object vs `unique_ptr<Investor>` — decide & correct docs | To do |
| 8 | Fix EOF infinite loop in `readValidated` + `getMonthName` bounds | To do |
| 9 | Stop tracking `data/users.txt` in git; ship an example file | To do |

#### Task 1: Enable Compiler Warnings

| Target File | Change Introduced | Problem Solved | Concept Used |
| :--- | :--- | :--- | :--- |
| [`CMakeLists.txt`](CMakeLists.txt) | Added per-compiler warning flags to the `MutualMind` target. | Suspicious code (unused variables, signed/unsigned mismatches, non-standard extensions) compiled silently. "0 warnings" was meaningless. | `target_compile_options`, `PRIVATE` scope, `if(MSVC)` compiler detection |

* **Old Behavior:** No warning flags → GCC only reported a small default set.
* **New Behavior:**
  ```cmake
  if(MSVC)
      target_compile_options(MutualMind PRIVATE /W4 /permissive-)
  else()
      target_compile_options(MutualMind PRIVATE -Wall -Wextra -Wpedantic)
  endif()
  ```
* **Why:**
  - **Two compilers:** local build uses MinGW GCC; CI on `windows-latest` uses MSVC — they need different flag syntax.
  - **`-Wall -Wextra -Wpedantic`** (GCC/Clang) ≈ **`/W4 /permissive-`** (MSVC): common + extra warnings + strict standard conformance.
  - **`target_compile_options` over `CMAKE_CXX_FLAGS`:** modern CMake attaches settings to one target instead of globally.
  - **`PRIVATE`:** flags apply when building this target only; they don't propagate to anything that links against it.
  - **Placed after `add_executable`:** the target must exist before options can be attached to it.
* **Key Lessons Learned:**
  - **Warning ≠ Error.** A warning still produces the `.exe`; only errors stop the build. `-Werror` (turn warnings into errors) is deferred to Level 2 CI.
  - **Test the safety net:** a temporary `int unused = 5;` triggered `-Wunused-variable`, proving the flags were active.
  - **Linker "Permission denied" on Windows** means `MutualMind.exe` is still running — Windows locks running executables. Close it, then rebuild.
  - **`--clean-first`** forces every `.cpp` to recompile; otherwise only changed files get checked by new flags.
* **Alternatives considered:**
  - *Global `set(CMAKE_CXX_FLAGS ...)`* — rejected: applies to everything in the build, including third-party code added later.
  - *Generator expressions* (`$<$<CXX_COMPILER_ID:MSVC>:/W4>`) — more compact, but harder to read at this stage; `if(MSVC)` is clearer.
  - *`-Werror` right away* — deferred: blocking local experiments is annoying; it belongs in CI (Level 2).
* **Mistakes I made:**
  - Claimed "0 warnings" in the Level 1 notes before any warning flags were enabled.
  - First rebuild failed with a linker "Permission denied" because the previous `MutualMind.exe` was still running.
* **Verification:** `cmake --build --preset windows-mingw-debug --clean-first` → all 6 translation units compiled with `-g -std=c++1z -Wall -Wextra -Wpedantic`: **0 errors, 0 warnings** (this time meaningful). MSVC: CI run #2 (`windows-latest`, commit `8d80805`) compiled all 6 files with `/W4 /permissive-` — **0 warnings** in the build log.

---

## Level 2: Testing, Tooling & CI
* **Status:** `Started` — GitHub Actions build workflow exists (`.github/workflows/ci.yml`, Ubuntu + Windows, smoke test only)
* **Planned changes:** see [roadmap.md](roadmap.md#level-2--testing-tooling--ci) — core library split, Catch2 v3, sanitizers in Linux CI, warnings-as-errors in CI, clang-format / clang-tidy, coverage.
