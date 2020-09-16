## spin_lock

一个验证生产者与消费者问题中的自旋锁的程序。



## 编译

> Windows 自行编译运行，Linux的二进制文件可在 [releases](https://github.com/AimTao/tool-by-cpp/releases/tag/v5.0.0) 中下载。

⚠️注意：

+ 由于 macOS 不支持**POSIX标准提供的编程接口**，所以不能编译和运行。

+ 由于 pthread 库不是 Linux 系统默认的库，连接时需要使用库 `libpthread.a`，所以在使用  `pthread_create` 创建线程时，在编译中要加 `-lpthread` 参数：`g++ spin_lock.cc -o spin_ -lpthread `



## 使用

`./spin_lock` 执行程序后，会弹出一下提示：

```
================= option =================
Add spin_lock, please input 1
Don't add spin_lock, please input 0
==========================================
```

+ 想验证 *生产者消费者问题* 请输入 0。
+ 想验证 *加入自旋锁后的生产者消费者问题* 请输入 1。



## 验证结果

+ 未加入自旋锁时，nums 不为 0；

+ 加入自旋锁时，nums 为 0。