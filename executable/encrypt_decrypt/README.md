## encrypt_decrypt

可以对任何文件进行加密解密，实现对称加密，但用户无需记住任何密钥。

升级版：[双密钥二重加密](https://github.com/AimTao/tool-by-cpp/tree/master/executable/encrypt_decrypt_double)



## 随机分组加密

1. 获取系统当前时间，处理后得到随机密钥、随机分组大小。
2. 混淆系统当前时间，分块写入加密文件。
3. 利用密钥加密明文。



## 使用

程序将根据文件名，自动生成 加密后的文件名 / 解密后的文件名。例如：

1. 待加密的文件：wallpaper.png		加密后的文件：wallpaper_enc.png
2. 待解密的文件：wallpaper.png		解密后的文件：wallpaper_dec.png

### 命令行式

+ linux、mac

```sh
# 加密
./enc need_encrypt_file

#解密
./dec need_decrypt_file
```

+ Windows

```sh
# 加密
enc need_encrypt_file

#解密
dec need_decrypt_file
```

### 交互式

双击运行图标运行。



