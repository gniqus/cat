#include "cat.h"

lru::lru(int cap) {
    cap_ = cap;
    size_ = 0;
}

any lru::get(string key) {
    if (kvmap_.find(key) != kvmap_.end()) {
        list_.remove(key);
        list_.push_back(key);
        kimap_[key] = --list_.end();
        return kvmap_[key];
    }
}

void lru::del(string key) {
    if (kvmap_.find(key) != kvmap_.end()) {
        kvmap_.erase(key);
        kimap_.erase(key);
        list_.remove(key);
        --size_;
    }
}

void lru::set(string key, any value) {
    if (kvmap_.find(key) != kvmap_.end()) {
        list_.remove(key);
    } else {
        if (size_ == cap_) {
            del(list_.front());
        }
        ++size_;
    }
    kvmap_[key] = value;
    list_.push_back(key);
    kimap_[key] = --list_.end();
}