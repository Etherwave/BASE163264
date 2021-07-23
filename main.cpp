#include "BASEXX.h"
using namespace std;



int main() {
    string a="昂首阿萨德好你说的话 daaspdj p22";
    string ans = "5piC6aaW6Zi/6JCo5b635aW95L2g6K+055qE6K+dIGRhYXNwZGogcDIy";

    ans = BASE16::encode(a.c_str(), a.size());
    cout<<ans<<endl;
    ans = BASE16::decode(ans.c_str(), ans.size());
    cout<<ans<<endl;

    ans = BASE16::encode(a);
    cout<<ans<<endl;
    ans = BASE16::decode(ans);
    cout<<ans<<endl;

    ans = BASE32::encode(a.c_str(), a.size());
    cout<<ans<<endl;
    ans = BASE32::decode(ans.c_str(), ans.size());
    cout<<ans<<endl;

    ans = BASE32::encode(a);
    cout<<ans<<endl;
    ans = BASE32::decode(ans);
    cout<<ans<<endl;

    ans = BASE64::encode(a.c_str(), a.size());
    cout<<ans<<endl;
    ans = BASE64::decode(ans.c_str(), ans.size());
    cout<<ans<<endl;

    ans = BASE64::encode(a);
    cout<<ans<<endl;
    ans = BASE64::decode(ans);
    cout<<ans<<endl;

    return 0;
}

