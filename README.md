# MD5
### 开发环境
在Linux CentOS7下使用C++开发，以g++/VSCode/Makefile作为开发工具
### 基本功能
输入任意长度的信息，经过处理，可以得到128位的摘要，摘要具有唯一性。
### 算法模块
1.根据原始数据添加填充位，添加bit长度。
2.初始化MD buffer，并按每一个chunk数据块进行轮转操作
3.拼接MD buffer摘要，输出 32位MD5值。
### 项目测试
使用该项目加密一段信息，并获取MD5结果。之后与Linux下使用md5sum工具对相同信息的加密结果进行校验。
### GitHub链接：https://github.com/KamSss/MD5
