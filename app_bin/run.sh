#! /bin/bash

type devscan

#判断devscan是否存在，不存在提示安装
if [ $? -eq 0 ]; then
    #未检查到触摸屏则一直检测不启动app
<<<<<<< HEAD
    timeout=0
=======
>>>>>>> b789fd9b3146a02734b4dec743febfcd5ae4c61d
    while [ ! $eventx ]
    do
        #寻找名叫goodix-ts的触摸屏驱动
        eventx=$(devscan "goodix-ts")
        #没有找到则寻找Goodix Capacitive TouchScreen
        if [ ! $eventx ]; then
                eventx=$(devscan "Goodix Capacitive TouchScreen")
        fi
        #没有找到则寻找iMX6UL Touchscreen Controller
        if [ ! $eventx ]; then
                eventx=$(devscan "iMX6UL Touchscreen Controller")
        fi
        ########################################################
        # 添加你自己的显示屏驱动
        # 首先 sudo evtest  查看是否存在显示屏驱动
        # 存在添加类似于上面的判断 改为你自己的显示屏驱动名称
        ########################################################
<<<<<<< HEAD
        if [ $timeout -ge 5 ]; then
            break
        fi
        let timeout=$timeout+1
        sleep 1
=======
        sleep 5
>>>>>>> b789fd9b3146a02734b4dec743febfcd5ae4c61d
    done
    #输出当前触摸屏驱动
    echo "eventx=$eventx"
    if [ "$eventx " != " " ]; then
        #判断触摸屏校准文件是否存在，不存在则校准触摸屏，/etc/pointercal为触摸屏校准文件
        if [ ! -f "/etc/pointercal" ]; then
            #指定触摸屏设备
            export TSLIB_TSDEVICE=/dev/input/$eventx
            type ts_calibrate
            if [ $? -eq 0 ]; then
                ts_calibrate
            fi
        fi
        #同步QT默认的坐标轴和触摸屏的坐标轴
        #export QT_QPA_EVDEV_TOUCHSCREEN_PARAMETERS=/dev/input/$eventx:rotate=90:invertx
        export QT_QPA_EVDEV_TOUCHSCREEN_PARAMETERS=/dev/input/$eventx:rotate=0
    else
        echo "eventx is null"
    fi
else
    echo "please install devscan"
    echo
    echo "sudo apt-get install devscan"
    exit
fi

#导出qtdemo的安装目录
export APP_DIR=/usr/local/qt-app
#指定qt插件路径
export QT_QPA_PLATFORM_PLUGIN_PATH=/usr/lib/plugins
#指定qt库路径
#export LD_LIBRARY_PATH=/lib:/usr/lib
#指定字体库
export QT_QPA_FONTDIR=/usr/lib/fonts
#qt命令路径
#export PATH=$PATH:$QT_DIR/libexec
#指定显示终端
export QT_QPA_PLATFORM=linuxfb:fb=/dev/fb0
#禁用QT自带的输入检测
#export QT_QPA_FB_DISABLE_INPUT=1
#TS配置文件
export TSLIB_CONFFILE=/etc/ts.conf
#TS校准文件
export TSLIB_CALIBFILE=/etc/pointercal
#触摸配置
export QT_QPA_GENERIC_PLUGINS=tslib:/dev/input/$eventx
#指定鼠标设备
export QWS_MOUSE_PROTO=tslib
#启用tslib支持而不是依赖于Linux多点触控协议和事件设备
export QT_QPA_EGLFS_TSLIB=1
export QT_QPA_FB_TSLIB=1

echo "start app..."
#运行App
$APP_DIR/App