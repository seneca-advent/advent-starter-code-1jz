#include <cstdio>
#include <cstring>
#include <iostream>
#include "utils.h"

/* 
Function opens and reads the file named fname.  Each line is
read into line array (thus first line of file will be in line[0], second
in line[1] etc.). the newline at the end of the line is not stored into 
the string.  Function reads up to max lines.  Function returns number of
lines read.
*/
int readLines(const char* fname, char* line[],int max){
	FILE* fp=fopen(fname,"r");
	int rc=0;
	if(!fp){
		std::cout << "unable to open " << fname << std::endl;
		return 0;
	}
	else{
		size_t len;
		while(rc<max && getline(&line[rc], &len, fp)!=-1 ){
			//fscanf(fp,"%[^\n]\n",line[rc]);
			int lineLength=strlen(line[rc]);
			line[rc][lineLength-1]='\0';
			rc++;
		}
		fclose(fp);
	}
	return rc;

}
