#ifndef Trash_H
#define Trash_H

#include <QObject>
#include <QMetaType>
#include "Folder.h"

class Trash : public Folder {
	Q_OBJECT

public:
	explicit Trash(QObject* parent = nullptr);
	explicit Trash(const Trash&);
	~Trash() {}
};

Q_DECLARE_METATYPE(Trash)
Q_DECLARE_METATYPE(Trash*)

#endif
