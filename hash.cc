#include "cat.h"

consistent::consistent(int virt, hash calc) {
    virt_ = virt;
    calc_ = calc;
}

void consistent::add(string key) {
    for (int i = 1; i <= virt_; ++i) {
        size_t hval = calc_(to_string(i) + key);
        keys_.push_back(hval);
        rotate(lower_bound(keys_.begin(), keys_.end() - 1, hval), keys_.end() - 1, keys_.end());
        cast_[hval] = key;
    }
}

string consistent::get(string key) {
    if (key.empty()) {
        return "";
    }
    sort(keys_.begin(), keys_.end());
    size_t hval = calc_(key);
    int i = lower_bound(keys_.begin(), keys_.end(), hval) - keys_.begin();
    return cast_[keys_[i%keys_.size()]];
}