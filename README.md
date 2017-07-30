# 深度拼音助手

深度拼音助手是一款帮助小朋友学习拼音的工具，启动助手以后说出想拼写的单词，会自动用讯飞API转换语音成为对应的汉字和拼音。
小朋友根据语音识别出的汉字拼音进行拼音输入法学习打字。

## 依赖

拷贝讯飞的动态库到系统目录:

* sudo cp ./lib/libmsc.so /usr/lib/x86_64-linux-gnu/

## 安装方法

* mkdir build
* cd build
* qmake ..
* make

## 使用

* ./deepin-font-installer

建议把这个命令绑定到快捷键，方便快速唤醒拼音助手。

## License

深度拼音助手以GPLv3协议发布，禁止违反GPLv3协议非法闭源.
