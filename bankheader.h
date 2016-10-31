/*
 *Header file for bank data mining problem..
 */

#ifndef _bankheader_h

#define SINGMAR "SM"
#define MARDIV "MD"
#define SINGDIV "SD"
#define SINGLE (1)
#define MARRIED (2)
#define DIVORCED (3)
#define YES (1)
#define NO (0)


typedef struct bankRecord
{
int homeOwner,maritalStatus,annualIncome,defaulted;
}bankRecord;

typedef union condition
{
char testCondition[5];
int annIncome;
}condition;

typedef struct treeNode
{
char isTestCond,testCond[20],isClassLabel,classLabel;
condition cond;
struct treeNode *right,*left;
}treeNode;

/*
 *0 - not defaulted, 1 - defaulted
 */

typedef struct defaulter
{
short yes,no;
}defaulter;

typedef struct attribset
{
char ho,ms,ai;
}attribset;

/*
 * 0 - home owner, 1 - not a home owner
 */

typedef struct hmOwner
{
defaulter yeshm,nohm;
float gini;
}hmOwner;

/*
 * 1 - single , 2 - married , 3 - divorced 
 */

typedef struct martialStat
{
defaulter married,divorced,single;
char str[3];
float gini;
}maritalStat;

/*

 *continuous attribute
 */

typedef struct annIncome
{
int income;
float gini;
defaulter lessThan,greaterThan;
}annIncome;

#endif

int read4mFile(bankRecord[]);
char argMax(bankRecord[],int);
void classify(bankRecord[],treeNode*,int);
int checkAllAttr(bankRecord[],int);
int stoppingCondition(bankRecord[],int);
char findBestSplit(treeNode**,bankRecord[],attribset*,int);
attribset initialise();
bankRecord* copyRecordHO(bankRecord[],int,char[],int*);
bankRecord* copyRecordMS(bankRecord[],int,char[],int*);
bankRecord* copyRecordAI(bankRecord[],int,int,char,int*);

float calGiniHmowner(hmOwner,int);
float minGiniMar(float,float,float,char[]);
float calGiniMaritalStat(maritalStat,int,char[]);
float calGiniIncome(annIncome,int);
annIncome finsStat4annIncome(bankRecord[],int,int);

hmOwner homeOwnerStat(bankRecord[],int,char);
maritalStat maritalStat_stat(bankRecord[],int,char);
annIncome annualIncome_stat(bankRecord[],int,char);

int takeInput(bankRecord*);
int takeDecision(treeNode*);
int decision4Loan(bankRecord,treeNode*);
