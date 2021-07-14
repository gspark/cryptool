//
// Created by Spark on 2021-07-12.
//

#ifndef CRYPTOOL_BASE64MODEL_H
#define CRYPTOOL_BASE64MODEL_H

#include <string>
#include "../pattern/abstractModel.h"

class Base64Model : public AbstractModel {
public:
    std::string data;
public:
    void base64Data(std::string &data);
    void clear();
};

#endif //CRYPTOOL_BASE64MODEL_H
