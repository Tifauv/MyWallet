#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "QmlClipboardAdapter.h"
#include "ManagedWallets.h"

int main(int p_argc, char* p_argv[]) {
	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
	QGuiApplication app(p_argc, p_argv);

	qmlRegisterType<QmlClipboardAdapter>("Wallets", 1, 0, "Clipboard");
	qmlRegisterType<ManagedWallets>("Wallets", 1, 0, "Wallets");

	QQmlApplicationEngine engine;
	engine.load(QUrl(QStringLiteral("qrc:/ui/main.qml")));
	if (engine.rootObjects().isEmpty())
		return -1;

	return app.exec();
}
