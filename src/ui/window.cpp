#include "window.h"

#include "../config.h"
#include "../crypto/digest/md4_5.h"
#include "../crypto/digest/sha.h"

#include <QDialogButtonBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QComboBox>
#include <QCursor>

#include <sstream>
#include <fstream>
#include <thread>


window::window(QWidget *parent)
        : QWidget(parent) {

    auto *buttonBox = new QDialogButtonBox(Qt::Horizontal);
    QPushButton *calcBtn = buttonBox->addButton(tr("&Calculate"), QDialogButtonBox::ActionRole);
    QPushButton *closeBtn = buttonBox->addButton(QDialogButtonBox::Close);

    connect(calcBtn, &QPushButton::clicked, this, &window::calculate);
    connect(closeBtn, &QPushButton::clicked, this, &QWidget::close);

    auto *line = new QFrame();
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);

    auto *mainLayout = new QVBoxLayout;
    inputData = new InputData();
    mainLayout->addWidget(inputData);
    hashData = new HashData();
    mainLayout->addWidget(hashData);
    mainLayout->addStretch();
    mainLayout->addWidget(line);
    mainLayout->addWidget(buttonBox);
    setLayout(mainLayout);

    this->resize(ConfigIni::getInstance().iniRead(QStringLiteral("window/size"), this->sizeHint()).toSize());
}

window::~window() {
// 一种正确的写法 qt5
#if 0
    QList<QWidget *> widgets = findChildren<QWidget *>("", Qt::FindDirectChildrenOnly);
    foreach(QWidget * widget, widgets)
    {
        delete widget;
    }
#endif
    setUpdatesEnabled(false);

    ConfigIni::getInstance().iniWrite(QStringLiteral("window/size"), this->size());

    qDeleteAll(findChildren<QWidget *>("", Qt::FindDirectChildrenOnly));

    this->deleteLater();
}

void window::calculate() {
    QCursor currCursor = this->cursor();
    this->setCursor(Qt::BusyCursor);
    this->setEnabled(false);

    std::vector<int> hashList = hashData->getHashList();
    std::istream *data_ptr = inputData->getData();
    if (nullptr == data_ptr) {
        return;
    }

    std::vector<std::thread *> ths;
    std::vector<std::ifstream *> ifstreams;

    auto *iss = dynamic_cast<std::istringstream *>(data_ptr);
    if (nullptr != iss) {
        for (int i : hashList) {
            auto *thr = new std::thread(&window::doCalc1, this, iss, i);
            ths.push_back(thr);
        }
    } else {
        auto *ifs = dynamic_cast<std::ifstream *>(data_ptr);
        if (nullptr != ifs) {
            size_t len = hashList.size();
            for (size_t i = 0; i < len; ++i) {
                auto *thr = new std::thread(&window::doCalc2, this, ifs, hashList[i]);
                ths.push_back(thr);

                // ifstream 线程不安全
                if (i < len - 1) {
                    ifstreams.push_back(ifs);
                    data_ptr = inputData->getData();
                    ifs = dynamic_cast<std::ifstream *>(data_ptr);
                }
            }
        }
    }

    for (std::thread *thr: ths) {
        thr->join();
        delete thr;
    }

    delete data_ptr;

    for (std::ifstream *ifs: ifstreams) {
        delete ifs;
    }

    this->setCursor(currCursor);
    this->setEnabled(true);
}

void window::doCalc1(const std::istringstream *iss, int iEnum) {
    switch (iEnum) {
        case static_cast<int>(HashEnum::MD5) : {
            std::string md5str = MD4_5::md5_digestHex16(iss->str());
            hashData->setHashData(HashEnum::MD5, md5str);
        }
            break;
        case static_cast<int>(HashEnum::MD4) : {
            std::string md4str = MD4_5::md4_digestHex16(iss->str());
            hashData->setHashData(HashEnum::MD4, md4str);
        }
            break;
        case static_cast<int>(HashEnum::SHA1): {
            std::string sha = sha::sha1_digestHex16(iss->str());
            hashData->setHashData(HashEnum::SHA1, sha);
        }
            break;
        case static_cast<int>(HashEnum::SHA256): {
            std::string sha = sha::sha256_digestHex16(iss->str());
            hashData->setHashData(HashEnum::SHA256, sha);
        }
            break;
        case static_cast<int>(HashEnum::SHA384): {
            std::string sha = sha::sha384_digestHex16(iss->str());
            hashData->setHashData(HashEnum::SHA384, sha);
        }
            break;
        case static_cast<int>(HashEnum::SHA512): {
            std::string sha = sha::sha512_digestHex16(iss->str());
            hashData->setHashData(HashEnum::SHA512, sha);
        }
            break;
        default:
            break;
    }
}

void window::doCalc2(const std::ifstream *ifs, int iEnum) {
    switch (iEnum) {
        case static_cast<int>(HashEnum::MD5) : {
            std::string md5str = MD4_5::md5_digestHex16((std::istream &) *ifs);
            hashData->setHashData(HashEnum::MD5, md5str);
        }
            break;
        case static_cast<int>(HashEnum::MD4) : {
            std::string md4str = MD4_5::md4_digestHex16((std::istream &) *ifs);
            hashData->setHashData(HashEnum::MD4, md4str);
        }
            break;
        case static_cast<int>(HashEnum::SHA1): {
            std::string sha = sha::sha1_digestHex16((std::istream &) *ifs);
            hashData->setHashData(HashEnum::SHA1, sha);
        }
            break;
        case static_cast<int>(HashEnum::SHA256): {
            std::string sha = sha::sha256_digestHex16((std::istream &) *ifs);
            hashData->setHashData(HashEnum::SHA256, sha);
        }
            break;
        case static_cast<int>(HashEnum::SHA384): {
            std::string sha = sha::sha384_digestHex16((std::istream &) *ifs);
            hashData->setHashData(HashEnum::SHA384, sha);
        }
            break;
        case static_cast<int>(HashEnum::SHA512): {
            std::string sha = sha::sha512_digestHex16((std::istream &) *ifs);
            hashData->setHashData(HashEnum::SHA512, sha);
        }
            break;
        default:
            break;
    }
}
