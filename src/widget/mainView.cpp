#include "mainView.h"
#include "hashdataModel.h"
#include "base64Model.h"
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
    inputDataView = new InputDataView();
    mainLayout->addWidget(inputDataView);

    auto *hashDataModel = new HashDataModel;
    hashDataView = new HashDataView();
    hashDataView->setModel(hashDataModel);

    connect(this, &MainView::refreshView, hashDataView, &HashDataView::refresh);
    connect(this, &MainView::refreshView, this, &MainView::calcCompleted);

    auto *base64Model = new Base64Model;
    base64View = new Base64View();
    base64View->setModel(base64Model);
    connect(this, &MainView::refreshView, base64View, &Base64View::refresh);

    tabWidget = new QTabWidget(this);

    tabWidget->addTab(hashDataView, tr(calculateEnumStrings[static_cast<int>(CalculateEnum::hash)]));
    tabWidget->addTab(base64View, tr(calculateEnumStrings[static_cast<int>(CalculateEnum::base64)]));
    connect(tabWidget, &QTabWidget::currentChanged,this, &MainView::currentTabChanged);

    mainLayout->addWidget(tabWidget);
    mainLayout->addStretch();
    mainLayout->addWidget(line);
    mainLayout->addWidget(buttonBox);
    setLayout(mainLayout);

    auto *mainViewModel = new MainViewModel();
    mainViewModel->setHashDataModel(hashDataModel);
    this->setModel(mainViewModel);

    connect(inputDataView, &InputDataView::dataTypeChanged, hashDataView, &HashDataView::clearData);
    connect(inputDataView, &InputDataView::dataChanged, hashDataView, &HashDataView::clearData);

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
    if (!this->calcBtn->isEnabled()) {
        return;
    }
    this->calcBtn->setEnabled(false);
    this->setCursor(Qt::BusyCursor);

    switch (tabWidget->currentIndex()) {
        case static_cast<int>(CalculateEnum::hash):
            emit calculate(this, CalculateEnum::hash);
            break;
        case static_cast<int>(CalculateEnum::base64):
            emit calculate(this, CalculateEnum::base64);
            break;
    }
    LOG_INFO << "emit calculate(this)";
}

void MainView::refresh() {
    emit refreshView(this);
    LOG_INFO << "MainView emit refreshView";
}

HashDataView *MainView::getHashDataView() {
    return this->hashDataView;
}

InputDataView *MainView::getInputDataView() {
    return this->inputDataView;
}

void MainView::calcCompleted() {
    this->setCursor(Qt::ArrowCursor);
    this->calcBtn->setEnabled(true);
}

void MainView::currentTabChanged(int index) {
    auto *mainViewModel = dynamic_cast<MainViewModel *>(this->getModel());
    if (nullptr == mainViewModel) {
        return;
    }
    if (index == 0) {
        mainViewModel->setHashDataModel(dynamic_cast<HashDataModel *>(this->hashDataView->getModel()));
    } else if (index == 1) {
        mainViewModel->setBase64Model(dynamic_cast<Base64Model *>(this->base64View->getModel()));
    }
}
