//
// Created by Spark on 2021-04-20.
//

#ifndef CRYPTOOL_HASHDATA_H
#define CRYPTOOL_HASHDATA_H

#include <QWidget>
#include "../pattern/abstractView.h"

QT_BEGIN_NAMESPACE
class QGridLayout;
QT_END_NAMESPACE


class HashData : public QWidget, public AbstractView {
Q_OBJECT

public:
    explicit HashData(QWidget *parent = nullptr);

    ~HashData() override;

public:
    void refresh() override;

    std::vector<int> getHashList();

    void clearData();

private:
    QGridLayout *mainLayout;

    void setHashBox();
};


#endif //CRYPTOOL_HASHDATA_H
