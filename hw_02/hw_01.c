void* findMaxBlock(list *head)
{
    size_t max = 0;
    void *address = NULL;
    while(head)
    {
        if(head->size > max)
        {
            max = head->size;
            address = head->address;
        }
        head = head->next;
    }
        return address;
}