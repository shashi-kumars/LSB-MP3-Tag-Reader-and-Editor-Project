#include "types.h"
#include<stdio.h>

typedef struct _TagInfo
{
    /* file info */
    char file_name[50];
    FILE *fptr_src;

    /* tag infomation */
    char tagId[5];
    uint tagSize;
    char *tagData;

}TagInfo;

/* function to displat content */
Status view_data(TagInfo *tagInfo);

/* function to open file */
Status openfile(TagInfo *tagInfo);

/* function to convert big edian to little */
Status big_litt(uint *tagSize);

/* function to print data */
Status print_tag_content(char *tagId,char *tagData,FILE *fptr_src);



