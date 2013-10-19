#include <conio.h>
#include <dos.h>
#include <iostream.h>
#include <stdio.h>
#include <stdlib.h>

unsigned int Speed=100 , Tone=200; //default

void Beep(short int Signal){

		while(1&Signal){
			sound(Tone);
//printf ("  S=%d  1&S=%d  2&S=%d\n" , Signal, 1&(Signal) ,  1&(Signal>>1)  );
			delay ( Speed + Speed * (2&(Signal)) );
//			printf ("\n%d\n",100+100 * (2&(Signal)));
			nosound();
			delay (Speed/2);
			Signal>>=2;
			}
	delay (Speed);
	}

void Read_txt_file(short int *Znak){
	FILE *stream;

	if ((stream = fopen("message.txt", "r")) == NULL){
		fprintf(stderr,"Can not open message file");
		//exit (0);
		return;
		}
	fseek(stream, 0, SEEK_SET);

	unsigned char temp[2];
	int n;

	fscanf(stream,"%s%d",&temp[0],&Speed);
	printf("\n%s %d\n",temp,Speed);
	if (temp[0]!=83){
		Speed=100;
		fseek(stream, 0, SEEK_SET);
		}

	fscanf(stream,"%s%d",&temp[0],&Tone);
	printf("\n%s %d\n",temp,Tone);
	if (temp[0]!=84){
		Tone=200;
		fseek(stream, 0, SEEK_SET);
		}

	temp[1]=0;

	fread(temp,1,1,stream);

		while(!feof(stream) && !kbhit()){
			printf("%s",temp);

			if (temp[0]<=32)
				delay (Speed/2);

			if (temp[0]>=48 && temp[0]<=57)
				Beep(*(Znak+temp[0]-48));

			if (temp[0]>=128 && temp[0]<=159)
				Beep(*(Znak+temp[0]-128+10));

			if (temp[0]>=44 && temp[0]<=46)
				Beep(*(Znak+temp[0]-44+42));

			if (temp[0]==33)
				Beep(3935);

			if (temp[0]==63)
				Beep(1525);

			fread(temp,1,1,stream);
			}

		fclose(stream);
	}




void main (void){

	short int *Znak;
	Znak=new short int[47];

//void Get_znak
	int line,n=0;
	FILE *stream;
	unsigned char temp[6];
	if ((stream = fopen("code", "r")) == NULL){
		fprintf(stderr,"\aCan not open code file");
		exit (0);
		}
	fseek(stream, 0, SEEK_SET);
	while(!feof(stream)){
		fgets(temp,6,stream);
		sscanf(temp,"%d",(Znak+n) );
//			printf("%d:%d\n",n,*(Znak+n) );
		n++;
		}
	fclose(stream);

	Read_txt_file(Znak);

	delete [] Znak;
	//getch();
	}