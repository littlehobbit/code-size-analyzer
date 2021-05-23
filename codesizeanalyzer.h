#ifndef CODESIZEANALYZER_H
#define CODESIZEANALYZER_H

#include <QString>
#include <QRegularExpression>
#include <map>

using std::map;

class CodeSizeAnalyzer
{
public:
    CodeSizeAnalyzer(const QString &code);

    float analyze();

private:
    void countMatches(map<QString, int> &dst, const QRegularExpression &rgx);

    QString _code;
    map<QString, int> _countPerOperand;
    map<QString, int> _countPerOperation;
};

#endif // CODESIZEANALYZER_H
