//
// Created by Spark on 2021-04-20.
//

#include "hashdataView.h"
#include "hashdataModel.h"
#include "../config.h"

#include <QGridLayout>
#include <QCheckBox>
#include <QLineEdit>

HashDataView::HashDataView(QWidget *parent) :
        QWidget(parent) {
    mainLayout = new QGridLayout(this);

//    mainLayout->setContentsMargins(0, 0, 0, 0);

    for (int i = 0; i < HashLength; ++i) {
        mainLayout->addWidget(new QCheckBox(tr(HashEnumStrings[i])), i, 0);
        auto qLineEdit = new QLineEdit;
        qLineEdit->setReadOnly(true);
        mainLayout->addWidget(qLineEdit, i, 1);
    }
    setHashBox();
}

HashDataView::~HashDataView() {

    std::string s;

    int len = mainLayout->rowCount() - 1;
    for (int i = 0; i < len; ++i) {
        auto *cb = dynamic_cast<QCheckBox *>(mainLayout->itemAtPosition(i, 0)->widget());
        if (cb->isChecked()) {
            s.append(std::to_string(i)).append(",");
        }
    }
    auto *cb = dynamic_cast<QCheckBox *>(mainLayout->itemAtPosition(len, 0)->widget());
    if (cb->isChecked()) {
        s.append(std::to_string(len));
    }

    ConfigIni::getInstance().iniWrite(QStringLiteral("Hash/data"), QString::fromStdString(s));
}

std::vector<int> HashDataView::getHashList() {
    std::vector<int> ret;

    for (int i = 0; i < mainLayout->rowCount(); ++i) {
        auto *cb = dynamic_cast<QCheckBox *>(mainLayout->itemAtPosition(i, 0)->widget());
        if (cb->isChecked() && cb->isVisible()) {
            ret.push_back(i);
        }
    }

    return ret;
}

void HashDataView::setHashBox() {
    auto s = ConfigIni::getInstance().iniRead(QStringLiteral("Hash/data"), "").toString();
    if (s.isEmpty()) {
        return;
    }
    for (int i = 0; i < mainLayout->rowCount(); ++i) {
        auto *cb = dynamic_cast<QCheckBox *>(mainLayout->itemAtPosition(i, 0)->widget());
        if (s.contains(QString::number(i), Qt::CaseInsensitive)) {
            cb->setCheckState(Qt::Checked);
        }
    }
}


void HashDataView::refresh() {
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

void HashDataView::clearData() {
    for (int i = 0; i < HashLength; ++i) {
        auto *qLineEdit = dynamic_cast<QLineEdit *>(mainLayout->itemAtPosition(i, 1)->widget());
        if (nullptr == qLineEdit) {
            continue;
        }
        qLineEdit->clear();
    }
}

void HashDataView::setHmacHashList(bool hmac) {
    if (hmac) {
        for (int i = HashLength - 2; i < HashLength; ++i) {
            mainLayout->itemAtPosition(i,0)->widget()->hide();
            mainLayout->itemAtPosition(i,1)->widget()->hide();
        }
    } else {
        for (int i = HashLength - 2; i < HashLength; ++i) {
            mainLayout->itemAtPosition(i,0)->widget()->show();
            mainLayout->itemAtPosition(i,1)->widget()->show();
        }
    }
}
