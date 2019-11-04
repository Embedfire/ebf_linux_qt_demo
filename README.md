# qt app

野火liunx-qt5-demo资料说明

1、发布包
该目录为:fire-app-release.tar.bz2，
1）、解压到开发板目录，
2）、修改ldsh脚本的qt目录
3）、执行命令：#：source ./ldsh
4)、 启动App: #: ./App

2、源码包 arm-NES-linux.tar.bz2为InfoNes模拟器源码，编译方法如下
1）、解压，进入目录
2）、 cd linux 
3）、 配置gcc环境变量 : export PATH=/opt/arm-gcc/bin:$PATH
4）、、 执行make
5)）、当前目录下的InfoNes即为模拟器应用程序，拷贝至App同目录
6）、测试模拟器： ./InfoNes xxxx.nes

3、源码包：FireApp-src-v1.1.0.1-20191102.tar.gz为Qt5版本的应用程序，编译流程如下
1）、安装sdk，并执行环境变量脚本
source /opt/fsl-imx-x11/4.1.15-2.1.0/environment-setup-cortexa7hf-neon-poky-linux-gnueabi
2）、解压目录，并进入FileApp目录
3）、执行目录下编译脚本$: ./build.sh
4）、脚本执行完会自动打包应用app，app生成目录在当前目录x/FileApp/app_bin

4、Qt5-demo源码介绍，本程序是基于Qt5开发的，不支持Qt4直接编译。
1）、FileApp.pro为多工程目录，里面的QtUi为demo的自定义基础控件库。Skin为皮肤资源文件。这2个都是必须的，且比较重要。
2）、App为demo的综合程序，即为开发板看到的App程序。
3）、其他注释的工程为单个的应用程序，可取消注释，单独编译。
4）、其他不懂的可以联系技术支持，随时在线。
