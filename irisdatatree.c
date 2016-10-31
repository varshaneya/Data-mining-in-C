/*aum sai ram
 *this is a decision tree classifier for a iris classification program
 */

#include"irisheader.h"
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

void getString(char str[])
{
char ch;
int i=0;

while((ch=getchar())!='\n')
{
str[i]=ch;
++i;
}
str[i]='\0';

}

int noOfRecords(char filename[])
{
FILE *fp = fopen(filename,"r");

if(!fp)
return 0;

int i=0;
float a,b,c,d;
char str[10];

while(!feof(fp))
{
fscanf(fp,"%f,%f,%f,%f,%s",&a,&b,&c,&d,str);
++i;
}

fclose(fp);

return i-1;
}


int matchIrisCategory(char str[])
{

if(!strcmp(str,"Iris-setosa"))
return IRIS_SETOSA;

else if(!strcmp(str,"Iris-versicolor"))
return IRIS_VERSICOLOUR;

else if(!strcmp(str,"Iris-virginica"))
return IRIS_VIRGINICA;
}

irisData* read4mFile(char filnam[],int size)
{

char irisCategory[20];
irisData *iris;

iris = calloc(size,sizeof(irisData));

FILE *fp = fopen(filnam,"r");

if(!fp)
return 0;

int i=0;

while(!feof(fp))
{
fscanf(fp,"%f,%f,%f,%f,%s",&iris[i].sepal.length,&iris[i].sepal.width,&iris[i].petal.length,&iris[i].petal.width,irisCategory);

iris[i].irisType=matchIrisCategory(irisCategory);

++i;
}

//fclose(fp);

return iris;
}

int argMax(irisData iris[],int size)
{

int setosa=0,versicolour=0,virginica=0,i=0;

while(i<size)
{
if(iris[i].irisType==IRIS_SETOSA)
++setosa;	
else if(iris[i].irisType==IRIS_VERSICOLOUR)
++versicolour;
else if(iris[i].irisType==IRIS_VIRGINICA)
++virginica;

++i;
}

if(setosa>versicolour)
{
	if(setosa>virginica)
	return IRIS_SETOSA;
	else
	return IRIS_VIRGINICA;
}

else
{
	if(versicolour>virginica)
	return IRIS_VERSICOLOUR;
	else
	return IRIS_VIRGINICA; 

}

}

void classify(irisData iris[],treeNode* node,int size)
{
(node)->isTestCond='n';
node->cond.irisType=argMax(iris,size);
return;

}

int checkAllAttr(irisData iris[],int size)
{
int  flag=0,i=0;

while(i<size-1)
{
if(iris[i].sepal.length==iris[i+1].sepal.length&&iris[i].sepal.width==iris[i+1].sepal.width&&iris[i].petal.length==iris[i+1].petal.length&&iris[i].petal.width==iris[i].petal.width)
++flag;

++i;
}

if(flag==size-1)
return 1;

return 0;

}

int findMaxInfoGain(float infoGain[])
{
int i;
float temp,tempArray[4];

for(i=0;i<4;i++)
tempArray[i]=infoGain[i];

for(i=0;i<3;i++)
	if(tempArray[i]>tempArray[i+1])
	{
	temp=tempArray[i+1];
	tempArray[i+1]=tempArray[i];
	tempArray[i]=temp;
	}

for(i=0;i<4;i++)
if(tempArray[3]==infoGain[i])
return i;

}

int stoppingCondition(irisData iris[],int size,attribset f)
{
if(size<=2)
return 1;

if(f.sLen == 'Y' && f.pLen == 'Y' && f.sWid == 'Y' && f.pWid == 'Y')
return 1;

int i=0,setosa=0,virginica=0,versicolour=0;

while(i<size)
{
if(iris[i].irisType==IRIS_SETOSA)
++setosa;

else if(iris[i].irisType==IRIS_VIRGINICA)
++virginica;

else if(iris[i].irisType==IRIS_VERSICOLOUR)
++versicolour;

++i;
}

if(setosa==size||virginica==size||versicolour==size) //check if all the records have the same class label
return 1;

return checkAllAttr(iris,size);
}

void findBestSplit(treeNode **r,irisData iris[],attribset *f,int size,char bestAttrib[])
{

float infoGain[4],parameter[4];
int option;

/* 0 - sl, 1 - sw, 2 - pl, 3 - pw
 */

infoGain[0] = informationGain(iris,size,"sl",f->sLen,&parameter[0]);
infoGain[1] = informationGain(iris,size,"sw",f->sWid,&parameter[1]);
infoGain[2] = informationGain(iris,size,"pl",f->pLen,&parameter[2]);
infoGain[3] = informationGain(iris,size,"pw",f->pWid,&parameter[3]);

option = findMaxInfoGain(infoGain);


switch(option)
{
case 0: (*r)->isTestCond='y';
	strcpy((*r)->testCond,"sepal length");
	(*r)->cond.measurement = parameter[0];
	strcpy(bestAttrib,"sl");
	f->sLen = 'y';
	break;

case 1: (*r)->isTestCond='y';
	strcpy((*r)->testCond,"sepal width");
	(*r)->cond.measurement = parameter[1];
	strcpy(bestAttrib,"sw");
	f->sWid = 'y';
	break;

case 2: (*r)->isTestCond='y';
	strcpy((*r)->testCond,"petal length");
	(*r)->cond.measurement = parameter[2];
	strcpy(bestAttrib,"pl");
	f->pLen = 'y';
	break;

case 3: (*r)->isTestCond='y';
	strcpy((*r)->testCond,"petal width");
	(*r)->cond.measurement = parameter[3];
	strcpy(bestAttrib,"pw");
	f->pWid = 'y';
	break;
}

return;
}

irisData* copyRecordSL(irisData iris[],float sLength,int size,char option,int* subSize)
{
int i=0,j;
irisData *copy;
*subSize = 0;

if(option == 'l')
{
	while(i<size)
	if(iris[i++].sepal.length <= sLength)
	(*subSize)++;

	if(*subSize)
	copy = calloc(*subSize,sizeof(irisData));

	if(!copy)
	return copy;
i=0;
j=0;		
	while(i<size)
	{
	if(iris[i].sepal.length <= sLength)
	copy[j++]=iris[i];

	++i;
	}
}

else if(option == 'g')
{

	while(i<size)
	if(iris[i++].sepal.length > sLength)
	(*subSize)++;

	if(*subSize)
	copy = calloc(*subSize,sizeof(irisData));

	if(!copy)
	return copy;

i=0;
j=0;		
	while(i<size)
	{	
	if(iris[i].sepal.length > sLength)
	copy[j++]=iris[i];

	++i;
	}
}

return copy;
}

irisData* copyRecordSW(irisData iris[],float sWidth,int size,char option,int* subSize)
{

int i=0,j;
irisData *copy;
*subSize = 0;

if(option == 'l')
{
	while(i<size)
	if(iris[i++].sepal.width <= sWidth)
	(*subSize)++;

	if(*subSize)
	copy = calloc(*subSize,sizeof(irisData));

	if(!copy)
	return copy;
i=0;
j=0;		
	while(i<size)
	{
	if(iris[i].sepal.width <= sWidth)
	copy[j++]=iris[i];

	++i;
	}
}

else if(option == 'g')
{

	while(i<size)
	if(iris[i++].sepal.width > sWidth)
	(*subSize)++;

	if(*subSize)
	copy = calloc(*subSize,sizeof(irisData));

	if(!copy)
	return copy;

i=0;
j=0;		
	while(i<size)
	{	
	if(iris[i].sepal.width > sWidth)
	copy[j++]=iris[i];

	++i;
	}
}

return copy;
}

irisData* copyRecordPL(irisData iris[],float pLength,int size,char option,int* subSize)
{

int i=0,j;
irisData *copy;
*subSize = 0;

if(option == 'l')
{
	while(i<size)
	if(iris[i++].petal.length <= pLength)
	(*subSize)++;

	if(*subSize)
	copy = calloc(*subSize,sizeof(irisData));

	if(!copy)
	return copy;
i=0;
j=0;		
	while(i<size)
	{
	if(iris[i].petal.length <= pLength)
	copy[j++]=iris[i];

	++i;
	}
}

else if(option == 'g')
{

	while(i<size)
	if(iris[i++].petal.length > pLength)
	(*subSize)++;

	if(*subSize)
	copy = calloc(*subSize,sizeof(irisData));

	if(!copy)
	return copy;

i=0;
j=0;		
	while(i<size)
	{	
	if(iris[i].petal.length > pLength)
	copy[j++]=iris[i];

	++i;
	}
}

return copy;
}

irisData* copyRecordPW(irisData iris[],float pWidth,int size,char option,int* subSize)
{

int i=0,j;
irisData *copy;
*subSize = 0;

if(option == 'l')
{
	while(i<size)
	if(iris[i++].petal.width <= pWidth)
	(*subSize)++;

	if(*subSize)
	copy = calloc(*subSize,sizeof(irisData));

	if(!copy)
	return copy;
i=0;
j=0;		
	while(i<size)
	{
	if(iris[i].petal.width <= pWidth)
	copy[j++]=iris[i];

	++i;
	}
}

else if(option == 'g')
{

	while(i<size)
	if(iris[i++].petal.width > pWidth)
	(*subSize)++;

	if(*subSize)
	copy = calloc(*subSize,sizeof(irisData));

	if(!copy)
	return copy;

i=0;
j=0;		
	while(i<size)
	{	
	if(iris[i].petal.width > pWidth)
	copy[j++]=iris[i];

	++i;
	}
}

return copy;

}


treeNode* treeGrowth(irisData iris[],attribset f,int size)
{
if(!iris)
return NULL;

if(stoppingCondition(iris,size,f))
{
treeNode *leaf = calloc(1,sizeof(treeNode));

if(!leaf)
return NULL;

classify(iris,leaf,size);

//printf("\nstopping condition\n");

return leaf;
}

else
{
char bestAttrib[2];
treeNode *root = calloc(1,sizeof(treeNode));
int subSize=0;
float param=0.0;
irisData *copy = NULL;

findBestSplit(&root,iris,&f,size,bestAttrib);
param = root->cond.measurement;

	if(!strcmp(bestAttrib,"sl") && f.sLen =='y')
	{
	f.sLen = 'Y';
	copy = copyRecordSL(iris,param,size,'l',&subSize);
	root->left = treeGrowth(copy,f,subSize);	
//	printf("\n%s %c %f\n",bestAttrib,'l',param);
	
		if(copy)
		{
		free(copy);
		copy=NULL;
		}

	copy = copyRecordSL(iris,param,size,'g',&subSize);
	root->right = treeGrowth(copy,f,subSize);
//	printf("\n%s %c %f\n",bestAttrib,'g',param);

		if(copy)
		{
		free(copy);
		copy = NULL;
		}
	}

	else if(!strcmp(bestAttrib,"sw") && f.sWid == 'y')
	{
	f.sWid = 'Y';
	copy = copyRecordSW(iris,param,size,'l',&subSize);
	root->left = treeGrowth(copy,f,subSize);	
//	printf("\n%s %c %f\n",bestAttrib,'l',param);
	
		if(copy)
		{
		free(copy);
		copy = NULL;
		}

	copy = copyRecordSW(iris,param,size,'g',&subSize);
	root->right = treeGrowth(copy,f,subSize);
//	printf("\n%s %c %f\n",bestAttrib,'g',param);

		if(copy)
		{
		free(copy);
		copy = NULL;
		}
//printf("\nsw\n");
	}

	else if(!strcmp(bestAttrib,"pl") && f.pLen == 'y')
	{
	f.pLen = 'Y';
	copy = copyRecordPL(iris,param,size,'l',&subSize);
	root->left = treeGrowth(copy,f,subSize);	
//	printf("\n%s %c %f\n",bestAttrib,'l',param);
	
		if(copy)
		{
		free(copy);
		copy = NULL;
		}

	copy = copyRecordPL(iris,param,size,'g',&subSize);
	root->right = treeGrowth(copy,f,subSize);
//	printf("\n%s %c %f\n",bestAttrib,'g',param);

		if(copy)
		{
		free(copy);
		copy = NULL;
		}
//printf("\npl\n");
	}

	else if(!strcmp(bestAttrib,"pw") && f.pWid == 'y')
	{
	f.pWid = 'Y';
	copy = copyRecordPW(iris,param,size,'l',&subSize);
	root->left = treeGrowth(copy,f,subSize);	
//	printf("\n%s %c %f\n",bestAttrib,'l',param);
	
		if(copy)
		{
		free(copy);
		copy = NULL;
		}
		
	copy = copyRecordPW(iris,param,size,'g',&subSize);
	root->right = treeGrowth(copy,f,subSize);
//	printf("\n%s %c %f\n",bestAttrib,'g',param);

		if(copy)
		{
		free(copy);
		copy = NULL;
		}
//printf("\npw\n");
	}

return root;
}

}

attribset initialise()
{
attribset temp;
temp.pLen = 'n';
temp.pWid='n';
temp.sLen='n';
temp.sWid='n';

return temp;
}

int main()
{

irisData *iris = NULL;

int actSize,flag=1;

attribset f;

treeNode *decisionTree = NULL;

char *filnam = calloc(101,sizeof(char));
char option;

printf("\f\t\t\t\t\tWelcome to the Iris Datamining centre\n");

f = initialise();

printf("\n\t\tEnter the full name of the file to be read for training dataset: ");
getString(filnam);

actSize = noOfRecords(filnam);

iris = read4mFile(filnam,actSize);

free(filnam);

if(actSize==0)
{
printf("\n\t\tError... Training data set file is not present\n"); 
return 1;
}

decisionTree = treeGrowth(iris,f,actSize);

printf("\n\t\tSuccessfully trained..\n");

do
{
option = 'n';
printf("\n\t\tEnter the parameters of the test data\n");

flag = takeDecision(decisionTree);

	if(flag==-1)
	{
	printf("\n\t\tDecision tree was not created... So could not decide anything\n");
	return 1;
	}

printf("\n\t\tDo you wish to continue testing new data (y/n): ");
scanf("%c%*c",&option);

}while(option=='y'||option=='Y');

cleanup(decisionTree);

return 0;
}
