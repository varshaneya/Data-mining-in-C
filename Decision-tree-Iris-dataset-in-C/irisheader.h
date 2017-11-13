/*
 *header file for iris data set
 */

#ifndef _irisdata_h

#define IRIS_SETOSA (1)
#define IRIS_VERSICOLOUR (2)
#define IRIS_VIRGINICA (3)

/*
 * pl - petal length, pw - petal width
 * sl - sepal length, sw - sepal width
 */

//union for storing either measurement of iris or the type of iris
typedef union testCondition
{
float measurement;
int irisType;
}testCondition;

//contains the different elements for a node in the decisiontree
typedef struct treeNode
{
char isTestCond,testCond[20];
testCondition cond;
struct treeNode *right,*left;
}treeNode;

typedef struct sepalRecord
{
float length,width;
}sepalRecord;

typedef struct petalRecord
{
float length,width;
}petalRecord;

typedef struct irisData
{
sepalRecord sepal;
petalRecord petal;
int irisType;
}irisData;

typedef struct irisRecord
{
int setosa;
int versicolour;
int virginica;
}irisRecord;

typedef struct petalLength
{
float length;
float entropy;
irisRecord lessThan,greaterThan;
}petalLength;

typedef struct petalWidth
{
float width;
float entropy;
irisRecord lessThan,greaterThan;
}petalWidth;

typedef struct sepalLength
{
float length;
float entropy;
irisRecord lessThan,greaterThan;
}sepalLength;

typedef struct sepalWidth
{
float width;
float entropy;
irisRecord lessThan,greaterThan;
}sepalWidth;

typedef struct attribset
{
char sLen,pLen,sWid,pWid;
}attribset;

#endif

//functions in irisdecisiontree.c 
int matchIrisCategory(char[]);
irisData* read4mFile(char[],int);
void getString(char[]);
int noOfRecords(char[]);

void findBestSplit(treeNode**,irisData[],attribset*,int,char[]);
int findMaxInfoGain(float[]);
void classify(irisData[],treeNode*,int);
int argMax(irisData[],int);
int checkAllAttr(irisData[],int);
int stoppingCondition(irisData[],int,attribset);
treeNode* treeGrowth(irisData[],attribset,int);

irisData* copyRecordSL(irisData[],float,int,char,int*);
irisData* copyRecordSW(irisData[],float,int,char,int*);
irisData* copyRecordPL(irisData[],float,int,char,int*);
irisData* copyRecordPW(irisData[],float,int,char,int*);

//functions in calentropy.c
float calEntropyPetalLength(petalLength,int);
petalLength findStat4PetalLength(irisData[],float,int);
petalLength petalLength_stat(irisData[],int,char);

float calEntropySepalLength(sepalLength,int);
sepalLength findStat4SepalLength(irisData[],float,int);
sepalLength sepalLength_stat(irisData[],int,char);

float calEntropyPetalWidth(petalWidth,int);
petalWidth findStat4PetalWidth(irisData[],float,int);
petalWidth petalWidth_stat(irisData[],int,char);

float calEntropySepalWidth(sepalWidth,int);
sepalWidth findStat4SepalWidth(irisData[],float,int);
sepalWidth sepalWidth_stat(irisData[],int,char);

float informationGain(irisData[],int,char[],char,float*);
float calEntropyOfParent(irisData[],int);

//funcions in takedecision.c
int takeInput(irisData*);
void decision4Iris(irisData,treeNode*);
int takeDecision(treeNode*);
void cleanup(treeNode*);
