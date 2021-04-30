//
// Created by Spark on 2021-04-29.
//

#include "hashdataModel.h"

void HashDataModel::setHashData(HashEnum hashEnum, std::string &data) {
    int code = static_cast<int>(hashEnum);
    hashDataMap[code] = data;

//    auto *qlineEdit = dynamic_cast<QLineEdit *>(mainLayout->itemAtPosition(code, 1)->widget());
//    qlineEdit->setText(QString::fromStdString(data));
}

void HashDataModel::clear() {
    hashDataMap.clear();
}
