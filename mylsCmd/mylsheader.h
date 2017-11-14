#include"apue.h"
#include<dirent.h>
#include<string.h>
#include<time.h>
#include<stdlib.h>
#include<grp.h>
#include<pwd.h>
#include<limits.h>

#define MAXLEN 256

struct filEntry
{
    char filName[PATH_MAX + 1],otherEntries[MAXLEN];
    long int modTime;
};

int cmprTime(const void *a, const void *b);
int cmprName(const void *a,const void *b);
int sortAccordingToName(const struct dirent **a, const struct dirent **b);
int removeHidden(const struct dirent *dirp);
int removeDotAndDotDot(const struct dirent *dirp);

int crawlThroughDir(char path[],struct dirent ***namelist,int extraOption);
void justDisplay(struct filEntry entries[],int n);
void justAddName(struct dirent **namelist,int n,struct filEntry entries[]);
void addFileSize(struct filEntry *entries[],int n);
void sortAccordingToTime(struct filEntry *entries[],int n,char option);
int getInfoAbtFiles(char path[], struct filEntry *entries[],int *n,char option,int extraOption);
void getDetailsAbtFile(char string[],mode_t mode);
void longListingGrpUser(struct filEntry *entries[],int n,char choice);
void listRecusively(int numarg, char *args[],char path[]);
void addInodeNo(struct filEntry *entries[],int n);

void lsCommand(int numarg, char *args[],char file[]);
