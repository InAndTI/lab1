#include <iostream>
#include <algorithm>
#include "hashtable.h"

struct HashTable::List {
    List(Key  k,Value  v): key(std::move(k)), value(std::move(v)) {}

    Key key;
    Value value;
    List *next = nullptr;
};

// Return hash by passed key
unsigned long HashTable::hash_func( const Key& k) const {
    size_t len = k.length();
    unsigned res = 0;
    for (int i = 0; i < len; i++) {
        res += (res * PRIME) + k[i];
    }

    return res % capacity_;
}

HashTable::HashTable() : data(new List*[DEFAULT_CAPACITY]()), capacity_(HashTable::DEFAULT_CAPACITY), size_(0){}

HashTable::~HashTable(){
    clear();
    delete[] data;
}

HashTable::HashTable(const HashTable& b) : capacity_(b.capacity_), data(new List*[capacity_]()), size_(){
    copy(b);
}

HashTable& HashTable::operator=(const HashTable& b) {
    if (this != &b) {
        clear();
        capacity_ = b.capacity_;
        delete [] data;
        data = new List*[capacity_]();
        copy(b);
    }
    return *this;
}

// Copy other hashtable
void HashTable::copy(const HashTable &b) {
    for (int i = 0; i < b.capacity_; i++) {
        if (b.data[i])
            for (List *tmp = b.data[i]; tmp; tmp = tmp->next) {
                add_list(tmp->key, tmp->value);
            }
    }
}

// Return element with passed key
// Add new element with passed key and value if element not find
HashTable::List* HashTable::add_list(const Key &k, const Value &v) {
    if (size_ >= capacity_ * 3 / 4)
        resize();

    unsigned long hash = hash_func(k);

    if (data[hash] == nullptr) {
        data[hash] = new List(k, v);
        size_++;
        return data[hash];
    }

    List *tmp;
    for (tmp = data[hash]; tmp->next && tmp->key != k; tmp = tmp->next) {}

    if (tmp->key != k) {
        tmp->next = new List(k, v);
        size_++;
        return tmp;
    }

    return tmp;
}

bool HashTable::insert(const Key& k, const Value& v){
    List* tmp = add_list(k, v);
    if (tmp->value != v) {
        tmp->value = v;
        return false;
    }

    return true;
}

Value& HashTable::operator[](const Key& k){
    return add_list(k, Value())->value;
}

// Find element with passed key and return element value
// Throw out_of_range if element not find
const Value& HashTable::at_const(const Key& k) const {
    unsigned long hash = hash_func(k);

    if (!data[hash])
        throw std::out_of_range("out_of_range");

    List* tmp;
    for (tmp = data[hash]; tmp->next && tmp->key != k; tmp = tmp->next) {}

    if (tmp->key != k)
        throw std::out_of_range("out_of_range");

    return tmp->value;
}

Value& HashTable::at(const Key& k){
    return const_cast<Value&>(at_const(k));
}

const Value& HashTable::at(const Key& k) const{
    return at_const(k);
}

void HashTable::clear(){
    for (int i = 0; i < capacity_; i++){
        while (data[i] != nullptr) {
            List* tmp = data[i]->next;
            delete data[i];
            data[i] = tmp;
        }
    }
    size_ = 0;
}

bool HashTable::erase(const Key& k){
    unsigned long hash = hash_func(k);

    if (data[hash] == nullptr)
        return false;

    List* tmp = data[hash];

    if (tmp->key == k) {
        data[hash] = tmp->next;
        delete tmp;
        size_--;
        return true;
    }

    List* next = tmp->next;
    while (next != nullptr) {
        if (next->key == k) {
            tmp->next = next->next;
            size_--;
            delete next;
            return true;
        }
        tmp = next;
        next = tmp->next;
    }

    return false;
}

bool HashTable::contains(const Key& k) const{
    unsigned long hash = hash_func(k);

    if (!data[hash])
        return false;

    List* tmp;
    for (tmp = data[hash]; tmp->next && tmp->key != k; tmp = tmp->next) {}

    if (tmp->key != k)
        return false;

    return true;
}

void HashTable::swap(HashTable& b){
    std::swap(size_, b.size_);
    std::swap(capacity_, b.capacity_);
    std::swap(data, b.data);
}

size_t HashTable::size() const{
    return size_;
}

bool HashTable::empty() const{
    return size_ == 0;
}

// Expands hashtable twice
void HashTable::resize() {
    List** other_data = new List*[capacity_ * 2]();
    std::swap(other_data, data);
    size_t other_capacity = capacity_;
    capacity_ *= 2;
    size_t other_size = size_;
    size_ = 0;
    List* tmp;

    for (int i = 0; i < other_capacity && other_size != 0; ++i) {
        while (other_data[i] != nullptr) {
            other_size--;
            add_list(other_data[i]->key, other_data[i]->value);
            tmp = other_data[i]->next;
            delete other_data[i];
            other_data[i] = tmp;
        }
    }
    delete [] other_data;
}

bool operator==(const HashTable& a, const HashTable& b){
    if (a.size() != b.size())
        return false;

    HashTable::List* a_list;
    HashTable::List* b_list;

    for (int i = 0; i < a.capacity_; ++i) {
        for (a_list = a.data[i]; a_list; a_list = a_list->next) {
            if (b.data[b.hash_func(a_list->key)] == nullptr)
                return false;

            for (b_list = b.data[b.hash_func(a_list->key)]; b_list->next && b_list->key != a_list->key; b_list = b_list->next) {}

            if (b_list->key != a_list->key || a_list->value != b_list->value)
                return false;
        }
    }
    return true;
}

bool operator!=(const HashTable& a, const HashTable& b){
    return !(a == b);
}
