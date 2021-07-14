//
// Created by Spark on 2021-07-12.
//

#include "base64Model.h"

Base64Model::Base64Model() : encrypt( EncryptEnum::ENCODING) {}

void Base64Model::base64Data(std::string &data) {
    this->data = data;
}

void Base64Model::clear() {
    this->data = std::string();
}

bool Base64Model::isEncrypt() {
    return this->encrypt == EncryptEnum::ENCODING;
}

void Base64Model::setEncrypt(EncryptEnum flag) {
    this->encrypt = flag;
}

std::string Base64Model::getData() {
    return this->data;
}
