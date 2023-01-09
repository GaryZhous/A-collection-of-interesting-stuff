#include <iostream>
#include <unordered_map>
using namespace std;

class Name{
public:
    Name(string const& xing,string const& ming):m_xing(xing),m_ming(ming){}
    bool operator==(Name const& that)const{
        return m_xing==that.m_xing && m_ming==that.m_ming;
    }
private:
    string m_xing;
    string m_ming;
    friend ostream& operator<<(ostream& os,Name const& name);
    friend class NameHash;
//  friend class NameEqual;
};
ostream& operator<<(ostream& os, Name const& name){
    return os << name.m_xing << name.m_ming;
}

class NameHash{
public:
    size_t operator()(Name const& name)const{
        hash<string> hs;
        return hs(name.m_xing)^(hs(name.m_ming)<<1);
    }
};

class NameEqual{
public:
    bool operator()(Name const& a, Name const& b)const{
        return a.m_xing==b.m_xing && a.m_ming==b.m_ming;
    }
};*/
int main(){
    unordered_map<Name,int,NameHash/*,NameEqual*/> um{
        {{"zhang","san"},88},{{"li","si"},70},{{"wang","wu"},66},
        {{"ma","liu"},90},{{"tian","qi"},85}
    };

    for(auto const& p : um)
        cout << p.first << ':' << p.second << endl;
/*    unordered_map<string,int> um{
        {"zhangsan",88},{"lisi",70},{"wangwu",66},{"maliu",90},{"tianqi",85}
    };
    cout << um["lisi"] << endl;
    hash<string> hs;
    for(auto const& p : um)
        cout << p.first << '(' << hs(p.first)  << ')' << ':' << p.second << endl;*/
    return 0;
}
