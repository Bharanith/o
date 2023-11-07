#include<stdio.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<string.h>
#include<unistd.h>
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
        servaddr.sin_port=htons(1025);                  // PORT number ranges from 1024 to 49151
        servaddr.sin_addr.s_addr=htonl(INADDR_ANY);

        int n;
        char space;
        printf("enter no of commands");
        scanf("%d",&n);
        scanf("%c",&space);

        while (n>0)
        {
                char command[50] ="";
                char output[50] ="";
                printf("enter command:");
                scanf("%d", &command);
                scanf("%d",& space);


                sendto(sockdesc,command,strlen(command),0,(struct sockaddr *)&servaddr,sizeof(servaddr));

                int len=sizeof(serveraddr);
                recvfrom(sockdesc,output,sizeof(output),0,(struct sockaddr *)&servaddr,sizeof(servaddr));
                printf("Message from server: %s\n", output);
                n--;
        }

        close(sockdesc);



        return 0;
}








































