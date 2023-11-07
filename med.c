#include<stdio.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
int main()
{
        int sockdesc, sockdesc1, sockdesc2;
        struct sockaddr_in medaddr, servaddr1, servaddr2, cliaddr;

        sockdesc=socket(AF_INET,SOCK_DGRAM,0);
        sockdesc1=socket(AF_INET,SOCK_DGRAM,0);
        sockdesc2=socket(AF_INET,SOCK_DGRAM,0);

        if(sockdesc==-1 || sockdesc1 == -1 || sockdesc2 == -1)
        {
                printf("Socket not created");
                return -1;
        }

        medaddr.sin_family=AF_INET;
        medaddr.sin_port=htons(22222);                 // PORT number ranges from 1024 to 49151
        medaddr.sin_addr.s_addr=htonl(INADDR_ANY);

        servaddr1.sin_family=AF_INET;
        servaddr1.sin_port=htons(22221);                 // PORT number ranges from 1024 to 49151
        servaddr1.sin_addr.s_addr=htonl(INADDR_ANY);

        servaddr2.sin_family=AF_INET;
        servaddr2.sin_port=htons(22223);                 // PORT number ranges from 1024 to 49151
        servaddr2.sin_addr.s_addr=htonl(INADDR_ANY);

        if(bind(sockdesc,(struct sockaddr *)&medaddr,sizeof(medaddr)) < 0)
        {
                printf("Bind Failed");
                return -1;
        }

        while(1)
        {
                int len=sizeof(cliaddr);

                char command[50] = "";
                char code[10] = "";
                char output[50] = "";
                recvfrom(sockdesc,command,sizeof(command),0,(struct sockaddr *)&cliaddr,&len);
                sum +=atoi(command);
                int j=0;
                for (int i=0; command[i] != '\0'; i++)
                {
                        if (command[i] == ' ')
                                break;
                        code[j] = command[i];
                        j++;

                }
                code[j] = '\0';


                if (strcmp(code, "ADD") == 0)
                {
                        int start = j+1;

                        for (int i=j+1; command[i] != '\0'; i++)
                        {
                                if (command[i] == ',')
                                {
                                        char temp[10] = "";
                                        int k;
                                        for (k=start; k<i; k++)
                                        {
                                                temp[k-start] = command[k];
                                        }
                                        temp[k-start] = '\0';
                                        int num = atoi(temp);
                                        printf("num = %s\n", temp);

                                        start = i+1;
                                }


                        }

                        sendto(sockdesc1,command,strlen(command),0,(struct sockaddr *)&servaddr1,sizeof(servaddr1));
                        int len = sizeof(servaddr1);
                        recvfrom(sockdesc1,output,sizeof(output),0,(struct sockaddr *)&servaddr1, &len);
                        printf("message from server1: %s\n", output);
                }
                else if (strcmp(code,"SUB") == 0)
                {
                        sendto(sockdesc2,command,strlen(command),0,(struct sockaddr *)&servaddr2,sizeof(servaddr2));
                        int len = sizeof(servaddr2);
                        recvfrom(sockdesc2,output,sizeof(output),0,(struct sockaddr *)&servaddr2, &len);
                        printf("message from server2: %s\n", output);
                }
                else
                        strcpy(output, "Invalid command");

                printf("Message received from client: %s\n", command);

                sendto(sockdesc,code,strlen(code),0,(struct sockaddr *)&cliaddr,sizeof(cliaddr));

        }

        close(sockdesc);



        return 0;
}