/*
* Speech analyzer
*
* Class: CS 141, Spring 2014, Thurs 4pm lab.
* System: Linux Mint x64, g++
* Author: Brian Howe
*
* TODO: output is off for some speeches and singular nouns.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


struct speech_struct {
    char speaker[32];
    char date[32];
    int letters;
    int words;
    int sents;
    int parags;
    int sing;
    int plur;
} typedef SPEECH;

char *sing[7] = {(char*)"i", (char*)"i've", (char*)"i'll", (char*)"me",
                    (char*)"my", (char*)"mine", (char*)"myself"};
char *plur[7] = {(char*)"we", (char*)"we've", (char*)"we'll", (char*)"us",
                    (char*)"our", (char*)"ours", (char*)"ourselves"};

void print_heading(int num, char *s) {
    printf("Author: Brian Howe\n");
    printf("Lab: Thur 4pm\n");
    printf("Program: #%d, %s\n\n", num, s);
}


// changes teh size of a char array
char * resize(char *in, int n) {
    free(in);
    char *out = (char*)malloc(sizeof(char) * n);
    return out;
}


// finds all singular and plural pronouns
void pronouns(SPEECH *sData, char *word) {
    int i;
    for(i = 0; i < 7; i++) {
        if(strcmp(word, sing[i]) == 0) {
            sData->sing++;
        }
        else if(strcmp(word, plur[i]) == 0) {
            sData->plur++;
        }
    }
}


// analyzes all the content of the file (letters, words, paragaphs, etc.)
void get_data(SPEECH *sData, FILE *sFile) {
    char *all;

    // initialize values
    sData->letters = 0;
    sData->words = 0;
    sData->sents = 0;
    sData->parags = 1; // the last parag doesnt end in '\r'
    sData->sing = 0;
    sData->plur = 0;

    int n = 20000; // 20000 is an average amount of characters in the speeches
    all = (char*)malloc(sizeof(char) * n);

    do {
        fseek(sFile, SEEK_SET, 0); // go to beginning of file
        fread(all, sizeof(char), n, sFile); // read file to array 'all'

        if(!feof(sFile)) { // if all was to small to fit the file
            n+=1000; // increase size of all
            all = resize(all, n);
        }
    } while(!feof(sFile));

    char *word = strtok(all, " "); // read first word in file
    int lenWord, i;
    while(word != NULL) { // while there are still words in fill
        sData->words++;
        lenWord = strlen(word);

        for(i = 0; i < lenWord; i++) {
            if(isalpha(word[i])) {
                sData->letters++;
                word[i] = tolower(word[i]);
            }
            else if(word[i] == '.' || word[i] == '?') {
                sData->sents++;
            }
            else if(word[i] == '\r') {
                sData->parags++;
                i = lenWord; // avoids extra '\r'
            }
        }
        pronouns(sData, word);

        word = strtok(NULL, " "); // read next word
    }
}


// opens file and parses name. then calls get_data
void analyze(SPEECH *sData, char *path) {
    FILE *sFile; // the speech file

    sFile = fopen(path, "r"); // opens the speech
    if(sFile == NULL) {
        printf("Could not open %s.\n", path);
    }

    path = &path[10]; // removes datafiles/ from string

    char *tmp = path;
    while(tmp != NULL) { // changes all '_' to ' '
        tmp = strchr(path, '_');
        if(tmp != NULL) {
            *tmp = ' ';
        }
    }

    char *tmpN = strtok(path, "-"); // gets the speakers name
    char *tmpD = strtok(NULL, "."); // gets the date of speech

    strcpy(sData->speaker, tmpN);
    strcpy(sData->date, tmpD);

    get_data(sData, sFile);
}


// prints a char a specified amount
void print_char(char c, int n) {
    int i;
    for(i = 0; i <= n; i++) {
        printf("%c", c);
    }
}


// prints all speech data
void print_data(SPEECH s[], int n) {
    int i;
    printf("%26s | %15s | %6s | %6s | %6s | %6s | %6s | %6s | %6s| %6s| %7s|\n",
                                                            "Speaker",
                                                            "Date",
                                                            "Letrs",
                                                            "Words",
                                                            "Sents",
                                                            "Parags",
                                                            "Sing.",
                                                            "Plur.",
                                                            "Let/Wd",
                                                            "Wd/Snt",
                                                            "Sng/Plr");
    for(i = 0; i < n; i++) {
        if(i > 0 && strcmp(s[i-1].speaker, s[i].speaker) == 0) {
            printf("%2d.", i+1);
            print_char(' ', 23);
            printf("| ");
        }
        else{
            print_char('-', 125);
            printf("\n%2d.%23s | ", i+1, s[i].speaker);
        }

        printf("%15s | ", s[i].date);
        printf("%6d | ", s[i].letters);
        printf("%6d | ", s[i].words);
        printf("%6d | ", s[i].sents);
        printf("%6d | ", s[i].parags);
        printf("%6d | ", s[i].sing);
        printf("%6d |", s[i].plur);
        printf("%6d |", s[i].letters/s[i].words);
        printf("%6d |", s[i].words/s[i].sents);
        printf("%7.2f |", (double)s[i].sing/s[i].plur);
        printf("\n");
    }
}


int main() {
    FILE *speechList;
    SPEECH speeches[57];

    print_heading(4, (char*)"Inaugural Analysis");

    speechList = fopen("datafiles.txt", "r");
    if(speechList == NULL) {
        printf("Could not open file speeches.txt.\n");
        return -1;
    }

    int i = 0;
    char *tmp;
    char *buff = (char*) malloc(sizeof(char) * 128);
    while(!feof(speechList) && i < 57) {
        strcpy(buff, (char*)"datafiles/");
        fgets(&buff[10], 119, speechList);
        tmp = strchr(buff, '\n');
        if(tmp != NULL) {
            *tmp = '\0';
        }

        analyze(&speeches[i], buff);

        i++;
    }

    print_data(speeches, i);

    return 0;
}
