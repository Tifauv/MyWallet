#include "Account.h"
#include <QtDebug>

// CONSTRUCTORS
/**
 * @brief Account::Account
 * @param p_name
 * @param p_login
 * @param p_parent
 */
Account::Account(const QString& p_name, const QString& p_login, QObject* p_parent) :
    QObject(p_parent),
    m_name(p_name),
    m_login(p_login) {
	qDebug() << "(i) [Account] Created " << m_name << " with login " << m_login;
}


/**
 * @brief Account::Account
 * @param p_toCopy
 */
Account::Account(const Account& p_toCopy) :
    QObject(),
    m_name(p_toCopy.name()),
    m_login(p_toCopy.login()) {
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
	return m_name;
}


/**
 * @brief Account::password
 * @return
 */
const QString& Account::password() const {
	qDebug() << "(i) [Account] ::password() is not yet implemented.";
	return "Not yet implemented";
}


// SETTERS
/**
 * @brief Account::setName
 * @param p_name
 */
void Account::setName(const QString& p_name) {
	m_name = p_name;
	// TODO implement name change in the KWallet backend
	qDebug() << "(i) [Account] ::setName() is not fully implemented yet.";
	emit nameChanged(m_name);
}


/**
 * @brief Account::setLogin
 * @param p_login
 */
void Account::setLogin(const QString& p_login) {
	m_login = p_login;
	// TODO implement login change in the KWallet backend
	qDebug() << "(i) [Account] ::setLogin() is not fully implemented yet.";
	emit loginChanged(m_login);
}


/**
 * @brief Account::setPassword
 * @param password
 */
void Account::setPassword(const QString &password) {
	// TODO implement password change in the KWallet backend
	qDebug() << "(i) [Account] ::setPassword() is not yet implemented.";
	emit passwordChanged("Not yet implemented");
}
