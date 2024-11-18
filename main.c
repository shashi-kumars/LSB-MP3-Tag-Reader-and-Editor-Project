#include<stdio.h>
#include<string.h>
#include "view.h"
#include "edit.h"
#include "types.h"
/*
Name : Shashi kumar S
Date : 13-06-2024
Description : MP3 Tag reader and editer project
*/

int main(int argc,char *argv[])
{
    /* Creating structure variables */
    TagInfo tagInfo;
    TagEdit tagEdit;
    
    /* Check if the CLA is 1 then print promt */
    if(argc == 1)
    {
	printf("-----------------:Mp3 Tag Reader and Editor:-----------------------------\n");
	printf("ERROR : ./a.out : INVALID ARGUMENTS\n");
	printf("USAGE :\n");
	printf("To view please pass like : ./a.out -v mp3filename\n");
	printf("To get help pass like    : ./a.out -help\n");
	printf("To edit please pass like : ./a.out -e <mp3filename> <-option> new_data\n");
	printf("----------------------------------------------------------------------------\n");
	return 0;
    }
    /* check if the passed argument is view mode */
    else if(strcmp(argv[1],"-v")==0)
    {
	/* check the CLA if file is passed or not */
	if(argv[2]==NULL)
	{
	    printf("To view please pass like : ./a.out -v mp3filename\n");
	}
	else
	{
	    /* copy source file name to structure variable */
	    strcpy(tagInfo.file_name,argv[2]);
	    printf("INFO: You enterd view mode.\n");
	    
	    /* calling view data function */
	    if(view_data(&tagInfo))
	    {
		printf("INFO: All data viewed successfully.\n");
	    }
	}
    }
    /* check if the passed argument is edit mode */
    else if(strcmp(argv[1],"-e")==0)
    {
	/* check if the CLA count is 5 */
	if(argc != 5)
	{
	    printf("To edit please pass like : ./a.out -e <mp3filename> <-option> new_data\n");
	}
	else
	{
	    /* copy the destination file name as temp name */
	    strcpy(tagEdit.dest_file,"temp.mp3");

	    /* calling the do edit function  */
	    if(do_edit(argv,&tagEdit))
	    {
		printf("INFO: Data edited successfully.\n");
	    }
	}
    }
    /* check if the passed argument is help mode */
    else if(strncmp(argv[1],"-help",2)==0)
    {
	printf("--------------:Help Menu for Mp3 Tag Reader and Editor:-----------------\n");
	printf("To view please pass like : ./a.out -v mp3filename\n");
	printf("To edit please pass like : ./a.out -e <mp3filename> <-option> new_data\n");
	printf("INFO: Modifier Options:\n");
	printf("Tag\t: -Option\n");
	printf("----------------\n");
	printf("Title\t: -t\nArtist\t: -A\nAlbum\t: -a\nYear\t: -y\nGenre\t: -g\nComment\t: -c\n");
	printf("----------------------------------------------------------------------------\n");
    }

    return 0;
}  

