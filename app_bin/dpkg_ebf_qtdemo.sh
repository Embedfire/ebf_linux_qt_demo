Version=1.0.0.0
Package=ebf-6ul-test_1.0.0.0_armhf.deb

# if [ ! -e App ]; then
#     echo "Please compile the program first"
#     exit 
# fi

echo "Package ${Package}"
echo "Version ${Version}"


echo -e "Copy temporary files"

#deb包 临时目录
PackageDir=ebfdemo

mkdir -p  $PackageDir

rm -rf $Package

USRLIB=$PackageDir/usr/lib
mkdir -p ${USRLIB}

#ffmpeg相关的库
cp -d -R ../ffmpeg/linuxlib/libavformat*              ${USRLIB}
cp -d -R ../ffmpeg/linuxlib/libavcodec*               ${USRLIB}
cp -d -R ../ffmpeg/linuxlib/libavutil*                ${USRLIB}
cp -d -R ../ffmpeg/linuxlib/libavfilter*              ${USRLIB}
cp -d -R ../ffmpeg/linuxlib/libswresample*            ${USRLIB}
cp -d -R ../ffmpeg/linuxlib/libavdevice*              ${USRLIB}
cp -d -R ../ffmpeg/linuxlib/libavfilter*              ${USRLIB}
cp -d -R ../ffmpeg/linuxlib/libswscale*               ${USRLIB}

#qtui和skin库
cp -d -R ../thirdpart/libskin/lib/libSkin*            ${USRLIB}
cp -d -R ../thirdpart/libqui/lib/libQtUi*             ${USRLIB}

#字体
# USRFONT=$PackageDir/usr/share/fonts
# mkdir -p ${USRFONT}
# cp -r    ttf/*                                      ${USRFONT}

#输入法
# INPUT=$PackageDir/usr/lib/arm-linux-gnueabihf/qt5/plugins/platforminputcontexts/
# mkdir -p ${INPUT}
# cp -r conf/platforminputcontexts/libSoft-keyboard.so ${INPUT}

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
cp -r 	 run.sh                                     ${APPINSTALL}

#修改脚本执行权限
chmod 775 $PackageDir/usr/local/qt-app/run.sh

#deb控制信息
echo -e "Creating deb control information"

# systemd执行qt run.sh
mkdir -p $PackageDir/lib/systemd/system
cat >$PackageDir/lib/systemd/system/ebf-qtdemo.service<<EOF
[Unit]
Description = ebf-qtdemo qtdemo
After=actlogo.service

[Service]
ExecStart = /usr/local/qt-app/run.sh
Type = simple

[Install]
WantedBy = multi-user.target
EOF

mkdir -p $PackageDir/DEBIAN
# 添加程序信息
cat >$PackageDir/DEBIAN/control<<EOF
Package: ebf-qtdemo-test
Version: $Version
Section: utils
Priority: optional
Architecture: armhf
Depends:devscan,libts-bin,alsa-utils,qt5-default,libqt5multimedia5,libqt5multimedia5-plugins,gstreamer1.0-plugins-base,gstreamer1.0-tools,gstreamer1.0-plugins-bad,gstreamer1.0-plugins-good,gstreamer1.0-alsa,gstreamer1.0-libav
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
echo -e "Package..."
dpkg -b $PackageDir $Package

rm -rf $PackageDir

echo -e "Package complete"