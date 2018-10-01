#ifndef Wallet_H
#define Wallet_H

#include <QAbstractListModel>
#include <QSharedPointer>
#include "Backend.h"
#include "Folder.h"

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
	~Wallet() {}

	int count() const;

	int rowCount(const QModelIndex &parent = QModelIndex()) const override;
	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

signals:
	void countChanged(int);

public slots:
	Folder* createFolder(const QString& name, const QString& tagColor);
	void removeFolder(int row);
	Folder* get(int row) const;

	bool appendRow(Folder* wallet);
	bool insertRow(int row, Folder* wallet);
	Folder* removeRow(int row);

protected:
	QHash<int, QByteArray> roleNames() const override;

protected slots:
	void addFolder(Folder* wallet);

private:
	QList<Folder*> m_folders;
	QSharedPointer<Backend> m_backend;
};

#endif
