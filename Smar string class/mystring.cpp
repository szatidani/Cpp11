#include <iostream>
#include <string.h>
#include "mystring.hpp"
using namespace std;

    //StringValue empty constructor
    StringValue::StringValue(){
        len = 0;
        counter = 0;
        mystr = nullptr;
    }
    //StringValue character array constructor
    StringValue::StringValue(const char* s){
        len = strlen(s);
        mystr = new char[len + 1];
        strcpy(mystr, s);
        counter = 0;
    }
    //StringValue character wrapper constructor
    StringValue::StringValue(const char s){
        len = 1;
        mystr = new char[len+1];
        mystr[0] = s;
        mystr[1] = 0;
        counter = 0;
    }
    //StringValue copy constructor
    StringValue::StringValue(const StringValue& other){
        len = other.len;
        counter = other.counter;
        //alloc memory for copying data
        mystr = new char[len + 1];
        strcpy(mystr, other.mystr);
    }
    //StringValue assignment operator
    StringValue& StringValue::operator=(const StringValue& other){
        if (this != &other){
            delete[] mystr;
            mystr = other.mystr;

            len = other.len;
            counter = other.counter;
        }
        return *this;
    }
    //StringValue move constructor
    StringValue::StringValue(StringValue&& other){
        other.counter++;

        len = other.len;
        other.len = 0;

        counter = other.counter;
        other.counter = 0;

        mystr = other.mystr;
        other.mystr = nullptr;
    }
    //StringValue move assignment operator
    StringValue& StringValue::operator=(StringValue&& other){
        if(this != &other){
            other.counter++;
            delete[] mystr;

            len = other.len;
            other.len = 0;

            counter = other.counter;
            other.counter = 0;

            mystr = other.mystr;
            other.mystr = nullptr;
        }
        return *this;
    }
    //StringValue concatenate
    StringValue StringValue::operator+(const StringValue& other)const{
        StringValue tmp;
        tmp.len = len + other.len;
        tmp.mystr = new char[tmp.len + 1];

        if(mystr != nullptr){
            strcpy(tmp.mystr, mystr);

            if(other.mystr != nullptr)
                strcat(tmp.mystr, other.mystr);

        } else {

            if(other.mystr != nullptr)
                strcpy(tmp.mystr, other.mystr);

            tmp.mystr = nullptr;
        }

        return tmp;
    }
    //StringValue length of string
    int StringValue::length(){
        return len;
    }
    //helper for printing out string
    void StringValue::print(std::ostream& os){
        os << mystr;
    }
    //helper for reading string
    void StringValue::save(std::istream& is){
	//it reads only length with <= len
        //it has to filled manually in case of empty string
        is.get(mystr,len);
    }
    //index operator
    char& StringValue::operator[](int i){
        if( i < 0 || i > len){
            cerr << "Invalid index" << endl;
        }
        return mystr[i];
    }
    //destructor
    StringValue::~StringValue(){
        delete[] mystr;
    }
    //MyString constructor
    MyString::MyString(){
        str = new StringValue();
        str->counter++;
    }
    //MyString constructor from character array
    MyString::MyString(const char* s){
        str = new StringValue(s);
        str->counter++;
    }
    //MyString constructor from character
    MyString::MyString(const char s){
        str = new StringValue(s);
        str->counter++;
    }
    //MyString copy constructor
    MyString::MyString(const MyString& other){
        this->str = other.str;
        str->counter++;
    }
    //MyString assignment operator
    MyString& MyString::operator=(const MyString& other){
       if(this != &other){

            if(--str->counter == 0)
                delete str;

            str = other.str;
            str->counter++;
       }
       return *this;
    }
    //Concatenation of MyStrings
    MyString MyString::operator+(const MyString& other){
        MyString tmp;
	*tmp.str = *str + *other.str;
        return tmp;
    }
    //MyString növelése másikkal
    MyString& MyString::operator+=(const MyString& other){
        StringValue *tmp = str;
        *str = *str + *other.str;
        str->counter++;

        if(--tmp->counter == 0)
            delete tmp;

        return *this;
    }
    //string + char, wrapped in string
    MyString MyString::operator+(const char ch) {
        MyString tmp(ch);
        return *this + tmp;
    }
    //string += char, wrapped in string
    MyString& MyString::operator+=(const char ch) {
        MyString tmp (ch);
        return *this += tmp;
    }
    //MyString's length
    int MyString::length(){
        return str->length();
    }
    //MyString index operator
    char& MyString::operator[](int i){
        StringValue *tmp = str;
        str = new StringValue(*str);
        str->counter = 1;

        if(--tmp->counter == 0)
            delete tmp;

        return (*str)[i];
    }
    //MyString d'tor
    MyString::~MyString(){
        if(--str->counter == 0)
            delete str;
    }
//print out
std::ostream& operator<<(std::ostream& os, const MyString& obj){
    obj.str->print(os);
    return os;
}
//read in
std::istream& operator>>(std::istream& is, MyString& obj){
    obj.str->save(is);
    return is;
}
