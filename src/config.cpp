//
// Created by Spark on 2021-04-20.
//

#include "config.h"

#include <QSettings>

ConfigIni::ConfigIni() : pathFile("config.ini"), settings(new QSettings(pathFile, QSettings::IniFormat)) {
    settings->setIniCodec("UTF-8");
}

ConfigIni::~ConfigIni() {
    if (nullptr != settings) {
        // 销毁前同步
        settings->sync();
        settings->deleteLater();
        settings = nullptr;
    }
}

ConfigIni &ConfigIni::getInstance() {
    static ConfigIni instance;
    return instance;
}

void ConfigIni::setPathFile(const QString &path_file) {
    if (path_file != this->pathFile) {
        this->pathFile = path_file;
        // 及时同步之前的
        settings->sync();
        // 改变路径
        settings->setPath(settings->format(), settings->scope(), path_file);
        settings->setIniCodec("UTF-8");
    }
}

void ConfigIni::iniWrite(const QString &key, const QVariant &value) {
    settings->setValue(key, value);
}

bool ConfigIni::iniContains(const QString &key) {
    return settings->contains(key);
}

QVariant ConfigIni::iniRead(const QString &key, const QVariant &defaultValue) {
    if (!settings->contains(key)) { // 不存在
        settings->setValue(key, defaultValue);  // 使用默认值创建
        return defaultValue;    // 返回默认值
    }
    return settings->value(key);
}


