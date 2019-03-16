#include "string.h"
#include <iostream>

String::String(){
    data = nullptr;
    capasity = 0;
    length = 0;
}

char& String::operator[](size_t index){
    return data[index];
}

char String::operator[](size_t index) const{
    return data[index];
}


String::String(const String &value){
    data = new char[value.length];
    for (int i = 0; i < value.length; ++i){
        data[i] = value.data[i];
    }
    capasity = value.length;
    length = value.length;
}

String::String(char * const value){
    int size_value = 0;
    int k = 0;
    while (value[k] != '\0') {
        ++size_value;
        ++k;
    }
    data = new char[size_value];
    for (int i = 0; i < size_value; ++i){
        data[i] = value[i];
    }
    capasity = size_value;
    length = size_value;
}

String::~String(){
    char * tmp = data;
    data = nullptr; 
    delete[] tmp;
    capasity = 0;
    length = 0;
}

String& String::operator = (const String &value){
    delete[] data;
    data = new char[value.length];
    for (int i = 0; i < value.length; ++i){
        data[i] = value.data[i];
    }
    capasity = value.length;
    length = value.length;
    return *this;    
}

std::ostream& operator <<(std::ostream & out, const String &value){
    std::cout<<value.data;
    return out; 
}

std::istream& operator >>(std::istream & in, String &value){
    delete[] value.data;
    char *tmp = new char[1000];
    std::cin>>tmp;
    int k = 0;
    while (tmp[k] != '\0') {
        ++k;
    }
    value.data = new char[k];
    for (int i = 0; i < k; ++i){
        value.data[i] = tmp[i];
    }
    delete[] tmp;
    value.capasity = k;
    value.length = k;
    return in;
}

int String::size() const{
    return length;
}

void String::increase_capasity(){
    char *tmp = data;
    if (capasity == 0){
        capasity = 1;
    }
    data = new char[capasity*2];
    for (int i = 0; i < length; ++i){
        data[i] = tmp[i]; 
    }
    delete[] tmp;
    capasity *= 2;
}

String operator +(const String &left, const String &right){
    String tmp;
    tmp.data = new char[left.length + right.length];
    tmp.length = left.length + right.length;
    tmp.capasity = tmp.length;
    for (int i = 0; i < left.length; ++i){
        tmp.data[i] = left.data[i];
    }
    for (int i = 0; i < right.length; ++i){
        tmp.data[i + left.length] = right.data[i];
    }
    return tmp;
}

String& String::operator +=(const String &right){
    if (length + right.length > capasity){    
        while (length + right.length > capasity){
            increase_capasity();
        }
    }
    for (int i = length; i < length + right.length; ++i){
        data[i] = right.data[i - length];
    }
    length += right.length;
    return *this;
}

int operator == (const String &left, const String &right){
    if (left.length != right.length){
        return 0;
    }
    for (int i = 0; i < left.length; ++i){
        if (left.data[i] != right.data[i]){
            return 0;
        }
    }
    return 1;
}

String String::substr(size_t pos = 0, size_t len = -1) const{
    String res;
    if (len == -1){
        len = length;
    }
    res.data = new char[length-pos];
    res.length = length-pos;
    res.capasity = length-pos;
    for (int i = 0; i < res.length; ++i){
        res.data[i] = data[pos+i];
    }
    return res;
}























