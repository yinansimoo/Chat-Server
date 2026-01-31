# Chat-Server
这是一个基于 C++ 的聊天服务器项目，支持跨服务器聊天。  

编译方式：  
cd build  
rm -fr *  
cmake ..  
make  

所需环境:  
json开发库  
muduo和boost网络库  
redis环境  
mysql数据库环境  
nginx的tcp模块  

该项目解耦了网络层和业务层代码，业务层中使用了mysql表的操作接口  
使用nginx的tcp负载均衡，监听端口号8000,配置了本地6000和6002两个不同端口号的服务器  
使用redis作为订阅-发布消息队列  
业务功能：注册账号，登录账号，注销账号，添加好友，创建群聊，加入群聊，一对一聊天和群聊聊天等业务。  
  
include文件中，db包含数据库连接，更新和查询等操作接口的头文件  
model包含数据库表user和group的ORM类，及user,friend,group,offlinemessage各表操作接口的头文件  
redis包含消息队列的连接，订阅，发布，取消订阅及向业务层上传消息回调接口的头文件  
public.hpp为server,client的公共头文件，枚举了各业务的msgid  
chatserver是服务器的头文件，chatservice为业务头文件  
