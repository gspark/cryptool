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

    static std::string md5_hmacHex(const std::string &data, const std::string &key);

    static std::string md5_hmacHex(const char *data, size_t size, const char *key, size_t key_size);

    static std::string md5_hmactHex(std::istream &stream, const std::string &key);

    static std::string md4_hmacHex(const std::string &data, const std::string &key);

    static std::string md4_hmacHex(const char *data, size_t size, const char *key, size_t key_size);

    static std::string md4_hmactHex(std::istream &stream, const std::string &key);
};

#endif // MD5_H
