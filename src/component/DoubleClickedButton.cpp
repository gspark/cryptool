//
// Created by Spark on 2021-05-17.
//

#include "DoubleClickedButton.h"

#include "../logger/Logger.h"

#include <QEvent>
#include <QTimer>

DoubleClickedButton::DoubleClickedButton(QWidget *parent) : QPushButton(parent),
                                                            m_single_clicked_timer(new QTimer(this)),
                                                            m_bDoubleClicked(false) {
    m_single_clicked_timer->setSingleShot(true);
    connect(m_single_clicked_timer, &QTimer::timeout, this, &DoubleClickedButton::singleClicked);
}

DoubleClickedButton::DoubleClickedButton(const QString &text, QWidget *parent) : DoubleClickedButton(parent) {
    setText(text);
}

DoubleClickedButton::DoubleClickedButton(const QIcon &icon, const QString &text, QWidget *parent)
        : DoubleClickedButton(text, parent) {
    setIcon(icon);
}

DoubleClickedButton::~DoubleClickedButton() {
    delete m_single_clicked_timer;
}

bool DoubleClickedButton::event(QEvent *event) {
    switch (event->type()) {
        case QEvent::MouseButtonRelease:
            if (m_bDoubleClicked) {
                //如果是第二次进入，重置状态
                m_bDoubleClicked = false;
            } else {
                //这里需要一个超时判断，超时还没进入MouseButtonDblClick事件才算是单击效果
                //测试发现间隔时间最好不要低于10ms，否则不够两个事件的反馈间隔，如果需要延迟，可以自行修改间隔时间
                LOG_INFO << "MouseButtonRelease:" << this->isEnabled();
                m_single_clicked_timer->start(5);
            }
            break;
        case QEvent::MouseButtonDblClick:
            //进入双击事件停止掉定时器
            m_single_clicked_timer->stop();
            m_bDoubleClicked = true;
            LOG_INFO << "MouseButtonDblClick";
            emit doubleClicked();
            break;
        default:
            break;
    }

    return QPushButton::event(event);
}

