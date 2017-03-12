#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#ifndef __PREPROCESSOR_H_
    #include "preprocessor.h"
#endif


char *input(char *dest, unsigned long long size){
    int i = 0;
    while(1){
        dest[i] = getchar();
        if(i >= size){
            size += 20;
            dest = realloc(dest, size);
        }
        if(dest[i] == '\n'){
            dest[i] = '\0';
            break;
        }
        i++;
    }
    return dest;
}

char *finput(char *dest, char *path, unsigned long long size){
    int i = 0;
    char c;
    FILE *fp = fopen(path, "r");
    if(fp == NULL){
        perror("fopen");
        exit(1);
    }
    while((c= fgetc(fp)) != EOF){
        dest[i] = c;
        if(i >= size){
            size += 20;
            dest = realloc(dest, size);
        }
        if(dest[i] == EOF){
            dest[i] = '\0';
            break;
        }
        i++;
    }
    fclose(fp);
    dest[i] = '\0';
    return dest;
}

char* preprocessor(char *buffer){
    bool in_string = false;
    int size = strlen(buffer) + 1;
    char* contents = calloc(1, size * sizeof(char));
    char* tmpptr;
    int i = 0;
    char c;
    while((c = buffer[i]) != '\0'){
        if(size - i < 10){
            size += 10;
            tmpptr = realloc(contents, size);
            if(tmpptr != NULL){
                contents = tmpptr;
            }
        }
        if(c == '\"'){
            if(i > 0){
                if(contents[i-1] != '\\' && in_string == false){
                    in_string = true;
                    contents[i++] = c;
                }
                else{
                    in_string = false;
                    contents[i++] = c;
                }
            }
            else{
                contents[i++] = c;
            }
            continue;
        }
        else{
            contents[i++] = c;
        }
        if(i > 1){
            if(contents[i-2] == '/' && contents[i-1] == '/' && in_string == false){
                i -= 2;
                while(1){
                    c = buffer[i];
                    if(c == '\n' || c == '\0'){
                        break;
                    }
                }
                contents[i++] = '\n';
                continue;
            }
            else if(contents[i-1] == '*' && contents[i-2] == '/' && in_string == false){
                i -= 2;
                char a = 'a';
                while(1){
                    a = c;
                    if(size - i < 10){
                        size += 10;
                        tmpptr = realloc(contents, size);
                        if(tmpptr != NULL){
                            contents = tmpptr;
                        }
                    }
                    c = buffer[i++];
                    if(c == '\0'){
                        puts("Unexpected EOF: comment was not closed.");
                        exit(1);
                    }
                    else if(c == '/' && a == '*'){
                        break;
                    }
                    else if(c == '\n'){
                        contents[i++] = '\n';
                    }
                }
            }
            continue;
        }
    }
    //contents[i] = '\0';
    //puts(contents);
    return contents;
}
