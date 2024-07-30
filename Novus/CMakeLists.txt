cmake_minimum_required(VERSION 3.16)

project(Novus VERSION 0.1 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Qt packages
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

# Enable AUTOMOC, AUTORCC, and AUTOUIC
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Add your executable and include the resources file
qt_add_executable(Novus
    main.cpp
    novus.cpp
    novus.h
    projectWindow.ui
    preferences.h
    preferences.cpp
    preferences.ui
    resources.qrc
    explorer.h explorer.cpp explorer.ui
)

# Link against Qt libraries
target_link_libraries(Novus PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets)

# Set target properties for macOS and Windows
set_target_properties(Novus PROPERTIES
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

# Install rules
include(GNUInstallDirs)
install(TARGETS Novus
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Finalize the executable
qt_finalize_executable(Novus)
