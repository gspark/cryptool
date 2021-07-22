//
// Created by Spark on 2021-04-29.
//

#ifndef CRYPTOOL_HASHDATAMODEL_H
#define CRYPTOOL_HASHDATAMODEL_H

#include "../pattern/abstractModel.h"

#include <string>
#include <map>

enum class HashEnum {
    MD5,
    MD4,
    SHA1,
    SHA256,
    SHA384,
    SHA512,
    SM3,
    CRC32
};

static const char *HashEnumStrings[] = {"MD5", "MD4", "SHA1", "SHA256", "SHA384", "SHA512", "SM3", "CRC32"};

static const unsigned int HashLength = sizeof(HashEnumStrings) / sizeof(HashEnumStrings[0]);

class HashDataModel : public AbstractModel {
public:
    std::map<int, std::string> hashDataMap;
public:
    void setHashData(HashEnum hashEnum, std::string &data);

    void clear();
};


#endif //CRYPTOOL_HASHDATAMODEL_H
