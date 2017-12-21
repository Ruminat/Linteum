#include "mainwindow.h"

#ifndef PLOTS_H
#define PLOTS_H

class Plots : public QVBoxLayout
{
private:
	QVector<Plot*> plots;
public:
	Plots(QScrollArea *scroll);
	Plot* add();
	void clear();
};

#endif // PLOTS_H
