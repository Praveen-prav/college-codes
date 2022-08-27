// Name     : M Praveen
// Roll No  : CS20B1023
// Lab 3

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <stdbool.h>
#include <ctype.h>


int op = 0, special_symbols = 0, constants = 0, keywords = 0, strings = 0, identifiers = 0;

bool isDelimiter(char ch){
    if (ch == ' ' || ch == '+' || ch == '-' || ch == '*' ||
        ch == '/' || ch == ',' || ch == ';' || ch == '>' ||
        ch == '<' || ch == '=' || ch == '(' || ch == ')' ||
        ch == '[' || ch == ']' || ch == '{' || ch == '}' || 
        ch == '"' || ch == '\''
        )
        return (true);
    return (false);
}

bool isOperator(char ch){
    if (ch == '+' || ch == '-' || ch == '*' ||
        ch == '/' || ch == '>' || ch == '<' ||
        ch == '=')
        return (true);
    return (false);
}

bool isValidIdentifier(char* str){
    if (str[0] == '0' || str[0] == '1' || str[0] == '2' ||
        str[0] == '3' || str[0] == '4' || str[0] == '5' ||
        str[0] == '6' || str[0] == '7' || str[0] == '8' ||
        str[0] == '9' || isDelimiter(str[0]) == true)
        return (false);
    return (true);
}
 
bool isKeyword(char* str){
    if (!strcmp(str, "if") || !strcmp(str, "else") ||
        !strcmp(str, "while") || !strcmp(str, "do") ||
        !strcmp(str, "break") ||
         !strcmp(str, "continue") || !strcmp(str, "int")
        || !strcmp(str, "double") || !strcmp(str, "float")
        || !strcmp(str, "return") || !strcmp(str, "char")
        || !strcmp(str, "case") || !strcmp(str, "char")
        || !strcmp(str, "sizeof") || !strcmp(str, "long")
        || !strcmp(str, "short") || !strcmp(str, "typedef")
        || !strcmp(str, "switch") || !strcmp(str, "unsigned")
        || !strcmp(str, "void") || !strcmp(str, "static")
        || !strcmp(str, "struct") || !strcmp(str, "goto"))
        return (true);
    return (false);
}
 
bool isInteger(char* str){
    int i, len = strlen(str);
 
    if (len == 0)
        return (false);
    for (i = 0; i < len; i++) {
        if (str[i] != '0' && str[i] != '1' && str[i] != '2'
            && str[i] != '3' && str[i] != '4' && str[i] != '5'
            && str[i] != '6' && str[i] != '7' && str[i] != '8'
            && str[i] != '9' || (str[i] == '-' && i > 0))
            return (false);
    }
    return (true);
}
 
bool isRealNumber(char* str){
    int i, len = strlen(str);
    bool hasDecimal = false;
 
    if (len == 0)
        return (false);
    for (i = 0; i < len; i++) {
        if (str[i] != '0' && str[i] != '1' && str[i] != '2'
            && str[i] != '3' && str[i] != '4' && str[i] != '5'
            && str[i] != '6' && str[i] != '7' && str[i] != '8'
            && str[i] != '9' && str[i] != '.' ||
            (str[i] == '-' && i > 0))
            return (false);
        if (str[i] == '.')
            hasDecimal = true;
    }
    return (hasDecimal);
}
 

bool isSpecialCharacter(char ch){
    if(ch == '"' || ch == '\'' || ch == '{' || ch == '}' ||
       ch == '[' || ch == ']' || ch == '(' || ch == ')'  ||
       ch == '#' || ch == ',' || ch == ':' || ch == ';'){
        return true;
    }
    return false;
}

char* subString(char* str, int left, int right)
{
    int i;
    char* subStr = (char*)malloc(sizeof(char) * (right - left + 2));
 
    for (i = left; i <= right; i++)
        subStr[i - left] = str[i];
    subStr[right - left + 1] = '\0';
    return (subStr);
}
 
void identifyTokens(char* str){
    int left = 0, right = 0;
    int len = strlen(str);
    int state = 0, tempv = 1, stringStart = 0;
    char *token;

    while(right <= len && left <= right){
        if(!isDelimiter(str[right]))
        {
            right++;
        }
        else{
            if(left == right){
                if(isOperator(str[right+1])){
                    if(isOperator(str[right])){
                        right+=2;
                        token = subString(str, left, right - 1);
                        tempv = 0;
                        left = right;
                    }
                    else{
                        token = &str[right];
                        right++;
                        left = right;
                        tempv = 1;
                    }
                }
                else{
                    token = &str[right];
                    right++;
                    left = right;
                    tempv = 1;
                }
            }
            else{
                if(stringStart == 0){
                    token = subString(str, left, right - 1);
                }
                else{
                    while(str[right] != '"' && str[right] != '\''){
                        right++;
                    }
                    token = subString(str, left, right - 1);
                    state = 6;
                }
                left = right;
                tempv = 0; 
            }

        char ch;
        int i = 0;
        int loopVariable = 1;

        while(loopVariable){
            switch(state){
                case 0: {
                    ch = token[i];
                    i++;
                    if(isalpha(ch)){
                        state = 1;
                        break;
                    }
                    else if(isdigit(ch)){
                        state = 2;
                        break;
                    }
                    else if(isOperator(ch)){
                        state = 4;
                        break;
                    }
                    else{
                        state = 5;
                        break;
                    }
                }
                break;

                case 1: {
                    ch = token[i];
                    i++;
                    if(isalpha(ch) || isdigit(ch)){
                        state = 1;
                        break;
                    }
                    else if(isKeyword(token)){
                        printf("'\033[0;34m%s\033[0m' - Keyword,State - %d\n", token, state);
                        keywords++;
                        loopVariable = 0;
                        break;
                    }
                    else if(ch != ' '){
                        if(!tempv){
                            printf("'\033[0;34m%s\033[0m' - Identifier,State - %d\n", token, state);
                        }
                        else{
                            printf("'\033[0;34m%c\033[0m' - Identifier,State - %d\n", token[0], state);
                        }
                        identifiers++;
                        loopVariable = 0;
                        break;
                    }
                    else{
                        loopVariable = 0;
                    }
                }
                break;

                case 2: {
                    ch = token[i];
                    i++;
                    if(isdigit(ch)){
                        state = 2;
                        break;
                    }
                    else if(ch == '.'){
                        state = 3;
                        break;
                    }
                    else if(ch == 'u' || ch == 'U' || ch == 'I' || ch == 'L'){
                            if(!tempv){
                                printf("'\033[0;34m%s\033[0m' - Integer,State - %d\n", token, state);
                            }
                            else{
                                printf("'\033[0;34m%c\033[0m' - Integer,State - %d\n", token[0], state);
                            }
                            constants++;
                            loopVariable = 0;
                            break;
                    }
                    else{
                        if(!tempv){
                            printf("'\033[0;34m%s\033[0m' - Integer,State - %d\n", token, state);
                        }
                        else{
                            printf("'\033[0;34m%c\033[0m' - Integer,State - %d\n", token[0], state);
                        }
                        constants++;
                        loopVariable = 0;
                        break;
                    }
                }
                break;

                case 3: {
                    ch = token[i];
                    i++;
                    if(isdigit(ch)){
                        state = 3;
                        break;
                    }
                    else{
                        printf("'\033[0;34m%s\033[0m' - Decimal Number, State - %d\n", token, state);
                        constants++;
                        loopVariable = 0;
                        break;
                    }
                }

                case 4:{
                    ch = token[i];
                    i++;
                    char temp = token[i];
                    if(isOperator(ch)){
                        printf("'\033[0;34m%s\033[0m' - Operator, State - %d\n", token, state);
                    }
                    else{
                        printf("'\033[0;34m%c\033[0m' - Operator, State - %d\n", token[0], state);
                    }
                    op++;
                    loopVariable = 0;
                    break;
                }
                break;

                case 5:{
                    if(ch == '"' || ch == '\''){
                        state = 6;
                        break;
                    }
                    else if(ch != ' '){
                        printf("'\033[0;34m%c\033[0m' - Special Symbol, State - %d\n", token[0], state);
                        special_symbols++;
                        loopVariable = 0;
                        break;
                    }
                    else{
                        loopVariable = 0;
                        break;
                    }
                }
                break;
                
                case 6:{
                    if(stringStart){
                        printf("'\033[0;34m%s\033[0m' - String,State - %d\n", token, state);
                        strings++;
                        stringStart = 0;
                        loopVariable = 0;
                        break;
                    }
                    else if(ch == '"' || ch == '\''){
                        printf("'\033[0;34m%c\033[0m' - Special symbol - 5\n", ch);
                        special_symbols++;
                        stringStart = 1;
                        loopVariable = 0;
                        break;
                    }
                }
            
            }
           }
        }

        state = 0;
    }
	return;
}

void removeCommentsDirectivesAndExtras(FILE *fp1, FILE *fp2){
	char ch, current, previous;
	int flag = 0;
	ch = fgetc(fp1);
	previous = '\n';
	current = ch;
	while(ch != EOF){
	if(ch == ' ' || ch == '\t' || ch == '\0' || ch == '\n'){
		if(flag == 0){
			fputc(ch, fp2);
			flag = 1;
		}
		ch = fgetc(fp1);
	}else{
		flag = 0;
        if(ch == '#'){
			if(previous == '\n'){
				while(ch!='\n'){
					ch = fgetc(fp1);
				}
			}
			flag = 1;
		}
		else if(ch == '/'){
			ch = fgetc(fp1);
			if(ch == '/'){
				while(ch!='\n'){
					ch = fgetc(fp1);
				}
			}else if(ch == '*'){
				previous = fgetc(fp1);
				current = fgetc(fp1);
				int temp = 0;
				if(current == '/' && previous == '*'){
					temp = 1;
				}
				while(temp != 1){
					previous = current;
					current = fgetc(fp1);
				if(current == '/' && previous == '*'){
					temp = 1;
				}
				}
				ch = fgetc(fp1);
			}else{
				fputc(ch, fp2);
			}
			ch = fgetc(fp1);
		}
        else{
			fputc(ch, fp2);
			ch = fgetc(fp1);
		}
	}
		previous = current;
		current = ch;
	}
}

int main(int argc, char** argv){
	if(argc != 2){
		printf("Enter the file name as an argument\n");
		exit(1);
	}
	FILE *fp1, *fp2;
	fp1 = fopen(argv[1], "r");
	fp2 = fopen("output.c", "w");
    
	removeCommentsDirectivesAndExtras(fp1, fp2);

	fclose(fp1);
	fclose(fp2);

	FILE *fp = fopen("output.c", "r");
	char characters[128];
    
    while(fgets(characters, sizeof(characters), fp) != NULL) {
        identifyTokens(characters);
    }
   
    printf("\nIdentifiers: %d\n", identifiers);
    printf("Keywords: %d\n", keywords);
    printf("Constants: %d\n", constants);
    printf("Operators: %d\n", op);
    printf("Special Chars: %d\n", special_symbols);
    printf("Strings: %d\n", strings);
    
	return 0;
}
