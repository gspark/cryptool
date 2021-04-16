#include "window.h"

#include <QDialogButtonBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QCheckBox>
#include <QLineEdit>
#include <QComboBox>

window::window(QWidget *parent)
    : QWidget(parent)
{
    createFormGroupBox();

    buttonBox = new QDialogButtonBox(Qt::Horizontal);
    QPushButton *calcBtn = buttonBox->addButton(tr("&Calculate"), QDialogButtonBox::ActionRole);
    QPushButton *closeBtn = buttonBox->addButton(QDialogButtonBox::Close);

    connect(calcBtn,&QPushButton::clicked,this,&window::calculate);
    connect(closeBtn, &QPushButton::clicked, this, &QWidget::close);

    QFrame *line = new QFrame();
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(formLayout);
    mainLayout->addWidget(line);
    mainLayout->addWidget(buttonBox);
    setLayout(mainLayout);
}

window::~window()
{
// 一种正确的写法 qt5
#if 0
    QList<QWidget *> widgets = findChildren<QWidget *>("", Qt::FindDirectChildrenOnly);
    foreach(QWidget * widget, widgets)
    {
        delete widget;
    }
#endif
    setUpdatesEnabled(false);
    qDeleteAll(findChildren<QWidget*>("", Qt::FindDirectChildrenOnly));

    this->deleteLater();
}

void window::createFormGroupBox()
{
    formLayout = new QFormLayout;
    formLayout->addRow(new QCheckBox(tr("MD5")), new QLineEdit);
    formLayout->addRow(new QCheckBox(tr("MD4")), new QLineEdit);
    formLayout->addRow(new QCheckBox(tr("SHA1")), new QLineEdit);
}

void window::calculate()
{
    return;
}
