/*
 *	Aum Sai ram
 *	this file contains the code for classifying a given test data..
 */

#include"irisheader.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int takeInput(irisData *iris)
{
printf("\n\t\tEnter the details of sepal:");
printf("\n\t\tLength: ");
scanf("%f%*c",&iris->sepal.length);

if(iris->sepal.length <= 0.0f)
return 0;

printf("\t\tWidth: ");
scanf("%f%*c",&iris->sepal.width);

if(iris->sepal.width <= 0.0f)
return 0;

printf("\n\t\tEnter the details of petal:");
printf("\n\t\tLength: ");
scanf("%f%*c",&iris->petal.length);

if(iris->petal.length <= 0.0f)
return 0;

printf("\t\tWidth: ");
scanf("%f%*c",&iris->petal.width);

if(iris->petal.width <= 0.0f)
return 0;


return 1;
}

void decision4Iris(irisData iris,treeNode* root)
{

if(!root)
{
printf("\n\t\tsorry cannot classify this test data\n");
return ;
}

if(root->testCond[0]=='\0'||root->isTestCond=='n')
switch(root->cond.irisType)
{
case IRIS_SETOSA:
printf("\n\t\tThis flower is setosa\n");break;

case IRIS_VIRGINICA:
printf("\n\t\tThis flower is virginica\n");break;

case IRIS_VERSICOLOUR: 
printf("\n\t\tThis flower is versicolor\n");break;

default:printf("\n\t\tError\n");
}


else if(root->isTestCond == 'y')
{
	if(!strcmp(root->testCond,"sepal length"))
	{
		if(root->cond.measurement > iris.sepal.length)
		decision4Iris(iris,root->left);
		else
		decision4Iris(iris,root->right);

	}

	if(!strcmp(root->testCond,"sepal width"))
	{
		if(root->cond.measurement > iris.sepal.width)
		decision4Iris(iris,root->left);
		else
		decision4Iris(iris,root->right);

	}
	if(!strcmp(root->testCond,"petal length"))
	{
		if(root->cond.measurement > iris.petal.length)
		decision4Iris(iris,root->left);
		else
		decision4Iris(iris,root->right);

	}
	if(!strcmp(root->testCond,"petal width"))
	{
		if(root->cond.measurement > iris.petal.width)
		decision4Iris(iris,root->left);
		else
		decision4Iris(iris,root->right);

	}

}

}

int takeDecision(treeNode *tree)
{
irisData iris;
int decision;

if(!tree)
return -1;

if(!takeInput(&iris))
{
printf("\n\t\tError in the input\n");
return 0;
}

decision4Iris(iris,tree);

return 1;
}

void cleanup(treeNode *tree)
{
if(!tree)
return;

else
{
cleanup(tree->left);
cleanup(tree->right);
free(tree);
}
}
