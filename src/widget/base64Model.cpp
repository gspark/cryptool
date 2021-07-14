//
// Created by Spark on 2021-07-12.
//

#include "base64Model.h"

void Base64Model::base64Data(std::string &data) {
    this->data = data;
}

void Base64Model::clear() {
    this->data = std::string();
}
