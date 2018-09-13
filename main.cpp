#include <QGuiApplication>
#include <QQmlApplicationEngine>

int main(int argc, char* p_argv[]) {
	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

	QGuiApplication app(p_argc, p_argv);

	QQmlApplicationEngine engine;
	engine.load(QUrl(QStringLiteral("qrc:/ui/main.qml")));
	if (engine.rootObjects().isEmpty())
		return -1;

	return app.exec();
}
