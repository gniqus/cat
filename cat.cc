#include <string>
#include <functional>
#include <mutex>
#include <shared_mutex>

using namespace std;

class getter {
private:
    typedef function<any (string)> callback;
    callback cb_;
public:
    getter() {}
    getter(callback cb) {
        if (cb == nullptr) {
            throw "null function!";
        }
        cb_ = cb;
    }
    
    any get(string key) {
        return cb_(key);
    }
};


class group {
private:
    string       name_;
    getter       gtr_;
    cache*       cache_;  
    shared_mutex mutex_;
public:
    group(string name, int cap, getter gtr) {
        name_ = name;
        gtr_ = gtr;
        cache_ = new cache(cap);
    }
    any get(string key) {
        return cache_->get(key);
    }
    void set(string key, any value) {
        cache_->set(key, value);
    }
    any pull(string key) {
        return gtr_.get(key);
    }
};

class cat {
private:
    map<string, group*> groups;
    group* current_;
    shared_mutex mutex_;
public:
    void add_group(string name, int cap, getter gtr) {
        unique_lock<shared_mutex> lock(mutex_);
        groups[name] = new group(name, cap, gtr);
    }
    group* get_group(string name) {
        shared_lock<shared_mutex> lock(mutex);
        current_ = groups[name];
        return current_;
    }
    any get(string key) {
        if (key.empty()) {
            return any();
        }
        any value = current_->get(key);
        return value.has_value() ? value : load(key);
    }
private:
    any load(string key) {
        return locally(key);
    }
    any locally(string key) {
        any value = current_->pull(key);
        if (value.has_value()) {
            record(key, value);
        }
        return value;
    }
    void record(string key, any value) {
        current_->set(key, value);
    }
};