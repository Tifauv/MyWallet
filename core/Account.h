#ifndef Account_H
#define Account_H

#include <QObject>

class Account : public QObject {
	Q_OBJECT

	Q_PROPERTY(QString name   READ name   WRITE setName   NOTIFY nameChanged   DESIGNABLE false)
	Q_PROPERTY(QString login  READ login  WRITE setLogin  NOTIFY loginChanged  DESIGNABLE false)

public:
	explicit Account(const QString& name = QString(), const QString& login = QString(), QObject* parent = nullptr);
	explicit Account(const Account&);
	~Account() {}

	const QString& name()     const;
	const QString& login()    const;

	Account* setName(const QString& name);
	Account* setLogin(const QString& login);

signals:
	void nameChanged(QString);
	void loginChanged(QString);

private:
	QString m_name;
	QString m_login;
};

#endif
