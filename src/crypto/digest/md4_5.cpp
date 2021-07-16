//
// Created by Spark on 2021-04-15.
//

#include "md4_5.h"
#include <string>
#include <sstream>

#include "str.h"
#include <openssl/md5.h>
#include <openssl/md4.h>
#include <openssl/evp.h>
#include <openssl/hmac.h>
//#include "../../logger/Logger.h"


MD4_5::MD4_5() = default;

MD4_5::~MD4_5() = default;

std::string MD4_5::md5_digestHex(const std::string &data) {
    return md5_digestHex(data.c_str(), data.size());
}

std::string MD4_5::md5_digestHex(const char *data, size_t size) {
    if (!data) {
        return std::string();
    }

    unsigned char md[MD5_DIGEST_LENGTH];
    ::MD5(reinterpret_cast<const unsigned char *>(data), size, reinterpret_cast<unsigned char *>(&md));

    return str::HexToString(md, MD5_DIGEST_LENGTH);
}

std::string MD4_5::md5_digestHex(std::istream &stream) {
    auto ctx = EVP_MD_CTX_create();
    unsigned char md_value[EVP_MAX_MD_SIZE];
    unsigned int md_len = 0;

    EVP_MD_CTX_init(ctx);
#ifndef OPENSSL_IS_BORINGSSL
    EVP_MD_CTX_set_flags(ctx, EVP_MD_CTX_FLAG_NON_FIPS_ALLOW);
#endif
    EVP_DigestInit_ex(ctx, EVP_md5(), nullptr);

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

std::string MD4_5::md4_digestHex(const std::string &data) {
    return md4_digestHex(data.c_str(), data.size());
}

std::string MD4_5::md4_digestHex(const char *data, size_t size) {
    if (nullptr == data || size <= 0) {
        return std::string();
    }

    unsigned char md[MD4_DIGEST_LENGTH];
    ::MD4(reinterpret_cast<const unsigned char *>(data), size, reinterpret_cast<unsigned char *>(&md));

    return str::HexToString(md, MD4_DIGEST_LENGTH);
}

std::string MD4_5::md4_digestHex(std::istream &stream) {
    auto ctx = EVP_MD_CTX_create();
    unsigned char md_value[EVP_MAX_MD_SIZE];
    unsigned int md_len = 0;

    EVP_MD_CTX_init(ctx);
#ifndef OPENSSL_IS_BORINGSSL
    EVP_MD_CTX_set_flags(ctx, EVP_MD_CTX_FLAG_NON_FIPS_ALLOW);
#endif
    EVP_DigestInit_ex(ctx, EVP_md4(), nullptr);

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

std::string MD4_5::md5_hmacHex(const std::string &data, const std::string &key) {
    return md5_hmacHex(data.c_str(), data.size(), key.c_str(), key.size());
}

std::string MD4_5::md5_hmacHex(const char *data, size_t size, const char *key, size_t key_size) {
    if (!data || !key) {
        return std::string();
    }

//    LOG_INFO << "data:" << data << " key:" << key;
//    LOG_INFO << "data_size:" << size << " key_size:" << key_size;

    unsigned char buf[EVP_MAX_MD_SIZE];
    unsigned int len;

    HMAC(EVP_md5(), key, key_size, reinterpret_cast<const unsigned char *>(data), size,
                                 reinterpret_cast<unsigned char *>(&buf),
                                 &len);
    return str::HexToString(buf, len);
}

std::string MD4_5::md5_hmactHex(std::istream &stream, const std::string &key) {
    HMAC_CTX *ctx;
    unsigned char buf[EVP_MAX_MD_SIZE];
    unsigned int len;

    ctx = HMAC_CTX_new();
    if (nullptr == ctx) {
        return std::string();
    }
    HMAC_CTX_get_md(ctx);
    HMAC_Init_ex(ctx, key.c_str(), key.size(), EVP_md5(), NULL);

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

std::string MD4_5::md4_hmacHex(const std::string &data, const std::string &key) {
    return md4_hmacHex(data.c_str(), data.size(), key.c_str(), key.size());
}

std::string MD4_5::md4_hmacHex(const char *data, size_t size, const char *key, size_t key_size) {
    if (!data || !key) {
        return std::string();
    }

    unsigned char buf[EVP_MAX_MD_SIZE];
    unsigned int len;

    HMAC(EVP_md4(), key, key_size, reinterpret_cast<const unsigned char *>(data), size,
         reinterpret_cast<unsigned char *>(&buf),
         &len);
    return str::HexToString(buf, len);
}

std::string MD4_5::md4_hmactHex(std::istream &stream, const std::string &key) {
    HMAC_CTX *ctx;
    unsigned char buf[EVP_MAX_MD_SIZE];
    unsigned int len;

    ctx = HMAC_CTX_new();
    if (nullptr == ctx) {
        return std::string();
    }
    HMAC_CTX_get_md(ctx);
    HMAC_Init_ex(ctx, key.c_str(), key.size(), EVP_md4(), NULL);

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




