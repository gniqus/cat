class db {
public:
    virtual any get(string key) = 0;
    virtual void set(string key, any value) = 0;
    virtual void del(string key) = 0;
    virtual ~db() = 0;
};

class lru: public db {
private:
    shared_mutex mutex_;
    size_t cap_;
    unordered_map<string, any> kvmap_;
    unordered_map<string, list<string>::iterator> kimap_;
    list<string> list_;
public:
    lru(size_t cap = 1024);
    any get(string key);
    void set(string key, any value);
    void del(string key);
    ~lru();
};