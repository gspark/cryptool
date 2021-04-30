//
// Created by Spark on 2021-04-29.
//

#include "abstractPresenter.h"

AbstractPresenter::AbstractPresenter() = default;

AbstractPresenter::AbstractPresenter(AbstractView *view, AbstractModel *model) {
    this->view = view;
    this->model = model;
}

AbstractPresenter::~AbstractPresenter() = default;