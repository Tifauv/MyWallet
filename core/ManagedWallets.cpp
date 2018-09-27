#include "ManagedWallets.h"
#include <QGuiApplication>
#include <QtDebug>

// CONSTRUCTORS
/**
 * @brief ManagedWallets::ManagedWallets
 * @param parent
 */
ManagedWallets::ManagedWallets(QObject* p_parent) :
    QAbstractListModel(p_parent),
    m_backend(KWallet::Wallet::openWallet(QGuiApplication::applicationName(), 0)) {
	qDebug() << "(i) [ManagedWallets] Created.";
	if (!KWallet::Wallet::isEnabled()) {
		qDebug() << "/!\\ [ManagedWallets] KWallet subsystem is disabled!";
		return;
	}

	// Open our wallet
	if (m_backend == nullptr) {
		qDebug() << "/!\\ [ManagedWallets] Wallet '" << qPrintable(QGuiApplication::applicationName()) <<  "' could not be opened!";
		return;
	}
	qDebug() << "(i) [ManagedWallets] Our wallet '" << qPrintable(QGuiApplication::applicationName()) << "' is now opened.";

	// Remove the default folders
	if (m_backend->hasFolder(KWallet::Wallet::FormDataFolder())) {
		m_backend->removeFolder(KWallet::Wallet::FormDataFolder());
		qDebug() << "(i) [ManagedWallets] Removed default folder '" << qPrintable(KWallet::Wallet::FormDataFolder()) << "' from our wallet.";
	}
	if (m_backend->hasFolder(KWallet::Wallet::PasswordFolder())) {
		m_backend->removeFolder(KWallet::Wallet::PasswordFolder());
		qDebug() << "(i) [ManagedWallets] Removed default folder '" << qPrintable(KWallet::Wallet::PasswordFolder()) << "' from our wallet.";
	}

	// Retrieve the folders
	qDebug() << "(i) [ManagedWallets] Listing existing folders:";
	auto folders = m_backend->folderList();
	foreach (QString folder, folders) {
		qDebug() << "(i) [ManagedWallets] Folder '" << qPrintable(folder) << "' found.";
		m_backend->setFolder(folder);

		// Create our model object
		auto wallet = new Wallet();
		wallet->setName(folder);

		// Retrieve the tag color
		if (m_backend->hasEntry("tagColor")) {
			QByteArray colorData;
			m_backend->readEntry("tagColor", colorData);
			wallet->setTagColor(colorData);
			qDebug() << "(i) [ManagedWallets]   has tag color '" << qPrintable(colorData) << "'.";
		}
		else {
			qDebug() << "/!\\ [ManagedWallets]   !! has no tag color entry!";

			/*QByteArray colorData;
			if (folder == "AIFE")
				colorData = "#2176c7";
			else if (folder == "CA-TS")
				colorData = "#738a05";
			else if (folder == "CNRS")
				colorData = "#259286";
			else if (folder == "SAIL")
				colorData = "#c61c6f";
			m_backend->writeEntry("tagColor", colorData, KWallet::Wallet::Stream);
			wallet->setTagColor(colorData);
			qDebug() << "(i) [ManagedWallets]   has tag color '" << qPrintable(colorData) << "'.";*/
		}

		// Load the accounts
		qDebug() << "(i) [ManagedWallets] Loading accounts of wallet '" << qPrintable(folder) << "'...";
		QMap<QString, QMap<QString, QString>> accounts;
		m_backend->readMapList("*", accounts);
		qDebug() << "(i) [ManagedWallets] " << accounts.count() << " accounts found:";
		QMapIterator<QString, QMap<QString, QString>> accountIter(accounts);
		while (accountIter.hasNext()) {
			accountIter.next();

			auto accountName = accountIter.key();
			qDebug() << "(i) [ManagedWallets]   Account name '" << accountName << "'";
			auto login = accountIter.value().value("login");
			qDebug() << "(i) [ManagedWallets]   Account login '" << login << "'";

			wallet->addAccount(accountName, login);
			qDebug() << "(i) [ManagedWallets]   Account '" << accountName << "' with login '" << login << "' added.";
		}

		// Add the wallet to the model
		addWallet(wallet);
	}

	// Add the trash wallet for deleted accounts
	auto trashWallet = new Wallet();
	addWallet(trashWallet->setName(tr("Deleted"))->setTagColor("transparent"));
}


// DESTRUCTORS
/**
 * @brief ManagedWallets::~ManagedWallets
 */
ManagedWallets::~ManagedWallets() {
	if (m_backend)
		m_backend->lockWallet();
}

// GETTERS
/**
 * @brief ManagedWallets::count
 * @return
 */
int ManagedWallets::count() const {
	return rowCount();
}


// NATIVE API
/**
 * @brief ManagedWallets::addWallet
 * @param p_wallet
 */
void ManagedWallets::addWallet(Wallet* p_wallet) {
	insertRow(rowCount(), p_wallet);
}


/**
 * @brief ManagedWallets::get
 * @param p_row
 * @return
 */
Wallet* ManagedWallets::get(int p_row) const {
	if (p_row < 0 || p_row >= rowCount())
		return nullptr;

	return m_wallets.at(p_row);
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
		qDebug() << "(i) [ManagedWallets]   wallet name is " << wallet->name();
		return wallet->name();
	case TagColorRole:
		qDebug() << "(i) [ManagedWallets]   wallet color is " << wallet->tagColor();
		return wallet->tagColor();
	case AccountListRole:
		qDebug() << "(i) [ManagedWallets]   wallet accounts has " << wallet->rowCount() << " accounts";
		return QVariant::fromValue(wallet);
	default:
		qDebug() << "/i\\ [ManagedWallets]   unknown role";
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
	emit countChanged(rowCount());
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
	emit countChanged(rowCount());
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
