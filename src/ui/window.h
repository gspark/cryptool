#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include "inputdata.h"
#include "hashdata.h"


class window : public QWidget {
Q_OBJECT

public:
    explicit window(QWidget *parent = nullptr);

    ~window() override;

private:
    InputData *inputData;
    HashData *hashData;

    void calculate();

    void calculate1(std::vector<int> &hashList, const std::istringstream *iss);

    void calculate2(std::vector<int> &hashList, const std::ifstream *ifs);

    void doCalc1(const std::istringstream *iss, int i);

    void doCalc2(const std::ifstream *ifs, int i);
};

#endif // WINDOW_H
