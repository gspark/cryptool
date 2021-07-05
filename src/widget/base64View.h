//
// Created by Spark on 2021-07-02.
//

#ifndef CRYPTOOL_BASE64VIEW_H
#define CRYPTOOL_BASE64VIEW_H

#include <QWidget>
#include "../pattern/abstractView.h"


QT_BEGIN_NAMESPACE
class QGridLayout;
class QTextEdit;
class QCheckBox;
QT_END_NAMESPACE

class Base64View : public QWidget, public AbstractView {
Q_OBJECT

public:
    explicit Base64View(QWidget *parent = nullptr);

    ~Base64View() override;

public:
    void refresh() override;

private:
    QGridLayout *mainLayout;
    QCheckBox *encryptCheckBox;
    QTextEdit *base64Result;

    void encryptStatus();
};


#endif //CRYPTOOL_BASE64VIEW_H
