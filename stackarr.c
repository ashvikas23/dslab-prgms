#include<stdio.h>
#define SIZE 20

int stack[SIZE];
int top=-1;

void push(int value){
    if(top>=SIZE){
        printf("Stack overflow. Cannot push %d\n",value);
    }else{
        top++;
        stack[top]=value;
        printf("%d pushed to stack.\n",stack[top]);
    }
}
void pop(){
    if(top==-1){
        printf("Stack underflow! Nothing to pop.");
    }else{
        printf("%d popped from Stack\n",stack[top]);
        top--;
    }
}
void display(){
    if(top==-1){
        printf("Stack is empty.\n");
    }else{
        printf("Stack elements: \n");
        for(int i=top; i>=0; i--){
            printf("%d\t",stack[i]);
        }
        printf("\n");
    }
}
int main(){
    int choice, value;
    while(1){
        printf("\n__STACK MENU__\n");
        printf("1.PUSH\n2.POP\n3.DISPLAY\n4.EXIT\n");
        printf("Enter your Choice: ");
        scanf("%d",&choice);
        switch(choice){
            case 1:
                printf("Enter value to push: ");
                scanf("%d",&value);
                push(value);
                break;
            case 2:
                pop();
                break;
            case 3:
                display();
                break;
            case 4:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid Choice. Try again!");
        }
    }
}