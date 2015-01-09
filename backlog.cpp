#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <sys/un.h>

static bool stop = false;

static void handle_term(int sig)
{
	stop = true;
}

int main( int argc, char* argv[])
{
	signal(	SIGTERM, handle_term);

	if(argc <= 3)
	{
		printf("usage: %s ip_address port_number backlog\n", basename(argv[0]));
		return 1;
	}
	const char* ip = argv[1];
	int port = atoi(argv[2]);
	int backlog = atoi(argv[3]);
	//socket(int domain, int type, int protocol)
	int sock = socket(PF_INET, SOCK_STREAM, 0);
	assert(sock >= 0);

	struct sockaddr_in address;
	//extern void bzero（void *s, int n）;   
	//参数说明：s 要置零的数据的起始地址； n 要置零的数据字节个数。
	//用法：#include <string.h>              
	//功能：置字节字符串s的前n个字节为零且包括‘\0’。
	bzero( &address, sizeof(address));
	address.sin_family = AF_INET;
	//inet_pton把点分ipv4或ipv6地址转换为二进制地址。第一个参数是类型，AF_INET表示ipv4地址。第二个source，第三个destination
	inet_pton(AF_INET, ip, &address.sin_addr);
	//htons host to network short, 转换端口号
	address.sin_port = htons(port);

	int ret = bind(sock, (struct sockaddr*)&address, sizeof(address));
	assert(ret != -1);

	ret = listen(sock, backlog);
	assert(ret != -1);

	while(!stop)
	{
		sleep(1);
	}
	close(sock);
	return 0;
}