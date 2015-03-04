#include<io.h>
#include<iostream>
#include <string>
#include<fstream>
#include<winsock2.h>
#include<winsock2.h>

#pragma comment(lib,"ws2_32.lib") //Winsock Library

using namespace std;
int main(int argc, char *argv[])
{
	WSADATA wsa;
	SOCKET s;
	struct sockaddr_in server;
	char *message, server_reply[2000];
	int recv_size;

	printf("\nInitialising Winsock...");
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		cout << "Failed. Error Code : " << WSAGetLastError();
		return 1;
	}

	cout << "Initialised.\n";

	//Create a socket
	if ((s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
	{
		cout << "Could not create socket : " << WSAGetLastError();
	}

	cout << "Socket created.\n";


	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_family = AF_INET;
	server.sin_port = htons(8888);

	//Connect to remote server
	if (connect(s, (struct sockaddr *)&server, sizeof(server)) < 0)
	{
		puts("connect error");
		return 1;
	}

	puts("Connected");



	//Reply to the client
	string STRING;
	ifstream infile;
	infile.open("C:\\Users\\Abdul Moeed\\Desktop\\file.txt");
	while (!infile.eof())
	{
		getline(infile, STRING);
		//stringToUpper(STRING);
		STRING += "\n";
		const char *STRING_mod = STRING.c_str();
		send(s, STRING_mod, strlen(STRING_mod), 0);
	}
	char *end_msg = "end";
	send(s, end_msg, strlen(end_msg), 0);

	infile.close();


	






	closesocket(s);
	WSACleanup();


	return 0;
}
