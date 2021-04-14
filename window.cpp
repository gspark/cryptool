#include "window.h"

#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QSpinBox>

window::window(QWidget *parent)
    : QWidget(parent)
{
    createFormGroupBox();

    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                                     | QDialogButtonBox::Cancel);

    connect(buttonBox, &QDialogButtonBox::accepted, this, &QWidget::close);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QWidget::close);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(formLayout);
    mainLayout->addWidget(buttonBox);
    setLayout(mainLayout);
}

window::~window()
{
}

void window::createFormGroupBox()
{
    formLayout = new QFormLayout;
    formLayout->addRow(new QLabel(tr("Line 1:")), new QLineEdit);
    formLayout->addRow(new QLabel(tr("Line 2, long text:")), new QComboBox);
    formLayout->addRow(new QLabel(tr("Line 3:")), new QSpinBox);
}
