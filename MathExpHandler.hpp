
/************************************************
 *
 *              CREATED BY QXORNET
 *
 ************************************************/

#pragma once

#include <tuple>
#include <vector>
#include <array>
#include <utility>
#include <memory>
#include <algorithm>
#include <string>
#include <any>
#include <variant>
#include <map>
#include <iostream>
#include <functional>
#include <cmath>

#include <QString>
#include <QDebug>

#define CalcFunc std::function<double(double, double)>

struct BaseOpt
{
    int weight;
    CalcFunc function;

    double operator()(double _larg, double _rarg);
};

class MathExpHandler
{

public:

    MathExpHandler();
    MathExpHandler(QString formula);
   ~MathExpHandler();

public:

    void setFormatString(QString formula);
    void processing();

    double getFinally() const;


private:

    void addOperation(QString _opt);
    void addOperator(QString _opr);

    void stringConversion();
    void calcMathExp();

    void funcInitilize();

protected:

// GOTO:

private:

    QString format;

    std::vector<QString> operations;
    std::vector<QString> operands;

    double finally {0.0};

    std::map<QString, BaseOpt> optMap = {
        {"(", {1, nullptr}}, {")", {1, nullptr}},
        {"/", {8, nullptr}}, {"^", {8, nullptr}},
        {"*", {8, nullptr}}, {"-", {6, nullptr}},
        {"+", {6, nullptr}}, {"%", {5, nullptr}},
        {"$sqrt", {8, nullptr}}, {"$abs",  {8, nullptr}},
        {"$sin",  {8, nullptr}}, {"$cos",  {8, nullptr}},
        {"$arcsin",  {8, nullptr}}, {"$arccos",  {8, nullptr}},
        {"$log",  {8, nullptr}}, {"$dlog",  {8, nullptr}},
        {"$exp",  {8, nullptr}}, {"$floor",  {8, nullptr}},
        {"$ceil",  {8, nullptr}}
    };

};

