#include "window.h"

#include "../crypto/digest/md5.h"

#include <QDialogButtonBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QCheckBox>
#include <QLineEdit>
#include <QComboBox>


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

    std::string data = inputData->getData();
    if (data.empty()) {
        return;
    }

    for (int i : hashList) {
        switch (i) {
            case static_cast<int>(HashEnum::MD5) :
                MD5 *md5 = new MD5;
                std::string md5str = md5->digestHex16(data);
                hashData->setHashData(HashEnum::MD5, md5str);
                delete md5;
                break;

        }
    }

    return;
}
