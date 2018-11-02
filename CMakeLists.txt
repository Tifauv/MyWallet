cmake_minimum_required(VERSION 3.1)

project(MyWallet LANGUAGES CXX)
set(PROJECT_VERSION "0.1")

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core Quick REQUIRED)
find_package(KF5Wallet)
find_package(KF5Config)

add_executable(MyWallet
	core/Account.cpp
	core/Folder.cpp
	core/Wallet.cpp
	core/Backend.cpp
	core/KWalletBackend.cpp
	QmlClipboardAdapter.cpp
	Config.cpp
	main.cpp
	ui.qrc
)

target_link_libraries(MyWallet
	Qt5::Core
	Qt5::Quick
	KF5::Wallet
	KF5::ConfigCore
)

install(TARGETS MyWallet DESTINATION bin)
install(
	FILES
		core/Account.h
		core/Folder.h
		core/Wallet.h
		core/Backend.h
		core/KWalletBackend.h
		QmlClipboardAdapter.h
		Config.h
	DESTINATION include)
install(
	FILES
		eu.catwitch.mywallet.desktop
	DESTINATION share/applications)
