#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

char* preprocessor(char* path){
    FILE *fp = fopen(path, "r");
    if(fp == NULL){
        perror("fopen");
        exit(1);
    }
    bool in_string = false;
    int size = 1000;
    char* contents = calloc(1, size * sizeof(char));
    char* tmpptr;
    int i = 0;
    char c;
    while((c = fgetc(fp)) != EOF){
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
                    c = fgetc(fp);
                    if(c == '\n' || c == EOF){
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
                    c = fgetc(fp);
                    if(c == EOF){
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
    fclose(fp);
    contents[i] = '\0';
    return contents;
}
