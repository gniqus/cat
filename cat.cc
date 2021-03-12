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
    cache_ = shared_ptr<cache>(new cache(cap));
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
string group::name() {
    return name_;
}

Cat::Cat(string self, string name, int cap, shared_ptr<getter> gtr) {
    add_group(name, cap, gtr);
    srv_ = shared_ptr<baserve>(new serve(self, shared_ptr<Cat>(this)));
}
void Cat::add_group(string name, int cap, shared_ptr<getter> gtr) {
    unique_lock<shared_mutex> lock(mutex_);
    groups[name] = shared_ptr<group>(new group(name, cap, gtr));
    current_ = groups[name];
}
shared_ptr<group> Cat::get_group(string name) {
    shared_lock<shared_mutex> lock(mutex);
    if (groups.find(name) == groups.end()) {
        cout << "group error" << endl;
    }
    current_ = groups[name];
    return current_;
}

void Cat::set(string key, any value) {
    current_->set(key, value);
}

any Cat::get(string key) {
    if (key.empty()) {
        return any();
    }
    any value = current_->get(key);
    return value.has_value() ? value : load(key);
}
void Cat::registerPeer(string peer) {
    regex sep(":");
    vector<string> v(sregex_token_iterator(peer.begin(), peer.end(), sep, -1), sregex_token_iterator());
    srv_->set(v[0], atoi(v[1].c_str()));
}
any Cat::load(string key) {
    if (srv_ != nullptr) {
        shared_ptr<client> cli = srv_->pick(key);
        if (cli != nullptr) {
            return cli->get(current_->name(), key);
        }
    }
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