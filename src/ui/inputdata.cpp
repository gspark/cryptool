//
// Created by Spark on 2021-04-19.
//


#include "inputdata.h"
#include "..\config.h"

#include <QPushButton>
#include <QLineEdit>
#include <QFormLayout>
#include <QDir>
#include <QFileDialog>
#include <QLabel>
#include <QComboBox>
#include <sstream>
#include <fstream>


InputData::InputData(QWidget *parent) :
        QWidget(parent) {
    fileName = new QLineEdit(this);

    browseButton = new QPushButton(tr("..."), this);
    browseButton->setMaximumWidth(24);

    connect(browseButton, &QAbstractButton::clicked, this, &InputData::browse);

    initDateType();

    mainLayout = new QGridLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    mainLayout->addWidget(new QLabel(tr("Data")), 0, 0);
    mainLayout->addWidget(new QLabel(tr("Data:")), 0, 1, 1, 2);
    mainLayout->addWidget(dataTypeCbBox, 1, 0);

    dataLineEdit = new QLineEdit;

    int dateType = ConfigIni::getInstance().iniRead(QStringLiteral("Hash/dataType"), 0).toInt();
    setDateType(dateType);
}

InputData::~InputData() = default;


void InputData::browse() {
    QString selectFile = QFileDialog::getOpenFileName(
            this,
            tr("select a file."),
            QDir::currentPath(),
            tr("All files(*.*)"));
    if (!selectFile.isEmpty()) {
        this->fileName->setText(selectFile);
    }
}

void InputData::initDateType() {
    dataTypeCbBox = new QComboBox(this);

    for (auto &s : this->dataType) {
        dataTypeCbBox->addItem(QString::fromStdString(s));
    }

    connect(dataTypeCbBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &InputData::setDateType);

}

void InputData::setDateType(int index) {
    if (index == 0) {
        mainLayout->removeWidget(dataLineEdit);
        if (dataLineEdit->isVisible()) {
            dataLineEdit->hide();
        }
        mainLayout->addWidget(fileName, 1, 1);
        mainLayout->addWidget(browseButton, 1, 2);
        if (fileName->isHidden()) {
            fileName->show();
            browseButton->show();
        }
    } else if (index == 1) {
        mainLayout->removeWidget(fileName);
        mainLayout->removeWidget(browseButton);
        if (fileName->isVisible()) {
            fileName->hide();
            browseButton->hide();
        }
        mainLayout->addWidget(dataLineEdit, 1, 1, 1, 2);
        dataLineEdit->show();
    }
}

std::istream *InputData::getData() {
    std::istream *ret = nullptr;
    if (dataTypeCbBox->currentIndex() == 0) {
        // 0 is file
        ret = new std::ifstream(fileName->text().toStdString(), std::ios_base::in | std::ios_base::binary);
    } else if (dataTypeCbBox->currentIndex() == 1) {
        // 1 is text
        ret = new std::istringstream(dataLineEdit->text().toStdString());
    }
    return ret;
}
