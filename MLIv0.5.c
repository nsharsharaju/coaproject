#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>


int bintonum(char *);

int main(){

	// File reading

	FILE *fp;
	char c[100][33];
	int i,j,flag=1,summer=0,d=0;

	fp = fopen("output.txt", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);
    j=0;
    while (flag) {

        for(i=0; i<32; i++){
	        if ((c[j][i] = fgetc(fp))&&c[j][i] == EOF){
	       		flag = 0;
	        	break;
	       		}
        }
        if (!flag) break;
        c[j][i] = '\0';
        j++;
	}
	fclose(fp);
	for(i=0;i<j;i++)
    {
        printf("%s\n",c[i]);
    }

	// decoding

	int reg[20]={0};
	int mem[1000]={0};
	int spreg[3]={0};

	// sp[0] -> Negative
	// sp[1] -> Zero
	spreg[2] = 0; // sp[2] -> PC

while(1){
		printf("The register status is:\n");
		for(i=0;i<16;i++)
		{
			printf("%d ",reg[i]);
		}
		printf("\nneg: %d \nzero: %d \nprogram counter:%d\n",spreg[0],spreg[1],spreg[2]);
		char temp1[33],temp2[33],temp3[33],temp4[33];
		int tempint[3];
		for(i=0; i< 8; i++){
			temp1[i] = c[spreg[2]][i];
		}
		temp1[i] = '\0';

		for(j=0; i< 16; i++,j++){
			temp2[j] = c[spreg[2]][i];
		}
		temp2[j] = '\0';

		for(j=0; i< 24; i++,j++){
			temp3[j] = c[spreg[2]][i];
		}
		temp3[j] = '\0';

		for(j=0; i< 32; i++,j++){
			temp4[j] = c[spreg[2]][i];
		}
		temp4[j] = '\0';


		//MOD

		if(!strcmp(temp1,"00000000")){
			tempint[0] = bintonum(temp2);
			tempint[1] = bintonum(temp3);
			tempint[2] = bintonum(temp4);
			summer=reg[tempint[1]];
			reg[tempint[0]]=summer%reg[tempint[2]];
			printf("enter mod %d %d %d %d\n",reg[tempint[0]],reg[tempint[1]],reg[tempint[2]],tempint[0]);
			spreg[2]++;
			continue;
		}


		// CMPI
		if(!strcmp(temp1,"00000010")){
		    printf("enter compi\n");
			tempint[0]=bintonum(temp2);
			strcat(temp3,temp4);
			tempint[1]=bintonum(temp3);
			summer=reg[tempint[0]]-tempint[1];
			printf("%d  %d\n",tempint[0],tempint[1]);
			printf("summer %d",summer);
			if(summer<0) {
				spreg[0]=1;
				spreg[1]=0;
			}
			if(summer==0) {
				spreg[1]=1;
				spreg[0]=0;
			}
			if(summer>0){
				spreg[1]=0;
				spreg[0]=0;
			}
			printf("special registers %d %d",spreg[0],spreg[1]);
			spreg[2]++;
			continue;
		}

		//MOVI
		if(!strcmp(temp1,"00000011")){
			tempint[0]=bintonum(temp2);
			strcat(temp3,temp4);
			tempint[1]=bintonum(temp3);
			reg[tempint[0]]=tempint[1];
			spreg[2]++;
			continue;
		}

		//ADD
		if(!strcmp(temp1,"00000100")){
			tempint[0] = bintonum(temp2);
			tempint[1] = bintonum(temp3);
			tempint[2] = bintonum(temp4);
			reg[tempint[0]]=reg[tempint[1]]+reg[tempint[2]];
			spreg[2]++;
			continue;
		}

		//CMPR
		strcat(temp1,temp2);
		if(!strcmp(temp1,"0000000100000001")){
			tempint[0]=bintonum(temp3);
			tempint[1]=bintonum(temp4);
			summer=reg[tempint[0]]-reg[tempint[1]];
			if(summer<0) {
				spreg[0]=1;
				spreg[1]=0;
			}
			if(summer==0) {
				spreg[1]=1;
				spreg[0]=0;
			}
			if(summer>0){
				spreg[1]=0;
				spreg[0]=0;
			}
			spreg[2]++;
			continue;
		}

		//IN
		if(!strcmp(temp1,"0000000100000010")){
			tempint[0]=bintonum(temp3);
			tempint[1]=bintonum(temp4);
			printf("enter a value\n");
			scanf("%d",&reg[tempint[0]]);
			spreg[2]++;
			continue;
		}

		//OUT
		if(!strcmp(temp1,"0000000100000011")){
			tempint[0]=bintonum(temp3);
			tempint[1]=bintonum(temp4);
			printf("\n\n\n\nvalue is %d\n\n\n\n\n",reg[tempint[0]]);
			spreg[2]++;
			continue;
		}

		//STB
		if(!strcmp(temp1,"0000000100000100")){
			tempint[0]=bintonum(temp3);
			tempint[1]=bintonum(temp4);
			mem[reg[tempint[0]]]=reg[tempint[1]];
			spreg[2]++;
			continue;
		}

		//LDB
		if(!strcmp(temp1,"0000000100000101")){
			tempint[0]=bintonum(temp3);
			tempint[1]=bintonum(temp4);
			reg[tempint[0]]=mem[reg[tempint[1]]];
			spreg[2]++;
			continue;
		}

		//MOVR
		if(!strcmp(temp1,"0000000100000110")){
			tempint[0]=bintonum(temp3);
			tempint[1]=bintonum(temp4);
			reg[tempint[0]]=reg[tempint[1]];
			spreg[2]++;
			continue;
		}
		strcat(temp1,temp3);

		//INC
		if(!strcmp(temp1,"000000010000100000000000")){
			tempint[0]=bintonum(temp4);
			reg[tempint[0]]++;
			spreg[2]++;
			continue;
		}

		//DEC
		if(!strcmp(temp1,"000000010000100000000001")){
			tempint[0]=bintonum(temp4);
			reg[tempint[0]]--;
			spreg[2]++;
			continue;
		}

		//JUMP
		if(!strcmp(temp1,"000000010000100000000010")){
			tempint[0]=bintonum(temp4);
			spreg[2]=tempint[0];
			continue;
		}

		//JG
		if(!strcmp(temp1,"000000010000100000000011")){
			tempint[0]=bintonum(temp4);
			if(spreg[0]==0&&spreg[1]==0){
				spreg[2]=tempint[0];
				continue;
			}
			spreg[2]++;
			continue;
		}

		//JL
		if(!strcmp(temp1,"000000010000100000000100")){
			tempint[0]=bintonum(temp4);
			if(spreg[0]==1&&spreg[1]==0){
				spreg[2]=tempint[0];
				continue;
			}
			spreg[2]++;
			continue;
		}

		//JE
		if(!strcmp(temp1,"000000010000100000000101")){
			tempint[0]=bintonum(temp4);
			if(spreg[0]==0&&spreg[1]==1){
				spreg[2]=tempint[0];
				continue;
			}
			spreg[2]++;
			continue;
		}

		//JNE
		if(!strcmp(temp1,"000000010000100000000111")){
			tempint[0]=bintonum(temp4);
			if(spreg[1]==0){
				spreg[2]=tempint[0];
				continue;
			}
			spreg[2]++;
			continue;
		}
		strcat(temp1,temp4);

		// HLT
		if(!strcmp(temp1,"00000001000010000000011000000000")){
			break;
		}
		spreg[2]++;
	}
	for(i=0;i<16;i++)
	{
		printf("%d ",reg[i]);
	}
	printf("\nneg: %d \nzero: %d \nprogram counter:%d\n",spreg[0],spreg[1],spreg[2]);
	printf("memeory is:\n");
	for(i=0;i<100;i++)
    {
        printf("%d ",mem[i]);
    }
	return 0;
}

int bintonum(char *c){
	int len,i,summer;
	len=strlen(c);
	int power=pow(2,len-1);
	summer=0;
	for(i=0;i<len;i++)
	{
		if(c[i]=='1') summer+=power;
		power/=2;
	}
	return summer;
}
