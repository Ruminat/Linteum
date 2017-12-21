#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent) :
	QWidget(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	plots = new Plots(ui->scrollPlots);

	QFile file("://WelcomeText.txt");
			QString line;
			ui->codeEditor->clear();
			if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
					QTextStream stream(&file);
					while (!stream.atEnd()) {
							line = stream.readLine();
							ui->codeEditor->setPlainText(ui->codeEditor->toPlainText() + line + "\n");
					}
					readCode(ui->codeEditor->toPlainText());
			}
	file.close();
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent* e)
{
	if (
			e->key() == Qt::Key_Return
			&& QApplication::keyboardModifiers() & Qt::ControlModifier
	)
	{
		readCode(ui->codeEditor->toPlainText());
	}
}

void MainWindow::readCode(QString text)
{
	try {
		plots->clear();
		CustomParser* parser = new CustomParser();
		QStringList lines = text.split('\n');
		for (QString line: lines) parser->parseLine(line, plots);
	} catch (...) {
		cout << "АЛЛО! ЧТО НАЧАЛОСЬ ТО?!" << endl;
	}
}
