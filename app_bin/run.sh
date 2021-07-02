#! /bin/bash

type devscan

#设置屏幕旋转角度 默认不旋转
rotation=0

#检测屏幕设备文件 MIPI屏幕自动旋转90度
if [ -e "/sys/bus/platform/devices/5a000000.dsi/5a000000.dsi.0" ]; then
    rotation=90
fi

# 旋转屏幕需要重新校准，每次都需要重新校准
if [ $rotation -ne 0 ]; then
    rm /etc/pointercal
    #指定qt插件路径 即需要旋转的时候，使用使用我们自己插件
    export QT_QPA_PLATFORM_PLUGIN_PATH=/usr/lib/plugins
fi

#判断devscan是否存在，不存在提示安装
if [ $? -eq 0 ]; then
    #未检查到触摸屏则一直检测不启动app
    timeout=0
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
        if [ $timeout -ge 5 ]; then
            break
        fi
        let timeout=$timeout+1
        sleep 1
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
                if [ $rotation -eq 0 ]; then
                    ts_calibrate -r 0
                elif [ $rotation -eq 90 ]; then
                    ts_calibrate -r 1
                elif [ $rotation -eq 180 ]; then
                    ts_calibrate -r 2
                elif [ $rotation -eq 270 ]; then
                    ts_calibrate -r 3
                else 
                    ts_calibrate
                fi
            fi
        fi
        #同步QT默认的坐标轴和触摸屏的坐标轴
        #export QT_QPA_EVDEV_TOUCHSCREEN_PARAMETERS=/dev/input/$eventx:rotate=90:invertx
        export QT_QPA_EVDEV_TOUCHSCREEN_PARAMETERS=/dev/input/$eventx:rotate=$rotation
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
#指定qt库路径
#export LD_LIBRARY_PATH=/lib:/usr/lib
#指定字体库
export QT_QPA_FONTDIR=/usr/share/fonts
#qt命令路径
#export PATH=$PATH:$QT_DIR/libexec

# if [ $rotation -ne 0 ]; then
#     #指定qt插件路径 即需要旋转的时候，使用使用我们自己插件
#     export QT_QPA_PLATFORM_PLUGIN_PATH=/usr/lib/plugins
#     #指定显示终端 和 旋转角度
#     export QT_QPA_PLATFORM=linuxfb:fb=/dev/fb0:rotation=$rotation
# else
#     #指定显示终端
#     export QT_QPA_PLATFORM=linuxfb:fb=/dev/fb0
# fi

#指定显示终端 和 旋转角度
export QT_QPA_PLATFORM=linuxfb:fb=/dev/fb0:rotation=$rotation

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