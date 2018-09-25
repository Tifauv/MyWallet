#ifndef ManagedWallets_H
#define ManagedWallets_H

#include <QAbstractListModel>
#include "Wallet.h"

class ManagedWallets : public QAbstractListModel {
	Q_OBJECT

public:
	enum Roles {
		NameRole = Qt::UserRole + 1,
		TagColorRole,
		AccountListRole
	};

	explicit ManagedWallets(QObject* parent = nullptr);
	~ManagedWallets() {}

	// Basic functionality:
	int rowCount(const QModelIndex &parent = QModelIndex()) const override;

	// Fetch data dynamically:
	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

	// Add and remove data:
	bool insertRow(int row, Wallet* wallet);
	Wallet* removeRow(int row);

protected:
	QHash<int, QByteArray> roleNames() const override;

private:
	QList<Wallet*> m_wallets;
};

#endif
