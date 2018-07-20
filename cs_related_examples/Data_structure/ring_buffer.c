/*
 * Ring_buffer: utilizes a fixed-size buffer  as if it were connected end-to-end (as if the buffer was circular in shape). 
 * The ring buffer is a FIFO type of buffer
*/

#include <stdbool.h>
#include <stdint.h>                 // needed for the uint8_t data type
#include <stdlib.h>                 // needed for the size_t and malloc
#include <stdio.h>                  // needed for the printf

/** variables declations and definitions*/

/* Declare a data type that holds the charactristics of a ring buffer */
typedef struct {
    uint8_t *buffer;                // a pointer to hold the address to the ring buffer
    size_t size;                    // `size_t` is used here to represent buffer 
                                    // object size in byte. `malloc` expects this data type
    size_t data_len;                // capture the length of the valid 
    size_t head;                    // the start index of the valid data
    size_t tail;                    // the end index of the valid data
}rbuf_t;
/*-----------------------------------------------------------------------------*/

/** functions prototyping */
void _advance_idx(size_t *idx, size_t *size);
bool rbuf_empty(rbuf_t* rbuf);
bool rbuf_full(rbuf_t *rbuf);
void rbuf_put( rbuf_t *rbuf, uint8_t data);
/*------------------------------------------------------------------------------*/ 


/** _advance_idx:
 * It is a helper function that advances an index of a ring buffer and set it to
 * zero when it is equal the buffer size
 *
 * @param *idx   *idx pointer to the head/tail ring buffer indices 
 * @param *size  *size pointer to the size of the buffer
 */
void _advance_idx(size_t *idx, size_t *size)
{
    
    if(++(*idx) == *size)
    {
        *idx= 0;
    }
}

/** rbuf_empty:
 * check if the ring buffer is empty
 *
 * @param   *rbuf   pointer to a ring buffer
 * @return  `true value` if the ring buffer is empty
 */
bool rbuf_empty(rbuf_t* rbuf)
{
    return (rbuf->data_len == 0); 
}

/** rbuf_full:
 * check if the ring buffer is full
 *
 * @param   *rbuf   pointer to a ring buffer
 * @return  `true value` if the ring buffer is full
 */
bool rbuf_full(rbuf_t *rbuf)
{
 return ( rbuf->data_len == rbuf->size); 
}

/** rbuf_put:
 * insert a value into the buffer
 *
 * @param *rbuf     pointer to a ring buffer
 * @param data      a byte to be inserted in to the buffer
 */ 
void rbuf_put( rbuf_t *rbuf, uint8_t data)
{
    // insert the data
    rbuf->buffer[rbuf->head] = data;
    // check if old data is overwritten
    if(rbuf_full(rbuf))
    {
        // advances the tail index to point to the old data
        // buffer size equals (max index + 1) 
        _advance_idx(&rbuf->tail, &rbuf->size);
    }
    else
    {
        // increase the length of the data if you do not overwrite old data
        rbuf->data_len++; 
    }
    // if the head index equals the buffer size set it back to zero 
    _advance_idx(&rbuf->head, &rbuf->size);
}

/** rbuf_get:
 * get a data from the buffer if it is not empty and advance tail pointer
 *
 * @param *rbuf     pointer to a ring buffer
 * @param *data     pointer to a variable to get the data from the buffer
 * @param  `true value` if the buffer is not empty
 */
bool rbuf_get(rbuf_t * rbuf, uint8_t *data)
{
    if(rbuf_empty(rbuf))
    {
        return (false);
    }
    // get the data
   *data = rbuf->buffer[rbuf->tail] ;
   // decrease the valid length
    rbuf->data_len--;
    _advance_idx(&rbuf->tail, &rbuf->size);
    return true;
}

bool rbuf_search( rbuf_t *rbuf, uint8_t word)
{
    uint16_t cntr = 0;
    while( cntr < rbuf->data_len)
    {
        if ( word == rbuf->buffer[(rbuf->tail) + cntr])
        {
            return true;
        }
        cntr++;
    }
return false;
}

/** rbuf_write:
 * write many bytes to the buffer
 *
 * @param *rbuf     pointer to a ring buffer 
 * @param numBytes  the number of bytes to be inseted
 * @param data      a pointer to byte of data to be inserted
 */ 
void rbuf_write( rbuf_t *rbuf, uint8_t numBytes, uint8_t *data)
{
    while(numBytes--)
    {
        rbuf_put(rbuf, *data);
        data++;
    }
}

/** rbuf_read:
 * read many bytes to the buffer
 *
 * @param *rbuf     pointer to a ring buffer
 * @param data      a byte to be read from the buffer
 */
void rbuf_read( rbuf_t *rbuf, uint8_t numBytes, uint8_t *data)
{
    while( (numBytes--) && rbuf_get(rbuf, data))
    {
        data++;
    }
}

int main()
{
   rbuf_t *rbuf = malloc(sizeof(rbuf_t));
   rbuf->data_len=0;
   rbuf->head = 0;
   rbuf->tail = 0;
   rbuf->size = 10;
   rbuf->buffer = malloc(rbuf->size);
   printf(" insert data\n");
   for(uint8_t i = 0; i < 7 ; i++)
   {
    printf("->%d\n", i);
    rbuf_put(rbuf, i);
   }

    printf("---------------\n");
   printf("data_len: %lu \n", rbuf->data_len);
   printf("tail  %lu \n", rbuf->tail);
   printf("head  %lu \n", rbuf->head);
   printf("size : %lu \n", rbuf->size);

    printf("----------------\n");
    uint8_t data;
   for(uint8_t i = 0; i < 9; i++)
   {
    if( rbuf_get(rbuf, &data))
    {
        printf("%d \n", data);
    }
   }

    printf("----------------\n");
   printf("data_len: %lu \n", rbuf->data_len);
   printf("tail  %lu \n", rbuf->tail);
   printf("head  %lu \n", rbuf->head);
   printf("size : %lu \n", rbuf->size);

   printf("----------------\n");
   printf(" insert data\n");
   for(uint8_t i = 0; i < 6; i++)
   {
    printf("->%d\n", i);
    rbuf_put(rbuf, i);
   }

    printf("----------------\n");
   printf("data_len: %lu \n", rbuf->data_len);
   printf("tail  %lu \n", rbuf->tail);
   printf("head  %lu \n", rbuf->head);
   printf("size : %lu \n", rbuf->size);

    printf("----------------\n");
   for(uint8_t i = 0; i < 3; i++)
   {
    if(!rbuf_get(rbuf, &data))
    {
        break;
    }
    printf("%d \n", data);
   }


    printf("----------------\n");
    uint8_t data_arr[] = {0,1,2,3,4,5,6,7,8};

   for(uint8_t i = 0; i < 9; i++)
   {
    if(rbuf_search(rbuf, data_arr[i]))
    {
        printf("found\n");
    }
    else
    {
        printf("not found\n");
    }
   }
return 0;
}






























