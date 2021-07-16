//
// Created by Spark on 2021-04-27.
//

#include "sha.h"
#include "str.h"

#include <sstream>
#include <openssl/sha.h>
#include <openssl/evp.h>
#include <openssl/hmac.h>
//#include "../../logger/Logger.h"

std::string sha::sha_digestHex(const char *data, size_t size,
                               unsigned char *(*sha)(const unsigned char *, size_t, unsigned char *),
                               int digestLength) {
    if (nullptr == data || size <= 0) {
        return std::string();
    }
    unsigned char md[digestLength];
    (*sha)(reinterpret_cast<const unsigned char *>(data), size, reinterpret_cast<unsigned char *>(&md));
    return str::HexToString(md, digestLength);
}

std::string sha::sha_digestHex(std::istream &stream, void *(*EVP_sha)()) {
    auto ctx = EVP_MD_CTX_create();
    unsigned char md_value[EVP_MAX_MD_SIZE];
    unsigned int md_len = 0;

    EVP_MD_CTX_init(ctx);
#ifndef OPENSSL_IS_BORINGSSL
    EVP_MD_CTX_set_flags(ctx, EVP_MD_CTX_FLAG_NON_FIPS_ALLOW);
#endif
    EVP_MD *(*EVP_shaPtr)() = reinterpret_cast<EVP_MD *(*)()>(EVP_sha);
    EVP_DigestInit_ex(ctx, EVP_shaPtr(), nullptr);

    stream.seekg(0, std::istream::beg);
    char streamBuffer[2048];
    while (stream.good()) {
        stream.read(streamBuffer, 2048);
        auto bytesRead = stream.gcount();

        if (bytesRead > 0) {
            EVP_DigestUpdate(ctx, streamBuffer, bytesRead);
        }
    }

    EVP_DigestFinal_ex(ctx, md_value, &md_len);
    EVP_MD_CTX_destroy(ctx);

    return str::HexToString(md_value, md_len);
}

std::string sha::sha1_digestHex(const std::string &data) {
    return sha::sha1_digestHex(data.c_str(), data.size());
}

std::string sha::sha1_digestHex(const char *data, size_t size) {
//    if (nullptr == data || size <= 0) {
//        return std::string();
//    }
//    unsigned char md[SHA_DIGEST_LENGTH];
//    ::SHA1(reinterpret_cast<const unsigned char *>(data), size, reinterpret_cast<unsigned char *>(&md));
//    return str::HexToString(md, SHA_DIGEST_LENGTH);
    return sha_digestHex(data, size, ::SHA1, SHA_DIGEST_LENGTH);
}

std::string sha::sha1_digestHex(std::istream &stream) {
//    auto ctx = EVP_MD_CTX_create();
//    unsigned char md_value[EVP_MAX_MD_SIZE];
//    unsigned int md_len = 0;
//
//    EVP_MD_CTX_init(ctx);
//#ifndef OPENSSL_IS_BORINGSSL
//    EVP_MD_CTX_set_flags(ctx, EVP_MD_CTX_FLAG_NON_FIPS_ALLOW);
//#endif
//    EVP_DigestInit_ex(ctx, EVP_sha1(), nullptr);
//
//    stream.seekg(0, std::istream::beg);
//    char streamBuffer[2048];
//    while (stream.good()) {
//        stream.read(streamBuffer, 2048);
//        auto bytesRead = stream.gcount();
//
//        if (bytesRead > 0) {
//            EVP_DigestUpdate(ctx, streamBuffer, bytesRead);
//        }
//    }
//
//    EVP_DigestFinal_ex(ctx, md_value, &md_len);
//    EVP_MD_CTX_destroy(ctx);
//
//    return str::HexToString(md_value, md_len);
    return sha_digestHex(stream, reinterpret_cast<void *(*)()>(EVP_sha1));
}

std::string sha::sha256_digestHex(const std::string &data) {
    return sha::sha256_digestHex(data.c_str(), data.size());
}

std::string sha::sha256_digestHex(const char *data, size_t size) {
    return sha_digestHex(data, size, ::SHA256, SHA256_DIGEST_LENGTH);
}

std::string sha::sha256_digestHex(std::istream &stream) {
    return sha_digestHex(stream, reinterpret_cast<void *(*)()>(EVP_sha256));
}

std::string sha::sha384_digestHex(const std::string &data) {
    return sha::sha384_digestHex(data.c_str(), data.size());
}

std::string sha::sha384_digestHex(const char *data, size_t size) {
    return sha_digestHex(data, size, ::SHA384, SHA384_DIGEST_LENGTH);
}

std::string sha::sha384_digestHex(std::istream &stream) {
    return sha_digestHex(stream, reinterpret_cast<void *(*)()>(EVP_sha384));
}

std::string sha::sha512_digestHex(const std::string &data) {
    return sha::sha512_digestHex(data.c_str(), data.size());
}

std::string sha::sha512_digestHex(const char *data, size_t size) {
    return sha_digestHex(data, size, ::SHA512, SHA512_DIGEST_LENGTH);
}

std::string sha::sha512_digestHex(std::istream &stream) {
    return sha_digestHex(stream, reinterpret_cast<void *(*)()>(EVP_sha512));
}

std::string sha::sha_hmacHex(void *(*EVP_sha)(), const char *data, size_t size, const char *key, size_t key_size) {
    if (!data || !key) {
        return std::string();
    }

//    LOG_INFO << "data:" << data << " key:" << key;
//    LOG_INFO << "data_size:" << size << " key_size:" << key_size;

    unsigned char buf[EVP_MAX_MD_SIZE];
    unsigned int len;

    HMAC(static_cast<EVP_MD *>((*EVP_sha)()), key, key_size, reinterpret_cast<const unsigned char *>(data), size,
         reinterpret_cast<unsigned char *>(&buf),
         &len);
    return str::HexToString(buf, len);
}

std::string sha::sha_hmacHex(void *(*EVP_sha)(), std::istream &stream, std::string key) {
    HMAC_CTX *ctx;
    unsigned char buf[EVP_MAX_MD_SIZE];
    unsigned int len;

    ctx = HMAC_CTX_new();
    if (nullptr == ctx) {
        return std::string();
    }
    HMAC_CTX_get_md(ctx);
    HMAC_Init_ex(ctx, key.c_str(), key.size(), static_cast<EVP_MD *>((*EVP_sha)()), NULL);

    stream.seekg(0, std::istream::beg);
    char streamBuffer[2048];
    while (stream.good()) {
        stream.read(streamBuffer, 2048);
        auto bytesRead = stream.gcount();

        if (bytesRead > 0) {
            HMAC_Update(ctx, reinterpret_cast<const unsigned char *>(streamBuffer), bytesRead);
        }
    }
    HMAC_Final(ctx, buf, &len);
    HMAC_CTX_free(ctx);

    return str::HexToString(buf, len);
}

std::string sha::sha1_hmacHex(const std::string &data, const std::string &key) {
    return sha::sha1_hmacHex(data.c_str(), data.size(), key.c_str(), key.size());
}

std::string sha::sha1_hmacHex(const char *data, size_t size, const char *key, size_t key_size) {
    return sha::sha_hmacHex(reinterpret_cast<void *(*)()>(EVP_sha1), data, size, key, key_size);
}

std::string sha::sha1_hmacHex(std::istream &stream, const std::string &key) {
    return sha::sha_hmacHex(reinterpret_cast<void *(*)()>(EVP_sha1), stream, key);
}

std::string sha::sha256_hmacHex(const std::string &data, const std::string &key) {
    return sha::sha256_hmacHex(data.c_str(), data.size(), key.c_str(), key.size());
}

std::string sha::sha256_hmacHex(const char *data, size_t size, const char *key, size_t key_size) {
    return sha::sha_hmacHex(reinterpret_cast<void *(*)()>(EVP_sha256), data, size, key, key_size);
}

std::string sha::sha256_hmacHex(std::istream &stream, const std::string &key) {
    return sha::sha_hmacHex(reinterpret_cast<void *(*)()>(EVP_sha256), stream, key);
}

std::string sha::sha384_hmacHex(const std::string &data, const std::string &key) {
    return sha::sha384_hmacHex(data.c_str(), data.size(), key.c_str(), key.size());
}

std::string sha::sha384_hmacHex(const char *data, size_t size, const char *key, size_t key_size) {
    return sha::sha_hmacHex(reinterpret_cast<void *(*)()>(EVP_sha384), data, size, key, key_size);
}

std::string sha::sha384_hmacHex(std::istream &stream, const std::string &key) {
    return sha::sha_hmacHex(reinterpret_cast<void *(*)()>(EVP_sha384), stream, key);
}

std::string sha::sha512_hmacHex(const std::string &data, const std::string &key) {
    return sha::sha512_hmacHex(data.c_str(), data.size(), key.c_str(), key.size());
}

std::string sha::sha512_hmacHex(const char *data, size_t size, const char *key, size_t key_size) {
    return sha::sha_hmacHex(reinterpret_cast<void *(*)()>(EVP_sha512), data, size, key, key_size);
}

std::string sha::sha512_hmacHex(std::istream &stream, const std::string &key) {
    return sha::sha_hmacHex(reinterpret_cast<void *(*)()>(EVP_sha512), stream, key);
}

