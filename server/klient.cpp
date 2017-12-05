#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

using namespace std;
int main(int argc, char **argv) {
    sockaddr_in addr;
    int port=atoi(argv[2]);
    addr.sin_family=AF_INET;
    addr.sin_addr.s_addr = inet_addr(argv[1]);
    inet_aton(argv[1], &addr.sin_addr);
    uint16_t hostPort =port;
    uint16_t hostportReverse = htons(hostPort);
    addr.sin_port = hostportReverse;
    int fd;
    if(((fd=socket(AF_INET, SOCK_STREAM,0))==-1)){
        perror("Blad otworzenie socketu\n");
        exit(1);
    }

    char buf[255];
	char buf2[255];
    if(connect(fd,(struct sockaddr*)&addr, sizeof(addr))==-1){
		perror("blad nawiazania polaczenia\n");
		exit(1);
	};
	while(1)
	{
		int size;
		if((size=read(1, buf2, sizeof(buf2)-1))==-1)
				perror("blad odczytu\n");
		if(write(fd, buf2, size)==-1)
			perror("blad wyslania do serwera\n");
	    
	    if((size=read(fd, buf, sizeof(buf)))==-1)
	    {
		perror("blad odczytu z sieci\n");
		//exit(1);
	    };
		
	    if(write(1, buf, size)==-1)
	    {
		perror("blad wypisywania na ekran\n");
		//exit(1);
	    };
		
	};

    shutdown(fd,SHUT_RDWR);
}
