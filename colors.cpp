#include "colors.h"

QVector<QColor> Colors::ColorsVector = {
	QColor("#5E81B5"), // blue
	QColor("#E19C24"), // orange
	QColor("#8FB131"), // green
	QColor("#F18A68")  // red
};

QMap<QString, QColor*> Colors::ColorsMap = {
	{"blue",   &ColorsVector[0]},
	{"orange", &ColorsVector[1]},
	{"green",  &ColorsVector[2]},
	{"red",    &ColorsVector[3]},
	{"white",  new QColor("#FFFFFF")},
	{"black",  new QColor("#000000")}
};
