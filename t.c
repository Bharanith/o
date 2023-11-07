#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<unistd.h>


int main()
{
        int sockfd;
        struct sockaddr_in server_addr,client_addr;
        socklen_t addr_len = sizeof(client_addr);


        sockfd=socket(AF_INET,SOCK_DGRAM,0);
        if(sockfd == -1)
        {
                perror("Socket not created");
                exit(1);
        }

        server_addr.sin_family=AF_INET;
        server_addr.sin_port=htons(2525);                       // PORT number ranges from 1024 to 49151
        server_addr.sin_addr.s_addr=htonl(INADDR_ANY);

        if(bind(sockfd,(struct sockaddr *)&server_addr,sizeof(server_addr)) ==-1)
        {
                perror("Bind Failed");
                exit(1);
        }
        printf("DNS server is listening on port ...\n");

        while(1)
        {

                char buffer[100]="";

                recvfrom(sockfd,buffer,sizeof(buffer),0,(struct sockaddr *)&client_addr,&addr_len);
                printf("domain:%s",buffer);
                if(strcmp(buffer,"annauniv")==0){


                int sockfd1;
                struct sockaddr_in server_addr1;
                socklen_t addr_len1 = sizeof(server_addr1);

                sockfd=socket(AF_INET,SOCK_DGRAM,0);
                if(sockfd == -1)
                {
                        perror("Socket not created");
                        exit(1);

                }

                server_addr1.sin_family=AF_INET;
                server_addr1.sin_port=htons(2530);
                server_addr1.sin_addr.s_addr=inet_addr("127.0.0.1");

                sendto(sockfd1,buffer,strlen(buffer),0,(struct sockaddr *)&server_addr1,addr_len1);
                int len=sizeof(server_addr);
                char ans[100];
                recvfrom(sockfd1,ans,sizeof(ans),0,(struct sockaddr *)&server_addr1,&addr_len);
                printf("port num from ADNS:%s\n:",ans);
                sendto(sockfd1,ans,sizeof(ans),0,(struct sockaddr *)&client_addr,&addr_len);

                close(sockfd1);
                }

        }
        close(sockfd);


        return 0;
        }






























