#include <qsolver.hpp>

#include <util/from_string.hpp>

#include <iostream>
#include <exception>
#include <string>

#include <cstdlib>
#include <cstring>

using TReal = long double;

using std::cout;
using std::cerr;
using std::endl;

struct TArguments {
    std::vector<TReal> Coefficients;
    TReal Precision{0};

    bool HelpOptionIsSet{false};

    bool Validate() const {
        if (Coefficients.size() != 3) {
            cerr << "Wrong coefficients count: 3 expected, but " << Coefficients.size() << " given." << endl;
            return false;
        }
        if (Precision < 0) {
            cerr << "Precision is less than zero." << endl;
            return false;
        }
        return true;
    }
};

int TryParseHelpOption(int argc, char* argv[]) {
    if (strcmp(argv[0], "-h") != 0 && strcmp(argv[0], "--help") != 0) {
        return 0;
    }

    return 1;
}

int TryParsePrecisionOption(int argc, char* argv[], TReal& precision) {
    if (argc < 2) {
        return 0;
    }

    if (strcmp(argv[0], "-p") != 0 && strcmp(argv[0], "--precision") != 0) {
        return 0;
    }

    try {
        precision = NUtil::ParseFromString<TReal>(argv[1]);
    } catch (const NUtil::TParsingException& exception) {
        return 0;
    }

    return 2;
}

int TryParseCoefficientOption(int argc, char* argv[], TReal& coefficient) {
    try {
        coefficient = NUtil::ParseFromString<TReal>(argv[0]);
    } catch (const NUtil::TParsingException& exception) {
        return 0;
    }

    return 1;
}

bool ParseArguments(int argc, char* argv[], TArguments& arguments) {
    int parsedOptionsCount;
    while (argc > 0) {
        TReal precision;
        TReal newCoefficient;
        if ((parsedOptionsCount = TryParseHelpOption(argc, argv))) {
            arguments.HelpOptionIsSet = true;
        } else if ((parsedOptionsCount = TryParsePrecisionOption(argc, argv, precision))) {
            arguments.Precision = precision;
        } else if ((parsedOptionsCount = TryParseCoefficientOption(argc, argv, newCoefficient))) {
            arguments.Coefficients.push_back(newCoefficient);
        } else {
            cerr << "Couldn't parse argument " << argv[0] << endl;
            return false;
        }

        argc -= parsedOptionsCount;
        argv += parsedOptionsCount;
    }

    return true;
}

void PrintUsage(const std::string& runCommand) {
    cout << "usage: " << runCommand << " [-h] [-p] A B C" << endl;
    cout << endl;
    cout << "Solve a quadratic equation in form A * x^2 + B * x + C = 0" << endl;
    cout << "Print newline-separated roots of the equation." << endl;
    cout << endl;
    cout << "positional arguments:" << endl;
    cout << " A, B, C     coefficients of the equation" << endl;
    cout << endl;
    cout << "optional arguments:" << endl;
    cout << " -h, --help  show this help message and exit" << endl;
    cout << " -p, --precision set real numbers compare precision" << endl;
}

int main(int argc, char* argv[]) {
    const std::string runCommand = argv[0];

    TArguments runArguments;
    if (!ParseArguments(argc - 1, argv + 1, runArguments)) {
        PrintUsage(argv[0]);
        return EXIT_FAILURE;
    }

    if (runArguments.HelpOptionIsSet) {
        PrintUsage(argv[0]);
        return EXIT_SUCCESS;
    }

    if (!runArguments.Validate()) {
        return EXIT_FAILURE;
    }

    NQSolver::TRoots<long double> roots;
    try {
        roots = NQSolver::SolveQuadraticEquation<TReal>(
                runArguments.Coefficients[2],
                runArguments.Coefficients[1],
                runArguments.Coefficients[0],
                runArguments.Precision
        );
    } catch(std::exception& exception) {
        cerr << exception.what() << endl;
        return EXIT_FAILURE;
    }

    for (const auto root : roots) {
        cout << root << endl;
    }
    return EXIT_SUCCESS;
}
