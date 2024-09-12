#include <stdio.h>
#include <inttypes.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LENGTH 1000

typedef struct list
{
   char word[20];
   struct list *next;
}list;

void add_word(struct list **head, const char *word)
{
    struct list *new_word = (struct list *)malloc(sizeof(struct list));
    strncpy(new_word->word, word, sizeof(new_word->word) - 1);
    new_word->word[sizeof(new_word->word) - 1] = '\0';
    new_word->next = NULL;
    if (*head == NULL)
        *head = new_word;
    else
    {
        struct list *current = *head;
        while (current->next != NULL)
            current = current->next;
        current->next = new_word;
    }
}

void swap_words(struct list *a, struct list *b)
{
    char temp[20];
    strncpy(temp, a->word, sizeof(temp) - 1);
    temp[sizeof(temp) - 1] = '\0';
    strncpy(a->word, b->word, sizeof(a->word) - 1);
    a->word[sizeof(a->word) - 1] = '\0';
    strncpy(b->word, temp, sizeof(b->word) - 1);
    b->word[sizeof(b->word) - 1] = '\0';
}

void sort_list(struct list *head)
{
    int swapped;
    struct list *ptr1;
    struct list *lptr = NULL;
    do
    {
        swapped = 0;
        ptr1 = head;
        while (ptr1->next != lptr)
        {
            if (strcmp(ptr1->word, ptr1->next->word) > 0)
            {
                swap_words(ptr1, ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}


void print_list(struct list *head)
{
    struct list *current = head;
    while (current != NULL)
    {
        printf("%s", current->word);
        if (current->next != NULL)
            printf(" ");
        current = current->next;
    }
    printf("\n");
}


void delete_list(struct list *head)
{
    struct list *tmp;
    while (head != NULL)
    {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}

int main(void)
{
	struct list *head = NULL;
    char input[MAX_LENGTH];
    fgets(input, sizeof(input), stdin);
    size_t len = strlen(input);
    if (len > 0 && input[len - 1] == '\n')
        input[len - 1] = '\0';
    len = strlen(input);
    if (len > 0 && input[len - 1] == '.')
        input[len - 1] = '\0';
    char *word = strtok(input, " ");
    while (word != NULL)
    {
        add_word(&head, word);
        word = strtok(NULL, " ");
    }

    sort_list(head);
    print_list(head);
    delete_list(head);

    return 0;
}