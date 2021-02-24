#include <mutex>

using namespace std;

class cache {
private:
    mutex mutex_;
    lru*  lru_;
    int   cap_;
public:
    cache(int cap) {
        cap_ = cap;
        lru_ = new lru(cap_);
    }
    void set(string key, any value) {
        lock_guard<mutex> lock(mutex_);
        if (lru_ == nullptr) {
            lru_ = new lru(cap_);
        }
        lru_->set(key, value);
    }

    any get(string key) {
        lock_guard<mutex> lock(mutex_);
        if (lru_ == nullptr) {
            return any();
        }
        return lru_->get(key);
    }
};