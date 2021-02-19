标题：一文看懂如何使用 C++ 开发 Android、iOS 项目

一文看懂如何使用 C++ 协同开发 Android、iOS 项目

模拟一个网络请求文件下载的案例

https://github.com/protocolbuffers/protobuf

网络请求模块
文件存储模块

### 为什么使用C++
C/C++是相对底层的语言，相比OC、Swift、Kotlin、Java等都要难，但是C/C++是Android和iOS都支持的语言，我们使用C++主要有一下几种原因：

- 跨平台，一套代码多端使用；
- 安全性，Java是极其容易被反编译的语言，如果把核心的代码改成C++可以有效提高安全性；
- 高性能，在多数的场景下这个优势并不明确，只有在一些特定的场景下才能发挥他的价值，比如音频、视频；
- 调用C++库API，有部分的库只提供了C++接口，如果需要访问那么就要使用C++实现。

### 工程设计基本要求

- 一个工程实现Android和iOS工程师一起编码；
- 可以添加依赖第三方库；
- 可以脱离手机实现代码调试；
- 可以使用手机实现代码调试；
- 可以实现单元测试；


### 特点
- 在iOS上支持 CocoaPods、Android支持Gradle；



## 附加

https://www.cnblogs.com/skyus/articles/8524408.html

##### 集成开发环境（IDE）

- [CLion](https://www.jetbrains.com/clion/)：JetBrains出品，最好用的C++ IDE，对CMake支持非常友好，需要付费的，对开源社区有贡献的可以申请免费使用；
- [AppCode](http://www.jetbrains.com/objc/)：JetBrains出品，支持Objective-C, Swift, C/C++语言，也是需要付费的；
- [Visual Studio Code](https://code.visualstudio.com/?wt.mc_id=DX_841432)：微软出品，支持多种平台，可以通过插件实现C++编码，也是一个非常不错的选择；
- [Xcode](https://developer.apple.com/xcode/)：苹果公司出品，对于iOS开发者非常友好，可以搭配CocoaPods一起开发C++；
- [Visual Studio](https://visualstudio.microsoft.com/zh-hans/vs/)：微软出品，仅支持Windows，功能非常强大；
- [Android Studio](https://developer.android.com/studio)：用于Android开发的IDE，同样也可以编译C++代码，适用于Android开发者；

##### C++常用库

- 综合
  - [boost](https://github.com/boostorg) 提供了很多强大的C++库，
  - [Apache C++ Standard Library](http://stdcxx.apache.org/)：主要包含了算法和容器的
- json：[ jsoncpp](https://github.com/open-source-parsers/jsoncpp) 和 [nlohmann/json](https://github.com/nlohmann/json) 都是不错的选择。
- 压缩：libzip2
- 网络：Boost.Asio](http://think-async.com/)：用于网络和底层I/O编程的跨平台的C++库。
- MD5/SHA1：
- 日志：腾讯开发的 [xlog](https://github.com/Tencent/mars) 是一个不错的选择，缺点是不支持x86，无法在模拟器上调试
- 调试、单元测试：CMake自带的 [CTest](https://cmake.org/cmake/help/latest/command/add_test.html)、[googletest](https://github.com/google/googletest)；
- 脚本、虚拟机：
  - [V8](http://code.google.com/p/v8/)：Google开发并维护的高性能 JavaScript 引擎；
  - [J2V8](https://github.com/eclipsesource/J2V8)：针对 V8 的 Java 绑定的JSI，可以在Android上使用；
  - JavaScriptCore：在 WebKit 中提供 JavaScript 引擎的开源框架，iOS7 后集成到了 iPhone 平台；
  - [quickjs](https://github.com/horhof/quickjs)：支持多平台的小型JavaScript引擎，只有210KB大小；
  - [Lua](http://www.lua.org/)：一个小型的lua脚本引擎，可以用于做简单的逻辑运行和控制；
- 数据库：
- 序列化：[protobuf](https://github.com/protocolbuffers/protobuf) 可以代替json/xml在不同的语言/设备之间传递对象序列化数据
- 音频视频：[FFmpeg](https://www.ffmpeg.org/) 用于音视频的处理

##### 构建系统

- cmake：是目前主流的构建系统，简单易用，也适合构建大型项目，常用的第三方库基本都支持cmake，可以非常简单添加第三方依赖，强烈推荐；
- makefile：是最基本的构建系统
- CocoaPods：是用于开发OC和Swift项目的构建系统，同样也支持C++，通常用于iOS应用开发；
- Android.mk：Android 上一代的构建方式，目前Android开发默认的构建方式已经变成了cmake；
- bazel：Google开源的构建系统，TensorFlow和Flutter都是基于bazel构建，使用复杂，适合大型的项目；
- ninja：
- autotools

