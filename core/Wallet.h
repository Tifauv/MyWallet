#ifndef Wallet_H
#define Wallet_H

#include <QAbstractListModel>
#include <QScopedPointer>
#include <KWallet/KWallet>
#include "Folder.h"
#include "Trash.h"

class Wallet : public QAbstractListModel {
	Q_OBJECT

	Q_PROPERTY(int count  READ count  NOTIFY countChanged)

public:
	enum Roles {
		NameRole = Qt::UserRole + 1,
		TagColorRole,
		AccountListRole
	};

	explicit Wallet(QObject* parent = nullptr);
	~Wallet();

	int count() const;

	int rowCount(const QModelIndex &parent = QModelIndex()) const override;
	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

signals:
	void countChanged(int);

public slots:
	void addFolder(Folder* wallet);
	Folder* get(int row) const;

	bool insertRow(int row, Folder* wallet);
	Folder* removeRow(int row);

protected:
	QHash<int, QByteArray> roleNames() const override;
	int loadBackend();

private:
	QList<Folder*> m_folders;
	Trash*         m_trash;
	QScopedPointer<KWallet::Wallet> m_backend;
};

#endif
