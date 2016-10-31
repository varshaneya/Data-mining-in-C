/*aum sai ram
 *this is a decision tree classifier for a bank loan sanctioning process...
 */
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"bankheader.h"
#include<string.h>

int read4mFile(bankRecord b[])
{
printf("\nEnter the full name of the file to be read for training dataset: ");

char filnam[101];

fgets(filnam,101,stdin);

FILE *fp=fopen(filnam,"r");

if(!fp)
return 0;

int i=0;

while(!feof(fp))
{
fscanf(fp,"%d,%d,%d,%d",&b[i].homeOwner,&b[i].maritalStatus,&b[i].annualIncome,&b[i].defaulted);
++i;
}

fclose(fp);

return i-1;
}

char argMax(bankRecord b[],int size)
{

int yes=0,no=0,i=0;

while(i<size)
{
if(b[i].defaulted==0)
++no;
else if(b[i].defaulted==1)
++yes;

++i;
}

if(yes>no)
return 'y';

else
return 'n';

}

void classify(bankRecord b[],treeNode* node,int size)
{
(node)->isTestCond='n';
(node)->isClassLabel='y';
node->classLabel=argMax(b,size);

return;
}

int checkAllAttr(bankRecord b[],int size)
{
int  flag=0,i=0;

while(i<size-1)
{
if(b[i].maritalStatus==b[i+1].maritalStatus&&b[i].homeOwner==b[i+1].homeOwner&&b[i].annualIncome==b[i+1].annualIncome)
++flag;

++i;
}

if(flag==size-1)
return 1;

return 0;
}

int stoppingCondition(bankRecord b[],int size)
{
if(size<=2)
return 1;

int i=0,no=0,yes=0;

while(i<size)
{
if(b[i].defaulted==NO)
++no;
else if(b[i].defaulted==YES)
++yes;

++i;
}

if(no==size||yes==size) //check if all the records have the same class label
return 1;

return checkAllAttr(b,size);
}

char findMinGini(float h,float m,float a)
{

if(h<m)
{
	if(h<a)
	return 'h';
	else
	return 'a';
}

else
{
	if(m<a)
	return 'm';
	else 
	return 'a';
}

}

char findBestSplit(treeNode **r,bankRecord b[],attribset *f,int size)
{
char option;

hmOwner h = homeOwnerStat(b,size,f->ho);
maritalStat m = maritalStat_stat(b,size,f->ms);
annIncome a = annualIncome_stat(b,size,f->ai);

option = findMinGini(h.gini,m.gini,a.gini);

switch(option)
{
case 'h':(*r)->isTestCond='y';
	 strcpy((*r)->testCond,"home owner");
	 (*r)->isClassLabel='n';
	//h.gini=100.0;
	 break;
case 'm':(*r)->isTestCond='y';
	 strcpy((*r)->testCond,"marital status");
	 strcpy((*r)->cond.testCondition,m.str);
	 (*r)->isClassLabel='n';
	//m.gini=100.0;
	 break;
case 'a':(*r)->isTestCond='y'; 
	 strcpy((*r)->testCond,"annual income");
	 (*r)->cond.annIncome=a.income;
	 //m.gini=100.0;
	 (*r)->isClassLabel='n';
	  break;
}

return option;
}

bankRecord* copyRecordHO(bankRecord b[],int size,char outcome[],int *subSize)
{
*subSize=0;

bankRecord *copy=NULL;
int i=0,j;

if(!strcmp("y",outcome))
{
	while(i<size)
	if(b[i++].homeOwner==1)
	(*subSize)++;

if(*subSize)
copy = calloc(*subSize,sizeof(bankRecord));
if(!copy)
return copy;

i=0;
j=0;		
	while(i<size)
	{
	if(b[i].homeOwner==1)
	copy[j++]=b[i];

	++i;
	}
}

else if(!strcmp("n",outcome))
{
	while(i<size)
	if(b[i++].homeOwner==0)
	(*subSize)++;
if(*subSize)
copy = calloc(*subSize,sizeof(bankRecord));
if(!copy)
return copy;
i=0;
j=0;		
	while(i<size)
	{
	if(b[i].homeOwner==0)
	copy[j++]=b[i];

	++i;
	}
}

return copy;
}

bankRecord* copyRecordMS(bankRecord b[],int size,char outcome[],int *subSize)
{
int i=0,j;
bankRecord *copy;
*subSize=0;

if(!strcmp(MARDIV,outcome))
{
	while(i<size)
	{
	if(b[i].maritalStatus==MARRIED||b[i].maritalStatus==DIVORCED)
	(*subSize)++;
	++i;
	}
if(*subSize)
copy = calloc(*subSize,sizeof(bankRecord));
if(!copy)
return copy;
i=0;
j=0;		
	while(i<size)
	{
	if(b[i].maritalStatus==MARRIED||b[i].maritalStatus==DIVORCED)
	copy[j++]=b[i];

	++i;
	}
}

else if(!strcmp(SINGMAR,outcome))
{
	while(i<size)
	{
	if(b[i].maritalStatus==SINGLE||b[i].maritalStatus==MARRIED)
	(*subSize)++;

	++i;
	}
if(*subSize)
copy = calloc(*subSize,sizeof(bankRecord));
if(!copy)
return copy;
i=0;
j=0;		
	while(i<size)
	{
	if(b[i].maritalStatus==SINGLE||b[i].maritalStatus==MARRIED)
	copy[j++]=b[i];

	++i;
	}
}

else if(!strcmp(SINGDIV,outcome))
{
	while(i<size)
	{
	if(b[i].maritalStatus==SINGLE||b[i].maritalStatus==DIVORCED)
	(*subSize)++;
	++i;
	}
if(*subSize)
copy = calloc(*subSize,sizeof(bankRecord));
if(!copy)
return copy;
i=0;
j=0;		
	while(i<size)
	{
	if(b[i].maritalStatus==SINGLE||b[i].maritalStatus==DIVORCED)
	copy[j++]=b[i];

	++i;
	}
}

else if(!strcmp("s",outcome))
{

	while(i<size)
	{
	if(b[i].maritalStatus==SINGLE)
	(*subSize)++;
	++i;
	}

if(*subSize)
	copy = calloc(*subSize,sizeof(bankRecord));
if(!copy)
return copy;
i=0;
j=0;		
	while(i<size)
	{
	if(b[i].maritalStatus==SINGLE)
	copy[j++]=b[i];

	++i;
	}
}

else if(!strcmp("m",outcome))
{

	while(i<size)
	{
	if(b[i].maritalStatus==MARRIED)
	(*subSize)++;
	++i;
	}
if(*subSize)
	copy = calloc(*subSize,sizeof(bankRecord));
if(!copy)
return copy;
i=0;
j=0;		
	while(i<size)
	{
	if(b[i].maritalStatus==MARRIED)
	copy[j++]=b[i];

	++i;
	}
}

else if(!strcmp("d",outcome))
{

	while(i<size)
	{
	if(b[i++].maritalStatus==DIVORCED)
	(*subSize)++;
	++i;
	}
if(*subSize)
	copy = calloc(*subSize,sizeof(bankRecord));
if(!copy)
return copy;
i=0;
j=0;		
	while(i<size)
	{
	if(b[i].maritalStatus==DIVORCED)
	copy[j++]=b[i];

	++i;
	}
}

return copy;
}


bankRecord* copyRecordAI(bankRecord b[],int size,int income,char outcome,int *subSize)
{
int i=0,j;
bankRecord *copy;
*subSize=0;

if(outcome=='l')
{
	while(i<size)
	if(b[i++].annualIncome<=income)
	(*subSize)++;

if(*subSize)
copy = calloc(*subSize,sizeof(bankRecord));
if(!copy)
return copy;
i=0;
j=0;		
	while(i<size)
	{
	if(b[i].annualIncome<=income)
	copy[j++]=b[i];

	++i;
	}
}

else if(outcome=='g')
{

	while(i<size)
	if(b[i++].annualIncome>income)
	(*subSize)++;

if(*subSize)
	copy = calloc(*subSize,sizeof(bankRecord));
if(!copy)
return copy;
i=0;
j=0;		
	while(i<size)
	{	
	if(b[i].annualIncome>income)
	copy[j++]=b[i];

	++i;
	}
}

return copy;
}

treeNode* treeGrowth(bankRecord b[],attribset f,int size)
{

if(!b)
return NULL;

if(stoppingCondition(b,size))
{
treeNode* leaf = calloc(1,sizeof(treeNode));

if(!leaf)
return NULL;

classify(b,leaf,size);

//printf("\nstopping condition\n");
return leaf;
}

else
{
char split;
treeNode *root = calloc(1,sizeof(treeNode));
int subSize;
bankRecord *copy;

split=findBestSplit(&root,b,&f,size);

if(split=='h')
{
char outcome[3][2];
f.ho='y';

strcpy(outcome[0],"y");
strcpy(outcome[1],"n");

copy = copyRecordHO(b,size,outcome[0],&subSize);
root->right=treeGrowth(copy,f,subSize);

if(copy)
free(copy);

copy = copyRecordHO(b,size,outcome[1],&subSize);
root->left=treeGrowth(copy,f,subSize);

if(copy)
free(copy);

//printf("\nhome owner\n");
}

else if(split=='m')
{
char outcome[2][3];
f.ms='y';

strcpy(outcome[0],root->cond.testCondition);

if(!strcmp(root->cond.testCondition,SINGMAR))
strcpy(outcome[1],"d");

else if(!strcmp(root->cond.testCondition,MARDIV))
strcpy(outcome[1],"s");

else if(!strcmp(root->cond.testCondition,SINGDIV))
strcpy(outcome[1],"m");

copy = copyRecordMS(b,size,outcome[0],&subSize);
root->right=treeGrowth(copy,f,subSize);

if(copy)
free(copy);

copy = copyRecordMS(b,size,outcome[1],&subSize);
root->left=treeGrowth(copy,f,subSize);

if(copy)
free(copy);

//printf("\nmarital status\n");
}

else if(split=='a')
{
int income = root->cond.annIncome;
f.ai='y';


copy = copyRecordAI(b,size,income,'g',&subSize);
root->right=treeGrowth(copy,f,subSize);

if(copy)
free(copy);

copy = copyRecordAI(b,size,income,'l',&subSize);
root->left=treeGrowth(copy,f,subSize);

if(copy)
free(copy);

//printf("\nannual income\n");
}

//printf("\ndone\n");

return root;
}

}

attribset initialise()
{
attribset a;
a.ho='n';
a.ms='n';
a.ai='n';
return a;
}

int main()
{
bankRecord *b;
int estiSize,actSize,flag=1;
char option;

printf("\fWelcome to data mining centre..");
printf("\nEnter an upper limit estimation of the no of training records: ");
scanf("%d%*c",&estiSize);

if(estiSize<=0)
{
printf("\nWrong entry for the estimate\n");
return 1;
}

b = calloc(estiSize,sizeof(bankRecord));

if(!b)
{
printf("\nNOt enough memory in your computer\n");
return 1;
}

attribset f = initialise();

actSize = read4mFile(b);

if(actSize <= estiSize)
{
treeNode *decisionTree;

decisionTree = treeGrowth(b,f,actSize);

do
{
option ='n';

flag = takeDecision(decisionTree);

	if(flag==-1)
	{
	printf("\nDecision tree was not created... So could not decide anything\n");
	return 1;
	}

printf("\nDo you wish to continue (y/n): ");
scanf("%c%*c",&option);

}while(option=='y'||option=='Y');
}

else 
printf("\nThe estimate size for the data is smaller than the original size\n");

if(b!=NULL)
free(b);

return 0;
}
