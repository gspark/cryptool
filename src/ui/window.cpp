#include "window.h"

#include "../crypto/digest/md5.h"

#include <QDialogButtonBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QComboBox>
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
    qDeleteAll(findChildren<QWidget *>("", Qt::FindDirectChildrenOnly));

    this->deleteLater();
}

void window::calculate() {
    std::vector<int> hashList = hashData->getHashList();

    std::istream *data_ptr = inputData->getData();
    if (nullptr == data_ptr) {
        return;
    }

    auto *iss = dynamic_cast<std::istringstream *>(data_ptr);
    if (nullptr != iss) {
        calculate1(hashList, iss);
        return;
    }

    auto *ifs = dynamic_cast<std::ifstream *>(data_ptr);
    if (nullptr != ifs) {
        calculate2(hashList, ifs);
    }

    delete data_ptr;
}

void window::calculate1(std::vector<int> &hashList, const std::istringstream *iss) {
    std::vector<std::thread *> ths;
    for (int i : hashList) {
        auto *thr = new std::thread(&window::doCalc1, this, iss, i);
        ths.push_back(thr);
    }

    for (std::thread *thr: ths) {
        thr->join();
    }
}

void window::doCalc1(const std::istringstream *iss, int i) {
    switch (i) {
        case static_cast<int>(HashEnum::MD5) : {
            MD5 *md5 = new MD5;
            std::string md5str = md5->digestHex16(iss->str());
            hashData->setHashData(HashEnum::MD5, md5str);
            delete md5;
        }
            break;
        case static_cast<int>(HashEnum::MD4) :
            break;
        case static_cast<int>(HashEnum::SHA1):
            break;
        case static_cast<int>(HashEnum::SHA256):
            break;
        case static_cast<int>(HashEnum::SHA384):
            break;
        case static_cast<int>(HashEnum::SHA512):
            break;
    }
}

void window::calculate2(std::vector<int> &hashList, const std::ifstream *ifs) {
    std::vector<std::thread *> ths;
    for (int i : hashList) {
        auto *thr = new std::thread(&window::doCalc2, this, ifs, i);
        ths.push_back(thr);
    }

    for (std::thread *thr: ths) {
        thr->join();
    }
}

void window::doCalc2(const std::ifstream *ifs, int i) {
    switch (i) {
        case static_cast<int>(HashEnum::MD5) : {
            MD5 *md5 = new MD5;
            std::string md5str = md5->digestHex16((std::istream &) *ifs);
            hashData->setHashData(HashEnum::MD5, md5str);
            delete md5;
        }
            break;
        case static_cast<int>(HashEnum::MD4) :
            break;
        case static_cast<int>(HashEnum::SHA1):
            break;
        case static_cast<int>(HashEnum::SHA256):
            break;
        case static_cast<int>(HashEnum::SHA384):
            break;
        case static_cast<int>(HashEnum::SHA512):
            break;
    }
}
