#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	// create main window
	MainWindow mainWindow;
	// change it's title
	mainWindow.setWindowTitle("Linteum");
	// place main window at center of the screen
	mainWindow.setGeometry(QStyle::alignedRect(
		Qt::LeftToRight,
		Qt::AlignCenter,
		mainWindow.size(),
		app.desktop()->availableGeometry()
	));
	// display our window
	mainWindow.show();

	return app.exec();
}
