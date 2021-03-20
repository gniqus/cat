#include "cat.h"

TcpServer::TcpServer(unsigned short port) {
    WSADATA wsaData;
    int iRet = 0;
    iRet = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iRet != 0) {
        throw "WSAStartup(MAKEWORD(2, 2), &wsaData) execute failed!";
    }
    if (2 != LOBYTE(wsaData.wVersion) || 2 != HIBYTE(wsaData.wVersion)) {
        WSACleanup();
        throw "WSADATA version is not correct!";
    }

    monitor_ = socket(AF_INET, SOCK_STREAM, 0);
    if (monitor_ == INVALID_SOCKET) {
        throw "monitor_ = socket(AF_INET, SOCK_STREAM, 0) execute failed!";
    }

    SOCKADDR_IN addrSrv;
    addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
    addrSrv.sin_family = AF_INET;
    addrSrv.sin_port = htons(port);

    iRet = bind(monitor_, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));
    if (iRet == SOCKET_ERROR) {
        throw "bind(monitor_, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR)) execute failed!";
    }

    iRet = listen(monitor_, CONNECT_NUM_MAX);
    if (iRet == SOCKET_ERROR) {
        throw "listen(monitor_, 10) execute failed!";
    }
}

TcpSocket* TcpServer::Accept() {
    SOCKADDR_IN clientAddr;
    int len = sizeof(SOCKADDR);
    SOCKET socket = accept(monitor_, (SOCKADDR*)&clientAddr, &len);
    if (socket == INVALID_SOCKET) {
        throw "accept(monitor_, (SOCKADDR*)&clientAddr, &len) execute failed!";
    }
    return new TcpSocket(socket);
}

TcpServer::~TcpServer() {
    closesocket(monitor_);
    WSACleanup();
}

TcpSocket::TcpSocket() {
    WSADATA wsaData;
    int iRet =0;
    iRet = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iRet != 0) {
        throw "WSAStartup(MAKEWORD(2, 2), &wsaData) execute failed!";
    }
    if (2 != LOBYTE(wsaData.wVersion) || 2 != HIBYTE(wsaData.wVersion)) {
        WSACleanup();
        throw "WSADATA version is not correct!";
    }

    socket_ = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_ == INVALID_SOCKET) {
        throw "socket_ = socket(AF_INET, SOCK_STREAM, 0) execute failed!";
    }
}

TcpSocket::TcpSocket(SOCKET socket) {
    WSADATA wsaData;
    int iRet =0;
    iRet = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iRet != 0) {
        throw "WSAStartup(MAKEWORD(2, 2), &wsaData) execute failed!";
    }
    if (2 != LOBYTE(wsaData.wVersion) || 2 != HIBYTE(wsaData.wVersion)) {
        WSACleanup();
        throw "WSADATA version is not correct!";
    }

    socket_ = socket;
    if (socket_ == INVALID_SOCKET) {
        throw "socket_ = socket(AF_INET, SOCK_STREAM, 0) execute failed!";
    }
}

void TcpSocket::Connect(string ip, unsigned short port) {
    SOCKADDR_IN srvAddr;
    srvAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
    srvAddr.sin_family = AF_INET;
    srvAddr.sin_port = htons(8888);

    int iRet = connect(socket_, (SOCKADDR*)&srvAddr, sizeof(SOCKADDR));
    if (0 != iRet) {
        throw "connect(socket_, (SOCKADDR*)&srvAddr, sizeof(SOCKADDR)) execute failed!";
    }
}

void TcpSocket::Send(string data) {
    send(socket_, data.c_str(), data.size()+1, 0);
}

string TcpSocket::Recv() {
    char recvBuf[256];
    recv(socket_, recvBuf, sizeof(recvBuf), 0);
    return string(recvBuf);
}

TcpSocket::~TcpSocket() {
    closesocket(socket_);
    WSACleanup();
}