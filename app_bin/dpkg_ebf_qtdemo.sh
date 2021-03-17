Version=1.0.0.0
Package=ebf-157-qtdemo_1.0.0.0_armhf.deb

mkdir -p  ebfdemo
rm -rf ebfdemo/*
rm -rf $Package

USRLIB=ebfdemo/usr/lib
mkdir -p ${USRLIB}

#ffmpeg相关的库
cp -d -R ../ffmpeg/armlib/libavformat*              ${USRLIB}
cp -d -R ../ffmpeg/armlib/libavcodec*               ${USRLIB}
cp -d -R ../ffmpeg/armlib/libavutil*                ${USRLIB}
cp -d -R ../ffmpeg/armlib/libavfilter*              ${USRLIB}
cp -d -R ../ffmpeg/armlib/libswresample*            ${USRLIB}
cp -d -R ../ffmpeg/armlib/libavdevice*              ${USRLIB}
cp -d -R ../ffmpeg/armlib/libavfilter*              ${USRLIB}
cp -d -R ../ffmpeg/armlib/libswscale*               ${USRLIB}

#qtui和skin库
cp -d -R ../thirdpart/libskin/lib/libSkin*	    ${USRLIB}
cp -d -R ../thirdpart/libqui/lib/libQtUi*	    ${USRLIB}

#字体
USRFONT=ebfdemo/usr/share/fonts
mkdir -p ${USRFONT}
cp -r    ttf/*                                      ${USRFONT}

#输入法
INPUT=ebfdemo/usr/lib/arm-linux-gnueabihf/qt5/plugins/platforminputcontexts/
mkdir -p ${INPUT}
cp -r conf/platforminputcontexts/libSoft-keyboard.so ${INPUT}

#qt-app中的资源文件和配置文件
APPINSTALL=ebfdemo/usr/local/qt-app
mkdir -p ${APPINSTALL}
cp -r 	 conf                                       ${APPINSTALL}
cp -r 	 dict                                       ${APPINSTALL}
cp -r 	 ebook                                      ${APPINSTALL}
cp -r 	 lrc                                        ${APPINSTALL}
cp -r 	 music                                      ${APPINSTALL}
cp -r 	 nes                                        ${APPINSTALL}
cp -r 	 notepad                                    ${APPINSTALL}
cp -r 	 photos                                     ${APPINSTALL}
cp -r 	 record                                     ${APPINSTALL}
cp -r 	 translations                               ${APPINSTALL}
cp -r 	 video                                      ${APPINSTALL}
cp -r 	 App                                        ${APPINSTALL}
cp -r 	 InfoNes                                    ${APPINSTALL}
cp -r 	 run.sh                                     ${APPINSTALL}
cp -r 	 run_myapp.sh                               ${APPINSTALL}
cp -r 	 run_eglfs.sh                               ${APPINSTALL}

#修改脚本执行权限
chmod 775 ebfdemo/usr/local/qt-app/run_eglfs.sh
chmod 775 ebfdemo/usr/local/qt-app/run.sh

#deb控制信息

# systemd执行qt run.sh
mkdir -p ebfdemo/lib/systemd/system
cat >ebfdemo/lib/systemd/system/ebf-qtdemo.service<<EOF
[Unit]
Description = ebf-qtdemo qtdemo
After=actlogo.service

[Service]
ExecStart = /usr/local/qt-app/run.sh
Type = simple

[Install]
WantedBy = multi-user.target
EOF

mkdir -p ebfdemo/DEBIAN
# 添加程序信息
cat >ebfdemo/DEBIAN/control<<EOF
Package: ebf-157-qtdemo
Version: $Version
Section: utils
Priority: optional
Architecture: armhf
Depends:devscan,libts-bin,alsa-utils,qt5-default,libqt5multimedia5,libqt5multimedia5-plugins,gstreamer1.0-plugins-base,gstreamer1.0-tools,gstreamer1.0-plugins-bad,gstreamer1.0-plugins-good,gstreamer1.0-alsa,gstreamer1.0-libav
Installed-Size: 512
Maintainer: [url=mailto:sunwill_chen@hotmail.com]sunwill_chen#hotmail.com
Description: soft package
EOF

# 添加自启动服务
cat >ebfdemo/DEBIAN/postinst<<EOF
#!/bin/bash
systemctl enable ebf-qtdemo
EOF

chmod 775 ebfdemo/DEBIAN/postinst

#打包
dpkg -b ebfdemo $Package
