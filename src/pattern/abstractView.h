//
// Created by Spark on 2021-04-29.
//

#ifndef CRYPTOOL_ABSTRACTVIEW_H
#define CRYPTOOL_ABSTRACTVIEW_H

class AbstractModel;

class AbstractView {
public:
    AbstractView();

    explicit AbstractView(AbstractModel *model);

    // 纯虚析构函数没有写函数体link会报错，需要加上。
    virtual ~AbstractView() = 0;

public:
    virtual void setModel(AbstractModel *model);

    virtual AbstractModel *getModel();

    virtual void refresh() = 0;

protected:
    //{}对model初始化
    AbstractModel *model{};
};


#endif //CRYPTOOL_ABSTRACTVIEW_H
