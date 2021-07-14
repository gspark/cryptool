//
// Created by Spark on 2021-07-12.
//

#ifndef CRYPTOOL_BASE64MODEL_H
#define CRYPTOOL_BASE64MODEL_H

#include <string>
#include "../pattern/abstractModel.h"

enum class EncryptEnum {
    ENCODING,
    DECODING
};

class Base64Model : public AbstractModel {
public:
    Base64Model();

private:
    std::string data;
    EncryptEnum encrypt;
public:
    void base64Data(std::string &data);
    std::string getData();
    void setEncrypt(EncryptEnum flag);
    bool isEncrypt();

    void clear();
};

#endif //CRYPTOOL_BASE64MODEL_H
