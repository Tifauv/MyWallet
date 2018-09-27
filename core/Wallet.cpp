#include "Wallet.h"
#include <QGuiApplication>
#include <QtDebug>

// CONSTRUCTORS
/**
 * @brief Wallet::Wallet
 * @param parent
 */
Wallet::Wallet(QObject* p_parent) :
    QAbstractListModel(p_parent),
    m_backend(KWallet::Wallet::openWallet(QGuiApplication::applicationName(), 0)) {
	qDebug() << "(i) [Wallet] Created.";
	if (!KWallet::Wallet::isEnabled()) {
		qDebug() << "/!\\ [Wallet] KWallet subsystem is disabled!";
		return;
	}

	// Open our wallet
	if (m_backend == nullptr) {
		qDebug() << "/!\\ [Wallet] Wallet '" << qPrintable(QGuiApplication::applicationName()) <<  "' could not be opened!";
		return;
	}
	qDebug() << "(i) [Wallet] Our wallet '" << qPrintable(QGuiApplication::applicationName()) << "' is now opened.";

	// Remove the default folders
	if (m_backend->hasFolder(KWallet::Wallet::FormDataFolder())) {
		m_backend->removeFolder(KWallet::Wallet::FormDataFolder());
		qDebug() << "(i) [Wallet] Removed default folder '" << qPrintable(KWallet::Wallet::FormDataFolder()) << "' from our wallet.";
	}
	if (m_backend->hasFolder(KWallet::Wallet::PasswordFolder())) {
		m_backend->removeFolder(KWallet::Wallet::PasswordFolder());
		qDebug() << "(i) [Wallet] Removed default folder '" << qPrintable(KWallet::Wallet::PasswordFolder()) << "' from our wallet.";
	}

	// Retrieve the folders
	qDebug() << "(i) [Wallet] Listing existing folders:";
	auto backendFolders = m_backend->folderList();
	foreach (QString backendFolder, backendFolders) {
		qDebug() << "(i) [Wallet] Folder '" << qPrintable(backendFolder) << "' found.";
		m_backend->setFolder(backendFolder);

		// Create our model object
		auto folder = new Folder();
		folder->setName(backendFolder);

		// Retrieve the tag color
		if (m_backend->hasEntry("tagColor")) {
			QByteArray colorData;
			m_backend->readEntry("tagColor", colorData);
			folder->setTagColor(colorData);
			qDebug() << "(i) [Wallet]   has tag color '" << qPrintable(colorData) << "'.";
		}
		else
			qDebug() << "/!\\ [Wallet]   !! has no tag color entry!";

		// Load the accounts
		qDebug() << "(i) [Wallet] Loading accounts of folder '" << qPrintable(backendFolder) << "'...";
		QMap<QString, QMap<QString, QString>> accounts;
		m_backend->readMapList("*", accounts);
		qDebug() << "(i) [Wallet] " << accounts.count() << " accounts found:";
		QMapIterator<QString, QMap<QString, QString>> accountIter(accounts);
		while (accountIter.hasNext()) {
			accountIter.next();

			auto accountName = accountIter.key();
			qDebug() << "(i) [Wallet]   Account name '" << accountName << "'";
			auto login = accountIter.value().value("login");
			qDebug() << "(i) [Wallet]   Account login '" << login << "'";

			folder->addAccount(accountName, login);
			qDebug() << "(i) [Wallet]   Account '" << accountName << "' with login '" << login << "' added.";
		}

		// Add the wallet to the model
		addFolder(folder);
	}

	// Add the trash wallet for deleted accounts
	auto trashWallet = new Folder();
	addFolder(trashWallet->setName(tr("Deleted"))->setTagColor("transparent"));
}


// DESTRUCTORS
/**
 * @brief Wallet::~Wallet
 */
Wallet::~Wallet() {
	if (m_backend)
		m_backend->lockWallet();
}

// GETTERS
/**
 * @brief Wallet::count
 * @return
 */
int Wallet::count() const {
	return rowCount();
}


// NATIVE API
/**
 * @brief Wallet::addFolder
 * @param p_folder
 */
void Wallet::addFolder(Folder* p_folder) {
	insertRow(rowCount(), p_folder);
}


/**
 * @brief Wallet::get
 * @param p_row
 * @return
 */
Folder* Wallet::get(int p_row) const {
	if (p_row < 0 || p_row >= rowCount())
		return nullptr;

	return m_folders.at(p_row);
}


// MODEL/VIEW API
/**
 * @brief Wallet::rowCount
 * @param p_parent
 * @return
 */
int Wallet::rowCount(const QModelIndex& p_parent) const {
	Q_UNUSED(p_parent);
	return m_folders.count();
}


/**
 * @brief Wallet::data
 * @param p_index
 * @param p_role
 * @return
 */
QVariant Wallet::data(const QModelIndex& p_index, int p_role) const {
	if (p_index.row() < 0 || p_index.row() >= rowCount())
		return QVariant();

	qDebug() << "(i) [Wallet] Looking for folder at row " << p_index.row() << " with role " << p_role;
	auto folder = m_folders.at(p_index.row());
	switch (p_role) {
	case NameRole:
		qDebug() << "(i) [Wallet]   folder name is " << folder->name();
		return folder->name();
	case TagColorRole:
		qDebug() << "(i) [Wallet]   folder color is " << folder->tagColor();
		return folder->tagColor();
	case AccountListRole:
		qDebug() << "(i) [Wallet]   folder has " << folder->rowCount() << " accounts";
		return QVariant::fromValue(folder);
	default:
		qDebug() << "/i\\ [Wallet]   unknown role";
		return QVariant();
	}
}


/**
 * @brief Wallet::insertRow
 * @param p_row
 * @param p_folder
 * @return
 */
bool Wallet::insertRow(int p_row, Folder* p_folder) {
	Q_ASSERT(p_folder);

	beginInsertRows(QModelIndex(), p_row, p_row);
	m_folders.insert(p_row, p_folder);
	endInsertRows();
	emit countChanged(rowCount());
	qDebug() << "(i) [Wallet] Folder " << p_folder->name() << " added.";
}


/**
 * @brief Wallet::removeRow
 * @param p_row
 * @return
 */
Folder* Wallet::removeRow(int p_row) {
	if (p_row < 0 || p_row >= rowCount())
		return nullptr;

	beginRemoveRows(QModelIndex(), p_row, p_row);
	auto folder = m_folders.takeAt(p_row);
	endRemoveRows();
	emit countChanged(rowCount());
	qDebug() << "(i) [Wallet] Folder " << folder->name() << " removed.";
	return folder;
}


/**
 * @brief Wallet::roleNames
 * @return
 */
QHash<int, QByteArray> Wallet::roleNames() const {
	QHash<int, QByteArray> names;
	names[NameRole]        = "name";
	names[TagColorRole]    = "color";
	names[AccountListRole] = "accounts";
	return names;
}
