// Client.cpp : Defines the entry point for the console application.
//

#include"stdio.h"
#include"conio.h"
#include"ws2tcpip.h"
#include"winsock2.h"
#include"process.h"
#define BUFF_SIZE 2048
#define MAX_CLIENT 1024
//void menu() {
//	printf("========================================================\n");
//	printf("==================      MENU       =====================\n");
//	printf("========================================================\n");
//	printf("=====   1. USER user     : login user               ====\n");
//	printf("=====   2. PASS password : login password           ====\n");
//	printf("=====   3. LOGOUT        : logout account           ====\n");
//	printf("========================================================\n");
//	printf("========================================================\n");
//}
int main(int argc, char* argv[])
{

	WSAData data;
	WORD version = MAKEWORD(2, 2);
	if (WSAStartup(version, &data)) {
		printf("version is not supported !\n");

	}
	SOCKET Client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(88);
	serverAddr.sin_addr.s_addr = inet_addr("192.168.1.22");
	if (connect(Client, (sockaddr*)&serverAddr, sizeof(serverAddr))) {
		printf("cannot connect server!\n");
		getch();
		return 0;
	}
	printf("server connected! \n");
	char buffSend[BUFF_SIZE];
	char buffRecv[BUFF_SIZE];
	int ret;
	long total = 0;
	/*menu();*/
	do {

		memset(buffSend, 0, BUFF_SIZE);
		memset(buffRecv, 0, BUFF_SIZE);


		printf("send to sever: ");
		gets_s(buffSend, BUFF_SIZE);
		if (strcmp(buffSend, "bye") == 0)break;
		ret = send(Client, buffSend, strlen(buffSend), 0);
		if (ret == SOCKET_ERROR) {
			printf("cannot send message! \n");
			getch();
			return 0;
		}
		/*ret = recv(Client, buffRecv, BUFF_SIZE, 0);
		if (ret == SOCKET_ERROR) {
			if (WSAGetLastError() == WSAETIMEDOUT) {
				printf("time-out! \n");
			}
			else {
				printf("cannot receive message !\n");
				getch();
				return 0;
			}

		}
		printf("receive from server: %s \n", buffRecv);*/
	} while (1);
	closesocket(Client);

	WSACleanup();
	return 0;
}


