//
// Created by Spark on 2021-04-27.
//

#include "str.h"
#include <sstream>
#include <cstring>

std::string str::HexToString(const unsigned char *data, size_t size, bool uppercase) {
    static const char lower_hex[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
    static const char upper_hex[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

    std::stringstream ss;
    char *hex = const_cast<char *>(lower_hex);
    if (uppercase) {
        hex = const_cast<char *>(upper_hex);
    }
    for (size_t i = 0; i < size; ++i)
        ss << hex[(data[i] >> 4)] << hex[(data[i] & 0x0F)];
    return ss.str();
}

std::string str::LongToHex(unsigned long entier) {
    char str[50];
    memset(str, 0, sizeof(str));
    sprintf(str, "%x", entier);
    return str;
}
