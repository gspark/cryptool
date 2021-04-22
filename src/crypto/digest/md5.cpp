//
// Created by Spark on 2021-04-15.
//

#include "md5.h"
#include <string>
#include <sstream>

#include <openssl/md5.h>
#include <openssl/evp.h>


MD5::MD5() = default;

MD5::~MD5() = default;


std::string MD5::HexToString(const unsigned char *data, size_t size) {
    static char hex[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
    std::stringstream ss;
    for (size_t i = 0; i < size; i++)
        ss << hex[(data[i] >> 4)] << hex[(data[i] & 0x0F)];
    return ss.str();

}

std::string MD5::digestHex16(const std::string &data) {
    return digestHex16(data.c_str(), data.size());
}

std::string MD5::digestHex16(const char *data, size_t size) {
    if (!data) {
        return "";
    }

    unsigned char md[MD5_DIGEST_LENGTH];
    ::MD5(reinterpret_cast<const unsigned char *>(data), size, reinterpret_cast<unsigned char *>(&md));

    return HexToString(md, MD5_DIGEST_LENGTH);
}

std::string MD5::digestHex16(std::istream &stream) {
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

    std::string strMD5 = HexToString(md_value, md_len);

    return strMD5;
}
