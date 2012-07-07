/*******************************************************************************
 * filterCalculate.c - small test program to verify some filter calculations   *
 *******************************************************************************
 * Copyright 2012 Jeroen Doggen (jeroendoggen@gmail.com)                       *
 *******************************************************************************
 * This program is free software; you can redistribute it and/or               *
 * modify it under the terms of the GNU Lesser General Public                  *
 * License as published by the Free Software Foundation; either                *
 * version 2.1 of the License, or (at your option) any later version.          *
 *                                                                             *
 * This program is distributed in the hope that it will be useful,             *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of              *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU           *
 * Lesser General Public License for more details.                             *
 *                                                                             *
 * You should have received a copy of the GNU Lesser General Public            *
 * License along with this program; if not, write to the Free Software         *
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA  *
 ******************************************************************************/


#include <stdio.h>
 
/* Convert an int to it's binary representation 
   Source: http://stackoverflow.com/questions/111928/is-there-a-printf-converter-to-print-in-binary-format
 */
int tmp, data;
int _v[2];

char *int2bin(int num, int pad)
{
 char *str = malloc(sizeof(char) * (pad+1));
  if (str) {
   str[pad]='\0';
   while (--pad>=0) {
    str[pad] = num & 1 ? '1' : '0';
    num >>= 1;
   }
  } else {
   return "";
  }
 return str;
}

void printAndCalculate(int data)
{
	printf("Incoming data: %d\n",data);
	printf("Previous samples: %d, %d, %d \n",_v[0],_v[1],_v[2]);

	tmp = (data * 662828L); 
	printf("tmp1: %d \n",tmp); //tmp=662828
	printf("tmp1: %s \n",int2bin(tmp, 32)); //tmp=662828

	tmp = ((data * 662828L) >>  4); 
	printf("tmp2: %d \n",tmp); //tmp=41426
	printf("tmp2: %s \n",int2bin(tmp, 32)); //tmp=662828L

	tmp = ((((data * 662828L) >>  4) + ((_v[0] * -540791L) >> 1) + (_v[1] * 628977L))+262144);
	printf("tmp3: %d \n",tmp); //tmp=303570
	printf("tmp3: %s \n",int2bin(tmp, 32)); //tmp=662828L

	tmp = ((((data * 662828L) >>  4) + ((_v[0] * -540791L) >> 1) + (_v[1] * 628977L))+262144) >> 19;
	printf("tmp4: %d \n",tmp); //tmp=0
	printf("tmp4: %s \n\n",int2bin(tmp, 32)); //tmp=662828L	
}


void main()
{
_v[0]=0;
_v[1]=0;
_v[2]=0;

printAndCalculate(1);
printAndCalculate(512);
printAndCalculate(1023);

_v[0]=1023;
_v[1]=1023;
_v[2]=1023;

printAndCalculate(1);
printAndCalculate(512);
printAndCalculate(1023);
}

