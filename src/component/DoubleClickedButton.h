//
// Created by Spark on 2021-05-17.
//

#ifndef CRYPTOOL_DOUBLECLICKEDBUTTON_H
#define CRYPTOOL_DOUBLECLICKEDBUTTON_H

#include <QPushButton>

class QTimer;

class DoubleClickedButton : public QPushButton {
Q_OBJECT

public:
    explicit DoubleClickedButton(QWidget *parent = Q_NULLPTR);

    explicit DoubleClickedButton(const QString &text, QWidget *parent = Q_NULLPTR);

    DoubleClickedButton(const QIcon &icon, const QString &text, QWidget *parent = Q_NULLPTR);

    ~DoubleClickedButton() override;

protected:
    bool event(QEvent *event) override;

signals:

    void singleClicked();

    void doubleClicked();

private:
    bool m_bDoubleClicked;
    QTimer *m_single_clicked_timer;
};


#endif //CRYPTOOL_DOUBLECLICKEDBUTTON_H
