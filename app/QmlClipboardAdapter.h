/*
 *  SPDX-FileCopyrightText: 2018 Olivier Serve <tifauv@gmail.com>
 *
 *  SPDX-License-Identifier: LGPL-2.0-or-later
 */

#ifndef QmlClipboardAdapter_h
#define QmlClipboardAdapter_h

#include <QGuiApplication>
#include <QClipboard>
#include <QTimer>
#include <QObject>

class QmlClipboardAdapter : public QObject {

	Q_OBJECT

public:
	explicit QmlClipboardAdapter(QObject* parent = nullptr);

public slots:
	void setText(const QString& text);
	void setSecretText(const QString& text);
	void clear();
	void setTextWithTimer(const QString& text, uint seconds);
	void setSecretTextWithTimer(const QString& text, uint seconds);

private:
	QClipboard* m_clipboard;
	QTimer*     m_timer;
};

#endif
