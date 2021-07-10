# C++工程：一文看懂如何使用 C++ 开发 Android、iOS 项目



### 为什么使用C++
C/C++是相对底层的语言，相比OC、Swift、Kotlin、Java等都要难，但是C/C++是Android和iOS都支持的语言，我们使用C++主要有一下几种原因：

- 跨平台，一套代码多端使用；
- 安全性，Java是极其容易被反编译的语言，如果把核心的代码改成C++可以有效提高安全性，但是在iOS意义就不大了；
- 高性能，在多数的场景下这个优势并不明确，只有在一些特定的场景下才能发挥他的价值，比如音频、视频；
- 调用C++库API，有部分的库只提供了C++版本，如果需要访问那么就要使用C++实现。

### 项目基本要求

- 一个工程实现Android和iOS工程师一起编码；
- 可以添加依赖第三方C++库；
- 可以脱离手机实现代码调试；
- 可以使用手机实现代码调试；



### 项目设计

设计思想参考了 Flutter Plugin 和 [protobuf](https://github.com/protocolbuffers/protobuf)  的工程结构，基于CMake 和 CocoaPods 实现，为大家提供一种多平台协同开发的思路，本篇文章不会把全部的代码贴出来，只会列出设计思想和关键的代码，详细代码请查看 [源码](https://github.com/taoweiji/cpp-android-ios-example)。

#### 目录结构

```
├── CMakeLists.txt
├── android
│   ├── build.gradle
│   └── src
│       └── main
│           ├── AndroidManifest.xml
│           ├── java/com/cross/Cross.java
│           └── cpp
│               ├── include
│               ├── cross.cpp
│               └── CMakeLists.txt
├── cross.podspec
├── ios
│   └── Classes
│       ├── Cross.h
│       └── Cross.mm
├── src
│   └── url_signature
│       ├── include/url_signature.h
│       ├── url_signature.cpp
│       └── CMakeLists.txt
├── third_party
│   ├── cxxurl
│   │   ├── include
│   │   ├── src
│   │   └── CMakeLists.txt
│   └── hash
│       ├── include
│       ├── src
│       └── CMakeLists.txt
├── test
│   ├── gtest
│   │   ├── include
│   │   ├── src
│   │   └── CMakeLists.txt
│   ├── main.cpp
│   └── CMakeLists.txt
├── example 
│   ├── android #省略
│   └── ios #省略
├── build.gradle
├── gradle.properties
├── settings.gradle
```

上面的目录结构主要分为：

- Android代码（android）：虽然C++是通用的语言，但是也有部分代码并不通用，这里主要是编写和NDK特定有关的代码，比如log，除了C++代码也会在这里编写JNI接口代码，提供给Java调用；
- iOS代码（ios）：和上面同理，也是编写和iOS有特定关联的代码，虽然.m改成.mm就可以调用C++代码，但是为了避免C++代码混入主项目，这里也要编写接口层代码，通过接口调用；
- iOS库配置文件（cross.podspec）：这个文件放到/ios目录才是比较合理，由于podspec不支持指定上一级的源文件，所以只能放到根目录；
- 核心C++（src）：这里是包含了我们编写的C++代码，这里也可以把不同功能的代码分为多个项目，实现代码隔离；
- 测试代码（test）：这里主要是包含了我们日常开发调试编写的测试代码，也可以包含单元测试代码；
- 第三方库（third_party）：这里是放第三方库，每一个库都有独立的文件夹和CMakeLists.txt，管理自身的头文件和代码；
- 示例（example/android、example/ios）
- Gradle脚本文件：build.gradle/gradle.properties/settings.gradle



#### C++库设计

无论是第三方库还是我们编写的代码，都使用同一的目录结构，都是一个库，这里以 jsoncpp 为例，每一个库都包含了CMakeLists.txt、include、src三部分，CMakeLists.txt是库定义，include是需要暴露的头文件，src是放实现源码。

```
├── CMakeLists.txt
├── include
│   └── json
│       ├── reader.h
│       ├── value.h
│       └── writer.h
└── src
    ├── json_reader.cpp
    ├── json_value.cpp
    └── json_writer.cpp
```

> 在这个项目当中，如果是第三方库，我会把实现代码放到src文件夹，如果是我们自己写的代码，我会把实现代码放到和CMakeLists.txt同一级别的目录。

CMakeLists.txt 的作用主要是暴露当前库的头文件，定义需要参与编译的源码文件。

```
# 设置cmake版本要求
cmake_minimum_required(VERSION 3.10.2)
# 定义库的名字
project(jsoncpp)
# 定义需要参与编译的源文件
add_library(${PROJECT_NAME} src/json_reader.cpp src/json_value.cpp src/json_writer.cpp)
# 定义需要暴露的头文件
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)
```

有了这个C++库的定义，接下来我们看看根目录的 CMakeLists.txt

##### CMakeLists.txt（根目录）

根目录的 CMakeLists.txt 是用来关联各个子项目，需要注意是，如果关联进来那么编译成Android的aar文件的都会把代码包含进来，所以我们要根据不同的场景编写脚本，比如在Android环境下需要包含android的C++代码，不要包含测试代码。

```
cmake_minimum_required(VERSION 3.10.2)
project(cpp-android-ios-example)
set(CMAKE_CXX_STANDARD 17)
add_subdirectory(third_party/hash)
add_subdirectory(third_party/cxxurl)
add_subdirectory(src/url_signature)
if (ANDROID)
    add_subdirectory(android/src/main/cpp)
else ()
    add_subdirectory(test/gtest)
    add_subdirectory(test)
endif ()
```

> 重点：android/build.gradle定义了 CMakeLists.txt 的路径，而这个路径必须指向根目录的 CMakeLists.txt。
>
> ```groovy
> externalNativeBuild {
>      cmake {
>          path "../CMakeLists.txt" // 这里需要指向项目根目录的 CMakeLists.txt
>          version "3.10.2"
>    }
> }
> ```

##### 库依赖

通过上面的方式把各个子项目关联起来后，那么我们就可以非常简单在一个子项目中引用另外一个子项目，这里以 src/url_signature/CMakeLists.txt  为例，我们需要在 url_signature 子项目添加 cxxurl 和 hash 的依赖。

```
cmake_minimum_required(VERSION 3.10.2)
set(CMAKE_CXX_STANDARD 14)
project(url_signature)
add_library(${PROJECT_NAME} url_signature.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME} cxxurl hash)
```

#### Android

以下是android的目录结构，这部分的代码主要是实现Java和C++的转换。

```
├── build.gradle
├── gradle.properties
├── settings.gradle
└── android
    ├── build.gradle
    └── src/main
        ├── AndroidManifest.xml
        ├── cpp
        │   ├── CMakeLists.txt
        │   └── native-lib.cpp
        └── java/com/cross/Cross.java
```
从上面的目录可以看到，项目的根目录有 build.gradle、gradle.properties和settings.gradle，之所以放在根目录是


##### android/build.gradle

```groovy
apply plugin: 'com.android.library'
android {
    compileSdkVersion 30
    buildToolsVersion "30.0.2"
    defaultConfig {
        minSdkVersion 16
        targetSdkVersion 30
        testInstrumentationRunner "androidx.test.runner.AndroidJUnitRunner"
        consumerProguardFiles "consumer-rules.pro"
        externalNativeBuild {
            cmake {
                cppFlags ""
            }
        }
    }
    buildTypes {
        release {
            minifyEnabled false
            proguardFiles getDefaultProguardFile('proguard-android-optimize.txt'), 'proguard-rules.pro'
        }
    }
    externalNativeBuild {
        cmake {
            // 这里需要指向项目根目录的 CMakeLists.txt 文件
            path "../CMakeLists.txt"
            version "3.10.2"
        }
    }
}
dependencies {
}
```
##### android/src/main/cpp/CMakeLists.txt

```
cmake_minimum_required(VERSION 3.10.2)
project("cross")
include_directories(export_include)
add_library(${PROJECT_NAME} SHARED cross.cpp)
find_library(log-lib log)
target_link_libraries(${PROJECT_NAME} ${log-lib} url_signature)
```

##### cross.cpp

```c++
#include <jni.h>
#include <string>
#include "url_signature.h"

extern "C"
JNIEXPORT jstring JNICALL
Java_com_cross_Cross_signatureUrl(JNIEnv *env, jclass clazz, jstring j_url) {
    const char *url = env->GetStringUTFChars(j_url, JNI_FALSE);
    auto result = env->NewStringUTF(SignatureUrl(url).c_str());
    env->ReleaseStringUTFChars(j_url, url);
    return result;
}
```

##### Cross.java

```java
package com.cross;
public class Cross {
    static {
        System.loadLibrary("cross");
    }
    public static native String signatureUrl(String url);
}
```



#### iOS

由于 podspec 无法指定父级的文件，如果放在ios目录下，那么就无法关联src和third_party的源文件，所以就把 cross.podspec 放到工程的根目录。Cross 类主要就是负责对接OC和C++，作为统一的接口类。

```
├── cross.podspec
├── ios
│   └── Classes
│       ├── Cross.h
│       └── Cross.mm
```

##### cross.podspec

```powershell
Pod::Spec.new do |s|
  s.name             = 'cross'
  s.version          = '0.0.1'
  s.summary          = 'cross library'
  s.description      = 'Cross library'
  s.homepage         = 'http://example.com'
  s.license          = { :file => '../LICENSE' }
  s.author           = { 'Your Company' => 'email@example.com' }
  s.source           = { :path => '.' }
  # 设置源文件，切记不要把测试代码包含进来
  s.source_files = 'ios/Classes/**/*','third_party/**/*.{cc,cpp,h}','src/**/*.{cc,cpp,h}'
  # 暴露头文件，否则引用该spec的项目无法找到头文件
  s.public_header_files = 'ios/Classes/**/*.h','src/url_signature/include/*.h'
  s.platform = :ios, '8.0'
  # 必须配置HEADER_SEARCH_PATHS属性，是否会导致项目中C++找不到头文件
  s.xcconfig = {
        'HEADER_SEARCH_PATHS' => '"${PODS_TARGET_SRCROOT}/third_party/cxxurl/include/" "${PODS_TARGET_SRCROOT}/third_party/hash/include/" "${PODS_TARGET_SRCROOT}/src/url_signature/include/"'
  }
end
```

##### Cross.h

```objective-c
@interface Cross : NSObject
- (NSString*)signatureUrl:(NSString *)url;
@end
```

##### Cross.mm

```objective-c
#import "Cross.h"
#include <string>
#include <url_signature.h>

@implementation Cross
- (NSString*)signatureUrl:(NSString *)url{
    std::string str = [url UTF8String];
    std::string result = SignatureUrl(str);
    NSString *newUrl = [NSString stringWithUTF8String:result.c_str()];
    return newUrl;
}
@end
```

### 示例设计

##### Android

```
├── build.gradle
├── settings.gradle
└── src
    └── main
        ├── AndroidManifest.xml
        ├── java/com/cross/example/MainActivity.java
        └── res
```

示例就是一个普通的工程，唯一需要注意的是 settings.gradle

```groovy
rootProject.name = 'example'
include ":cross"
project(":cross").projectDir = new File("../../android")
```

build.gradle

```groovy
buildscript {
    repositories {
        google()
        jcenter()
    }
    dependencies {
        classpath "com.android.tools.build:gradle:4.1.2"
    }
}
apply plugin: 'com.android.application'
android {
	...	
}
dependencies {
    implementation project(path: ':cross')
}
```

##### iOS

```
├── Podfile
├── example
│   ├── AppDelegate.h
│   ├── AppDelegate.m
│   ├── ViewController.h
│   ├── ViewController.m
│   └── main.m
├── example.xcodeproj
```

Podfile

```
target 'example' do
  use_frameworks!
    pod 'cross', :path => '../../'
end
```

##### 如何编码？

- 如果是Android开发者，建议使用 Android Studio 打开 example/android，文件目录选择 Android 风格的，就可以在一个环境下同时编写 C++、Java、还有example的代码。
- 如果是iOS也是同样打开example/ios项目，记得要先执行 pod install 哦。
- 但多数情况下还是建议使用 vscode 或者 clion 打开 工程的根目录，在 test 目录下编写测试代码，脱离与平台关联进行开发调试，这样的效率更高。

### 总结

通常C++部分的代码不会和APP主工程的代码放到同一个仓库，而是独立开发，比如Android会打包成aar发布到maven仓库中，而iOS就会发布到内部的CocoaPods仓库，通过外部库的引入到主项目当中。

源码：https://github.com/taoweiji/cpp-android-ios-example



### 附加资料

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
- 网络：[Boost.Asio](http://think-async.com/)：用于网络和底层I/O编程的跨平台的C++库。
- MD5/SHA1：[hash-library](https://github.com/stbrumme/hash-library)
- 调试、单元测试：CMake自带的 [CTest](https://cmake.org/cmake/help/latest/command/add_test.html)、[googletest](https://github.com/google/googletest)；
- 脚本、虚拟机：
  - [V8](http://code.google.com/p/v8/)：Google开发并维护的高性能 JavaScript 引擎；
  - [J2V8](https://github.com/eclipsesource/J2V8)：针对 V8 的 Java 绑定的JSI，可以在Android上使用；
  - JavaScriptCore：在 WebKit 中提供 JavaScript 引擎的开源框架，iOS7 后集成到了 iPhone 平台；
  - [quickjs](https://github.com/horhof/quickjs)：支持多平台的小型JavaScript引擎，只有210KB大小；
  - [Lua](http://www.lua.org/)：一个小型的lua脚本引擎，可以用于做简单的逻辑运行和控制；
- 序列化：[protobuf](https://github.com/protocolbuffers/protobuf) 可以代替json/xml在不同的语言/设备之间传递对象序列化数据；
- 音频视频：[FFmpeg](https://www.ffmpeg.org/) 用于音视频的处理；

##### 构建系统

- cmake：是目前主流的构建系统，简单易用，也适合构建大型项目，常用的第三方库基本都支持cmake，可以非常简单添加第三方依赖，强烈推荐；
- makefile：是最基本的构建系统
- CocoaPods：是用于开发OC和Swift项目的构建系统，同样也支持C++，通常用于iOS应用开发；
- ndk-build：Android 上一代的构建方式，配置文件为Android.mk，目前Android开发默认的构建方式已经变成了cmake；
- bazel：Google开源的构建系统，TensorFlow和Flutter都是基于bazel构建，使用复杂，适合大型的项目；

