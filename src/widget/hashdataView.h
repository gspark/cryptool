//
// Created by Spark on 2021-04-20.
//

#ifndef CRYPTOOL_HASHDATAVIEW_H
#define CRYPTOOL_HASHDATAVIEW_H

#include <QWidget>
#include "../pattern/abstractView.h"

QT_BEGIN_NAMESPACE
class QGridLayout;
QT_END_NAMESPACE


class HashDataView : public QWidget, public AbstractView {
Q_OBJECT

public:
    explicit HashDataView(QWidget *parent = nullptr);

    ~HashDataView() override;

public:
    void refresh() override;

    std::vector<int> getHashList();

    void clearData();

    void setHmacHashList(bool hmac);

private:
    QGridLayout *mainLayout;

    void setHashBox();
};


#endif //CRYPTOOL_HASHDATAVIEW_H
