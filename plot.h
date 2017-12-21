#include "mainwindow.h"

using std::string;
using std::cout;

#ifndef PLOT_H
#define PLOT_H

class Plots;

class Plot : QCustomPlot
{
	friend class Plots;
	friend class CustomParser;

private:
  // plot can have multiple functions, so we give each one of them an ID
  // when we add a function to the plot, we encrease this value by 1
  int ID = 0;
  // the size (in px) of each plot element in UI
  static const int size = 360;
  // the number of partitions we divide the interval (x from ... to ...)
  static const int partitions = 720;
	QVector<double> X, Y;

	string var = "x";
	// x
	double from = -5;
	double to = 5;
	// y
	double minVal = -1;
	double maxVal = 1;
	bool autoValues = true; // minValue & maxValue are being computed while parsing

	double lineWidth = 2;
	QString xLabel = "";
	QString yLabel = "";
	QColor color = Colors::get(QString("blue"));

	void mousePressEvent(QMouseEvent*);
public:
	Plot();
	virtual ~Plot(void) {}
	void draw();
};

#endif // PLOT_H
