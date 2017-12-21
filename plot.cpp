#include "plot.h"

Plot::Plot()
{
	this->setFixedHeight(size);
	X = QVector<double>(partitions+1);
	Y = QVector<double>(partitions+1);
}

// Save plot by clicking
void Plot::mousePressEvent(QMouseEvent*)
{
	QString fileName = QFileDialog::getSaveFileName(this,
		tr("Сохранить график"), "",
		tr("PDF (*.pdf);;PNG (*.png);;JPEG (*.jpg)")
	);
	QString ext = fileName.mid(fileName.length() - 4, 4);
	if (fileName == "") return;
	if (ext == ".pdf") this->savePdf(fileName, 512, 512);
	else if (ext == ".png") this->savePng(fileName, 512, 512);
	else if (ext == ".jpg") this->saveJpg(fileName, 512, 512);
	else this->savePdf(fileName + ".pdf", 512, 512);
}

void Plot::draw()
{
	try
	{
		this->addGraph();
		this->graph(ID)->setData(X, Y);
		QPen myPen = this->graph(ID)->pen();
		myPen.setWidth(lineWidth);
		myPen.setColor(color);
		this->graph(ID)->setPen(myPen);
		// add labeles if needed
		if (xLabel != "") this->xAxis->setLabel(xLabel);
		if (yLabel != "") this->yAxis->setLabel(yLabel);
		// set axes ranges, so we see all data:
		this->xAxis->setRange(from, to);
		this->yAxis->setRange(minVal - 0.5, maxVal + 0.5);
		// set axes ranges, so we see all data:
		this->replot();
	}
	catch (...)
	{
		cout << "АЛЯРМА!!! АШИБКАААА!!!!11!!11!1!!!!!" << endl;
	}
}
