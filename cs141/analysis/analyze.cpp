/*
 AUTH: Brian Howe

 DESC: anaylize the inagural speeches of the presidents

 TODO: out put is fucked. fix get_data and make it so print_data
       can print the name and date.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


struct speech_struct {
    char *speaker;
    char *date;
    int letters;
    int words;
    int sents;
    int parags;
} typedef SPEECH;


void print_heading(int num, char *s) {
    printf("Author: Brian Howe\n");
    printf("Lab: Thur 4pm\n");
    printf("Program: #%d, %s\n\n", num, s);
}


char * resize(char *in, int n) {
    free(in);
    char *out = (char*)malloc(sizeof(char) * n);
    return out;
}


void get_data(SPEECH sData, FILE *sFile) {
    char *all;

    sData.letters = 0;
    sData.words = 0;
    sData.sents = 0;
    sData.parags = 0;

    int n = 20000;
    all = (char*)malloc(sizeof(char) * n);
    do {
        fseek(sFile, SEEK_SET, 0); // go to beginning of file
        fread(all, sizeof(char), n, sFile); // read file to array 'all'
        if(!feof(sFile)) { // if all was to small to fit the file
            n+=200; // increase size of all
            all = resize(all, n);
        }
    } while(!feof(sFile));

    char *word = strtok(all, " "); // read first word in file
    int lenWord, i;
    while(word != NULL) { // while there are still words in fill
        lenWord = strlen(word);

        for(i = 0; i < lenWord; i++) {
            if(isalpha(word[i])) {
                sData.letters++;
            }
            else if(word[i] == ' ') {
                sData.words++;
            }
            else if(word[i] == '.') {
                sData.sents++;
            }
            else if(word[i] == '\r') {
                sData.parags++;
            }
        }

        word = strtok(NULL, " "); // read next word
    }
}


void analyze(SPEECH sData, char *path) {
    FILE *sFile; // the speech file

    sFile = fopen(path, "r"); // opens the speech
    if(sFile == NULL) {
        printf("Could not open %s.\n", path);
    }

    path = &path[9]; // removes speeches/ from string

    char *tmp = path;
    while(tmp != NULL) { // changes all '_' to ' '
        tmp = strchr(path, '_');
        if(tmp != NULL) {
            *tmp = ' ';
        }
    }

    char *tmpN = strtok(path, "-"); // gets the speakers name
    char *tmpD = strtok(NULL, "."); // gets the date of speech

    sData.speaker =  (char*)malloc(sizeof(char) * strlen(tmpN));
    sData.date = (char*)malloc(sizeof(char) * strlen(tmpD));

    strcpy(sData.speaker, tmpN);
    strcpy(sData.date, tmpD);

    get_data(sData, sFile);
}


void print_data(SPEECH s[], int n) {
    int i;
    for(i = 0; i < n; i++) {
       // printf("%40s | ", s[i].speaker);
       // printf("%20s | ", s[i].date);
        printf("%10d | ", s[i].letters);
        printf("%10d | ", s[i].words);
        printf("%8d | ", s[i].sents);
        printf("%6d", s[i].parags);
        printf("\n");
    }
}


int main() {
    FILE *speechList;
    SPEECH speeches[57];

    print_heading(4, (char*)"Inaugural Analysis");

    speechList = fopen("speeches.txt", "r");
    if(speechList == NULL) {
        printf("Could not open file speeches.txt.\n");
        return -1;
    }

    int i = 0;
    int j;
    char *tmp;
    char *buff = (char*) malloc(sizeof(char) * 128);
    while(!feof(speechList) && i < 57) {
        strcpy(buff, (char*)"speeches/");
        fgets(&buff[9], 119, speechList);
        tmp = strchr(buff, '\n');
        if(tmp != NULL) {
            *tmp = '\0';
        }
        analyze(speeches[i], buff);
        i++;
    }

    print_data(speeches, 57);

    return 0;
}
