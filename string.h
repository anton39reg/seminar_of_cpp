#include <iostream>

class String{
    friend int operator == (const String &, const String &);
    friend String operator + (const String &, const String &);
    friend std::ostream & operator << (std::ostream &, const String &);
    friend std::istream & operator >> (std::istream &, String &); 
    
  private:
    char *data;
    size_t capasity;
    size_t length;
    void increase_capasity();
    
  public:
    String();
    String(const String &);
    String(char * const);
    ~String();
    int size() const; 
    String substr(size_t pos, size_t len) const;
    char& operator[](size_t index);
    char operator[](size_t index) const;
    String& operator = (const String &);
    String& operator += (const String &);
};

