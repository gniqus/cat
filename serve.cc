#include "cat.h"

serve::serve(string self, shared_ptr<Cat> cat) {
    self_ = self;
    base_ = "/cache/";
    cat_  = cat;
}

serve::run(unsigned short port) {
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
            cout << "not found" << endl;
            continue;
        }
        cout << any_cast<string>(value) << endl;
        // socket->Send(any_cast<string>(value));
    }
}