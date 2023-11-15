
#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include <winsock2.h>
#include <string.h>
#include <ctime>
#pragma comment(lib, "Ws2_32.lib")
//typedef struct LogInfomation {
//	char* name;
//	char* info;
//	struct LogInfomation* Next;
//} LogInfo;
//
//DWORD WINAPI LoggerThread(LPVOID);
//
//LogInfo* CreateLog() {
//	LogInfo* log = (LogInfo*)malloc(sizeof(struct LogInfomation));
//	log->Next = NULL;
//	return log;
//}
//
//LogInfo* headLogs = NULL;
//LogInfo* tailLogs = NULL;
//HANDLE handleLogger = NULL;
////them luong
//void CreateLogger() {
//	if (handleLogger == NULL) {
//		headLogs = CreateLog();
//		tailLogs = headLogs;
//		handleLogger = CreateThread(0, 0, LoggerThread, 0, 0, 0);
//		printf("Logger created!\n");
//	}
//	else {
//		printf("Logger Created! Do not create again!\n");
//	}
//}
//// huy luong
//void TerminateLogger() {
//	if (handleLogger != NULL) {
//		TerminateThread(handleLogger, 0);  // huy luong trong windown
//		handleLogger = NULL;
//		free(headLogs);   // xoa bo nho 
//		printf("Logger Terminated!\n");
//	}
//	else {
//		printf("Logger Terminated! Do not terminate again!\n");
//	}
//}
// ghi lich su 
//DWORD WINAPI LoggerThread(LPVOID lpParam) {
//	LogInfo* log = headLogs;
//	char* info;
//	char* filename = "log.txt";
//	while (true) {
//		if (log->Next != NULL) {
//			log = log->Next;
//			time_t timenow = time(0);
//			tm* today = localtime(&timenow);
//			info = (char*)malloc(18 + strlen(log->name) + 2 + strlen(log->info) + 2);
//			sprintf(info, "%d:%d:%d %d/%d/%d %s: %s\n", today->tm_hour, today->tm_min, today->tm_sec, today->tm_mday, today->tm_mon + 1, today->tm_year + 1900, log->name, log->info, filename);
//			FILE* f = fopen(filename, "a+");
//			fprintf(f, "%s", info);
//			fclose(f);
//		}
//	}
//}
//// khoi tao luong 
//void ExecuteLog(char* name, char* info) {
//	LogInfo* log = CreateLog();
//	log->name = (char*)malloc(strlen(name) + 1);
//	log->info = (char*)malloc(strlen(info) + 1);
//	strcpy(log->name, name);
//	strcpy(log->info, info);
//	tailLogs->Next = log;
//	tailLogs = log;
//}
//
//void PrintLog() {
//
//}
void ReplaceSpace2(char*);

void Post(SOCKET client, char* buf) {

	int res = 0;
	char* path;
	char* filepath = (char*)calloc(1024, 1);
	char* url = (char*)calloc(1024, 1);

	path = (char*)strstr(buf, "post");
	ReplaceSpace2(path);

	int len = strlen(path);
	if (path[len - 1] != '/') {
		path[len] = '/';
		path[len + 1] = 0;
	}

	strcpy(url, &path[5]);

	sprintf(filepath, "C:%s*.*", url);

	Send(client, filepath, url);

}
void ReplaceSpace2(char* filepath) {
	int len = strlen(filepath);
	if (len < 2) {
		return;
	}
	for (int i = 0; i < len - 2; i++) {
		if (strncmp(filepath + i, "+", 1) == 0) {
			len = strlen(filepath);
			filepath[i] = ' ';
			memcpy(filepath + i + 1, filepath + i + 1, len - i - 1);
			filepath[len] = 0;
		}

		if (strncmp(filepath + i, "%3A", 3) == 0) {
			len = strlen(filepath);
			filepath[i] = ':';
			memcpy(filepath + i + 1, filepath + i + 3, len - i - 3);
			filepath[len - 2] = 0;
		}

		if (strncmp(filepath + i, "%2F", 3) == 0) {
			len = strlen(filepath);
			filepath[i] = '/';
			memcpy(filepath + i + 1, filepath + i + 3, len - i - 3);
			filepath[len - 2] = 0;
		}
	}
}
void Send(SOCKET client, char* filepath, char* url)
{
	char temp[1024];
	int len = strlen(url);
	WIN32_FIND_DATAA data;
	HANDLE h = FindFirstFileA(filepath, &data); // liet ke thu muc o == system("dir url");
	if (h != INVALID_HANDLE_VALUE) {
		printf("Send directory: %s\n", filepath); // gui ve danh muc :

		char msg[] = "HTTP/1.1 200 OK\nContent-Type: text/html\n\n<html><body><form method = \"post\" action = \"/go\"><br>POST: C: <input type = \"text\" name = \"post\" size = \"150\"/><br><br><input type = \"submit\" value = \"SEND\"/></form><br></body></html>";
		// gui ve cho client
		send(client, msg, strlen(msg), 0);

		char  html[] = "<html>";
		send(client, html, strlen(html), 0);

		do {
			// gui link duong dan
			if (data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
				sprintf(temp, "<b><a href=\"%s%s\">%s</a></b><br>", url, data.cFileName, data.cFileName);
				send(client, temp, strlen(temp), 0);
			}
			else {
				sprintf(temp, "<i><a href=\"%s%s\">%s</a></i><br>", url, data.cFileName, data.cFileName);
				send(client, temp, strlen(temp), 0);
			}
		} while (FindNextFileA(h, &data));

		sprintf(temp, "</body></html>");
		send(client, temp, strlen(temp), 0);
	}
	else {
		filepath[strlen(filepath) - 4] = 0;
		FILE* f = fopen(filepath, "rb");
		if (f == NULL) {
			char msg[] = "File not found!";
			send(client, msg, strlen(msg), 0);
			return;
		}
		printf("Send file: %s\n", filepath);
		if (strncmp((url + len - 4), "mp3", 3) == 0) {
			char msg[] = "HTTP/1.1 200 OK\nContent-Type: audio/mpeg\n\n";
			send(client, msg, strlen(msg), 0);
		}
		else if (strncmp((url + len - 4), "txt", 3) == 0) {
			char msg[] = "HTTP/1.1 200 OK\nContent-Type: text/html\n\n";
			send(client, msg, strlen(msg), 0);
		}
		else if (strncmp((url + len - 4), "jpg", 3) == 0) {
			char msg[] = "HTTP/1.1 200 OK\nContent-Type: image/jpeg\n\n";
			send(client, msg, strlen(msg), 0);
		}

		char filebuf[1024];
		while (true) {
			int res = fread(filebuf, 1, sizeof(filebuf), f);
			if (res > 0) {
				send(client, filebuf, res, 0);
			}
			else {
				break;
			}
		}
		fclose(f);
	}
}

void ReplaceSpace(char*);
void Get(SOCKET client, char* url) {
	char filepath[2048];
	int res = 0;

	ReplaceSpace(url); //Replace %20 to space
	int len = strlen(url);
	if (url[len - 1] != '/') {
		url[len] = '/';
		url[len + 1] = 0;
	}
	if (strcmp(url, "/") == 0) {
		strcpy(filepath, "C:/*.*");
	}
	else {
		sprintf(filepath, "C:%s*.*", url);
	}

	Send(client, filepath, url);
}

void ReplaceSpace(char* filepath) {
	int len = strlen(filepath);
	if (len < 2) {
		return;
	}
	for (int i = 0; i < len - 2; i++) {
		if (strncmp(filepath + i, "%20", 3) == 0) {
			len = strlen(filepath);
			filepath[i] = ' ';
			memcpy(filepath + i + 1, filepath + i + 3, len - i - 3);
			filepath[len - 2] = 0;
		}
	}
}


int main(int argc, char** argv) {
	//CreateLogger();
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);
	SOCKET server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	SOCKADDR_IN addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(80);

	bind(server, (SOCKADDR*)&addr, sizeof(addr));
	listen(server, 5);

	fd_set fdread;
	int res;
	SOCKET clients[64];
	int numClients = 0;
	char buf[1024];
	char cmd[16], path[64];

	while (true) {
		FD_ZERO(&fdread);
		FD_SET(server, &fdread);
		for (int i = 0; i < numClients; i++)
			FD_SET(clients[i], &fdread);

		res = select(0, &fdread, NULL, NULL, NULL);
		if (res == SOCKET_ERROR)
			break;
		if (res > 0) {
			if (FD_ISSET(server, &fdread)) {
				SOCKADDR_IN addr2;
				int len = sizeof(addr2);
				SOCKET client = accept(server, (SOCKADDR*)&addr2, &len);
				char log[64];
				sprintf(log, "%s connected", inet_ntoa(addr2.sin_addr));
				//ExecuteLog("New Connect", log);
				clients[numClients] = client;
				numClients++;
			}
			for (int i = 0; i < numClients; i++) {
				if (FD_ISSET(clients[i], &fdread)) {
					// Xu ly du lieu nhan duoc tu client
					res = recv(clients[i], buf, sizeof(buf), 0);
					if (res == SOCKET_ERROR || res == 0) {
						continue;
					}

					buf[res] = 0;
					printf("%s", buf);

					res = sscanf(buf, "%s %s", cmd, path);
					if (res == 2) {
						if (strcmp(cmd, "GET") == 0) {
							Get(clients[i], path);
							break;
						}
						if (strcmp(cmd, "POST") == 0) {
							Post(clients[i], buf);
							break;
						}

					}
				}
			}
		}
	}

	closesocket(server);
	WSACleanup();
	return 0;
}
