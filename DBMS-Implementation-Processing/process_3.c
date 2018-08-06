#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXFIELDS 100 // for now
#define MAXINPUTLENGTH 5000
#define MAXLENOFFIELDNAMES 50
#define MAXLENOFFIELDTYPES 50
struct _field {
	char fieldName[MAXLENOFFIELDNAMES];
 	char fieldType[MAXLENOFFIELDTYPES];
 	int fieldLength;
};
struct _table {
	char *tableFileName;
	int reclen;
	int fieldcount;
	struct _field fields[MAXFIELDS]; 
};
typedef enum{false, true} bool;


void trimwhitespace(char *buffer){
	//strtok(buffer,"\r\n");
	char *e=buffer+strlen(buffer);
    	while(e>buffer&&*e=='\0'||*e=='\r'||*e=='\t'||*e=='\n'||*e==' '){
		*e='\0';
		e--;
   	}  
}
// READ THE DATA FROM STDIN AS THE DESIGN OF THE DATABASE TABLE
// LOAD "table" WITH THE APPROPRIATE INFO
bool loadSchema(struct _table *table) {
	printf("*** LOG: Creating table...\n");
	printf("*** LOG: Loading table fields...\n");
	int i=0;
	char buf[MAXINPUTLENGTH];
	char *fileName;
	//table->reclen=0;

	printf("*** LOG: Table data name is [%s.bin]\n", table->tableFileName);
	printf("*** LOG: Table schema name is [%s.schema]\n", table->tableFileName);

	FILE *fp;
	char *extension=".schema";
	fileName=strcat(table->tableFileName, extension);

	if((fp=fopen(fileName, "wb"))!=NULL){
		while(fgets(buf, MAXINPUTLENGTH-1, stdin)){
			char *p=strtok(buf, " ");
			if (strcmp(p,"END")==0){
			    break;
			}

			else if(strcmp(p,"ADD")==0){
				strcpy(buf, strtok(NULL, "\r\n"));
				fwrite(&buf, MAXINPUTLENGTH, 1, fp);
			}
			else{
				break;
			}

			i++;
		}
	
		table->fieldcount=i;
		printf("*** LOG: END OF CREATE TABLE\n");
		fclose(fp);
		return true;
	}
	else{
		printf("Can't open schema file\n");
		return false;
	}
}
bool loadTable(struct _table *table){
	FILE *fp;
	FILE *fp2;
	char *extension=".schema";
	char *extension2=".bin";
	char temp[20];
	char tempFileName[30];
	char *fileName;
	char *fileName2;
	char buf[MAXINPUTLENGTH];
	int i=0;

	printf("----------- SCHEMA --------------\n");
	printf("TABLE NAME: %s\n", table->tableFileName);
	strcpy(tempFileName, table->tableFileName);
	fileName=strcat(table->tableFileName, extension);
	fileName2=strcat(tempFileName, extension2);

	if((fp=fopen(fileName, "r"))!=NULL){
		while(fscanf(fp, "%s %s %d\n", table->fields[i].fieldName, table->fields[i].fieldType, &table->fields[i].fieldLength)==3){
			printf("--- %s (%s-%d)\n", table->fields[i].fieldName, table->fields[i].fieldType, table->fields[i].fieldLength);

			i++;
			fseek(fp, i*MAXINPUTLENGTH, SEEK_SET);
		}
	}
	else{
		printf("Can't open schema file\n");
	}
	
	printf("*** LOG: Loading database from input ***\n");
	if((fp2=fopen(fileName2, "wb"))!=NULL){
		while(fgets(buf, MAXINPUTLENGTH-1, stdin)){
			if (strlen(buf)<3){
			    break;
			}
			if(strcmp(buf, "END\n")==0){
				break;
			}
			fwrite(&buf, MAXINPUTLENGTH, 1, fp2);

			strncpy(temp, buf, 20);
	 	      	temp[20] = 0;
	 	      	printf("*** LOG: Loading input data starting with [%s]\n", temp);
		}
	}
	else{
		printf("Can't open binary file.\n");
	}


	if((fclose(fp)==0)&(fclose(fp2)==0)){
		printf("*** LOG: Closing file\n");
	}
	else{
		printf("Failure to close\n");
	}
		
}

int getRecord(int i, char *buff){
	char tempBuf[MAXINPUTLENGTH];
	int sign_for_zero=0;
	
	strcpy(tempBuf, buff);


	char *p=strtok(tempBuf, ",");
	if(i==sign_for_zero){
		printf("%s", p);
	}
	else{
		for(int j=1; j<i; j++){
			strtok(NULL, "\r\n,");
		}
		char *token=strtok(NULL, "\r\n,");
     		trimwhitespace(token);
		printf("%s", token);
	}
	return 0;

}
bool selectTable(struct _table *table){
	//int i=0;
	FILE *fp;
	FILE *fp2;
	char *extension=".schema";
	char *extension2=".bin";
	char tempFileName[30];

	//char scanField[30];
	char *fileName;
	char *fileName2;
	char buf[MAXINPUTLENGTH];
	char buf2[MAXINPUTLENGTH];

	strcpy(tempFileName, table->tableFileName);
	fileName=strcat(table->tableFileName, extension);
	fileName2=strcat(tempFileName, extension2);
	fp=fopen(fileName, "r");
	fp2=fopen(fileName2, "r");
int k=0;

if(fp2!=NULL){
	if(fp!=NULL){
		while(fread(buf2, 1, MAXINPUTLENGTH, fp2)){
			if(strlen(buf2)<1){break;}
//FIND MATCHING ITEM
				fseek(fp, 0, SEEK_SET);//SET THE CURSOR to the beginning of file in .schema file.
				int i=0;
				while(fread(buf, 1, MAXINPUTLENGTH, fp)){
					if(strlen(buf)<1){break;}
					char *p=strtok(buf, " ");

			
					for(int j=0; j<MAXFIELDS; j++){
						if(strcmp(p, table->fields[j].fieldName)==0){
							getRecord(i, buf2);
							putchar(' ');
						}
					}
					i++;

				}

			putchar('\n');	
		}

	}
}
	fclose(fp);
	fclose(fp2);
}

void processCommand(char *buffer){

	char *p = strtok(buffer, " ");
	struct _table table;

	if(strcmp(p,"CREATE")==0){
		table.tableFileName=(char *)malloc(sizeof(char)*30);
		char *trash=strtok(NULL, " ");//Skip TABLE
		strcpy(table.tableFileName, strtok(NULL, "\r\n")); 
		loadSchema(&table);
	}
	else if(strcmp(p,"LOAD")==0){
		table.tableFileName=(char *)malloc(sizeof(char)*30);
		char *trash=strtok(NULL, " ");//Skip TABLE
		strcpy(table.tableFileName, strtok(NULL, "\r\n")); 
		loadTable(&table);

	}

	else if(strcmp(p, "SELECT")==0){

		table.tableFileName=(char *)malloc(sizeof(char)*30);
		
		for(int i=0; i<MAXFIELDS; i++){
			char *token=strtok(NULL, ", ");

			if(strcmp(token, "FROM")==0){
				strcpy(table.tableFileName, strtok(NULL, "\r\n"));
				break;
			}
			else{
				strcpy(table.fields[i].fieldName, token);
			}
		}

	selectTable(&table);
	}
}


int main() {
	static char buffer[MAXINPUTLENGTH];
	memset(buffer, 0, MAXINPUTLENGTH);
 	printf("Welcome!\n");
 	char *status = fgets(buffer, MAXINPUTLENGTH-1, stdin); 
	while (status != NULL) {
     	trimwhitespace(buffer);
     	if (strlen(buffer) < 5)
         	break; // not a real command, CR/LF, extra line, etc.
     	printf("===> %s\n", buffer);
		processCommand(buffer);
 		status = fgets(buffer, MAXINPUTLENGTH-1, stdin); 
    }     
 	printf("Goodbye!\n");
 	return 0;
}
