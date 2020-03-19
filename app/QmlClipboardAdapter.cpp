#include "QmlClipboardAdapter.h"

#include <QMimeData>
#include <QtDebug>

// CONSTRUCTOR
QmlClipboardAdapter::QmlClipboardAdapter(QObject* p_parent) :
QObject(p_parent) {
	m_clipboard = QGuiApplication::clipboard();
	m_timer = new QTimer(this);
	m_timer->setSingleShot(true);
	connect(m_timer, SIGNAL(timeout()), this, SLOT(clear()));
}


// SLOTS
/**
 * @brief Copies some text to the clipboard.
 *
 * @param p_text
 *            the text to copy to the clipboard
 */
void QmlClipboardAdapter::setText(const QString& p_text) {
	QMimeData* mimeData = new QMimeData();
	mimeData->setText(p_text);
	m_clipboard->setMimeData(mimeData, QClipboard::Clipboard);
	qDebug() << "(i) [QmlClipboardAdapter] Text copied to Clipboard.";

	if (m_clipboard->supportsSelection()) {
		QMimeData* mimeData = new QMimeData();
		mimeData->setText(p_text);
		m_clipboard->setMimeData(mimeData, QClipboard::Selection);
		qDebug() << "(i) [QmlClipboardAdapter] Text copied to Selection.";
	}
}


/**
 * @brief Copies some text to the clipboard.
 *
 * @param p_text
 *            the text to copy to the clipboard
 */
void QmlClipboardAdapter::setSecretText(const QString& p_text) {
	QMimeData* mimeData = new QMimeData();
	mimeData->setText(p_text);
	mimeData->setData("x-kde-passwordManagerHint", QString("secret").toUtf8());
	m_clipboard->setMimeData(mimeData, QClipboard::Clipboard);
	qDebug() << "(i) [QmlClipboardAdapter] Secret text copied to Clipboard.";

	if (m_clipboard->supportsSelection()) {
		QMimeData* mimeData = new QMimeData();
		mimeData->setText(p_text);
		mimeData->setData("x-kde-passwordManagerHint", QString("secret").toUtf8());
		m_clipboard->setMimeData(mimeData, QClipboard::Selection);
		qDebug() << "(i) [QmlClipboardAdapter] Secret text copied to Selection.";
	}
}


/**
 * @brief Clears the clipboard.
 */
void QmlClipboardAdapter::clear() {
	m_clipboard->clear(QClipboard::Clipboard);
	qDebug() << "(i) [QmlClipboardAdapter] Clipboard cleared.";
	m_clipboard->clear(QClipboard::Selection);
	qDebug() << "(i) [QmlClipboardAdapter] Selection cleared.";
}


/**
 * @brief Copies some text to the clipboard for a limited duration only.
 *
 * @param p_text
 *            the text to copy to the clipboard
 * @param p_seconds
 *            the number of seconds after which the clipboard is cleared
 */
void QmlClipboardAdapter::setTextWithTimer(const QString& p_text, uint p_seconds) {
	setText(p_text);
	m_timer->start(p_seconds * 1000);
	qDebug() << "(i) [QmlClipboardAdapter] Text will be cleared in" << p_seconds << "seconds.";
}



/**
 * @brief Copies some text to the clipboard for a limited duration only.
 *
 * @param p_text
 *            the text to copy to the clipboard
 * @param p_seconds
 *            the number of seconds after which the clipboard is cleared
 */
void QmlClipboardAdapter::setSecretTextWithTimer(const QString& p_text, uint p_seconds) {
	setSecretText(p_text);
	m_timer->start(p_seconds * 1000);
	qDebug() << "(i) [QmlClipboardAdapter] Secret text will be cleared in" << p_seconds << "seconds.";
}
