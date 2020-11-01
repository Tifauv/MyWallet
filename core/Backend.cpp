/*
 *  SPDX-FileCopyrightText: 2018 Olivier Serve <tifauv@gmail.com>
 *
 *  SPDX-License-Identifier: LGPL-2.0-or-later
 */

#include "Backend.h"
#include "Folder.h"
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
