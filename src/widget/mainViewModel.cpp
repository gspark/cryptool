//
// Created by Spark on 2021-04-30.
//

#include "mainViewModel.h"

HashDataModel *MainViewModel::getHashDataModel() {
    return this->hashDataModel;
}

void MainViewModel::setHashDataModel(HashDataModel *model) {
    this->hashDataModel = model;
}

Base64Model *MainViewModel::getBase64Model() {
    return this->base64Model;
}

void MainViewModel::setBase64Model(Base64Model *model) {
    this->base64Model = model;
}
