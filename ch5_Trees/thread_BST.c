//thread: replace null link by pointer to other node
//if ptr->left_child == NULL, ptr->left_child = (xx-order) predecessor of ptr
//if ptr->right_child == NULL, ptr->right_child = (xx-order) successor of ptr
//Need not use "recursion".

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//Inorder traversal
struct node{
    int data;
    struct node *left_child, *right_child;
    bool left_thread, right_thread;
    //true if left_child connect to predecessor
    //true if right_child connect to successor
};

struct node* insert(struct node * head, struct node *root, int input);
struct node *find_successor(struct node *head, struct node *ptr);
void inorder(struct node *head);

int main(){
    struct node *head = malloc(sizeof(struct node));
    struct node *root = NULL;
    head->left_child = root;
    head->right_child = head;

    root = insert(head, root, 20); 
    root = insert(head, root, 10); 
    root = insert(head, root, 30); 
    root = insert(head, root, 5); 
    root = insert(head, root, 16); 
    root = insert(head, root, 14); 
    root = insert(head, root, 17); 
    root = insert(head, root, 13); 
  
    inorder(head); 

    return 0;
}

struct node *insert(struct node *head, struct node *root, int input){

    // first node
    if(!root){
        root=malloc(sizeof(struct node));
        root->data = input;
        root->left_child = head;
        root->right_thread = head;
        root->left_thread = true;
        root->right_thread = true;
        return root;
    }

    struct node* ptr = root;
    struct node* parent;

    //find insert site
    while(ptr){
        parent=ptr;

        if(input < ptr->data){
            if(ptr->left_thread == false){ //has child
                ptr = ptr->left_child;
            }
            else{ //thread
                break;
            }
        }

        else{ //input >= ptr->data
            if(ptr->right_thread == false){ //has child
                ptr = ptr->right_child;
            }
            else{ //thread
                break;
            }
        }
    }

    //creat new node and connect
    struct node *tmp;
    tmp = malloc(sizeof(struct node));
    tmp->data = input;
    tmp->left_thread = true;
    tmp->right_thread = true;

    //inorder: left, parent, right. left child first
    if(input < parent->data){
        tmp->left_child = parent->left_child; 
        tmp->right_child = parent;
        parent->left_thread = false; //parent has left child
        parent->left_child = tmp;
    }

    else{ // input < parent->data
        tmp->left_child = parent;
        tmp->right_child = parent->right_child; 
        parent->right_thread = false; //parent has right child
        parent->right_child = tmp;
    }

    return root; 
}

struct node *find_successor(struct node *head, struct node *ptr){
    //right_thread link to successor
    if(ptr->right_thread == true){
        if(ptr->right_child == head){
            return NULL;
        }
        return ptr->right_child;
    }

    //the left-most node of right sub-tree
    else{
        ptr = ptr->right_child;
        while(ptr->left_thread == false){
            ptr = ptr->left_child;
        }
        return ptr;
    }
}

void inorder(struct node *head){
    struct node *ptr = head->left_child; //root

    //move to left-most
    while(ptr->left_thread == false){
        ptr = ptr->left_child;
    }

    while(ptr){
        printf("%d ",ptr->data);
        ptr = find_successor(head, ptr);
    }
    printf("\n");
}