## encrypt_decrypt

可以对任何文件进行加密解密，随机分组二重对称加密。

使用随机生成的两个不同的密钥，实现对称加密，但用户无需记住任何密钥。



## 随机分组二重加密

> 结合分组加密、多重加密的两者的特点。

1. 获取系统当前时间，处理后得到随机密钥、随机分组大小。
2. 混淆系统当前时间，分块写入加密文件。
3. 利用密钥加密明文得到临时密文。
4. 获取系统当前时间，处理后得到新的随机密钥、随机分组大小
5. 进行二次加密。



## 使用

程序将根据文件名，自动生成 加密后的文件名 / 解密后的文件名。例如：

1. 待加密的文件：wallpaper.png		加密后的文件：wallpaper_enc.png
2. 待解密的文件：wallpaper.png		解密后的文件：wallpaper_dec.png

如果加密文件很大，加密过程中，会看到一个临时文件 tmp_file ，程序会自动删掉。

### 命令行式

+ linux、mac

```sh
# 加密
./enc2 need_encrypt_file

#解密
./dec2 need_decrypt_file
```

+ Windows

```sh
# 加密
enc2 need_encrypt_file

#解密
dec2 need_decrypt_file
```

### 交互式

双击运行图标运行。



