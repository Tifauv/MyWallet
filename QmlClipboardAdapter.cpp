#include "QmlClipboardAdapter.h"

#include <QTimer>
#include <iostream>

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
	m_clipboard->setText(p_text, QClipboard::Clipboard);
	m_clipboard->setText(p_text, QClipboard::Selection);
}


/**
 * @brief Clears the clipboard.
 */
void QmlClipboardAdapter::clear() {
	std::cerr << ">> QmlClipboardAdapter::clear (text is " << qPrintable(m_clipboard->text()) << ")" << std::endl;
	m_clipboard->clear(QClipboard::Clipboard);
	m_clipboard->clear(QClipboard::Selection);
	std::cerr << "<< QmlClipboardAdapter::clear (text is " << qPrintable(m_clipboard->text()) << ")" << std::endl;
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
