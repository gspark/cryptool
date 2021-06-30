#include "mainView.h"
#include "hashdataModel.h"
#include "mainViewModel.h"

#include "../config.h"
#include "../logger/Logger.h"
#include "../component/DoubleClickedButton.h"

#include <QDialogButtonBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QComboBox>
#include <QCoreApplication>
#include <QTabWidget>

MainView::MainView(QWidget *parent)
        : QWidget(parent) {

    auto *buttonBox = new QDialogButtonBox(Qt::Horizontal);
    calcBtn = new DoubleClickedButton(tr("&Calculate"), buttonBox);
    buttonBox->addButton(calcBtn, QDialogButtonBox::ActionRole);
    QPushButton *closeBtn = buttonBox->addButton(QDialogButtonBox::Close);

    connect(calcBtn, &DoubleClickedButton::singleClicked, this, &MainView::calcClicked);
    connect(closeBtn, &QPushButton::clicked, this, &QWidget::close);

    auto *line = new QFrame();
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);

    auto *mainLayout = new QVBoxLayout;
    inputData = new InputData();
    mainLayout->addWidget(inputData);

    auto *hashDataModel = new HashDataModel;
    hashData = new HashData();
    hashData->setModel(hashDataModel);

    connect(this, &MainView::refreshView, hashData, &HashData::refresh);
    connect(this, &MainView::refreshView, this, &MainView::calcCompleted);

    tabWidget = new QTabWidget(this);
    tabWidget->addTab(hashData, tr("hash"));

    mainLayout->addWidget(tabWidget);
    mainLayout->addStretch();
    mainLayout->addWidget(line);
    mainLayout->addWidget(buttonBox);
    setLayout(mainLayout);

    auto *mainViewModel = new MainViewModel();
    mainViewModel->setHashDataModel(hashDataModel);
    this->setModel(mainViewModel);

    connect(inputData, &InputData::dataTypeChanged, hashData, &HashData::clearData);
    connect(inputData, &InputData::dataChanged, hashData, &HashData::clearData);

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
    LOG_INFO << "calcClicked() enable is" << this->calcBtn->isEnabled();
//    disconnect(calcBtn, nullptr, nullptr, nullptr);
    this->calcBtn->setEnabled(false);
//    this->calcBtn->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    this->setCursor(Qt::BusyCursor);
    QCoreApplication::processEvents();
    // 发送信号
    emit calculate(this);
    LOG_INFO << "emit calculate(this)";
}

void MainView::refresh() {
    emit refreshView(this);
    LOG_INFO << "MainView emit refreshView";
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
//    this->calcBtn->clicked(true);
//    connect(calcBtn, &QPushButton::clicked, this, &MainView::calcClicked);
//    this->calcBtn->setAttribute(Qt::WA_TransparentForMouseEvents, false);
//    QCoreApplication::processEvents();
}
