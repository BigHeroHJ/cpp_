##### Conan 的使用

##### conan profile 
默认的 conan profile 在～/.conan/profile/default
doc 指出，可以根据不同情况，使用不同的profile 比较靠谱
在使用Conan install 的时候 指定参数-pr --> --profil = xxxprofile 文件

**在一个profile 文件中也可以通过include 引入其他的profile**

**如果找不到 mission package 之类的**
看看https://conan.io/center/poco?version=1.9.4&os=Macos&tab=dependencies
**比如 看看 对应的 架构和compiler 是否有这个包**

**测试 比如要安装poco 包，先用conan inspect poco/1.9.4 查看，他会列出poco 的一些配置，**
比如 settings 中需要哪些， 
~ GavinCao@HW0013779 build$ conan inspect poco/1.9.4
name: poco
version: 1.9.4
url: https://github.com/conan-io/conan-center-index
homepage: https://pocoproject.org
license: BSL-1.0
author: None
description: Modern, powerful open source C++ class libraries for building network- and internet-based applications that run on desktop, server, mobile and embedded systems.
topics: ('building', 'networking', 'server', 'mobile', 'embedded')
generators: ('cmake', 'cmake_find_package')
exports: None
exports_sources: None
short_paths: False
apply_env: True
build_policy: None
revision_mode: hash

**注意 之前就是settings中 写错了 compiler, 少些了 build_type=Release导致下载不下来**

#### conan install 
conan install .. --pr xxxprofile_path 
类似cmake 一样 .. 会读取上一级的conanfile.txt 文件来install一些dependency
当前目录一般都是新建的build目录，所有的build 产物 都在build 目录中

install 结束都会给dependency 生产一个xxx.cmake 的一个编译文件，这个是
在conanfile 中指定了generator 为cmake 生成的cmake编译脚本，需要在自己的project中CMakeList.txt中 使用 才能吧install的package 导入进来

不指定 profile 用的是default 应该，也可以通过命令行输入
**conan install .. --settings os="Linux" --settings compiler="gcc" --settings arch=x86** 

#### conan remote 的使用
conan remote add xxxremote 
如果已经增加的remote 要修改位置
conan remote update xxxremote http://xxx/remote/url --insert=0 
插入到第一个remote list 中的第一个位置

```
CMakeList的一些处理
# 加上 keep_path conan 生产的cmake 默认是会set(CMAKE_SKIP_RPATH 1) 这样设置的
# 所以 默认的target link 的就是一个name 默认会从系统的/usr/local/lib、/lib, /usr/lib 下面查找
# 加上keep_rpath的话，会增加相应的path， 
# 此处rpath 和executable_path 其实是一样的了
# otool -l ./bin/md5 查看具体路径
# /Users/GavinCao/.conan/data/sqlite3/3.38.1/_/_/package/8ac1c185f15fbd5988e2e83eca9e5a743b194ab6/lib/xxx.dylib
# 不然的话就是/usr/local/lib/xxx.dylib
# 但是此处缺点是 这个bin 给别人 用不了，每个机器上的link dependecy 不同， 正常来说够了
# 在conanprofile 中增加了import 把动态库 都拷贝到bin 下面， 指定使用install_name 完美的
# https://github.com/conan-io/conan/issues/1238
# CMAKE_MACOSX_RPATH = ON (to prepend @rpath to the install name)

todo link relative dependency
```