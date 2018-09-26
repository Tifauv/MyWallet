#include "QmlClipboardAdapter.h"

#include <QMimeData>

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
	mimeData->setData("x-kde-passwordManagerHint", QString("secret").toUtf8());
	m_clipboard->setMimeData(mimeData, QClipboard::Clipboard);

	if (m_clipboard->supportsSelection()) {
		QMimeData* mimeData = new QMimeData();
		mimeData->setText(p_text);
		mimeData->setData("x-kde-passwordManagerHint", QString("secret").toUtf8());
		m_clipboard->setMimeData(mimeData, QClipboard::Selection);
	}
}


/**
 * @brief Clears the clipboard.
 */
void QmlClipboardAdapter::clear() {
	m_clipboard->clear(QClipboard::Clipboard);
	m_clipboard->clear(QClipboard::Selection);
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
}
