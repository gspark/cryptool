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

set(PREBUILT_LIB_DIRECTORY D:/ops/msys64/mingw64/lib)

# Qt
include_directories(d:/osc/Qt/5.15.2/qtbase/src/*.c)
include_directories(d:/osc/Qt/5.15.2/qtbase/src/*.cpp)


set(QT_VERSION 5)
set(REQUIRED_LIBS Core Gui Widgets)
set(REQUIRED_LIBS_QUALIFIED Qt5::Core Qt5::Gui Qt5::Widgets)

add_executable(${PROJECT_NAME} WIN32
        src/main.cpp
        src/ui/window.h
        src/ui/window.cpp
        src/crypto/digest/md5.h
        src/crypto/digest/md5.cpp
        src/ui/inputdata.cpp
        src/ui/inputdata.h
        src/ui/hashdata.cpp
        src/ui/hashdata.h
        src/config.cpp
        src/config.h)

# 查找Qt库
find_package(Qt${QT_VERSION} COMPONENTS ${REQUIRED_LIBS} REQUIRED)
target_link_libraries(${PROJECT_NAME} ${REQUIRED_LIBS_QUALIFIED})

# openssl
# 静态链接openssl
set(OPENSSL_USE_STATIC_LIBS TRUE)
find_package(OpenSSL REQUIRED)
target_link_libraries(${PROJECT_NAME} OpenSSL::Crypto OpenSSL::SSL)

# zlib
find_package(ZLIB REQUIRED)
if (ZLIB_FOUND)
    message(STATUS "zlib lib = ${ZLIB_LIBRARIES}")
    include_directories(${ZLIB_INCLUDE_DIRS})
#    target_link_libraries(${PROJECT_NAME} ${ZLIB_LIBRARIES})
    # dll.a 有bug
    target_link_libraries(${PROJECT_NAME} ${PREBUILT_LIB_DIRECTORY}/libz.a)
    target_link_libraries(${PROJECT_NAME} ${PREBUILT_LIB_DIRECTORY}/libzstd.a)
endif ()








