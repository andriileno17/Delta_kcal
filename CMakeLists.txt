cmake_minimum_required(VERSION 3.16)
project(Delta_kcal)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON) 
set(CMAKE_AUTORCC ON) 

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Gui Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Gui Widgets)

add_executable(Delta_kcal
    src/main.cpp
    src/core/MetabolicCore/MetabolicCore.cpp
    src/core/MetabolicCore/MetabolicCore.h
    src/core/User/User.cpp
    src/core/User/User.h
    src/ui/Profile/Profile.cpp
    src/ui/Profile/Profile.h
)

target_include_directories(Delta_kcal PRIVATE
    src/core/MetabolicCore
    src/core/User
    src/ui/Profile
)

target_link_libraries(Delta_kcal Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Gui Qt${QT_VERSION_MAJOR}::Widgets)