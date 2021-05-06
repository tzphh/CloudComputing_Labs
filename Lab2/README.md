# Lab 2: Your Own HTTP Server
服务器代码为httpserver.cc，在终端使用make编译

运行命令为./httpserver --ip --port。

GET请求（包含DELETE,PUT）客户端为GETclient.c，用gcc编译生成可执行文件为get（gcc GETclient.c -o get），运行命令为./get ip port num。num为请求的连接数。

POST请求客户端为POSTclient.c，用gcc编译生成可执行文件为post（gcc POSTclient.c -o post），运行命令为./post ip port num。num为请求的连接数。

若运行时出现文件数过多的报错，是因为句柄开太多的缘故。输入ulimit -n 8192对最大文件数进行修改。