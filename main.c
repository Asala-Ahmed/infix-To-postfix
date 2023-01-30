#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define MAXSIZE 256

typedef union
{
    float fData;
    char cData;
}item;

typedef struct
{
   int top;
   item input[MAXSIZE];
}stack;

stack* initialize()
{
    stack* s=malloc(sizeof(stack));
    s->top=0;
    return s;
}

void push(stack* s,item value)
{
   s->input[s->top]=value;
   s->top++;
}

item pop(stack* s)
{
    s->top--;
    item value=s->input[s->top];
    return value;
}

int isEmpty(stack* s)
{
    if(s->top==0)
        return 1;
    else
        return 0;
}

item top(stack* s)
{
    return s->input[s->top-1];
}

int priority(char c)
{
    switch(c)
    {
        case'(':
              return 3;
        case '^':
            return 2;
        case '*':
        case '/':
        case '%':
            return 1;
        case '+':
        case '-':
            return 0;

    }

}
void replaceNewLineBySpace(char *s)
{
    char *s1 = s;
    while((s1 = strstr(s1, "\n")) != NULL)
        *s1 = ' ';
}
int isnumber(char * expression){
    for(int i=0;i<strlen(expression);i++){

        if(!isdigit(expression[i])&& expression[i]!= '.' )
            return 0;
        }
        return 1;
}
int isNegnum(char * expression){
    if(expression[0]=='-'&& strlen(expression)>1){

        for(int i =1;i<strlen(expression);i++){

            if(!isdigit(expression[i])&& expression[i]!= '.' )
                return 0;
        }

        return 1;
    }
    else
        return 0;
}

void infixToPostfix(char* infix ,char* postfix)
{
    stack* s=initialize();
    char*tok;
    item temp;
    tok =strtok(infix," ");
    int j;
    int k=0;
    while(tok!=NULL)
    {
        j=0;
        if(isdigit(tok[j]) || (tok[j]=='-' && strlen(tok)>1))
        {
            for(j=0;j<strlen(tok);j++){
                postfix[k++]=tok[j];
            }
                postfix[k++]=' ';
        }
        else
        {
            item x;
            x.cData = tok[0];

            if(tok[0]==')')
            {
                while(!isEmpty(s) && top(s).cData!='(')
                {
                    postfix[k++]=pop(s).cData;
                    postfix[k++]=' ';
                }
                pop(s);
            }

            else if(isEmpty(s))
            {
                push(s,x);
            }
            else
            {
                while(!isEmpty(s) && priority(top(s).cData)>=priority(tok[0]) && top(s).cData!='('){
                        postfix[k++]=pop(s).cData;
                        postfix[k++]=' ';
                      }
                      push(s,x);

            }
        }
       tok=strtok(NULL," ");
    }
    while(!isEmpty(s)){
            postfix[k++] = pop(s).cData;
            postfix[k++] = ' ';

    }
    postfix[k]='\0';
}

float evaluatePostfix(char* postfix){
   stack* s=initialize();
    char*tok;
    item temp;
    tok =strtok(postfix," ");
    item operand1,operand2,value;
    int j;
    int k=0;
while(tok!= NULL){

        if(isnumber(tok) || isNegnum(tok)){
            temp.fData = atof(tok);
            push(s,temp);
}
        else{
            operand2=pop(s);
            operand1=pop(s);

            if(strcmp(tok, "+")==0){
                value.fData = operand2.fData+operand1.fData;
                push(s,value);
            }
            else if (strcmp(tok, "-")==0){
                value.fData = operand1.fData-operand2.fData;
                push(s,value);
            }
            else if(strcmp(tok,"*")==0){
                value.fData = operand2.fData*operand1.fData;
                push(s,value);
            }
            else if(strcmp(tok,"/")==0){
                value.fData = operand1.fData/operand2.fData;
                push(s,value);
            }
            else if(strcmp(tok,"^")==0){
                value.fData = pow(operand1.fData,operand2.fData);
                push(s,value);
            }
        }
        tok = strtok(NULL," ");
    }
     return pop(s).fData;
}
int main()
{
    char infixExpr[256] = "";
    char postfixExpr[256] = "";
    printf("Enter an expression you want to evaluate or Ctrl+Z to exit: ");
    while(fgets(infixExpr, 255, stdin) != NULL)
    {
        replaceNewLineBySpace(infixExpr);
        infixToPostfix(infixExpr, postfixExpr);
        printf("Postfix : %s\n", postfixExpr);
        float result = evaluatePostfix(postfixExpr);
        printf("Result: %f\n\n", result);
        printf("Enter an expression you want to evaluate or Ctrl+Z to exit: ");
    }
    return 0;
}

