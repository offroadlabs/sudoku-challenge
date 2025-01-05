set(SOURCES
    main.cpp
    mainwindow.cpp
    screens/screen.cpp
    screens/homescreen.cpp
    screens/difficultyscreen.cpp
    screens/gamescreen.cpp
    screens/gameoverscreen.cpp
    core/grid.cpp
    core/sudoku.cpp
    core/gamestatemanager.cpp
)

set(HEADERS
    mainwindow.h
    screens/screen.h
    screens/homescreen.h
    screens/difficultyscreen.h
    screens/gamescreen.h
    screens/gameoverscreen.h
    core/grid.h
    styles/styles.h
    core/sudoku.h
    core/cell.h
    core/gamestatemanager.h
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

if(APPLE)
    set(ICON_NAME "sudoku.icns")
    set(ICON_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../resources/${ICON_NAME}")
    set_source_files_properties(${ICON_PATH} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        MACOSX_BUNDLE TRUE
        MACOSX_BUNDLE_BUNDLE_NAME "Sudoku"
        MACOSX_BUNDLE_BUNDLE_VERSION "1.0.0"
        MACOSX_BUNDLE_SHORT_VERSION_STRING "1.0"
        MACOSX_BUNDLE_INFO_PLIST "${CMAKE_CURRENT_SOURCE_DIR}/../resources/MacOSXBundleInfo.plist.in"
        MACOSX_BUNDLE_ICON_FILE ${ICON_NAME}
        OUTPUT_NAME "Sudoku"
    )
    target_sources(${PROJECT_NAME} PRIVATE ${ICON_PATH})
endif()

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets) 
