#include <iostream>
#include "string.h"

int main() {
    string str = "hello ";
    str += str + str + *string("world") + ' ' + "from prog " + str;
    std::cout << str << str.size() << std::endl;
    str = "hello world";
    std::cout << str << str.size() << std::endl;
    str = string().assign(30, 'a').insert(4, "bcd hello world").substr(2,16).replace(2, 5, string("PROG")).append(string("test"));
    std::cout << str << std::endl;
    std::cout << str.find(string("lte"))<< std::endl;
    return 0;
}