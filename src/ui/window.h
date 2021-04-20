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
};

#endif // WINDOW_H
