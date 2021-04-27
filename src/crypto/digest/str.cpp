//
// Created by Spark on 2021-04-27.
//

#include "str.h"
#include <sstream>

std::string str::HexToString(const unsigned char *data, size_t size) {
    static const char hex[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
    std::stringstream ss;
    for (size_t i = 0; i < size; ++i)
        ss << hex[(data[i] >> 4)] << hex[(data[i] & 0x0F)];
    return ss.str();
}
