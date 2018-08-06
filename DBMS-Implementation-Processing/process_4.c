#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXFIELDS 100
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
	char *e=buffer+strlen(buffer);
    	while(e>buffer&&*e=='\0'||*e=='\r'||*e=='\t'||*e=='\n'||*e==' '){
		*e='\0';
		e--;
   	}  
}


bool createTable(struct _table *table) {

	int i=0;
	char buf[MAXINPUTLENGTH];
	char *fileName;

	FILE *fp;
	char *extension=".schema";
	fileName=strcat(table->tableFileName, extension);

	if((fp=fopen(fileName, "wb"))!=NULL){
		while(fgets(buf, MAXINPUTLENGTH-1, stdin)){
			printf("===> %s", buf);
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

		fclose(fp);
		return true;
	}
	else{
		printf("Can't open schema file\n");
		return false;
	}
}
bool loadTable(struct _table *table){

	FILE *fp2;

	char *extension2=".bin";



	char *fileName2;
	char buf[MAXINPUTLENGTH];
	int i=0;


	fileName2=strcat(table->tableFileName, extension2);


	if((fp2=fopen(fileName2, "wb"))!=NULL){
		while(fgets(buf, MAXINPUTLENGTH-1, stdin)){
			trimwhitespace(buf);

			if (strlen(buf)<3){
			    break;
			}

			if(strcmp(buf, "END")==0){
				break;
			}
			printf("===> %s", buf);
			printf("\n");
			fwrite(&buf, MAXINPUTLENGTH, 1, fp2);
		}
	}
	else{
		printf("Can't open binary file.\n");
	}
	printf("===> END\n");

	fclose(fp2);
		
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
	printf("===> END\n");


	FILE *fp;
	FILE *fp2;
	char *extension=".schema";
	char *extension2=".bin";
	char tempFileName[30];

	char *fileName;
	char *fileName2;
	char buf[MAXINPUTLENGTH];
	char buf2[MAXINPUTLENGTH];

	strcpy(tempFileName, table->tableFileName);
	fileName=strcat(table->tableFileName, extension);
	fileName2=strcat(tempFileName, extension2);
	fp=fopen(fileName, "r");
	fp2=fopen(fileName2, "r");

int c;

if(fp2!=NULL){
	if(fp!=NULL){

	fread(buf, 1, MAXINPUTLENGTH, fp);
	if((c = fgetc(fp)) == EOF){
		printf("Table quotes does not exist.\n");
	}
	else{

		while(fread(buf2, 1, MAXINPUTLENGTH, fp2)){

			if(strlen(buf2)<1){break;}
			if(strcmp(buf2, "END")==0){
				break;
			}

				fseek(fp, 0, SEEK_SET);
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
}

	while(fgets(buf, MAXINPUTLENGTH-1, stdin)){
		break;
	}

	fclose(fp);
	fclose(fp2);
}

bool where_selectTable(struct _table *table, char *where_field_name, char *info){

	printf("===> END\n");

	FILE *fp;
	FILE *fp2;
	char *extension=".schema";
	char *extension2=".bin";
	char tempFileName[30];

	char *fileName;
	char *fileName2;
	char buf[MAXINPUTLENGTH];
	char buf2[MAXINPUTLENGTH];
	char tempBuf2[MAXINPUTLENGTH];

	int store_position=0;//store position
	int store_p;

	strcpy(tempFileName, table->tableFileName);
	fileName=strcat(table->tableFileName, extension);
	fileName2=strcat(tempFileName, extension2);
	fp=fopen(fileName, "r");
	fp2=fopen(fileName2, "r");

if(fp2!=NULL){

	if(fp!=NULL){

		while(fread(buf2, 1, MAXINPUTLENGTH, fp2)){
			strcpy(tempBuf2, buf2);

			if(strlen(buf2)<1){break;}
			if(strcmp(buf2, "END")==0){break;}

			if(strstr(buf2, info)==NULL){
				continue;
			}

				fseek(fp, 0, SEEK_SET);
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

	while(fgets(buf, MAXINPUTLENGTH-1, stdin)){
		break;
	}
	fclose(fp);
	fclose(fp2);
	return true;
}

void dropTable(struct _table *table){

	FILE *fp;
	FILE *fp2;
	char *extension=".schema";
	char *extension2=".bin";
	char tempFileName[30];

	char *fileName;
	char *fileName2;

	strcpy(tempFileName, table->tableFileName);
	fileName=strcat(table->tableFileName, extension);
	fileName2=strcat(tempFileName, extension2);
	fp=fopen(fileName, "w+");
	fp2=fopen(fileName2, "w+");

	if(fp!=NULL&fp2!=NULL){
		fclose(fp);
		fclose(fp2);
	}

}

void processCommand(char *buffer){
	char temppbuf[MAXINPUTLENGTH];

	char *p = strtok(buffer, " ");
	struct _table table;

	if(strcmp(p,"CREATE")==0){
		table.tableFileName=(char *)malloc(sizeof(char)*30);
		char *trash=strtok(NULL, " ");//Skip TABLE
		strcpy(table.tableFileName, strtok(NULL, "\r\n")); 
		createTable(&table);
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
			if(token==NULL){break;}
			strcpy(table.fields[i].fieldName, token);
		}

		while(fgets(buffer, MAXINPUTLENGTH-1, stdin)){
			printf("===> %s", buffer);
			char *token=strtok(buffer," ");
			if(token==NULL){break;}
			if(strcmp(token, "FROM")==0){
				strcpy(table.tableFileName, strtok(NULL, "\r\n"));	
				break;
			}
		}

	selectTable(&table);

		while(fgets(buffer, MAXINPUTLENGTH-1, stdin)){
			trimwhitespace(buffer);
			strcpy(temppbuf, buffer);

			char *p1=strtok(buffer, " ");
			if(p1==NULL){break;}
			printf("===> %s\n", temppbuf);

			if(strcmp(p1, "DROP")==0){
				memset(&table, 0, sizeof(struct _table));
				char *trash=strtok(NULL, " ");//Skip TABLE
				table.tableFileName=(char *)malloc(sizeof(char)*30);
				strcpy(table.tableFileName, strtok(NULL, "\r\n")); 
				dropTable(&table);
				break;

			}

			else if(strcmp(p1,"CREATE")==0){
				table.tableFileName=(char *)malloc(sizeof(char)*30);
				char *trash=strtok(NULL, " ");//Skip TABLE
				strcpy(table.tableFileName, strtok(NULL, "\r\n")); 
				createTable(&table);
				break;
			}

			else if(strcmp(p1, "SELECT")==0){
				memset(&table, 0, sizeof(struct _table));
		
				for(int i=0; i<MAXFIELDS; i++){
					char *token=strtok(NULL, ", ");	
					if(token==NULL){break;}
					strcpy(table.fields[i].fieldName, token);
				}
			}

			else if(strcmp(p1, "FROM")==0){
				table.tableFileName=(char *)malloc(sizeof(char)*30);
				strcpy(table.tableFileName, strtok(NULL, "\r\n"));
			}
			else if(strcmp(p1, "END")==0){
				break;
			}



			else if(strcmp(p1, "WHERE")==0){
				char *where_field_name=strtok(NULL, " \"");
				char *equal=strtok(NULL, " \"");//Skip equal symbol
				char *info=strtok(NULL, " \"\r\n");//Skip equal symbol
				where_selectTable(&table, where_field_name, info);
				break;
			}
		}

	}

	else if(strcmp(p, "DROP")==0){
		memset(&table, 0, sizeof(struct _table));
		char *trash=strtok(NULL, " ");//Skip TABLE
		table.tableFileName=(char *)malloc(sizeof(char)*30);
		strcpy(table.tableFileName, strtok(NULL, "\r\n")); 
		dropTable(&table);

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
