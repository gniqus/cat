#include "cat.h"
#include <iostream>

// #include<iostream>
// #include <winsock2.h>
// using namespace std;
 
// #pragma comment(lib, "ws2_32.lib")
int main1()
{   
    try {
        TcpSocket socket;
        socket.Connect("127.0.0.1", 8888);
        socket.Send("/cache/default/test");
    } catch(const char* e) {
        cout << string(e) << endl;
    }
    //加载套接字库
    // WSADATA wsaData;
    // int iRet =0;
    // iRet = WSAStartup(MAKEWORD(2, 2), &wsaData);
    // if (iRet != 0)
    // {
    //     cout << "WSAStartup(MAKEWORD(2, 2), &wsaData) execute failed!" << endl;
    //     return -1;
    // }
    // if (2 != LOBYTE(wsaData.wVersion) || 2 != HIBYTE(wsaData.wVersion))
    // {
    //     WSACleanup();
    //     cout << "WSADATA version is not correct!" << endl;
    //     return -1;
    // }
 
    // //创建套接字
    // SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    // if (clientSocket == INVALID_SOCKET)
    // {
    //     cout << "clientSocket = socket(AF_INET, SOCK_STREAM, 0) execute failed!" << endl;
    //     return -1;
    // }
 
    // //初始化服务器端地址族变量
    // SOCKADDR_IN srvAddr;
    // srvAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
    // srvAddr.sin_family = AF_INET;
    // srvAddr.sin_port = htons(8888);
 
    // //连接服务器
    // iRet = connect(clientSocket, (SOCKADDR*)&srvAddr, sizeof(SOCKADDR));
    // if (0 != iRet)
    // {
    //     cout << "connect(clientSocket, (SOCKADDR*)&srvAddr, sizeof(SOCKADDR)) execute failed!" << endl;
    //     return -1;
    // }
 
    // //接收消息
    // char recvBuf[100];
    // recv(clientSocket, recvBuf, 100, 0);
    // printf("%s\n", recvBuf);
 
    // //发送消息
    // char sendBuf[100];
    // sprintf_s(sendBuf, "Hello, This is client %s", "兔子");
    // send(clientSocket, sendBuf, strlen(sendBuf)+1, 0);
 
    // //清理
    // closesocket(clientSocket);
    // WSACleanup();
     
    // system("pause");
    // return 0;
}