#ifndef Wallet_H
#define Wallet_H

#include <QObject>
#include <QMetaType>
#include <QAbstractListModel>
#include "Account.h"

class Wallet : public QAbstractListModel {
	Q_OBJECT

	Q_PROPERTY(QString name      READ name      WRITE setName      NOTIFY nameChanged      DESIGNABLE false)
	Q_PROPERTY(QString tagColor  READ tagColor  WRITE setTagColor  NOTIFY tagColorChanged                  )
	Q_PROPERTY(int     count     READ count                        NOTIFY countChanged                     )

public:
	enum Roles {
		NameRole = Qt::UserRole + 1,
		LoginRole,
		PasswordRole
	};

	explicit Wallet(QObject* parent = nullptr);
	explicit Wallet(const Wallet&);
	~Wallet() {}

	const QString& name()     const;
	const QString& tagColor() const;
	int count() const;

	Wallet* setName(const QString& name);
	Wallet* setTagColor(const QString& color);

	int rowCount(const QModelIndex& parent = QModelIndex()) const override;
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

	bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;

signals:
	void nameChanged(const QString&);
	void tagColorChanged(const QString&);
	void countChanged(int);

public slots:
	void insertRow(int row, Account* account);
	Account* removeRow(int row);

protected:
	QHash<int, QByteArray> roleNames() const override;

private slots:
	void handleDataChanged();

private:
	QString m_name;
	QString m_tagColor;
	QList<Account*> m_accounts;
};

Q_DECLARE_METATYPE(Wallet)
Q_DECLARE_METATYPE(Wallet*)
Q_DECLARE_METATYPE(QList<Wallet*>)

#endif
