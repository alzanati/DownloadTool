cmake_minimum_required(VERSION 3.5)
project(Download)

# Tell CMake to run moc when necessary:
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

# As moc files are generated in the binary dir, tell CMake
# to always look for includes there:
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# to qt5.7
set(CMAKE_CXX_STANDARD 14)

# Widgets finds its own dependencies.
find_package(Qt5Widgets REQUIRED)
find_package(Qt5DBus)

# Find curl
set(curl find_package(libcurl))
if(curl)
    MESSAGE(curl)
endif(curl)

# find ui and add executable
qt5_wrap_ui(UIS_HRDS mainwindow.ui)
add_executable(download_url main.cpp mainwindow.cpp ${UIS_HRDS})

# use widgets module
target_link_libraries(download_url Qt5::Widgets Qt5::DBus curl)
