#include<stdio.h>
#include "view.h"
#include<stdlib.h>
#include<string.h>

Status view_data(TagInfo *tagInfo)
{

    /* Opening source file */
    tagInfo->fptr_src=fopen(tagInfo->file_name,"r");

    if(tagInfo->fptr_src != NULL)
    {
	printf("INFO: Source mp3 file opened successfully\n");
    }
    else
    {
	printf("ERROR: Source file not opend!\n");
	return e_failure;
    }

    /* Check version */
    char version[3];
    fread(&version,1,3,tagInfo->fptr_src);
    printf("INFO: Mp3 version :- %s\n",version);

    /* Skip header data */
    fseek(tagInfo->fptr_src,10,SEEK_SET);

    printf("---------   ------------\n");
    printf("Tag Name    Tag Content:\n");
    printf("---------   ------------\n");

    /* run loop to get tags */
    for(int i=1;i<=6;i++)
    {
	/* initialize tagsize as 0 */
	tagInfo->tagSize=0;

	/* read 4 bytes tagid */
	fread(tagInfo->tagId,1,4,tagInfo->fptr_src);

	/* read 4 bytes of tagsize */
	fread(&tagInfo->tagSize,4,1,tagInfo->fptr_src);

	/* convert size from big to little endian */
	big_litt(&tagInfo->tagSize);

	/* skip 3 bytes */
	fseek(tagInfo->fptr_src,3,SEEK_CUR);

	/* allocate size times size */
	tagInfo->tagData=malloc((tagInfo->tagSize-1)*(sizeof(char)));

	/* read size times data and store */
	fread(tagInfo->tagData,tagInfo->tagSize-1,1,tagInfo->fptr_src);
	tagInfo->tagData[tagInfo->tagSize-1]='\0';

	/* calling function that will print tag and titles */
        print_tag_content(tagInfo->tagId,tagInfo->tagData,tagInfo->fptr_src);

	/* free allocated memory */
	free(tagInfo->tagData);
    }
    return e_success;
}

Status big_litt(uint *tagSize)
{
    /* convet big endian to little endian */
    *tagSize = (((*tagSize >> 24) & 0xff) | ((*tagSize << 8) & 0xff0000) | ((*tagSize >> 8) & 0xff00) | ((*tagSize << 24) & 0xff000000));
    return e_success;
}

Status print_tag_content(char* tagId,char *tagData,FILE *fptr_src)
{
    /* compare tagId with desired tags */
    /* if match found then print tag tile and data */
    if(strcmp(tagId,"TIT2")==0)
    {
	printf("Title\t:  %s\n",tagData);
    }
    else if(strcmp(tagId,"TPE1")==0)
    {
	printf("Artist\t:  %s\n",tagData);
    }
    else if(strcmp(tagId,"TALB")==0)
    {
	printf("Album\t:  %s\n",tagData);
    }
    else if(strcmp(tagId,"TYER")==0)
    {
	printf("Year\t:  %s\n",tagData);
    }
    else if(strcmp(tagId,"TCON")==0)
    {
	printf("Genre\t:  %s\n",tagData);
    }
    else if(strcmp(tagId,"COMM")==0)
    {
	printf("Comment\t:  %s\n",tagData);
    }
    else
    {
	return e_failure;
    }

    return e_success;
}
