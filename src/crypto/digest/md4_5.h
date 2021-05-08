#ifndef MD5_H
#define MD5_H

#include <string>

class MD4_5 {
public:
    MD4_5();

    ~MD4_5();

public:
    static std::string md5_digestHex(const std::string &data);

    static std::string md5_digestHex(const char *data, size_t size);

    static std::string md5_digestHex(std::istream &stream);

    static std::string md4_digestHex(const std::string &data);

    static std::string md4_digestHex(const char *data, size_t size);

    static std::string md4_digestHex(std::istream &stream);
};

#endif // MD5_H
