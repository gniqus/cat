lru::lru(size_t cap) {
    cap_ = cap;
}

any lru::get(string key) {
    shared_lock<shared_mutex> lock(mutex_);
    cout << "db get key: " << key << endl;
    if (kimap_.find(key) == kimap_.end()) {
        cout << "not found key: " << key << endl;
        return any();
    }
    list_.erase(kimap_[key]);
    list_.push_front(key);
    kimap_[key] = list_.begin();
    return kvmap_[key];
}

void lru::set(string key, any value) {
    unique_lock<shared_mutex> lock(mutex_);
    cout << "db set key: " << key << endl;
    if (kimap_.find(key) == kimap_.end()) {
        if (list_.size() == cap_) {
            del(list_.back());
        }
    } else {
        list_.erase(kimap_[key]);
    }
    list_.push_front(key);
    kvmap_[key] = value;
    kimap_[key] = list_.begin();
}

void lru::del(string key) {
    unique_lock<shared_mutex> lock(mutex_);
    cout << "db del key: " << key << endl;
    if (kimap_.find(key) == kimap_.end()) {
        return;
    }
    list_.erase(kimap_[key]);
    kimap_.erase(key);
    kvmap_.erase(key);
}

lru::~lru() {}