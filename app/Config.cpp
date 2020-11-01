/*
 *  SPDX-FileCopyrightText: 2018 Olivier Serve <tifauv@gmail.com>
 *
 *  SPDX-License-Identifier: LGPL-2.0-or-later
 */

#include "Config.h"

// CONSTRUCTORS
/**
 * @brief Config::Config
 * @param p_parent
 */
Config::Config(QObject* p_parent) :
    QObject(p_parent) {
}


// GETTERS
/**
 * @brief Config::previousWallet
 * @return
 */
const QString Config::previousWallet() const {
	KConfigGroup previousRun(&m_kconfig, "PreviousRun");
	return previousRun.readEntry("Wallet", QString());
}


/**
 * @brief Config::previousFolder
 * @return
 */
const QString Config::previousFolder() const {
	KConfigGroup previousRun(&m_kconfig, "PreviousRun");
	return previousRun.readEntry("Folder", QString());
}


/**
 * @brief Config::previousWidth
 * @return
 */
uint Config::previousWidth() const {
	KConfigGroup previousRun(&m_kconfig, "PreviousRun");
	return previousRun.readEntry("Width", 640u);
}


/**
 * @brief Config::previousHeight
 * @return
 */
uint Config::previousHeight() const {
	KConfigGroup previousRun(&m_kconfig, "PreviousRun");
	return previousRun.readEntry("Height", 480u);
}


// SETTERS
/**
 * @brief Config::setPreviousWallet
 * @param p_wallet
 */
void Config::setPreviousWallet(const QString& p_wallet) {
	KConfigGroup previousRun(&m_kconfig, "PreviousRun");
	previousRun.writeEntry("Wallet", p_wallet);
	emit previousWalletChanged(p_wallet);
}


/**
 * @brief Config::setPreviousFolder
 * @param p_folder
 */
void Config::setPreviousFolder(const QString& p_folder) {
	KConfigGroup previousRun(&m_kconfig, "PreviousRun");
	previousRun.writeEntry("Folder", p_folder);
	emit previousFolderChanged(p_folder);
}


/**
 * @brief Config::setPreviousWidth
 * @param p_width
 */
void Config::setPreviousWidth(uint p_width) {
	KConfigGroup previousRun(&m_kconfig, "PreviousRun");
	previousRun.writeEntry("Width", p_width);
	emit previousWidthChanged(p_width);
}


/**
 * @brief Config::setPreviousHeight
 * @param p_height
 */
void Config::setPreviousHeight(uint p_height) {
	KConfigGroup previousRun(&m_kconfig, "PreviousRun");
	previousRun.writeEntry("Height", p_height);
	emit previousHeightChanged(p_height);
}
