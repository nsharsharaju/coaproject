/*************************************************************************************/
/* 						Authors : 													 */
/* 						Mukul Jain (14UCS073)										 */
/* 						Anumala Rahul (14UCS021)									 */
/* 						Sri Harsha (14UCS074)										 */
/* 						Badal Sharma (14UCS030)										 */
/*																					 */
/*																					 */
/*																					 */
/*************************************************************************************/

//Changelog V0.3
//ADD Function added
//JNE function added



#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* OPCODEBIN(char* );//function to give the machine code of opcode
char* REGISTERBIN(char* );//function to give the machine code of registers

int main(){
	struct label{  //array of structures to store labels
		char lab[10];//member to store label ex.L0
		int count;//member to store where program has to jump
	};

	struct label labels[15];//creating array of label structure


	int i=0,z,k,j,check=0,l,v=0,w,pc,flag;

	char machine[100][100], machinetemp[100], *token, line[100][100],str[100],*token2;
	char s[] = " ";


	//Saving file text to an array

	FILE *fp;

	fp = fopen("input.txt", "rw");
    if (fp == NULL)
        exit(EXIT_FAILURE);//if file is not found exit of the program

    while (1) {
        if (fgets(line[i],150, fp) == NULL) break;//reading the file line by line until fgets returns null pointer
        j = 0;//for traversing till the end of string
        while(line[i][j] != '\n'){j++;}//increasing the value of j until we got enter
        line[i][j] = '\0';//ending the stirng with null character
        i++;

	}
	fclose(fp);

    printf("done\n");
	//pass 1,  making table for labels

	l=i;
	w=0;
	pc=0;
	for(i=0; i<l; i++,pc++){
		strcpy(str,line[i]);//coping the string in line[i] to str 
	    token = strtok(str, s);//dividing the string into parts

	   	while( token != NULL ){//if strtol gives NULL we will go to next line
				if(OPCODEBIN(token) == "countongod")//this function returns countongod if it can't find the opcode then it must be label
				{
					strcpy(labels[w].lab,token);//coping that into labels structure
					labels[w].count=pc;
					pc--;
					w++;
				}
			break;
		}
	}
	for(i=0;i<w;i++)
    {
        printf("%s %d\n",labels[i].lab,labels[i].count);
    }

	// pass 2 changing instruction to machine language

	v=0;
	for(i=0; i<l; i++,v++){
		check = 0;
		strcpy(str,line[i]);
	    token = strtok(str, s);

	   	while( token != NULL ){
		   	if(check==0){
				if(OPCODEBIN(token) == "countongod"){
					v--;
					break;
		   		}
		   		strcpy(machine[v],OPCODEBIN(token));
				check = 1;
				if(!strcmp("CMPI",token) || !strcmp("MOVI",token))
					k = 15;
				else
					k = 7;
			}
			token2=token;
			token = strtok(NULL, s);
			flag=0;
			if(!strcmp(token2,"JMP")||!strcmp(token2,"JG")||!strcmp(token2,"JL")||!strcmp(token2,"JE")||!strcmp(token2,"JNE"))
			{

				for(j=0;j<w;j++)
				{
					if(!strcmp(labels[j].lab,token))
					{
						flag=1;
						for (z = 7; z >= 0; z--){
						int n = labels[j].count;
					    k = n >> z;

					    if (k & 1)
					      strcat(machine[v],"1");
					    else
					      strcat(machine[v],"0");
						}
					}
				}
				if(flag==1)
					break;
			}
			if(flag==1) continue;
		   	if(token != NULL){
				if(token[0] == 'R' && (token[1]=='0'||token[1]=='1')){
			    	strcpy(machinetemp,REGISTERBIN(token));
			    	strcat(machine[v],machinetemp);
				}
				else{
					for (z = k; z >= 0; z--){
						int n = atoi(token);
					    k = n >> z;

					    if (k & 1)
					      strcat(machine[v],"1");
					    else
					      strcat(machine[v],"0");
					}
				}
			}

	    }
	}

	// final printing and creating output.txt file
	l=v;
	fp = fopen("output.txt", "w+");
	for(v=0; v<l;v++){
    	printf("%s\n", machine[v]);
    	fputs(machine[v],fp);

	}

}



//For opcodes

char* OPCODEBIN(char* key){

	char *OPCODETABLE[] = {
	        "00000000",
	        "00000010",
	        "0000000100000001",
	        "0000000100000010",
	        "0000000100000011",
	        "0000000100000100",
	        "0000000100000101",
	        "0000000100000110",
	        "00000011",
	        "000000010000100000000000",
	        "000000010000100000000001",
	        "000000010000100000000010",
	        "000000010000100000000011",
	        "000000010000100000000100",
	        "000000010000100000000101",
	        "000000010000100000000111",
	        "00000100",
	        "00000001000010000000011000000000"
	};


	    if(!strcmp(key, "MOD")) return OPCODETABLE[0];
	    if(!strcmp(key, "CMPI")) return OPCODETABLE[1];
	    if(!strcmp(key, "CMPR")) return OPCODETABLE[2];
	    if(!strcmp(key, "IN")) return OPCODETABLE[3];
	    if(!strcmp(key, "OUT")) return OPCODETABLE[4];
	    if(!strcmp(key, "STB")) return OPCODETABLE[5];
	    if(!strcmp(key, "LDB")) return OPCODETABLE[6];
	    if(!strcmp(key, "MOVR")) return OPCODETABLE[7];
	    if(!strcmp(key, "MOVI")) return OPCODETABLE[8];
	    if(!strcmp(key, "INC")) return OPCODETABLE[9];
	    if(!strcmp(key, "DEC")) return OPCODETABLE[10];
	    if(!strcmp(key, "JMP")) return OPCODETABLE[11];
	    if(!strcmp(key, "JG")) return OPCODETABLE[12];
	    if(!strcmp(key, "JL")) return OPCODETABLE[13];
	    if(!strcmp(key, "JE")) return OPCODETABLE[14];
	    if(!strcmp(key, "JNE")) return OPCODETABLE[15];
	    if(!strcmp(key, "ADD")) return OPCODETABLE[16];
	    if(!strcmp(key, "HLT")) return OPCODETABLE[17];
		else{
			return "countongod";
		}


}

//For register
char* REGISTERBIN(char* key){

char *REGISTERTABLE[] = {
	        "00000000",
	        "00000001",
	        "00000010",
	        "00000011",
	        "00000100",
	        "00000101",
	        "00000110",
	        "00000111",
	        "00001000",
	        "00001001",
	        "00001010",
	        "00001011",
	        "00001100",
	        "00001101",
	        "00001110",
	        "00001111"
	    };


	        if(!strcmp("R00",key)) return REGISTERTABLE[0] ;
	        if(!strcmp("R01",key)) return REGISTERTABLE[1] ;
	        if(!strcmp("R02",key)) return REGISTERTABLE[2] ;
	        if(!strcmp("R03",key)) return REGISTERTABLE[3] ;
	        if(!strcmp("R04",key)) return REGISTERTABLE[4] ;
	        if(!strcmp("R05",key)) return REGISTERTABLE[5] ;
	        if(!strcmp("R06",key)) return REGISTERTABLE[6] ;
	        if(!strcmp("R07",key)) return REGISTERTABLE[7] ;
	        if(!strcmp("R08",key)) return REGISTERTABLE[8] ;
	        if(!strcmp("R09",key)) return REGISTERTABLE[9] ;
	        if(!strcmp("R10",key)) return REGISTERTABLE[10] ;
	        if(!strcmp("R11",key)) return REGISTERTABLE[11] ;
	        if(!strcmp("R12",key)) return REGISTERTABLE[12] ;
	        if(!strcmp("R13",key)) return REGISTERTABLE[13] ;
	        if(!strcmp("R14",key)) return REGISTERTABLE[14] ;
	        if(!strcmp("R15",key)) return REGISTERTABLE[15] ;


}
