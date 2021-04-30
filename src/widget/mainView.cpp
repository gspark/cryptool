#include "mainView.h"
#include "hashdataModel.h"
#include "mainViewModel.h"

#include "../config.h"

#include <QDialogButtonBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QComboBox>
#include <QCoreApplication>


MainView::MainView(QWidget *parent)
        : QWidget(parent) {

    auto *buttonBox = new QDialogButtonBox(Qt::Horizontal);
    calcBtn = buttonBox->addButton(tr("&Calculate"), QDialogButtonBox::ActionRole);
    QPushButton *closeBtn = buttonBox->addButton(QDialogButtonBox::Close);

    connect(calcBtn, &QPushButton::clicked, this, &MainView::calcClicked);
    connect(closeBtn, &QPushButton::clicked, this, &QWidget::close);

    auto *line = new QFrame();
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);

    auto *mainLayout = new QVBoxLayout;
    inputData = new InputData();
    mainLayout->addWidget(inputData);

    HashDataModel *hashDataModel = new HashDataModel;
    hashData = new HashData();
    hashData->setModel(hashDataModel);

    connect(this, &MainView::refreshView, hashData, &HashData::refresh);
    connect(this, &MainView::refreshView, this, &MainView::calcCompleted);

    mainLayout->addWidget(hashData);
    mainLayout->addStretch();
    mainLayout->addWidget(line);
    mainLayout->addWidget(buttonBox);
    setLayout(mainLayout);

    MainViewModel *mainViewModel = new MainViewModel();
    mainViewModel->setHashDataModel(hashDataModel);
    this->setModel(mainViewModel);

    this->resize(ConfigIni::getInstance().iniRead(QStringLiteral("MainView/size"), this->sizeHint()).toSize());
}

MainView::~MainView() {
// 一种正确的写法 qt5
#if 0
    QList<QWidget *> widgets = findChildren<QWidget *>("", Qt::FindDirectChildrenOnly);
    foreach(QWidget * widget, widgets)
    {
        delete widget;
    }
#endif
    setUpdatesEnabled(false);

    ConfigIni::getInstance().iniWrite(QStringLiteral("MainView/size"), this->size());

    qDeleteAll(findChildren<QWidget *>("", Qt::FindDirectChildrenOnly));

    this->deleteLater();
}

void MainView::calcClicked() {
//    QCursor currCursor = this->cursor();
    this->setCursor(Qt::BusyCursor);
    this->calcBtn->setEnabled(false);
    QCoreApplication::processEvents();
    // 发送信号
    emit calculate(this);
}

void MainView::refresh() {
    emit refreshView(this);
}

HashData *MainView::getHashDataView() {
    return this->hashData;
}

InputData *MainView::getInputDataView() {
    return this->inputData;
}

void MainView::calcCompleted() {
    this->setCursor(Qt::ArrowCursor);
    this->calcBtn->setEnabled(true);
    QCoreApplication::processEvents();
}
