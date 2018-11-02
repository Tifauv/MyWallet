#ifndef Config_H
#define Config_H

#include <QObject>
#include <KConfigCore/KConfig>
#include <KConfigCore/KConfigGroup>

class Config : public QObject {
	Q_OBJECT

	Q_PROPERTY(QString previousFolder  READ previousFolder  WRITE setPreviousFolder  NOTIFY previousFolderChanged)
	Q_PROPERTY(uint    previousWidth   READ previousWidth   WRITE setPreviousWidth   NOTIFY previousWidthChanged )
	Q_PROPERTY(uint    previousHeight  READ previousHeight  WRITE setPreviousHeight  NOTIFY previousHeightChanged)

public:
	explicit Config(QObject* parent = nullptr);

	const QString previousFolder() const;
	uint          previousWidth()  const;
	uint          previousHeight() const;

	void setPreviousFolder(const QString&);
	void setPreviousWidth( uint);
	void setPreviousHeight(uint);

signals:
	void previousFolderChanged(QString);
	void previousWidthChanged( uint);
	void previousHeightChanged(uint);

private:
	KConfig m_kconfig;
};

#endif