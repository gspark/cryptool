//
// Created by Spark on 2021-07-06.
//

#ifndef CRYPTOOL_BASE64_H
#define CRYPTOOL_BASE64_H


class Base64 {
public:
    Base64();

    virtual ~Base64();

public:
    static std::string encode(const std::string &data);

    static std::string encode(const char *data, int size);
};


#endif //CRYPTOOL_BASE64_H
