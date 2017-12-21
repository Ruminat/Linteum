#include "mainwindow.h"

#ifndef CUSTOMPARSER_H
#define CUSTOMPARSER_H

class CharSet : public QSet<char>
	{
	public:
		CharSet(string const &chars) {
			for (char c: chars) this->insert(c);
		}
		~CharSet() {
			delete this;
		}
	};

class CustomParser
{
private:
	typedef exprtk::symbol_table<double> SymbolTable;
	typedef exprtk::expression<double> Expression;
	typedef exprtk::parser<double> Parser;
	typedef exprtk::function_compositor<double> Compositor;
	typedef typename Compositor::function Function;

	SymbolTable table;
	QMap<string, Compositor*> functions;
	QMap<string, double*> variables;
	Parser parser;

	CharSet alphabet = CharSet("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_$");
	CharSet numbers = CharSet("0123456789");
public:
	void parseLine(QString line, Plots* plots);
	void parseParams(QString params, Plot* plot);
	void checkMainPart(QString part);
	void split(QString line, QString &mainPart, QString &params);
	void assign(QString what, QString to);
	bool checkVar(QString var);
	void range(QString source, double &from, double &to);
	double eval(QString expr);
	void fillValues(Plot* p, string expr);
	CustomParser();
	~CustomParser() { delete this; }
};

#endif // CUSTOMPARSER_H
