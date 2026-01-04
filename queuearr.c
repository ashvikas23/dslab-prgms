#include<stdio.h>
#define SIZE 50

int queue[SIZE];
int front=-1, rear=-1;

void enqueue(int value){
    if(rear==SIZE-1){
        printf("Queue Overflow\n");
    }else{
        if(front==-1){
            front=0;
        }
        rear++;
        queue[rear]=value;
        printf("Inserted %d\n",value);
    }
}
void dequeue(){
    if(front==-1 || front>rear){
        printf("Queue underflow.\n");
    }else{
        printf("Deleted %d\n",queue[front]);
        front++;
    }
}
void display(){
    if(front==-1 || front>rear){
        printf("Queue is empty!\n");
    }else{
        printf("Queue elements: ");
        for(int i=front;i<=rear;i++){
            printf("%d\t", queue[i]);
            printf("\n");
        }
    }
}
int main(){
    int choice,value;

    while(1){
        printf("\n__QUEUE MENU__\n");
        printf("1.Enqueue\n2.Dequeue\n3.Display\n4.Exit\n");
        printf("Enter your choice: ");
        scanf("%d",&choice);

        switch(choice){
            case 1:
            printf("Enter value to insert: ");
            scanf("%d",&value);
            enqueue(value);
            break;

            case 2:
            dequeue();
            break;

            case 3:
            display();
            break;

            case 4:
            printf("Exiting...");
            return 0;

            default:
            printf("Invalid choice. Try again.\n");
        }
    }
}