#include "mainwindow.h"

using namespace std;

#ifndef OPTIONS_H
#define OPTIONS_H

class Colors
{
private:
	static QVector<QColor> ColorsVector;
	static QMap<QString, QColor*> ColorsMap;
public:
	static bool contains(QString color) { return ColorsMap.contains(color); }
	static QColor get(string color) { return *ColorsMap[QString::fromStdString(color)]; }
	static QColor get(QString color) { return get(color.toStdString()); }
	static QColor get(int colorID) { return ColorsVector[colorID]; }
};

#endif // OPTIONS_H
