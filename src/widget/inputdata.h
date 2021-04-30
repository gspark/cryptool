//
// Created by Spark on 2021-04-19.
//

#ifndef CRYPTOOL_INPUTDATA_H
#define CRYPTOOL_INPUTDATA_H

#include <QWidget>
#include <istream>

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
    const std::string dataType[2] = {"File", "Text string"};

    std::istream *getData();

public :
Q_SIGNALS:

    void dataTypeChanged();

    void dataChanged();

private slots:

    void browse();

    void setDateType(int index);

private:
    QGridLayout *mainLayout;

    QLineEdit *fileName;
    QPushButton *browseButton;
    QComboBox *dataTypeCbBox;

    QLineEdit *dataLineEdit;

    void initDateType(int currentIdx);
};


#endif //CRYPTOOL_INPUTDATA_H
