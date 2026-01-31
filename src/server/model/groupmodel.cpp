#include "groupmodel.hpp"
#include "db.h"

//  创建群聊
bool GroupModel::creatGroup(Group &group)
{
    char sql[1024] = {0};
    sprintf(sql, "insert into allgroup(groupname,groupdesc) values('%s','%s')",
            group.getName().c_str(), group.getDesc().c_str());

    MySQL mysql;
    if (mysql.connect())
    {
        if (mysql.update(sql))
        {
            group.setId(mysql_insert_id(mysql.getConnection()));
            return true;
        }
    }

    return false;
}

//  加入群聊
void GroupModel::addGroup(int userid, int groupid, string role)
{
    char sql[1024] = {0};
    sprintf(sql, "insert into groupuser values(%d,%d,'%s')",
            groupid, userid, role.c_str());

    MySQL mysql;
    if (mysql.connect())
    {
        mysql.update(sql);
    }
}

//  查询用户所在群信息
vector<Group> GroupModel::queryGroups(int userid)
{
    /*
    1`  根据userid在groupuser表中查询出该用户所属的群聊消息
    2`  根据返回的群聊消息，查询属于该群聊的所有用户userid，并和user表多表联合查询，查出用户的详细信息
    */
    char sql[1024] = {0};
    sprintf(sql, "select ag.id,ag.groupname,ag.groupdesc from allgroup as ag inner join \
        groupuser as gu on ag.id=gu.groupid where gu.userid=%d",
            userid);

    vector<Group> groupVec;

    MySQL mysql;
    if (mysql.connect())
    {
        MYSQL_RES *res = mysql.query(sql);
        if (res != nullptr)
        {
            MYSQL_ROW row;
            while ((row = mysql_fetch_row(res)) != nullptr)
            {
                Group group;
                group.setId(atoi(row[0]));
                group.setName(row[1]);
                group.setDesc(row[2]);
                groupVec.push_back(group);
            }
            mysql_free_result(res);
        }
    }

    //  查询群聊的用户信息
    for (Group &group : groupVec)
    {
        sprintf(sql, "select u.id,u.name,u.state,gu.grouprole from user as u inner join \
            groupuser as gu on gu.userid=u.id where gu.groupid=%d",
                group.getId());

        MYSQL_RES *res = mysql.query(sql);
        if (res != nullptr)
        {
            MYSQL_ROW row;
            while ((row = mysql_fetch_row(res)) != nullptr)
            {
                GroupUser user;
                user.setId(atoi(row[0]));
                user.setName(row[1]);
                user.setState(row[2]);
                user.setRole(row[3]);
                group.getUsers().push_back(user);
            }
            mysql_free_result(res);
        }
    }
    return groupVec;
}

//  根据指定groudid查询群聊用户id列表，除userid，主要用户群聊业务給群组其他成员群发消息
vector<int> GroupModel::queryGroupUsers(int userid, int groupid)
{
    char sql[1024] ={0};
    sprintf(sql,"select userid from groupuser where groupid=%d and userid!=%d",
    groupid,userid);

    vector<int>vec;

    MySQL mysql;
    if(mysql.connect())
    {
        MYSQL_RES* res = mysql.query(sql);
        if(res != nullptr)
        {
            MYSQL_ROW row;
            while((row=mysql_fetch_row(res))!= nullptr)
            {
                int id=atoi(row[0]);
                vec.push_back(id);
            }
            mysql_free_result(res);
        }
    }
    return vec;
}