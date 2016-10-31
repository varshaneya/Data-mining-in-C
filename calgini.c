/*
 *this file contains program to find the gini index of attributes..
 */

#include"bankheader.h"
#include<math.h>
#include<string.h>
#include<stdlib.h>
#include<limits.h>

float calGiniHmOwner(hmOwner var,int size)
{
float weightedGini,hmOwnerGini,hmNotOwnerGini;
int totHmOwner,totNotHmOwner;

totHmOwner = var.yeshm.yes + var.yeshm.no;
totNotHmOwner = var.nohm.yes + var.nohm.no;

if(totHmOwner)
hmOwnerGini = 1.0F - (pow(((float)var.yeshm.yes / totHmOwner) , 2) +pow(((float)var.yeshm.no / totHmOwner) , 2));

if(totNotHmOwner)
hmNotOwnerGini = 1.0F - (pow(((float)var.nohm.yes / totNotHmOwner) , 2) +pow(((float)var.nohm.no / totNotHmOwner) , 2));

weightedGini = (((float)totHmOwner / size) * hmOwnerGini) + (((float)totNotHmOwner / size) * hmNotOwnerGini);

return weightedGini;
}

float minGiniMar(float sd,float sm,float  md,char str[])
{
if(sd<sm)
{
	if(sm<md)
	{
	strcpy(str,SINGDIV);
	return sd;
	}
	
	else
	{
	strcpy(str,MARDIV);
	return md;
	}
}

else
{	
	if(sm<md)
	{
	strcpy(str,SINGMAR);
	return sm;
	}

	else
	{
	strcpy(str,MARDIV);
	return md;
	}

}
}

float calGiniMaritalStat(maritalStat var,int size,char formatstr[])
{
float weightedGini,favGini=1.0,unFavGini=1.0;
int totFav,totUnFav;

if(!strcmp(formatstr,SINGDIV))
{
totFav = var.single.yes + var.single.no + var.divorced.yes + var.divorced.no;

totUnFav = var.married.yes + var.married.no;

if(totFav)
favGini = 1.0F - ( pow(((float)var.single.yes/totFav),2) + pow(((float)var.single.no/totFav),2) + pow(((float)var.divorced.yes/totFav),2) + pow(((float)var.divorced.no/totFav),2));

if(totUnFav)
unFavGini = 1.0F - ( pow(((float)var.married.yes/totUnFav),2) + pow(((float)var.married.no/totUnFav),2)); 

weightedGini = (((float)totFav/size) * favGini) + (((float)totUnFav/size) * unFavGini);
}

else if(!strcmp(formatstr,SINGMAR))
{

totFav = var.single.yes + var.single.no + var.married.yes + var.married.no;

totUnFav = var.divorced.yes + var.divorced.no;

if(totFav)
favGini = 1.0F - ( pow(((float)var.single.yes/totFav),2) + pow(((float)var.single.no/totFav),2) + pow(((float)var.married.yes/totFav),2) + pow(((float)var.married.no/totFav),2));

if(totUnFav)
unFavGini = 1.0F - ( pow(((float)var.divorced.yes/totUnFav),2) + pow(((float)var.divorced.no/totUnFav),2)); 

weightedGini = (((float)totFav/size) * favGini) + (((float)totUnFav/size) * unFavGini);

}

else if(!strcmp(formatstr,MARDIV))
{

totFav = var.married.yes + var.married.no + var.divorced.yes + var.divorced.no;

totUnFav = var.single.yes + var.single.no;

if(totFav)
favGini = 1.0F - ( pow(((float)var.married.yes/totFav),2) + pow(((float)var.married.no/totFav),2) + pow(((float)var.divorced.yes/totFav),2) + pow(((float)var.divorced.no/totFav),2));

if(totUnFav)
unFavGini = 1.0F - ( pow(((float)var.single.yes/totUnFav),2) + pow(((float)var.single.no/totUnFav),2)); 

weightedGini = (((float)totFav/size) * favGini) + (((float)totUnFav/size) * unFavGini);

}

return weightedGini;
}

hmOwner homeOwnerStat(bankRecord b[],int size,char status)
{
hmOwner temp;

if(status=='n')
{
int i=0;

temp.yeshm.yes=0;
temp.yeshm.no=0;
temp.nohm.yes=0;
temp.nohm.no=0;

while(i<size)
{
	if(b[i].homeOwner==YES&&b[i].defaulted==YES)
	++temp.yeshm.yes;
	else if(b[i].homeOwner==YES&&b[i].defaulted==NO)
	++temp.yeshm.no;
	else if(b[i].homeOwner==NO&&b[i].defaulted==YES)
	++temp.nohm.yes;
	else if(b[i].homeOwner==NO&&b[i].defaulted==NO)
	++temp.nohm.no;
++i;
}

temp.gini = calGiniHmOwner(temp,size);
}

else
temp.gini=100.0F;

return temp;
}


maritalStat maritalStat_stat(bankRecord b[],int size,char status)
{
maritalStat temp;

if(status=='n')
{
int i=0;
float sd,sm,md;

temp.married.yes=0;
temp.married.no=0;
temp.divorced.yes=0;
temp.divorced.no=0;
temp.single.yes=0;
temp.single.no=0;

while(i<size)
{
	if(b[i].maritalStatus==MARRIED&&b[i].defaulted==YES)
	++temp.married.yes;
	else if(b[i].maritalStatus==MARRIED&&b[i].defaulted==NO)
	++temp.married.no;
	else if(b[i].maritalStatus==SINGLE&&b[i].defaulted==YES)
	++temp.single.yes;
	else if(b[i].maritalStatus==SINGLE&&b[i].defaulted==NO)
	++temp.single.no;
	else if(b[i].maritalStatus==DIVORCED&&b[i].defaulted==YES)
	++temp.divorced.yes;
	else if(b[i].maritalStatus==DIVORCED&&b[i].defaulted==NO)
	++temp.divorced.no;
++i;
}

sd=calGiniMaritalStat(temp,size,SINGDIV);
sm=calGiniMaritalStat(temp,size,SINGMAR);
md=calGiniMaritalStat(temp,size,MARDIV);

temp.gini=minGiniMar(sd,sm,md,temp.str);
}

else
temp.gini=100.0F;

return temp;
}

float calGiniIncome(annIncome var,int size)
{
float weightedGini,lessThanGini=1.0,greaterThanGini=1.0;
int noOfLess,noOfGreater;

noOfLess = var.lessThan.yes + var.lessThan.no;
noOfGreater = var.greaterThan.yes + var.greaterThan.no;

if(noOfLess)
lessThanGini = 1.0F - ( pow(((float)var.lessThan.yes / noOfLess),2) + pow(((float)var.lessThan.no / noOfLess),2));

if(noOfGreater)
greaterThanGini = 1.0F - ( pow(((float)var.greaterThan.yes / noOfGreater),2) + pow(((float)var.greaterThan.no / noOfGreater),2));

weightedGini = (((float)noOfLess/size) * lessThanGini) + (((float)noOfGreater/size) * greaterThanGini);

return weightedGini;
}

annIncome findStat4annIncome(bankRecord b[],int inc,int size)
{
annIncome temp;
int i=0;

temp.income = inc;
temp.lessThan.yes=0;
temp.lessThan.no=0;
temp.greaterThan.yes=0;
temp.greaterThan.no=0;

while(i<size)
{
	if(b[i].annualIncome<=inc&&b[i].defaulted==YES)
	++temp.lessThan.yes;
	else if(b[i].annualIncome<=inc&&b[i].defaulted==NO)
	++temp.lessThan.no;
	else if(b[i].annualIncome>inc&&b[i].defaulted==YES)
	++temp.greaterThan.yes;
	else if(b[i].annualIncome>inc&&b[i].defaulted==NO)
	++temp.greaterThan.no;
++i;
}

temp.gini=calGiniIncome(temp,size);

return temp;
}

annIncome annualIncome_stat(bankRecord b[],int size,char status)
{
annIncome temp,*array;

if(status == 'n')
{
array=calloc(size,sizeof(annIncome));
float min=1000.0F;

int i=0;

while(i<size)
{
array[i] = findStat4annIncome(b,b[i].annualIncome,size);
++i;
}

i=0;

while(i<size)
{
	if(array[i].gini<min)
	temp=array[i];
++i;
}

free(array);
}

else
temp.gini=100.0F;

return temp;
}
