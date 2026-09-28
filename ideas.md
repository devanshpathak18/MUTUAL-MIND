# MutualMind — Ideas

Ideas I might build later. Nothing here is committed — an idea moves to [roadmap.md](roadmap.md) only once I decide to do it.

---

## Parked

- **Thread pool** — a reusable worker pool (task queue + `std::condition_variable`) instead of spawning threads per simulation. Natural follow-up to Level 4.
- **Google Benchmark** — replace hand-timed measurements with a proper micro-benchmark harness.
- **Markowitz optimisation** — covariance matrix of fund returns; weights that maximise the Sharpe ratio (efficient frontier).
- **Value at Risk / Expected Shortfall** — 95% and 99% historical and parametric VaR; average loss in the worst cases.
- **Crisis backtesting** — replay portfolios through the 2008 crash and March 2020.
- **Inflation-adjusted projections** — show real (today's money) vs nominal value.
- **In-memory cache** in front of the Level 6 SQLite cache.

---

## Already moved into the roadmap

| Idea | Where it went |
| :--- | :--- |
| Catch2, sanitizers, CI | Level 2 |
| Strategy + Factory patterns, Repository pattern | Level 3 |
| Monte Carlo simulation, parallel execution, step-up SIP | Level 4 |
| SQLite persistence + password hashing | Level 5 — using Argon2id instead of salted SHA-256, because SHA-256 is too fast to protect passwords |
| REST API, JSON, offline caching | Level 6 |
| CSV / HTML reports | Level 4 (CSV) and Level 7 (HTML) |
| Dear ImGui dashboard | Level 8 |
