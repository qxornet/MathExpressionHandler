
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

#include <QString>
#include <QDebug>

class MathExpHandler
{

public:

    MathExpHandler();
   ~MathExpHandler();

// methods
public:

    void setFormatString(QString formula);
    void processing();

    double getFinally() const;

// methods
private:

    void addOperation(QString _opt);
    void addOperator(QString _opr);

    void stringConversion();

// variables
protected:


// variables
private:

    QString format;

    std::vector<QString> operations;
    std::vector<QString> operands;

    double finally {0.0};

    std::map<QString, int> weightOpt = {
        {"(", 1},
        {")", 1},
        {"/", 8},
        {"^", 8},
        {"*", 8},
        {"-", 6},
        {"+", 6},
        {"%", 5},
        {"$sqrt", 8},
        {"$mod",  8},
        {"$sin",  8},
        {"$cos",  8},
    };

};

