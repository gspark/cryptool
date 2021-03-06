//
// Created by Spark on 2021-04-19.
//


#include "inputdataView.h"
#include "../config.h"

#include <QPushButton>
#include <QLineEdit>
#include <QFormLayout>
#include <QPlainTextEdit>
#include <QDir>
#include <QFileDialog>
#include <QLabel>
#include <QComboBox>
#include <QCheckBox>
#include <sstream>
#include <fstream>


InputDataView::InputDataView(QWidget *parent) :
        QWidget(parent) {
    fileName = new QLineEdit(this);

    browseButton = new QPushButton(tr("..."), this);
    browseButton->setMaximumWidth(24);

    connect(browseButton, &QAbstractButton::clicked, this, &InputDataView::browse);

    int dateType = ConfigIni::getInstance().iniRead(QStringLiteral("Hash/dataType"), 0).toInt();
    initDateType(dateType);

    mainLayout = new QGridLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    mainLayout->addWidget(new QLabel(tr("Type")), 0, 0);
    mainLayout->addWidget(new QLabel(tr("Data:")), 0, 1, 1, 2);
    mainLayout->addWidget(dataTypeCbBox, 1, 0);

    dataLineEdit = new QPlainTextEdit;
    dataLineEdit->setUndoRedoEnabled(false);
    setDateType(dateType);

    // HMAC
    mainLayout->addWidget(new QLabel(tr("Key:")), 2, 1, 1, 2);
    int hmacCheck = ConfigIni::getInstance().iniRead(QStringLiteral("Hash/hmacState"), 0).toInt();
    initHmacCheckBox(hmacCheck);

    connect(fileName, &QLineEdit::textChanged, this, &InputDataView::dataChanged);
    connect(dataLineEdit, &QPlainTextEdit::textChanged, this, &InputDataView::dataChanged);
    connect(hmacKey, &QLineEdit::textChanged, this, &InputDataView::dataChanged);

    this->setMaximumHeight(dataTypeCbBox->heightMM() * 10 + dataLineEdit->heightMM());
}

InputDataView::~InputDataView() {
    ConfigIni::getInstance().iniWrite(QStringLiteral("Hash/dataType"), dataTypeCbBox->currentIndex());
    ConfigIni::getInstance().iniWrite(QStringLiteral("Hash/hmacState"), hmacCheckBox->checkState());
}

void InputDataView::browse() {
    QString selectFile = QFileDialog::getOpenFileName(
            this,
            tr("select a file."),
            QDir::currentPath(),
            tr("All files(*.*)"));
    if (!selectFile.isEmpty()) {
        this->fileName->setText(selectFile);
    }
}

void InputDataView::initDateType(int currentIdx) {
    dataTypeCbBox = new QComboBox(this);

    for (auto &s : this->dataType) {
        dataTypeCbBox->addItem(QString::fromStdString(s));
    }
    dataTypeCbBox->setCurrentIndex(currentIdx);

    connect(dataTypeCbBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &InputDataView::setDateType);
}

void InputDataView::setDateType(int index) {
    if (index == 0) {
        mainLayout->removeWidget(dataLineEdit);
        if (dataLineEdit->isVisible()) {
            dataLineEdit->hide();
        }
        mainLayout->addWidget(fileName, 1, 1);
        mainLayout->addWidget(browseButton, 1, 2);
        if (!fileName->isVisible()) {
            fileName->show();
            browseButton->show();
        }
    } else if (index == 1) {
        mainLayout->removeWidget(fileName);
        mainLayout->removeWidget(browseButton);
        if (!fileName->isHidden()) {
            fileName->hide();
            browseButton->hide();
        }
        mainLayout->addWidget(dataLineEdit, 1, 1, 1, 2);
        dataLineEdit->show();
    }

    emit dataTypeChanged();
}

std::istream *InputDataView::getData() {
    std::istream *ret = nullptr;
    if (dataTypeCbBox->currentIndex() == 0) {
        // 0 is file
        // ifstream ?????????????????? string?????????
        if (fileName->text().isEmpty()) {
            return ret;
        }
        ret = new std::ifstream(fileName->text().toStdWString().c_str(), std::ios_base::in | std::ios_base::binary);
    } else if (dataTypeCbBox->currentIndex() == 1) {
        // 1 is text
        QString txt = dataLineEdit->toPlainText();
        if (txt.isEmpty()) {
            return ret;
        }
        ret = new std::istringstream(txt.toStdString());
    }
    return ret;
}

bool InputDataView::dateTypeIsFile() {
    return dataTypeCbBox->currentIndex() == 0;
}

std::string *InputDataView::getHmacKey() {
    if (!hmacCheckBox->isChecked()) {
        return nullptr;
    }
    return new std::string(hmacKey->text().toStdString());;
}

void InputDataView::hmacStateChang(int state) {
    if (state == Qt::CheckState::Checked) {
        this->hmacKey->setEnabled(true);
    } else {
        this->hmacKey->setEnabled(false);
    }
}

void InputDataView::initHmacCheckBox(int state) {
    hmacCheckBox = new QCheckBox(tr("HMAC"));
    if (state == Qt::CheckState::Checked) {
        hmacCheckBox->setCheckState(Qt::CheckState::Checked);
    } else {
        hmacCheckBox->setCheckState(Qt::CheckState::Unchecked);
    }

    mainLayout->addWidget(hmacCheckBox, 3, 0);
    hmacKey = new QLineEdit(this);
    mainLayout->addWidget(hmacKey, 3, 1, 1, 2);
    hmacStateChang(state);

    connect(hmacCheckBox, &QCheckBox::stateChanged, this, &InputDataView::hmacStateChanged);
    connect(hmacCheckBox, &QCheckBox::stateChanged, this, &InputDataView::hmacStateChang);
}

void InputDataView::hmacEnabled(bool enabled) {
    hmacCheckBox->setEnabled(enabled);
    if (!enabled) {
        this->hmacKey->clear();
        hmacStateChang(0);
    } else {
        hmacStateChang(2);
    }
}
