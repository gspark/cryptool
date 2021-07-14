//
// Created by Spark on 2021-04-29.
//

#ifndef CRYPTOOL_MAINVIEWPRESENTER_H
#define CRYPTOOL_MAINVIEWPRESENTER_H

#include <QObject>
#include "../pattern/abstractPresenter.h"
#include "mainViewModel.h"


#include <sstream>
#include <fstream>

class MainView;

class MainViewModel;

class MainViewPresenter : public AbstractPresenter, public QObject {

public:
    explicit MainViewPresenter(AbstractView *view, AbstractModel *model = nullptr);

    ~MainViewPresenter() override;

public:

private:
    void calculate(MainView *v, CalculateEnum type);

    void hashCalc(MainView *view, std::istream *data_ptr);

    void base64Calc(MainView *view, std::istream *data_ptr);

    void doCalc1(const std::istringstream *iss, int iEnum);

    void doCalc2(const std::ifstream *ifs, int iEnum);

    void doBase64Calc1(const std::istringstream *iss);

    void doBase64Calc2(const std::ifstream *ifs);
};


#endif //CRYPTOOL_MAINVIEWPRESENTER_H
