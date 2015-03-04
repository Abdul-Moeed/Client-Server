#include<io.h>
#include<iostream>
#include <string>
#include<fstream>
#include<winsock2.h>
#include<winsock2.h>


#pragma comment(lib,"ws2_32.lib") //Winsock Library

using namespace std;

void stringToUpper(string &s)
{
	for (unsigned int l = 0; l < s.length(); l++)
	{
		s[l] = toupper(s[l]);
	}
}

int main()
{
	WSADATA wsa;
	SOCKET s, new_socket;
	struct sockaddr_in server, client;
	int c;
	char *message;
	char server_reply[2000];
	int recv_size;

	cout << "\nInitialising Winsock...";
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		cout << "Failed. Error Code" << WSAGetLastError();
		return 1;
	}

	cout << "Initialised.\n";

	//Create a socket
	if ((s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
	{
		cout << "Could not create socket " << WSAGetLastError();
	}

	cout << "Socket created.\n";

	//Prepare the sockaddr_in structure
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(8888);

	//Bind
	if (bind(s, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR)
	{
		cout << "Bind failed with error code : " << WSAGetLastError();
		exit(EXIT_FAILURE);
	}

	puts("Bind done");

	//Listen to incoming connections
	listen(s, 3);

	//Accept and incoming connection
	puts("Waiting for incoming connections...");

	c = sizeof(struct sockaddr_in);

	while ((new_socket = accept(s, (struct sockaddr *)&client, &c)) != INVALID_SOCKET)
	{
		puts("Connection accepted");

		recv_size = recv(new_socket, server_reply, 2000, 0);
		server_reply[recv_size] = '\0';
		while (server_reply != "end"){

			cout << server_reply << endl;
			recv_size = recv(s, server_reply, 2000, 0);
			server_reply[recv_size] = '\0';

		}



	}

	if (new_socket == INVALID_SOCKET)
	{
		cout << "accept failed with error code : " << WSAGetLastError();
		return 1;
	}

	closesocket(s);
	WSACleanup();



	return 0;
}
