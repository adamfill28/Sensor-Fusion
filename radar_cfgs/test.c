#include <stdio.h>   /* Standard input/output definitions */
#include <string.h>  /* String function definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */
#include <time.h>
#include <stdbool.h>
#include <math.h>

#define DATA_PORT_PATH "/dev/ttyACM1"

#define STDIN 	0
#define STDOUT	1

#define microSec_bwCommands 100000

#define READ_BUF_SIZE  500

int multiply(char* data){
	return (data[0]
		+ data[1]<<8
		+ data[2]<<16
		+ data[3]<<24);
}

int multiplyTwo(char* data){
        return (data[0]
		+ data[1]<<8
		+ data[2]<<16
		+ data[3]<<24);   
}


bool isMagic(char data[], int size,int baseIndex){
if(size>=baseIndex+8){
return (data[baseIndex+0]==2&& data[baseIndex+1]==1&&data[baseIndex+2]==4&&data[baseIndex+3]==3&&data[baseIndex+4]==6&&data[baseIndex+5]==5&&data[baseIndex+6]==8&&data[baseIndex+7]==7);
}
return false;
}

void slice (int indexfrom, int indexto, char data[],char slice[]){
int j=0;
for(int i =indexfrom;i<=indexto;i++){
slice[j]=data[i];
j++;
}
}

void reshape(char shape[][10],char array[], int rows, int columns,int arrayLength){
int k =0;
for(int r=0;r<rows;r++){
char row[columns];

 for(int c=0;c<columns;c++){
    
   int i =c+k;
   if(i<arrayLength){
      row[c]=array[i];
    }  
   }//for
    int j=r;
    for(int i=0;i<columns;i++){
     
     shape[j][i]=row[i];
     }//for
}//Main For Loop
 k=k+columns;
}





int main(){

char read_buffer[] = {2,0x1,0x4,0x3,0x6,0x5,0x8,0x7,0x4,0x0,0x0,0x2,0x192,0x2,0x0,0x0,0x66,0x22,0x10,0x0,0x169,0x0,0x0,0x0,0x89,0x132,0x47,0x230,0x8,0x0,0x0,0x0,0x3,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1,0x0,0x0,0x0,0x100,0x0,0x0,0x0,0x8,0x0,0x9,0x0,0x2,0x0,0x0,0x0,0x142,0x4,0x214,0x255,0x16,0x0,0x0,0x0,0x255,0x0,0x0,0x0,0x62,0x0,0x254,0x15,0x120,0x15,0x0,0x0,0x15,0x0,0x3,0x0,0x81,0x9,0x225,0x255,0x78,0x1,0x0,0x0,0x204,0x0,0x4,0x0,0x32,0x0,0x29,0x1,0x196,0x17,0x0,0x0,0x241,0x0,0x253,0x255,0x25,0x0,0x80,0x1,0x253,0x20,0x0,0x0,0x12,0x0,0x254,0x255,0x133,0x0,0x122,0x255,0x232,0x0,0x0,0x0,0x255,0x0,0x0,0x0,0x55,0x0,0x100,0x1,0x53,0x22,0x0,0x0,0x204,0x0,0x4,0x0,0x30,0x0,0x226,0x249,0x183,0x16,0x0,0x0,0x2,0x0,0x0,0x0,0x0,0x2,0x0,0x0,0x150,0x126,0x29,0x137,0x46,0x138,0x255,0x129,0x67,0x114,0x208,0x103,0x236,0x92,0x194,0x93,0x103,0x93,0x87,0x94,0x114,0x94,0x180,0x95,0x168,0x104,0x14,0x115,0x129,0x116,0x202,0x110,0x51,0x103,0x162,0x99,0x236,0x97,0x101,0x103,0x194,0x102,0x174,0x96,0x129,0x91,0x18,0x91,0x29,0x91,0x133,0x89,0x247,0x81,0x253,0x84,0x108,0x94,0x5,0x98,0x231,0x93,0x40,0x84,0x102,0x91,0x43,0x89,0x211,0x82,0x43,0x85,0x162,0x84,0x14,0x79,0x181,0x80,0x166,0x81,0x148,0x79,0x183,0x84,0x199,0x92,0x159,0x90,0x126,0x95,0x104,0x103,0x99,0x109,0x168,0x117,0x64,0x110,0x63,0x111,0x191,0x107,0x62,0x107,0x171,0x118,0x40,0x124,0x87,0x118,0x126,0x110,0x220,0x112,0x131,0x121,0x202,0x122,0x145,0x117,0x76,0x110,0x112,0x107,0x63,0x116,0x70,0x122,0x17,0x121,0x109,0x114,0x145,0x103,0x204,0x106,0x162,0x107,0x168,0x99,0x75,0x94,0x152,0x104,0x51,0x109,0x90,0x108,0x233,0x102,0x83,0x104,0x225,0x107,0x75,0x108,0x151,0x109,0x3,0x109,0x163,0x106,0x153,0x106,0x53,0x104,0x77,0x101,0x77,0x99,0x159,0x98,0x45,0x99,0x253,0x101,0x213,0x101,0x14,0x100,0x199,0x109,0x40,0x107,0x130,0x102,0x56,0x103,0x93,0x102,0x197,0x104,0x93,0x105,0x73,0x104,0x130,0x103,0x218,0x117,0x59,0x117,0x208,0x99,0x186,0x95,0x29,0x93,0x23,0x98,0x6,0x104,0x80,0x100,0x169,0x89,0x22,0x90,0x83,0x93,0x196,0x97,0x65,0x95,0x41,0x89,0x181,0x94,0x6,0x106,0x141,0x112,0x158,0x109,0x159,0x99,0x124,0x101,0x105,0x104,0x0,0x110,0x153,0x111,0x135,0x116,0x68,0x119,0x189,0x108,0x160,0x97,0x186,0x100,0x86,0x107,0x200,0x101,0x10,0x109,0x179,0x112,0x251,0x102,0x139,0x105,0x214,0x100,0x66,0x84,0x187,0x100,0x229,0x101,0x239,0x101,0x159,0x97,0x126,0x104,0x204,0x102,0x226,0x92,0x160,0x93,0x204,0x96,0x174,0x93,0x108,0x87,0x226,0x82,0x126,0x88,0x147,0x91,0x108,0x96,0x186,0x96,0x134,0x92,0x193,0x106,0x209,0x108,0x160,0x96,0x114,0x90,0x44,0x90,0x69,0x92,0x26,0x93,0x248,0x97,0x26,0x93,0x7,0x101,0x162,0x100,0x219,0x93,0x231,0x90,0x161,0x91,0x79,0x88,0x213,0x80,0x15,0x85,0x130,0x88,0x236,0x89,0x86,0x94}


int size = sizeof(read_buffer)/sizeof(read_buffer[0]);
       if (sizeof(read_buffer)/sizeof(read_buffer[0])>=8+4+4 && isMagic(read_buffer,size,0)){
       //PROCESS
       //The indecies were obtained using the given mmwave documentation and the UART output packet
	char packetLength[4];//jump
        slice(12,15,read_buffer,packetLength) ;
	int length = multiply(packetLength);
	char numObjs[4];
        slice (28, 31,  read_buffer,numObjs);
        int numdetectedObjs=multiply(numObjs);
	printf("number of detected objects is %i",numdetectedObjs);
        char numTLV [4];
	slice(32,35,read_buffer,numTLV);
	int numTLVs = multiply(numTLV);
	char tag[4];
	slice(36,39,read_buffer,tag);
        char tagValue= multiply(tag);//tag should have a value of 1
        
	char jump1 [4];
	slice(40,43,read_buffer,jump1);
	int jump = multiply(jump1);
	int currentInd = 36;
	int numberObjs;
	for(int i=0;i<length;i++){
	if (tagValue==1){
	  for(int j=0;j<numdetectedObjs;j++){
	   char objects[2];//2 byte number of objects
	   currentInd = currentInd+8;
	   slice (currentInd, currentInd+1, read_buffer,objects);
	   numberObjs=multiplyTwo(objects);
	   currentInd = currentInd +2;
	   char xyzFormat[2];
	   slice(currentInd,currentInd+1,read_buffer,xyzFormat);
	   int scalingFactor= multiplyTwo(xyzFormat);
	   currentInd = currentInd +2;
	   char x[2] ;
           slice(currentInd,currentInd+1,read_buffer,x);
 	   int xV = multiplyTwo(x);
	   printf("x coordinate %i",xV);
	   currentInd=currentInd +2;
           char y[2];
           slice(currentInd,currentInd+1,read_buffer,y);
	   int yV = multiplyTwo(y);
	   printf("Y coordinate %i ",yV);
	   currentInd = currentInd +2;
	   char z[2];
	   slice(currentInd,currentInd+1,read_buffer,z);
	   int zV = multiplyTwo(z);
	   printf("Z coordinate %i",zV);
	  }  break;//for 
	} else {
	    currentInd = currentInd+jump +2*4+1;//jump to the next tag
	    char tag[4];
	    slice(currentInd,currentInd+4,read_buffer,tag);
            char tagValue= multiply(tag);//new tag value
	      
	  }		
		
	}
	  //for	
	/*if(tagValue!=1){
	  printf("No detected objects");
          //jump

         } else {
   	   char numDetectedObjs[2];
	   slice (44, 45, read_buffer,numObjs);
	   numdetectedObjs=multiplyTwo(numDetectedObjs);
	   char xyzFormat[2];
	   slice(46,47,read_buffer,xyzFormat);
	   int scalingFactor= multiplyTwo(xyzFormat);
	   char x[2] ;
           slice(54,55,read_buffer,x);
 	   int xV = multiplyTwo(x);
           char y[2];
           slice(56,57,read_buffer,y);
	   int yV = multiplyTwo(y);
	   char z[2];
	   slice(58,59,read_buffer,z);
	   int zV = multiplyTwo(z);
	   
	   }*/
         		
	   } else {
      printf("invalid data\n");
       
       }
      

return 0;

}