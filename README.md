# Windows Systems
Prerequisites
Either install one of the open source SDKs (MinGW or Cygwin), which come with a modified GCC plus the required development headers. Or install Microsoft's Visual Studio (MSVC).

Building with MSVC
Open a "Visual Studio Command Prompt" (x86, x64 or ARM64), cd to the directory with the source code and run these commands:

```
cd src
msvcbuild
```
Check the msvcbuild.bat file for more options. Then follow the installation instructions below.

For an x64 to ARM64 cross-build run this first: vcvarsall.bat x64_arm64