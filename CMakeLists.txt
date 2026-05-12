cmake_minimum_required(VERSION 3.16)
project(Delta_kcal)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON) 
set(CMAKE_AUTORCC ON) 

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Gui Widgets Sql Charts)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Gui Widgets Sql Charts)

add_executable(Delta_kcal
    src/main.cpp
    
    src/core/MetabolicCore/MetabolicCore.cpp
    src/core/MetabolicCore/MetabolicCore.h
    src/core/User/User.cpp
    src/core/User/User.h
    src/core/DataBaseManager/DataBaseManager.cpp
    src/core/DataBaseManager/DataBaseManager.h
    
    src/ui/MainWindow/MainWindow.cpp
    src/ui/MainWindow/MainWindow.h
    src/ui/StartScreen/StartScreen.cpp
    src/ui/StartScreen/StartScreen.h
    src/ui/Profile/Profile.cpp
    src/ui/Profile/Profile.h
    src/ui/UserSelectionScreen/UserSelectionScreen.cpp
    src/ui/UserSelectionScreen/UserSelectionScreen.h
    src/ui/UsersPage/UsersPage.cpp
    src/ui/UsersPage/UsersPage.h
)

target_include_directories(Delta_kcal PRIVATE
    src/core/MetabolicCore
    src/core/User
    src/core/DataBaseManager
    src/ui/MainWindow
    src/ui/StartScreen
    src/ui/Profile
    src/ui/UserSelectionScreen
    src/ui/UsersPage
)

target_link_libraries(Delta_kcal Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Gui Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Sql Qt6::Charts)