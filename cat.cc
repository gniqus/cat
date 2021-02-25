#include "cat.h"

getter::getter(callback cb) {
    if (cb == nullptr) {
        throw "null function!";
    }
    cb_ = cb;
}
any getter::get(string key) {
    return cb_(key);
}

group::group(string name, int cap, shared_ptr<getter> gtr) {
    name_ = name;
    gtr_ = gtr;
    cache_ = new cache(cap);
}
any group::get(string key) {
    return cache_->get(key);
}
void group::set(string key, any value) {
    cache_->set(key, value);
}
any group::pull(string key) {
    return gtr_->get(key);
}
group::~group() {
    delete cache_;
}

Cat::Cat(string name, int cap, shared_ptr<getter> gtr) {
    add_group(name, cap, gtr);
}
void Cat::add_group(string name, int cap, shared_ptr<getter> gtr) {
    unique_lock<shared_mutex> lock(mutex_);
    groups[name] = new group(name, cap, gtr);
}
group* Cat::get_group(string name) {
    shared_lock<shared_mutex> lock(mutex);
    current_ = groups[name];
    return current_;
}
any Cat::get(string key) {
    if (key.empty()) {
        return any();
    }
    any value = current_->get(key);
    return value.has_value() ? value : load(key);
}
any Cat::load(string key) {
    return locally(key);
}
any Cat::locally(string key) {
    any value = current_->pull(key);
    if (value.has_value()) {
        record(key, value);
    }
    return value;
}
void Cat::record(string key, any value) {
    current_->set(key, value);
}
Cat::~Cat() {
    delete current_;
    for (auto it = groups.begin(); it != groups.end(); ++it) {
        delete it->second;
    }
}