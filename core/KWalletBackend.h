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
	int load() const;

	// Folder management
	bool hasFolder(const QString& name) const;
	void createFolder(const Folder& folder) const;
	void removeFolder(const QString& name) const;

	// Account management
	const QString& retrievePassword(const QString& folder, const QString& account) const;

private:
	QString m_walletName;
	QScopedPointer<KWallet::Wallet> m_kwallet;
};

#endif
