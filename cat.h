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
    mutex mutex_;
    lru*  lru_;
    int   cap_;
public:
    cache(int cap);
    void set(string key, any value);
    any get(string key);
    ~cache();
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
    cache*              cache_;  
    shared_mutex        mutex_;
public:
    group(string name, int cap, shared_ptr<getter> gtr);
    any get(string key);
    void set(string key, any value);
    any pull(string key);
    ~group();
};

class Cat {
private:
    map<string, group*> groups;
    group* current_;
    shared_mutex mutex_;
public:
    Cat(string name = "default", int cap = 64, shared_ptr<getter> gtr = shared_ptr<getter>(new getter([](string key) {
        return any();
    })));
    void add_group(string name, int cap, shared_ptr<getter> gtr);
    group* get_group(string name);
    any get(string key);
    ~Cat();
private:
    any load(string key);
    any locally(string key);
    void record(string key, any value);
};