//
// Created by Spark on 2021-04-27.
//

#ifndef CRYPTOOL_SHA_H
#define CRYPTOOL_SHA_H

#include <string>

class sha {
private:
    static std::string sha_digestHex(const char *data, size_t size,
                                     unsigned char *(*sha)(const unsigned char *d, size_t n, unsigned char *md),
                                     int digestLength);

    static std::string sha_digestHex(std::istream &stream, void *(*EVP_sha)());

public:
    static std::string sha1_digestHex(const std::string &data);

    static std::string sha1_digestHex(const char *data, size_t size);

    static std::string sha1_digestHex(std::istream &stream);

    static std::string sha256_digestHex(const std::string &data);

    static std::string sha256_digestHex(const char *data, size_t size);

    static std::string sha256_digestHex(std::istream &stream);

    static std::string sha384_digestHex(const std::string &data);

    static std::string sha384_digestHex(const char *data, size_t size);

    static std::string sha384_digestHex(std::istream &stream);

    static std::string sha512_digestHex(const std::string &data);

    static std::string sha512_digestHex(const char *data, size_t size);

    static std::string sha512_digestHex(std::istream &stream);
};


#endif //CRYPTOOL_SHA_H
