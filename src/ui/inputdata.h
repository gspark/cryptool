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
class QGridLayout;
QT_END_NAMESPACE

class InputData : public QWidget {
Q_OBJECT

public:
    explicit InputData(QWidget *parent = nullptr);
    ~InputData() override;

public:
    const std::string dataType[2] = { "File" , "Text string" };
    std::string getData();

private slots:
    void browse();
    void setDateType(int index);
private:
    QGridLayout *mainLayout;

    QLineEdit *fileName;
    QPushButton *browseButton;
    QComboBox *dataTypeCbBox;

    QLineEdit *dataLineEdit;

    void initDateType();
};


#endif //CRYPTOOL_INPUTDATA_H
