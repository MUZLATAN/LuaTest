# Windows 系统环境准备
安装 Microsoft's Visual Studio (MSVC).

Building with MSVC
打开 "Visual Studio Command Prompt" (x86, x64 or ARM64),切到3rd_parties下面，并运行下面命令

```
cd src
msvcbuild
```
即可得到luajit 的库dll，以及头文件
或者检车msvcbuild.bat 文件查看更多选项.

`For an x64 to ARM64 cross-build run this first: vcvarsall.bat x64_arm64`
# 运行
双击build.bat 即可生成vs工程文件

# 进入build 
打开.sln文件即可