#ifndef _GROUPMODEL_H_
#define _GROUPMODEL_H_

#include "group.hpp"
#include <string>
#include <vector>
using namespace std;

//  维护群组信息的操作接口方法
class GroupModel
{
public:
    //  创建群聊
    bool creatGroup(Group &group);
    //  加入群聊
    void addGroup(int userid,int groupid,string role);
    //  查询用户所在群信息
    vector<Group>  queryGroups(int userid);
    //  根据指定groudid查询群聊用户id列表，除userid，主要用户群聊业务給群组其他成员群发消息
    vector<int> queryGroupUsers(int userid,int groupid);
};


  

#endif 