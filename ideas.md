# MutualMind — Master Architectural Ideas & Technical Blueprint

> **Vision:** Transforming a basic C++ console application into an industry-grade, resume-defining portfolio project demonstrating modern C++ standards, architectural design patterns, testing rigor, and applied financial engineering.

---

## 🧭 Project Evolution Matrix

```
Student Project (Baseline)                 Industry-Grade System (Goal)
├── Plaintext passwords in .txt     ───►   Salted SHA-256 + SQLite3 Embedded Database
├── Hardcoded static tables         ───►   GoF Strategy & Factory Design Patterns
├── Manual console verification     ───►   Catch2 Unit Tests + AddressSanitizer + GitHub Actions CI
├── Static 12% compound math        ───►   Stochastic Monte Carlo Simulation Engine
├── Manual text parsing             ───►   REST API Ingestion (libcurl) + JSON Parsing + Local Caching
└── Console stdout only             ───►   Structured CSV Exporter & Interactive Desktop GUI (Dear ImGui)
```

---

## 🏗️ Track A: Core Software Engineering & Systems (Primary Focus)

These upgrades establish the software engineering foundation expected of candidates interviewing for **Software Development Engineer (SWE / SDE)** roles.

### 1. Security & Modern Persistence
* **Current State:** Plaintext `name|email|password` stored in raw `data/users.txt` with manual delimiter splitting.
* **Target Upgrades:**
  - **Cryptographic Hashing & Salting:** Store irreversible SHA-256 digests with unique 16-byte random salts (`salt$hash`) to prevent rainbow table attacks.
  - **Embedded Relational Database (SQLite3):** Replace text files with SQLite tables (`users`, `portfolios`, `cached_navs`) using prepared statements to prevent injection attacks.
  - **The Repository Pattern:** Decouple data access (`IUserRepository`) from domain logic so the underlying database can be swapped without touching core business code.
* **Key Buzzwords:** *Cryptographic security, Salted SHA-256, SQLite3 C API, Repository Pattern, RAII Statement Handles.*

---

### 2. Software Architecture & GoF Design Patterns
* **Current State:** Hardcoded static lookup tables in `RiskProfile` and procedural `if/else` checks.
* **Target Upgrades:**
  - **GoF Strategy Pattern:** Define an `IAllocationStrategy` interface with interchangeable strategies:
    * `ConservativeStrategy` (Capital preservation / Debt heavy)
    * `ModerateStrategy` (Balanced hybrid)
    * `AggressiveStrategy` (Equity & small-cap growth)
    * `AgeBasedGlideslopeStrategy` (Dynamic glidepath based on investor age)
  - **Factory Method Pattern:** An `AllocationStrategyFactory` that dynamically constructs the appropriate strategy at runtime.
  - **Smart Pointer Ownership:** Enforce exclusive ownership using `std::unique_ptr` and zero raw pointer lifecycle hazards.
* **Key Buzzwords:** *Gang of Four (GoF) Patterns, Strategy Pattern, Factory Method, Open/Closed Principle (OCP), Smart Pointers.*

---

### 3. Engineering Rigor, Testing & CI/CD
* **Current State:** Manual keyboard testing through console input.
* **Target Upgrades:**
  - **Automated Test Suite (Catch2 v3):** Unit test targets validating financial formulas, boundary conditions (negative values, zero rates, edge scores), and authentication edge cases.
  - **Memory Sanitizers:** Compile with `-fsanitize=address,undefined` in debug builds to prove zero memory leaks and undefined behavior.
  - **GitHub Actions CI Pipeline:** Automated CI matrix compiling across Ubuntu (GCC/Clang) and Windows on every push and pull request.
* **Key Buzzwords:** *Test-Driven Development (TDD), Catch2, AddressSanitizer (ASan), Multi-Platform CI/CD, Regression Testing.*

---

### 4. Networking, REST APIs & Offline Caching
* **Current State:** Hardcoded fund names and dummy NAV rates.
* **Target Upgrades:**
  - **Live HTTP Client (`cpr` / `libcurl`):** Ingest real historical mutual fund NAV time-series from open financial endpoints (e.g., [mfapi.in](https://www.mfapi.in/)).
  - **JSON Deserialization (`nlohmann/json`):** Parse complex nested REST API responses into structured C++ data objects.
  - **Offline-First Caching Layer:** Cache downloaded NAV histories into SQLite so the application functions seamlessly even without an active internet connection.
* **Key Buzzwords:** *REST API Integration, libcurl, JSON Deserialization, Tiered Caching Strategy (Memory -> SQLite -> Network).*

---

### 5. Multi-Format Reporting & Interactive UI
* **Current State:** Standard console `cout` output only.
* **Target Upgrades:**
  - **Structured CSV Exporter:** Export complete projection schedules to RFC 4180-compliant `.csv` files.
  - **Self-Contained HTML/PDF Reports:** Generate standalone formatted investment summaries with embedded CSS and printable stylesheets (`@media print`).
  - **Desktop GUI (Dear ImGui):** An immediate-mode graphical dashboard with interactive sliders, real-time calculation updates, and charts via **ImPlot**.
* **Key Buzzwords:** *File Serialization, Immediate-Mode GUI (Dear ImGui), ImPlot, Automated Report Generation.*

---

## 📈 Track B: Quantitative Finance & Advanced Modeling (Future Expansion)

Once the core software engineering layer is complete, these advanced modules can be layered on for **Fintech & Quantitative Developer** roles.

### 1. Multithreaded Monte Carlo Simulation
* Replace static return projections with **10,000 to 100,000 stochastic trajectory simulations**.
* Model monthly returns using a normal distribution: $R_t \sim \mathcal{N}(\mu, \sigma)$ via standard `<random>` (`std::mt19937`).
* Compute key risk percentiles:
  - **10th Percentile:** Bear market / downside risk.
  - **50th Percentile:** Expected median return.
  - **90th Percentile:** Bull market upside potential.
  - **Probability of Loss:** $P(\text{Final Portfolio Value} < \text{Total Invested})$.

### 2. Custom C++ Thread Pool & Concurrency
* Build a custom C++17/20 **Thread Pool** with a task queue, condition variables (`std::condition_variable`), and worker threads (`std::thread` / `std::jthread`).
* Parallelize Monte Carlo path generation across all CPU cores with zero lock contention using thread-local random engines.
* Micro-benchmark with **Google Benchmark** (Single-threaded vs. 8-core Parallel Worker Pool).

### 3. Modern Portfolio Theory (Markowitz Optimization)
* Given $N$ funds, construct the historical $N \times N$ **Covariance Matrix ($\Sigma$)**.
* Solve for optimal portfolio weights ($w$) maximizing the **Sharpe Ratio** for a target volatility level (Efficient Frontier calculation).

### 4. Risk Modeling & Historical Stress Testing
* **Value-at-Risk (VaR):** Compute 95% and 99% Parametric and Historical VaR.
* **Conditional VaR (CVaR / Expected Shortfall):** Average loss incurred during extreme tail events.
* **Crisis Backtesting:** Replay portfolio performance against historical crashes (2008 Lehman Brothers, March 2020 COVID).

---

## 📝 Resume Impact: Before vs. After

### ❌ Before (Basic Student Project)
> *"Developed a C++ console application for mutual fund recommendations and SIP calculation using OOP concepts and file handling."*

### ✅ After (Production-Grade Engineering Showcase)
> **MutualMind — Quantitative Investment & Portfolio Engine** | *C++17, CMake, Catch2, SQLite3, libcurl, Dear ImGui, GitHub Actions*
> * Architected an object-oriented investment advisory engine implementing the **GoF Strategy & Repository patterns** to dynamically balance portfolio allocations across equity, debt, and liquid instruments.
> * Implemented a **Monte Carlo simulation engine** utilizing C++ `<random>` normal distributions to project 10,000+ probabilistic returns and percentile risk metrics.
> * Integrated an asynchronous **REST API client (`cpr`/`libcurl`)** with multi-tiered **SQLite3 caching** to ingest live NAV time-series and compute historical volatility, Sharpe Ratio, and Maximum Drawdown.
> * Engineered cryptographic **salted SHA-256 authentication** with RAII-managed database statements protecting against delimiter and SQL injection.
> * Designed an interactive immediate-mode desktop dashboard using **Dear ImGui**, enabling real-time visual scenario analysis and styled HTML/CSV report exports.
> * Established a multi-platform **CI/CD pipeline with GitHub Actions**, executing automated **Catch2** test suites with **AddressSanitizer (ASan)** ensuring zero memory leaks.