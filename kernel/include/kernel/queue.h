#ifndef _KERNEL_QUEUE
#define _KERNEL_QUEUE

#include <stdint.h>

#define _BUFFER_SIZE 8

#define buffer_next(i)  (i + 1) % _BUFFER_SIZE
#define buffer_empty(queue)  queue.head == queue.tail
#define buffer_full(queue)   buffer_next(queue.tail) == queue.head

struct queue {
    uint8_t buffer[_BUFFER_SIZE];
    uint8_t head;
    uint8_t tail;
};
typedef struct queue queue_t;

uint8_t dequeue(queue_t queue, uint8_t *c);

void enqueue(queue_t queue, uint8_t c);
#endif
