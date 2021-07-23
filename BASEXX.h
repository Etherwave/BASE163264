//
// Created by amzing on 2021/7/11.
//

#include <iostream>
#include <string>
#include <string.h>

using namespace std;

#ifndef BASE163264_BASEXX_H
#define BASE163264_BASEXX_H

class BASE16
{
public:
    constexpr static const char table_int2char[]="0123456789ABCDEF";
    constexpr static const int table_char2int[]=
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
             0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,3,4,5,6,7,8,9,0,0,0,0,0,0,0,10,11,12,13,14,15};
    BASE16();
    ~BASE16();
    static string encode(const char *s, unsigned long long len);
    static string decode(const char *s, unsigned long long len);
    static string encode(const string &s);
    static string decode(const string &s);
};

class BASE32
{
public:
    constexpr static const char table_int2char[]="ABCDEFGHIJKLMNOPQRSTUVWXYZ234567";
    constexpr static const int table_char2int[]=
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
             ,26,27,28,29,30,31,0,0,0,0,0,0,0,0,0,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25};
    BASE32();
    ~BASE32();
    static string encode(const char *s, unsigned long long len);
    static string decode(const char *s, unsigned long long len);
    static string encode(const string &s);
    static string decode(const string &s);
};

class BASE64
{
public:
    constexpr static const char table_int2char[]="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    constexpr static const int table_char2int[]=
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,62,0,0,0,63,52,53,
             54,55,56,57,58,59,60,61,0,0,0,0,0,0,0,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,
             0,0,0,0,0,0,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51};
    BASE64();
    ~BASE64();
    static string encode(const char *s, unsigned long long len);
    static string decode(const char *s, unsigned long long len);
    static string encode(const string &s);
    static string decode(const string &s);
};

#endif //BASE163264_BASEXX_H
