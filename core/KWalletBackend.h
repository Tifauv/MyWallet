#ifndef KWalletBackend_H
#define KWalletBackend_H

#include <QObject>
#include <QScopedPointer>
#include <KWallet/KWallet>
#include "Backend.h"

class KWalletBackend : public Backend {
	Q_OBJECT

public:
	explicit KWalletBackend(const QString& walletName, QObject* parent = nullptr);
	~KWalletBackend() override;

	// Initial loading
	void load() override;

	// Folder management
	bool hasFolder(const QString& name) const override;
	void createFolder(const Folder& folder) const override;
	void removeFolder(const QString& name) const override;

	// Account management
	bool hasAccount(const QString& folder, const QString& name) const override;
	void createAccount(const QString& folder, const Account& account, const QString& password) const override;
	void removeAccount(const QString& folder, const QString& name) const override;

	bool modifyAccountLogin(const QString& folder, const QString& name, const QString& login) const override;
	bool modifyAccountWebsite(const QString& folder, const QString& name, const QString& website) const override;
	bool modifyAccountNotes(const QString& folder, const QString& name, const QString& notes) const override;

	// Password management
	const QString retrievePassword(const QString& folder, const QString& account) const override;
	const QMap<QString,QString> retrievePasswordHistory(const QString& p_folder, const QString& p_account) const override;
	bool renewPassword(const QString& p_folder, const QString& p_account, const QString& p_password) const override;

private slots:
	void loadWalletContent(bool openSuccess);
	
private:
	QString m_walletName;
	QScopedPointer<KWallet::Wallet> m_kwallet;
	
	const QString LOGIN_KEY = "login";
	const QString PASSWORD_KEY = "password";
	const QString WEBSITE_KEY = "website";
	const QString NOTES_KEY = "notes";
};

#endif
