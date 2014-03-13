/*
 AUTH: Brian Howe

 DESC: generates a file with the names of all files in the folder speeches.
       The folder must be in same directory as this program.

 *** Run with "./fListGen > output.txt" ***
*/

#include <stdio.h>
#include <dirent.h>
#include <string>

int main() {

    DIR *dir;
    struct dirent *ent;

    if ((dir = opendir ("speeches/")) != NULL) {
        /* print all the files and directories within directory */
        while ((ent = readdir (dir)) != NULL) {
            std::string file = ent->d_name;

            // only print if file extension is .txt
            if(file.substr(file.find_last_of(".") + 1) == "txt") {
                printf ("%s\n", ent->d_name);
            }
        }
        closedir (dir);
    }
    else {
        /* could not open directory */
        perror ("");
        return -1;
    }

    return 0;
}
