size_t total_memory_usage(list *head) 
{
    size_t total_size = 0;

    while (head) 
    {
        total_size += head->size;
        head = head->next;
    }
    return total_size;
}