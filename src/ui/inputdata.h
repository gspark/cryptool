//
// Created by Spark on 2021-04-19.
//

#ifndef CRYPTOOL_INPUTDATA_H
#define CRYPTOOL_INPUTDATA_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QLineEdit;
class QPushButton;
class QComboBox;
QT_END_NAMESPACE

class InputData : public QWidget {
Q_OBJECT

public:
    explicit InputData(QWidget *parent = nullptr);

    ~InputData() override;

private slots:
    void browse();
private:
    QLineEdit *fileName;
    QPushButton *browseButton;
    QComboBox *dataType;
};


#endif //CRYPTOOL_INPUTDATA_H
