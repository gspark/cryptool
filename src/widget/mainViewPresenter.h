//
// Created by Spark on 2021-04-29.
//

#ifndef CRYPTOOL_MAINVIEWPRESENTER_H
#define CRYPTOOL_MAINVIEWPRESENTER_H

#include <QObject>
#include "../pattern/abstractPresenter.h"


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
    void calculate(MainView *v);

    void doCalc1(const std::istringstream *iss, int iEnum);

    void doCalc2(const std::ifstream *ifs, int iEnum);
};


#endif //CRYPTOOL_MAINVIEWPRESENTER_H
