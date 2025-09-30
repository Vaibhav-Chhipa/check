#include<stdio.h>
#include<string.h>

int numbers[100];
char operators[100];
int numTop = -1;
int operatorTop = -1;
int hasError = 0;

int Calculate(char exp[]){
    int len = strlen(exp);
    int i = 0;
    
    while(i < len){
        char c = exp[i];

        if(c == ' '){
            i++;
            continue;
        }

        if((c >= '0' && c <= '9') || (c == '-' && i+1 < len && exp[i+1] >= '0' && exp[i+1] <= '9')){
            int num = 0;
            int isNegative = 0;

            if(c == '-'){
                isNegative = 1;
                i++;
                c = exp[i];
            }

            while(i < len && c >= '0' && c <= '9'){
                num = num * 10 + (c - '0');
                i++;
                if(i < len){
                    c = exp[i];
                }
            }

            if(isNegative){
                num = -1*num;
            }
            
            numTop++;
            numbers[numTop] = num;
            continue;
        }

        if(c == '+' || c == '-' || c == '*' || c == '/'){
            while(operatorTop != -1) {
                char top = operators[operatorTop];
                
                int topPri, curPri;
                if(top == '*' || top == '/')
                    topPri = 2;
                else
                    topPri = 1;
                    
                if(c == '*' || c == '/')
                    curPri = 2;
                else
                    curPri = 1;
                
                if(topPri < curPri)
                    break;
                
                char op = operators[operatorTop];
                operatorTop--;
                
                int b = numbers[numTop];
                numTop--;
                
                int a = numbers[numTop];
                numTop--;
                
                int result;
                if(op == '+'){
                    result = a + b;
                }
                else if(op == '-'){
                    result = a - b;
                }
                else if(op == '*'){
                    result = a * b;
                }
                else if(op == '/'){
                    if(b == 0){
                        hasError = 1;
                        return 0;
                    }
                    result = a / b;
                }
                
                numTop++;
                numbers[numTop] = result;
            }
            
            operatorTop++;
            operators[operatorTop] = c;
        }
        
        i++;
    }
    
    // Process remaining operators
    while(operatorTop != -1){
        char op = operators[operatorTop];
        operatorTop--;  
        
        int b = numbers[numTop];
        numTop--;
        
        int a = numbers[numTop];
        numTop--;
        
        int result;
        if(op == '+'){
            result = a + b;
        }
        else if(op == '-'){
            result = a - b;
        }
        else if(op == '*'){
            result = a * b;
        }
        else if(op == '/'){
            if(b == 0){
                return -1;
            }
            result = a / b;
        }
        
        numTop++;
        numbers[numTop] = result;
    }
    
    return numbers[numTop];
}

int isValid(char exp[]){
    int checkNum = 1;
    int hasNum = 0;

    for(int i = 0;exp[i] != '\0'; i++){
        char c = exp[i];
        if(c == ' '){
            continue;
        }

        if(c >= '0' && c <= '9'){
            if(checkNum == 0){
                return 0;
            }
            hasNum = 1;
            while(exp[i+1] >= '0' && exp[i+1] <= '9'){
                i++;
            }
            checkNum = 0;
        } else if(c == '+' || c == '*' || c == '/'){
            if(checkNum == 1){
                return 0;
            }
            checkNum = 1;
        } else if(c == '-'){
            if(checkNum == 1){
                if(!(exp[i+1] >= '0' && exp[i+1] <= '9')){
                    return 0;
                }
                continue;
            }
            checkNum = 1;
        } else {
            return 0;
        }
    }
    if(checkNum == 0 && hasNum == 1){
        return 1;
    }
    return 0;
}

int main(){
    char exp[100];
    scanf("%[^\n]%*c", exp);

    if(isValid(exp) == 0){
        printf("Error: Invalid expression.");
        return 0;
    }

    int ans = Calculate(exp);

    if(hasError == 1){
        printf("Error: Division by zero.");
    }
    else{
        printf("%d", ans);
    }

    return 0;
}