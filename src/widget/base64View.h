//
// Created by Spark on 2021-07-02.
//

#ifndef CRYPTOOL_BASE64VIEW_H
#define CRYPTOOL_BASE64VIEW_H

#include <QWidget>
#include "../pattern/abstractView.h"


QT_BEGIN_NAMESPACE
class QGridLayout;
class QPlainTextEdit;
class QCheckBox;
QT_END_NAMESPACE

class Base64View : public QWidget, public AbstractView {
Q_OBJECT

public:
    explicit Base64View(QWidget *parent = nullptr);

    ~Base64View() override;

public:
    void refresh() override;
    void setEncrypt(bool flag);
    void clearData();
private:
    QGridLayout *mainLayout;
    QCheckBox *encryptCheckBox;
    QPlainTextEdit *base64Result;

    void encryptStatus();
};


#endif //CRYPTOOL_BASE64VIEW_H
