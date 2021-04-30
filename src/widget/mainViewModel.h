//
// Created by Spark on 2021-04-30.
//

#ifndef CRYPTOOL_MAINVIEWMODEL_H
#define CRYPTOOL_MAINVIEWMODEL_H


#include "../pattern/abstractModel.h"

class HashDataModel;

class MainViewModel : public AbstractModel {

private:
    HashDataModel *hashDataModel;

public:
    HashDataModel *getHashDataModel();

    void setHashDataModel(HashDataModel *model);
};


#endif //CRYPTOOL_MAINVIEWMODEL_H
