/*
AUTH: Brian Howe

DESC: generates a file with the names of all files in the folder speeches.
The folder must be in same directory as this program.

*** Run with "./fListGen > output.txt" ***
*/

#include <stdio.h>
#include <dirent.h>
#include <string>
#include <algorithm>

using namespace std;

// prints the list
void print_files(string files[], int n) {
    int i;
    for(i = 0; i < n; i++) {
        printf("%s\n", files[i].c_str());
    }
}


int main() {

    DIR *dir;
    struct dirent *ent;
    string files[60]; // there are less than 60 speeches
    int i =0;

    if ((dir = opendir ("speeches/")) != NULL) {

        while ((ent = readdir (dir)) != NULL) {
            files[i] = ent->d_name;

            // only print if file extension is .txt
            if(files[i].substr(files[i].find_last_of(".") + 1) == "txt") {
                i++;
            }
        }
        closedir (dir);
    }
    else {
        /* could not open directory */
        perror ("Could not open directory.\n");
        return -1;
    }

    sort(files, files+i);

    print_files(files, i);

    return 0;
}
