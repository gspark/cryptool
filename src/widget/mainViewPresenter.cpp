//
// Created by Spark on 2021-04-29.
//

#include "mainViewPresenter.h"
#include "hashdataModel.h"
#include "mainViewModel.h"
#include "mainView.h"

#include "../logger/Logger.h"
#include "../crypto/digest/md4_5.h"
#include "../crypto/digest/sha.h"
#include "../crypto/digest/sm3.h"

#include <thread>
#include <QEventLoop>

MainViewPresenter::MainViewPresenter(AbstractView *view, AbstractModel *model) : AbstractPresenter(view, model) {
    if (nullptr != view) {
        auto *v = dynamic_cast<MainView *>(view);
        if (nullptr != v) {
            connect(v, &MainView::calculate, this, &MainViewPresenter::calculate);
//            connect(this, &MainViewPresenter::refresh, v, &MainView::refresh);
        }
    }
}

MainViewPresenter::~MainViewPresenter() {
    delete this->model;
}

void MainViewPresenter::calculate(MainView *view, CalculateEnum type) {
    if (nullptr == view) {
        return;
    }
    std::istream *data_ptr = view->getInputDataView()->getData();

    if (nullptr == data_ptr) {
        this->view->refresh();
        return;
    }

    switch (type) {
        case CalculateEnum::hash:
            hashCalc(view, data_ptr);
            break;
        case CalculateEnum::base64:
            break;
    }
}


void MainViewPresenter::hashCalc(MainView *view, std::istream *data_ptr) {
    // 定义一个loop对象
    QEventLoop loop;
    // 绑定信号  在loop收到界面发送的signalRunOver信号后，退出循环
    connect(view, &MainView::signalRunOver, &loop, &QEventLoop::quit);

    std::vector<int> hashList = view->getHashDataView()->getHashList();

    std::vector<std::thread *> ths;
    std::vector<std::ifstream *> ifstreams;

    auto *iss = dynamic_cast<std::istringstream *>(data_ptr);
    if (nullptr != iss) {
        for (int i : hashList) {
            auto *thr = new std::thread(&MainViewPresenter::doCalc1, this, iss, i);
            ths.push_back(thr);
        }
    } else {
        auto *ifs = dynamic_cast<std::ifstream *>(data_ptr);
        if (nullptr != ifs) {
            size_t len = hashList.size();
            for (size_t i = 0; i < len; ++i) {
                auto *thr = new std::thread(&MainViewPresenter::doCalc2, this, ifs, hashList[i]);
                ths.push_back(thr);

                // ifstream 线程不安全
                if (i < len - 1) {
                    ifstreams.push_back(ifs);
                    data_ptr = view->getInputDataView()->getData();
                    ifs = dynamic_cast<std::ifstream *>(data_ptr);
                }
            }
        }
    }

    std::thread testThread([&] {
        // runResult = 连接网络 、拷贝文件、等等耗时操作  实际执行的任务放在这个位置执行
        // 执行耗时操作完成后 发出信号  告知线程执行结束
        for (std::thread *thr: ths) {
            thr->join();
            delete thr;
        }

        delete data_ptr;

        for (std::ifstream *ifs: ifstreams) {
            delete ifs;
        }

        LOG_INFO << "The calculation is complete";
        emit view->signalRunOver();
        this->view->refresh();
    });
    testThread.detach();

    loop.exec();
    LOG_INFO << "loop.exec(exit)";
}


void MainViewPresenter::doCalc1(const std::istringstream *iss, int iEnum) {
    this->model = this->view->getModel();

    if (nullptr == this->model) {
        return;
    }

    auto *m = dynamic_cast<MainViewModel *>(this->model);
    if (nullptr == m) {
        return;
    }

    switch (iEnum) {
        case static_cast<int>(HashEnum::MD5) : {
            std::string md5str = MD4_5::md5_digestHex(iss->str());
            m->getHashDataModel()->setHashData(HashEnum::MD5, md5str);
        }
            break;
        case static_cast<int>(HashEnum::MD4) : {
            std::string md4str = MD4_5::md4_digestHex(iss->str());
            m->getHashDataModel()->setHashData(HashEnum::MD4, md4str);
        }
            break;
        case static_cast<int>(HashEnum::SHA1): {
            std::string sha = sha::sha1_digestHex(iss->str());
            m->getHashDataModel()->setHashData(HashEnum::SHA1, sha);
        }
            break;
        case static_cast<int>(HashEnum::SHA256): {
            std::string sha = sha::sha256_digestHex(iss->str());
            m->getHashDataModel()->setHashData(HashEnum::SHA256, sha);
        }
            break;
        case static_cast<int>(HashEnum::SHA384): {
            std::string sha = sha::sha384_digestHex(iss->str());
            m->getHashDataModel()->setHashData(HashEnum::SHA384, sha);
        }
            break;
        case static_cast<int>(HashEnum::SHA512): {
            std::string sha = sha::sha512_digestHex(iss->str());
            m->getHashDataModel()->setHashData(HashEnum::SHA512, sha);
        }
            break;
        case static_cast<int>(HashEnum::SM3): {
            std::string sm3 = SM3::sm3_digestHex(iss->str());
            m->getHashDataModel()->setHashData(HashEnum::SM3, sm3);
        }
            break;
        default:
            break;
    }
}

void MainViewPresenter::doCalc2(const std::ifstream *ifs, int iEnum) {
    this->model = this->view->getModel();

    if (nullptr == this->model) {
        return;
    }

    auto *m = dynamic_cast<MainViewModel *>(this->model);
    if (nullptr == m) {
        return;
    }

    switch (iEnum) {
        case static_cast<int>(HashEnum::MD5) : {
            std::string md5str = MD4_5::md5_digestHex((std::istream &) *ifs);
            m->getHashDataModel()->setHashData(HashEnum::MD5, md5str);
        }
            break;
        case static_cast<int>(HashEnum::MD4) : {
            std::string md4str = MD4_5::md4_digestHex((std::istream &) *ifs);
            m->getHashDataModel()->setHashData(HashEnum::MD4, md4str);
        }
            break;
        case static_cast<int>(HashEnum::SHA1): {
            std::string sha = sha::sha1_digestHex((std::istream &) *ifs);
            m->getHashDataModel()->setHashData(HashEnum::SHA1, sha);
        }
            break;
        case static_cast<int>(HashEnum::SHA256): {
            std::string sha = sha::sha256_digestHex((std::istream &) *ifs);
            m->getHashDataModel()->setHashData(HashEnum::SHA256, sha);
        }
            break;
        case static_cast<int>(HashEnum::SHA384): {
            std::string sha = sha::sha384_digestHex((std::istream &) *ifs);
            m->getHashDataModel()->setHashData(HashEnum::SHA384, sha);
        }
            break;
        case static_cast<int>(HashEnum::SHA512): {
            std::string sha = sha::sha512_digestHex((std::istream &) *ifs);
            m->getHashDataModel()->setHashData(HashEnum::SHA512, sha);
        }
            break;
        case static_cast<int>(HashEnum::SM3): {
            std::string sm3 = SM3::sm3_digestHex((std::istream &) *ifs);
            m->getHashDataModel()->setHashData(HashEnum::SM3, sm3);
        }
        default:
            break;
    }
}

void MainViewPresenter::base64Calc(MainView *view) {

}



