#include <stdio.h>
#include <stdlib.h>


typedef struct node { 
    int key; 
    struct node* left;
    struct node* right;
}node;

struct node* root= NULL;
int count=0;
void preOrder(node* temp){

    if (temp!=NULL){
        printf("%d ",temp->key);
        preOrder(temp->left);
        preOrder(temp->right);
    }
}
//for printing
void inOrder(node* temp){

        if (temp!=NULL){
           inOrder(temp->left);
           printf("%d ",temp->key);
           inOrder(temp->right);
        }

}
void printPrompt(void){
    int choice=-1;

    do{
        printf("   Enter <1> Inorder <2> Preorder <3> Return to Menu: ");
        scanf("%d", &choice);

        if(choice!=1 && choice!=2 && choice!=3)  printf("   Error: invalid input! \n\n");
        if(choice==1){
           if(root==NULL) printf("\tError: is empty tree\n");
              else {
                   printf("\tInorder:\t ");
                   inOrder(root);
                   printf("\n\n");
              }
        }
        else if (choice==2){
           struct node* temp=root;
           if(root==NULL) printf("\tError: is empty tree\n");
              else {
                   printf("\tPreorder:\t ");
                   preOrder(root);
                   printf("\n\n");
              }
        }


    }while (choice!=3);
    printf("   <Exit print method>\n\n");

}
//printing complete

//both are similar code- one searches and another finds the node
int contains(node* current, int value){
    if(current==NULL) return 0;
    if (value==current->key) {
        return 1;
    }
    else if(value < current->key) return contains(current->left, value);
    else return contains(current->right, value);
}
node* findParent(node* current, int value){
    if (value == current->key) return NULL; //if only one node in BST, then no parent node
    if (value < current->key) {
        if (current->left == NULL) return NULL; //if value not found, return null
        else if (current->left->key == value) return current;
        else return findParent (current->left, value);
    }
    else {
        if (current->right == NULL) return NULL;
        else if (current->right->key== value) return current;
        else return findParent (current->right, value);
    }
}

node* findNode(node* current, int value){
    if (current == NULL) return NULL;
    if (current->key == value) {
        return current;
    }
    else if (value < current->key)  return findNode (current->left, value);
    else return findNode (current->right, value);
}
//

void del(value){
    struct node* nodeToRemove= findNode(root, value);
    if (nodeToRemove == NULL) printf("\tError: node not found in tree\n");
    else {
       struct node* parent = findParent(root, value);
       if (count == 1 ) {
            root= NULL; 
            printf("\tRemoving the only node in BST\n");
       }
       else if (nodeToRemove->left == NULL && nodeToRemove->right == NULL){
            printf("\tRemoving leaf node in BST\n");
            if (nodeToRemove->key < parent->key) parent->left = NULL;
            else parent->right = NULL;
       }
       else if (nodeToRemove->left== NULL && nodeToRemove->right != NULL){
            printf("\tRemoving node with right subtree but no left subtree\n");
            if (nodeToRemove->key < parent->key) {
                parent->left = nodeToRemove->right;
            }
            else parent->right = nodeToRemove->right;
       }
       else if (nodeToRemove->left!= NULL && nodeToRemove->right == NULL){
            printf("\tRemoving node with left subtree but no right subtree\n");
            if (nodeToRemove->key < parent->key) {
                parent->left = nodeToRemove->left;
            }
            else parent->right = nodeToRemove->left;
       }
       else{
            printf("\tRemoving node with both left subtree and right subtree\n");
            struct node* nodeLargestLeft = nodeToRemove -> left;
                while (nodeLargestLeft -> right != NULL) nodeLargestLeft= nodeLargestLeft->right;
            findParent(root, nodeLargestLeft->key)->right=NULL;
            nodeToRemove->key=nodeLargestLeft->key;
       }   
   }

            printf("\tResult: ");
            preOrder(root);
            printf("\n");  
            count= count-1;
}

void deletePrompt(void){
    int value=-1;
    do{
        printf("   Delete key or press -1 to return to menu:  ");
        scanf("%d", &value);
        if(value>0){
           if(root==NULL) printf("\tError: is empty tree\n");
           printf("%s\n", value );
             else del(value);

        }
         else if (value<=0) printf("\tError: key not positive\n");
    }while (value!=-1); 
    printf("   <Exit delete method>\n\n");
}

void searchPrompt(void){
    int value=-1;
    do{
        printf("   Search key or press -1 to return to menu: ");
        scanf("%d", &value);
        if(value>0){
            if (root==NULL) printf("\tError: tree is empty\n"); 
            else {
                if(contains(root, value)) printf("\tKey %d is found\n",value);
                else printf("\tKey %d is not found\n",value);
            }
        }
        else if (value<=0) printf("\tError: key not positive\n");
    }while (value!=-1);
    printf("   <Exit search method>\n\n");
}
//for search




//for insertion
void insertNode(node* current, int value){        
        if(value< current->key){
            if (current->left == NULL) {
                current->left=(node*) malloc(sizeof(node));
                current->left->key = value;
                current->left->left = NULL;
                current->left->right = NULL;
                printf("\tSuccess! Value inserted: %d\n", current->left->key);

            }
            else {
                insertNode(current->left, value);
            }
        }
        else {
            if (current->right == NULL) {
                current->right=(node*) malloc(sizeof(node));
                current->right->key = value;
                current->right->left = NULL;
                current->right->right = NULL;
                printf("\tSuccess! Value inserted: %d\n", current->right->key);
            }
            else {
                insertNode(current->right, value);
            }
        }
}//end insert

void insert(int value){

    if(root==NULL){  //empty tree
        root =(node*) malloc(sizeof(node));

        root->key= value;
        printf("\tPrint root here: %d\n", value);
        root->left= NULL;
        root->right=NULL;
        printf("\tSuccess! Value inserted: %d\n", root->key);
    }
    else {
        insertNode(root, value);
    }        
        printf("\tResult: ");
        preOrder(root);
        printf("\n");
}

void insertPrompt(void){
    int value=-1;
    do{
        printf("   Insert value or press -1 to return to menu:  ");
        scanf("%d", &value);
        if(value>0){
            insert(value);
            count= count+1;
            printf("\tCount: %d\n", count);
        }
        else if (value<=0)printf("\tError: key not positive\n");
    }while (value!=-1);
    printf("   <Exit insert method>\n\n");

}

int menuPrompt(void){
    int choice=-1;
    do{
        printf("Enter <1> Search <2> Insert <3> Delete <4> Print Tree <5> Quit: ");
        scanf("%d", &choice);
        if(choice>5 || choice<1) printf("Error: invalid input! \n\n");
    }  while(choice>5 || choice<1);
    return choice;

}


int main(int argc, char *argv[]){
   int choice=-1;
   int value=-1;


    while(choice!=5){

   choice=menuPrompt();

   switch(choice){
    case 1:
         searchPrompt();
         break;
    case 2:
         insertPrompt();
         break;
    case 3:
         deletePrompt();
         break;
    case 4:
         printPrompt();
         break;    
    case 5:
         printf("<Exit program> \n");
         break;
   }//end switch

}

  system("PAUSE");  
  return 0;
}