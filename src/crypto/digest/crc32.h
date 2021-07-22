//
// Created by Spark on 2021-07-19.
//

#ifndef CRYPTOOL_CRC32_H
#define CRYPTOOL_CRC32_H


class Crc32 {

public:
    Crc32();

    virtual ~Crc32();

public:
    static std::string crc32(const std::string &data);

    static std::string crc32(const char *data, size_t size);

    static std::string crc32(std::istream &stream);
};


#endif //CRYPTOOL_CRC32_H
