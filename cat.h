#include <mutex>
#include <string>
#include <functional>
#include <shared_mutex>
#include <list>
#include <string>
#include <any>
#include <unordered_map>
#include <map>
#include <memory>
#include <algorithm>
#include <iostream>

#include<WinSock2.h>
#pragma comment(lib, "ws2_32.lib")
#define CONNECT_NUM_MAX 10

using namespace std;

class lru {
private:
    unordered_map<string, any> kvmap_;
    unordered_map<string, list<string>::iterator> kimap_; 
    list<string> list_;
    int cap_, size_;
public:
    lru(int cap);
    any get(string key);
    void set(string key, any value);
    void del(string key);
};

class cache {
private:
    mutex           mutex_;
    shared_ptr<lru> lru_;
    int             cap_;
public:
    cache(int cap);
    void set(string key, any value);
    any get(string key);
};

class getter {
private:
    typedef function<any (string)> callback;
    callback cb_;
public:
    getter(callback cb);
    any get(string key);
};

class group {
private:
    string              name_;
    shared_ptr<getter>  gtr_;
    shared_ptr<cache>   cache_;  
    shared_mutex        mutex_;
public:
    group(string name, int cap, shared_ptr<getter> gtr);
    any get(string key);
    void set(string key, any value);
    any pull(string key);
};

class Cat {
private:
    map<string, shared_ptr<group>> groups;
    shared_ptr<group> current_;
    shared_mutex mutex_;
public:
    Cat(string name = "default", int cap = 64, shared_ptr<getter> gtr = shared_ptr<getter>(new getter([](string key) {
        return any();
    })));
    void add_group(string name, int cap, shared_ptr<getter> gtr);
    shared_ptr<group> get_group(string name);
    any get(string key);
private:
    any load(string key);
    any locally(string key);
    void record(string key, any value);
};

class consistent {
private:
    typedef function<size_t (string)> hash;
    hash                calc_;
    int                 virt_;
    vector<size_t>      keys_;
    map<size_t, string> cast_;

    void add() {}
public:
    consistent(int virt, hash calc = std::hash<string>());
    void add(string key);
    string get(string key);
};

class TcpSocket {
private:
    SOCKET socket_;
public:
    TcpSocket();
    TcpSocket(SOCKET socket);
    void Connect(string ip, unsigned short port);
    void Send(string data);
    string Recv();
    ~TcpSocket();
};

class TcpServer {
private:
    SOCKET monitor_;
public:
    TcpServer(unsigned short port);
    TcpSocket* Accept();
    ~TcpServer();
};