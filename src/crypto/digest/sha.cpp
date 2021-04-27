//
// Created by Spark on 2021-04-27.
//

#include "sha.h"
#include "str.h"

#include <sstream>
#include <openssl/sha.h>
#include <openssl/evp.h>

std::string sha::sha1_digestHex16(const std::string &data) {
    return sha::sha1_digestHex16(data.c_str(), data.size());
}

std::string sha::sha1_digestHex16(const char *data, size_t size) {
    if (nullptr == data || size <= 0) {
        return std::string();
    }
    unsigned char md[SHA_DIGEST_LENGTH];
    ::SHA1(reinterpret_cast<const unsigned char *>(data), size, reinterpret_cast<unsigned char *>(&md));
    return str::HexToString(md, SHA_DIGEST_LENGTH);
}

std::string sha::sha1_digestHex16(std::istream &stream) {
    auto ctx = EVP_MD_CTX_create();
    unsigned char md_value[EVP_MAX_MD_SIZE];
    unsigned int md_len = 0;

    EVP_MD_CTX_init(ctx);
#ifndef OPENSSL_IS_BORINGSSL
    EVP_MD_CTX_set_flags(ctx, EVP_MD_CTX_FLAG_NON_FIPS_ALLOW);
#endif
    EVP_DigestInit_ex(ctx, EVP_sha1(), nullptr);

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
