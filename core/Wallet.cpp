#include "Wallet.h"
#include <QtDebug>

// CONSTRUCTORS
/**
 * @brief Wallet::Wallet
 * @param p_parent
 */
Wallet::Wallet(QObject* p_parent) :
    QAbstractListModel(p_parent) {
	qDebug() << "(i) [Wallet] Created.";
}


/**
 * @brief Wallet::Wallet
 * @param p_toCopy
 */
Wallet::Wallet(const Wallet& p_toCopy) :
    QAbstractListModel(),
    m_name(p_toCopy.name()),
    m_tagColor(p_toCopy.tagColor()),
    m_accounts(p_toCopy.m_accounts) {
	qDebug() << "(i) [Wallet] Copied wallet " << m_name << " with tag color " << m_tagColor << " and " << m_accounts.count() << " accounts.";
}


// GETTERS
/**
 * @brief Wallet::name
 * @return
 */
const QString& Wallet::name() const {
	return m_name;
}


/**
 * @brief Wallet::tagColor
 * @return
 */
const QString& Wallet::tagColor() const {
	return m_tagColor;
}


/**
 * @brief Wallet::count
 * @return
 */
int Wallet::count() const {
	return rowCount();
}


// SETTERS
/**
 * @brief Wallet::setName
 * @param p_name
 */
Wallet* Wallet::setName(const QString& p_name) {
	m_name = p_name;
	qDebug() << "(i) [Wallet] Changed name to " << m_name;
	emit nameChanged(m_name);
	return this;
}


/**
 * @brief Wallet::setTagColor
 * @param p_color
 */
Wallet* Wallet::setTagColor(const QString& p_color) {
	m_tagColor = p_color;
	qDebug() << "(i) [Wallet] Changed tag color to " << m_tagColor;
	emit tagColorChanged(m_tagColor);
	return this;
}


// NATIVE API
/**
 * @brief Wallet::addAccount
 * @param p_name
 * @param p_login
 */
void Wallet::addAccount(const QString& p_name, const QString& p_login) {
	insertRow(rowCount(), new Account(p_name, p_login));
}


// MODEL/VIEW API
/**
 * @brief Wallet::rowCount
 * @param p_parent
 * @return
 */
int Wallet::rowCount(const QModelIndex& p_parent) const {
	Q_UNUSED(p_parent);
	return m_accounts.count();
}


/**
 * @brief Wallet::roleNames
 * @return
 */
QHash<int, QByteArray> Wallet::roleNames() const {
	QHash<int, QByteArray> names;
	names[NameRole] = "name";
	names[LoginRole] = "login";
	names[PasswordRole] = "password";
	return names;
}


/**
 * @brief Wallet::data
 * @param p_index
 * @param p_role
 * @return
 */
QVariant Wallet::data(const QModelIndex& p_index, int p_role) const {
	qDebug() << "(i) [Wallet] Query data for role " << p_role << " of account at row " << p_index.row();
	if (p_index.row() < 0 || p_index.row() >= rowCount())
		return QVariant();

	Account* account = m_accounts.at(p_index.row());
	switch (p_role) {
	case NameRole:
		return account->name();
	case LoginRole:
		return account->login();
	case PasswordRole:
		return account->password();
	default:
		return QVariant();
	}
}


/**
 * @brief Wallet::insertRow
 * @param p_row
 * @param p_account
 */
void Wallet::insertRow(int p_row, Account* p_account) {
	Q_ASSERT(p_account);

	beginInsertRows(QModelIndex(), p_row, p_row);
	connect(p_account, SIGNAL(nameChanged(QString)),     SLOT(handleDataChanged()));
	connect(p_account, SIGNAL(loginChanged(QString)),    SLOT(handleDataChanged()));
	connect(p_account, SIGNAL(passwordChanged(QString)), SLOT(handleDataChanged()));
	m_accounts.insert(p_row, p_account);
	//p_account->setParent(this);
	endInsertRows();
	emit countChanged(rowCount());
	qDebug() << "(i) [Wallet] Account " << p_account->name() << " inserted into wallet " << name() << " at position " << p_row;
}


/**
 * @brief Wallet::removeRow
 * @param p_row
 * @return
 */
Account* Wallet::removeRow(int p_row) {
	if (p_row < 0 || p_row >= rowCount())
		return nullptr;

	beginRemoveRows(QModelIndex(), p_row, p_row);
	Account* account = m_accounts.takeAt(p_row);
	account->disconnect(this, SLOT(handleDataChanged()));
	endRemoveRows();
	emit countChanged(rowCount());
	qDebug() << "(i) [Wallet] Account " << account->name() << " removed from wallet " << name();
	return account;
}


// PRIVATE SLOTS: DATA CHANGE SIGNALLING
/**
 * @brief Wallet::handleDataChanged
 */
void Wallet::handleDataChanged() {
	Account* account = static_cast<Account*>(sender());
	QModelIndex index = createIndex(m_accounts.indexOf(account), 0);
	emit dataChanged(index, index);
}
