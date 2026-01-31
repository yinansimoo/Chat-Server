#include "friendmodel.hpp"
#include "db.h"

//  增加好友
void FriendModel::insert(int userid, int friendid)
{
    //  组装sql语句
    char sql[1024] = {0};
    sprintf(sql, "insert into friend values(%d,%d)",
            userid, friendid);

    MySQL mysql;
    if (mysql.connect())
    {
        mysql.update(sql);
    }
}

//  返回用户好友列表
vector<User> FriendModel::query(int userid)
{
    vector<User> vec;
    char sql[1024] = {0};
    sprintf(sql, "select u.id,u.name,u.state from user as u inner join friend as f on f.friend_id = u.id where f.user_id=%d",
            userid);

    MySQL mysql;
    if (mysql.connect())
    {
        MYSQL_RES *res = mysql.query(sql);
        if (res != nullptr)
        {
            MYSQL_ROW row;
            while ((row = mysql_fetch_row(res)) != nullptr)
            {
                User user;
                user.setId(atoi(row[0]));
                user.setName(row[1]);
                user.setState(row[2]);
                vec.push_back(user);
            }
            mysql_free_result(res);
            return vec;
        }
    }

    return vec;
}