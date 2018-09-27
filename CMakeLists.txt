cmake_minimum_required(VERSION 3.1)

project(Wallets LANGUAGES CXX)
set(PROJECT_VERSION "0.1")

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core Quick REQUIRED)
find_package(KF5Wallet)

add_executable(${PROJECT_NAME}
		core/Account.cpp
		core/Folder.cpp
		core/Trash.cpp
		core/Wallet.cpp
		QmlClipboardAdapter.cpp
		main.cpp
		ui.qrc
)

target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Quick KF5::Wallet)
