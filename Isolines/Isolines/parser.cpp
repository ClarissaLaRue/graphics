#include <QFile>
#include <stdio.h>
#include "parser.h"

using std::string;

Parser::Parser()
{

}

void Parser::ParseFile(QString file){
    QFile inFile(file);
    inFile.open(QIODevice::ReadOnly);

    QByteArray line = inFile.readLine();
    string str = line.toStdString();
    k = std::stoi(str, 0, 10);
    m = std::stoi(str.substr(str.find(" ")), 0, 10);

    line = inFile.readLine();
    str = line.toStdString();
    n = std::stoi(str, 0, 10);

    int r;
    int g;
    int b;
    for (int i = 0; i <= n; i++){
        line = inFile.readLine();
        str = line.toStdString();
        r = std::stoi(str, 0, 10);
        str = str.substr(str.find(" ")+1);
        g = std::stoi(str, 0, 10);
        str = str.substr(str.find(" "));
        b = std::stoi(str, 0, 10);
        if (i == n){
            lineColor = QColor(r, g, b);
        }else{
            colors.push_back(QColor(r, g, b));
        }

    }

    inFile.close();
}

int Parser::getM(){
    return m;
}

int Parser::getK(){
    return k;
}

int Parser::getN(){
    return n;
}

vector<QColor> Parser::getColors(){
    return colors;
}

QColor Parser::getLineColor(){
    return lineColor;
}
