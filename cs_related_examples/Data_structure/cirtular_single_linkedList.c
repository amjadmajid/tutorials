/*
@ Author: Amjad Yousef Majid
@ Date: 13/March/2017
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
// tail always points to the end of the list
node *tail=NULL;


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

	if(isEmpty())
	{
		// adding the very first link to the linkedlist
		tail = link;
		head = link;
		// the link (node) points to itself
		tail->next = head;
	}else{
	// let the new link (node) points to the top of the linkedlist
	link->next =  head;
	// let the head points to the new top of the linkedlist
	head = link;
	// link the tail to the new head
	tail->next = head;
	}
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
	do 
	{
		length++;
		current = current->next;
	} while(current != head); 
	return length;
}

//find a link with given id
node * find(int id) {

   //start from the first link
   node* current = head;

   do{
   		if(current->id == id) {
      	// return the node with given id
         return current;
      	} 
      current = current->next;

   }while( current != head);

  // If the id is not found.
   return NULL;
}

//find the previous node 
node* findPrevious(int id) {

   //start from the first link (node)
   node* previous = head;

   do{
   	   	// node(a) -> node(b). If the id matches node(b) id return node(a)
      if(previous->next->id == id) {
         return previous ;
      } 
      previous = previous->next;
   }while (previous != head);

if(tail->next->id == id)
	return tail;

   return NULL;
}

void delete(int id)
{
	node * current = find(id);
	node * previous = findPrevious(id);

	if(current != NULL && previous != NULL)
	{
		previous->next = current->next;
		// if the top of the linkedlist is to be deleted
		// we need to move the head to the second link (node)
		if(current == head)
			{
				head =  current->next;
			}
		current->next =NULL;
		free(current);
	}else {
		printf("ERROR: could not delete the node.\n");
	}
}

//is list empty
bool isEmpty() {
   return head == NULL;
}

void display( node * head)
{
	current = head;
	do
	{
		printf("node(%d,%d)\n", current->id, current->value );
		current = current->next;
	}while(current != head);
}

int main(int argc, char const *argv[])
{
	insert(1,20);
	insert(2,30);
	insert(3,87);
	delete(3);
	printf("The length of the linkedlist is %d\n", length(head));

	display(head);

	current=head;
	for(int i =10; i ; i--)
	{
		printf("Node(%d)\n", current->id );
		current = current->next;
	}

	return 0;
}


/*
Some good recources:
* https://www.tutorialspoint.com/
* http://www.sanfoundry.com
*/