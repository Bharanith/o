#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <time.h>

#define PORT 6666
#define SIZE 300
#define N 20


typedef struct{
        int regno;
        int age;
        int sem;
        char c_name[3][SIZE];
        int marks[3];
        char name[SIZE];
        char gender;
}student;

typedef struct{
        char method[N];
        char path[N];
        char version[N];
        char accept[N];
        char connection[N];
        char useragent[N];
        student stu;
}request;

typedef struct{
        int status;
        char statmsg[N];
        char version[N];
        char connection[N];
        char contype[N];
        char datetime[N];
        student stu;
}response;

























