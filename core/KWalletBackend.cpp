#include "KWalletBackend.h"
#include "Folder.h"
#include <QDebug>

// CONSTRUCTORS
/**
 * @brief KWalletBackend::KWalletBackend
 * @param p_walletName
 * @param p_parent
 */
KWalletBackend::KWalletBackend(const QString& p_walletName, QObject* p_parent) :
    Backend(p_parent),
    m_walletName(p_walletName),
    m_kwallet(KWallet::Wallet::openWallet(p_walletName, 0)) {
	qDebug() << "(i) [KWalletBackend] Created.";
}


// DESTRUCTORS
/**
 * @brief KWalletBackend::~KWalletBackend
 */
KWalletBackend::~KWalletBackend() {
	if (m_kwallet)
		m_kwallet->lockWallet();
}


// INITIAL LOADING
/**
 * @brief KWalletBackend::load
 * @return
 */
int KWalletBackend::load() const {
	if (!KWallet::Wallet::isEnabled()) {
		qDebug() << "/!\\ [KWalletBackend] KWallet subsystem is disabled!";
		return 1;
	}

	// Open our wallet
	if (m_kwallet == nullptr) {
		qDebug() << "/!\\ [KWalletBackend] Wallet '" << m_walletName <<  "' could not be opened!";
		return 2;
	}
	qDebug() << "(i) [KWalletBackend] Wallet '" << m_walletName << "' is now opened.";

	// Remove the default folders
	if (m_kwallet->hasFolder(KWallet::Wallet::FormDataFolder())) {
		m_kwallet->removeFolder(KWallet::Wallet::FormDataFolder());
		qDebug() << "(i) [KWalletBackend] Removed default folder '" << qPrintable(KWallet::Wallet::FormDataFolder()) << "' from wallet '" << m_walletName << "'.";
	}
	if (m_kwallet->hasFolder(KWallet::Wallet::PasswordFolder())) {
		m_kwallet->removeFolder(KWallet::Wallet::PasswordFolder());
		qDebug() << "(i) [KWalletBackend] Removed default folder '" << qPrintable(KWallet::Wallet::PasswordFolder()) << "' from wallet '" << m_walletName << "'.";
	}

	// Retrieve the folders
	qDebug() << "(i) [KWalletBackend] Listing existing folders:";
	auto backendFolders = m_kwallet->folderList();
	foreach (QString backendFolder, backendFolders) {
		qDebug() << "(i) [KWalletBackend] Folder '" << backendFolder << "' found.";
		m_kwallet->setFolder(backendFolder);

		// Create our model object
		auto folder = new Folder();
		folder->setName(backendFolder);

		// Retrieve the tag color
		if (m_kwallet->hasEntry("tagColor")) {
			QByteArray colorData;
			m_kwallet->readEntry("tagColor", colorData);
			folder->setTagColor(colorData);
			qDebug() << "(i) [KWalletBackend]   has tag color '" << colorData << "'.";
		}
		else
			qDebug() << "/!\\ [KWalletBackend]   !! has no tag color entry!";

		// Load the accounts
		qDebug() << "(i) [KWalletBackend] Loading accounts of folder '" << backendFolder << "'...";
		QMap<QString, QMap<QString, QString>> accounts;
		m_kwallet->readMapList("*", accounts);
		qDebug() << "(i) [KWalletBackend] " << accounts.count() << " accounts found:";
		QMapIterator<QString, QMap<QString, QString>> accountIter(accounts);
		while (accountIter.hasNext()) {
			accountIter.next();

			auto accountName = accountIter.key();
			auto login = accountIter.value().value("login");

			folder->addAccount(new Account(accountName, login));
			qDebug() << "(i) [KWalletBackend]   Account '" << accountName << "' with login '" << login << "' added.";
		}

		// Signal the new folder
		emit folderLoaded(folder);
	}
	return 0;
}


// FOLDER MANAGEMENT
/**
 * @brief KWalletBackend::hasFolder
 * @param p_name
 */
bool KWalletBackend::hasFolder(const QString& p_name) const {
	return m_kwallet->hasFolder(p_name);
}


/**
 * @brief KWalletBackend::createFolder
 * @param p_folder
 */
void KWalletBackend::createFolder(const Folder& p_folder) const {
	if (hasFolder(p_folder.name())) {
		qDebug() << "/!\\ [KWalletBackend] Cannot create folder '" << p_folder.name() << "' because on already exist.";
		return;
	}

	if (!m_kwallet->createFolder(p_folder.name())) {
		qDebug() << "/!\\ [KWalletBackend] Failed to create folder '" << p_folder.name() << "'.";
		return;
	}
	qDebug() << "(i) [KWalletBackend] Folder '" << p_folder.name() << "' created.";

	m_kwallet->setFolder(p_folder.name());
	QByteArray value(p_folder.tagColor().toUtf8());
	m_kwallet->writeEntry("tagColor", value, KWallet::Wallet::Stream);
	qDebug() << "(i) [KWalletBackend] Tag color '" << p_folder.tagColor() << "' stored for folder '" << p_folder.name() << "'.";
}


/**
 * @brief KWalletBackend::removeFolder
 * @param p_name
 */
void KWalletBackend::removeFolder(const QString& p_name) const {
	if (!hasFolder(p_name)) {
		qDebug() << "/!\\ [KWalletBackend] Cannot remove folder '" << p_name << "' because it does not exist.";
		return;
	}

	if (!m_kwallet->removeFolder(p_name))
		qDebug() << "/!\\ [KWalletBackend] Failed to remove folder '" << p_name << "'.";
	else
		qDebug() << "(i) [KWalletBackend] Folder '" << p_name << "' removed.";
}


// ACCOUNT MANAGEMENT
/**
 * @brief KWalletBackend::hasAccount
 * @param p_folder
 * @param p_name
 * @return
 */
bool KWalletBackend::hasAccount(const QString& p_folder, const QString& p_name) const {
	if (m_kwallet->setFolder(p_folder))
		return m_kwallet->hasEntry(p_name);

	return false;
}


/**
 * @brief KWalletBackend::createAccount
 * @param account
 */
void KWalletBackend::createAccount(const QString& p_folder, const Account& p_account, const QString& p_password) const {
	if (m_kwallet->setFolder(p_folder)) {
		if (m_kwallet->hasEntry(p_account.name())) {
			qDebug() << "/!\\ [KWalletBackend] Cannot create account '" << p_account.name() << "' in folder '" << p_folder << "' because one already exist.";
			return;
		}

		// Write the password
		QString currentPwdId = p_account.name() + "-0001";
		if (m_kwallet->hasEntry(currentPwdId)) {
			m_kwallet->removeEntry(currentPwdId);
			qDebug() << "(i) [KWalletBackend] Removed the orphaned password '" << currentPwdId << "' in folder '" << p_folder << "'.";
		}
		m_kwallet->writePassword(currentPwdId, p_password);

		// Write the account
		QMap<QString, QString> accountData;
		accountData["login"] = p_account.login();
		accountData["password"] = currentPwdId;
		m_kwallet->writeMap(p_account.name(), accountData);
		qDebug() << "(i) [KWalletBackend] Account '" << p_account.name() << "' created in folder '" << p_folder << "'.";
	}
	else
		qDebug() << "/!\\ [KWalletBackend] Folder '" << p_folder << "' does not exist, cannot create account '" << p_account.name() << "' in it.";
}


/**
 * @brief KWalletBackend::removeAccount
 * @param folder
 * @param name
 */
void KWalletBackend::removeAccount(const QString& p_folder, const QString& p_name) const {
	if (!hasAccount(p_folder, p_name)) {
		qDebug() << "/!\\ [KWalletBackend] Cannot remove account '" << p_name << "' from folder '" << p_folder << "' because it does not exist.";
	}

	// Retrieve all entries (account data & password history)
	QMap<QString, QByteArray> data;
	m_kwallet->readEntryList(p_name + "*", data);

	// Remove all entries
	QMapIterator<QString, QByteArray> dataIter(data);
	while (dataIter.hasNext()) {
		dataIter.next();

		if (m_kwallet->removeEntry(dataIter.key()) == 0)
			qDebug() << "(i) [KWalletBackend] Removed entry '" << dataIter.key() << "' from folder '" << p_folder << "'.";
		else
			qDebug() << "/!\\ [KWalletBackend] Failed to remove entry '" << dataIter.key() << "' from folder '" << p_folder << "'.";
	}
}


/**
 * @brief retrievePassword
 * @param p_folder
 * @param p_account
 * @return
 */
const QString KWalletBackend::retrievePassword(const QString& p_folder, const QString& p_account) const {
	// Set the current folder
	if (!m_kwallet->setFolder(p_folder)) {
		qDebug() << "/i\\ [Folder] No folder named '" << p_folder << "'!";
		return QString::null;
	}

	// Retrieve the account data
	QMap<QString, QString> accountData;
	if (m_kwallet->readMap(p_account, accountData) != 0) {
		qDebug() << "/i\\ [Folder] No account named '" << p_account << "' in folder '" << p_folder << "'!";
		return QString::null;
	}

	// Get the current password identifier
	const QString& currentPwdId = accountData.value("password");
	if (currentPwdId.isEmpty()) {
		qDebug() << "/!\\ [Folder] Account '" << p_account << "' has no current password identifier!";
		return QString::null;
	}

	// Get the current password
	QString password;
	if (m_kwallet->readPassword(currentPwdId, password) != 0) {
		qDebug() << "/!\\ [Folder] No password with id '" << currentPwdId << "'!";
		return QString::null;
	}

	return password;
}
