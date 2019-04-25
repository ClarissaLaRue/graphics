#ifndef PARSER_H
#define PARSER_H

#include <QColor>
#include <QString>
#include <vector>

using std::vector;

class Parser
{
public:
    Parser();
    void ParseFile(QString file);
    int getM();
    int getK();
    int getN();
    vector<QColor> getColors();
    QColor getLineColor();


private:
    int k;
    int m;
    int n;
    vector<QColor> colors;
    QColor lineColor;
};

#endif // PARSER_H
