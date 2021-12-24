#include "MathExpHandler.hpp"

MathExpHandler::MathExpHandler()
{
    funcInitilize();
}

MathExpHandler::MathExpHandler(QString formula) :
    format(formula)
{
    funcInitilize();
}

void MathExpHandler::setFormatString(QString formula)
{
    format = formula;
}

void MathExpHandler::processing()
{
    stringConversion();
    calcMathExp();

    for(auto& item : operands)
    {
        std::cout << item.toStdString() + " ";
    }

    std::cout << std::endl;
}


double MathExpHandler::getFinally() const
{
    return finally;
}

void MathExpHandler::stringConversion()
{
    operations.clear();
    operands.clear();

    QString symbol;
    QString value;
    bool isWaitOpt = false;
    for(auto& chr : format)
    {
        if(!isWaitOpt) symbol = QString(chr);
        else symbol += QString(chr);

        if(!symbol.compare("$")) isWaitOpt = true;
        if(optMap.find(symbol) != optMap.end())
        {
            try
            {
                if(!value.isEmpty())
                {
                    addOperator(value);
                    value.clear();
                }

                addOperation(symbol);
                symbol.clear();

                isWaitOpt = false;
            }
            catch(std::string e)
            {
                std::cout << e << std::endl;
            }
        }
        else
        {
            if(!symbol.compare(" ") || isWaitOpt) continue;
            value += symbol;
        }
    }

    addOperator(value);
    operands.insert(operands.end(), operations.begin(), operations.end());
    operations.clear();
}

void MathExpHandler::calcMathExp()
{
    double lvalue = 0.0;
    double rvalue = 0.0;

    for(auto& item : operands)
    {

        if(optMap.find(item) != optMap.end() &&
                lvalue != 0 && rvalue != 0)
        {
            double result = optMap[item](lvalue, rvalue);
            auto rfound = std::find(operands.begin(), operands.end(), QString::number(rvalue));
            auto lfound = std::find(operands.begin(), operands.end(), QString::number(lvalue));
            operands.erase(rfound);
        }

        lvalue = lvalue == 0 ? item.toDouble() : lvalue;
        rvalue = rvalue == 0 ? item.toDouble() : rvalue;
    }

    qDebug() << optMap["^"](10, 2);
}

void MathExpHandler::addOperation(QString _opt)
{
    if(!_opt.compare(")"))
    {
        std::reverse(operations.begin(), operations.end());

        auto founded = std::find(operations.begin(), operations.end(), "(");
        if(founded == operations.end()) throw std::string("Syntax error");

        operands.insert(operands.end(), operations.begin(), founded);
        operations.erase(operations.begin(), founded+1);

        std::reverse(operations.begin(), operations.end());
        return;
    }

    if(!_opt.compare("(")) { operations.push_back(_opt); return; }
    if(!operations.empty() && optMap[_opt].weight <= optMap[operations.back()].weight)
    {

        operands.push_back(operations.back());
        operations.pop_back();
        operations.push_back(_opt);
        return;
    }

    operations.push_back(_opt);
}

void MathExpHandler::addOperator(QString _opr)
{
    if(!_opr.isEmpty())
        operands.push_back(_opr);
}

void MathExpHandler::funcInitilize()
{
    optMap["/"].function = [](double leftValue, double rightValue) {
        return leftValue / rightValue;
    };

    optMap["*"].function = [](double leftValue, double rightValue) {
        return leftValue * rightValue;
    };

    optMap["^"].function = [](double leftValue, double rightValue) {
        return std::pow(leftValue, rightValue);
    };

    optMap["-"].function = [](double leftValue, double rightValue) {
        return leftValue - rightValue;
    };

    optMap["+"].function = [](double leftValue, double rightValue) {
        return leftValue + rightValue;
    };

    optMap["%"].function = [](double leftValue, double rightValue) {
        return std::fmod(leftValue, rightValue);
    };

    optMap["$sqrt"].function = [](double leftValue, double rightValue) {
        return std::sqrt(leftValue);
    };

    optMap["$abs"].function = [](double leftValue, double rightValue) {
        return std::fabs(leftValue);
    };

    optMap["$sin"].function = [](double leftValue, double rightValue) {
        return std::sin(leftValue);
    };

    optMap["$cos"].function = [](double leftValue, double rightValue) {
        return std::cos(leftValue);
    };

    optMap["$arcsin"].function = [](double leftValue, double rightValue) {
        return std::asin(leftValue);
    };

    optMap["$arccos"].function = [](double leftValue, double rightValue) {
        return std::acos(leftValue);
    };

    optMap["$log"].function = [](double leftValue, double rightValue) {
        return std::log(leftValue);
    };

    optMap["$dlog"].function = [](double leftValue, double rightValue) {
        return std::log10(leftValue);
    };

    optMap["$exp"].function = [](double leftValue, double rightValue) {
        return std::exp(leftValue);
    };

    optMap["$floor"].function = [](double leftValue, double rightValue) {
        return std::floor(leftValue);
    };

    optMap["$ceil"].function = [](double leftValue, double rightValue) {
        return std::ceil(leftValue);
    };
}


MathExpHandler::~MathExpHandler()
{

}

double BaseOpt::operator()(double _larg, double _rarg)
{
    return function(_larg, _rarg);
}
