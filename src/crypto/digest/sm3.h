//
// Created by Spark on 2021-05-08.
//

#ifndef CRYPTOOL_SM3_H
#define CRYPTOOL_SM3_H


#include <string>

class SM3 {
public:
    SM3();

    ~SM3();

public:
    static std::string sm3_digestHex(const std::string &data);

    static std::string sm3_digestHex(const char *data, size_t size);

    static std::string sm3_digestHex(std::istream &stream);
};


#endif //CRYPTOOL_SM3_H
