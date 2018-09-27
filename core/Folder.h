#ifndef Folder_H
#define Folder_H

#include <QObject>
#include <QMetaType>
#include <QAbstractListModel>
#include "Account.h"

/**
 * @brief The Folder class
 */
class Folder : public QAbstractListModel {
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

	explicit Folder(QObject* parent = nullptr);
	explicit Folder(const Folder&);
	~Folder() {}

	const QString& name()     const;
	const QString& tagColor() const;
	int count() const;

	Folder* setName(const QString& name);
	Folder* setTagColor(const QString& color);

	int rowCount(const QModelIndex& parent = QModelIndex()) const override;
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

signals:
	void nameChanged(const QString&);
	void tagColorChanged(const QString&);
	void countChanged(int);

public slots:
	void addAccount(const QString& name, const QString& login);
	void insertRow(int row, Account* account);
	Account* removeRow(int row);

protected:
	QHash<int, QByteArray> roleNames() const override;
	int retrievePassword(Account& account, QString& password) const;

private slots:
	void handleDataChanged();

private:
	QString m_name;
	QString m_tagColor;
	QList<Account*> m_accounts;
};

Q_DECLARE_METATYPE(Folder)
Q_DECLARE_METATYPE(Folder*)
Q_DECLARE_METATYPE(QList<Folder*>)

#endif
