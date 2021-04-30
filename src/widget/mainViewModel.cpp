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
