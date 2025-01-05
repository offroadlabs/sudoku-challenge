#!/bin/bash

# Couleurs pour les messages
GREEN='\033[0;32m'
RED='\033[0;31m'
BLUE='\033[0;34m'
NC='\033[0m'

# Fonction d'aide
show_help() {
    echo -e "${BLUE}Usage: ./build.sh <command>${NC}"
    echo
    echo "Commands:"
    echo -e "  ${GREEN}dev${NC}      - Clean, build et lance l'application"
    echo -e "  ${GREEN}build${NC}     - Compile le projet"
    echo -e "  ${GREEN}run${NC}       - Lance l'application"
    echo -e "  ${GREEN}clean${NC}     - Nettoie les fichiers de build"
    echo -e "  ${GREEN}test${NC}      - Exécution des tests"
}

# Compilation du projet
build() {
    echo -e "${BLUE}Compilation du projet...${NC}"
    mkdir -p build
    cd build
    
    if [[ "$OSTYPE" == "darwin"* ]]; then
        # Configuration pour macOS avec Homebrew
        cmake .. -DCMAKE_PREFIX_PATH=$(brew --prefix qt6)
    else
        # Configuration standard pour Linux
        cmake ..
    fi
    
    make -j$(nproc 2>/dev/null || sysctl -n hw.ncpu)
    cd ..
}

# Lancement de l'application
run() {
    if [[ "$OSTYPE" == "darwin"* ]]; then
        if [ ! -d "build/src/Sudoku.app" ]; then
            echo -e "${RED}L'application n'est pas compilée. Compilation...${NC}"
            build
        fi
        echo -e "${BLUE}Lancement de l'application...${NC}"
        open build/src/Sudoku.app
    else
        if [ ! -f "build/src/sudoku-qt" ]; then
            echo -e "${RED}L'application n'est pas compilée. Compilation...${NC}"
            build
        fi
        echo -e "${BLUE}Lancement de l'application...${NC}"
        ./build/src/sudoku-qt
    fi
}

# Nettoyage
clean() {
    echo -e "${BLUE}Nettoyage des fichiers de build...${NC}"
    rm -rf build
}

test() {
    echo -e "${BLUE}Exécution des tests...${NC}"
    mkdir -p build
    cd build
    
    if [[ "$OSTYPE" == "darwin"* ]]; then
        cmake .. -DCMAKE_PREFIX_PATH=$(brew --prefix qt6)
    else
        cmake ..
    fi
    
    # Compiler les tests
    cmake --build . --target sudoku_tests
    
    # Exécuter les tests
    ctest --output-on-failure
    
    cd ..
}

case "$1" in
    build)
        build
        ;;
    run)
        run
        ;;
    clean)
        clean
        ;;
    test)
        test
        ;;
    *)
        show_help
        exit 1
        ;;
esac 