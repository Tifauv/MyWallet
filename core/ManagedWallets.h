#ifndef ManagedWallets_H
#define ManagedWallets_H

#include <QAbstractListModel>
#include "Wallet.h"

class ManagedWallets : public QAbstractListModel {
	Q_OBJECT

	Q_PROPERTY(int count  READ count  NOTIFY countChanged)

public:
	enum Roles {
		NameRole = Qt::UserRole + 1,
		TagColorRole,
		AccountListRole
	};

	explicit ManagedWallets(QObject* parent = nullptr);
	~ManagedWallets() {}

	int count() const;

	// Basic functionality:
	int rowCount(const QModelIndex &parent = QModelIndex()) const override;

	// Fetch data dynamically:
	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

signals:
	void countChanged(int);

public slots:
	void addWallet(Wallet* wallet);
	Wallet* get(int row) const;

	bool insertRow(int row, Wallet* wallet);
	Wallet* removeRow(int row);

protected:
	QHash<int, QByteArray> roleNames() const override;

private:
	QList<Wallet*> m_wallets;
};

#endif
