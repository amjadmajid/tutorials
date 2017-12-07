/*
@ Author: Amjad Yousef Majid
@ Date: 12/March/2017
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// The linkedlist node or link
struct _node{
	int value;
	int id;
	struct _node * next;
};
// deffining data type
typedef struct _node node;
// * // Global variables
// head always points to the beginning of the list
node *head=NULL; 		
// current is used during traversing the likedlist
node *current=NULL;


// * // function prototyping
void insert(int, int);
int length( node*  );
node* find(int );
node* findPrevious(int );
void delete(int );
bool isEmpty();
void display( node * );
bool insertBefore(int ,int, int );

// Add a link (node) to the top of the list
void insert(int id, int value){
	// Assign a memory for the node
	node *link = (node*)malloc(sizeof(node));
	if(link == NULL)
	{
		printf("ERROR: could not alocate memory for the node.");
		return;
	}
	// assign values to the struct fields
	link->id = id; 
	link->value = value;
// link the nodes
/*			   head
				v
	node(1)->node(NULL) */
	link->next =  head;
// Move the head pointer to the top of the linked list
/*		head
	   	 v
	  node(1)->node(NULL)   */
	head = link;
}

// insert a node at a specific location in the list
bool insertBefore(int nodeId ,int id, int value){
	// Assign a memory for the node
	node *link = (node*)malloc(sizeof(node));
	if(link == NULL)
	{
		printf("ERROR: could not alocate memory for the node.");
		return false;
	}
	// assign values to the struct fields
	link->id = id; 
	link->value = value;
// link the nodes

	node * previous =  find(nodeId);

	if(previous != NULL){
		link->next =  previous->next;
		previous->next =  link;

		return true;
	}

	return false;
}


//find the length of the list
int length( node * listHead ){
	int length=0;
	// a pointer is passed as as such it should not be 
	// modified (passed by reference)
	node * current = listHead;  
	// when the current reaches the end of the list
	// it will equal NULL and the loop will break
	while(current) 
	{
		length++;
		current = current->next;
	}  
	return length;
}

//find a link with given id
node * find(int id) {

   //start from the first link
   node* current = head;

   while(current) {
      if(current->id == id) {
      	// return the node with given id
         return current;
      } 
      current = current->next;
  }
  // If the id is not found.
   return NULL;
}

//find the previous node 
node* findPrevious(int id) {

   //start from the first link (node)
   node* previous = head;

   while(previous) {
   	// node(a) -> node(b). If the id matches node(b) id return node(a)
      if(previous->next->id == id) {
         return previous ;
      } 
      previous = previous->next;
  }
   return NULL;
}

void delete(int id)
{
	node * current = find(id);
	node * previous = findPrevious(id);
	if(current != NULL && previous != NULL)
	{
		previous->next = current->next;
		current->next =NULL;
		free(current);
		// delete the first node 
	}else if(current != NULL && previous == NULL)
	{
		// Let the head points to the seconde node in the list
		head = current->next;
		// disconnect the first node in the list
		current->next = NULL;
		// dealocate the memory for the first node
		free(current);

	}
}

//is list empty
bool isEmpty() {
   return head == NULL;
}

void display( node * head)
{
	current = head;
	while(current)
	{
		printf("node(%d,%d)\n", current->id, current->value );
		current = current->next;
	}
}

int main(int argc, char const *argv[])
{
	insert(1,20);
	insert(2,30);
	insert(3,87);
	insertBefore(3,4,87);

	printf("The length of the list is %d\n", length(head) );
	display( head);

	delete(1);
	printf("Delete a node \n" );
	display( head);

	return 0;
}


/*
Some good recources:
* https://www.tutorialspoint.com/
* http://www.sanfoundry.com
*/