//
// Created by Spark on 2021-04-27.
//

#ifndef CRYPTOOL_SHA_H
#define CRYPTOOL_SHA_H

#include <string>

class sha {
public:
    static std::string sha1_digestHex16(const std::string &data);

    static std::string sha1_digestHex16(const char *data, size_t size);

    static std::string sha1_digestHex16(std::istream &stream);
};


#endif //CRYPTOOL_SHA_H
