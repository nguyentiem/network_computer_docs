
#include"stdio.h"
#include"conio.h"
#include"ws2tcpip.h"
#include"winsock2.h"
#define BUFF_SIZE 100


int main()
{
	WSADATA wsaData;
	WORD version = MAKEWORD(2, 2);
	if (WSAStartup(version, &wsaData)) {
		printf("version is not supported! \n");
		getch();
		return 0;
	}

	SOCKET client = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	sockaddr_in clientAddr;
	clientAddr.sin_family = AF_INET;
	clientAddr.sin_port = htons(99);
	clientAddr.sin_addr.s_addr = inet_addr("192.168.1.21");
	if (bind(client, (sockaddr*)&clientAddr, sizeof(clientAddr))) {
		printf("cannot bind server  \n");
	}

	sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(55);
	serverAddr.sin_addr.s_addr = inet_addr("192.168.1.30");
	printf("server Started! \n");
	//sockaddr_in clientAddr;
	char buff[BUFF_SIZE];
	int ret, serverAddrLen = sizeof(serverAddr);
	while (1) {

		ret = recvfrom(client, buff, BUFF_SIZE, 0, (sockaddr*)&serverAddr, &serverAddrLen);
		if (ret == SOCKET_ERROR) {
			printf(" cannot receive message!\n");
			getch();
			return 0;
		}

		printf("reveive from %s :  %s ", inet_ntoa(clientAddr.sin_addr), buff);
		printf("send to sever: ");
		gets_s(buff, BUFF_SIZE);
		ret = sendto(client, buff, 100, 0, (sockaddr*)&serverAddr, serverAddrLen);
		if (ret == SOCKET_ERROR) {
			printf(" cannot send  message!\n");
			getch();
			return 0;
		}
		/*memset(buff, 0, 100);
		ret = recvfrom(client, buff, BUFF_SIZE, 0, (sockaddr*)&serverAddr, &serverAddrLen);
		if (ret == SOCKET_ERROR) {
			printf(" cannot receive message!\n");
			getch();
			return 0;
		}
		printf("reveive from %s :  %s ", inet_ntoa(serverAddr.sin_addr), buff);*/
	}
	closesocket(client);
	WSACleanup();
	return 0;
}

