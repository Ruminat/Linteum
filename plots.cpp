#include "plots.h"

Plots::Plots(QScrollArea *scroll)
{
	scroll->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
	scroll->setWidgetResizable(true);
	scroll->setFixedWidth(Plot::size + 16);

	QWidget *widget = new QWidget();
	scroll->setWidget(widget);

	widget->setLayout(this);
}

Plot* Plots::add()
{
	Plot *plot = new Plot();
	plots.push_back(plot);
	this->addWidget(plot);
	return plot;
}

void Plots::clear()
{
	for (int c = plots.size() - 1; c >= 0; c--) delete plots[c];
	plots.clear();
}
