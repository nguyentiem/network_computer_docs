//
//#include"stdio.h"
//#include"ws2tcpip.h"
//#include"winsock2.h"
//#include"conio.h"
//#define BUFF_SIZE 100
//
//int main(int argc, char* argv[])
//{
//
//	WSAData data;
//	WORD version = MAKEWORD(2, 2);
//	if (WSAStartup(version, &data)) {
//		printf("version is not supported !\n");
//
//	}
//	SOCKET server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
//	sockaddr_in serverAddr;
//	serverAddr.sin_family = AF_INET;
//	serverAddr.sin_port = htons(88);
//	serverAddr.sin_addr.s_addr = inet_addr("192.168.1.21");
//	if (bind(server, (sockaddr*)&serverAddr, sizeof(serverAddr))) {
//		printf("cannot bind server!\n");
//		getch();
//		return 0;
//	}
//
//	if (listen(server, 10)) {
//		printf("cannot listen !\n");
//		getch();
//		return 0;
//	}
//	printf("server Started\n");
//	sockaddr_in clientAddr;
//	char buffRe[BUFF_SIZE];
//
//
//	int ret, clientAddrLen = sizeof(clientAddr);
//
//	SOCKET con;
//	while (1) {
//		con = accept(server, (sockaddr*)&clientAddr, &clientAddrLen);
//		printf("connected \n");
//		while (1) {
//			memset(buffRe, 0, BUFF_SIZE);
//			ret = recv(con, buffRe, BUFF_SIZE, 0);
//			printf("receive from %s: %d \n", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));
//			printf("buff: %s \n", buffRe);
//			if (ret == SOCKET_ERROR) {
//				printf("cannot receive !\n");
//				getch();
//
//			}
//
//
//
//			ret = send(con, buffRe, BUFF_SIZE, 0);
//			if (ret == SOCKET_ERROR) {
//				printf("cannot send !\n");
//				getch();
//				break;
//
//			}
//			printf("send : %s", buffRe);
//
//		}
//		printf("server cancell \n");
//		shutdown(con, SD_BOTH);
//		closesocket(con);
//
//	}
//	closesocket(server);
//	WSACleanup();
//	return 0;
//}
