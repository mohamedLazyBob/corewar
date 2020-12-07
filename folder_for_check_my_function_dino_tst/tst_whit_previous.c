
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct  s_t
{
    char        *str;
    struct  s_t *previous;
    struct  s_t *next;
}               t_t;

void    ft_killi(t_t **carriage, t_t **proc)
{
    t_t *temp;



    if (((*carriage)->next == NULL && (*carriage)->previous == NULL)) /* only the last (*carriage)*/
    {
        free((*proc));
        (*proc) = NULL;
        (proc) = NULL;
        (*carriage) = NULL;
        (carriage) = NULL;
    }
    else if ((*carriage)->next == NULL) /*last curriage in the list order*/
    {
        free((*carriage));
        (*carriage)->previous->next = NULL;
        (*carriage) = NULL;

    }
    else
    {
        
        if ((*carriage)->previous == NULL) /* the first curriage in the list order*/
        {
            (*carriage) = (*carriage)->next;
            free((*carriage)->previous);
            (*carriage)->previous = NULL;
            (*proc) = (*carriage);

        }
        else
        {
            temp = (*carriage)->previous;
            temp->next = (*carriage)->next;
            (*carriage) = (*carriage)->next;
            (*carriage)->previous = temp;
        }
    }
}

void    ft_cheki(t_t **proc, int *cycle)
{
    t_t *carriage;
    int i = -1;

    carriage = *proc;


    while ((carriage))
    {
        (carriage) = (carriage)->next;
    }
    carriage = *proc;
    while ((carriage) != NULL)
    {
        if (!strcmp((carriage)->str, "1234"))
        {
            ft_killi(&carriage, proc); /* ft_kill_(*carriage) point to the next*/
        }
        else
            (carriage) = (carriage)->next;
    }
}


void ft_add_node(t_t **prev, char *str)
{
    
    t_t *node;

    node = (t_t*)malloc(sizeof(t_t));
    node->str = strdup(str);
    node->next = NULL;
    node->previous = *prev;
    //
    (*prev)->next = node;

}

void ft_inisialistion_node(t_t **node, char *str)
{
    (*node) = (t_t*)malloc(sizeof(t_t));
    (*node)->str = strdup(str);
    (*node)->next = NULL;
    (*node)->previous = NULL;
}


int main(int ac, char **av)
{
    t_t *data;
    t_t *head;
    t_t *head1;
    int i;

    i = 1;
    
    if (ac > 1)
    {

        while (i < ac)
        {
            if (i == 1)
            {
                ft_inisialistion_node(&data, av[i]);
                head = data;
            }
            else
            {
                ft_add_node(&data, av[i]);
                data = data->next;
            }
            i++;
        }
        head1 = head;
/*print list*/
        ft_cheki(&head, &i);
        while (head)
        {
            printf("%s\n", head->str);
            head = head->next;
        }
    }

    return (0);
}
