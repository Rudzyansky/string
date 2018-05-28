#include <cstdlib>
#include <new>
#include <cstring>
#include "string.h"

string::string() : _data((char *) calloc(1, 1)), _size(0) { throw_if_null(_data) }

string::string(const char *str) : _size(lengthOf(str)), _data((char *) malloc(_size + 1)) {
    throw_if_null(_data)
    memcpy(_data, str, _size);
    _data[_size] = 0;
}

string::string(const char c) : _size(1), _data((char *) calloc(2, 1)) {
    throw_if_null(_data)
    _data[0] = c;
}

string::~string() {
    free(_data);
}

char *string::data() {
    return _data;
}

size_t string::size() {
    return _size;
}

size_t string::lengthOf(const char *str) {
    size_t tmp = 0;
    for (const char *ptr = str; *ptr; ++ptr, ++tmp);
    return tmp;
}

string &string::operator*() {
    return *this;
}

string &string::operator+(string &str) {
    auto tmp = new string();
    throw_if_null(tmp)
    tmp->_size = _size + str._size;
    tmp->_data = (char *) malloc(tmp->_size + 1);
    throw_if_null(tmp->_data)
    memcpy(tmp->_data, _data, _size);
    memcpy(tmp->_data + _size, str._data, str._size);
    tmp->_data[tmp->_size] = 0;
    return *tmp;
}

string &string::operator+(const char *str) {
    auto tmp = new string();
    throw_if_null(tmp)
    size_t length = lengthOf(str);
    tmp->_size = _size + length;
    tmp->_data = (char *) malloc(tmp->_size + 1);
    throw_if_null(tmp->_data)
    memcpy(tmp->_data, _data, _size);
    memcpy(tmp->_data + _size, str, length);
    tmp->_data[tmp->_size] = 0;
    return *tmp;
}

string &string::operator+(char c) {
    auto tmp = new string();
    throw_if_null(tmp)
    tmp->_size = _size;
    tmp->_data = (char *) malloc(tmp->_size + 1);
    throw_if_null(tmp->_data)
    memcpy(tmp->_data, _data, _size);
    tmp->_data[tmp->_size++] = c;
    tmp->_data[tmp->_size] = 0;
    return *tmp;
}

string &string::operator+=(const string &str) {
    size_t length = _size + str._size;
    auto tmp = (char *) malloc(length + 1);
    throw_if_null(tmp)
    memcpy(tmp, _data, _size);
    memcpy(tmp + _size, str._data, str._size);
    tmp[length] = 0;
    free(_data);
    _data = tmp;
    _size = length;
    return *this;
}

string &string::operator+=(string &str) {
    size_t length = _size + str._size;
    auto tmp = (char *) malloc(length + 1);
    throw_if_null(tmp)
    memcpy(tmp, _data, _size);
    memcpy(tmp + _size, str._data, str._size);
    tmp[length] = 0;
    free(_data);
    _data = tmp;
    _size = length;
    return *this;
}

string &string::operator=(const char *str) {
    _size = lengthOf(str);
    auto tmp = (char *) malloc(_size + 1);
    throw_if_null(tmp)
    memcpy(tmp, str, _size);
    tmp[_size] = 0;
    free(_data);
    _data = tmp;
    return *this;
}

string &string::operator=(const string &str) {
    auto tmp = (char *) malloc(_size + 1);
    throw_if_null(tmp)
    _size = str._size;
    memcpy(tmp, str._data, _size);
    tmp[_size] = 0;
    free(_data);
    _data = tmp;
    return *this;
}

bool string::operator==(string &str) {
    if (this == &str) return true;
    if (_size != str._size) return false;
    for (const char *ptr1 = _data, *ptr2 = str._data; *ptr1; ++ptr1, ++ptr2) if (*ptr1 != *ptr2) return false;
    return true;
}

std::ostream &operator<<(std::ostream &os, const string &str) {
    os << str._data;
    return os;
}

char &string::front() {
    return *_data;
}

char &string::back() {
    return _data[_size - 1];
}

char &string::operator[](size_t index) {
    if (index > _size) throw std::out_of_range("invalid index");
    return _data[index];
}

string &string::assign(size_t count, char c) {
    auto ptr = (char *) malloc(count + 1);
    throw_if_null(ptr)
    free(_data);
    _data = ptr;
    _size = count;
    for (size_t i = 0; i < count; ++i, ++ptr) *ptr = c;
    ptr[count] = 0;
    return *this;
}

const char *string::c_str() {
    return _data;
}

bool string::empty() {
    return !(bool) _size;
}

void string::clear() {
    auto ptr = (char *) calloc(1, 1);
    throw_if_null(ptr);
    free(_data);
    _data = ptr;
    _size = 0;
}

string &string::insert(size_t index, const char *str) {
    if (index > _size) throw std::out_of_range("invalid index");
    size_t str_len = lengthOf(str);
    auto ptr = (char *) malloc(_size + str_len + 1);
    throw_if_null(ptr);
    memcpy(ptr, _data, index);
    memcpy(ptr + index, str, str_len);
    memcpy(ptr + index + str_len, _data + index, _size - index);
    free(_data);
    _data = ptr;
    _data[_size += str_len] = 0;
    return *this;
}

string &string::replace(size_t pos, size_t count, const string &str) {
    if (pos > _size) throw std::out_of_range("invalid index");
    if (count > _size - pos) count = _size - pos;
    auto ptr = (char *) malloc(_size - count + str._size + 1);
    throw_if_null(ptr);
    memcpy(ptr, _data, pos);
    memcpy(ptr + pos, str._data, str._size);
    memcpy(ptr + pos + str._size, _data + pos + count, _size - count);
    free(_data);
    _data = ptr;
    _data[_size += str._size - count] = 0;
    return *this;
}

void string::push_back(char c) {
    auto ptr = realloc(_data, _size + 2);
    throw_if_null(ptr)
    _data[_size++] = c;
    _data[_size++] = 0;
}

char string::pop_back() {
    char c = _data[_size];
    _data[_size--] = 0;
    return c;
}

string &string::append(const string &str) {
    auto ptr = (char *) malloc(_size + str._size + 1);
    throw_if_null(ptr);
    memcpy(ptr, _data, _size);
    memcpy(ptr + _size, str._data, str._size);
    free(_data);
    _data = ptr;
    _data[_size += str._size] = 0;
    return *this;
}

string string::substr(size_t pos, size_t count) {
    if (pos > _size) throw std::out_of_range("invalid index");
    if (count > _size - pos) count = _size - pos;
    string str;
    str._size = count;
    str._data = (char *) malloc(count + 1);
    throw_if_null(str._data);
    memcpy(str._data, _data + pos, count);
    str._data[count] = 0;
    return str;
}

size_t string::find(char ch) {
    size_t index = static_cast<size_t>(-1), i = 0;
    for (const char *c = _data; *c; ++c, ++i) if (*c == ch) index = i;
    return index;
}

size_t string::find(const string &str) {
    if (str._size > _size) std::out_of_range("long size");
    auto index = static_cast<size_t>(-1);
    for (size_t i = 0; i <= _size - str._size; ++i)
        if (memcmp(_data + i, str._data, str._size) == 0) index = i;
    return index;
}
