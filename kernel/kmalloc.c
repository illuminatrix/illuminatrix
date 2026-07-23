#include <stddef.h>
#include <stdint.h>
#include "kmalloc.h"
#include "mm.h"

#define HEAP_START_VIRTUAL 0xD0000000

struct heap_block {
    uint32_t size;
    uint8_t is_free;
    struct heap_block *next;
};

static struct heap_block *heap_head = NULL;
static uint32_t heap_end_virtual = 0;

static struct heap_block *create_heap_block(void *addr, uint32_t size, struct heap_block *next)
{
    struct heap_block *block = (struct heap_block*)addr;
    block->is_free = 1;
    block->size = size;
    block->next = next;
    return block;
}

void heap_init(void)
{
    mm_alloc_region_at(HEAP_START_VIRTUAL, FRAME_SIZE, PAGE_PRESENT | PAGE_RW);

    heap_head = create_heap_block((void *)HEAP_START_VIRTUAL, FRAME_SIZE - sizeof(struct heap_block), NULL);
    heap_end_virtual = HEAP_START_VIRTUAL + FRAME_SIZE;
}

void *kmalloc(uint32_t size)
{
    if (size == 0) return NULL;

    while (1) {
        struct heap_block *current = heap_head;
        struct heap_block *last = NULL;

        while (current != NULL) {
            if (current->is_free && current->size >= size) {
                if (current->size > size + sizeof(struct heap_block)) {
                    current->next = create_heap_block((void *)(uint8_t *)current + sizeof(struct heap_block) + size,
                                      current->size - size - sizeof(struct heap_block),
                                      current->next);
                    current->size = size;
                }

                current->is_free = 0;
                return (void *)(current + 1);
            }

            last = current;
            current = current->next;
        }

        uint32_t needed_bytes = size + sizeof(struct heap_block);
        uint32_t expansion_size = (needed_bytes + 0xFFF) & ~0xFFF;

        mm_alloc_region_at(heap_end_virtual, expansion_size, PAGE_PRESENT | PAGE_RW);

        struct heap_block *new_expansion = create_heap_block((void *)heap_end_virtual, expansion_size - sizeof(struct heap_block), NULL);
        if (last != NULL)
            last->next = new_expansion;

        heap_end_virtual += expansion_size;
    }
}

void kfree(void *ptr)
{
    if (ptr == NULL) return;

    struct heap_block *header = (struct heap_block *)ptr - 1;

    header->is_free = 1;

    struct heap_block *current = heap_head;

    while (current != NULL && current->next != NULL) {
        if (current->is_free && current->next->is_free) {
            current->size += current->next->size + sizeof(struct heap_block);
            current->next = current->next->next;
        } else
            current = current->next;
    }
}
