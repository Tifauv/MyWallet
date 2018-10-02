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
	~KWalletBackend();

	// Initial loading
	int load() const override;

	// Folder management
	bool hasFolder(const QString& name) const override;
	void createFolder(const Folder& folder) const override;
	void removeFolder(const QString& name) const override;

	// Account management
	bool hasAccount(const QString& folder, const QString& name) const override;
	void createAccount(const QString& folder, const Account& account, const QString& password) const override;
	void removeAccount(const QString& folder, const QString& name) const override;

	const QString retrievePassword(const QString& folder, const QString& account) const override;

private:
	QString m_walletName;
	QScopedPointer<KWallet::Wallet> m_kwallet;
};

#endif
