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

struct node* insert(struct node *root, int input);
struct node *find_successor(struct node *ptr);
void inorder(struct node *root);

int main(){
    struct node *root = (struct node *)malloc(sizeof(struct node));
    root->left_child = root;
    root->right_child = root;
    root->left_thread = false;
    root->right_thread = false;
    
    root = insert(root, 20); 
    root = insert(root, 10); 
    root = insert(root, 30); 
    root = insert(root, 5); 
    root = insert(root, 16); 
    root = insert(root, 14); 
    root = insert(root, 17); 
    root = insert(root, 13);
  
    inorder(root); 

    return 0;
}

//return root
struct node *insert(struct node *root, int input){
    struct node *ptr, *parent;
    ptr = root->left_child;
    parent = root;

    // first node
    if(ptr == root){
        struct node *tmp;
        tmp = malloc(sizeof(struct node));

        tmp->data = input;
        tmp->left_thread = true;
        tmp->right_thread = true;
        tmp->left_child = parent->left_child; //root
        tmp->right_child = parent; //root

        parent->left_thread = false;
        parent->left_child = tmp;

        return root;
    }

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
    tmp = (struct node *)malloc(sizeof(struct node));
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

    else{ // input >= parent->data
        tmp->left_child = parent;
        tmp->right_child = parent->right_child; 
        parent->right_thread = false; //parent has right child
        parent->right_child = tmp;
    }

    return root; 
}

struct node *find_successor(struct node *ptr){
    //right_thread link to successor
    if(ptr->right_thread == true){
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

void inorder(struct node *root){
    struct node *ptr = root->left_child;

    //move to left-most
    while(ptr->left_thread == false){
        ptr = ptr->left_child;
    }
    printf("%d ",ptr->data);

    while(1){
        ptr = find_successor(ptr);
        if(ptr == root){
            //printf("finish\n");
            break;
        }
        printf("%d ",ptr->data);
    }
    printf("\n");
}

/*
後記：
在做thread的時候一定要用一個虛的node，
因為這樣才有辦法處理traverse順序中的第一個和最後一個node。
*/