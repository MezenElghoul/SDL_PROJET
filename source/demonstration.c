#include<stdio.h>
void new_methode();
void methode_standart();
    int main(){
        printf("\nmethode 1:\n");
        new_methode();
        printf("\nmethode 2:\n");
        methode_standart();
        return 0;
    }
void new_methode(){
        FILE*F=fopen("../question.txt","r");
        char question[250],reponse[3][250];
        int index=0;
        while (fscanf(F,"%99[^'\n']\n%99[^'\n']\n%99[^'\n']\n%99[^'\n']\n%d\n",question,reponse[0],reponse[1],reponse[2],&index)!=EOF)
        {
            printf("qustion:%s\n\treponse1:%s\n\treponse2:%s\n\treponse3:%s\n\treponse_correct:%d\n",question,reponse[0],reponse[1],reponse[2],index);
        }
        fclose(F);
}
void methode_standart(){
    FILE*F=fopen("../question.txt","r");
    char question[250],reponse[3][250];
    int index=0;
    while (fscanf(F,"%s\n%s\n%s\n%s\n%d",question,reponse[0],reponse[1],reponse[2],reponse[3])!=EOF)
    {
        printf("qustion:%s\n\treponse1:%s\n\treponse2:%s\n\treponse3:%s\n\treponse_correct:%d\n",question,reponse[0],reponse[1],reponse[2],index);
    }
    fclose(F);
}