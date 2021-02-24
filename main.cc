#include <string>
#include <functional>
#include <mutex>
#include <shared_mutex>
#include <iostream>
#include <any>
#include <map>
#include <list>
#include <unordered_map>

#include "lru.cc"
#include "cache.cc"
#include "cat.cc"

using namespace std;

map<string, string> db;
map<string, int> loadcnt;

any testgtr(string key) {
    cout << "[SlowDB] search key: " << key << endl;
    if (db.find(key) == db.end()) {
        cout << key << " not exists!" << endl;
    }
    loadcnt[key]++;
    return db[key];
}

int main() {
    db["tom"] = "11";
    db["ack"] = "12";
    db["sam"] = "13";

    getter gtr(testgtr);

    cat test;
    test.add_group("test", 512, gtr);
    test.get_group("test");
    for (auto it = db.begin(); it != db.end(); it++) {
        string k = it->first;
        string v = it->second;
        cout.flush();

        any value = test.get(k);
        if (any_cast<string>(value) != v) {
            cout << "failed get " << k << endl;
        }
        value = test.get(k);
        if (loadcnt[k] > 1) {
            cout << "cache miss " << k << endl;
        }
        cout << "hit" << " " << any_cast<string>(value) << endl;
    }
    any value = test.get("tom");
    if (value.has_value()) {
        cout << "get tom has_value" << " " << any_cast<string>(value) << endl;
    }
    value = test.get("unknown");
    if (value.has_value()) {
        cout << "unknown get has_value" << endl;
    }
}