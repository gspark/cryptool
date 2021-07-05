//
// Created by Spark on 2021-07-02.
//

// You may need to build the project (run Qt uic code generator) to get "ui_base64View.h" resolved

#include "base64View.h"
#include <QGridLayout>
#include <QCheckBox>
#include <QTextEdit>

Base64View::Base64View(QWidget *parent) : QWidget(parent) {
    mainLayout = new QGridLayout(this);

    base64Result = new QTextEdit;
    base64Result->setReadOnly(true);

    encryptCheckBox = new QCheckBox(tr("加密"));
    encryptCheckBox->setCheckState(Qt::CheckState::Checked);

    connect(encryptCheckBox, &QCheckBox::stateChanged, this, &Base64View::encryptStatus);

    mainLayout->addWidget(encryptCheckBox, 0, 0);
    mainLayout->addWidget(base64Result, 1, 0, -1,0);
}

Base64View::~Base64View() = default;

void Base64View::refresh() {
    // todo
}

void Base64View::encryptStatus() {
    if (encryptCheckBox->isChecked()) {
        encryptCheckBox->setText(tr("加密"));
    } else if (!encryptCheckBox->isChecked()) {
        encryptCheckBox->setText(tr("解密"));
    }
}

