#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include "../pattern/abstractView.h"
#include "inputdata.h"
#include "hashdata.h"


class MainView : public QWidget, public AbstractView {
Q_OBJECT

public:
    explicit MainView(QWidget *parent = nullptr);

    ~MainView() override;

public:
Q_SIGNALS:

    void calculate(MainView *view);

    void refreshView(MainView *view);

public:
    void refresh() override;

    HashData *getHashDataView();

    InputData *getInputDataView();

private:
    QPushButton *calcBtn;

    InputData *inputData;
    HashData *hashData;

    void calcClicked();

    void calcCompleted();
};

#endif // WINDOW_H
