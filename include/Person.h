#pragma once

// ──────────────────────────────────────────
// Person.h — Base class (virtual destructor)
// ──────────────────────────────────────────

#include <string>

class Person {
protected:
    std::string name;
    int age;

public:
    Person(const std::string& n, int a) : name(n), age(a) {}

    const std::string& getName() const { return name; }
    int                getAge()  const { return age; }

    virtual ~Person() = default;
};
