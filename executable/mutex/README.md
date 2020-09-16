## mutex

一个验证生产者与消费者问题中的互斥量的程序。



## 使用

> Windows 自行编译运行。Linux、MacOS 的二进制文件可在 [releases](https://github.com/AimTao/tool-by-cpp/releases/tag/v4.0.0) 中下载。

`./mutex` 执行程序后，会弹出一下提示：

```
================= option =================
Add mutex, please input 1
Don't add mutex, please input 0
==========================================
```

+ 想验证 *生产者消费者问题* 请输入 0。
+ 想验证 *加入互斥量后的生产者消费者问题* 请输入 1。



## 验证结果

+ 未加入互斥量时，nums 不为 0；

+ 加入互斥量时，nums 为 0。