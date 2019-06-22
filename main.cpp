#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>
#include <cmath>
#include <exception>


using namespace std;

class ReadFile {
public:
    size_t GetExampleNumber(string path) {
        size_t ex_numb;
        ifstream fin;
        fin.open(path, ios_base::in);
        if (fin.is_open()) {
            fin >> ex_numb;
            fin.close();
            return ex_numb;

        } else {
            throw exception(ios_base::failure);
        }
    }

    string GetExample(string path) {
        int a = 1;
        string str;
        ifstream fin(path);
        if (fin.is_open()) {
            while (!fin.eof()) {
                getline(fin, str);
                if (a == 2) break;
                ++a;
            }
            fin.close();
            return str;

        } else {
            throw exception(ios_base::failure);
        }
    }

};

class Parser {
public:
    double *ParseringNumbs(string example) {
        size_t length_ex = example.length();
        double *result = new double[length_ex];
        int num = 0;
        bool neg = false;
        string sty;
        int i = 0, j = 0;
        for (int k = 0; k < length_ex; k++) {
            result[k] = 0;
        }

        while ((i < length_ex)) {
            if (isdigit(example[i]) && i > 0) {

                if (example[i - 1] == '-') {
                    neg = true;
                }
            }

            while (isdigit(example[i])) {
                i++;
            }
            if (i > j) {
                sty = example.substr(j, i - j);
                if (neg == false) {
                    result[num] = stoi(sty);
                } else {
                    result[num] = stoi(sty)*(-1);
                    neg=false;
                }
                num++;
            } else if (example[i] == 'x') {

                result[num] = 1;
                num++;
            }
            if ((example[i] == 'x') && (isdigit(example[i + 1]))) {
                i += 2; //перепрыгиваем икс и степень
            } else i++;
            j = i;
        }

        return result;
    }

};


class ExSolutionInterface {
public:
    virtual double *solution(string ex) = 0;
};

class ExSolution1 : public ExSolutionInterface {
    Parser parser;
public:
    double *solution(string example) override {
        double *answ = new double[2];
        int *var = parser.ParseringNumbs(example);
        double D, x1, x2;
        double a = var[0], b = var[1], c = var[2] - var[3];

        D = b * b - 4 * a * c;
        if (D < 0) {
            throw IRRD;
            throw exception("Irrational radical");
        }
        x1 = (-b - sqrt(D)) / (2 * a);
        x2 = (-b + sqrt(D)) / (2 * a);
        answ[0] = x1;
        answ[1] = x2;
        return answ;
    }
};

class ExSolution2 : public ExSolutionInterface {
    Parser parser;
public:
    double *solution(string example) override {
        double *answ = new double[1];
        int *var = parser.ParseringNumbs(example);
        string *oop = parser.ParseringOps(example);
        answ[0] = var[0] + var[1];
        return answ;
    }
};

class ExSolution3 : public ExSolutionInterface {
    Parser parser;
public:
    double *solution(string example) override {
        double *answ = new double[1];
        int *var = parser.ParseringNumbs(example);
        string *oop = parser.ParseringOps(example);
        answ[0] = var[0] - var[1];
        return answ;
    }
};

class ExSolution4 : public ExSolutionInterface {
    Parser parser;
public:
    double *solution(string example) override {
        double *answ = new double[1];
        int *var = parser.ParseringNumbs(example);
        string *oop = parser.ParseringOps(example);
        answ[0] = var[0] * var[1];
        return answ;
    }

};

class ExSolution5 : public ExSolutionInterface {
    Parser parser;
public:
    double *solution(string example) override {
        double *answ = new double[1];
        double x1,x2;
        int *var = parser.ParseringNumbs(example);
        string *oop = parser.ParseringOps(example);
        try
        {
            if (var[1] == 0)throw 2;
        }
        catch(int i)
        {
            cout << "Ошибка №" << i << " - на 0 делить нельзя!!!!" << endl;
        }
        x1 = var[0];
        x2 = var[1];
        answ[0] = x1/x2;

        return answ;
    }

};

class SolutionsLib {
private:
    vector<ExSolutionInterface *> allSolutions;

public:

    void addSolution(ExSolutionInterface *solution) {
        allSolutions.push_back(solution);
    }

    ExSolutionInterface *returnSolution(int exNumb) {
        return allSolutions[exNumb - 1];

    }
};

class Printer {
public:
    void print(double *answ, int ex_numb, string example) {
        if (ex_numb == 1) {
            cout << example << endl;
            if (answ == 0) {
                cout << " корней нет" << endl;
            } else {
                cout << "x1 = " << answ[0] << endl << "x2 = " << answ[1] << endl;
            }
        } else {
            if (answ == 0) {
                cout << "нет решения" << endl;
            } else {
                cout << example << " = " << answ[0] << endl;
            }
        };
    }

};

class Calculator {
    SolutionsLib *solutionsLib;
    ReadFile reader;
    Printer printer;

public:
    Calculator(SolutionsLib *solutionsLib, ReadFile reader, Printer printer)
            : solutionsLib(solutionsLib), reader(reader), printer(printer) {
    }

    ExSolutionInterface *setSolution(string path) {
        size_t exNumb = reader.GetExampleNumber(path);
        return solutionsLib->returnSolution(exNumb);
    }

    void calcSolution(string path) {
        ExSolutionInterface *exSolution;
        exSolution = setSolution(path);
        double *answ = exSolution->solution(reader.GetExample(path));
        printer.print(answ, reader.GetExampleNumber(path), reader.GetExample(path));
    }

};

int main() {
    ReadFile readFile;
    Printer printer;
    string path1 = "C:/cprojects/Repositories/kateBekk/kateBekk-primerchiki/files/f1";
    string path2 = "C:/cprojects/Repositories/kateBekk/kateBekk-primerchiki/files/f2";
    string path3= "C:/cprojects/Repositories/kateBekk/kateBekk-primerchiki/files/f3";
    string path4 = "C:/cprojects/Repositories/kateBekk/kateBekk-primerchiki/files/f4";
    string path5 = "C:/cprojects/Repositories/kateBekk/kateBekk-primerchiki/files/f5";
    SolutionsLib solutionsLib;
    ExSolution1 exSol1;
    ExSolution2 exSol2;
    ExSolution3 exSol3;
    ExSolution4 exSol4;
    ExSolution5 exSol5;
    solutionsLib.addSolution(&exSol1);
    solutionsLib.addSolution(&exSol2);
    solutionsLib.addSolution(&exSol3);
    solutionsLib.addSolution(&exSol4);
    solutionsLib.addSolution(&exSol5);

    Calculator calculator(&solutionsLib, readFile, printer);
    calculator.calcSolution(path1);
    calculator.calcSolution(path2);
    calculator.calcSolution(path3);
    calculator.calcSolution(path4);
    calculator.calcSolution(path5);


    return 0;

}