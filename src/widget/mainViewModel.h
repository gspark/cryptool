//
// Created by Spark on 2021-04-30.
//

#ifndef CRYPTOOL_MAINVIEWMODEL_H
#define CRYPTOOL_MAINVIEWMODEL_H


#include "../pattern/abstractModel.h"

class HashDataModel;
class Base64Model;

enum class CalculateEnum {
    hash,
    base64
};

static const char *calculateEnumStrings[] = {"hash", "Base64"};

class MainViewModel : public AbstractModel {

private:
    HashDataModel *hashDataModel;
    Base64Model *base64Model;
public:
    HashDataModel *getHashDataModel();
    Base64Model *getBase64Model();

    void setHashDataModel(HashDataModel *model);
    void setBase64Model(Base64Model *model);
};


#endif //CRYPTOOL_MAINVIEWMODEL_H
