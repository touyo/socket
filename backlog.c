#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>

static bool stop = false;

static viod handel_term(int sig)
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
