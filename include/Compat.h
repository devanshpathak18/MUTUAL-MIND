#pragma once

// ──────────────────────────────────────────────────────────
// Compat.h — Cross-compiler Modern C++ Compatibility Layer
//   Provides standard optional & string_view aliases so
//   code works identically across GCC 6.x to GCC 14+, Clang, and MSVC.
// ──────────────────────────────────────────────────────────

#if __has_include(<optional>)
  #include <optional>
  namespace std_compat {
    template<typename T> using optional = std::optional<T>;
  }
#elif __has_include(<experimental/optional>)
  #include <experimental/optional>
  namespace std_compat {
    template<typename T> using optional = std::experimental::optional<T>;
  }
#endif

#if __has_include(<string_view>)
  #include <string_view>
  namespace std_compat {
    using string_view = std::string_view;
  }
#elif __has_include(<experimental/string_view>)
  #include <experimental/string_view>
  namespace std_compat {
    using string_view = std::experimental::string_view;
  }
#endif
