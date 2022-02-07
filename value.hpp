#ifndef UNTITLED1_VALUE_H
#define UNTITLED1_VALUE_H

#include <string>

typedef std::string Key;

struct Value
{
    Value() = default;
    Value (std::string n, unsigned a = 0) : name(n), age(a) {}
    std::string name;
    unsigned age{};

    friend bool operator==(const Value& a, const Value& b) {
        return a.name == b.name && a.age == b.age;
    }

    friend bool operator!=(const Value& a, const Value& b) {
        return !(a == b);
    }
};

#endif
