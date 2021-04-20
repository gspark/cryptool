//
// Created by Spark on 2021-04-20.
//

#include "hashdata.h"

#include <QGridLayout>
#include <QCheckBox>
#include <QLineEdit>

HashData::HashData(QWidget *parent) :
        QWidget(parent) {
    mainLayout = new QGridLayout(this);

    mainLayout->setContentsMargins(0, 0, 0, 0);

    unsigned int len = sizeof(HashEnumStrings) / sizeof(HashEnumStrings[0]);
    for (int i = 0; i < len; ++i) {
        mainLayout->addWidget(new QCheckBox(tr(HashEnumStrings[i])), i, 0);
        auto qlineEdit = new QLineEdit;
        qlineEdit->setReadOnly(true);
        mainLayout->addWidget(qlineEdit, i, 1);
    }
}

HashData::~HashData() = default;

std::vector<int> HashData::getHashList() {
    std::vector<int> ret;

    for (int i = 0; i < mainLayout->rowCount(); ++i) {
        auto *cb = dynamic_cast<QCheckBox *>(mainLayout->itemAtPosition(i, 0)->widget());
        if (cb->isChecked()) {
            ret.push_back(i);
        }
    }

    return ret;
}

void HashData::setHashData(HashEnum hashEnum, std::string &data) {
    int ihash = static_cast<int>(hashEnum);
    auto *qlineEdit = dynamic_cast<QLineEdit *>(mainLayout->itemAtPosition(ihash, 1)->widget());
    qlineEdit->setText(QString::fromStdString(data));
}
