# Chat-Server

这是一个基于 C++ 开发的跨服务器聊天服务器项目，支持注册、登录、好友互动、群聊等核心社交功能，采用分层架构解耦网络与业务逻辑。

## 编译步骤
进入构建目录
cd build

清理旧构建文件
rm -fr *

生成Makefile
cmake ..

编译项目
make

## 依赖环境
运行项目前需确保以下环境已安装配置：  
基础库：json 开发库、boost 网络库  
网络框架：muduo（高性能 C++ 网络库）  
中间件：  
Redis（实现订阅 - 发布消息队列）  
MySQL（存储用户 / 好友 / 群聊数据）  
负载均衡：Nginx（启用 TCP 模块，实现多服务器负载分发）  
## 技术架构 
分层设计  
项目采用「网络层 + 业务层」解耦架构：  
网络层：基于 muduo 实现 TCP 通信，处理连接管理、数据收发；  
业务层：通过 MySQL 操作接口、Redis 消息队列接口实现业务逻辑，依赖 Nginx 的 TCP 负载均衡（监听端口 8000，分发请求至本地 6000、6002 端口的后端服务器）。  
## 业务功能 
支持的核心功能包括：  
用户管理：注册账号、登录账号、注销账号  
社交互动：添加好友、创建群聊、加入群聊  
消息通信：一对一聊天、群聊聊天  
## 代码结构（include
include 目录下的核心头文件分工：  
db/：封装 MySQL 的连接、新增 / 查询 / 更新等操作接口  
model/：定义 user、friend、group、offlinemessage 等表的 ORM 类，提供数据操作接口  
redis/：封装 Redis 的连接、订阅 / 发布消息、回调等接口  
public.hpp：server 与 client 的公共头文件，定义各业务的消息类型 ID（msgid）  
chatserver.hpp：服务器核心逻辑头文件  
chatservice.hpp：业务层核心逻辑头文件  
