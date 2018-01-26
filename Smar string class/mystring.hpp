#pragma once

class StringValue{
private:
    char *mystr;

    int len;
public:
int counter = 0;
    StringValue();
    StringValue(const char* s);
    StringValue(const char s);
    StringValue(const StringValue& other);
    StringValue& operator=(const StringValue& other);
    StringValue(StringValue&& other);
    StringValue& operator=(StringValue&& other);
    StringValue operator+(const StringValue& other)const;
    char& operator[](int i);
    int length();
    void print(std::ostream& os);
    void save(std::istream& is);
    ~StringValue();
};

class MyString{
public:
    StringValue* str;
    MyString();
    MyString(const char* s);
    MyString(const char s);
    MyString(const MyString& other);
    MyString& operator=(const MyString& other);
    MyString operator+(const MyString& other);
    MyString& operator+=(const MyString& other);
    MyString operator+(const char ch);
    MyString& operator+=(const char ch);
    char& operator[](int i);
    int length();

    ~MyString();
};

std::ostream& operator<<(std::ostream& os, const MyString& obj);
std::istream& operator>>(std::istream& is, MyString& obj);
