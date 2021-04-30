//
// Created by Spark on 2021-04-29.
//

#ifndef CRYPTOOL_ABSTRACTPRESENTER_H
#define CRYPTOOL_ABSTRACTPRESENTER_H

class AbstractModel;

class AbstractView;

class AbstractPresenter {
public:
    AbstractPresenter();

    AbstractPresenter(AbstractView *view, AbstractModel *model);

    virtual ~AbstractPresenter() = 0;

protected:
    AbstractView *view{};
    AbstractModel *model{};
};


#endif //CRYPTOOL_ABSTRACTPRESENTER_H
