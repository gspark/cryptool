#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include "inputdata.h"

QT_BEGIN_NAMESPACE
class QDialogButtonBox;
class QFormLayout;
QT_END_NAMESPACE

class window : public QWidget
{
    Q_OBJECT

public:
    explicit window(QWidget *parent = nullptr);
    ~window() override;
private:
    QDialogButtonBox *buttonBox;
    QFormLayout *formLayout;
    InputData *selectFile;

    void createFormGroupBox();

    void calculate();
};
#endif // WINDOW_H
