#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
/*
 * Function that finds length of string.
 */
int length_of_string(char string[]){
    int i = 0;
    while(string[i] != '\0' ){
        i++;
    }
    return i-1; //-1 because last character is new line, and we don`t need it.
}
/*
 * Function for comparing two strings. Used for checking if flag was correctly written.
 */
bool same_strings(char string_1[],char string_2[]){
    if(length_of_string(string_1) != length_of_string(string_2)){
        return false;
    }
    for(int i = 0; i < length_of_string(string_1) ; i++ ){
        if(string_1[i] != string_2[i]){
            return false;
        }
    }
    return true;
}
/*
 * Function for which will tell you if char is in range of characters.
 * Returns True or False.
 */
bool range_in_string(char string[],char start,char end){
    for(int i = 0 ; string[i] != '\n' ; i++ ){
        if((string[i] >= start) && (string[i] <= end)) {
            return true;
        }
    }
    return false;
}
/*
 * Function made for Level 1 which calls function range_in_string and asks her if there are both lower_case and upper_case letters in password.
 * Returns True or False.
 */
bool Level_1(char string[]){
    return ((range_in_string(string,'a','z'))&&(range_in_string(string,'A','Z')));
}
/*
 * Function made for Level 2 which calls function range_in_string as well but this time it checks in how many intervals does the characters
 * from a string appears and then compares it with argument parameter.
 * Returns True or False.
 */
bool Level_2(char string[],int number_of_groups){
    int helper = 0;
    helper+= range_in_string(string, 'a', 'z');
    helper+= range_in_string(string, 'A', 'Z');
    helper+= range_in_string(string, '0', '9');
    helper+= (range_in_string(string, ' ', '/') || range_in_string(string, ':', '@') || range_in_string(string, '[', '`') || range_in_string(string, '{', '~'));
    return ((helper>=number_of_groups)||((number_of_groups>4)&&(helper==4)));
}
/*
 * Function made for Level 3 which compares how many same characters are there in a row and then check if the chain of characters is bigger
 * than argument parameter.
 * Returns True or False.
 */
bool Level_3(char string[],int length_of_chain){
    int max = 0;
    int helper = 1;
    for(int i = 1; string[i] != '\0'; i++){
        if (string[i]==string[i-1]){
            helper++;
        }
        else{
            if(helper>max){
                max=helper;
                helper=1;
            }
        }
    }
    return (max<length_of_chain);
}
/*
 * Function is searching for same characters in the string, when same characters is found, function is checking if there are same characters
 * behind him as well, when there is a character helper will count a pair until there are no more. Then it will compare it with integer max
 * and at the end it will return true if the max is lower than argument parameter.
 * Returns True or False.
 */
bool Level_4(char string[],int length_of_substring){
    int max = 0;
    int helper = 0;
    for(int x = 0; string[x] != '\0'; x++){
        for(int y = x+1; string[y] != '\0'; y++){
            for(int z = 0; z <= length_of_substring; z++){
                if(string[x+z] == string[y+z]){
                    helper++;
                }
                else{
                    if(helper > max){
                        max = helper;
                    }
                    helper = 0;
                    z = length_of_substring;

                }
            }
        }
    }
    return (length_of_substring>max);
}
/*
 * Function that calls Level function and then checks if the password does pass the security level.
 * If password passes the level returns True otherwise False is returned.
 */
bool Level_Checker(char string[],int level,int parameter){
    int helper = 1;
    for(int i = 1; i <= level; i++){
        switch(i){
            case 1:
                helper *= Level_1(string);
                break;
            case 2:
                helper *= Level_2(string,parameter);
                break;
            case 3:
                helper *= Level_3(string,parameter);
                break;
            case 4:
                helper *= Level_4(string,parameter);
                break;
        }
    }
    return helper;
}
/*
 * Function that counts how many characters are in string
 * Function returns number of characters
 */
int characters_counter(int array[]){
    int counter = 0;
    for(int i = 0; i < 128 ; i++){
        if(array[i]>0){
            counter++;
        }
    }
    return counter;
}
/*
 * Function that compares two passwords, then returns shortest
 */
int comparing_len_password(int password_length, int shortest){
    if(password_length < shortest){
        return password_length;
    }
    return shortest;
}
/*
 * Run with ./pwcheck [Level: 1-4] [Parameter: >=1] [--stats] 
 */
int main(int argc,char *argv[]) {
    int level = atoi(argv[1]);
    int parameter = atoi(argv[2]);
    int number_of_passwords = 0;
    double length_of_all_passwords = 0;
    int characters[128] = {0};
    int shortest_password = 100;
    bool stats = false;
    /*
     * Errors Settings Start
     */
    if(argc < 3) {
        fprintf(stderr, "Not enough arguments received, arguments received: %d \n", argc-1);
        return 1;
    }
    if((level < 1) || (level >4 )){
        fprintf( stderr, "Invalid value in argument, argument value of level can be only from interval 1-4 not: %d \n" , level);
        return 1;
    }
    if(parameter < 1){
        fprintf( stderr, "Invalid value in argument, argument value of parameter can be only from interval positive numbers, which is not: %d \n" , parameter);
        return 1;
    }
    if(argc == 4) {
        if (!(same_strings(argv[3], "--stats"))) {
            fprintf(stderr, "Invalid flag, was looking for --stats found: %s \n", argv[3]);
            return 1;
        }
        stats = true;
    }
    if(argc > 4){
        fprintf(stderr, "More arguments gave then needed, arguments given: %d \n", argc-1);
        return 1;
    }
    /*
     * Error Settings End
     */
    char password[101]={};
    while(fgets(password,sizeof password,stdin)!=NULL){ //Used to read lines for strings until line is empty
        if(length_of_string(password)>100){
            fprintf(stderr, "Password is too long.\n");
            return 1;
        }
        number_of_passwords++; //counting how many passwords are there in code
        length_of_all_passwords += length_of_string(password);//Sums len of passwords
        if(Level_Checker(password,level,parameter)){  //Checks if password pass needed levels, if the password pass needed levels password is printed
            printf("%s",password);
        }
        //Looking for shortest password
        shortest_password = comparing_len_password(length_of_string(password),shortest_password);
        //Counting characters
        for(int i = 0; i < length_of_string(password) ; i++){
            int helper = password[i];
            characters[helper] += 1;
        }
    }
    /*
     * Stats that are printed at the end.
     */
    if(stats){
        printf("Statistika:\n");
        printf("Ruznych znaku: %d\n", characters_counter(characters));
        printf("Minimalni delka: %d\n", shortest_password);
        printf("Prumerna delka: %0.1lf\n", (length_of_all_passwords/number_of_passwords));
    }
    return 0;
}
