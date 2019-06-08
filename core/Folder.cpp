#include "Folder.h"
#include "Backend.h"
#include <QGuiApplication>
#include <QScopedPointer>
#include <QtDebug>


// CONSTRUCTORS
/**
 * @brief Folder::Wallet
 * @param p_parent
 */
Folder::Folder(QObject* p_parent) :
    QAbstractListModel(p_parent) {
	qDebug() << "(i) [Folder] Created.";
}


/**
 * @brief Folder::Wallet
 * @param p_toCopy
 */
Folder::Folder(const Folder& p_toCopy) :
    QAbstractListModel(),
    m_name(p_toCopy.name()),
    m_tagColor(p_toCopy.tagColor()),
    m_accounts(p_toCopy.m_accounts),
    m_backend(p_toCopy.m_backend) {
	qDebug() << "(i) [Folder] Copied folder '" << m_name << "' with tag color '" << m_tagColor << "' and " << m_accounts.count() << " accounts.";
}


// GETTERS
/**
 * @brief Folder::name
 * @return
 */
const QString& Folder::name() const {
	return m_name;
}


/**
 * @brief Folder::tagColor
 * @return
 */
const QString& Folder::tagColor() const {
	return m_tagColor;
}


/**
 * @brief Folder::count
 * @return
 */
int Folder::count() const {
	return rowCount();
}


// SETTERS
/**
 * @brief Folder::setName
 * @param p_name
 *
 * @return this
 */
Folder* Folder::setName(const QString& p_name) {
	m_name = p_name;
	qDebug() << "(i) [Folder] Changed name to '" << m_name << "'.";
	emit nameChanged(m_name);
	return this;
}


/**
 * @brief Folder::setTagColor
 * @param p_color
 *
 * @return this
 */
Folder* Folder::setTagColor(const QString& p_color) {
	m_tagColor = p_color;
	qDebug() << "(i) [Folder] Changed tag color to '" << m_tagColor << "'.";
	emit tagColorChanged(m_tagColor);
	return this;
}


/**
 * @brief Folder::setBackend
 * @param p_backend
 * @return
 */
Folder* Folder::setBackend(const QSharedPointer<Backend> p_backend) {
	m_backend = p_backend;
	return this;
}


// NATIVE API
/**
 * @brief Folder::createAccount
 * @param p_name
 * @param p_login
 */
Account* Folder::createAccount(const QString& p_name, const QString& p_login, const QString& p_password) {
	auto account = new Account(p_name, p_login, this);
	m_backend->createAccount(name(), *account, p_password);
	addAccount(account);
	return account;
}


/**
 * @brief Folder::deleteAccount
 * @param p_row
 */
void Folder::deleteAccount(int p_row) {
	// Index range check
	if (p_row < 0 || p_row >= rowCount())
		return;

	auto account = removeRow(p_row);
	if (m_backend->hasAccount(name(), account->name()))
		m_backend->removeAccount(name(), account->name());
	delete account;
}


/**
 * @brief Folder::get
 * @param p_row
 * @return 
 */
Account* Folder::get(int p_row) const {
	if (p_row < 0 || p_row >= rowCount())
		return nullptr;
	
	return m_accounts.at(p_row);
}


// PRIVATE BACKEND API
/**
 * @brief Folder::addAccount
 * @param p_account
 */
void Folder::addAccount(Account* p_account) {
	p_account->setParent(this);
	appendRow(p_account);
}


// MODEL/VIEW API
/**
 * @brief Folder::rowCount
 * @param p_parent
 * @return
 */
int Folder::rowCount(const QModelIndex& p_parent) const {
	Q_UNUSED(p_parent);
	return m_accounts.count();
}


/**
 * @brief Folder::data
 * @param p_index
 * @param p_role
 * @return
 */
QVariant Folder::data(const QModelIndex& p_index, int p_role) const {
	qDebug() << "(i) [Folder] Query data for role " << p_role << " of account at row " << p_index.row();
	if (p_index.row() < 0 || p_index.row() >= rowCount())
		return QVariant();

	auto account = m_accounts.at(p_index.row());
	switch (p_role) {
	case NameRole:
		return account->name();
	case LoginRole:
		return account->login();
	case PasswordRole:
		return m_backend->retrievePassword(name(), account->name());
	}

	return QVariant();
}


/**
 * @brief Folder::roleNames
 * @return
 */
QHash<int, QByteArray> Folder::roleNames() const {
	QHash<int, QByteArray> names;
	names[NameRole]     = "name";
	names[LoginRole]    = "login";
	names[PasswordRole] = "password";
	return names;
}


/**
 * @brief Folder::appendRow
 * @param p_account
 */
void Folder::appendRow(Account* p_account) {
	insertRow(rowCount(), p_account);
}


/**
 * @brief Folder::insertRow
 * @param p_row
 * @param p_account
 */
void Folder::insertRow(int p_row, Account* p_account) {
	Q_ASSERT(p_account);

	beginInsertRows(QModelIndex(), p_row, p_row);
	connect(p_account, SIGNAL(nameChanged(QString)),  SLOT(handleDataChanged()));
	connect(p_account, SIGNAL(loginChanged(QString)), SLOT(handleDataChanged()));
	m_accounts.insert(p_row, p_account);
	endInsertRows();
	emit countChanged(rowCount());
	qDebug() << "(i) [Folder] Account '" << p_account->name() << "' inserted into folder '" << name() << "' at position " << p_row << ".";
}


/**
 * @brief Folder::removeRow
 * @param p_row
 * @return
 */
Account* Folder::removeRow(int p_row) {
	if (p_row < 0 || p_row >= rowCount())
		return nullptr;

	beginRemoveRows(QModelIndex(), p_row, p_row);
	auto account = m_accounts.takeAt(p_row);
	account->disconnect(this, SLOT(handleDataChanged()));
	endRemoveRows();
	emit countChanged(rowCount());
	qDebug() << "(i) [Folder] Account '" << account->name() << "' removed from folder '" << name() << "'.";
	return account;
}


// PRIVATE SLOTS: DATA CHANGE SIGNALLING
/**
 * @brief Folder::handleDataChanged
 */
void Folder::handleDataChanged() {
	QModelIndex index( createIndex( m_accounts.indexOf(static_cast<Account*>(sender())), 0 ) );
	emit dataChanged(index, index);
}
