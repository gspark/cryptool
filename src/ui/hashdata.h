//
// Created by Spark on 2021-04-20.
//

#ifndef CRYPTOOL_HASHDATA_H
#define CRYPTOOL_HASHDATA_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QGridLayout;

QT_END_NAMESPACE

enum class HashEnum {
    MD5,
    MD4,
    SHA1,
    SHA256,
    SHA384,
    SHA512
};

static const char *HashEnumStrings[] = {"MD5", "MD4", "SHA1", "SHA256", "SHA384", "SHA512"};

class HashData : public QWidget {
Q_OBJECT

public:
    explicit HashData(QWidget *parent = nullptr);

    ~HashData() override;

public:
    std::vector<int> getHashList();

    void setHashData(HashEnum hashEnum, std::string &data);

private:
    QGridLayout *mainLayout;
};


#endif //CRYPTOOL_HASHDATA_H
