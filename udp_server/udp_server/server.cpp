
#include"stdio.h"
#include"conio.h"
#include"ws2tcpip.h"
#include"winsock2.h"
#define BUFF_SIZE 100
int check(char* buff) {
	return 0;
}

int main()
{
	WSADATA wsaData;
	WORD version = MAKEWORD(2, 2);
	if (WSAStartup(version, &wsaData)) {
		printf("version is not supported! \n");
		getch();
		return 0;
	}
	SOCKET server = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(99);
	serverAddr.sin_addr.s_addr = inet_addr("192.168.1.21");
	if (bind(server, (sockaddr*)&serverAddr, sizeof(serverAddr))) {
		printf("cannot bind server  \n");
	}
	printf("server Started! \n");
	sockaddr_in clientAddr;
	char buff[BUFF_SIZE];
	int ret, clientAddrLen = sizeof(clientAddr);
	while (1) {

		ret = recvfrom(server, buff, BUFF_SIZE, 0, (sockaddr*)&clientAddr, &clientAddrLen);
		if (ret == SOCKET_ERROR) {
			printf(" cannot receive message!\n");
			getch();
			return 0;
		}
		
		printf("reveive from %s : %d : %s  ", inet_ntoa(clientAddr.sin_addr),ntohs(clientAddr.sin_port) ,buff);
		printf("send to sever: ");
		gets_s(buff, BUFF_SIZE);
		ret = sendto(server, buff, ret, 0, (sockaddr*)&clientAddr, clientAddrLen);
		if (ret == SOCKET_ERROR) {
			printf(" cannot send  message!\n");
			getch();
			return 0;
		}
		
	}
	closesocket(server);
	WSACleanup();
	return 0;
}

