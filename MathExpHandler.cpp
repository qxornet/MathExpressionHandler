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
    try
    {
        stringConversion();
        calcMathExp();
    }
    catch(...)
    {
        std::cout << "Incorrect syntax" << std::endl;
    }
}


double MathExpHandler::getFinally() const
{
    return finally;
}

QString MathExpHandler::formatString() const
{
    return format;
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
            if(!value.isEmpty())
            {
                addOperator(value);
                value.clear();
            }

            addOperation(symbol);
            symbol.clear();

            isWaitOpt = false;
        }
        else
        {
            if(!symbol.compare(" ") || isWaitOpt) continue;
            value += symbol;
        }
    }

    std::sort(operations.begin(), operations.end(), [this](auto& litem, auto& ritem)
    {
       if(optMap[litem].weight >= optMap[ritem].weight) return true;
    });

    addOperator(value);
    operands.insert(operands.end(), operations.begin(), operations.end());
    operations.clear();
}

void MathExpHandler::calcMathExp()
{
    std::list<QString> window;

    for(auto iter = operands.begin(); iter != operands.end(); iter++)
    {
        if(operands.size() <= 1) break;
        if(window.size() == 3 && operands.size() >= 3) window.pop_front();
        window.push_back(*iter);

        if(optMap.find(window.back()) == optMap.end()) continue;

        double result = 0.0;
        if(optMap[window.back()].isAloneArg)
        {
            if(window.size() < 2) throw std::string("Icorrect syntax");
            auto value = std::prev(window.end(), 2);
            result = optMap[window.back()](value->toDouble(), 1);
            operands.erase(iter); iter -= 1;

            *iter = QString::number(result);
        }
        else
        {
            auto lvalue = window.begin();
            auto rvalue = std::next(window.begin(), 1);

            result = optMap[window.back()](lvalue->toDouble(), rvalue->toDouble());
            operands.erase(iter-2, iter); iter -= 2;

            *iter = QString::number(result);
        }

        iter = operands.begin() - 1;
    }


    finally = operands.size() > 0 ? operands[0].toDouble() : 0;
}

void MathExpHandler::addOperation(QString _opt)
{
    bool isBlock = false;
    QString symbol = "(";
    if(!_opt.compare(")")) isBlock = true;
    else if(!_opt.compare("]")) { symbol = "["; isBlock = true; }

    if(isBlock)
    {
        std::reverse(operations.begin(), operations.end());

        auto founded = std::find(operations.begin(), operations.end(), symbol);
        if(founded == operations.end()) throw std::string("Syntax error");

        operands.insert(operands.end(), operations.begin(), founded);
        operations.erase(operations.begin(), founded+1);

        std::reverse(operations.begin(), operations.end());
        return;
    }

    if(!_opt.compare("(") || !_opt.compare("[")) { operations.push_back(_opt); return; }
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
    if(_opr.isEmpty()) return;

    _opr.replace("~", "-");
    operands.push_back(_opr);
}

MathExpHandler::~MathExpHandler()
{

}

double BaseOpt::operator()(double _larg, double _rarg)
{
    return function(_larg, _rarg);
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
