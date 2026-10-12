#include <string>
#include <cstring>
#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;

class mystring
{
private:
    char *ch = nullptr;
    int len = 0;

public:
    // Default constructor
    mystring()
    {
        ch = nullptr;
        len = 0;
    }
    
    // Constructor with length and character
    mystring(int _len, int c)
    {
        len = _len;
        ch = new char[len];
        for (int i = 0; i < len; i++) {
            ch[i] = c;
        }
    }
    
    // Constructor from string
    mystring(string &c)
    {
        len = c.length();
        ch = new char[len];
        for (int i = 0; i < len; i++) {
            ch[i] = c[i];
        }
    }
    
    // Destructor
    ~mystring()
    {
        delete[] ch;
        ch = nullptr;
        len = 0;
    }
    
    // Subscript operator
    char operator[](int x) const
    {
        if (x < 0 || x >= len) {
            return '\0';
        }
        return ch[x];
    }
    
    // Less than operator
    bool operator<(const mystring &other) const
    {
        int min_len = (len < other.len) ? len : other.len;
        for (int i = 0; i < min_len; i++) {
            if (ch[i] < other.ch[i]) return true;
            if (ch[i] > other.ch[i]) return false;
        }
        // If all compared characters are equal, shorter string is smaller
        return len < other.len;
    }
    
    // Equality operator
    bool operator==(const mystring &other) const
    {
        if (len != other.len) return false;
        for (int i = 0; i < len; i++) {
            if (ch[i] != other.ch[i]) return false;
        }
        return true;
    }
    
    // Concatenation operator
    mystring operator+(const mystring &other) const
    {
        mystring result;
        result.len = len + other.len;
        result.ch = new char[result.len];
        
        // Copy first string
        for (int i = 0; i < len; i++) {
            result.ch[i] = ch[i];
        }
        // Copy second string
        for (int i = 0; i < other.len; i++) {
            result.ch[len + i] = other.ch[i];
        }
        
        return result;
    }
    
    // In-place concatenation operator
    mystring& operator+=(const mystring &other)
    {
        // Create new buffer with combined length
        char *new_ch = new char[len + other.len];
        
        // Copy existing string
        for (int i = 0; i < len; i++) {
            new_ch[i] = ch[i];
        }
        // Copy other string
        for (int i = 0; i < other.len; i++) {
            new_ch[len + i] = other.ch[i];
        }
        
        // Clean up old buffer
        delete[] ch;
        
        // Update members
        ch = new_ch;
        len = len + other.len;
        
        return *this;
    }
    
    // ADD function to concatenate another mystring
    void ADD(const mystring &other)
    {
        *this += other;
    }
    
    // Output function
    void out() const
    {
        for (int i = 0; i < len; i++) {
            cout << ch[i];
        }
    }
    
    // Get length function
    int get_len() const
    {
        return len;
    }
    
    // Substring function
    mystring substr(int pos, int length) const
    {
        // Handle edge cases
        if (pos >= len || pos < 0 || length <= 0) {
            return mystring(); // Return empty string
        }
        
        // Adjust length if it goes beyond string end
        if (pos + length > len) {
            length = len - pos;
        }
        
        mystring result;
        result.len = length;
        result.ch = new char[length];
        
        for (int i = 0; i < length; i++) {
            result.ch[i] = ch[pos + i];
        }
        
        return result;
    }
    
    // Insert function
    void insert(int pos, const mystring &str)
    {
        // Handle invalid positions
        if (pos < 0) pos = 0;
        if (pos > len) pos = len;
        
        // Create new buffer with increased length
        int new_len = len + str.len;
        char *new_ch = new char[new_len];
        
        // Copy part before insertion point
        for (int i = 0; i < pos; i++) {
            new_ch[i] = ch[i];
        }
        
        // Copy inserted string
        for (int i = 0; i < str.len; i++) {
            new_ch[pos + i] = str.ch[i];
        }
        
        // Copy part after insertion point
        for (int i = 0; i < len - pos; i++) {
            new_ch[pos + str.len + i] = ch[pos + i];
        }
        
        // Clean up old buffer
        delete[] ch;
        
        // Update members
        ch = new_ch;
        len = new_len;
    }
    
    // Erase function
    void erase(int pos, int length)
    {
        // Handle invalid positions
        if (pos < 0) pos = 0;
        if (pos >= len) return; // Nothing to erase
        
        // Adjust length if it goes beyond string end
        if (pos + length > len) {
            length = len - pos;
        }
        
        // Create new buffer with reduced length
        int new_len = len - length;
        if (new_len == 0) {
            // Erasing entire string
            delete[] ch;
            ch = nullptr;
            len = 0;
            return;
        }
        
        char *new_ch = new char[new_len];
        
        // Copy part before erased section
        for (int i = 0; i < pos; i++) {
            new_ch[i] = ch[i];
        }
        
        // Copy part after erased section
        for (int i = 0; i < new_len - pos; i++) {
            new_ch[pos + i] = ch[pos + length + i];
        }
        
        // Clean up old buffer
        delete[] ch;
        
        // Update members
        ch = new_ch;
        len = new_len;
    }
};

string str_in1, str_in2;
int n, id;
int main()
{
    cin >> id;
    if (id == 1)
    {
        mystring str1(100,'a');
        str1.out(); puts("");
        // cout << str1 << endl;
    }
    else if (id == 2)
    {
        cin >> str_in1;
        mystring str2 = str_in1;
        cin >> n;
        for (int i = 0, x; i < n; ++ i)
        {
            cin >> x;
            cout << str2[x] << endl;
        }
    }
    else if (id == 3)
    {
        cin >> str_in1 >> str_in2;
        mystring str2 = str_in1;
        mystring str3 = str_in2;
        cout << (int)(str2 < str3) << endl;
    }
    else if (id == 4)
    {
        cin >> str_in1 >> str_in2;
        mystring str2 = str_in1;
        mystring str3 = str_in2;
        str2.ADD(str3);
        str2.out(); puts("");
        // cout << str2 << endl;
    }
    else
    {
        cin >> str_in1 >> str_in2;
        mystring str2 = str_in1;
        mystring str3 = str_in2;
        cin >> n;
        for (int i = 0, x; i < n; ++ i)
        {
            cin >> x;
            cout << str3[x] << endl;
        }
        cout << str2.get_len() << " " << str3.get_len() << endl;
        cout << (int)(str2 < str3) << endl;
        str2.ADD(str3);
        str2.out(); puts("");
        // cout << str2 << endl;
        cout << str2.get_len() << endl;
    }
    return 0;
}