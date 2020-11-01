/*
 *  SPDX-FileCopyrightText: 2018 Olivier Serve <tifauv@gmail.com>
 *
 *  SPDX-License-Identifier: LGPL-2.0-or-later
 */

#ifndef Account_H
#define Account_H

#include <QObject>
#include <QMetaType>
#include <QSharedPointer>

class Backend;

/**
 * @brief The Account class
 */
class Account : public QObject {
	Q_OBJECT

	Q_PROPERTY(QString name      READ name      WRITE setName     NOTIFY nameChanged      DESIGNABLE false)
	Q_PROPERTY(QString login     READ login     WRITE setLogin    NOTIFY loginChanged     DESIGNABLE false)
	Q_PROPERTY(QString website   READ website   WRITE setWebsite  NOTIFY websiteChanged   DESIGNABLE false)
	Q_PROPERTY(QString notes     READ notes     WRITE setNotes    NOTIFY notesChanged     DESIGNABLE false)
	Q_PROPERTY(QString password  READ password                    NOTIFY passwordChanged  DESIGNABLE false)
	
public:
	explicit Account(const QString& name = QString(), const QString& login = QString(), const QString& website = QString(), const QString& notes = QString(), QObject* parent = nullptr);
	explicit Account(const Account&);
	~Account() {}

	const QString& name()     const;
	const QString& login()    const;
	const QString& website()  const;
	const QString& notes()    const;
	const QString  password() const;

	Account* setName(const QString& name);
	Account* setLogin(const QString& login);
	Account* setWebsite(const QString& url);
	Account* setNotes(const QString& notes);
	Account* setBackend(const QSharedPointer<Backend>& backend);

signals:
	void nameChanged(QString);
	void loginChanged(QString);
	void websiteChanged(QString);
	void notesChanged(QString);
	void passwordChanged(QString);

private:
	QString m_name;
	QString m_login;
	QString m_website;
	QString m_notes;
	QSharedPointer<Backend> m_backend;
};

Q_DECLARE_METATYPE(Account)
Q_DECLARE_METATYPE(Account*)

#endif
