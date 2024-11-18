#include "types.h"
#include<stdio.h>

typedef struct _TagEdit
{
    /* file info */
    char file_name[50];
    FILE *fptr_src;

    /* dest file */
    char dest_file[50];
    FILE *fptr_dest;

    /* tag infomation */
    uint tagSize;

    /* new data */
    char destTag[4];
    uint newDataSize;

}TagEdit;
/* function prototype */

/* function to edit tag */
Status do_edit(char *argv[],TagEdit *tagEdit);

/* function to find and get the tag */
Status find_get_tag(char *optin,char *tagId);

/* function to copy data from source to destination file with size */
Status copy_data(FILE *fptr_src,FILE *fptr_dest,int size);

/* function to convert big to little edian */
Status big_litt_end(uint *tagSize);

/* function to convert little to big endian */
Status Little_big(uint *tagSize);

/* function to copy remaining data */
Status Remain_data(FILE *fptr_src,FILE *fptr_dest);


