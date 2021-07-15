Version=1.0.0.2
Package=ebf-157-qtdemo_1.0.0.2_armhf.deb

#deb包 临时目录
PackageDir=ebfdemo

mkdir -p  $PackageDir

rm -rf $Package

USRLIB=$PackageDir/usr/lib
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

# qtui和skin库
cp -d -R ../thirdpart/libskin/lib/libSkin*          ${USRLIB}
cp -d -R ../thirdpart/libqui/lib/libQtUi*           ${USRLIB}

#字体
USRFONT=$PackageDir/usr/share/fonts
mkdir -p ${USRFONT}
cp -r    ttf/*                                      ${USRFONT}

#输入法
INPUT=$PackageDir/usr/lib/arm-linux-gnueabihf/qt5/plugins/platforminputcontexts/
mkdir -p ${INPUT}
cp -r conf/plugins/platforminputcontexts/libSoft-keyboard.so ${INPUT}

# 可旋转的 linuxfb
LinuxFb=$PackageDir/usr/lib/plugins/platforms/
mkdir -p ${LinuxFb}
cp -r conf/plugins/platforms/libqlinuxfb.so         ${LinuxFb}

#qt-app中的资源文件和配置文件
APPINSTALL=$PackageDir/usr/local/qt-app
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
chmod 775 $PackageDir/usr/local/qt-app/run_eglfs.sh
chmod 775 $PackageDir/usr/local/qt-app/run.sh

#deb控制信息

# systemd执行qt run.sh
mkdir -p $PackageDir/lib/systemd/system
cat >$PackageDir/lib/systemd/system/ebf-qtdemo.service<<EOF
[Unit]
Description = ebf-qtdemo qtdemo

[Service]
ExecStart = /usr/local/qt-app/run.sh
Type = simple

[Install]
WantedBy = multi-user.target
EOF

mkdir -p $PackageDir/DEBIAN
# 添加程序信息
cat >$PackageDir/DEBIAN/control<<EOF
Package: ebf-qtdemo
Version: $Version
Section: utils
Priority: optional
Architecture: armhf
Depends:devscan,libts-bin,alsa-utils,qt5-default,libqt5multimedia5,libqt5multimedia5-plugins,gstreamer1.0-plugins-base,gstreamer1.0-tools,gstreamer1.0-plugins-bad,gstreamer1.0-plugins-good,gstreamer1.0-alsa,gstreamer1.0-libav,peripheral,ipppd
Installed-Size: 512
Maintainer: embedfire <embedfire@embedfire.com>
Description: soft package
EOF

# 添加自启动服务
cat >$PackageDir/DEBIAN/postinst<<EOF
#!/bin/bash
systemctl enable ebf-qtdemo
EOF

chmod 775 $PackageDir/DEBIAN/postinst

#打包
dpkg -b $PackageDir $Package

rm -rf $PackageDir