#include <stdio.h> 
#include <dirent.h> 
#include <string.h>
#include <stdlib.h>
  
int main(int argc, char *argv[])
{ 
    char **dirs_to_read = NULL;
    int ndirs = 0;
    int dirindex = 0;
    char *default_dir = malloc(sizeof(char) * 2);
    strcpy(default_dir, ".");
    if (argc <= 1) {
        dirs_to_read = &default_dir;
        ndirs = 1;
    } else {
        dirs_to_read = argv + 1;
        ndirs = argc - 1;
    }
    struct dirent *de;  // Pointer for directory entry 
    DIR *dr = NULL;
  
    // opendir() returns a pointer of DIR type.  
    for (dirindex = 0; dirindex < ndirs; dirindex++) {
        dr = opendir(dirs_to_read[dirindex]); 
      
        if (dr == NULL)  // opendir returns NULL if couldn't open directory 
        { 
            printf("Could not open current directory" ); 
            return 0; 
        } 
      
        // Refer http://pubs.opengroup.org/onlinepubs/7990989775/xsh/readdir.html 
        // for readdir() 
        while ((de = readdir(dr)) != NULL) 
                printf("%s\n", de->d_name); 
      
        closedir(dr);     
    }
    free(default_dir);
    return 0; 
} 

