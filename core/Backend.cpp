#include "Backend.h"
#include <QDebug>

// CONSTRUCTORS
/**
 * @brief Backend::Backend
 * @param p_parent
 */
Backend::Backend(QObject* p_parent) :
    QObject(p_parent) {
	qDebug() << "(i) [Backend] Created.";
}
