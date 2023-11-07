#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<unistd.h>

struct DNSRecord {
        char domain[100];
        int ip;
};

struct DNSRecord dnsDatabase[]={
        {"com", 2524},
        {"edu", 2526},
};
int numRecords= sizeof(dnsDatabase)/ sizeof(dnsDatabase[0]);

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
                char response[100] ="Domaain not found";

                int x[2];
                x[0]=0;

                recvfrom(sockfd,buffer,sizeof(buffer),0,(struct sockaddr *)&client_addr,&addr_len);

                for(int i=0; i < numRecords; i++){
                        if(strcmp(dnsDatabase[i].domain,buffer)==0){
                                x[0]=dnsDatabase[i].ip;
                                break;
                        }
                }

                sendto(sockfd,x,sizeof(x),0,(struct sockaddr *)&client_addr,addr_len);

        }

        close(sockfd);



        return 0;
}












