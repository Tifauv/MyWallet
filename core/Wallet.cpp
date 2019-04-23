#include "Wallet.h"
#include "KWalletBackend.h"
#include <QGuiApplication>
#include <QtDebug>

// CONSTRUCTORS
/**
 * @brief Wallet::Wallet
 * @param parent
 */
Wallet::Wallet(QObject* p_parent) :
    QAbstractListModel(p_parent) {
	qDebug() << "(i) [Wallet] Created.";
	load("Wallets", new KWalletBackend("Wallets"));
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
 * @brief Wallet::count
 * @return
 */
int Wallet::count() const {
	return rowCount();
}


// NATIVE API
/**
 * @brief load
 * @param p_name
 * @param p_backend
 */
void Wallet::load(const QString& p_name, Backend* p_backend) {
	if (m_backend.data() != nullptr)
		disconnect(m_backend.data(), &Backend::folderLoaded, this, &Wallet::addFolder);

	// Change the backend
	m_backend.reset(p_backend);
	if (m_backend) {
		connect(m_backend.data(), &Backend::folderLoaded, this, &Wallet::addFolder);
		clear();
		m_backend->load();
	}

	// Change the name
	m_name = p_name;
	emit nameChanged(m_name);
}


/**
 * @brief Wallet::createFolder
 * @param p_name
 * @param p_tagColor
 */
Folder* Wallet::createFolder(const QString& p_name, const QString& p_tagColor) {
	// The folder already exist
	if (m_backend->hasFolder(p_name))
		return nullptr;

	auto folder = new Folder(this);
	folder->setName(p_name)->setTagColor(p_tagColor);
	m_backend->createFolder(*folder);
	addFolder(folder);
	return folder;
}


/**
 * @brief Wallet::deleteFolder
 * @param p_row
 */
void Wallet::deleteFolder(int p_row) {
	// Index range check
	if (p_row < 0 || p_row >= rowCount())
		return;

	auto folder = removeRow(p_row);
	if (m_backend->hasFolder(folder->name()))
		m_backend->removeFolder(folder->name());
	delete folder;
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


/**
 * @brief Wallet::find
 * @param p_folderName
 * @return
 */
int Wallet::find(const QString& p_folderName) const {
	for (int i=0; i < m_folders.size(); ++i)
		if (m_folders.at(i)->name() == p_folderName)
			return i;
	return -1;
}


// PRIVATE BACKEND API
/**
 * @brief Wallet::addFolder
 * @param p_folder
 */
void Wallet::addFolder(Folder* p_folder) {
	p_folder->setParent(this);
	p_folder->setBackend(m_backend);
	appendRow(p_folder);
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
	Folder* folder = m_folders.at(p_index.row());

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


/**
 * @brief Wallet::appendRow
 * @param p_folder
 * @return
 */
void Wallet::appendRow(Folder* p_folder) {
	insertRow(rowCount(), p_folder);
}


/**
 * @brief Wallet::insertRow
 * @param p_row
 * @param p_folder
 * @return
 */
void Wallet::insertRow(int p_row, Folder* p_folder) {
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
 * @brief Wallet::clear
 */
void Wallet::clear() {
	if (rowCount() > 0) {
		beginRemoveRows(QModelIndex(), 0, rowCount() - 1);
		while (rowCount() > 0)
			delete m_folders.takeAt(0);
		endRemoveRows();
		emit countChanged(rowCount());
		qDebug() << "(i) [Wallet] Folder list cleared.";
	}
}
