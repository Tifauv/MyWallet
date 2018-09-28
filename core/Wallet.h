#ifndef Wallet_H
#define Wallet_H

#include <QAbstractListModel>
#include <QScopedPointer>
#include "Backend.h"
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
	~Wallet() {}

	int count() const;

	int rowCount(const QModelIndex &parent = QModelIndex()) const override;
	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

signals:
	void countChanged(int);

public slots:
	Folder* createFolder(const QString& name, const QString& tagColor);
	Folder* get(int row) const;

	bool insertRow(int row, Folder* wallet);
	Folder* removeRow(int row);

protected:
	QHash<int, QByteArray> roleNames() const override;

protected slots:
	void addFolder(Folder* wallet);

private:
	QList<Folder*> m_folders;
	Trash*         m_trash;
	QScopedPointer<Backend> m_backend;
};

#endif
