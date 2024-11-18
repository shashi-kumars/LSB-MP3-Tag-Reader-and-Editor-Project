#include "edit.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

char tagId[4];
uint size;

Status do_edit(char *argv[],TagEdit *tagEdit)
{
    /* copy file name from arguments */
    strcpy(tagEdit->file_name,argv[2]);
    
    /* open the source file in read mode */
    tagEdit->fptr_src=fopen(tagEdit->file_name,"r");
    
    /* check the souce file opened successfully or not */
    if(tagEdit->fptr_src != NULL)
    {
	printf("INFO: Source file opened successfully.\n");
    }
    else
    {
	printf("ERROR: Source file unable to open.\n");
	return e_failure;
    }
    
    /* get the new data size */
    tagEdit->newDataSize=strlen(argv[4])+1;
    size=tagEdit->newDataSize;

    /* open the destination file in write mode */
    tagEdit->fptr_dest=fopen(tagEdit->dest_file,"w");

    /* check if the destination file opened or not */
    if(tagEdit->fptr_dest != NULL)
    {
	printf("INFO: Destination file opened successfully.\n");
    }
    else
    {
	printf("ERROR: Destination file unable to open.\n");
	return e_failure;
    }


    /* find and get tag which you want to chage */
    if(find_get_tag(argv[3],tagEdit->destTag))
    {
	printf("INFO: Destination tag id assigned succesfully.\n");
    }
    else
    {
	printf("Error: Destination tag not found.\n");
	return e_failure;
    }

    /* copy header */
    if(copy_data(tagEdit->fptr_src,tagEdit->fptr_dest,10))
    {
	printf("INFO: MP3 header copied successfully.\n");
    }
    else
    {
	printf("ERROR: MP3 header not copied.\n");
    }

    /* run loop for get tags */
    for(int i=0;i<6;i++)
    {
	/* read 4 bytes of tag from source file and write to destination file */
	fread(tagId,1,4,tagEdit->fptr_src);
	fwrite(tagId,1,4,tagEdit->fptr_dest);

	/* check if the tag is matched with given tag id */
	if(strcmp(tagId,tagEdit->destTag)==0)
	{
	    /* match found then read 4 bytes of size  */
	    fread(&tagEdit->tagSize,4,1,tagEdit->fptr_src);

	    /* convert that size from big to little endian */
	    big_litt_end(&tagEdit->tagSize);

	    /* convert new data size from little to big endian */
	    Little_big(&size);

	    /* write that new data size to destination file */
	    fwrite(&size,4,1,tagEdit->fptr_dest);

	    /* copy the 3 bytes data from soruce to destination file */
	    if(!copy_data(tagEdit->fptr_src,tagEdit->fptr_dest,3))
	    {
		printf("ERROR: Data not copied.\n");
		return e_failure;
	    }
	    
	    /* write the new data to destination file */
	    char ch;
	    for(int i=0; argv[4][i] != '\0';i++)
	    {
		ch=argv[4][i];
		fwrite(&ch,1,1,tagEdit->fptr_dest);
	    }

	    /* move offset to tagdata size */
	    fseek(tagEdit->fptr_src,tagEdit->tagSize-1,SEEK_CUR);
	    break;
	}
	else
	{
	    /* match not found read 4 bytes of size and write to destination file */
	    fread(&tagEdit->tagSize,4,1,tagEdit->fptr_src);
	    fwrite(&tagEdit->tagSize,4,1,tagEdit->fptr_dest);

	    /* convert big endian to little */
	    big_litt_end(&tagEdit->tagSize);

	    /* store size temperarly */
	    int temp=(tagEdit->tagSize)+2;

	    /* copy size + 2 bytes fo data from source to destinaion */
	    if(!copy_data(tagEdit->fptr_src,tagEdit->fptr_dest,temp))
	    {
		printf("ERROR: Data not copied.\n");
		return e_failure;
	    }   
	}
    }

    /* copy remaining data */
    if(Remain_data(tagEdit->fptr_src,tagEdit->fptr_dest))
    {
	printf("INFO: Ramaining data copied successfully.\n");
    }

    /* remove and rename source and destinaion files */
    remove(tagEdit->file_name);
    rename(tagEdit->dest_file,tagEdit->file_name);

    return e_success;
}

Status copy_data(FILE *fptr_src,FILE *fptr_dest,int size)
{
    /* read size bytes of data into buffer */
    /* wrte size bytes of data into destinaion file */
    char buffer[size];
    fread(buffer,1,size,fptr_src);
    fwrite(buffer,1,size,fptr_dest);
    return e_success;
}

Status big_litt_end(uint *tagSize)
{
    /* convert big to little endian */
    *tagSize = (((*tagSize >> 24) & 0xff) | ((*tagSize << 8) & 0xff0000) | ((*tagSize >> 8) & 0xff00) | ((*tagSize << 24) & 0xff000000));
    return e_success;
}

Status Remain_data(FILE *fptr_src,FILE *fptr_dest)
{
    /* run loop till end of file and read character */
    /* write character to destination */
    /* close the both files */
    char ch;
    while(fread(&ch,1,1,fptr_src) > 0)
    {
	fwrite(&ch,1,1,fptr_dest);
    }

    fclose(fptr_src);
    fclose(fptr_dest);
    return e_success;
}

Status find_get_tag(char *option,char *destTag)
{
    /* compare option with given option */
    /* if match found the copy that tagid to destTag */
    if(strcmp(option,"-t")==0)
    {
	strcpy(destTag,"TIT2");
	return e_success;
    }
    else if(strcmp(option,"-A")==0)
    {
	strcpy(destTag,"TPE1");
	return e_success;
    }
    else if(strcmp(option,"-a")==0)
    {
	strcpy(destTag,"TALB");
	return e_success;
    }
    else if(strcmp(option,"-y")==0)
    {
	strcpy(destTag,"TYER");
	return e_success;
    }
    else if(strcmp(option,"-g")==0)
    {
	strcpy(destTag,"TCON");
	return e_success;
    }
    else if(strcmp(option,"-c")==0)
    {
	strcpy(destTag,"COMM");
	return e_success;
    }
    return e_failure;
}
Status Little_big(uint *num)
{
    /* convert little to big endian */
    *num = ( ((*num >> 24) & 0xff) | ((*num << 8) & 0xff0000) |(( *num >> 8) & 0xff00) | ((*num << 24) & 0xff000000) );
    return e_success;
}
