#ifndef Backend_H
#define Backend_H

#include <QObject>
#include "Folder.h"

class Backend : public QObject {
	Q_OBJECT

public:
	explicit Backend(QObject* parent = nullptr);
	~Backend() {}

	// Initial loading
	virtual int load() const = 0;

	// Folder management
	virtual bool hasFolder(const QString& name) const = 0;
	virtual void createFolder(const Folder& folder) const = 0;
	virtual void removeFolder(const QString& name) const = 0;

	// Account management
	virtual const QString& retrievePassword(const QString& folderName, const QString& accountName) const = 0;

signals:
	void folderLoaded(Folder*) const;
};

#endif
