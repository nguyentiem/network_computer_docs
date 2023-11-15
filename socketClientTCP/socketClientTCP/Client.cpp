//#include <winsock2.h>
//#include <stdio.h>
//#include <conio.h>
//
//#pragma comment (lib,"ws2_32.lib")
//void Send(SOCKET client, char* filepath, char* url)
//{
//	char temp[1024];
//	int len = strlen(url);
//	WIN32_FIND_DATAA data;
//	HANDLE h = FindFirstFileA(filepath, &data); // liet ke thu muc o == system("dir url");
//	if (h != INVALID_HANDLE_VALUE) {
//		printf("Send directory: %s\n", filepath); // gui ve danh muc :
//
//		char msg[] = "HTTP/1.1 200 OK\nContent-Type: text/html\n\n<html><body><form method = \"post\" action = \"/go\"><br>POST: C: <input type = \"text\" name = \"post\" size = \"150\"/><br><br><input type = \"submit\" value = \"SEND\"/></form><br></body></html>";
//		// gui ve cho client
//		send(client, msg, strlen(msg), 0);
//
//		char  html[] = "<html>";
//		send(client, html, strlen(html), 0);
//
//		do {
//			// gui link duong dan
//			if (data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
//				sprintf(temp, "<b><a href=\"%s%s\">%s</a></b><br>", url, data.cFileName, data.cFileName);
//				send(client, temp, strlen(temp), 0);
//			}
//			else {
//				sprintf(temp, "<i><a href=\"%s%s\">%s</a></i><br>", url, data.cFileName, data.cFileName);
//				send(client, temp, strlen(temp), 0);
//			}
//		} while (FindNextFileA(h, &data));
//
//		sprintf(temp, "</body></html>");
//		send(client, temp, strlen(temp), 0);
//	}
//	else {
//		filepath[strlen(filepath) - 4] = 0;
//		FILE* f = fopen(filepath, "rb");
//		if (f == NULL) {
//			char msg[] = "File not found!";
//			send(client, msg, strlen(msg), 0);
//			return;
//		}
//		printf("Send file: %s\n", filepath);
//		if (strncmp((url + len - 4), "mp3", 3) == 0) {
//			char msg[] = "HTTP/1.1 200 OK\nContent-Type: audio/mpeg\n\n";
//			send(client, msg, strlen(msg), 0);
//		}
//		else if (strncmp((url + len - 4), "txt", 3) == 0) {
//			char msg[] = "HTTP/1.1 200 OK\nContent-Type: text/html\n\n";
//			send(client, msg, strlen(msg), 0);
//		}
//		else if (strncmp((url + len - 4), "jpg", 3) == 0) {
//			char msg[] = "HTTP/1.1 200 OK\nContent-Type: image/jpeg\n\n";
//			send(client, msg, strlen(msg), 0);
//		}
//
//		char filebuf[1024];
//		while (true) {
//			int res = fread(filebuf, 1, sizeof(filebuf), f);
//			if (res > 0) {
//				send(client, filebuf, res, 0);
//			}
//			else {
//				break;
//			}
//		}
//		fclose(f);
//	}
//}
//
//void ReplaceSpace2(char*);
//
//void Post(SOCKET client, char* buf) {
//
//	int res = 0;
//	char* path;
//	char* filepath = (char*)calloc(1024, 1);
//	char* url = (char*)calloc(1024, 1);
//
//	path = (char*)strstr(buf, "post");
//	ReplaceSpace2(path);
//
//	int len = strlen(path);
//	if (path[len - 1] != '/') {
//		path[len] = '/';
//		path[len + 1] = 0;
//	}
//
//	strcpy(url, &path[5]);
//
//	sprintf(filepath, "C:%s*.*", url);
//
//	Send(client, filepath, url);
//
//}
//void ReplaceSpace2(char* filepath) {
//	int len = strlen(filepath);
//	if (len < 2) {
//		return;
//	}
//	for (int i = 0; i < len - 2; i++) {
//		if (strncmp(filepath + i, "+", 1) == 0) {
//			len = strlen(filepath);
//			filepath[i] = ' ';
//			memcpy(filepath + i + 1, filepath + i + 1, len - i - 1);
//			filepath[len] = 0;
//		}
//
//		if (strncmp(filepath + i, "%3A", 3) == 0) {
//			len = strlen(filepath);
//			filepath[i] = ':';
//			memcpy(filepath + i + 1, filepath + i + 3, len - i - 3);
//			filepath[len - 2] = 0;
//		}
//
//		if (strncmp(filepath + i, "%2F", 3) == 0) {
//			len = strlen(filepath);
//			filepath[i] = '/';
//			memcpy(filepath + i + 1, filepath + i + 3, len - i - 3);
//			filepath[len - 2] = 0;
//		}
//	}
//}
//
//void ReplaceSpace(char*);
//void Get(SOCKET client, char* url) {
//	char filepath[2048];
//	int res = 0;
//
//	ReplaceSpace(url); //Replace %20 to space
//	int len = strlen(url);
//	if (url[len - 1] != '/') {
//		url[len] = '/';
//		url[len + 1] = 0;
//	}
//	if (strcmp(url, "/") == 0) {
//		strcpy(filepath, "C:/*.*");
//	}
//	else {
//		sprintf(filepath, "C:%s*.*", url);
//	}
//
//	Send(client, filepath, url);
//}
//
//void ReplaceSpace(char* filepath) {
//	int len = strlen(filepath);
//	if (len < 2) {
//		return;
//	}
//	for (int i = 0; i < len - 2; i++) {
//		if (strncmp(filepath + i, "%20", 3) == 0) {
//			len = strlen(filepath);
//			filepath[i] = ' ';
//			memcpy(filepath + i + 1, filepath + i + 3, len - i - 3);
//			filepath[len - 2] = 0;
//		}
//	}
//}
//
//
//int main(int argc, char** argv) {
//	//CreateLogger();
//	WSADATA wsa;
//	WSAStartup(MAKEWORD(2, 2), &wsa);
//	SOCKET server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
//	SOCKADDR_IN addr;
//	addr.sin_family = AF_INET;
//	addr.sin_addr.s_addr = inet_addr("192.168.1.21");
//	addr.sin_port = htons(9000);
//
//	bind(server, (SOCKADDR*)&addr, sizeof(addr));
//	listen(server, 5);
//
//	fd_set fdread;
//	int res;
//	SOCKET clients[64];
//	int numClients = 0;
//	char buf[1024];
//	char cmd[16], path[64];
//
//	while (true) {
//		FD_ZERO(&fdread);
//		FD_SET(server, &fdread);
//		for (int i = 0; i < numClients; i++)
//			FD_SET(clients[i], &fdread);
//
//		res = select(0, &fdread, NULL, NULL, NULL);
//		if (res == SOCKET_ERROR)
//			break;
//		if (res > 0) {
//			if (FD_ISSET(server, &fdread)) {
//				SOCKADDR_IN addr2;
//				int len = sizeof(addr2);
//				SOCKET client = accept(server, (SOCKADDR*)&addr2, &len);
//				char log[64];
//				sprintf(log, "%s connected", inet_ntoa(addr2.sin_addr));
//				//ExecuteLog("New Connect", log);
//				clients[numClients] = client;
//				numClients++;
//			}
//			for (int i = 0; i < numClients; i++) {
//				if (FD_ISSET(clients[i], &fdread)) {
//					// Xu ly du lieu nhan duoc tu client
//					res = recv(clients[i], buf, sizeof(buf), 0);
//					if (res == SOCKET_ERROR || res == 0) {
//						continue;
//					}
//
//					buf[res] = 0;
//					printf("%s", buf);
//
//					res = sscanf(buf, "%s %s", cmd, path);
//					if (res == 2) {
//						if (strcmp(cmd, "GET") == 0) {
//							Get(clients[i], path);
//							break;
//						}
//						if (strcmp(cmd, "POST") == 0) {
//							Post(clients[i], buf);
//							break;
//						}
//
//					}
//				}
//			}
//		}
//	}
//
//	closesocket(server);
//	WSACleanup();
//	return 0;
//}
//
//
//
//
////
////
////
////
////#define SERVER_ADDR "192.168.1.2"
////#define PORT 80
////#define BUFF_SIZE 100
////#define BUFF1_SIZE 100
////int main(int argc, char* argv[])
////{
////	//Step 1: Initiate WinSock
////	WSADATA wsaData;
////	WORD wVersion = MAKEWORD(2, 2);
////	if (WSAStartup(wVersion, &wsaData))
////		printf("Version is not supported\n");
////
////	SOCKET Client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
////	sockaddr_in serverAddr;
////	serverAddr.sin_family = AF_INET;
////	serverAddr.sin_port = htons(80);
////	serverAddr.sin_addr.s_addr = inet_addr(SERVER_ADDR);
////	if (connect(Client, (sockaddr*)&serverAddr, sizeof(serverAddr))) {
////		printf("cannot connect server!\n");
////		getch();
////		return 0;
////	}
////	printf("server connected! \n");
////	char buff[BUFF_SIZE];
////	char buff1[BUFF1_SIZE];
////	int ret;
////	do {
////		
////		memset(buff, 0, BUFF_SIZE);
////		memset(buff1, 0, BUFF_SIZE);
////		scanf("%s", buff);
////		ret = send(Client,buff,100,0);
////		if (ret == 0) {
////			printf("cannot send file! \n");
////			getch();
////			break;
////		}
////	
////		
////	} while (1);
////	closesocket(Client);
////	WSACleanup();
////	return 0;
////}
