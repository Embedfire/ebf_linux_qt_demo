#! /bin/sh

# 指定显示平台插件
# QT_QPA_PLATFORM 或者-platform命令行选项指定其他设置
export QT_QPA_PLATFORM=eglfs
# 此环境变量强制执行特定的插件
# QT_QPA_EGLFS_INTEGRATION 设置为eglfs_kms将使用KMS / DRM后端
export QT_QPA_EGLFS_INTEGRATION=eglfs_kms
# KMS / DRM后端还通过JSON文件支持自定义配置
# QT_QPA_EGLFS_KMS_CONFIG 指定配置文件的路径
export QT_QPA_EGLFS_KMS_CONFIG=/usr/local/qt-app/conf/cursor.json
# 指定将current选择一种分辨率与当前模式匹配的模式
# QT_QPA_EGLFS_ALWAYS_SET_MODE
export QT_QPA_EGLFS_ALWAYS_SET_MODE=1
# 默认情况下，KMS后端将使用旧版API，但是您可以启用DRM原子API，
# 通过将QT_QPA_EGLFS_KMS_ATOMIC环境变量设置为1。
export QT_QPA_EGLFS_KMS_ATOMIC=1

#export DISPLAY=':0.0'
export QT_QPA_FB_DRM=1

# Qt应用程序将在Qt的lib/fonts目录中查找字体，QT_QPA_FONTDIR环境变量来覆盖此目录
#export QT_QPA_FONTDIR=/usr/share/fonts/

# 鼠标设备
# QT_QPA_EVDEV_MOUSE_PARAMETERS
export QT_QPA_EVDEV_MOUSE_PARAMETERS=abs
# 键盘设备
# QT_QPA_EVDEV_KEYBOARD_PARAMETERS
# 触摸屏设备
# QT_QPA_EVDEV_TOUCHSCREEN_PARAMETERS

# eglfs 禁用内置输入处理程序
# QT_QPA_EGLFS_DISABLE_INPUT
#export QT_QPA_EGLFS_DISABLE_INPUT=1
# linuxfb 禁用内置输入处理程序
# QT_QPA_FB_DISABLE_INPUT

# eglfs 未设置时候，鼠标光标就会出现
# QT_QPA_EGLFS_HIDECURSOR
# linuxfb 未设置时候，鼠标光标就会出现
# QT_QPA_FB_HIDECURSOR

# eglfs 启用tslib支持
# QT_QPA_EGLFS_TSLIB
export QT_QPA_EGLFS_TSLIB=1
# linuxfb 启用tslib支持
# QT_QPA_FB_TSLIB

# 传递设备名称
# TSLIB_TSDEVICE
# export TSLIB_TSDEVICE=/dev/input/$eventx
# evdevtablet 插件为Wacom和类似的基于笔的平板​​电脑提供基本支持。
# QT_QPA_GENERIC_PLUGINS
# export QT_QPA_GENERIC_PLUGINS=tslib:/dev/input/$eventx

# export TSLIB_TSDEVICE=/dev/input/$eventx
# export TSLIB_TSEVENTTYPE=INPUT
# 指定触摸屏校准文件
# export TSLIB_CONFFILE=/etc/ts.conf
# 指定触摸屏校准程序
# export TSLIB_CALIBFILE=/etc/pointercal

# 开启调试
# export QT_LOGGING_RULES=qt.qpa.gl=true
# export QSG_INFO=1
# export QT_DEBUG_PLUGINS=1

#导出qtdemo的安装目录
export APP_DIR=/usr/local/qt-app
$APP_DIR/App
