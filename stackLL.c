#include<stdio.h>
#include<stdlib.h>

struct Node{
    int data;
    struct Node*next;
};
struct Node*top=NULL;

void push(int value){
    struct Node*newNode=(struct Node*)malloc(sizeof(struct Node));
    if(newNode==NULL){
        printf("Stack Overflow/n");
        return;
    }
    newNode->data=value;
    newNode->next=top;
    top=newNode;
    printf("%d pushed",value);
}
void pop(){
    if(top==NULL){
        printf("Underflow\n");
        return;
    }
    struct Node*temp=top;
    printf("%d popped\n",temp->data);
    top=top->next;
    free(temp);
}
void peek(){
    if(top==NULL){
        printf("Stack is Empty\n");
        return;
    }
    printf("Top element: %d\n",top->data);
}
void display(){
    if(top==NULL){
        printf("Stack is empty\n");
        return;
    }
    struct Node*temp=top;
    printf("Stack Elements: ");
    while(temp!=NULL){
        printf("%d\t",temp->data);
        temp=temp->next;
    }
    printf("\n");
}
int main(){
    int choice, value;

    while(1){
        printf("\n__STACK MENU__\n");
        printf("1.Push\n2.Pop\n3.Peek\n4.Display\n5.Exit\n");
        printf("Enter your Choice: ");
        scanf("%d",&choice);

        switch(choice){
            case 1:
            printf("Enter the value to insert: \n");
            scanf("%d",&value);
            push(value);
            break;

            case 2:
            pop();
            break;

            case 3:
            peek();
            break;

            case 4:
            display();
            break;

            case 5:
            printf("Exiting...\n");
            return 0;

            default:
            printf("Invalid choice, try again.\n");
        }
    }
    return 0;

}
