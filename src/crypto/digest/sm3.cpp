//
// Created by Spark on 2021-05-08.
//

#include "sm3.h"
#include "str.h"

#include <sstream>
#include <openssl/evp.h>

SM3::SM3() = default;

SM3::~SM3() = default;

std::string SM3::sm3_digestHex(const std::string &data) {
    return sm3_digestHex(data.c_str(), data.length());
}

std::string SM3::sm3_digestHex(const char *data, size_t size) {
    if (!data) {
        return std::string();
    }

    auto ctx = EVP_MD_CTX_create();
    unsigned char md_value[EVP_MAX_MD_SIZE];
    unsigned int md_len = size;

    EVP_MD_CTX_init(ctx);
#ifndef OPENSSL_IS_BORINGSSL
    EVP_MD_CTX_set_flags(ctx, EVP_MD_CTX_FLAG_NON_FIPS_ALLOW);
#endif
    EVP_DigestInit_ex(ctx, EVP_sm3(), nullptr);

    EVP_DigestUpdate(ctx, data, md_len);

    EVP_DigestFinal_ex(ctx, md_value, &md_len);

    EVP_MD_CTX_destroy(ctx);

    return str::HexToString(md_value, md_len);
}


std::string SM3::sm3_digestHex(std::istream &stream) {
    auto ctx = EVP_MD_CTX_create();
    unsigned char md_value[EVP_MAX_MD_SIZE];
    unsigned int md_len = 0;

    EVP_MD_CTX_init(ctx);
#ifndef OPENSSL_IS_BORINGSSL
    EVP_MD_CTX_set_flags(ctx, EVP_MD_CTX_FLAG_NON_FIPS_ALLOW);
#endif
    EVP_DigestInit_ex(ctx, EVP_sm3(), nullptr);

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




