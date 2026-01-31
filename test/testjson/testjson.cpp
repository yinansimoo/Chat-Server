#include"json.hpp"
using json = nlohmann::json;

#include<iostream>
#include<vector>
#include<map>
#include<string>

using namespace std;

string func()
{   
    json js;
    js["msg_type"] = 2;
    js["from"] = "zhang san";
    js["to"] = "li si";
    js["msg"] = "hello,what are you doing now?";

    string sendBuf = js.dump();
    return sendBuf;
}

void fun1()
{
    json js;
    js["id"] = {1,2,3,4,5};
    js["name"] = "zhang san";
    js["msg"]["zhang san"] = "hello world";
    js["msg"]["liu tao"] = "hello china,hello";
    //js["msg"] = {{"zhang san","hello world"},{"liu tao","hello china"}};
    cout  << js << endl;
}

void fun2()
{
    json js;

    vector<int> vec;
    vec.push_back(1);
    vec.push_back(3);
    vec.push_back(6);

    js["list"] = vec;

    map<int ,string> m;
    m.insert({vec[1]-1,"晃晃"});
    m.insert({3,"朗朗"});
    m.insert({6,"命名"});

    js["path"] = m;

    string sendBuf = js.dump(); //json数据对象 --> 序列化 json 字符串

    cout << sendBuf.c_str() << endl;
}

//数据的返序列化
json func1(string sendBuf)
{
    return json::parse(sendBuf);
}

string func2()
{
    json js;
    js["id"] = {1,2,3,4,5};
    js["name"] = "zhang san";
    js["msg"]["zhang san"] = "hello world";
    js["msg"]["liu tao"] = "hello china,hello";
    //js["msg"] = {{"zhang san","hello world"},{"liu tao","hello china"}};
    //cout  << js << endl;
    return js.dump();
}

string func3()
{
    json js;

    vector<int> vec;
    vec.push_back(1);
    vec.push_back(3);
    vec.push_back(6);

    js["list"] = vec;

    map<int ,string> m;
    m.insert({vec[1]-1,"晃晃"});
    m.insert({3,"朗朗"});
    m.insert({6,"命名"});

    js["path"] = m;

    return js.dump();
}

int main()
{
    string sendBuf = func3();
    json jsbuf  =  func1(sendBuf);
    vector<int> ar = jsbuf["list"];
    for(int &i :ar)
    cout << i << "  ";
    cout << endl;

    map<int,string>ma = jsbuf["path"];
    for(auto& i:ma)
    cout << i.second << "  ";
    cout << endl;

    return 0;
    }
