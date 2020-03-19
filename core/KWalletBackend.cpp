#include "KWalletBackend.h"
#include "Folder.h"
#include <QDebug>
#include <QGuiApplication>
#include <QWindow>

// CONSTRUCTORS
/**
 * @brief KWalletBackend::KWalletBackend
 * @param p_walletName
 * @param p_parent
 */
KWalletBackend::KWalletBackend(const QString& p_walletName, QObject* p_parent) :
    Backend(p_parent),
    m_walletName(p_walletName),
    m_kwallet(nullptr) {
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
void KWalletBackend::load() {
	if (!KWallet::Wallet::isEnabled()) {
		qDebug() << "/!\\ [KWalletBackend] KWallet subsystem is disabled!";
		emit openFailed();
	}

	// Open our wallet
	m_kwallet.reset(KWallet::Wallet::openWallet(m_walletName, qGuiApp->topLevelWindows().first()->winId(), KWallet::Wallet::Asynchronous));
	connect(m_kwallet.get(), &KWallet::Wallet::walletOpened, this, &KWalletBackend::loadWalletContent);
}


void KWalletBackend::loadWalletContent(bool p_openedSuccessfully) {
	if (!p_openedSuccessfully) {
		qDebug() << "/!\\ [KWalletBackend] Wallet " << m_walletName <<  " could not be opened!";
		emit openFailed();
		return;
	}

	qDebug() << "(i) [KWalletBackend] Wallet " << m_walletName << " is now opened.";
	emit opened();

	// Remove the default folders
	if (m_kwallet->hasFolder(KWallet::Wallet::FormDataFolder())) {
		m_kwallet->removeFolder(KWallet::Wallet::FormDataFolder());
		qDebug() << "(i) [KWalletBackend] Removed default folder " << qPrintable(KWallet::Wallet::FormDataFolder()) << " from wallet " << m_walletName << ".";
	}
	if (m_kwallet->hasFolder(KWallet::Wallet::PasswordFolder())) {
		m_kwallet->removeFolder(KWallet::Wallet::PasswordFolder());
		qDebug() << "(i) [KWalletBackend] Removed default folder " << qPrintable(KWallet::Wallet::PasswordFolder()) << " from wallet " << m_walletName << ".";
	}

	// Retrieve the folders
	qDebug() << "(i) [KWalletBackend] Listing existing folders:";
	auto backendFolders = m_kwallet->folderList();
	foreach (QString backendFolder, backendFolders) {
		qDebug() << "(i) [KWalletBackend] Folder " << backendFolder << " found.";
		m_kwallet->setFolder(backendFolder);

		// Create our model object
		auto folder = new Folder();
		folder->setName(backendFolder);

		// Retrieve the tag color
		if (m_kwallet->hasEntry("tagColor")) {
			QByteArray colorData;
			m_kwallet->readEntry("tagColor", colorData);
			folder->setTagColor(colorData);
			qDebug() << "(i) [KWalletBackend]   has tag color " << colorData << ".";
		}
		else
			qDebug() << "/!\\ [KWalletBackend]   !! has no tag color entry!";

		// Load the accounts
		qDebug() << "(i) [KWalletBackend] Loading accounts of folder " << backendFolder << "...";
		QMap<QString, QMap<QString, QString>> accounts;
		m_kwallet->readMapList("*", accounts);
		qDebug() << "(i) [KWalletBackend] " << accounts.count() << " accounts found:";
		QMapIterator<QString, QMap<QString, QString>> accountIter(accounts);
		while (accountIter.hasNext()) {
			accountIter.next();

			auto accountName = accountIter.key();
			auto login   = accountIter.value().value(LOGIN_KEY);
			auto website = accountIter.value().value(WEBSITE_KEY);
			auto notes   = accountIter.value().value(NOTES_KEY);

			folder->addAccount(new Account(accountName, login, website, notes));
			qDebug() << "(i) [KWalletBackend]   Account " << accountName << " with login " << login << " loaded.";
		}

		// Signal the new folder
		emit folderLoaded(folder);
	}
	
	emit loaded();
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
		qDebug() << "/!\\ [KWalletBackend] Cannot create folder " << p_folder.name() << " because on already exist.";
		return;
	}

	if (!m_kwallet->createFolder(p_folder.name())) {
		qDebug() << "/!\\ [KWalletBackend] Failed to create folder " << p_folder.name() << ".";
		return;
	}
	qDebug() << "(i) [KWalletBackend] Folder " << p_folder.name() << " created.";

	m_kwallet->setFolder(p_folder.name());
	QByteArray value(p_folder.tagColor().toUtf8());
	m_kwallet->writeEntry("tagColor", value, KWallet::Wallet::Stream);
	qDebug() << "(i) [KWalletBackend] Tag color " << p_folder.tagColor() << " stored for folder " << p_folder.name() << ".";
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
	if (!m_kwallet->setFolder(p_folder)) {
		qDebug() << "/!\\ [KWalletBackend] Folder " << p_folder << " does not exist, cannot create account " << p_account.name() << " in it.";
		return;
	}

	if (m_kwallet->hasEntry(p_account.name())) {
		qDebug() << "/!\\ [KWalletBackend] Cannot create account " << p_account.name() << " in folder " << p_folder << " because one already exist.";
		return;
	}

	// Write the password
	QString currentPwdId = p_account.name() + "-0001";
	if (m_kwallet->hasEntry(currentPwdId)) {
		m_kwallet->removeEntry(currentPwdId);
		qDebug() << "(i) [KWalletBackend] Removed the orphaned password " << currentPwdId << " in folder " << p_folder << ".";
	}
	m_kwallet->writePassword(currentPwdId, p_password);

	// Write the account
	QMap<QString, QString> accountData;
	accountData[LOGIN_KEY]    = p_account.login();
	accountData[PASSWORD_KEY] = currentPwdId;
	accountData[WEBSITE_KEY]  = p_account.website();
	accountData[NOTES_KEY]    = p_account.notes();
	m_kwallet->writeMap(p_account.name(), accountData);
	qDebug() << "(i) [KWalletBackend] Account " << p_account.name() << " created in folder " << p_folder << ".";
}


/**
 * @brief KWalletBackend::removeAccount
 * @param folder
 * @param name
 */
void KWalletBackend::removeAccount(const QString& p_folder, const QString& p_name) const {
	if (!hasAccount(p_folder, p_name)) {
		qDebug() << "/!\\ [KWalletBackend] Cannot remove account " << p_name << " from folder " << p_folder << " because it does not exist.";
	}

	// Retrieve all entries (account data & password history)
	QMap<QString, QByteArray> data;
	m_kwallet->readEntryList(p_name + "*", data);

	// Remove all entries
	QMapIterator<QString, QByteArray> dataIter(data);
	while (dataIter.hasNext()) {
		dataIter.next();

		if (m_kwallet->removeEntry(dataIter.key()) == 0)
			qDebug() << "(i) [KWalletBackend] Removed entry " << dataIter.key() << " from folder " << p_folder << ".";
		else
			qDebug() << "/!\\ [KWalletBackend] Failed to remove entry " << dataIter.key() << " from folder " << p_folder << ".";
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
		qDebug() << "/!\\ [KWalletBackend] No folder named " << p_folder << "!";
		return QString();
	}

	// Retrieve the account data
	QMap<QString, QString> accountData;
	if (m_kwallet->readMap(p_account, accountData) != 0) {
		qDebug() << "/!\\ [KWalletBackend] No account named " << p_account << " in folder " << p_folder << "!";
		return QString();
	}

	// Get the current password identifier
	const QString& currentPwdId = accountData.value(PASSWORD_KEY);
	if (currentPwdId.isEmpty()) {
		qDebug() << "/!\\ [KWalletBackend] Account " << p_account << " has no current password identifier!";
		return QString();
	}

	// Get the current password
	QString password;
	if (m_kwallet->readPassword(currentPwdId, password) != 0) {
		qDebug() << "/!\\ [KWalletBackend] No password with id " << currentPwdId << "!";
		return QString();
	}

	return password;
}


/**
 * @brief KWalletBackend::retrievePasswordHistory
 * @param p_folder
 * @param p_account
 * @return 
 */
const QMap<QString, QString> KWalletBackend::retrievePasswordHistory(const QString& p_folder, const QString& p_account) const {
	// Set the current folder
	if (!m_kwallet->setFolder(p_folder)) {
		qDebug() << "/i\\ [KWalletBackend] No folder named " << p_folder << "!";
		return QMap<QString,QString>();
	}

	// Retrieve the account data
	QMap<QString, QString> accountData;
	if (m_kwallet->readMap(p_account, accountData) != 0) {
		qDebug() << "/i\\ [KWalletBackend] No account named " << p_account << " in folder " << p_folder << "!";
		return QMap<QString,QString>();
	}

	// Get the current password identifier
	const QString& currentPwdId = accountData.value(PASSWORD_KEY);
	if (currentPwdId.isEmpty()) {
		qDebug() << "/!\\ [KWalletBackend] Account " << p_account << " has no current password identifier!";
		return QMap<QString,QString>();
	}

	// Retrieve all password entries whose name begin with "<p_account>-"
	QMap<QString, QString> history;
	if (m_kwallet->readPasswordList(p_account+"-*", history) != 0) {
		qDebug() << "/!\\ [KWalletBackend] Account " << p_account << " has no passwords!";
	}
	return history;
}


/**
 * @brief KWalletBackend::renewPassword
 * @param p_folder
 * @param p_account
 * @param p_password
 */
bool KWalletBackend::renewPassword(const QString& p_folder, const QString& p_account, const QString& p_password) const {
	// Set the current folder
	if (!m_kwallet->setFolder(p_folder)) {
		qDebug() << "/!\\ [KWalletBackend] No folder named " << p_folder << "!";
		return false;
	}

	// Retrieve the account data
	QMap<QString, QString> accountData;
	if (m_kwallet->readMap(p_account, accountData) != 0) {
		qDebug() << "/!\\ [KWalletBackend] No account named " << p_account << " in folder " << p_folder << "!";
		return false;
	}

	// Retrieve all the password identifiers
	QMap<QString, QString> passwordsList;
	if (m_kwallet->readPasswordList(p_account + "*", passwordsList) != 0) {
		qDebug() << "/!\\ [KWalletBackend] Could not retrieve existing passwords for account " << p_account << " in folder " << p_folder << "!";
		return false;
	}

	// Extract the latest password identifier to build the name of the new one
	uint maxId = 0;
	QMapIterator<QString, QString> passwordIter(passwordsList);
	while (passwordIter.hasNext()) {
		passwordIter.next();

		// Extract the numerical identifier from the 4 last characters of the name
		QString passwordId = passwordIter.key();
		bool ok;
		uint currentId = passwordId.rightRef(4).toUInt(&ok, 10);
		if (!ok) {
			qDebug() << "/!\\ [KWalletBackend] Skipping malformed password id " << passwordId << " because the numerical id is not an unsigned int.";
			continue;
		}

		// Set the new maximum identifier
		if (currentId > maxId)
			maxId = currentId;
	}

	// And the new password id is...
	maxId++;

	// Overflow case : restart at '0000'
	if (maxId > 9999)
		maxId = 0;

	QString currentPwdId = p_account + "-" + QString::number(maxId, 10).rightJustified(4, '0');
	if (m_kwallet->hasEntry(currentPwdId)) {
		m_kwallet->removeEntry(currentPwdId);
		qDebug() << "(i) [KWalletBackend] Removed the old password " << currentPwdId << " in folder " << p_folder << ".";
	}
	m_kwallet->writePassword(currentPwdId, p_password);

	// Update the account
	accountData[PASSWORD_KEY] = currentPwdId;
	m_kwallet->writeMap(p_account, accountData);

	return true;
}
