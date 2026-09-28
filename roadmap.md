# MutualMind — Roadmap

MutualMind is a C++ console app for young investors: a risk quiz, fund suggestions, and SIP projections. I'm rebuilding it level by level to learn modern C++ and real software engineering practice. Each level introduces a few concepts, applies them to the codebase, and ends with a working, tested build.

- Ideas I haven't committed to yet: [ideas.md](ideas.md)
- What changed and why, task by task: [changes.md](changes.md)

---

## Timeline

Started 29 Sep 2026. Pace: roughly 1–1.5 hours a day alongside college and DSA practice.

| Weeks | Level | Target (approx.) | Status |
| :---: | :--- | :--- | :--- |
| 1–2 | Level 1 — Modern C++ idioms & memory safety | 12 Oct 2026 | In progress (first pass done, polish task 1 of 9 done) |
| 3–4 | Level 2 — Testing, tooling & CI | 26 Oct 2026 | CI build workflow exists |
| 5–6 | Level 3 — Design patterns & architecture | 9 Nov 2026 | Not started |
| 7–8 | Level 4 — Simulation engine & concurrency | 23 Nov 2026 | Not started |
| — | **Checkpoint v1.0 — ready for early applications** | 23 Nov 2026 | |
| 9–10 | Level 5 — Persistence & password security | 7 Dec 2026 | Not started |
| 11–12 | Level 6 — Live data & networking | 21 Dec 2026 | Not started |
| 13 | **Release v2.0** | 28 Dec 2026 | |
| 14–15 | Level 7 — Reports | 11 Jan 2027 | Not started |
| 16–20 | Level 8 — Desktop dashboard (Dear ImGui) | 15 Feb 2027 | Not started |
| 21 | **Release v3.0** | 22 Feb 2027 | |
| 22–24 | Buffer — exams, DSA, polish | 15 Mar 2027 | |

If a level runs late, the buffer absorbs it. When scope has to be cut, it comes out of Levels 7–8, never out of testing.

---

## How every level ends (exit criteria)

A level is done only when all of these are true:

1. **Clean build and green tests.** Zero warnings on GCC and MSVC; all tests pass in CI (from Level 2 onward).
2. **changes.md entry written by me.** What changed, why, alternatives I considered, and mistakes I made along the way.
3. **Explain-back.** I can explain every change without notes — checked with a 10-minute mock interview on that level.
4. **Honest history.** One commit per task in my own words; the finished level is tagged (`v0.1-level1`, `v0.2-level2`, …).

---

## Level 1 — Modern C++ Idioms & Memory Safety

**Goal:** write idiomatic C++17 instead of "C with classes".

**Concepts:** RAII · Rule of Zero · ownership (stack object vs `std::unique_ptr`) · `std::optional` · `std::string_view` · move semantics · compiler warnings

**Tasks**
- [x] First pass: `loginUser()` returns `std::optional<User>`, `string_view` in lookups, move-constructed `User`
- [x] 1. Enable compiler warnings (`-Wall -Wextra -Wpedantic` / `/W4 /permissive-`)
- [ ] 2. Upgrade toolchain to MSYS2 (UCRT64) GCC, update CMake presets, remove `Compat.h`
- [ ] 3. Rule of Zero — remove user-declared destructors that suppress move operations
- [ ] 4. Let RAII close file streams (drop manual `close()` calls)
- [ ] 5. Remove leftover `UserAuth` state; apply `string_view` and `const` consistently
- [ ] 6. Sink-parameter move pattern in `Person` / `Investor` / `MutualFund`
- [ ] 7. Stack object vs `unique_ptr<Investor>` — decide, and correct the Level 1 notes
- [ ] 8. Fix the EOF infinite loop in `readValidated`; bounds-check `getMonthName`
- [ ] 9. Stop tracking `data/users.txt` in git; ship an example file instead

> **Why the toolchain upgrade comes early:** the current compiler is MinGW.org GCC 6.3 (2016, 32-bit, `win32` thread model). It has no `std::thread` (needed in Level 4) and no sanitizer support (needed in Level 2).

**Resources**
- [LearnCpp — Smart pointers & move semantics](https://www.learncpp.com/cpp-tutorial/introduction-to-smart-pointers-move-semantics/)
- [LearnCpp — std::optional](https://www.learncpp.com/cpp-tutorial/stdoptional/)
- [C++ Core Guidelines](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines) — R.5 (prefer scoped objects), C.20 (Rule of Zero)
- [MSYS2](https://www.msys2.org/)

---

## Level 2 — Testing, Tooling & CI

**Goal:** prove correctness automatically on every push.

**Concepts:** unit tests & boundary cases · testability shaping design · CMake libraries and `PUBLIC`/`PRIVATE` · `FetchContent` · sanitizers · static analysis & formatting · CI

**Tasks**
- [x] GitHub Actions build on Ubuntu + Windows (done early)
- [ ] Split into a `mutualmind_core` library + `MutualMind` CLI executable
- [ ] Separate quiz scoring from console input so `RiskAssessor` can be tested
- [ ] Add Catch2 v3 via `FetchContent`; `tests/` covering `FinanceMath` (0% rate, 40-year horizon, number formatting incl. negatives) and risk-score boundaries
- [ ] Run tests in CI (`ctest`) on both platforms
- [ ] AddressSanitizer + UndefinedBehaviorSanitizer job in Linux CI
- [ ] Warnings as errors in CI only (`-Werror` / `/WX`)
- [ ] `.clang-format` + format check in CI; `clang-tidy` with a small, deliberate check set
- [ ] Coverage report (gcov/lcov) — record the real percentage

**Resources**
- [Catch2 tutorial](https://github.com/catchorg/Catch2/blob/devel/docs/tutorial.md)
- [AddressSanitizer wiki](https://github.com/google/sanitizers/wiki/AddressSanitizer)
- [clang-tidy](https://clang.llvm.org/extra/clang-tidy/)
- [GitHub Actions docs](https://docs.github.com/en/actions)

---

## Level 3 — Design Patterns & Architecture

**Goal:** add new behaviour by adding code, not by editing existing code.

**Concepts:** Strategy · Factory Method · Repository · dependency inversion · Open/Closed principle · where `unique_ptr` genuinely belongs (owning polymorphic objects)

**Tasks**
- [ ] `IAllocationStrategy` with Conservative / Moderate / Aggressive implementations
- [ ] Make allocations and fund picks consistent (every asset class in the split gets a matching fund)
- [ ] `AllocationStrategyFactory` returning `std::unique_ptr<IAllocationStrategy>`
- [ ] `IUserRepository` + `FileUserRepository`; `UserAuth` depends only on the interface
- [ ] Tests for each strategy; tests for auth using an in-memory fake repository
- [ ] Optional: `AgeBasedStrategy` (equity ≈ 100 − age) — proof that a new strategy is a new class with no edits elsewhere

**Resources**
- [Refactoring.Guru — Strategy in C++](https://refactoring.guru/design-patterns/strategy/cpp/example)
- [Refactoring.Guru — Factory Method in C++](https://refactoring.guru/design-patterns/factory-method/cpp/example)

---

## Level 4 — Simulation Engine & Concurrency

**Goal:** replace a single fixed-rate projection with a range of likely outcomes, and make it fast.

**Concepts:** `<random>` (`std::mt19937`, `std::normal_distribution`) and why not `rand()` · Monte Carlo simulation · percentiles · `std::thread`, data races, one RNG per thread · benchmarking · CSV output

**Tasks**
- [ ] `MonteCarloSimulator`: N paths using an *assumed* monthly mean and volatility per profile (replaced with real data in Level 6)
- [ ] Report 10th / 50th / 90th percentile outcomes and the probability of ending below the amount invested
- [ ] Seedable RNG so tests are deterministic
- [ ] Parallelise across threads; benchmark 1 thread vs N threads and record the machine + numbers
- [ ] Step-up SIP (contribution grows X% per year)
- [ ] CSV export of the SIP schedule and simulation percentiles
- [ ] Optional: XIRR using Newton-Raphson

**Resources**
- [LearnCpp — Random numbers with Mersenne Twister](https://www.learncpp.com/cpp-tutorial/generating-random-numbers-using-mersenne-twister/)
- [cppreference — std::thread](https://en.cppreference.com/w/cpp/thread/thread)
- [Wikipedia — Monte Carlo method](https://en.wikipedia.org/wiki/Monte_Carlo_method)

---

## Checkpoint v1.0 — Ready for Early Applications

- [ ] README rewritten in my own words: what it does, how to build it, design decisions, measured numbers
- [ ] Short terminal demo GIF in the README
- [ ] Tag `v1.0` and publish a GitHub release with the CI-built binaries
- [ ] Resume entry drafted only from what is actually done

---

## Level 5 — Persistence & Password Security

**Goal:** store data safely.

**Concepts:** why passwords need a slow hash (Argon2id) rather than a fast one like SHA-256 · salts · SQLite, prepared statements, transactions · RAII wrappers around C APIs

**Tasks**
- [ ] RAII wrappers for `sqlite3*` and `sqlite3_stmt*`
- [ ] `SqliteUserRepository` implementing `IUserRepository` — swapped in without touching `UserAuth`
- [ ] Hash passwords with Argon2id via libsodium (`crypto_pwhash_str` / `crypto_pwhash_str_verify`)
- [ ] Prepared statements only — no SQL built from strings
- [ ] One-time import of existing users from the old text file (hashing on import)
- [ ] Tests against an in-memory database (`:memory:`)

**Resources**
- [SQLite C/C++ interface intro](https://www.sqlite.org/cintro.html)
- [OWASP Password Storage Cheat Sheet](https://cheatsheetseries.owasp.org/cheatsheets/Password_Storage_Cheat_Sheet.html)
- [libsodium documentation](https://doc.libsodium.org/)
- [Computerphile — How NOT to store passwords](https://www.youtube.com/watch?v=8ZtInClt1FE)

---

## Level 6 — Live Data & Networking

**Goal:** base recommendations and simulations on real fund data.

**Concepts:** HTTP/REST, status codes, timeouts and failure handling · JSON parsing · caching and offline fallback · volatility, Sharpe ratio, maximum drawdown

**Tasks**
- [ ] Fetch NAV history from [mfapi.in](https://www.mfapi.in/) with `cpr`
- [ ] Parse responses with `nlohmann/json` into plain structs
- [ ] Cache in SQLite; work offline from the cache; refresh when stale
- [ ] Compute annualised return, volatility, Sharpe ratio and maximum drawdown from real NAV data
- [ ] Feed the real mean and volatility into the Monte Carlo engine (replacing Level 4's assumptions)
- [ ] Tests use saved JSON fixtures — no network access in tests

**Resources**
- [cpr documentation](https://docs.libcpr.org/)
- [nlohmann/json](https://github.com/nlohmann/json)

---

## Release v2.0

- [ ] README and changes.md up to date; tag `v2.0`; release binaries

---

## Level 7 — Reports

**Goal:** output a user can keep or share.

**Tasks**
- [ ] Self-contained HTML report: summary, allocation, projection table, simulation percentiles
- [ ] Print-friendly CSS (`@media print`)
- [ ] Escape user-provided text in the HTML
- [ ] Tests on the generated output

---

## Level 8 — Desktop Dashboard (Dear ImGui)

**Goal:** a visual front end on top of the same core library.

**Concepts:** immediate-mode GUI · render loop · GLFW + OpenGL setup · ImPlot charts

**Tasks**
- [ ] GLFW + OpenGL + Dear ImGui window linked to `mutualmind_core` (no logic duplicated in the GUI)
- [ ] Sliders for SIP amount, duration and risk profile
- [ ] Live projection chart and Monte Carlo percentile bands (ImPlot)
- [ ] Allocation chart
- [ ] Demo GIF at the top of the README

**Resources**
- [Dear ImGui](https://github.com/ocornut/imgui)
- [ImPlot](https://github.com/epezent/implot)

---

## Release v3.0

- [ ] README and changes.md up to date; tag `v3.0`; release binaries
