cmake_minimum_required(VERSION 3.16)
# 工程名
project(cryptool LANGUAGES CXX)

#set(CMAKE_INCLUDE_CURRENT_DIR ON)

# 打开Qt的MOC、UI等功能
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置可执行文件的输出目录
#SET(EXECUTABLE_OUTPUT_PATH z:/temp/${PROJECT_NAME}/bin)
#SET(CMAKE_C_COMPILE_OBJECT z:/temp/${PROJECT_NAME}/obj)
#SET(CMAKE_CXX_COMPILE_OBJECT z:/temp/${PROJECT_NAME}/obj)

#定义变量
set(PREBUILT_LIB_DIRECTORY D:/ops/msys64/mingw64/lib)

set(CMAKE_DEBUG_POSTFIX "d" CACHE STRING "add a postfix, usually d on windows")

# Qt
#include_directories(d:/osc/Qt/5.15.2/qtbase/src/*.c)
#include_directories(d:/osc/Qt/5.15.2/qtbase/src/*.cpp)

#set(CMAKE_MODULE_PATH d:/ops/qt-6.1.0-mingw64/static/lib/cmake/Qt6)
list(APPEND CMAKE_PREFIX_PATH "d:/ops/qt-6.1.1-mingw64/static")
#set(REQUIRED_LIBS Core Gui Widgets)
#set(REQUIRED_LIBS_QUALIFIED Qt6::Core Qt6::Gui Qt6::Widgets)

add_executable(${PROJECT_NAME}
        src/resource.rc
        src/main.cpp
        src/widget/mainView.h
        src/widget/mainView.cpp
        src/crypto/digest/md4_5.h
        src/crypto/digest/md4_5.cpp
        src/widget/inputdataView.cpp
        src/widget/inputdataView.h
        src/widget/hashdataView.cpp
        src/widget/hashdataView.h
        src/config.cpp
        src/config.h src/crypto/digest/str.cpp src/crypto/digest/str.h src/crypto/digest/sha.cpp src/crypto/digest/sha.h
        src/pattern/abstractView.h src/pattern/abstractPresenter.h src/pattern/abstractModel.h src/pattern/abstractView.cpp
        src/pattern/abstractPresenter.cpp src/widget/mainViewPresenter.cpp src/widget/mainViewPresenter.h
        src/widget/hashdataModel.cpp src/widget/hashdataModel.h src/widget/mainViewModel.cpp src/widget/mainViewModel.h
        src/pattern/abstractModel.cpp src/crypto/digest/sm3.cpp src/crypto/digest/sm3.h
        src/logger/Logger.h
        src/logger/Logger.cpp
        src/logger/LoggerTemplate.h src/component/DoubleClickedButton.cpp src/component/DoubleClickedButton.h
        src/widget/base64View.cpp src/widget/base64View.h
#        src/crypto/digest/base64.cpp
#        src/crypto/digest/base64.h
        src/widget/base64Model.cpp
        src/widget/base64Model.h src/crypto/digest/crc32.cpp src/crypto/digest/crc32.h)

set_target_properties(${PROJECT_NAME} PROPERTIES
        WIN32_EXECUTABLE TRUE
        )

# 查找Qt库
find_package(Qt6 COMPONENTS Core)
find_package(Qt6 COMPONENTS Gui)
find_package(Qt6 COMPONENTS Widgets)

target_link_libraries(${PROJECT_NAME}
        Qt::Core
        Qt::Gui
        Qt::Widgets)

# openssl
# 静态链接openssl
set(OPENSSL_USE_STATIC_LIBS TRUE)
find_package(OpenSSL REQUIRED)
if (OPENSSL_FOUND)
    message(STATUS "OpenSSL Found!")
    # Qt6 链接 dll.a 有依赖dll
    #    target_link_libraries(${PROJECT_NAME} OpenSSL::Crypto OpenSSL::SSL)
    target_link_libraries(${PROJECT_NAME} ${PREBUILT_LIB_DIRECTORY}/libcrypto.a)
endif ()

# zlib
find_package(ZLIB REQUIRED)
if (ZLIB_FOUND)
    message(STATUS "zlib lib = ${ZLIB_LIBRARIES}")
    include_directories(${ZLIB_INCLUDE_DIRS})
    #    target_link_libraries(${PROJECT_NAME} ${ZLIB_LIBRARIES})
    # 链接 dll.a 有依赖dll
    target_link_libraries(${PROJECT_NAME} ${PREBUILT_LIB_DIRECTORY}/libz.a)
    target_link_libraries(${PROJECT_NAME} ${PREBUILT_LIB_DIRECTORY}/libzstd.a)
endif ()

#链接gcc-g++静态库
if (MINGW)
    message(STATUS "is mingw")
    #    set(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "${CMAKE_SHARED_LIBRARY_LINK_C_FLAGS} -static-libgcc -s")
    #    set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "${CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS} -static-libgcc -static-libstdc++ -s")
    set(BUILD_SHARED_LIBS OFF)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -s")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s")
    set(CMAKE_EXE_LINKER_FLAGS "-static -static-libgcc -static-libstdc++")
    #    target_link_libraries(${PROJECT_NAME} ${CMAKE_DL_LIBS} -lpthread)
endif ()








