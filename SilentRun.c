#include <windows.h>
#include <stdio.h>
#include <string.h>

// 执行指定路径的程序
void executeProgram(const char* programPath, BOOL hideWindow) {
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	
	// 初始化结构体
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));
	
	// 根据 hideWindow 参数决定是否隐藏窗口
	si.dwFlags = STARTF_USESHOWWINDOW;
	si.wShowWindow = hideWindow ? SW_HIDE : SW_SHOW;
	
	// 创建新进程
	if (!CreateProcess(NULL,   // 没有启动应用程序的路径，使用命令行
		(char*)programPath, // 要启动的应用程序名
		NULL,           // 进程的安全属性
		NULL,           // 线程的安全属性
		FALSE,          // 不继承句柄
		CREATE_NO_WINDOW,  // 创建标志
		NULL,           // 使用父进程的环境块
		NULL,           // 使用父进程的当前目录
		&si,            // STARTUPINFO结构
		&pi)) {         // PROCESS_INFORMATION结构
		printf("Failed to create process: %s\n", programPath);
		return;
	}
	
	// 关闭进程和线程句柄
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
}

// 处理命令行参数并执行相应的程序
void handleArgs(int argc, char* argv[]) {
	for (int i = 1; i < argc; ++i) {
		if (strcmp(argv[i], "-r") == 0) {
			// 找到 -r 参数，执行其后的每个程序路径
			for (int j = i + 1; j < argc; ++j) {
				executeProgram(argv[j], FALSE);
			}
			return; // 所有路径已执行，返回
		} else if (strcmp(argv[i], "-rh") == 0) {
			for (int j = i + 1; j < argc; ++j) {
				executeProgram(argv[j], TRUE);
			}
			return;
		}
	}
	
	//如果没有 -r 或 -rh 参数，执行默认启动程序
	const char* defaultPrograms[] = {
		"RunAny\\RunAny.exe",
		"Run.exe"
	};
	
	for (int i = 0; i < 2; ++i) {
		executeProgram(defaultPrograms[i], FALSE);
	}
	//静默启动默认批处理
	const char* defaultBat[] = {
		"SilentRun.bat",
		"Run.bat"
	};
	
	for (int i = 0; i < 2; ++i) {
		executeProgram(defaultBat[i], TRUE);
	}	
}

int main(int argc, char* argv[]) {
	// 处理命令行参数
	handleArgs(argc, argv);
	return 0;
}
