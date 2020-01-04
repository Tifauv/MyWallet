#ifndef QmlClipboardAdapter_h
#define QmlClipboardAdapter_h

#include <QGuiApplication>
#include <QClipboard>
#include <QTimer>
#include <QObject>

class QmlClipboardAdapter : public QObject {

	Q_OBJECT

public:
	explicit QmlClipboardAdapter(QObject* parent = 0);

public slots:
	void setText(const QString& text);
	void clear();
	void setTextWithTimer(const QString& text, uint seconds);

private:
	QClipboard* m_clipboard;
	QTimer*     m_timer;
};

#endif
