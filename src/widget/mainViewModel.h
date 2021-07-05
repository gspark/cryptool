//
// Created by Spark on 2021-04-30.
//

#ifndef CRYPTOOL_MAINVIEWMODEL_H
#define CRYPTOOL_MAINVIEWMODEL_H


#include "../pattern/abstractModel.h"

class HashDataModel;

enum class CalculateEnum {
    hash,
    base64
};

static const char *calculateEnumStrings[] = {"hash", "base64"};

class MainViewModel : public AbstractModel {

private:
    HashDataModel *hashDataModel;

public:
    HashDataModel *getHashDataModel();

    void setHashDataModel(HashDataModel *model);
};


#endif //CRYPTOOL_MAINVIEWMODEL_H
