#ifndef MD5_H
#define MD5_H

#include <string>

class MD4_5 {
public:
    MD4_5();

    ~MD4_5();

public:
    static std::string md5_digestHex16(const std::string &data);

    static std::string md5_digestHex16(const char *data, size_t size);

    static std::string md5_digestHex16(std::istream &stream);

    static std::string md4_digestHex16(const std::string &data);

    static std::string md4_digestHex16(const char *data, size_t size);

    static std::string md4_digestHex16(std::istream &stream);
};

#endif // MD5_H
