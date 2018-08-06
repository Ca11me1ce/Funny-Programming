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


// READ FROM STDIN AND WRITE THE RECORDS TO THE DATABASE FILE
// THE DATABASE FILE MUST BE CALLED [table name].bin <-- where "table name" 
// is the table named in the schema
// BE CERTAIN TO WRITE THESE IN THE FORMAT AS SPECIFIED BY THE SCHEMA
// MAKE SURE THAT THE DATA LENGTHS DO NOT TRASH YOUR FILE!
// Note that I made the design decision to store the string
// null terminators in the file. 

bool loadDatabase(struct _table *table) {
	printf("*** LOG: Loading database from input ***\n");
	FILE *fp;
	char *extension=".bin";
	char buffer[table->reclen],temp[20], *fileName;
	int i;
	fileName=strcat(table->tableFileName, extension);

	if((fp=fopen(fileName, "wb"))!=NULL){
				while(gets(buffer)){
					if (strlen(buffer)<1){
		    				break;
					}
					strncpy(temp, buffer, 20);
	       				temp[20] = 0;
	       				printf("*** LOG: Loading input data starting with [%s]\n", temp);
					fwrite(&buffer, sizeof(buffer), 1, fp);

					char *p = strtok(buffer, ",");
					for(i=1; i<table->fieldcount; i++){
						char *token=strtok(NULL, ",");
						if((strlen(token))>(table->fields[i].fieldLength)){
							printf("*** WARNING: Data in field %s is being truncated ***\n", table->fields[i].fieldName);
						}
						else{continue;}
					}
				}
			printf("*** LOG: Closing file\n");

			fclose(fp);
			return 1;
		}
		else{
			printf("Can't open the file");
			return 0;
		}
}
// READ THE DATA FROM STDIN AS THE DESIGN OF THE DATABASE TABLE
// LOAD "table" WITH THE APPROPRIATE INFO
bool loadSchema(struct _table *table) {
	printf("*** LOG: Loading table fields...\n");
	int i=0;
	char buffer[300];
	char trashCan[10];
	table->reclen=0;
	table->tableFileName=(char *)malloc(sizeof(char)*10);
	scanf("CREATE TABLE %s\n", table->tableFileName);
	printf("*** LOG: Table name is [%s.bin]\n", table->tableFileName);

	while((scanf("ADD %s %s %d\n", table->fields[i].fieldName, table->fields[i].fieldType, &table->fields[i].fieldLength))==3){
		printf("*** LOG: ADDING FIELD [%s] [%s] [%d]\n", table->fields[i].fieldName, table->fields[i].fieldType, table->fields[i].fieldLength);
		(table->reclen)=(table->reclen)+(table->fields[i].fieldLength);
		i++;
	}

	printf("*** LOG: END OF CREATE TABLE\n");

	table->fieldcount=i;
	printf("*** LOG: %d Fields loaded\n", table->fieldcount);
	printf("*** LOG: Total record length is %d\n", table->reclen);

	if(scanf("%s\n", trashCan)==1){//skip "END"
		return true;
	}
}
// GET THE RECORD FROM THE FILE BY FSEEKING TO THE RIGHT SPOT AND READING IT
bool getRecord(int recnum, char *record, struct _table *table){
	printf("*** LOG: Getting record %d from the database ***\n", recnum);
	FILE *fp;
	fp=fopen(table->tableFileName, "rb");
	fseek(fp, recnum*table->reclen, SEEK_SET);
	fread(record, table->reclen, 1, fp);
	if(record!=NULL){
		fclose(fp);
		return true;
	}
	else{
		return false;
	}
}
// DISPLAY THE CURRENT RECORD USING THE ASSOCIATED FIELD NAMES
void showRecord(struct _field *fields, char *record, int fieldcount){
	printf("----------- RECORD --------------\n");
	int i;
	char *p = strtok(record, ",");
	printf("--- %s: [%s]\n", fields[0].fieldName, p);
	for(i=1; i<fieldcount; i++){
		char *token=strtok(NULL, ",");
		if((strlen(token))<=(fields[i].fieldLength)){
			printf("--- %s: [%s]\n", fields[i].fieldName, token);
		}
		else{
			char temp[(fields->fieldLength)-1];
			strncpy(temp, token, (fields[i].fieldLength)-1);
       			temp[(fields[i].fieldLength)-1] = 0;
			printf("--- %s: [%s]\n", fields[i].fieldName, temp);
		}
	}
}

int main() {
	struct _table table;
 	loadSchema(&table);
	loadDatabase(&table);

 	char *record = calloc(1, table.reclen);
	if (record == NULL) 
		printf("\n\n**** ERROR OUT OF MEMORY ***\n\n");
    else {
     	if (getRecord(4, record, &table))
     		showRecord(table.fields, record, table.fieldcount);
     	if (getRecord(10, record, &table))
     		showRecord(table.fields, record, table.fieldcount);
    }
 	return 0;
}
