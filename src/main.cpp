#include "widget/mainView.h"
#include "widget/mainViewPresenter.h"
#include "logger/Logger.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    Logger::initLog();

    MainView w;
    MainViewPresenter mainViewPresenter(&w);
    w.show();
    return QApplication::exec();
}
