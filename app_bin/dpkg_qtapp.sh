Version=0.1.3.1
Package=ebf-qtapp_0.1.3.1_armhf.deb

#deb包 临时目录
PackageDir=qtapp

mkdir -p  $PackageDir

#deb控制信息

mkdir -p $PackageDir/DEBIAN
# 添加程序信息
cat >$PackageDir/DEBIAN/control<<EOF
Package: qt-app
Version: $Version
Section: utils
Priority: optional
Architecture: armhf
Depends:ebf-qtdemo
Installed-Size: 512
Maintainer: embedfire <embedfire@embedfire.com>
Description: soft package
EOF


#打包
dpkg -b $PackageDir $Package

# rm -rf $PackageDir