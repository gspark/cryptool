//
// Created by Spark on 2021-07-06.
//

#include <string>
#include <openssl/evp.h>
#include "base64.h"

Base64::Base64() = default;

Base64::~Base64() = default;

std::string Base64::encode(const std::string &data) {
    return encode(data.c_str(), (int) data.size());
}

std::string Base64::encode(const char *data, int size) {
    EVP_ENCODE_CTX *ctx;
    unsigned char *encode_out;
    int output_len, chunk_len;
    std::string ret = std::string();

    ctx = EVP_ENCODE_CTX_new();
    // 分配空间
    encode_out = reinterpret_cast<unsigned char *>(OPENSSL_malloc(EVP_ENCODE_LENGTH(size)));
    if (nullptr == ctx || nullptr == encode_out) {
        goto err;
    }

    EVP_EncodeInit(ctx);

    if (!EVP_EncodeUpdate(ctx, encode_out, &chunk_len, reinterpret_cast<const unsigned char *>(data), size)) {
        goto err;
    }

    output_len = chunk_len;
    EVP_EncodeFinal(ctx, encode_out + chunk_len, &chunk_len);
    output_len += chunk_len;

    ret = std::string(reinterpret_cast<const char *>(encode_out), output_len);

err:
    OPENSSL_free(encode_out);
    EVP_ENCODE_CTX_free(ctx);
    return ret;
}