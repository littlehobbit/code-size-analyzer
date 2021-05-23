#include <map>
#include <cmath>

#include <QRegExp>

#include "codesizeanalyzer.h"

CodeSizeAnalyzer::CodeSizeAnalyzer(const QString &code)
    : _code(code)
{}

void CodeSizeAnalyzer::countMatches(map<QString, int> &dst, const QRegularExpression &rgx)
{
    auto matchIter = rgx.globalMatch(_code);
    while (matchIter.hasNext()) {
        auto match = matchIter.next();
        QString str = match.captured();
        if (dst.count(str))
            dst[str]++;
        else
            dst[str] = 1;
    }
}

float CodeSizeAnalyzer::analyze()
{
    // Избавление от всего ненужного
    QRegExp nonImportant("\\bmain(?=[ ]*\\()|#(.*)[\r]?\n|(/\\*([^*]|[\r\n]|(\\*+([^*/]|[\r\n])))*\\*+/)|(//(.*)[\n\r])|(\\b(?:const|(?:un)?signed|long|short|int|char|float|double|(?:(?:struct|union|enum)[ ]+\\w+))+(?:[ ]*[*]+)?)");
    nonImportant.setMinimal(true);
    _code.remove(nonImportant);


    // Избавление от лишних переводов строк и табуляций
    _code.replace(QRegExp("\n|\t"), " ");
    // Избавление от лишних (от двух и более) пробелов
    _code.replace(QRegExp("[ ]{2,}"), " ");

    // Подсчитываем количество строк-операндов
    const QRegularExpression strings(R"(".*?")");
    countMatches(_countPerOperand, strings);
    _code.remove(strings);

    // Подсчитывем количество операторов
    const QRegularExpression operations(R"((?:[a-zA-Z0-9_]+)(?=[ ]*(?=\(.*\)))|;|->|\.|\(|\{|\[|\+\+|--|\+|-|\*|\/|%|&&|\|\||&|\||\^|<<|>>|~|!|==|!=|<=|>=|=|<|>)");
    countMatches(_countPerOperation, operations);

    // Удаление уже ненужных операторов
    const QRegularExpression nonOperands("(?:[a-zA-Z0-9_]+)(?=[ ]*(?=\\(.*\\)))|;|->|\\.|\\(|\\{|\\[|\\+\\+|--|\\+|-|\\*|\\/|%|&&|\\|\\||&|\\||\\^|<<|>>|~|!|==|!=|<=|>=|=|<|>|\\)|\\}|\\]|\\.|\\,");
    _code.replace(nonOperands, " ");
    _code.replace(QRegExp("[ ]{2,}"), " ");

    // Подсчитываем количество операндов
    const QRegularExpression operands("(\\S+)");
    countMatches(_countPerOperand, operands);

    const auto mapSum = [](int sum, const std::pair<QString, int> &elem) {
        return sum + elem.second;
    };

    int n = _countPerOperand.size() + _countPerOperation.size();

    int N = std::accumulate(_countPerOperand.begin(),
                            _countPerOperand.end(), 0, mapSum);

    N += std::accumulate(_countPerOperation.begin(),
                         _countPerOperation.end(), 0, mapSum);

    return N * std::log2(n);
}
