#ifndef Account_H
#define Account_H

#include <QObject>

class Account : public QObject {
	Q_OBJECT

	Q_PROPERTY(QString name      READ name      WRITE setName      NOTIFY nameChanged      DESIGNABLE false)
	Q_PROPERTY(QString login     READ login     WRITE setLogin     NOTIFY loginChanged     DESIGNABLE false)
	Q_PROPERTY(QString password  READ password  WRITE setPassword  NOTIFY passwordChanged  DESIGNABLE false)

public:
	explicit Account(const QString& name = QString::null, const QString& login = QString::null, QObject* parent = nullptr);
	explicit Account(const Account&);
	~Account() {}

	const QString& name()     const;
	const QString& login()    const;
	const QString& password() const;

	void setName(const QString& name);
	void setLogin(const QString& login);
	void setPassword(const QString& password);

signals:
	void nameChanged(QString);
	void loginChanged(QString);
	void passwordChanged(QString);

private:
	QString m_name;
	QString m_login;
};

#endif
