#include "mathexphandler.hpp"

MathExpHandler::MathExpHandler()
{

}

void MathExpHandler::setFormatString(QString formula)
{
    format = formula;
}

void MathExpHandler::processing()
{
    stringConversion();

    for(auto item : operands)
    {
        std::cout << item.toStdString() + " ";
    }

    std::cout << std::endl;
}



double MathExpHandler::getFinally() const
{
    return finally;
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
    if(!operations.empty() && weightOpt[_opt] <= weightOpt[operations.back()])
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
        if(weightOpt.find(symbol) != weightOpt.end())
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

MathExpHandler::~MathExpHandler()
{

}
