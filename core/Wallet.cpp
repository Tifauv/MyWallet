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
    QAbstractListModel(p_parent),
    m_trash(new Trash()),
    m_backend(new KWalletBackend(QGuiApplication::applicationName())) {
	qDebug() << "(i) [Wallet] Created.";
	if (m_backend) {
		connect(m_backend.data(), &Backend::folderLoaded, this, &Wallet::addFolder);
		m_backend->load();
	}
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
 * @brief Wallet::createFolder
 * @param p_name
 * @param p_tagColor
 */
Folder* Wallet::createFolder(const QString& p_name, const QString& p_tagColor) {
	// The folder already exist
	if (m_backend->hasFolder(p_name))
		return nullptr;

	auto folder = new Folder();
	folder->setName(p_name)->setTagColor(p_tagColor);
	m_backend->createFolder(*folder);
	appendRow(folder);
	return folder;
}


/**
 * @brief Wallet::removeFolder
 * @param p_row
 */
void Wallet::removeFolder(int p_row) {
	removeRow(p_row);
}


/**
 * @brief Wallet::get
 * @param p_row
 * @return
 */
Folder* Wallet::get(int p_row) const {
	if (p_row < 0 || p_row >= rowCount())
		return nullptr;

	if (p_row == m_folders.count())
		return m_trash;
	return m_folders.at(p_row);
}


// PRIVATE BACKEND API
/**
 * @brief Wallet::addFolder
 * @param p_folder
 */
void Wallet::addFolder(Folder* p_folder) {
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
	return m_folders.count() + 1; // +1 for the trash
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

	Folder* folder;
	if (p_index.row() == m_folders.count()) {
		qDebug() << "(i) [Wallet] Looking for trash folder with role " << p_role;
		folder = m_trash;
	}
	else {
		qDebug() << "(i) [Wallet] Looking for folder at row " << p_index.row() << " with role " << p_role;
		folder = m_folders.at(p_index.row());
	}

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
 * @brief Wallet::appendRow
 * @param p_folder
 * @return
 */
bool Wallet::appendRow(Folder* p_folder) {
	insertRow(rowCount()-1, p_folder);
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
	// Upper bound check prevents removing the trash item
	if (p_row < 0 || p_row >= m_folders.count())
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
