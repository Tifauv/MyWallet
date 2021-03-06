/*
 *  SPDX-FileCopyrightText: 2018 Olivier Serve <tifauv@gmail.com>
 *
 *  SPDX-License-Identifier: LGPL-2.0-or-later
 */

#ifndef Wallet_H
#define Wallet_H

#include <QAbstractListModel>
#include <QSharedPointer>
#include "Backend.h"
#include "Folder.h"

class Wallet : public QAbstractListModel {
	Q_OBJECT

	Q_PROPERTY(QString name   READ name   WRITE loadKWallet  NOTIFY nameChanged )
	Q_PROPERTY(int     count  READ count                     NOTIFY countChanged)

public:
	enum Roles {
		NameRole = Qt::UserRole + 1,
		TagColorRole,
		AccountListRole
	};

	explicit Wallet(QObject* parent = nullptr);
	~Wallet() override {}

	const QString& name() const;
	int count() const;

	int rowCount(const QModelIndex &parent = QModelIndex()) const override;
	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

signals:
	void opened();
	void openFailed();
	void loaded();
	void nameChanged(const QString&);
	void countChanged(int);

public slots:
	void load(const QString& name, Backend* backend);
	void loadKWallet(const QString& p_name);
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
	QString                 m_name;
	QVector<Folder*>        m_folders;
	QSharedPointer<Backend> m_backend;
};

#endif
