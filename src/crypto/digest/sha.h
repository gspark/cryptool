//
// Created by Spark on 2021-04-27.
//

#ifndef CRYPTOOL_SHA_H
#define CRYPTOOL_SHA_H

#include <string>

class sha {
private:
    static std::string sha_digestHex16(const char *data, size_t size,
                                       unsigned char *(*sha)(const unsigned char *d, size_t n, unsigned char *md),
                                       int digestLength);

    static std::string sha_digestHex16(std::istream &stream, void *(*EVP_sha)());

public:
    static std::string sha1_digestHex16(const std::string &data);

    static std::string sha1_digestHex16(const char *data, size_t size);

    static std::string sha1_digestHex16(std::istream &stream);

    static std::string sha256_digestHex16(const std::string &data);

    static std::string sha256_digestHex16(const char *data, size_t size);

    static std::string sha256_digestHex16(std::istream &stream);

    static std::string sha384_digestHex16(const std::string &data);

    static std::string sha384_digestHex16(const char *data, size_t size);

    static std::string sha384_digestHex16(std::istream &stream);

    static std::string sha512_digestHex16(const std::string &data);

    static std::string sha512_digestHex16(const char *data, size_t size);

    static std::string sha512_digestHex16(std::istream &stream);
};


#endif //CRYPTOOL_SHA_H
