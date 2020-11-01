/*
 *  SPDX-FileCopyrightText: 2018 Olivier Serve <tifauv@gmail.com>
 *
 *  SPDX-License-Identifier: LGPL-2.0-or-later
 */

#ifndef Backend_H
#define Backend_H

#include <QObject>

class Folder;
class Account;

class Backend : public QObject {
	Q_OBJECT

public:
	explicit Backend(QObject* parent = nullptr);
	~Backend() {}

	// Initial loading
	virtual void load() = 0;

	// Folder management
	virtual bool hasFolder(const QString& name) const = 0;
	virtual void createFolder(const Folder& folder) const = 0;
	virtual void removeFolder(const QString& name) const = 0;

	// Account management
	virtual bool hasAccount(const QString& folder, const QString& name) const = 0;
	virtual void createAccount(const QString& folder, const Account& account, const QString& password) const = 0;
	virtual void removeAccount(const QString& folder, const QString& name) const = 0;

	virtual bool modifyAccountLogin(const QString& folder, const QString& name, const QString& login) const = 0;
	virtual bool modifyAccountWebsite(const QString& folder, const QString& name, const QString& website) const = 0;
	virtual bool modifyAccountNotes(const QString& folder, const QString& name, const QString& notes) const = 0;
	
	// Password management
	virtual const QString retrievePassword(const QString& folderName, const QString& accountName) const = 0;
	virtual const QMap<QString,QString> retrievePasswordHistory(const QString& p_folder, const QString& p_account) const = 0;
	virtual bool renewPassword(const QString& p_folder, const QString& p_account, const QString& p_password) const = 0;

signals:
	void opened();
	void openFailed();
	void folderLoaded(Folder*) const;
	void loaded();
};

#endif
