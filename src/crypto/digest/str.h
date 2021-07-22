//
// Created by Spark on 2021-04-27.
//

#ifndef CRYPTOOL_STR_H
#define CRYPTOOL_STR_H

#include <string>

class str {

public:
    static std::string HexToString(const unsigned char *data, size_t size, bool uppercase = false);

    static std::string LongToHex(unsigned long entier);
};


#endif //CRYPTOOL_STR_H
