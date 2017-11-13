#include "apue.h"
#include <sys/wait.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include <signal.h>

pid_t pid[_SC_CHILD_MAX],pTemp;

static void sigHandler(int signo)
{
  printf("Interrupt received from the keyboard terminating the current command\n");
  kill(pTemp,SIGINT);
}

static void sigHandler1(int signo)
{
  exit(1);
}


char** getArg(char cmd[])
{
    char **args;

    unsigned int i = 0,numArg=0,j,k=0,l=0;
    char* token;

    while(cmd[i]!='\0')
    {
        if(isspace(cmd[i]) && !isspace(cmd[i+1]))
            ++numArg;

        ++i;
    }

    ++numArg;

    args = (char**)calloc(numArg,sizeof(char*));

    for(i=0;i<numArg;i++)
        args[i] = calloc(MAXLINE,sizeof(char));

    i = 0;

    token = strtok(cmd," ");

    while(token != NULL)
    {
        //puts(token);
        strcpy(args[i++],token);
        token = strtok(NULL," ");
    }

    return args;
}

pid_t runProcess(char temp[])
{
    pid_t pid;
    char** arg;
    int t;

    arg = getArg(temp);

    if ((pid = fork()) < 0)
    {
        err_sys("fork error");
    }
    else if (pid == 0) //child
    {
        //sleep(5);
        //if (signal(SIGINT,sigHandler1)<0)
        //err_sys("Cannot catch interrupt signal\n");

        if((t = execvp(arg[0],arg))<0)
        {
            printf("cannot execute the command \'%s\'\n",temp);
            return -1;
        }
    }

    return pid;

}

int updatePidList(pid_t pid[],int loc,int length)
{
    int i;
    for(i=loc;i<length;i++)
        pid[i] = pid[i+1];

    return length - 1;
}

int main(void)
{

char temp[MAXLINE]; /* from apue.h */
char *PWD,*PATH;
int status,i;
unsigned int numProcess = 0;

PWD = getenv("PWD");
PATH  = getenv("PATH");

printf("Welcome to simple shell\n[%s]%% ",PWD); /* print prompt (printf requires %% to print %) */

while ((fgets(temp, MAXLINE, stdin) != NULL) && strcmp(temp,"exit\n"))
{

    if (temp[strlen(temp) - 1] =='\n')
        temp[strlen(temp) - 1] = 0; //replace newline with null

    if(strstr(temp,"="))
        putenv(temp);

    else if(temp[strlen(temp) - 1] == '&')
    {
        temp[strlen(temp) - 1] =0;

        pTemp = runProcess(temp);

        if(pTemp > 0)
        {
            pid[numProcess++]=pTemp;
            printf("\nChild Process: %d is spawned and running in background\n",pid[numProcess-1]);
        }

        //if (signal(SIGINT,sigHandler)<0)
        //err_sys("Cannot catch interrupt signal\n");

        for(i=0;i<numProcess;i++)
        {
            pTemp = waitpid(pid[i],&status,WNOHANG|WUNTRACED);

            if(pTemp < 0)
                continue;

            if(WIFSIGNALED(status))
                printf("\nabnormal termination of child process %d. status: %d\n",pid[i],status);

            if(WIFEXITED(status))
            {
                printf("\nChild Process: %d exited with status: %d\n",pid[i],status);
                numProcess=updatePidList(pid,i,numProcess);
            }
        }
    }
    else
    {
        pTemp = runProcess(temp);

        if (signal(SIGINT,sigHandler)<0)
        err_sys("Cannot catch interrupt signal\n");

        if(pTemp > 0)
        {
            pTemp = waitpid(pTemp, &status, 0);
                //err_sys("waitpid error");
            if(WIFSIGNALED(status))
                printf("\nabnormal termination of child process %d. status: %d\n",pTemp,status);

            if(WIFEXITED(status))
                printf("\nChild Process: %d exited with status: %d\n",pTemp,status);
        }
    }

    PWD = getenv("PWD");
    PATH  = getenv("PATH");
    printf("[%s]%% ",PWD);

}

    for(i=0;i<numProcess;i++)
    {
        pTemp = waitpid(pid[i],&status,0);

        if(pTemp < 0)
            continue;

        if(WIFSIGNALED(status))
            printf("\nabnormal termination of child process %d. status: %d\n",pid[i],status);

        if(WIFEXITED(status))
        {
            printf("\nChild Process: %d exited with status: %d\n",pid[i],status);
            numProcess=updatePidList(pid,i,numProcess);
        }
    }
exit(0);

}
