#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define HASHSIZE 10

struct nlist{
	struct nlist * next; // next entry in chain
	char * name; 
	char *defn;
};

static struct nlist *hashtab[HASHSIZE];

// hash the innput string 
unsigned hash( char *s)
{
	unsigned hashval;
	hashval = *s + 31 * hashval;
	return hashval % HASHSIZE ;
}


struct nlist *  lookup(char *s)
{
	struct nlist *np;
	for( np = hashtab[hash(s)]; np !=NULL; np = np->next )
		if(strcmp(s, np->name) == 0)
			return np;
	
	return NULL;
} 

struct nlist * install( char * name, char *defn)
{
	struct nlist *np;
	unsigned hashval;

	if( (np=lookup(name)) ==  NULL ) // no found
	{
		np =  (struct nlist *) malloc ( sizeof(*np) );
		if(np == NULL || (np->name = strdup(name)) == NULL)
			return NULL;
		hashval = hash(name);
		np->next =  hashtab[hashval];
	}else // already there
		free((void*) np->defn);
		if((np->defn =  strdup(defn)) ==NULL)
			return NULL;
	return np;
}

int main(int argc, char const *argv[])
{
	// install("amjad", "0");
	// install("Noor", "1");
	// install("Ali", "2");
	// struct nlist * Ali_num = lookup("Ali");
	// printf("%s\n", Ali_num->defn );
	putchar('c');
	return 0;
}