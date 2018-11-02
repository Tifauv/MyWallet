#ifndef Wallet_H
#define Wallet_H

#include <QAbstractListModel>
#include <QSharedPointer>
#include "Backend.h"
#include "Folder.h"

class Wallet : public QAbstractListModel {
	Q_OBJECT

	Q_PROPERTY(QString name   READ name   NOTIFY nameChanged )
	Q_PROPERTY(int     count  READ count  NOTIFY countChanged)

public:
	enum Roles {
		NameRole = Qt::UserRole + 1,
		TagColorRole,
		AccountListRole
	};

	explicit Wallet(QObject* parent = nullptr);
	~Wallet() {}

	const QString& name() const;
	int count() const;

	int rowCount(const QModelIndex &parent = QModelIndex()) const override;
	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

signals:
	void nameChanged(const QString&);
	void countChanged(int);

public slots:
	void load(const QString& name, Backend* backend);
	Folder* createFolder(const QString& name, const QString& tagColor);
	void deleteFolder(int row);
	Folder* get(int row) const;
	int find(const QString& folderName) const;

protected:
	QHash<int, QByteArray> roleNames() const override;
	void appendRow(Folder* wallet);
	void insertRow(int row, Folder* wallet);
	Folder* removeRow(int row);
	void clear();

protected slots:
	void addFolder(Folder* wallet);

private:
	QString        m_name;
	QList<Folder*> m_folders;
	QSharedPointer<Backend> m_backend;
};

#endif
