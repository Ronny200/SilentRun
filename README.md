# SilentRun

想做一个程序能调用其他程序，可以批量打开程序，可以隐藏运行批处理。

虽然bat和vbs也可以，但是没有exe方便

用c吧，虽然从来没用过，但是编译出来够小够快就行，反正没几行代码

## 程序默认调用名单

设置默认打开文件，当有下面几个文件名运行程序的时候会自动开启：

1. "RunAny\\RunAny.exe"
2. "Run.exe"
3. "SilentRun.bat"
4. "Run.bat"

第一个是为了配合RunAny在u盘中的调用特地设置。

## 程序参数

正常调用-r

```c
//单独调用
SilentRun.bat -r "test.exe"
//批量调用
SilentRun.bat -r "test1.exe" "test2.exe"
```

静默调用-rh

```c
//静默调用
SilentRun.bat -rh "test.bat"
//批量静默调用
SilentRun.bat -r "test1.bat" "test2.bat"
```

目前调用外部程序有点小bug,一些exe运行会创建进程失败，摸索中……
