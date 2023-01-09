#ifndef _TREE_H
#define _TREE_H
//header protector let's goo
#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int data;
    struct node* left;//store the address of left node
    struct node* right;//store the address of right node
}node_t;
//define the structure of a binary tree
typedef struct tree{
    struct node* root;
    int cnt;
}tree_t;
extern void tree_travel(tree_t* tree);
extern void tree_clear(tree_t* tree);

extern void tree_insert(tree_t* tree, int data);

extern void tree_del(tree_t* tree, int data);

extern void tree_mod(tree_t* tree, int old_data, int new_data);
#endif 
//define the root node
static void travel(node_t* proot){
#ifdef A
   
    if(proot != NULL){// if the root node isn't empty, travel the whole tree
        printf("%d ", proot->data);
        travel(proot->left);
        travel(proot->right);
        return;
    }
#endif
#ifdef  B 
    if(proot != NULL){
        travel(proot->left); //start from the very first left node and start traveling
        printf("%d ", proot->data);
        travel(proot->right);
        return;
    }
#endif
#ifdef C 
    if(proot != NULL){
        travel(proot->left);
        travel(proot->right);
        printf("%d ", proot->data);
        return;
    }

#endif
}
//travel function
void tree_travel(tree_t* tree){
    travel(tree->root);
    printf("\n");
}

//recursion function that clear all the nodes
//clear(&tree->root)
static void clear(node_t** pproot){
    if(*pproot != NULL){
        clear(&(*pproot)->left);
        clear(&(*pproot)->right);
        free(*pproot);
        *pproot = NULL;
    }
}

//function that clear the whole tree
void tree_clear(tree_t* tree){
    clear(&tree->root);
    tree->cnt = 0;
}

//build a new node
static node_t* create_node(int data){
    node_t* pnew = (node_t*)malloc(sizeof(node_t));
    pnew->data = data;
    pnew->left = NULL;
    pnew->right = NULL;
    return pnew;//return the address of the new node
} 

//insert a new node to the tree in order
static void insert(node_t** pproot, node_t* pnew){
    if(*pproot == NULL){
        *pproot = pnew;//插入新节点
        return;
    }
    if((*pproot)->data > pnew->data){//insert it to the left tree branch
        insert(&(*pproot)->left, pnew);
        return;
    }else{//insert it the the right tree branch
        insert(&(*pproot)->right, pnew);
        return;
    }
}
//function that create a new node
void tree_insert(tree_t* tree, int data){
    //create a new node
    node_t* pnew = create_node(data);
    //use recursion function to insert the node
    insert(&tree->root, pnew);
    //renew count
    tree->cnt++;
}
//function that can find a specific node
static node_t** find(node_t** pproot, int data){
    
    if(*pproot == NULL)
        return pproot;//can't find it
 
    if((*pproot)->data == data)
        return pproot;//found it!
    else if((*pproot)->data > data){
        //go through the left branch to find it
        return find(&(*pproot)->left, data);
    }else{
        //or the right branch
        return find(&(*pproot)->right, data);
    }
}

static node_t** find_node(tree_t* tree, int data){
    return find(&tree->root, data);
}

//delete the node which store a specific data
void tree_del(tree_t* tree, int data){
    //find the node
    node_t** ppnode = find_node(tree, data);
    if(*ppnode == NULL){
        printf("can't find it.\n");
        return;
    }
    //continue
    if((*ppnode)->left != NULL)
        insert(&(*ppnode)->right,  (*ppnode)->left);
    node_t* ptmp = *ppnode;//temporarily store the node for future free()
    *ppnode = (*ppnode)->right;
    free(ptmp);
    tree->cnt--;
}
//modify a stored data
//ex: 20 -> 130
void tree_mod(tree_t* tree, int old_data, int new_data){
   //delete the old node
    tree_del(tree, old_data);
    //add the new node
    tree_insert(tree, new_data);
}
