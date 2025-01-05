#!/bin/bash

# Couleurs pour les messages
RED='\033[0;31m'
GREEN='\033[0;32m'
BLUE='\033[0;34m'
NC='\033[0m'

# Vérifier si on est sur macOS
if [ "$(uname)" != "Darwin" ]; then
    echo -e "${RED}Ce script ne fonctionne que sur macOS${NC}"
    exit 1
fi

# Vérifier si l'image source existe
if [ ! -f "resources/icon.png" ]; then
    echo -e "${RED}Erreur: resources/icon.png non trouvé${NC}"
    echo -e "Veuillez placer votre image source au format PNG dans resources/icon.png"
    exit 1
fi

echo -e "${BLUE}Création de l'application macOS avec icône...${NC}"

# Créer les répertoires nécessaires
mkdir -p resources/Icon.iconset

# Générer les différentes tailles d'icônes
echo -e "${BLUE}Génération des icônes...${NC}"
SIZES=("16" "32" "64" "128" "256" "512" "1024")
for size in "${SIZES[@]}"; do
    if [ "$size" = "1024" ]; then
        sips -z $size $size resources/icon.png --out resources/Icon.iconset/icon_512x512@2x.png
    elif [ "$size" = "64" ]; then
        sips -z $size $size resources/icon.png --out resources/Icon.iconset/icon_32x32@2x.png
    elif [ "$size" = "32" ]; then
        sips -z $size $size resources/icon.png --out resources/Icon.iconset/icon_16x16@2x.png
        sips -z $size $size resources/icon.png --out resources/Icon.iconset/icon_32x32.png
    elif [ "$size" = "16" ]; then
        sips -z $size $size resources/icon.png --out resources/Icon.iconset/icon_16x16.png
    else
        sips -z $size $size resources/icon.png --out resources/Icon.iconset/icon_${size}x${size}.png
        sips -z $((size*2)) $((size*2)) resources/icon.png --out resources/Icon.iconset/icon_${size}x${size}@2x.png
    fi
done

# Créer le fichier .icns
echo -e "${BLUE}Création du fichier .icns...${NC}"
iconutil -c icns resources/Icon.iconset -o resources/sudoku.icns

# Créer le fichier Info.plist
echo -e "${BLUE}Création du fichier Info.plist...${NC}"
cat > resources/MacOSXBundleInfo.plist.in << 'EOL'
<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE plist PUBLIC "-//Apple Computer//DTD PLIST 1.0//EN" "http://www.apple.com/DTDs/PropertyList-1.0.dtd">
<plist version="1.0">
<dict>
    <key>CFBundleDevelopmentRegion</key>
    <string>French</string>
    <key>CFBundleExecutable</key>
    <string>${MACOSX_BUNDLE_EXECUTABLE_NAME}</string>
    <key>CFBundleGetInfoString</key>
    <string>${MACOSX_BUNDLE_INFO_STRING}</string>
    <key>CFBundleIconFile</key>
    <string>sudoku.icns</string>
    <key>CFBundleIdentifier</key>
    <string>com.offroadlabs.sudoku</string>
    <key>CFBundleName</key>
    <string>${MACOSX_BUNDLE_BUNDLE_NAME}</string>
    <key>CFBundlePackageType</key>
    <string>APPL</string>
    <key>CFBundleShortVersionString</key>
    <string>${MACOSX_BUNDLE_SHORT_VERSION_STRING}</string>
    <key>CFBundleVersion</key>
    <string>${MACOSX_BUNDLE_BUNDLE_VERSION}</string>
    <key>NSHighResolutionCapable</key>
    <true/>
</dict>
</plist>
EOL

# Modifier le CMakeLists.txt
echo -e "${BLUE}Mise à jour du CMakeLists.txt...${NC}"
if ! grep -q "MACOSX_BUNDLE" src/CMakeLists.txt; then
    # Sauvegarder une copie
    cp src/CMakeLists.txt src/CMakeLists.txt.bak
    
    # Ajouter la configuration macOS
    awk '/add_executable\(.*\)/ { 
        print;
        print "\nif(APPLE)";
        print "    set(ICON_NAME \"sudoku.icns\")";
        print "    set(ICON_PATH \"${CMAKE_CURRENT_SOURCE_DIR}/../resources/${ICON_NAME}\")";
        print "    set_source_files_properties(${ICON_PATH} PROPERTIES MACOSX_PACKAGE_LOCATION \"Resources\")";
        print "    set_target_properties(${PROJECT_NAME} PROPERTIES";
        print "        MACOSX_BUNDLE TRUE";
        print "        MACOSX_BUNDLE_BUNDLE_NAME \"Sudoku\"";
        print "        MACOSX_BUNDLE_BUNDLE_VERSION \"1.0.0\"";
        print "        MACOSX_BUNDLE_SHORT_VERSION_STRING \"1.0\"";
        print "        MACOSX_BUNDLE_INFO_PLIST \"${CMAKE_CURRENT_SOURCE_DIR}/../resources/MacOSXBundleInfo.plist.in\"";
        print "        MACOSX_BUNDLE_ICON_FILE ${ICON_NAME}";
        print "        OUTPUT_NAME \"Sudoku\"";
        print "    )";
        print "    target_sources(${PROJECT_NAME} PRIVATE ${ICON_PATH})";
        print "endif()";
        next }1' src/CMakeLists.txt.bak > src/CMakeLists.txt
fi

# Nettoyer les fichiers temporaires
rm -rf resources/Icon.iconset
rm -f src/CMakeLists.txt.bak

echo -e "${GREEN}Configuration terminée !${NC}"
echo -e "Pour compiler l'application :"
echo -e "${BLUE}1. ./build.sh clean${NC}"
echo -e "${BLUE}2. ./build.sh build${NC}"
echo -e "L'application se trouvera dans ${BLUE}build/src/sudoku-qt.app${NC}"