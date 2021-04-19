//
// Created by Spark on 2021-04-19.
//


#include "inputdata.h"

#include <QPushButton>
#include <QLineEdit>
#include <QFormLayout>
#include <QDir>
#include <QFileDialog>
#include <QLabel>
#include <QComboBox>

InputData::InputData(QWidget *parent) :
        QWidget(parent) {
    fileName = new QLineEdit(this);

    browseButton = new QPushButton(tr("..."), this);
    connect(browseButton, &QAbstractButton::clicked, this, &InputData::browse);

    dataType = new QComboBox(this);

    auto *mainLayout = new QGridLayout(this);
    mainLayout->setContentsMargins(0,0,0,0);

    mainLayout->addWidget(new QLabel(tr("Data")), 0, 0);
    mainLayout->addWidget(new QLabel(tr("Data:")), 0, 1, 1, 2);
    mainLayout->addWidget(dataType, 1, 0);
    mainLayout->addWidget(fileName, 1, 1);
    mainLayout->addWidget(browseButton, 1, 2);
}

InputData::~InputData() = default;


void InputData::browse() {
    QString selectFile =
            QFileDialog::getOpenFileName(
                    this,
                    tr("open a file."),
                    QDir::currentPath(),
                    tr("All files(*.*)"));
    if (!selectFile.isEmpty()) {
        this->fileName->setText(selectFile);
    }
}
