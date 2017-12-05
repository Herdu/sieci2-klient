#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstdio>
#include <cstdlib>

using namespace std;
int main(int argc, char **argv) {
    sockaddr_in addr;
    addr.sin_family=AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    uint16_t hostPort =1333;
    uint16_t hostportReverse = htons(hostPort);
    addr.sin_port = hostportReverse;
    int fd, nfd;

    if(((fd=socket(AF_INET, SOCK_STREAM,0))==-1)){
        perror("Blad otworzenie socketu\n");
        exit(1);
    }
    const int one = 1;
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one));
    if(bind(fd, (struct sockaddr*)&addr, sizeof(addr))==-1)
    {
        perror("problem zwiazania polaczenia - zajety port!\n");
    };
    if(listen(fd, 10)==-1)
    {
        perror("problem nasluchiwania\n");
    };
    socklen_t len;
    char ipstr[INET_ADDRSTRLEN];
    char buf[255] = "Witaj na serwerze!\n";
    char buf2[255];

    while(1) {
        if ((nfd = accept(fd, (struct sockaddr *) &addr, &len)) == -1 ) {
            perror("problem nawiazania polaczenia\n");
        };
	int size;
	while(1)
	{
		if((size=read(nfd, buf2, sizeof(buf)-1))==-1)
		{
			perror("blad odczytu od klienta\n");
		}
		else
		{
			if(write(1, "Odebrano wiadomosc: ", 21)==-1)
				perror("blad wypisania na ekran\n");
		};
		if(write(1, buf2,size)==-1)
			perror("blad wypisania na ekran\n");

   		if(write(nfd, buf, sizeof(buf) - 1)==-1)
			perror("blad wypisania na ekran\n");

		if(write(1, "od ", 3)==-1)
			perror("blad wypisania na ekran\n");
		struct sockaddr_in *s = (struct sockaddr_in *) &addr;
        	int port = ntohs(s->sin_port);
        	inet_ntop(AF_INET, &s->sin_addr, ipstr, sizeof ipstr);
        	printf("%s %d\n", ipstr, port);
        };
        shutdown(nfd, SHUT_RDWR);
    }
}
