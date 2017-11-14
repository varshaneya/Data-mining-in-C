#include"mylsheader.h"

void lsCommand(int numarg, char *args[],char file[])
{
    int extraOption = 1,flag=0,n=0,isRecursion=0;
    char c,option;
    struct filEntry *entries = NULL;
    extern int optind;
    
    optind = 1;
    
    while((c = getopt(numarg,args,"aAidtsnlcR")) != -1)
    {
        switch(c)
        {
            case 'a': 
                option = 'a';
                extraOption = 0;
                ++flag;
                getInfoAbtFiles(file,&entries,&n,'a',extraOption);
                break;
            case 'A': 
                option = 'A';
                extraOption = 2;
                ++flag;
                getInfoAbtFiles(file,&entries,&n,'A',extraOption);
                break;
                
            case 'd': 
                option = 'd';
                getInfoAbtFiles(file,&entries,&n,'d',extraOption); 
                ++flag;
                break;
        }
    }
    
    optind = 1;
    
    while((c = getopt(numarg,args,"aAidtsnlcR")) != -1)
    {
        switch(c)
        {
             case 'i':
                 option = 'i';
                 getInfoAbtFiles(file,&entries,&n,'i',extraOption);
                 ++flag;
                 break;
            case 't':
                option = 't';
                getInfoAbtFiles(file,&entries,&n,'t',extraOption); 
                ++flag;
                break;
            case 's': 
                option = 's';
                getInfoAbtFiles(file,&entries,&n,'s',extraOption); 
                ++flag;
                break;
            case 'n': 
                option = 'n';
                getInfoAbtFiles(file,&entries,&n,'n',extraOption); 
                ++flag;
                break;
            case 'c':
                getInfoAbtFiles(file,&entries,&n,'c',extraOption); 
                ++flag;
                break;
        }
    }
    
    optind = 1;
    
    while((c = getopt(numarg,args,"aAidtsnlcR")) != -1)
    {
        switch(c)
        {
            case 'l': 
                option = 'l';
                getInfoAbtFiles(file,&entries,&n,'l',extraOption); 
                ++flag;
                break;
        }
    }
    
    optind = 1;
    
    while((c = getopt(numarg,args,"aAidtsnlcR")) != -1)
    {
        switch(c)
        {
            case 'R':
                printf("\ndirectory %s contains the files:\n",file);
                getInfoAbtFiles(file,&entries,&n,option,extraOption); 
                justDisplay(entries,n);
                ++isRecursion;
                n=0;
                listRecusively(numarg,args,file);
                ++flag;
                break;
        }
    }
    
    if(numarg == 2 && flag == 0)
        getInfoAbtFiles(file,&entries,&n,0,1);   //./myls <filename>
         
      if(!isRecursion)
      {
        justDisplay(entries,n);
        free(entries);
      }
}


int main(int argc,char* argv[])
{
    char file[PATH_MAX+1],**args=NULL;
    int n,i,flag =0;
    struct filEntry *entries = NULL;
    
    getcwd(file,MAXLEN);
    
    if(argc == 1)
    {
        getInfoAbtFiles(file,&entries,&n,0,1);   //./myls
        justDisplay(entries,n);
        return 0;
    }
    
    args = calloc(argc,sizeof(char*));
    
    for(i = 0;i<argc;i++)
    {
        args[i] = malloc(PATH_MAX);
        strcpy(args[i],argv[i]);
    }
    
    extern int optind;
    char c;
    
    optind = 1;
    
    while((c = getopt(argc,argv,"aAidtsnlcR")) != -1)
    {
        switch(c)
        {
            case 'a':
            case 'A':
            case 'i':
            case 'd':
            case 't':
            case 's':
            case 'n':
            case 'l':
            case 'c':
            case 'R':break;
            default:exit(1);
        }
    }
    
    for(i =1 ;i<argc;i++)
        if(strstr(argv[i],"-") != NULL)
            continue;
        else
        {
            strcpy(file,argv[i]);
            ++flag;
            puts(file);
            lsCommand(argc,args,file);
        }
        
    if(!flag)
        lsCommand(argc,args,file);
    
    for(i=0;i<argc;i++)
        free(args[i]);
    free(args);
       
}
