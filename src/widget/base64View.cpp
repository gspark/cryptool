//
// Created by Spark on 2021-07-02.
//

// You may need to build the project (run Qt uic code generator) to get "ui_base64View.h" resolved

#include "base64View.h"
#include "base64Model.h"
#include <QGridLayout>
#include <QCheckBox>
#include <QPlainTextEdit>

Base64View::Base64View(QWidget *parent) : QWidget(parent) {
    mainLayout = new QGridLayout(this);

    base64Result = new QPlainTextEdit;
    base64Result->setReadOnly(true);
    base64Result->setUndoRedoEnabled(false);
    // 换行
    base64Result->setLineWrapMode(QPlainTextEdit::LineWrapMode::WidgetWidth);
    // 换行速度慢
//    base64Result->setWordWrapMode(QTextOption::NoWrap);

    encryptCheckBox = new QCheckBox(tr("加密"));
    encryptCheckBox->setCheckState(Qt::CheckState::Checked);

    connect(encryptCheckBox, &QCheckBox::stateChanged, this, &Base64View::encryptStatus);

    mainLayout->addWidget(encryptCheckBox, 0, 0);
    mainLayout->addWidget(base64Result, 1, 0, -1, 0);
}

Base64View::~Base64View() = default;

void Base64View::refresh() {
    auto *m = dynamic_cast<Base64Model *>(this->model);
    if (nullptr == m) {
        return;
    }
    base64Result->setPlainText(QString::fromStdString(m->getData()));
}

void Base64View::encryptStatus() {
    auto *m = dynamic_cast<Base64Model *>(this->model);
    if (nullptr == m) {
        return;
    }
    if (encryptCheckBox->isChecked()) {
        encryptCheckBox->setText(tr("加密"));
        m->setEncrypt(EncryptEnum::ENCODING);
    } else if (!encryptCheckBox->isChecked()) {
        encryptCheckBox->setText(tr("解密"));
        m->setEncrypt(EncryptEnum::DECODING);
    }
}

void Base64View::setEncrypt(bool flag) {
    encryptCheckBox->setEnabled(!flag);
    encryptCheckBox->setCheckState(Qt::CheckState::Checked);
}

void Base64View::clearData() {
    base64Result->clear();
}

