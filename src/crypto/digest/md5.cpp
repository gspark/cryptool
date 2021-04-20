//
// Created by Spark on 2021-04-15.
//

#include "md5.h"
#include <string>
#include <sstream>

#include <openssl/md5.h>


MD5::MD5() = default;

MD5::~MD5() = default;


std::string MD5::HexToString(const unsigned char *data, size_t size) {
    static char hex[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
    std::stringstream ss;
    for (size_t i = 0; i < size; i++)
        ss << hex[(data[i] >> 4)] << hex[(data[i] & 0x0F)];
    return ss.str();

}

std::string MD5::digestHex16(const std::string &data) {
    return digestHex16(data.c_str(), data.size());
}

std::string MD5::digestHex16(const char *data, size_t size) {
    if (!data) {
        return "";
    }

    unsigned char md[MD5_DIGEST_LENGTH];
    ::MD5(reinterpret_cast<const unsigned char *>(data), size, reinterpret_cast<unsigned char *>(&md));

    return HexToString(md, MD5_DIGEST_LENGTH);
}
