//
// Created by Spark on 2021-07-19.
//

#include <string>
#include <sstream>
#include "crc32.h"
#include "zlib.h"
#include "str.h"

Crc32::Crc32() = default;

Crc32::~Crc32() = default;

std::string Crc32::crc32(const char *data, size_t size) {
    uLong crc = ::crc32(0, reinterpret_cast<const Bytef *>(data), size);
    return str::LongToHex(crc);
}

std::string Crc32::crc32(const std::string &data) {
    return crc32(data.c_str(), data.size());
}

std::string Crc32::crc32(std::istream &stream) {
    stream.seekg(0, std::istream::beg);
    char streamBuffer[2048];
    uLong crc = ::crc32(0L, Z_NULL, 0);

    while (stream.good()) {
        stream.read(streamBuffer, 2048);
        auto bytesRead = stream.gcount();
        crc = ::crc32(crc, reinterpret_cast<const Bytef *>(streamBuffer), bytesRead);
    }
    return str::LongToHex(crc);
}