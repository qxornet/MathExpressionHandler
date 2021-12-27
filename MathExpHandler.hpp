
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
        {"/", {8, false, nullptr}}, {"^", {8, false, nullptr}},
        {"*", {8, false, nullptr}}, {"-", {6, false, nullptr}},
        {"+", {6, false, nullptr}}, {"%", {5, false, nullptr}},
        {"$sqrt", {8, true, nullptr}}, {"$abs",  {8, true, nullptr}},
        {"$sin",  {8, true, nullptr}}, {"$cos",  {8, true, nullptr}},
        {"$arcsin",  {8, true, nullptr}}, {"$arccos",  {8, true, nullptr}},
        {"$log",  {8, true, nullptr}}, {"$dlog",  {8, true, nullptr}},
        {"$exp",  {8, true, nullptr}}, {"$floor",  {8, true, nullptr}},
        {"$ceil",  {8, true, nullptr}}
    };

};