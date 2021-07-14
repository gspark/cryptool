#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include "../pattern/abstractView.h"
#include "inputdataView.h"
#include "hashdataView.h"
#include "base64View.h"
#include "mainViewModel.h"

class DoubleClickedButton;

class QTabWidget;

class MainView : public QWidget, public AbstractView {
Q_OBJECT

public:
    explicit MainView(QWidget *parent = nullptr);

    ~MainView() override;

public:
Q_SIGNALS:

    void calculate(MainView *view, CalculateEnum type);

    void refreshView(MainView *view);

    // 线程执行结束后发送此信号
    void signalRunOver();

public:
    void refresh() override;

    HashDataView *getHashDataView();

    InputDataView *getInputDataView();

private:
    DoubleClickedButton *calcBtn;

    InputDataView *inputDataView;
    HashDataView *hashDataView;

    Base64View *base64View;

    QTabWidget *tabWidget;

    void calcClicked();

    void calcCompleted();

    void currentTabChanged(int index);
};

#endif // WINDOW_H
