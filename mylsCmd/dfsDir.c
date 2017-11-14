#include"mylsheader.h"

int isNameAdded = 0;
int areDetailsAdded = 0;
int isModTImeAdded=0;

int cmprTime(const void *a, const void *b)
{
    return ((struct filEntry *)b)->modTime - ((struct filEntry *)a)->modTime;
}

int cmprName(const void *a,const void *b)
{
    return *((char*)a) - *((char*)b);
}

int sortAccordingToName(const struct dirent **a, const struct dirent **b)
{
    return (*a)->d_name[0] - (*b)->d_name[0];
}

/////filters....
int removeHidden(const struct dirent *dirp)
{
    if(dirp->d_name[0]=='.')
        return 0;
    else
        return 1;
}

int removeDotAndDotDot(const struct dirent *dirp)
{
    if(!strcmp(dirp->d_name,".") || !strcmp(dirp->d_name,".."))
        return 0;
    else
        return 1;
}
////////filters........

void justDisplay(struct filEntry entries[],int n)
{
    unsigned int i=0;
    char *ptr;
    
    if(entries == NULL)
        return;
    
    while(i<n)
    {
        if(areDetailsAdded)
            printf("%s  ",entries[i].otherEntries);
        if(isModTImeAdded)
        {
            ptr = ctime(&entries[i].modTime);
            ptr[strlen(ptr)-1]='\0';
            printf("%s  ",ptr);
        }
        
        if(isNameAdded)
            printf("%s  ",entries[i].filName);
        
        printf("\n");
        
        i++;
    }
}

void justAddName(struct dirent **namelist,int n,struct filEntry entries[])
{
    
    if (n < 0)
        perror("scandir");
    else 
    {
        int i =0;
        
        while (i<n) 
        {
            strcpy(entries[i].filName,namelist[i]->d_name);
            free(namelist[i]);
            i++;
        }
        
        isNameAdded = 1;
        free(namelist);
    }
    
    qsort(entries,n,sizeof(struct filEntry),cmprName);
}

void addFileSize(struct filEntry *entries[],int n)
{
    unsigned int count = 0;
    struct stat statInfo;
    char temp[MAXLEN];
    
    while(count < n)
    {
        if(lstat((*entries+count)->filName,&statInfo) < 0)
            {
                fprintf(stderr,"cannot stat file %s.. so continuing..\n",entries[count]->filName);
                continue;
            }
            
        sprintf(temp,"%lu  ",statInfo.st_blocks);
        strcat((*entries+count)->otherEntries,temp);
        ++count;
    }
    
    areDetailsAdded = 1;
}

void addInodeNo(struct filEntry *entries[],int n)
{
    unsigned int count = 0;
    struct stat statInfo;
    char temp[MAXLEN];
    
    while(count < n)
    {
        if(lstat((*entries+count)->filName,&statInfo) < 0)
            {
                fprintf(stderr,"cannot stat file %s.. so continuing..\n",entries[count]->filName);
                continue;
            }
        
        
        sprintf(temp,"%lu  ",statInfo.st_ino);
        strcat((*entries+count)->otherEntries,temp);
        ++count;
    }
    
    areDetailsAdded = 1;
}

void getDetailsAbtFile(char string[],mode_t mode)
{
    char temp[11];
    
    if(S_ISDIR(mode))
        temp[0] = 'd';
    else if(S_ISLNK(mode))
        temp[0]= 'l';
    else
        temp[0]='-';
    
    if(mode & S_IRUSR)
        temp[1] = 'r';
    else
        temp[1] = '-';
    
    if(mode & S_IWUSR)
        temp[2] = 'w';
    else
        temp[2] = '-';
    
    if(mode & S_IXUSR)
        temp[3] = 'x';
    else
        temp[3] = '-';
    
    if(mode & S_IRGRP)
        temp[4] = 'r';
    else
        temp[4] = '-';
    
    if(mode & S_IWGRP)
        temp[5] = 'w';
    else
        temp[5] = '-';
    if(mode & S_IXGRP)
        temp[6] = 'x';
    else
        temp[6] = '-';
    
    if(mode & S_IROTH)
        temp[7] = 'r';
    else
        temp[7] = '-';
    
    if(mode & S_IWOTH)
        temp[8] = 'w';
    else
        temp[8] = '-';
    
    if(mode & S_IXOTH)
        temp[9] = 'x';
    else
        temp[9] = '-';
    
    temp[10]='\0';
    
    strcpy(string,temp);
}

void longListingGrpUser(struct filEntry *entries[],int n,char choice)
{
    unsigned int count = 0;
    struct stat statInfo;
    char temp[MAXLEN];
    
    while(count < n)
    {
        if(lstat((*entries+count)->filName,&statInfo) < 0)
            {
                fprintf(stderr,"cannot stat file %s.. so continuing..\n",entries[count]->filName);
                continue;
            }
        
        getDetailsAbtFile(temp,statInfo.st_mode);
        
        if(choice == 'n' && strlen((*entries+count)->otherEntries) < 10)
        {
            sprintf(temp,"%s  %ld  %u  %u  %ld  ",temp,statInfo.st_nlink,statInfo.st_uid,statInfo.st_gid,statInfo.st_size);
            strcat((*entries+count)->otherEntries,temp);
        }
        
        else if(choice == 'l'  && strlen((*entries+count)->otherEntries) < 10)
        {
            struct group *g;
            struct passwd *p;
            
            g = getgrgid(statInfo.st_gid);
            p = getpwuid(statInfo.st_uid);
            
            sprintf(temp,"%s  %ld  %s  %s  %ld  ",temp,statInfo.st_nlink,p->pw_name,g->gr_name,statInfo.st_size);
            strcat((*entries+count)->otherEntries,temp);
        }
        
        (*entries+count)->modTime = statInfo.st_mtime;
        ++count;
    }
    
    areDetailsAdded = 1;
    isModTImeAdded = 1;
}

void sortAccordingToTime(struct filEntry *entries[],int n,char option)
{
    unsigned int count = 0;
    struct stat statInfo;
    
    while(count < n)
    {
        if(lstat((*entries+count)->filName,&statInfo) < 0)
            {
                fprintf(stderr,"cannot stat file %s.. so continuing..\n",entries[count]->filName);
                continue;
            }
        
        if(option == 't')
            (*entries+count)->modTime = statInfo.st_mtime;
        else if(option == 'c')
            (*entries+count)->modTime = statInfo.st_ctime;
        
        ++count;
    }
    isModTImeAdded=1;
}


int crawlThroughDir(char path[],struct dirent ***namelist,int extraOption)
{
    chdir(path);
    
    int n;
    
    switch(extraOption)
    {
        case 0: n = scandir(path, namelist, NULL, sortAccordingToName);break;
        case 1: n = scandir(path, namelist, removeHidden, sortAccordingToName);break;
        case 2: n = scandir(path, namelist, removeDotAndDotDot, sortAccordingToName);break;
    }
    
    return n;

}

int getInfoAbtFiles(char path[], struct filEntry *entries[],int *n,char option,int extraOption)
{
    struct dirent **namelist;
    
    if(option == 'd' && *n == 0)
    {
        *entries = (struct filEntry*) malloc(sizeof(struct filEntry));
        strcpy((*entries)->filName,path);
        *n = 1;
        isNameAdded = 1;
        
    }
    
    else if(*n == 0)
    {
        *n = crawlThroughDir(path,&namelist,extraOption);
        
        if(*n > 0)
        {
            *entries = (struct filEntry*) calloc(*n,sizeof(struct filEntry));
            justAddName(namelist,*n,*entries);
        }
        
        else
            return -1;
    }
    
    switch(option)
    {
        case 'a': break;  //'a'
        case 'A': break;  //'A'
        case 'i': 
            addInodeNo(entries,*n);   //'i'
            break;
        case 't': 
            sortAccordingToTime(entries,*n,'t');
            qsort(*entries,*n,sizeof(struct filEntry),cmprTime);
            break;   //'t'
        case 's':
            addFileSize(entries,*n);
            break;  //'s'
        case 'n':
            longListingGrpUser(entries,*n,'n');
            break;
        case 'l':
            longListingGrpUser(entries,*n,'l');
            break;
        case 'c':
            sortAccordingToTime(entries,*n,'c');
            qsort(*entries,*n,sizeof(struct filEntry),cmprTime);
            break;
    }
    
    
    return *n;
}

void listRecusively(int numarg, char *args[],char path[])
{
    
    char mainPath[PATH_MAX+1];
    DIR *dp;
     struct dirent *dirp;
     struct stat statInfo;
    
     strcpy(mainPath,path);
     
     dp = opendir(mainPath);
     
     if(dp == NULL)
         return;
     
     if(mainPath[strlen(mainPath) - 1] != '/')
         strcat(mainPath,"/");
     
     while((dirp = readdir(dp)) != NULL)
     {
         if(!strcmp(dirp->d_name,".") || !strcmp(dirp->d_name,".."))
             continue;
             
         strcpy(path,mainPath);
         strcat(path,dirp->d_name);
         
         if(stat(path,&statInfo)<0)
         {
             fprintf(stderr,"\ncannot get stat info for %s.. so skipping it\n",path);
             continue;
         }
         
         if(S_ISDIR(statInfo.st_mode))
         {
             lsCommand(numarg,args,path);
             listRecusively(numarg,args,path);
         }
     }
}
