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
	char buf[MAXINPUTLENGTH];

	char temp_file_name[20];
	char temp_file_name2[20];
	char *file_name;
	char *file_name2;

	strcpy(temp_file_name, table->tableFileName);
	strcpy(temp_file_name2, table->tableFileName);

	FILE *fp;
	FILE *fp2;
	char *ext=".schema";
	char *ext2=".bin";
	file_name=strcat(temp_file_name, ext);
	file_name2=strcat(temp_file_name2, ext2);


	if((fp2=fopen(file_name2, "wb"))!=NULL){
		fclose(fp2);
	}
	else{
		printf("Can't open bin file\n");
		return false;
	}

	if((fp=fopen(file_name, "w"))!=NULL){
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
		}

		fclose(fp);
		return true;
	}
	else{
		printf("Can't open schema file\n");
		return false;
	}
}

bool insertInfo(char *insert_file_name, char *p1) {
	FILE *fp;
	char *file_name;
	char temp_buf[MAXINPUTLENGTH];
	strcpy(temp_buf, p1);

	char *ext=".bin";

	file_name=strcat(insert_file_name, ext);

	if((fp=fopen(file_name, "ab"))!=NULL){
		fwrite(&temp_buf, MAXINPUTLENGTH-1, 1, fp);
		fprintf(fp, "\n");
	}
	else{
		printf("Can't open bin file\n");
	}

	if(fclose(fp)==0){
		return true;
	}
	else{
		printf("Can't close bin file\n");
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
		createTable(&table);
	}
	else if(strcmp(p,"INSERT")==0){
		char *trash=strtok(NULL, " ");//Skip INto
		char *insert_file_name=strtok(NULL, " ");
		char *p1=strtok(NULL, "\0");
		insertInfo(insert_file_name, p1);
	}	
	else if(strcmp(p, "SELECT")==0){
		memset(&table, 0, sizeof(struct _table));//initial the table
		table.tableFileName=(char *)malloc(sizeof(char)*30);//alocate the sapce to filename
		
		for(int i=0; i<MAXFIELDS; i++){
			char *token=strtok(NULL, ", ");	
			if(token==NULL){break;}
			strcpy(table.fields[i].fieldName, token);
		}

		while(fgets(buffer, MAXINPUTLENGTH-1, stdin)){
			     	trimwhitespace(buffer);
			printf("===> %s\n", buffer);
			char *token=strtok(buffer," ");
			if(token==NULL){break;}
			if(strcmp(token, "FROM")==0){
				strcpy(table.tableFileName, strtok(NULL, "\0"));	
				break;
			}
		}

		selectTable(&table);
		fgets(buffer, MAXINPUTLENGTH-1, stdin);
			     	trimwhitespace(buffer);
		if(strcmp(buffer, "END")){return;}
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
