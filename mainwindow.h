#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QtGui>
#include <QStyle>
#include <QDesktopWidget>
#include <QSet>
#include <QMap>

#include <iostream>
#include <string>
#include <cmath>
#include "limits.h"

#include "exprtk.hpp"
#include "qcustomplot.h"

#include "colors.h"
#include "plot.h"
#include "plots.h"
#include "customparser.h"

using std::string;
using std::cout;

namespace Ui { class MainWindow; }

class MainWindow : public QWidget
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget* parent = 0);
	~MainWindow();

protected:
	void keyPressEvent(QKeyEvent* e);

private:
	Ui::MainWindow* ui;
	Plots* plots;
	void readCode(QString text);
};

#endif // MAINWINDOW_H
