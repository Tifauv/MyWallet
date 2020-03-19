#include "Account.h"
#include "Folder.h"
#include "Backend.h"
#include <QtDebug>

// CONSTRUCTORS
/**
 * @brief Account::Account
 * @param p_name
 * @param p_login
 * @param p_parent
 */
Account::Account(const QString& p_name, const QString& p_login, const QString& p_website, const QString& p_notes, QObject* p_parent) :
    QObject(p_parent),
    m_name(p_name),
    m_login(p_login),
	m_website(p_website),
	m_notes(p_notes) {
	qDebug() << "(i) [Account] Created " << m_name << " with login " << m_login;
}


/**
 * @brief Account::Account
 * @param p_toCopy
 */
Account::Account(const Account& p_toCopy) :
    QObject(),
    m_name(p_toCopy.name()),
    m_login(p_toCopy.login()),
	m_website(p_toCopy.website()),
	m_notes(p_toCopy.notes()),
	m_backend(p_toCopy.m_backend) {
	qDebug() << "(i) [Account] Copied account " << m_name << " with login " << m_login;
}


// GETTERS
/**
 * @brief Account::name
 * @return
 */
const QString& Account::name() const {
	return m_name;
}


/**
 * @brief Account::login
 * @return
 */
const QString& Account::login() const {
	return m_login;
}


/**
 * @brief Account::website
 * @return
 */
const QString& Account::website() const {
	return m_website;
}


/**
 * @brief Account::notes
 * @return
 */
const QString& Account::notes() const {
	return m_notes;
}


/**
 * @brief Account::password
 * @return 
 */
const QString Account::password() const {
	if (parent() == nullptr)
		return QString();

	return m_backend->retrievePassword(dynamic_cast<Folder*>(parent())->name(), name());
}


// SETTERS
/**
 * @brief Account::setName
 * @param p_name
 */
Account* Account::setName(const QString& p_name) {
	m_name = p_name;
	// TODO implement name change in the KWallet backend
	qDebug() << "(i) [Account] ::setName() is not fully implemented yet.";
	emit nameChanged(m_name);
	return this;
}


/**
 * @brief Account::setLogin
 * @param p_login
 */
Account* Account::setLogin(const QString& p_login) {
	m_login = p_login;
	// TODO implement login change in the KWallet backend
	qDebug() << "(i) [Account] ::setLogin() is not fully implemented yet.";
	emit loginChanged(m_login);
	return this;
}


/**
 * @brief Account::setWebsite
 * @param p_url
 */
Account* Account::setWebsite(const QString& p_url) {
	m_website = p_url;
	// TODO implement website change in the KWallet backend
	qDebug() << "(i) [Account] ::setWebsite() is not fully implemented yet.";
	emit websiteChanged(m_website);
	return this;
}


/**
 * @brief Account::setNotes
 * @param p_notes
 */
Account* Account::setNotes(const QString& p_notes) {
	m_notes = p_notes;
	// TODO implement notes change in the KWallet backend
	qDebug() << "(i) [Account] ::setNotes() is not fully implemented yet.";
	emit notesChanged(m_notes);
	return this;
}


/**
 * @brief Account::setBackend
 * @param p_backend
 * @return
 */
Account* Account::setBackend(const QSharedPointer<Backend>& p_backend) {
	m_backend = p_backend;
	return this;
}

