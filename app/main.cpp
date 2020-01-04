#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QIcon>
#include <QWindow>

#include "QmlClipboardAdapter.h"
#include "Config.h"
#include "MyWalletConfig.h"
#include "core/Wallet.h"

int main(int p_argc, char* p_argv[]) {
	QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
	QGuiApplication app(p_argc, p_argv);
	app.setOrganizationName("CatWitch");
	app.setOrganizationDomain("catwitch.eu");
	app.setApplicationName("mywallet");
	app.setApplicationDisplayName("MyWallet");
	app.setApplicationVersion("MYWALLET_MAJOR_VERSION.MYWALLET_MINOR_VERSION");

	// Register model types with the QML engine
	qmlRegisterType<QmlClipboardAdapter>("Wallets", 1, 0, "Clipboard");
	qmlRegisterType<Config>(             "Wallets", 1, 0, "Config"   );
	qmlRegisterType<Wallet>(             "Wallets", 1, 0, "Wallet"   );
	qmlRegisterType<Folder>(             "Wallets", 1, 0, "Folder"   );
	qmlRegisterType<Account>(            "Wallets", 1, 0, "Account"  );

	// Set the default icon theme name
	if (QIcon::themeName().isEmpty()) {
		QIcon::setThemeName("breeze");
	}

	QQmlApplicationEngine engine;
	engine.load(QUrl(QStringLiteral("qrc:/ui/main.qml")));
	if (engine.rootObjects().isEmpty())
		return -1;

	return app.exec();
}
