#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "QmlClipboardAdapter.h"
#include "core/ManagedWallets.h"

int main(int p_argc, char* p_argv[]) {
	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
	QGuiApplication app(p_argc, p_argv);

	qmlRegisterType<QmlClipboardAdapter>("Wallets", 1, 0, "Clipboard");
	qmlRegisterType<ManagedWallets>(     "Wallets", 1, 0, "Wallets"  );
	qmlRegisterType<Wallet>(             "Wallets", 1, 0, "Wallet"   );
	qmlRegisterType<Account>(            "Wallets", 1, 0, "Account"  );

	QQmlApplicationEngine engine;
	engine.load(QUrl(QStringLiteral("qrc:/ui/main.qml")));
	if (engine.rootObjects().isEmpty())
		return -1;

	return app.exec();
}
