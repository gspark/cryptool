#ifndef MD5_H
#define MD5_H

#include <string>

class MD5 {
public:
    MD5();

    ~MD5();

public:
    std::string digestHex16(const std::string &data);

    std::string digestHex16(const char *data, size_t size);

    std::string digestHex16(std::istream &stream);

    static std::string HexToString(const unsigned char *data, size_t size);
};

#endif // MD5_H
