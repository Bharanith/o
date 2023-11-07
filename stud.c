#include<stdio.h>
#define SIZE 300
#define SEM 2
#define N 2

typedef struct{
        int regno;
        int age;
        int sem;
        char c_name[3][SIZE];
        int marks[3];
        char name[SIZE];
        char gender;
}student;

int main(){
        student s[N];
        FILE *of;
        of = fopen("stud.txt", "w");
        for (int i = 0; i < N; i++){
                printf("Enter Regno, Name, Age, Gender\n");
                scanf("%d", &s[i].regno);
                getchar();
                scanf("%[^\n]%*c", s[i].name);
                scanf("%d", &s[i].age);
                getchar();
                scanf("%c", &s[i].gender);
                for (int k = 0; k < SEM; k++){
                        s[i].sem = k + 1;
                        printf("Enter courses and marks for 3 subjects(SEM %d):\n", k +1);
                        for (int j = 0; j < 3; j++)
                                scanf("%s %d", &s[i].c_name[j], &s[i].marks[j]);

                                write (&s[i], sizeof(student), 1, of);

                }

        }
        fclose(of);
        student stu;
        FILE *inf;
        inf = fopen("stud.txt", "r");
        while(fread(&stu, sizeof(student), 1, inf)){
                printf("Regno: %d\nName: %s\nAge: %d\nGender: %c\nSem: %d\nCourse Marks ",stu.regno, stu.name, stu.age, stu.gender,stu.sem);
                printf("\n");
                for (int j = 0; j < 3; j++)
                        printf("%s %d\n", stu.c_name[j], stu.marks[j]);
                printf("\n");
        }
        fclose(inf);
        return 0;
}











