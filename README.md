# tool-by-cpp

使用 C/C++ 写的一些小工具。

 `executable` 文件夹下，有各平台的部分可执行程序。担心有些二进制文件过大，造成 `.git` 文件过于臃肿，没有放到  `executable` 文件夹下，可以在 [releases](https://github.com/AimTao/tool-by-cpp/releases) 下载 ，或者自行 clone 源码编译。👋 

字符集使用 utf-8，运行程序如出现乱码，可自行自行 clone 源码编译。👋

随缘更新。。。



## 目录

| 工具                                                         | 下载                                                         | 描述                                                         |
| ------------------------------------------------------------ | ------------------------------------------------------------ | ------------------------------------------------------------ |
| [encrypt_decrypt](https://github.com/AimTao/tool-by-cpp/tree/master/executable/encrypt_decrypt) | [命令行式](https://github.com/AimTao/tool-by-cpp/releases/tag/v2.0.0)｜[交互式](https://github.com/AimTao/tool-by-cpp/releases/tag/v2.1.0) | 对任何文件可进行加密解密（随机分组加密）。                   |
| [encrypt_decrypt_double](https://github.com/AimTao/tool-by-cpp/tree/master/executable/encrypt_decrypt_double) | [命令行式](https://github.com/AimTao/tool-by-cpp/releases/tag/v3.0.0)｜[交互式](https://github.com/AimTao/tool-by-cpp/releases/tag/v3.1.0) | [encrypt_decrypt](https://github.com/AimTao/tool-by-cpp/tree/master/executable/encrypt_decrypt)的升级版，添加二重加密。 |
| [mutex](https://github.com/AimTao/tool-by-cpp/tree/master/executable/mutex) | [命令行式](https://github.com/AimTao/tool-by-cpp/releases/tag/v4.0.0) | 验证生产者与消费者问题中互斥锁的工具。                       |
| [spin_lock](https://github.com/AimTao/tool-by-cpp/tree/master/executable/spin_lock) | [命令行式](https://github.com/AimTao/tool-by-cpp/releases/tag/v5.0.0) | 验证生产者与消费者问题中自旋锁的工具。                       |



以下工具没必要 `release`，在 `executable` 文件夹找就可以啦。👋

| 鸡肋                                                         | 描述                      |
| ------------------------------------------------------------ | ------------------------- |
| [copy](https://github.com/AimTao/tool-by-cpp/tree/master/executable/copy) | 实现 Linux 的 `cp` 命令。 |
| [size](https://github.com/AimTao/tool-by-cpp/tree/master/executable/size) | 查看文件大小。            |
|                                                              |                           |

