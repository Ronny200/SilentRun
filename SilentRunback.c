#include <windows.h>
#include <stdio.h>
#include <string.h>

// ִ��ָ��·���ĳ���
void executeProgram(const char* programPath, BOOL hideWindow) {
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	
	// ��ʼ���ṹ��
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));
	
	// ���� hideWindow ���������Ƿ����ش���
	si.dwFlags = STARTF_USESHOWWINDOW;
	si.wShowWindow = hideWindow ? SW_HIDE : SW_SHOW;
	
	// �����½���
	if (!CreateProcess(NULL,   // û������Ӧ�ó����·����ʹ��������
		(char*)programPath, // Ҫ������Ӧ�ó�����
		NULL,           // ���̵İ�ȫ����
		NULL,           // �̵߳İ�ȫ����
		FALSE,          // ���̳о��
		CREATE_NO_WINDOW,  // ������־
		NULL,           // ʹ�ø����̵Ļ�����
		NULL,           // ʹ�ø����̵ĵ�ǰĿ¼
		&si,            // STARTUPINFO�ṹ
		&pi)) {         // PROCESS_INFORMATION�ṹ
		printf("Failed to create process: %s\n", programPath);
		return;
	}
	
	// �رս��̺��߳̾��
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
}

// ���������в�����ִ����Ӧ�ĳ���
void handleArgs(int argc, char* argv[]) {
	for (int i = 1; i < argc; ++i) {
		if (strcmp(argv[i], "-r") == 0) {
			// �ҵ� -r ������ִ������ÿ������·��
			for (int j = i + 1; j < argc; ++j) {
				executeProgram(argv[j], FALSE);
			}
			return; // ����·����ִ�У�����
		} else if (strcmp(argv[i], "-rh") == 0) {
			for (int j = i + 1; j < argc; ++j) {
				executeProgram(argv[j], TRUE);
			}
			return;
		}
	}
	
	//���û�� -r �� -rh ������ִ��Ĭ����������
	const char* defaultPrograms[] = {
		"RunAny\\RunAny.exe",
		"Run.exe"
	};
	
	for (int i = 0; i < 2; ++i) {
		executeProgram(defaultPrograms[i], FALSE);
	}
	//��Ĭ����Ĭ��������
	const char* defaultBat[] = {
		"SilentRun.bat",
		"Run.bat"
	};
	
	for (int i = 0; i < 2; ++i) {
		executeProgram(defaultBat[i], TRUE);
	}	
}

int main(int argc, char* argv[]) {
	// ���������в���
	handleArgs(argc, argv);
	return 0;
}
