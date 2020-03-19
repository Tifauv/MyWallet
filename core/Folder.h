#ifndef Folder_H
#define Folder_H

#include <QObject>
#include <QMetaType>
#include <QAbstractListModel>
#include <QSharedPointer>
#include "Account.h"

class Backend;

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
		AccountRole = Qt::UserRole + 1,
		NameRole,
		LoginRole,
		WebsiteRole,
		NotesRole
	};

	explicit Folder(QObject* parent = nullptr);
	explicit Folder(const Folder&);
	~Folder() override {}

	const QString& name()     const;
	const QString& tagColor() const;
	int count() const;

	Folder* setName(const QString& name);
	Folder* setTagColor(const QString& color);
	Folder* setBackend(const QSharedPointer<Backend> backend);

	int rowCount(const QModelIndex& parent = QModelIndex()) const override;
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

signals:
	void nameChanged(const QString&);
	void tagColorChanged(const QString&);
	void countChanged(int);

public slots:
	Account* createAccount(const QString& name, const QString& login, const QString& website, const QString& notes, const QString& password);
	void addAccount(Account* account);
	void deleteAccount(int row);
	Account* get(int p_row) const;

protected:
	QHash<int, QByteArray> roleNames() const override;
	void appendRow(Account* account);
	void insertRow(int row, Account* account);
	Account* removeRow(int row);

private slots:
	void handleDataChanged();

private:
	QString m_name;
	QString m_tagColor;
	QList<Account*> m_accounts;
	QSharedPointer<Backend> m_backend;
};

Q_DECLARE_METATYPE(Folder)
Q_DECLARE_METATYPE(Folder*)
Q_DECLARE_METATYPE(QList<Folder*>)

#endif
