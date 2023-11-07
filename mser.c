#include<stdio.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
int main()
{
        int sockdesc;
        struct sockaddr_in servaddr,cliaddr;

        sockdesc=socket(AF_INET,SOCK_DGRAM,0);
        if(sockdesc==-1)
        {
                printf("Socket not created");
                return -1;
        }

        servaddr.sin_family=AF_INET;
        servaddr.sin_port=htons(22223);                 // PORT number ranges from 1024 to 49151
        servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
        if(bind(sockdesc,(struct sockaddr *)&servaddr,sizeof(servaddr)) < 0)
        {
                printf("Bind Failed");
                return -1;
        }

        while(1)
        {
                int len=sizeof(cliaddr);

                char command[50] = "";
                char code[10] = "";
                char input[50] = "";

                recvfrom(sockdesc,command,sizeof(command),0,(struct sockaddr *)&cliaddr,&len);
                printf("message from mediator: %s\n", command);
                sendto(sockdesc,command,strlen(command),0,(struct sockaddr *)&cliaddr, sizeof(cliaddr));
        }
        close(sockdesc);
        return 0;
}























































