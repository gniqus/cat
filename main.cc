#include "cat.h"

using namespace std;

// map<string, string> db;
// map<string, int> loadcnt;

// any testgtr(string key) {
//     cout << "[SlowDB] search key: " << key << endl;
//     if (db.find(key) == db.end()) {
//         cout << key << " not exists!" << endl;
//         return any();
//     }
//     loadcnt[key]++;
//     return db[key];
// }

int main() {
    Cat cat("127.0.0.1:8081");
    
    // Cat* cat = new Cat();
    // cat->set("test", string("success"));
    // serve s("test", shared_ptr<Cat>(cat));
    // s.run(8888);

    // TcpServer server(8888);
    // while (1) {
    //     TcpSocket* socket = server.Accept();
    //     string r = socket->Recv();
    //     cout << r << endl;
    //     delete socket;
    // }
    // while (1) {
    //     cout.flush();
    //     TcpSocket* socket = server.Accept();
    //     socket->Send("hello im server");
    //     string r = socket->Recv();
    //     cout << r << endl;
    // }
    // consistent cons(3, [](string key) {
    //     return atoll(key.c_str());
    // });
    // cons.add("6");
    // cons.add("4");
    // cons.add("2");
    // map <string, string> test;
    // test["2"] = "2";
    // test["11"] = "2";
    // test["23"] = "4";
    // test["27"] = "2";
    // for (auto i : test) {
    //     if (cons.get(i.first) != i.second) {
    //         cout << "error " << i.first << " " << i.second << endl;
    //     }
    // }
    // cons.add("8");
    // test["27"] = "8";
    // for (auto i : test) {
    //     if (cons.get(i.first) != i.second) {
    //         cout << "error " << i.first << " " << i.second << endl;
    //     }
    // }
    // db["tom"] = "11";
    // db["ack"] = "12";
    // db["sam"] = "13";

    // shared_ptr<getter> gtr(new getter(testgtr));

    // Cat test("test", 512, gtr);

    // test.add_group("test", 512, gtr);
    // test.get_group("test");
    // for (auto it = db.begin(); it != db.end(); it++) {
    //     string k = it->first;
    //     string v = it->second;
    //     cout.flush();

    //     any value = test.get(k);
    //     if (any_cast<string>(value) != v) {
    //         cout << "failed get " << k << endl;
    //     }
    //     value = test.get(k);
    //     if (loadcnt[k] > 1) {
    //         cout << "cache miss " << k << endl;
    //     }
    //     cout << "hit" << " " << any_cast<string>(value) << endl;
    // }

    // any value = test.get("cao");
    // if (value.has_value()) {
    //     cout << "get tom has_value" << " " << any_cast<string>(value) << endl;
    // }
    // value = test.get("unknown");
    // if (value.has_value()) {
    //     cout << "unknown get has_value" << endl;
    // }
    // cout << "end" << endl;
}
