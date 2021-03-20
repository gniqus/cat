class Server {
private:
    db* db_;        // 对应多个节点，每个节点是一个数据库
    size_t dbnum_;  // 存储节点的数量

    void get(string key);
    void set(string key, any value);
public:
    Server(size_t dbnum = 16);
    void Run(unsigned short port);
};