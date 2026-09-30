# MutualMind — Ideas

Ideas I might build later. Nothing here is committed — an idea moves to [roadmap.md](roadmap.md) only once I decide to do it.

---

## Parked

- **Google Benchmark** — replace hand-timed measurements with a proper micro-benchmark harness.
- **Markowitz optimisation** — covariance matrix of fund returns; weights that maximise the Sharpe ratio (efficient frontier).
- **Value at Risk / Expected Shortfall** — 95% and 99% historical and parametric VaR; average loss in the worst cases.
- **Crisis backtesting** — replay portfolios through the 2008 crash and March 2020.
- **Inflation-adjusted projections** — show real (today's money) vs nominal value.
- **HTML report** — self-contained, print-friendly report: summary, allocation, projection table, simulation percentiles. Was Level 7; replaced by the REST API server.

---

## Already moved into the roadmap

| Idea | Where it went |
| :--- | :--- |
| Catch2, sanitizers, CI | Level 2 |
| Strategy + Factory patterns, Repository pattern | Level 3 |
| SQLite persistence + password hashing | Level 4 — using Argon2id instead of salted SHA-256, because SHA-256 is too fast to protect passwords |
| Monte Carlo simulation, parallel execution, step-up SIP | Level 5 |
| Thread pool | Level 5 (optional task) |
| CSV reports | Level 5 |
| Fetching fund data from a REST API, JSON, offline caching | Level 6 |
| In-memory cache | Level 6 — as an LRU cache in front of the SQLite cache |
| Dear ImGui dashboard | Level 8 |
