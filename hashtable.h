#ifndef UNTITLED1_HASHTABLE_H
#define UNTITLED1_HASHTABLE_H

#include "value.hpp"

class HashTable {
public:
    HashTable();

    ~HashTable();

    //Copy other hashtable
    HashTable(const HashTable& b);

    // Return copy other hashtable
    HashTable& operator=(const HashTable& b);

    // Add new element with passed key and value and return true
    // Chang value if element with passed key exist and return false
    bool insert(const Key& k, const Value& v);

    // Find element with passed key and return element value
    // Add new element with passed key and default value if element not find
    Value& operator[](const Key& k);

    // Find element with passed key and return element value
    // Throw out_of_range if key not found
    Value& at(const Key& k);
    const Value& at(const Key& k) const;

    // Delete all elements from hashtable
    void clear();

    // Delete element with passed key
    // Return true if element was removed else false
    bool erase(const Key& k);

    // Return true if element is find else false
    bool contains(const Key& k) const;

    // Swap this and other hashtable
    void swap(HashTable& b);

    // Return number of table elements
    size_t size() const;

    // Return whether hashtable is empty
    bool empty() const;

    // Return result comparison two hashtable by keys and values
    // CR: specify what happens in ==
    friend bool operator==(const HashTable& a, const HashTable& b);
    friend bool operator!=(const HashTable& a, const HashTable& b);
private:
    struct List;

    // CR: static
    const int PRIME = 7;
    // CR: static
    const int DEFAULT_CAPACITY = 8;

    // CR: init with DEFAULT_CAPACITY
    size_t capacity_;
    size_t size_;
    List **data;

    unsigned long hash_func(const Key& k) const;
    void resize();
    const Value& at_const(const Key& k) const;
    void copy(const HashTable& b);
    List* add_list(const Key& k, const Value& v);

};

#endif
