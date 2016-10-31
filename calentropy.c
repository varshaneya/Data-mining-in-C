/*
 *this file contains the code for calculating the entropy for different attributes in the iris dataset..
 */

#include"irisheader.h"
#include<math.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/*
 * calculation for various parameters for the petal length like entropy
 */

float calEntropyPetalLength(petalLength temp,int size)
{
float weightedEntropy,lessThanEntropy=1.0,greaterThanEntropy=1.0;
float setosa,virginica,versicolour;
int noOfLess,noOfGreater;

noOfLess=temp.lessThan.setosa + temp.lessThan.virginica + temp.lessThan.versicolour;

noOfGreater=temp.greaterThan.setosa + temp.greaterThan.virginica + temp.greaterThan.versicolour;

if(noOfLess)
{
setosa = ((float)temp.lessThan.setosa)/noOfLess;
virginica =((float)temp.lessThan.virginica)/noOfLess;
versicolour = ((float)temp.lessThan.versicolour)/noOfLess;

	if(setosa!=0.0f&&virginica!=0.0f&&versicolour!=0.0f)
	lessThanEntropy = -1*((setosa * log2(setosa)) + (virginica * log2(virginica)) + (versicolour * log2(versicolour)) );
}


if(noOfGreater)
{
setosa = ((float)temp.greaterThan.setosa)/noOfLess;
virginica =((float)temp.greaterThan.virginica)/noOfLess;
versicolour = ((float)temp.greaterThan.versicolour)/noOfLess;

	if(setosa!=0.0f&&virginica!=0.0f&&versicolour!=0.0f)
	greaterThanEntropy = -1*((setosa * log2(setosa)) + (virginica * log2(virginica)) + (versicolour * log2(versicolour)));
}

weightedEntropy = (((float)noOfLess/size) * lessThanEntropy) + (((float)noOfGreater/size) * greaterThanEntropy);

return weightedEntropy;
}

petalLength findStat4PetalLength(irisData iris[],float length,int size)
{

petalLength temp;

int i=0;

temp.length=length;
temp.entropy=0.0;
temp.lessThan.setosa=0;
temp.lessThan.virginica=0;
temp.lessThan.versicolour=0;
temp.greaterThan.setosa=0;
temp.greaterThan.virginica=0;
temp.greaterThan.versicolour=0;

while(i<size)
{
	if(iris[i].petal.length<=length&&iris[i].irisType==IRIS_SETOSA)
	++temp.lessThan.setosa;

	else if(iris[i].petal.length<=length&&iris[i].irisType==IRIS_VERSICOLOUR)
	++temp.lessThan.versicolour;

	else if(iris[i].petal.length<=length&&iris[i].irisType==IRIS_VIRGINICA)
	++temp.lessThan.virginica;

	else if(iris[i].petal.length>length&&iris[i].irisType==IRIS_SETOSA)
	++temp.greaterThan.setosa;

	else if(iris[i].petal.length>length&&iris[i].irisType==IRIS_VIRGINICA)
	++temp.greaterThan.virginica;

	else if(iris[i].petal.length>length&&iris[i].irisType==IRIS_VERSICOLOUR)
	++temp.greaterThan.versicolour;
++i;
}

temp.entropy = calEntropyPetalLength(temp,size);

return temp;
}

petalLength petalLength_stat(irisData iris[],int size,char status)
{
petalLength temp,*array;

if(status=='n')
{
array=calloc(size,sizeof(petalLength));
float min = 100.0F;

int i=0;

while(i<size)
{
array[i]=findStat4PetalLength(iris,iris[i].petal.length,size);
++i;
}

i=0;

while(i<size)
{
	if(array[i].entropy<min)
	{
	min = array[i].entropy;
	temp=array[i];
	}
++i;
}

free(array);
}

else
temp.entropy=100.0F;

return temp;
}


/*
 * calculation for various parameters for the sepal length like entropy
 */

float calEntropySepalLength(sepalLength temp,int size)
{
float weightedEntropy,lessThanEntropy=1.0,greaterThanEntropy=1.0;
float setosa,virginica,versicolour;
int noOfLess,noOfGreater;

noOfLess=temp.lessThan.setosa + temp.lessThan.virginica + temp.lessThan.versicolour;

noOfGreater=temp.greaterThan.setosa + temp.greaterThan.virginica + temp.greaterThan.versicolour;

if(noOfLess)
{
setosa = ((float)temp.lessThan.setosa)/noOfLess;
virginica =((float)temp.lessThan.virginica)/noOfLess;
versicolour = ((float)temp.lessThan.versicolour)/noOfLess;

	if(setosa!=0.0f&&virginica!=0.0f&&versicolour!=0.0f)
	lessThanEntropy = -1*((setosa * log2(setosa)) + (virginica * log2(virginica)) + (versicolour * log2(versicolour)) );
}


if(noOfGreater)
{
setosa = ((float)temp.greaterThan.setosa)/noOfLess;
virginica =((float)temp.greaterThan.virginica)/noOfLess;
versicolour = ((float)temp.greaterThan.versicolour)/noOfLess;

	if(setosa!=0.0f&&virginica!=0.0f&&versicolour!=0.0f)
	greaterThanEntropy = -1*((setosa * log2(setosa)) + (virginica * log2(virginica)) + (versicolour * log2(versicolour)));
}

weightedEntropy = (((float)noOfLess/size) * lessThanEntropy) + (((float)noOfGreater/size) * greaterThanEntropy);

return weightedEntropy;
}

sepalLength findStat4SepalLength(irisData iris[],float length,int size)
{

sepalLength temp;

int i=0;

temp.length=length;
temp.entropy=0.0;
temp.lessThan.setosa=0;
temp.lessThan.virginica=0;
temp.lessThan.versicolour=0;
temp.greaterThan.setosa=0;
temp.greaterThan.virginica=0;
temp.greaterThan.versicolour=0;

while(i<size)
{
	if(iris[i].sepal.length<=length&&iris[i].irisType==IRIS_SETOSA)
	++temp.lessThan.setosa;

	else if(iris[i].sepal.length<=length&&iris[i].irisType==IRIS_VERSICOLOUR)
	++temp.lessThan.versicolour;

	else if(iris[i].sepal.length<=length&&iris[i].irisType==IRIS_VIRGINICA)
	++temp.lessThan.virginica;

	else if(iris[i].sepal.length>length&&iris[i].irisType==IRIS_SETOSA)
	++temp.greaterThan.setosa;

	else if(iris[i].sepal.length>length&&iris[i].irisType==IRIS_VIRGINICA)
	++temp.greaterThan.virginica;

	else if(iris[i].sepal.length>length&&iris[i].irisType==IRIS_VERSICOLOUR)
	++temp.greaterThan.versicolour;
++i;
}

temp.entropy = calEntropySepalLength(temp,size);

return temp;
}

sepalLength sepalLength_stat(irisData iris[],int size,char status)
{
sepalLength temp,*array;

if(status=='n')
{
array=calloc(size,sizeof(sepalLength));
float min = 100.0F;

int i=0;

while(i<size)
{
array[i]=findStat4SepalLength(iris,iris[i].sepal.length,size);
++i;
}

i=0;

while(i<size)
{
	if(array[i].entropy<min)
	{
	min = array[i].entropy;
	temp=array[i];
	}
++i;
}

free(array);
}

else
temp.entropy=100.0F;

return temp;
}


/*
 * calculation for various parameters for the petal width like entropy
 */

float calEntropyPetalWidth(petalWidth temp,int size)
{
float weightedEntropy,lessThanEntropy=1.0,greaterThanEntropy=1.0;
float setosa,virginica,versicolour;
int noOfLess,noOfGreater;

noOfLess=temp.lessThan.setosa + temp.lessThan.virginica + temp.lessThan.versicolour;

noOfGreater=temp.greaterThan.setosa + temp.greaterThan.virginica + temp.greaterThan.versicolour;

if(noOfLess)
{
setosa = ((float)temp.lessThan.setosa)/noOfLess;
virginica =((float)temp.lessThan.virginica)/noOfLess;
versicolour = ((float)temp.lessThan.versicolour)/noOfLess;

	if(setosa!=0.0f&&virginica!=0.0f&&versicolour!=0.0f)
	lessThanEntropy = -1*((setosa * log2(setosa)) + (virginica * log2(virginica)) + (versicolour * log2(versicolour)) );
}


if(noOfGreater)
{
setosa = ((float)temp.greaterThan.setosa)/noOfLess;
virginica =((float)temp.greaterThan.virginica)/noOfLess;
versicolour = ((float)temp.greaterThan.versicolour)/noOfLess;

	if(setosa!=0.0f&&virginica!=0.0f&&versicolour!=0.0f)
	greaterThanEntropy = -1*((setosa * log2(setosa)) + (virginica * log2(virginica)) + (versicolour * log2(versicolour)));
}

weightedEntropy = (((float)noOfLess/size) * lessThanEntropy) + (((float)noOfGreater/size) * greaterThanEntropy);

return weightedEntropy;
}

petalWidth findStat4PetalWidth(irisData iris[],float width,int size)
{

petalWidth temp;

int i=0;

temp.width=width;
temp.entropy=0.0;
temp.lessThan.setosa=0;
temp.lessThan.virginica=0;
temp.lessThan.versicolour=0;
temp.greaterThan.setosa=0;
temp.greaterThan.virginica=0;
temp.greaterThan.versicolour=0;

while(i<size)
{
	if(iris[i].petal.width<=width&&iris[i].irisType==IRIS_SETOSA)
	++temp.lessThan.setosa;

	else if(iris[i].petal.width<=width&&iris[i].irisType==IRIS_VERSICOLOUR)
	++temp.lessThan.versicolour;

	else if(iris[i].petal.width<=width&&iris[i].irisType==IRIS_VIRGINICA)
	++temp.lessThan.virginica;

	else if(iris[i].petal.width>width&&iris[i].irisType==IRIS_SETOSA)
	++temp.greaterThan.setosa;

	else if(iris[i].petal.width>width&&iris[i].irisType==IRIS_VIRGINICA)
	++temp.greaterThan.virginica;

	else if(iris[i].petal.width>width&&iris[i].irisType==IRIS_VERSICOLOUR)
	++temp.greaterThan.versicolour;
++i;
}

temp.entropy = calEntropyPetalWidth(temp,size);

return temp;
}

petalWidth petalWidth_stat(irisData iris[],int size,char status)
{
petalWidth temp,*array;

if(status=='n')
{
array=calloc(size,sizeof(petalWidth));
float min = 100.0F;

int i=0;

while(i<size)
{
array[i]=findStat4PetalWidth(iris,iris[i].petal.width,size);
++i;
}

i=0;

while(i<size)
{
	if(array[i].entropy<min)
	{
	min = array[i].entropy;
	temp=array[i];
	}
++i;
}

free(array);
}

else
temp.entropy=100.0F;

return temp;
}


/*
 * calculation for various parameters for the sepal width like entropy
 */

float calEntropySepalWidth(sepalWidth temp,int size)
{
float weightedEntropy,lessThanEntropy=1.0,greaterThanEntropy=1.0;
float setosa,virginica,versicolour;
int noOfLess,noOfGreater;

noOfLess=temp.lessThan.setosa + temp.lessThan.virginica + temp.lessThan.versicolour;

noOfGreater=temp.greaterThan.setosa + temp.greaterThan.virginica + temp.greaterThan.versicolour;

if(noOfLess)
{
setosa = ((float)temp.lessThan.setosa)/noOfLess;
virginica =((float)temp.lessThan.virginica)/noOfLess;
versicolour = ((float)temp.lessThan.versicolour)/noOfLess;

	if(setosa!=0.0f&&virginica!=0.0f&&versicolour!=0.0f)
	lessThanEntropy = -1*((setosa * log2(setosa)) + (virginica * log2(virginica)) + (versicolour * log2(versicolour)) );
}


if(noOfGreater)
{
setosa = ((float)temp.greaterThan.setosa)/noOfLess;
virginica =((float)temp.greaterThan.virginica)/noOfLess;
versicolour = ((float)temp.greaterThan.versicolour)/noOfLess;

	if(setosa!=0.0f&&virginica!=0.0f&&versicolour!=0.0f)
	greaterThanEntropy = -1*((setosa * log2(setosa)) + (virginica * log2(virginica)) + (versicolour * log2(versicolour)));
}

weightedEntropy = (((float)noOfLess/size) * lessThanEntropy) + (((float)noOfGreater/size) * greaterThanEntropy);

return weightedEntropy;
}

sepalWidth findStat4SepalWidth(irisData iris[],float width,int size)
{

sepalWidth temp;

int i=0;

temp.width=width;
temp.entropy=0.0;
temp.lessThan.setosa=0;
temp.lessThan.virginica=0;
temp.lessThan.versicolour=0;
temp.greaterThan.setosa=0;
temp.greaterThan.virginica=0;
temp.greaterThan.versicolour=0;

while(i<size)
{
	if(iris[i].sepal.width<=width&&iris[i].irisType==IRIS_SETOSA)
	++temp.lessThan.setosa;

	else if(iris[i].sepal.width<=width&&iris[i].irisType==IRIS_VERSICOLOUR)
	++temp.lessThan.versicolour;

	else if(iris[i].sepal.width<=width&&iris[i].irisType==IRIS_VIRGINICA)
	++temp.lessThan.virginica;

	else if(iris[i].sepal.width>width&&iris[i].irisType==IRIS_SETOSA)
	++temp.greaterThan.setosa;

	else if(iris[i].sepal.width>width&&iris[i].irisType==IRIS_VIRGINICA)
	++temp.greaterThan.virginica;

	else if(iris[i].sepal.width>width&&iris[i].irisType==IRIS_VERSICOLOUR)
	++temp.greaterThan.versicolour;
++i;
}

temp.entropy = calEntropySepalWidth(temp,size);

return temp;
}

sepalWidth sepalWidth_stat(irisData iris[],int size,char status)
{
sepalWidth temp,*array;

if(status=='n')
{
array=calloc(size,sizeof(sepalWidth));
float min = 100.0F;

int i=0;

while(i<size)
{
array[i]=findStat4SepalWidth(iris,iris[i].sepal.width,size);
++i;
}

i=0;

while(i<size)
{
	if(array[i].entropy<min)
	{
	min = array[i].entropy;
	temp=array[i];
	}
++i;
}

free(array);
}

else
temp.entropy=100.0F;

return temp;
}

//calculates the entropy of the parent before splitting

float calEntropyOfParent(irisData iris[],int size)
{
float entropy=0.0;
int setosa=0,versicolour=0,virginia=0;

for(int i=0;i<size;i++)
	if(iris[i].irisType==IRIS_SETOSA)
	++setosa;
	else if(iris[i].irisType==IRIS_VERSICOLOUR)
	++versicolour;
	else if(iris[i].irisType==IRIS_VIRGINICA)
	++virginia;

if(setosa)
entropy += (-1 * (log2((float)setosa/size)));

if(versicolour)
entropy += (-1 * (log2((float)versicolour/size)));

if(virginia)
entropy += (-1 * (log2((float)virginia/size)));

return entropy;
}

//calculation of information gain for the given data

float informationGain(irisData iris[],int size,char str[],char status,float *param)
{
float infoGain;
float infoParent = calEntropyOfParent(iris,size);

if(!strcmp(str,"sw"))
{
sepalWidth temp;
temp = sepalWidth_stat(iris,size,status);
*param = temp.width;
infoGain = infoParent - temp.entropy;
}

else if(!strcmp(str,"sl"))
{
sepalLength temp;
temp = sepalLength_stat(iris,size,status);
*param = temp.length;
infoGain = infoParent - temp.entropy;
}

else if(!strcmp(str,"pw"))
{
petalWidth temp;
temp = petalWidth_stat(iris,size,status);
*param = temp.width;
infoGain = infoParent - temp.entropy;
}
if(!strcmp(str,"pl"))
{
petalLength temp;
temp = petalLength_stat(iris,size,status);
*param = temp.length;
infoGain = infoParent - temp.entropy;
}

return infoGain;
}
