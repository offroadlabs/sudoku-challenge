set(CMAKE_SYSTEM_NAME Darwin)
set(CMAKE_SYSTEM_PROCESSOR arm64)

# Chemins Qt sur macOS
set(Qt6_DIR "$(brew --prefix qt6)/lib/cmake/Qt6")
set(CMAKE_PREFIX_PATH "$(brew --prefix qt6)") 