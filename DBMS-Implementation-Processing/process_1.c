#include <stdio.h>
#include <string.h>
#define DATABASENAME "database.bin"

struct _record{
	char id[50];
	char lname[50];
	char fname[50];
	char mname[50];
	char suffix[50];
	char dob[50];
	char gender[50];
	char ssnum[50];
	char address1[50];
	char address2[50];
	char zip[50];
	char maiden[50];
	char mrn[50];
	char city[50];
	char state[50];
	char phone1[50];
	char phone2[50];
	char email[50];
	char alias[50];
};

int loadDatabase(char *fileName);
int getRecord(char *fileName, int node, struct _record *info);
int showRecord(struct _record *info);
int changeRecord(char *fileName, int node, char *term, char *changeInfo);

int main() {
   if (loadDatabase(DATABASENAME)) {
      struct _record tmp;
      if (getRecord(DATABASENAME, 0, &tmp))
         showRecord(&tmp);
      if (getRecord(DATABASENAME, 4, &tmp))
         showRecord(&tmp);
      if (getRecord(DATABASENAME, 5, &tmp))
         showRecord(&tmp);
      if (changeRecord(DATABASENAME, 4, "lname", "Shaffer")) 
      	if (changeRecord(DATABASENAME, 4, "phone1", "814-555-1212"))
      		  if (getRecord(DATABASENAME, 4, &tmp))
                 showRecord(&tmp);
   }
   return 0;
}

int loadDatabase(char *fileName){
	printf("*** LOG: Loading database from input ***\n");
	FILE *fp;
	char buffer[300],temp[20];
	struct _record info;

	if((fp=fopen(fileName, "wb"))!=NULL){
			while(gets(buffer)){
				if (strlen(buffer)<1){
            				break;
			}
				strncpy(temp, buffer, 20);
       				temp[20] = 0;
       				printf("*** LOG: Parsing input data starting with [%s]\n", temp);
//-------------------------------------------------------------------------------------------------------
               
      			char *bufferToken = strtok(buffer, ",");      
				if(bufferToken){
					strcpy(info.id, bufferToken);
 					strcpy(info.lname, strtok(NULL, ","));    
 					strcpy(info.fname, strtok(NULL, ","));    
 			 		strcpy(info.mname, strtok(NULL, ","));     
 					strcpy(info.suffix, strtok(NULL, ","));     
			 		strcpy(info.dob, strtok(NULL, ","));    
			 		strcpy(info.gender, strtok(NULL, ","));    
 			 		strcpy(info.ssnum, strtok(NULL, ","));     
			 		strcpy(info.address1, strtok(NULL, ","));     
 					strcpy(info.address2, strtok(NULL, ","));     
 					strcpy(info.zip, strtok(NULL, ","));     
					strcpy(info.maiden, strtok(NULL, ","));     
					strcpy(info.mrn, strtok(NULL, ","));      
					strcpy(info.city, strtok(NULL, ","));     
					strcpy(info.state, strtok(NULL, ","));  
 					strcpy(info.phone1, strtok(NULL, ","));    
			 		strcpy(info.phone2, strtok(NULL, ","));  
 					strcpy(info.email, strtok(NULL, ","));   
  					strcpy(info.alias, strtok(NULL, ","));	
				
					fwrite(&info, sizeof(struct _record), 1, fp);
					printf("*** LOG: Appending record to database ***\n");
				}
			
			}

		fclose(fp);
		return 1;
	}
	else{
		printf("Can't open the file");
		return 0;
	}
}

int getRecord(char *fileName, int node, struct _record *info){
	FILE *fp;
	fp=fopen(fileName, "rb");
	fseek(fp, node*sizeof(struct _record), SEEK_SET);
	fread(info, sizeof(struct _record), 1, fp);
	printf("*** LOG: Getting record %d from the database ***\n", node);
	fclose(fp);
	return 1;

}

int showRecord(struct _record *info){
		printf("---------------------------------\n");
		printf("ID: %s\n", info->id);
		printf("Last name: %s\n", info->lname);
		printf("First name: %s\n", info->fname);
		printf("Middle name: %s\n", info->mname);
		printf("Suffix: %s\n", info->suffix);
		printf("Birth date: %s\n", info->dob);
		printf("Gender: %s\n", info->gender);
		printf("SS Num: %s\n", info->ssnum);
		printf("Address 1: %s\n", info->address1);
		printf("Address 2: %s\n", info->address2);
		printf("Zip: %s\n", info->zip);
		printf("Maiden: %s\n", info->maiden);
		printf("MRN: %s\n", info->mrn);
		printf("City: %s\n", info->city);
		printf("State: %s\n", info->state);
		printf("Phone 1: %s\n", info->phone1);
		printf("Phone 2: %s\n", info->phone2);
		printf("Email: %s\n", info->email);
		printf("Alias: %s\n", info->alias);
		printf("\n");
		return 0;
	
}


int changeRecord(char *fileName, int node, char *term, char *changeInfo){
	printf("*** LOG: Changing field %s in record %d to [%s] ***\n", term, node, changeInfo);
	FILE *fp;
	struct _record info;
   
	getRecord(fileName, node, &info);
	fp=fopen(fileName, "r+b");

	if(term=="lname"){
		strcpy(info.lname, changeInfo);
		fseek(fp, node*sizeof(struct _record), SEEK_SET);
		fwrite(&info, sizeof(struct _record), 1, fp);
		printf("*** LOG: Updating record %d in the database ***\n", node);
		fflush(fp);
		fclose(fp);	
		return 1;

	}
	else if (term=="phone1"){
		strcpy(info.phone1, changeInfo);
		fseek(fp, node*sizeof(struct _record), SEEK_SET);
		fwrite(&info, sizeof(struct _record), 1, fp);
		printf("*** LOG: Updating record %d in the database ***\n", node);
		fflush(fp);
		fclose(fp);	
		return 1;
	}	
}	
