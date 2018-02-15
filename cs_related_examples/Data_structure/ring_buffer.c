/*
 * Ring_buffer: utilizes a fixed-size buffer  as if it were connected end-to-end (as if the buffer was circular in shape). 
 * The ring buffer is a FIFO type of buffer
*/

#include <stdbool.h>
#include <stdint.h>                 // needed for the uint8_t data type
#include <stdlib.h>                 // needed for the size_t and malloc
#include <stdio.h>                  // needed for the printf

/*
 * Declare a data type that holds the charactristics of a ring buffer
 */
typedef struct {
    uint8_t *buffer;                // a pointer to hold the address to the ring buffer
    size_t size;                    // `size_t` is used here to represent buffer 
                                    // object size in byte. `malloc` expects this data type
    size_t data_len;              // capture the length of the valid 
    size_t head;                    // the start index of the valid data
    size_t tail;                    // the end index of the valid data
}rbuf_t;

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
    if(rbuf->head == rbuf->tail)
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

int main()
{
   rbuf_t *rbuf;
   rbuf->head = 0;
   rbuf->tail = 0;
   rbuf->size = 10;
   rbuf->buffer = malloc(rbuf->size);
   
   for(uint8_t i = 0; i < 10; i++)
   {
    rbuf_put(rbuf, i);
   }

    uint8_t data;
   for(uint8_t i = 0; i < 10; i++)
   {
    rbuf_get(rbuf, &data);
    printf("%d \n", data);
   }
return 0;
}
