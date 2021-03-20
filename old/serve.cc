#include "cat.h"

serve::serve(string self, shared_ptr<Cat> cat) {
    self_ = self;
    base_ = "/cache/";
    cat_  = cat;
    cons_ = shared_ptr<consistent>(new consistent(3));
    regex sep(":");
    vector<string> v(sregex_token_iterator(self_.begin(), self_.end(), sep, -1), sregex_token_iterator());
    string ip = v[0];
    string port = v[1];
    run(atoi(port.c_str()));
}

void serve::run(unsigned short port) {
    TcpServer server(port);
    while (1) {
        shared_ptr<TcpSocket> socket(server.Accept());
        string r = socket->Recv();
        if (r.find(base_) == 0) {
            r = r.substr(base_.size());
        }
        
        regex sep("/");
        vector<string> v(sregex_token_iterator(r.begin(), r.end(), sep, -1), sregex_token_iterator());
        
        cat_->get_group(v[0]);
        any value = cat_->get(v[1]);
        if (!value.has_value()) {
            socket->Send("not found.");
            continue;
        }
        // cout << any_cast<string>(value) << endl;
        socket->Send(any_cast<string>(value));
    }
}

void serve::set(string ip, unsigned short port) {
    lock_guard<mutex> lock(mutex_);
    string peer = ip + ":" + to_string(port);
    cons_->add(peer);
    clients_[peer] = shared_ptr<client>(new client(ip, port, base_));
}

shared_ptr<client> serve::pick(string key) {
    lock_guard<mutex> lock(mutex_);
    string peer = cons_->get(key);
    if (peer.empty() || peer == self_) {
        return clients_[peer];
    }
    return nullptr;
}