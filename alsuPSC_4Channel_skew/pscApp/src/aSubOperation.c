#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <dbAccess.h>
#include <dbDefs.h>
#include <dbFldTypes.h>
#include <registryFunction.h>
#include <aSubRecord.h>
#include <waveformRecord.h>
#include <epicsExport.h>
#include <epicsTime.h>

#define RAW_DATA_SIZE_BYTE_NUM 2621440
#define SNAPSHOT_POINTS_NUM 20000

static long ADCSnapShotParse(aSubRecord *pasub) 
{
	char *aptr;	
	int RAW_DATASIZE_BYTE=RAW_DATA_SIZE_BYTE_NUM; 
	int SnapShot_POINTS=SNAPSHOT_POINTS_NUM; 
	unsigned char data[RAW_DATASIZE_BYTE];
	float tempF;        
	float SnapShotData[SnapShot_POINTS];
	int byteIndex;
	int SnapShotIndex;
	int SnapShotOffsetByteStart=1; 
	int SnapShotOffsetByte;
	int ADCIndex;
	float *fPtr;
	char section;
	int fullRange,halfRange;
	int i;
	memcpy(data,pasub->a,RAW_DATASIZE_BYTE*sizeof(char));
	section = 1;

	for(ADCIndex=0;ADCIndex<8;ADCIndex++) {
		if(section==1) {fullRange=0x3FFFF;halfRange=0x20000;}
		else {fullRange=0xFFFF; halfRange=0x8000;}
		SnapShotOffsetByte = SnapShotOffsetByteStart + (ADCIndex*4);
		for(SnapShotIndex=0;SnapShotIndex<SnapShot_POINTS;SnapShotIndex++) {
		    byteIndex= SnapShotOffsetByte + SnapShotIndex*128;
		    if(section==1)
			tempF = (data[byteIndex]<<16)+(data[byteIndex+1]<<8)+data[byteIndex+2];		    
		    else tempF = (data[byteIndex+1]<<8)+data[byteIndex+2];		    	

		    if(tempF >= halfRange) tempF = -1.0*((float)(fullRange-tempF))*(20.0/fullRange);
		    else tempF = tempF*(20.0/fullRange);
		    SnapShotData[SnapShotIndex]=tempF;
		}
	switch(ADCIndex) {
		case 0:  fPtr=(float *)pasub->vala; break;
		case 1:  fPtr=(float *)pasub->valb; break;
		case 2:  fPtr=(float *)pasub->valc; break;
		case 3:  fPtr=(float *)pasub->vald; break;
		case 4:  fPtr=(float *)pasub->vale; break;
		case 5:  fPtr=(float *)pasub->valf; break;
		case 6:  fPtr=(float *)pasub->valg; break;
		case 7:  fPtr=(float *)pasub->valh; break;
		default: break; }
	memcpy(fPtr,SnapShotData,SnapShot_POINTS*sizeof(float));	
	}	
}

static long ADCSnapShotParse2(aSubRecord *pasub) 
{
	char *aptr;	
	int RAW_DATASIZE_BYTE=RAW_DATA_SIZE_BYTE_NUM; 
	int SnapShot_POINTS=SNAPSHOT_POINTS_NUM; 
	unsigned char data[RAW_DATASIZE_BYTE];
	float tempF;        
	float SnapShotData[SnapShot_POINTS];
	int byteIndex;
	int SnapShotIndex;
	int SnapShotOffsetByteStart=1+8*4; //77+24*4;
	int SnapShotOffsetByte;
	int ADCIndex;
	float *fPtr;
	char section;
	int fullRange,halfRange;
	int i;
	memcpy(data,pasub->a,RAW_DATASIZE_BYTE*sizeof(char));
	section = 2;

	for(ADCIndex=0;ADCIndex<8;ADCIndex++) {
		if(section==1) {fullRange=0x3FFFF;halfRange=0x20000;}
		else {fullRange=0xFFFF; halfRange=0x8000;}
		SnapShotOffsetByte = SnapShotOffsetByteStart + (ADCIndex*4);
		for(SnapShotIndex=0;SnapShotIndex<SnapShot_POINTS;SnapShotIndex++) {
		    byteIndex= SnapShotOffsetByte + SnapShotIndex*128;
		    if(section==1)
			tempF = (data[byteIndex]<<16)+(data[byteIndex+1]<<8)+data[byteIndex+2];		    
		    else tempF = (data[byteIndex+1]<<8)+data[byteIndex+2];		    	

		    if(tempF >= halfRange) tempF = -1.0*((float)(fullRange-tempF))*(20.0/fullRange);
		    else tempF = tempF*(20.0/fullRange);
		    SnapShotData[SnapShotIndex]=tempF;
		}
	switch(ADCIndex) {
		case 0:  fPtr=(float *)pasub->vala; break;
		case 1:  fPtr=(float *)pasub->valb; break;
		case 2:  fPtr=(float *)pasub->valc; break;
		case 3:  fPtr=(float *)pasub->vald; break;
		case 4:  fPtr=(float *)pasub->vale; break;
		case 5:  fPtr=(float *)pasub->valf; break;
		case 6:  fPtr=(float *)pasub->valg; break;
		case 7:  fPtr=(float *)pasub->valh; break;
		default: break; }
	memcpy(fPtr,SnapShotData,SnapShot_POINTS*sizeof(float));	
	}	
}

static long ADCSnapShotParse3(aSubRecord *pasub) 
{
	char *aptr;	
	int RAW_DATASIZE_BYTE=RAW_DATA_SIZE_BYTE_NUM; 
	int SnapShot_POINTS=SNAPSHOT_POINTS_NUM; 
	unsigned char data[RAW_DATASIZE_BYTE];
	float tempF;        
	float SnapShotData[SnapShot_POINTS];
	int byteIndex;
	int SnapShotIndex;
	int SnapShotOffsetByteStart=1+16*4; 
	int SnapShotOffsetByte;
	int ADCIndex;
	float *fPtr;
	char section;
	int fullRange,halfRange;
	int i;
	memcpy(data,pasub->a,RAW_DATASIZE_BYTE*sizeof(char));
	section = 3;

	for(ADCIndex=0;ADCIndex<8;ADCIndex++) {
		if(section==1) {fullRange=0x3FFFF;halfRange=0x20000;}
		else {fullRange=0xFFFF; halfRange=0x8000;}
		SnapShotOffsetByte = SnapShotOffsetByteStart + (ADCIndex*4);
		for(SnapShotIndex=0;SnapShotIndex<SnapShot_POINTS;SnapShotIndex++) {
		    byteIndex= SnapShotOffsetByte + SnapShotIndex*128;
		    if(section==1)
			tempF = (data[byteIndex]<<16)+(data[byteIndex+1]<<8)+data[byteIndex+2];		    
		    else tempF = (data[byteIndex+1]<<8)+data[byteIndex+2];		    	

		    if(tempF >= halfRange) tempF = -1.0*((float)(fullRange-tempF))*(20.0/fullRange);
		    else tempF = tempF*(20.0/fullRange);
		    SnapShotData[SnapShotIndex]=tempF;
		}
	switch(ADCIndex) {
		case 0:  fPtr=(float *)pasub->vala; break;
		case 1:  fPtr=(float *)pasub->valb; break;
		case 2:  fPtr=(float *)pasub->valc; break;
		case 3:  fPtr=(float *)pasub->vald; break;
		case 4:  fPtr=(float *)pasub->vale; break;
		case 5:  fPtr=(float *)pasub->valf; break;
		case 6:  fPtr=(float *)pasub->valg; break;
		case 7:  fPtr=(float *)pasub->valh; break;
		default: break; }
	memcpy(fPtr,SnapShotData,SnapShot_POINTS*sizeof(float));	
	}	
}

static long ADCSnapShotParse4(aSubRecord *pasub) 
{
	char *aptr;	
	int RAW_DATASIZE_BYTE=RAW_DATA_SIZE_BYTE_NUM; 	 
	int SnapShot_POINTS=SNAPSHOT_POINTS_NUM; 
	unsigned char data[RAW_DATASIZE_BYTE];
	float tempF;        
	float SnapShotData[SnapShot_POINTS];
	int byteIndex;
	int SnapShotIndex;
	int SnapShotOffsetByteStart=1+24*4; 
	int SnapShotOffsetByte;
	int ADCIndex;
	float *fPtr;
	char section;
	int fullRange,halfRange;
	int i;
	memcpy(data,pasub->a,RAW_DATASIZE_BYTE*sizeof(char));
	section = 3;

	for(ADCIndex=0;ADCIndex<8;ADCIndex++) {
		if(section==1) {fullRange=0x3FFFF;halfRange=0x20000;}
		else {fullRange=0xFFFF; halfRange=0x8000;}
		SnapShotOffsetByte = SnapShotOffsetByteStart + (ADCIndex*4);
		for(SnapShotIndex=0;SnapShotIndex<SnapShot_POINTS;SnapShotIndex++) {
		    byteIndex= SnapShotOffsetByte + SnapShotIndex*128;
		    if(section==1)
			tempF = (data[byteIndex]<<16)+(data[byteIndex+1]<<8)+data[byteIndex+2];		    
		    else tempF = (data[byteIndex+1]<<8)+data[byteIndex+2];		    	

		    if(tempF >= halfRange) tempF = -1.0*((float)(fullRange-tempF))*(20.0/fullRange);
		    else tempF = tempF*(20.0/fullRange);
		    SnapShotData[SnapShotIndex]=tempF;
		}
	switch(ADCIndex) {
		case 0:  fPtr=(float *)pasub->vala; break;
		case 1:  fPtr=(float *)pasub->valb; break;
		case 2:  fPtr=(float *)pasub->valc; break;
		case 3:  fPtr=(float *)pasub->vald; break;
		case 4:  fPtr=(float *)pasub->vale; break;
		case 5:  fPtr=(float *)pasub->valf; break;
		case 6:  fPtr=(float *)pasub->valg; break;
		case 7:  fPtr=(float *)pasub->valh; break;
		default: break; }
	memcpy(fPtr,SnapShotData,SnapShot_POINTS*sizeof(float));	
	}	
}

static long ADCSnapShotParse5(aSubRecord *pasub) 
{
	char *aptr;	
	int RAW_DATASIZE_BYTE=RAW_DATA_SIZE_BYTE_NUM;  
	int SnapShot_POINTS=SNAPSHOT_POINTS_NUM; 
	unsigned char data[RAW_DATASIZE_BYTE];
	float tempF;        
	float SnapShotData[SnapShot_POINTS];
	int byteIndex;
	int SnapShotIndex;
	int SnapShotOffsetByteStart=1+8*4; 
	int SnapShotOffsetByte;
	int ADCIndex;
	float *fPtr;
	char section;
	int fullRange,halfRange;
	int i;
	memcpy(data,pasub->a,RAW_DATASIZE_BYTE*sizeof(char));
	section = 3;

	for(ADCIndex=0;ADCIndex<8;ADCIndex++) {
		if(section==1) {fullRange=0x3FFFF;halfRange=0x20000;}
		else {fullRange=0xFFFF; halfRange=0x8000;}
		SnapShotOffsetByte = SnapShotOffsetByteStart + (ADCIndex*4);
		for(SnapShotIndex=0;SnapShotIndex<SnapShot_POINTS;SnapShotIndex++) {
		    byteIndex= SnapShotOffsetByte + SnapShotIndex*128;
		    if(section==1)
			tempF = (data[byteIndex]<<16)+(data[byteIndex+1]<<8)+data[byteIndex+2];	    
		    else tempF = (data[byteIndex-1]<<8)+data[byteIndex];		    	

		    if(tempF >= halfRange) tempF = tempF; 
		    else tempF = tempF; 
		    SnapShotData[SnapShotIndex]=tempF;
		}
	switch(ADCIndex) {
		case 0:  fPtr=(float *)pasub->vala; break;
		case 1:  fPtr=(float *)pasub->valb; break;
		case 2:  fPtr=(float *)pasub->valc; break;
		case 3:  fPtr=(float *)pasub->vald; break;
		case 4:  fPtr=(float *)pasub->vale; break;
		case 5:  fPtr=(float *)pasub->valf; break;
		case 6:  fPtr=(float *)pasub->valg; break;
		case 7:  fPtr=(float *)pasub->valh; break;
		default: break; }
	memcpy(fPtr,SnapShotData,SnapShot_POINTS*sizeof(float));	
	}	
}

epicsRegisterFunction(ADCSnapShotParse);
epicsRegisterFunction(ADCSnapShotParse2);
epicsRegisterFunction(ADCSnapShotParse3);
epicsRegisterFunction(ADCSnapShotParse4);
epicsRegisterFunction(ADCSnapShotParse5);




