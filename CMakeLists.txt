cmake_minimum_required (VERSION 3.1)

project (MyWallet  VERSION 0.2  LANGUAGES CXX)

set (CMAKE_INCLUDE_CURRENT_DIR ON)
set (CMAKE_AUTOMOC ON)
set (CMAKE_AUTORCC ON)
set (CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

# Find dependencies
find_package (Qt5 COMPONENTS Core Quick REQUIRED)
find_package (KF5Kirigami2 REQUIRED)
find_package (KF5Wallet    REQUIRED)
find_package (KF5Config    REQUIRED)

# Configure a header file to pass some CMake settings to the source code
configure_file (
	"${PROJECT_SOURCE_DIR}/MyWalletConfig.h.in"
	"${PROJECT_BINARY_DIR}/MyWalletConfig.h"
)
# Add the binary tree to the search path for include files
include_directories ("${PROJECT_BINARY_DIR}")

# Main executable
add_executable (MyWallet
	core/Account.cpp
	core/Folder.cpp
	core/Wallet.cpp
	core/Backend.cpp
	core/KWalletBackend.cpp
	app/QmlClipboardAdapter.cpp
	app/Config.cpp
	app/main.cpp
	app/ui.qrc
)

target_link_libraries (MyWallet
	Qt5::Core
	Qt5::Quick
	KF5::Wallet
	KF5::ConfigCore
)

install (TARGETS MyWallet DESTINATION bin)
install (
	FILES app/eu.catwitch.mywallet.desktop
	DESTINATION share/applications)
