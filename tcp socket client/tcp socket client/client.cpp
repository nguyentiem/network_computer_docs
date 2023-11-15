
//#include "stdafx.h"
#include"stdio.h"

#include"ws2tcpip.h"
#include"winsock2.h"
#include <windows.h>
#include"conio.h"
#include <time.h>
#include"string.h"
#include<cstring>
#define BUFF_SIZE 100





int main()
{
	time_t rawtime;
	struct tm* timeinfo;
	char log_mess[100];
	FILE* fptr;
	
	WSAData data;
	WORD version = MAKEWORD(2, 2);
	if (WSAStartup(version, &data)) {
		printf("version is not supported !\n");

	}
	SOCKET client;
	int tv = 10000;
	//setsockopt(client, SOL_SOCKET, SO_RCVTIMEO, (const char*)(&tv), sizeof(int));
	sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(88);
	serverAddr.sin_addr.s_addr = inet_addr("192.168.0.115");
	while (1) {
		client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (connect(client, (sockaddr*)&serverAddr, sizeof(serverAddr))) {
			printf("cannot connect server!\n");
			getch();
			return 0;
		}
		char buffSend[BUFF_SIZE];
		char buffRecv[BUFF_SIZE];
		memset(buffSend, 0, BUFF_SIZE);
		memset(buffRecv, 0, BUFF_SIZE);
		memset(log_mess, 0, 100);
		strcpy(buffSend, "GET"); 
		int ret;
		printf("GET to sever: ");

	
		if (strcmp(buffSend, "") == 0) continue;
		ret = send(client, buffSend, BUFF_SIZE, 0);
		if (ret == SOCKET_ERROR) {
			printf("cannot send message! \n");
			getch();
			return 0;
		}
		

		ret = recv(client, buffRecv, BUFF_SIZE, 0);
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
		

		time(&rawtime);
		timeinfo = localtime(&rawtime);
		strcpy(log_mess,asctime(timeinfo));
		int t = strlen(log_mess);
		log_mess[t-1] = ' ';
		strcat(log_mess, " ");
		strcat(log_mess, buffRecv);
		strcat(log_mess, "\n"); 
		fptr = fopen("log.txt", "a+");

		if (fptr == NULL)
		{
			printf("Error!");
			return 0;
		}

		

		fprintf(fptr, "%s", log_mess);
		fclose(fptr);
	   printf("receive from : %s: %d  %s \n", inet_ntoa(serverAddr.sin_addr), ntohs(serverAddr.sin_port), buffRecv);
       printf("session is stoped! \n");	
	   closesocket(client);
	   Sleep(5000);
}


	WSACleanup();
	getch();
	return 0;
}