//
// Created by Spark on 2021-04-20.
//

#include "hashdata.h"
#include "hashdataModel.h"

#include <QGridLayout>
#include <QCheckBox>
#include <QLineEdit>

HashData::HashData(QWidget *parent) :
        QWidget(parent) {
    mainLayout = new QGridLayout(this);

    mainLayout->setContentsMargins(0, 0, 0, 0);

    for (int i = 0; i < HashLength; ++i) {
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

void HashData::refresh() {
    auto *m = dynamic_cast<HashDataModel *>(this->model);
    if (nullptr == m) {
        return;
    }

    for (int i = 0; i < HashLength; ++i) {
        auto *qlineEdit = dynamic_cast<QLineEdit *>(mainLayout->itemAtPosition(i, 1)->widget());
        if (nullptr == qlineEdit) {
            continue;
        }

        if (m->hashDataMap.find(i) != m->hashDataMap.end()) {
            qlineEdit->setText(QString::fromStdString(m->hashDataMap[i]));
        }
    }
}
