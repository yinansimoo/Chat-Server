cmake_minimum_required(VERSION 3.10)
project(main)


#  gcc -o server -o/-g  muduo_server.cpp -l/usr/include -L/usr/lib -lmuduo_net -lmuduo_base -lpthread  
#  server 为可执行文件，*.a(静态)  *.so(动态)
#  muduo_server.cpp 为需要编译的源文件
#  -l/usr/include 为头文件搜索路径 (usr/inculude是默认路径，自动搜索
#  -L/usr/lib 为库文件搜索路径  (usr/lib是默认路径，自动搜索
#  -l muduo_net等 为需要连接的库

#  配置编译选项
set(CMAKE_CXX ${CMAKE_CXX} -g)

#  配置头文件搜索路径
# include_directories()

#  配置库文件搜索路径
# link_directories()

#  设置需要编译的源文件列表
set(SRC_LIST ./muduo_server.cpp)

#  设置可执行文件存储路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

#  把 . 指定路径下的所有源文件名字放入变量名 SRC_LIST 里面
# aux_source_directory(. SRC_LIST)

#  表示生成可执行文件 server,由SRC_LIST 变量所定义的源文件编译而来
add_executable(server ${SRC_LIST}) 

#  表示server 这个目标程序，需要连接muduo_net muduo_base pthread这三个库文件
target_link_libraries(server muduo_net muduo_base pthread)


