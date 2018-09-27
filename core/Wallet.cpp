#include "Wallet.h"
#include <QGuiApplication>
#include <QScopedPointer>
#include <QtDebug>
#include <KWallet/KWallet>


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


/**
 * @brief Wallet::retrievePassword
 * @param p_account
 * @param p_password
 *
 * @return 0: no error ;
 *         1: cannot open the application's wallet in KWallet ;
 *         2: there is no folder named after this wallet in KWallet ;
 *         3: there is no data for the requested account in this folder ;
 *         4: the account's data lacks the 'current password identifier' field ;
 *         5: there is no password named as the 'current password identifier'.
 */
int Wallet::retrievePassword(Account& p_account, QString& p_password) const {
	QScopedPointer<KWallet::Wallet> backend(KWallet::Wallet::openWallet(QGuiApplication::applicationName(), 0));
	if (!backend) {
		qDebug() << "/!\\ [Wallet] Wallet '" << qPrintable(QGuiApplication::applicationName()) <<  "' could not be opened!";
		return 1;
	}

	// Set the current folder
	if (!backend->setFolder(name())) {
		qDebug() << "/i\\ [Wallet] No folder named '" << qPrintable(name()) << "'!";
		return 2;
	}

	// Retrieve the account data
	QMap<QString, QString> accountData;
	if (backend->readMap(p_account.name(), accountData) != 0) {
		qDebug() << "/i\\ [Wallet] No account named '" << qPrintable(p_account.name()) << "' in folder '" << qPrintable(name()) << "'!";
		return 3;
	}

	// Get the current password identifier
	const QString& currentPwdId = accountData.value("password");
	if (currentPwdId.isEmpty()) {
		qDebug() << "/!\\ [Wallet] Account '" << p_account.name() << "' has no current password identifier!";
		return 4;
	}

	// Get the current password
	QString password;
	if (backend->readPassword(currentPwdId, password) != 0) {
		qDebug() << "/!\\ [Wallet] No password with id '" << currentPwdId << "'!";
		return 5;
	}

	p_password = password;
	return 0;
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
	names[NameRole]     = "name";
	names[LoginRole]    = "login";
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
		QString password;
		if (retrievePassword(*account, password) == 0)
			return QVariant(password);
	}

	return QVariant();
}


/**
 * @brief Wallet::insertRow
 * @param p_row
 * @param p_account
 */
void Wallet::insertRow(int p_row, Account* p_account) {
	Q_ASSERT(p_account);

	beginInsertRows(QModelIndex(), p_row, p_row);
	connect(p_account, SIGNAL(nameChanged(QString)),  SLOT(handleDataChanged()));
	connect(p_account, SIGNAL(loginChanged(QString)), SLOT(handleDataChanged()));
	m_accounts.insert(p_row, p_account);
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
