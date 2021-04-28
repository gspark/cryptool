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

    void doCalc1(const std::istringstream *iss, int iEnum);

    void doCalc2(const std::ifstream *ifs, int iEnum);
};

#endif // WINDOW_H
