#include <iostream>
#include <map>
#include <cmath>

#include <QFile>
#include <QTextStream>

#include "codesizeanalyzer.h"

void printUsage()
{
    std::cout << "Usage: " << std::endl
              << "\tCodeAnalyzer filename.c[pp]" << std::endl;
}

int main(int argc, char *argv[])
{
    if (argc == 2) {
        QFile code(argv[1]);
        code.open(QIODevice::Text | QIODevice::ReadOnly);

        if (!code.isOpen()) {
            std::cout << "Can't open file." << std::endl;
            printUsage();
            return 1;
        }
        std::cout << "Input file: " << argv[1] << std::endl;
        QTextStream fileStream(&code);
        CodeSizeAnalyzer codeAnalayzer(fileStream.readAll());
        std::cout << "Size = " << codeAnalayzer.analyze() << std::endl;
        return 0;
    } else {
        std::cout << "Incorrect arguments number" << std::endl;
        printUsage();
        return 1;
    }
}
