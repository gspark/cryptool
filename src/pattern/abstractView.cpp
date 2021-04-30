//
// Created by Spark on 2021-04-29.
//

#include "abstractView.h"


AbstractView::AbstractView()= default;

// 纯虚析构函数没有写函数体link会报错，这里加上。
AbstractView::~AbstractView() = default;

AbstractView::AbstractView(AbstractModel *model) {
    this->model = model;
}

void AbstractView::setModel(AbstractModel *m) {
    this->model = m;
}

AbstractModel *AbstractView::getModel() {
    return this->model;
}


