#include <stdio.h>
#include <stdlib.h>

typedef struct _Element {
    int prioritet;
    void* data;
} Element;

typedef struct {
    int n;          // current number of elements
    int capacity;   // maximum capacity
    Element* queue_arr;
} Queue;

Queue create_queue(int capacity)
{
    Queue q;
    q.n = 0;
    q.capacity = capacity;
    q.queue_arr = (Element*)malloc(capacity * sizeof(Element));

    if (q.queue_arr == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    return q;
}

void delete_queue(Queue* q)
{
    q->n = 0;
    q->capacity = 0;
    free(q->queue_arr);
    q->queue_arr = NULL;
}

void sort_queue_top_iter(Queue* q, int c)
{
    while (c > 0) {
        int r = (c - 1) / 2;

        if (q->queue_arr[c].prioritet > q->queue_arr[r].prioritet) {
            Element temp = q->queue_arr[c];
            q->queue_arr[c] = q->queue_arr[r];
            q->queue_arr[r] = temp;
            c = r;
        } else {
            break;
        }
    }
}

void queue_add(Queue* q, Element el)
{
    if (q->n >= q->capacity) {
        printf("Queue overflow! Cannot add more elements.\n");
        return;
    }

    q->queue_arr[q->n] = el;
    q->n++;

    sort_queue_top_iter(q, q->n - 1);
}

void sort_queue_bottom_iter(Queue* q, int r)
{
    while (1) {
        int c_l = 2 * r + 1;
        int c_r = 2 * r + 2;
        int largest = r;

        if (c_l < q->n && q->queue_arr[c_l].prioritet > q->queue_arr[largest].prioritet)
            largest = c_l;

        if (c_r < q->n && q->queue_arr[c_r].prioritet > q->queue_arr[largest].prioritet)
            largest = c_r;

        if (largest != r) {
            Element temp = q->queue_arr[r];
            q->queue_arr[r] = q->queue_arr[largest];
            q->queue_arr[largest] = temp;
            r = largest;
        } else {
            break;
        }
    }
}

void remove_from_top(Queue* q)
{
    if (q->n == 0) {
        printf("Queue underflow! Nothing to remove.\n");
        return;
    }

    q->queue_arr[0] = q->queue_arr[q->n - 1];
    q->n--;

    sort_queue_bottom_iter(q, 0);
}

int main()
{
    Queue q = create_queue(10);

    for (int i = 0; i < 10; i++)
    {
        Element temp;
        temp.prioritet = i;
        temp.data = NULL;     // FIXED
        queue_add(&q, temp);
    }

    printf("Heap after insertion:\n");
    for (int i = 0; i < q.n; i++)
        printf("%d\n", q.queue_arr[i].prioritet);

    printf("\nAfter removing top element:\n");
    remove_from_top(&q);

    for (int i = 0; i < q.n; i++)
        printf("%d\n", q.queue_arr[i].prioritet);

    delete_queue(&q);
    return 0;
}