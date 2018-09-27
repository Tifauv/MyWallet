#include "Trash.h"
#include <QtDebug>

// CONSTRUCTORS
/**
 * @brief Trash::Trash
 * @param p_parent
 */
Trash::Trash(QObject* p_parent) :
    Folder(p_parent) {
	setName(tr("Trash"));
	setTagColor("transparent");
	qDebug() << "(i) [Trash] Created.";
}


/**
 * @brief Trash::Trash
 * @param p_toCopy
 */
Trash::Trash(const Trash& p_toCopy) :
    Folder(p_toCopy) {
	qDebug() << "(i) [Trash] Copied trash with " << count() << " accounts.";
}
