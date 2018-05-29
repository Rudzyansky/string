#ifndef STRING_STRING_H
#define STRING_STRING_H

#include <cstddef>
#include <ostream>

namespace rudzyansky {
    class string {
        size_t _size;
        char *_data;
        inline void throw_if_null(void *ptr);
        inline void *allocate(size_t size);
    public:
        string();
        string(const char *str);
        explicit string(char c);
        ~string();

        char *data();
        size_t size();

        static size_t lengthOf(const char *str);

        string &operator*();

        string &operator+(const char *str);
        string &operator+(string &str);
        string &operator+(char c);

        string &operator+=(const string &str);
        string &operator+=(string &str);

        string &operator=(const char *str);
        string &operator=(const string &str);

        char &operator[](size_t index);

        bool operator==(string &str);

        friend std::ostream &operator<<(std::ostream &os, const string &str);

        string &assign(size_t count, char c);

        char &front();
        char &back();

        const char *c_str();

        bool empty();

        void clear();

        string &insert(size_t index, const char *str);

        void push_back(char c);

        char pop_back();

        string &append(const string &str);

        string &replace(size_t pos, size_t count, const string &str);

        string substr(size_t pos, size_t count);

        size_t find(char c);
        size_t find(const string &str);
    };
}

#endif //STRING_STRING_H
