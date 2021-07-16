//
// Created by Spark on 2021-04-19.
//

#ifndef CRYPTOOL_INPUTDATAVIEW_H
#define CRYPTOOL_INPUTDATAVIEW_H

#include <QWidget>
#include <istream>

QT_BEGIN_NAMESPACE

class QLineEdit;

class QPlainTextEdit;

class QPushButton;

class QComboBox;

class QGridLayout;

class QCheckBox;

QT_END_NAMESPACE

class InputDataView : public QWidget {
Q_OBJECT

public:
    explicit InputDataView(QWidget *parent = nullptr);

    ~InputDataView() override;

public:
    const std::string dataType[2] = {"File", "Text string"};

    std::istream *getData();

    bool dateTypeIsFile();

    std::string *getHmacKey();

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

    QPlainTextEdit *dataLineEdit;

    QCheckBox *hmacCheckBox;

    QLineEdit *hmacKey;

    void initDateType(int currentIdx);
};


#endif //CRYPTOOL_INPUTDATAVIEW_H
