#include "widget/mainView.h"
#include "widget/mainViewPresenter.h"

#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainView w;
    MainViewPresenter mainViewPresenter(&w);
    w.show();
    return QApplication::exec();
}
