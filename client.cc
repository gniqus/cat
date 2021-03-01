#include "cat.h"

client::client(string ip, unsigned short port, string base) {
    ip_   = ip;
    base_ = base;
    port_ = port;
}

any client::get(string group, string key) {
    TcpSocket socket;
    socket.Connect(ip_, port_);
    socket.Send(base_+group+"/"+key);
    return socket.Recv();
}