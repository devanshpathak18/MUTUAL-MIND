cmake_minimum_required(VERSION 3.16)
project(MutualMind LANGUAGES CXX)

# ── C++ Standard ──
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ── Source files ──
set(SOURCES
    src/main.cpp
    src/FinanceMath.cpp
    src/UserAuth.cpp
    src/RiskAssessor.cpp
    src/InvestmentLearningHub.cpp
    src/SIPPredictor.cpp
)

# ── Target definition ──
add_executable(MutualMind ${SOURCES})

# ── Modern target-based include directories ──
target_include_directories(MutualMind PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# ── Copy data/ folder next to the binary so the app finds users.txt ──
add_custom_command(TARGET MutualMind POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/data
        $<TARGET_FILE_DIR:MutualMind>/data
    COMMENT "Copying data folder to output directory"
)
