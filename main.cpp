#include "MainWindow.hpp"

#include <QApplication>

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);

	MainWindow mainWindow;
	mainWindow.setWindowTitle("Object Management Application");
	mainWindow.resize(800, 600);
	mainWindow.show();

	return app.exec();
}
