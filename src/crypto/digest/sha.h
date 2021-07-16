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

    static std::string sha_hmacHex(void *(*EVP_sha)(), const char *data, size_t size, const char *key, size_t key_size);

    static std::string sha_hmacHex(void *(*EVP_sha)(), std::istream &stream, std::string key);

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

    static std::string sha1_hmacHex(const std::string &data, const std::string &key);

    static std::string sha1_hmacHex(const char *data, size_t size, const char *key, size_t key_size);

    static std::string sha1_hmacHex(std::istream &stream, const std::string &key);

    static std::string sha256_hmacHex(const std::string &data, const std::string &key);

    static std::string sha256_hmacHex(const char *data, size_t size, const char *key, size_t key_size);

    static std::string sha256_hmacHex(std::istream &stream, const std::string &key);

    static std::string sha384_hmacHex(const std::string &data, const std::string &key);

    static std::string sha384_hmacHex(const char *data, size_t size, const char *key, size_t key_size);

    static std::string sha384_hmacHex(std::istream &stream, const std::string &key);

    static std::string sha512_hmacHex(const std::string &data, const std::string &key);

    static std::string sha512_hmacHex(const char *data, size_t size, const char *key, size_t key_size);

    static std::string sha512_hmacHex(std::istream &stream, const std::string &key);
};


#endif //CRYPTOOL_SHA_H
