cmake_minimum_required(VERSION 3.5)
project(Download)

# Tell CMake to run moc when necessary:
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

# As moc files are generated in the binary dir, tell CMake
# to always look for includes there:
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_PREFIX_PATH "/opt/Qt5.7.0/5.7/gcc_64")

# to qt5.7
set(CMAKE_CXX_STANDARD 14)

# Widgets finds its own dependencies.
find_package(Qt5Widgets REQUIRED)
find_package(Qt5DBus)

# add source files
set(SOURCES
    main.cpp
    mainwindow/mainwindow.cpp)

# add main window
set(HEADERS mainwindow)
include_directories(${HEADERS})

# add details window
#set(HEADERS detailswindow)
#include_directories(${HEADERS})

# Find curl
set(curl find_package(libcurl))
if(curl)
    message(status "curl has been founded")
endif(curl)

# find ui and add executable
qt5_wrap_ui(UIS_HRDS
            mainwindow/mainwindow.ui)

add_executable(download_url ${SOURCES} ${UIS_HRDS} ${HEADERS})

# use widgets module
target_link_libraries(download_url Qt5::Widgets Qt5::DBus curl)
