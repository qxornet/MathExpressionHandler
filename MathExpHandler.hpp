
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
    bool isAloneArg;
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
    QString formatString() const;

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
        {"(", {1, true, nullptr}}, {")", {1, true, nullptr}},
        {"[", {1, true, nullptr}}, {"]", {1, true, nullptr}},
        {"/", {8, false, nullptr}}, {"^", {8, false, nullptr}},
        {"*", {8, false, nullptr}}, {"-", {6, false, nullptr}},
        {"+", {6, false, nullptr}}, {"%", {5, false, nullptr}},
        {"$sqrt", {9, true, nullptr}}, {"$abs",  {9, true, nullptr}},
        {"$sin",  {9, true, nullptr}}, {"$cos",  {9, true, nullptr}},
        {"$arcsin",  {9, true, nullptr}}, {"$arccos",  {9, true, nullptr}},
        {"$log",  {9, true, nullptr}}, {"$dlog",  {9, true, nullptr}},
        {"$exp",  {9, true, nullptr}}, {"$floor",  {9, true, nullptr}},
        {"$ceil",  {9, true, nullptr}}
    };

};
