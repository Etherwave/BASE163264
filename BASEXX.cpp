//
// Created by amzing on 2021/7/11.
//

#include "BASEXX.h"

//--------------------------------------------BASE16_START-------------------------------------------------------
BASE16::BASE16() {}

BASE16::~BASE16() {}

string BASE16::encode(const char *s, unsigned long long len)
{
    // BASE16是4位一取，一个字节有8位，所以说一个字节拆成了两个字节，数据的最小单位为字节，所以一定可以成功加密
    string ans="";
    unsigned long long unll_len = len;
    // string 的最大长度除以2，得到最多能处理多少个字符
    const unsigned long long max_size = ans.max_size()>>1;
    const int t4 = 0x0F;
    for(unsigned long long i=0;i<unll_len&&i<max_size;i++)
    {
        ans+=table_int2char[(s[i]>>4)&t4];
        ans+=table_int2char[s[i]&t4];
    }
    return ans;
}

string BASE16::encode(const string &s)
{
    string ans="";
    unsigned long long unll_len = s.size();
    const unsigned long long max_size = ans.max_size()>>1;
    const int t4 = 0x0F;
    for(unsigned long long i=0;i<unll_len&&i<max_size;i++)
    {
        ans+=table_int2char[(s[i]>>4)&t4];
        ans+=table_int2char[s[i]&t4];
    }
    return ans;
}

string BASE16::decode(const char *s, unsigned long long len)
{
    string ans="";
    // string 的最大长度乘以2，得到最多能处理多少个字符
    const unsigned long long max_size = ans.max_size()<<1;
    unsigned long long p=0;
    // 取两个字符，拼成一个即可
    while(p+1<len&&p<max_size)
    {
        ans+=char((table_char2int[s[p]]<<4)+table_char2int[s[p+1]]);
        p+=2;
    }
    return ans;
}

string BASE16::decode(const string &s)
{
    string ans="";
    const unsigned long long max_size = ans.max_size()<<1;
    unsigned long long p=0;
    while(p+1<s.size()&&p<max_size)
    {
        ans+=char((table_char2int[s[p]]<<4)+table_char2int[s[p+1]]);
        p+=2;
    }
    return ans;
}

//--------------------------------------------BASE16_END-------------------------------------------------------

//--------------------------------------------BASE32_START-------------------------------------------------------
BASE32::BASE32() {}

BASE32::~BASE32() {}

string BASE32::encode(const char *s, unsigned long long len)
{
    // BASE32是5位一取，一个字节有8位，5和8的最小公倍数是40，所以5个字节组成一个完整的加密，加密结果为8个字节
    string ans="";
    const unsigned long long max_size = ans.max_size()/8*5;
    const int t5 = 0x1F;
    unsigned long long p=0;
    unsigned long long t;
    // 每次取5个字符，5*8=40，编码一次
    while(p+4<len&&p<max_size)
    {
        t=0;
        for(int i=0;i!=5;i++)
        {
            t<<=8;
            t+=(int(s[p+i])&0x000000FF);
        }

        for(int i=7;i>=0;i--)
            ans+=table_int2char[(t>>(i*5))&t5];

        p+=5;
    }
    // 剩余的bit数量不是5的倍数的话，就补齐到5的倍数
    if(p<len&&p<max_size)
    {
        t=0;
        int cnt=0;
        while(p<len)
        {
            t<<=8;
            t+=(int(s[p])&0x000000FF);
            p++;cnt++;
        }
        t<<=(5-((cnt*8)%5));
        int cnt2=cnt*8/5+(cnt*8%5>0?1:0);
        for(int i=1;i<9;i++)
        {
            if(i<=cnt2)ans+=table_int2char[(t>>((cnt2-i)*5))&t5];
            else ans+="=";
        }
    }

    return ans;
}

string BASE32::encode(const string &s)
{
    string ans="";
    const unsigned long long max_size = ans.max_size()/8*5;
    const int t5 = 0x1F;
    unsigned long long p=0;
    unsigned long long t;
    while(p+4<s.size()&&p<max_size)
    {
        t=0;
        for(int i=0;i!=5;i++)
        {
            t<<=8;
            t+=(int(s[p+i])&0x000000FF);
        }

        for(int i=7;i>=0;i--)
            ans+=table_int2char[(t>>(i*5))&t5];

        p+=5;
    }

    if(p<s.size()&&p<max_size)
    {
        t=0;
        int cnt=0;
        while(p<s.size())
        {
            t<<=8;
            t+=(int(s[p])&0x000000FF);
            p++;cnt++;
        }
        t<<=(5-((cnt*8)%5));
        int cnt2=cnt*8/5+(cnt*8%5>0?1:0);
        for(int i=1;i<9;i++)
        {
            if(i<=cnt2)ans+=table_int2char[(t>>((cnt2-i)*5))&t5];
            else ans+="=";
        }
    }

    return ans;
}

string BASE32::decode(const char *s, unsigned long long len)
{
    string ans="";
    unsigned long long true_len = len;
    while(s[true_len-1]=='=')true_len--;
    unsigned long long max_size=ans.max_size()/5*8;
    unsigned long long p=0;
    unsigned long long t=0;
    const int t8=0xFF;
    // 每次取8个字符，8*5=40，解码一次
    while(p+7<true_len&&p<max_size)
    {
        t = 0;
        for(int i=0;i!=8;i++)
        {
            t<<=5;
            t+=table_char2int[s[p+i]];
        }

        for(int i=4;i>=0;i--)
            ans+=char(t>>(i*8)&t8);

        p+=8;
    }
    // 剩余的bit数量，不是8的倍数就补齐到8的倍数，翻译出来
    if(p<true_len&&p<max_size)
    {
        t=0;
        int cnt=0;
        while(p<true_len)
        {
            t<<=5;
            t+=table_char2int[s[p]];
            p++;cnt++;
        }
        bool flag = false;
        int cnt2=0;
        int cnt3=(cnt*5)%8;
        for(int i=0;i!=cnt3;i++)
        {
            if((t>>i)&1)
            {
                flag = true;
                break;
            }
        }
        if(flag)
        {
            t<<=(8-((cnt*5)%8));
            cnt2 = cnt*5/8+(cnt*5%8>0?1:0);
        }
        else
        {
            t>>=cnt3;
            cnt2 = cnt*5/8;
        }

        for(int i=cnt2-1;i>=0;i--)
            ans+=char(t>>(i*8)&t8);
    }

    return ans;
}

string BASE32::decode(const string &s)
{
    string ans="";
    unsigned long long true_len = s.size();
    while(s[true_len-1]=='=')true_len--;
    unsigned long long max_size=ans.max_size()/5*8;
    unsigned long long p=0;
    unsigned long long t=0;
    const int t8=0xFF;
    while(p+7<true_len&&p<max_size)
    {
        t = 0;
        for(int i=0;i!=8;i++)
        {
            t<<=5;
            t+=table_char2int[s[p+i]];
        }

        for(int i=4;i>=0;i--)
            ans+=char(t>>(i*8)&t8);

        p+=8;
    }

    if(p<true_len&&p<max_size)
    {
        t=0;
        int cnt=0;
        while(p<true_len)
        {
            t<<=5;
            t+=table_char2int[s[p]];
            p++;cnt++;
        }
        bool flag = false;
        int cnt2=0;
        int cnt3=(cnt*5)%8;
        for(int i=0;i!=cnt3;i++)
        {
            if((t>>i)&1)
            {
                flag = true;
                break;
            }
        }
        if(flag)
        {
            t<<=(8-((cnt*5)%8));
            cnt2 = cnt*5/8+(cnt*5%8>0?1:0);
        }
        else
        {
            t>>=cnt3;
            cnt2 = cnt*5/8;
        }

        for(int i=cnt2-1;i>=0;i--)
            ans+=char(t>>(i*8)&t8);
    }

    return ans;
}


//--------------------------------------------BASE32_END-------------------------------------------------------

//--------------------------------------------BASE64_START-------------------------------------------------------

BASE64::BASE64() {}

BASE64::~BASE64() {}

string BASE64::encode(const char *s, unsigned long long len)
{
    // BASE64和BASE32的思路一致，只不过BASE64是6位一取，一个字节8位，6，8的最小公倍数是24
    // 还有就是len%3==1时，最后结果补两个=，len%3==2时，最后结果补一个=
    string ans="";
    unsigned long long max_size = ans.max_size()/4*3;
    unsigned long long p=0;
    unsigned long long t=0;
    const int t6=0x3F;

    // 每次取3个字符，3*8=24，编码一次
    while(p+2<len&&p<max_size)
    {
        t = 0;
        for(int i=0;i!=3;i++)
        {
            t<<=8;
            // 注意这里不能直接加，如果是中文的话，那么一个char的8个bit的最高的bit是1，转换到unll时，会在高位不断补1，导致数值错误
            // 但是在处理ASCLL的时候，由于最高位不是1，所以不会错误。
            t+=(int(s[p+i])&0x000000FF);
        }

        for(int i=3;i>=0;i--)
            ans+=table_int2char[(t>>(i*6))&t6];

        p+=3;
    }
    // 剩余的bit如果不是6的倍数，补齐到6的倍数
    if(p<len&&p<max_size)
    {
        t=0;
        int cnt=0;
        while(p<len)
        {
            t<<=8;
            t+=(int(s[p])&0x000000FF);
            p++;cnt++;
        }
        t<<=(6-((cnt*8)%6));
        int cnt2=cnt*8/6+(cnt*8%6>0?1:0);
        for(int i=1;i<=4;i++)
        {
            if(i<=cnt2)ans+=table_int2char[(t>>((cnt2-i)*6))&t6];
            else ans+="=";
        }
    }

    return ans;
}

string BASE64::encode(const string &s)
{
    string ans="";
    unsigned long long max_size = ans.max_size()/4*3;
    unsigned long long p=0;
    unsigned long long t=0;
    const int t6=0x3F;
    while(p+2<s.size()&&p<max_size)
    {
        t = 0;
        for(int i=0;i!=3;i++)
        {
            t<<=8;
            t+=(int(s[p+i])&0x000000FF);
        }

        for(int i=3;i>=0;i--)
            ans+=table_int2char[(t>>(i*6))&t6];

        p+=3;
    }

    if(p<s.size()&&p<max_size)
    {
        t=0;
        int cnt=0;
        while(p<s.size())
        {
            t<<=8;
            t+=(int(s[p])&0x000000FF);
            p++;cnt++;
        }
        t<<=(6-((cnt*8)%6));
        int cnt2=cnt*8/6+(cnt*8%6>0?1:0);
        for(int i=1;i<=4;i++)
        {
            if(i<=cnt2)ans+=table_int2char[(t>>((cnt2-i)*6))&t6];
            else ans+="=";
        }
    }

    return ans;
}

string BASE64::decode(const char *s, unsigned long long len)
{
    string ans="";
    unsigned long long true_len = len;
    while(s[true_len-1]=='=')true_len--;
    unsigned long long max_size=ans.max_size()/3*4;
    unsigned long long p=0;
    unsigned long long t=0;
    const int t8=0xFF;
    // 每次取4个字符，4*6=24，解码一次
    while(p+3<true_len&&p<max_size)
    {
        t = 0;
        for(int i=0;i!=4;i++)
        {
            t<<=6;
            t+=table_char2int[s[p+i]];
        }

        for(int i=2;i>=0;i--)
            ans+=char(t>>(i*8)&t8);

        p+=4;
    }
    // 剩余的bit数量，不是8的倍数就补齐到8的倍数，翻译出来
    if(p<true_len&&p<max_size)
    {
        t=0;
        int cnt=0;
        while(p<true_len)
        {
            t<<=6;
            t+=table_char2int[s[p]];
            p++;cnt++;
        }
        bool flag = false;
        int cnt2=0;
        int cnt3=(cnt*6)%8;
        for(int i=0;i!=cnt3;i++)
        {
            if((t>>i)&1)
            {
                flag = true;
                break;
            }
        }
        if(flag)
        {
            t<<=(8-((cnt*6)%8));
            cnt2 = cnt*6/8+(cnt*6%8>0?1:0);
        }
        else
        {
            t>>=cnt3;
            cnt2 = cnt*6/8;
        }

        for(int i=cnt2-1;i>=0;i--)
            ans+=char(t>>(i*8)&t8);
    }

    return ans;
}

string BASE64::decode(const string &s)
{
    string ans="";
    unsigned long long true_len = s.size();
    while(s[true_len-1]=='=')true_len--;
    unsigned long long max_size=ans.max_size()/3*4;
    unsigned long long p=0;
    unsigned long long t=0;
    const int t8=0xFF;
    while(p+3<true_len&&p<max_size)
    {
        t = 0;
        for(int i=0;i!=4;i++)
        {
            t<<=6;
            t+=table_char2int[s[p+i]];
        }

        for(int i=2;i>=0;i--)
            ans+=char(t>>(i*8)&t8);

        p+=4;
    }

    if(p<true_len&&p<max_size)
    {
        t=0;
        int cnt=0;
        while(p<true_len)
        {
            t<<=6;
            t+=table_char2int[s[p]];
            p++;cnt++;
        }
        bool flag = false;
        int cnt2=0;
        int cnt3=(cnt*6)%8;
        for(int i=0;i!=cnt3;i++)
        {
            if((t>>i)&1)
            {
                flag = true;
                break;
            }
        }
        if(flag)
        {
            t<<=(8-((cnt*6)%8));
            cnt2 = cnt*6/8+(cnt*6%8>0?1:0);
        }
        else
        {
            t>>=cnt3;
            cnt2 = cnt*6/8;
        }

        for(int i=cnt2-1;i>=0;i--)
            ans+=char(t>>(i*8)&t8);
    }

    return ans;
}

//--------------------------------------------BASE64_END-------------------------------------------------------