#include "customparser.h"

CustomParser::CustomParser()
{
	table.add_constant("e", 2.71828182845904523536028747135266);
	table.add_constant("phi", 1.618033988749894848204586834365);
	table.add_constants();
}

void CustomParser::parseLine(QString line, Plots* plots)
{
	if (line.trimmed() == "") return;
	QString mainPart = "";
	QString params = "";

	split(line, mainPart, params);
	if (mainPart.trimmed() == "") return;
	QStringList parts = mainPart.split('=');

	if (parts.length() == 1)
	{ // f(x)
		Plot* p = plots->add();
		parseParams(params, p);
		fillValues(p, mainPart.toStdString());
		p->draw();
	}
	else if (parts.length() == 2)
	{ // ... = ...
		assign(parts[0].trimmed(), parts[1].trimmed());
	}
}

void CustomParser::fillValues(Plot* p, string expr)
{
	double x, y;

	table.add_variable(p->var, x);
	Expression expression;
	expression.register_symbol_table(table);

	if (!parser.compile(expr, expression))
		throw 1;
	else
	{
		x = p->from;
		y = expression.value();
		double minValTemp = +numeric_limits<double>::max();
		double maxValTemp = -numeric_limits<double>::max();
		for (int c = 0; c <= p->partitions; c++)
		{
			x = p->from + abs(p->from - p->to) * ((double)c / (double)p->partitions);
			y = expression.value();

			p->X[c] = x;
			p->Y[c] = y;

			if (p->autoValues && abs(y) != INFINITY && !isnan(y))
			{
				if (minValTemp > y) minValTemp = y;
				if (maxValTemp < y) maxValTemp = y;
			}
		}
		if (p->autoValues)
		{
			p->minVal = (minValTemp == numeric_limits<double>::max()) ? 0 : minValTemp;
			p->maxVal = (minValTemp == numeric_limits<double>::min()) ? 0 : maxValTemp;
		}
	}
}

void CustomParser::split(QString line, QString &mainPart, QString &params)
{
	for (int c = 0; c < line.length(); c++)
	{
		if (line[c] == '#') return;
		if (line[c] == ':' && c + 2 < line.length() && line[c+1] == ':')
		{
			c += 2;
			while (c < line.length())
			{
				if (line[c] == '#') return;
				params += line[c];
				c++;
			}
			return;
		}
		mainPart += line[c];
	}
}

void CustomParser::assign(QString what, QString to)
{
	QString name = "";
	string whatStd = what.toStdString();
	if (!alphabet.contains(whatStd[0])) throw 1;
	for (int c = 0; c < what.length(); c++)
	{
		char s = whatStd[c];
		if (alphabet.contains(whatStd[c]) || numbers.contains(whatStd[c])) name += s;
		else if (s == '(')
		{
			// function
			string nameStd = name.toStdString();
			if (what[what.length() - 1] != ')') throw 1;
			QStringList vars = what.mid(c + 1, what.length() - name.length() - 2).split(',');
			Function f = Function().name(nameStd);
			for (QString v: vars)
			{
				QString var = v.trimmed();
				if (!checkVar(var)) throw 1;
				f.var(var.toStdString());
			}
			f.expression(to.toStdString());
			if (functions.contains(nameStd)) functions[nameStd]->clear();
			else functions[nameStd] = new Compositor(table);
			functions[nameStd]->add(f);
			return;
		}
		else throw 1;
	}
	// variable
	string nameStd = name.toStdString();
	Expression varExpr;
	varExpr.register_symbol_table(table);
	if (!parser.compile(to.toStdString(), varExpr))
		throw 1;
	else
	{
		if (!variables.contains(nameStd)) {
			variables[nameStd] = new double(varExpr.value());
			table.add_variable(nameStd, *variables[nameStd]);
		} else *variables[nameStd] = varExpr.value();
	}
}

bool CustomParser::checkVar(QString var)
{
	string varStd = var.toStdString();
	if (!alphabet.contains(varStd[0])) return false;
	for (int c = 1; c < var.length(); c++)
		if (!alphabet.contains(varStd[c]) && !numbers.contains(varStd[c])) return false;
	return true;
}

void CustomParser::range(QString source, double& from, double& to)
{
	QStringList parts = source.split("..");
	from = eval(parts[0]);
	to = eval(parts[1]);
}

double CustomParser::eval(QString str)
{
	Expression expr;
	expr.register_symbol_table(table);
	if (!parser.compile(str.toStdString(), expr))
		throw 1;
	else return expr.value();
}

void CustomParser::parseParams(QString params, Plot* plot)
{
	if (params == "") return;
	QStringList paramsList = params.split(';');
	for (QString s: paramsList)
	{
		QStringList parts = s.split('=');
		QString param = parts[0].trimmed();
		QString value = parts[1].trimmed();
		if ( param[0] == '@' && checkVar(param.mid(1, param.length())) ) {
			plot->var = param.mid(1, param.length()).toStdString();
			if (param != "") range(value, plot->from, plot->to);
		} else if (param == "y" || param == "range") {
			range(value, plot->minVal, plot->maxVal);
			plot->autoValues = false;
		}
		else if (param == "color")
		{
			if (Colors::contains(value)) plot->color = Colors::get(value);
			else throw 1;
		}
		else if (param == "xLabel") plot->xLabel = value;
		else if (param == "yLabel") plot->yLabel = value;
		else if (param == "lineWidth") plot->lineWidth = eval(value);
	}
}
