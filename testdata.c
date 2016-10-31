/*
 * Aum Sai Ram
 * 
 */

#include"bankheader.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int takeInput(bankRecord *b)
{
printf("\nEnter the whether the person is a home owner:\n 0 - not home owner and 1 - home owner: ");
scanf("%d%*c",&b->homeOwner);

if(b->homeOwner!=0&&b->homeOwner!=1)
return 0;


printf("\nEnter the person's marital status:\n 1 - single, 2 - married and 3 - divorced: ");
scanf("%d%*c",&b->maritalStatus);

switch(b->maritalStatus)
{
case 1:
case 2:
case 3:break;
default: return 0;
}

printf("\nEnter the person's annual income: ");
scanf("%d%*c",&b->annualIncome);

if(b->annualIncome <=0)
return 0;

return 1;
}

int decision4Loan(bankRecord b,treeNode* root)
{
if(root->isClassLabel=='y')
{
	if(root->classLabel=='y')
	return 1;
	else if(root->classLabel=='n')
	return 0;
}

else if(root->isTestCond=='y')
{
	if(!strcmp(root->testCond,"home owner"))
	{
		if(b.homeOwner==1)
		decision4Loan(b,root->right);
		else 
		decision4Loan(b,root->left);
	}

	else if(!strcmp(root->testCond,"annual income"))
	{
		if(root->cond.annIncome<b.annualIncome)
		decision4Loan(b,root->left);
		else
		decision4Loan(b,root->right);
	}

	else if(!strcmp(root->testCond,"marital status"))
	{
		if(!strcmp(root->cond.testCondition,SINGDIV))
		{
			if(b.maritalStatus==SINGLE||b.maritalStatus==DIVORCED)
			decision4Loan(b,root->right);
			else
			decision4Loan(b,root->left);
		}
		else if(!strcmp(root->cond.testCondition,SINGMAR))
		{
			if(b.maritalStatus==SINGLE||b.maritalStatus==MARRIED)
			decision4Loan(b,root->right);
			else
			decision4Loan(b,root->left);
		}
	
		else if(!strcmp(root->cond.testCondition,MARDIV))
		{
			if(b.maritalStatus==MARRIED||b.maritalStatus==DIVORCED)
			decision4Loan(b,root->right);
			else
			decision4Loan(b,root->left);
		}
	
	
	}

}

}

int takeDecision(treeNode *tree)
{
bankRecord bRecord;

if(!tree)
return -1;

if(!takeInput(&bRecord))
{
printf("\nError in the input\n");
return 0;
}

if(decision4Loan(bRecord,tree))
printf("\nBorrower might default... Donot sanction the loan\n");

else
printf("\nBorrower will not default... Sanction the loan\n");

return 1;
}
