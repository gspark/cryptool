#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include "../pattern/abstractView.h"
#include "inputdata.h"
#include "hashdata.h"

class DoubleClickedButton;

class QTabWidget;

class MainView : public QWidget, public AbstractView {
Q_OBJECT

public:
    explicit MainView(QWidget *parent = nullptr);

    ~MainView() override;

public:
Q_SIGNALS:

    void calculate(MainView *view);

    void refreshView(MainView *view);

    // 线程执行结束后发送此信号
    void signalRunOver();

public:
    void refresh() override;

    HashData *getHashDataView();

    InputData *getInputDataView();

private:
    DoubleClickedButton *calcBtn;

    InputData *inputData;
    HashData *hashData;

    QTabWidget * tabWidget;

    void calcClicked();

    void calcCompleted();
};

#endif // WINDOW_H
