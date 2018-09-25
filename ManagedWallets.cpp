#include "ManagedWallets.h"
#include <QGuiApplication>
#include <QtDebug>
#include <KWallet/kwallet.h>

// CONSTRUCTORS
/**
 * @brief ManagedWallets::ManagedWallets
 * @param parent
 */
ManagedWallets::ManagedWallets(QObject* p_parent) :
    QAbstractListModel(p_parent) {
	qDebug() << "(i) [ManagedWallets] Created.";
	if (!KWallet::Wallet::isEnabled()) {
		qDebug() << "/!\\ [ManagedWallets] KWallet subsystem is disabled !";
		return;
	}
	qDebug() << "(i) [ManagedWallets] Default local wallet is '" << qPrintable(KWallet::Wallet::LocalWallet()) << "'.";
	//qDebug() << "(i) [ManagedWallets] Default network wallet is '" << qPrintable(KWallet::Wallet::NetworkWallet()) << "'.";

	// Open the default wallet
	KWallet::Wallet* mainWallet = KWallet::Wallet::openWallet(KWallet::Wallet::LocalWallet(), 0);
	qDebug() << "(i) [ManagedWallets] Default wallet is now opened";

	// Retrieve the app folder
	if (mainWallet->hasFolder(QGuiApplication::applicationName()))
		qDebug() << "(i) [ManagedWallets] Our own folder '" << qPrintable(QGuiApplication::applicationName()) << "' already exists.";
	else {
		mainWallet->createFolder(QGuiApplication::applicationName());
		qDebug() << "(i) [ManagedWallets] Our own folder '" << qPrintable(QGuiApplication::applicationName()) << "' has been created.";
	}
	mainWallet->setFolder(QGuiApplication::applicationName());
	qDebug() << "(i) [ManagedWallets] Our own folder '" << qPrintable(QGuiApplication::applicationName()) << "' has been selected.";

	// List the managed wallets
	QMap<QString, QString> tagColors;
	mainWallet->readMap("ManagedWallets", tagColors);
	qDebug() << "(i) [ManagedWallets] Managed wallets:";
	QMapIterator<QString, QString> i(tagColors);
	while (i.hasNext()) {
		i.next();
		qDebug() << "(i) [ManagedWallets]   - Wallet " << qPrintable(i.key()) << " (tag " << qPrintable(i.value()) << ").";
		auto wallet = new Wallet();
		wallet->setName(i.key())->setTagColor(i.value());

		// Retrieve the password of the wallet
		QString password;
		mainWallet->readPassword(wallet->name(), password);
		qDebug() << "(i) [ManagedWallets]     Password: " << qPrintable(password);

		// Open the new wallet
		KWallet::Wallet* dataWallet = KWallet::Wallet::openWallet(wallet->name(), 0);
		delete dataWallet;

		// Add the wallet to the model
		insertRow(rowCount(), wallet);
	}
}


// MODEL/VIEW API
/**
 * @brief ManagedWallets::rowCount
 * @param p_parent
 * @return
 */
int ManagedWallets::rowCount(const QModelIndex& p_parent) const {
	Q_UNUSED(p_parent);
	return m_wallets.count();
}


/**
 * @brief ManagedWallets::data
 * @param p_index
 * @param p_role
 * @return
 */
QVariant ManagedWallets::data(const QModelIndex& p_index, int p_role) const {
	if (p_index.row() < 0 || p_index.row() >= rowCount())
		return QVariant();

	qDebug() << "(i) [ManagedWallets] Looking for data at row " << p_index.row() << " with role " << p_role;
	Wallet* wallet = m_wallets.at(p_index.row());
	switch (p_role) {
	case NameRole:
		return wallet->name();
	case TagColorRole:
		return wallet->tagColor();
	case AccountListRole:
		return QVariant::fromValue(wallet);
	default:
		return QVariant();
	}
}


/**
 * @brief ManagedWallets::insertRow
 * @param p_row
 * @param p_wallet
 * @return
 */
bool ManagedWallets::insertRow(int p_row, Wallet* p_wallet) {
	Q_ASSERT(p_wallet);

	beginInsertRows(QModelIndex(), p_row, p_row);
	m_wallets.insert(p_row, p_wallet);
	endInsertRows();
	qDebug() << "(i) [ManagedWallets] Wallet " << p_wallet->name() << " added.";
}


/**
 * @brief ManagedWallets::removeRow
 * @param p_row
 * @return
 */
Wallet* ManagedWallets::removeRow(int p_row) {
	if (p_row < 0 || p_row >= rowCount())
		return nullptr;

	beginRemoveRows(QModelIndex(), p_row, p_row);
	Wallet* wallet = m_wallets.takeAt(p_row);
	endRemoveRows();
	qDebug() << "(i) [ManagedWallets] Wallet " << wallet->name() << " removed from the managed wallets.";
	return wallet;
}


/**
 * @brief ManagedWallets::roleNames
 * @return
 */
QHash<int, QByteArray> ManagedWallets::roleNames() const {
	QHash<int, QByteArray> names;
	names[NameRole]        = "name";
	names[TagColorRole]    = "color";
	names[AccountListRole] = "accounts";
	return names;
}
