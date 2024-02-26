#include "./HashMap.h"
#include <iostream>
#include <string>


int main() {
    HashMap<std::string, int> foo1;
    foo1.insert({"hello", 1});
    foo1.insert({"world", 2});
    foo1.insert({"foo", 3});
    foo1.inspect();
    foo1.insert({"bar", 4});
    foo1.inspect();
    foo1.insert({"baz", 5});
    foo1.inspect();
    foo1.insert({"qux", 6});
    foo1.inspect();
    foo1.insert({"quux", 7});
    foo1.insert({"corge", 8});
    foo1.insert({"grault", 9});
    foo1.insert({"garply", 10});
    foo1.insert({"waldo", 11});
    foo1.insert({"fred", 12});
    foo1.insert({"plugh", 13});
    foo1.insert({"xyzzy", 14});
    foo1.insert({"thud", 15});
    foo1.insert({"foxy", 16});
    foo1.insert({"baaz", 17});

    foo1.inspect();

    foo1.erase(foo1.begin());
    foo1.erase(foo1.begin());
    foo1.erase(foo1.begin());
    foo1.erase(foo1.begin());
    foo1.insert_or_assign("foo", -1000);
    foo1.insert_or_assign("lhy", -1000);
    foo1["lhy"] = 10000;
    foo1["lhylhylhy"];
    foo1.emplace("xxxxxxxxx", 1000000);
    foo1.emplace("lhy", -111);
    foo1.inspect();

    std::cout << foo1.contains("lhy");
    return 0;
}