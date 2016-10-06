#include <kernel/queue.h>
#include <stdint.h>

uint8_t
dequeue(queue_t *queue, uint8_t *c)
{
    if (buffer_empty(queue))
        return -1;

    *c = queue->buffer[queue->head];
    queue->head = buffer_next(queue->head);
    return 0;
}

void
enqueue(queue_t *queue, uint8_t c)
{
    if (buffer_full(queue))
        return;
    
    queue->buffer[queue->tail] = c;
    queue->tail = buffer_next(queue->tail);
}
