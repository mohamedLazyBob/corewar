
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct  s_t
{
    char        *str;
    struct  s_t *next;
}               t_t;

void    ft_killi(t_t **carriage)
{
    t_t *temp;

if ((*carriage)->next->next == NULL) /*last curriage in the list order*/
    {
        free((*carriage)->next);
        (*carriage)->next = NULL;
    }
    else
    {
        temp = (*carriage);
        temp->next = (*carriage)->next->next;
        (*carriage) = (*carriage)->next->next;
        (*carriage) = temp;
    }
}

void    ft_cheki(t_t **proc, int *cycle)
{
    t_t *carriage;
    int i = -1;

    carriage = *proc;

    if (carriage != NULL && carriage->next == NULL && (!strcmp((carriage)->str, "1234"))) /* the first curriage in the list order*/
    {
        free((*proc));
        (*proc) = NULL;
        (proc) = NULL;
        (carriage) = NULL;
    }
    else if (carriage != NULL && carriage->next != NULL && (!strcmp((carriage)->str, "1234"))) /* the first curriage in the list order*/
    {
        (carriage) = (carriage)->next;
        free(*proc);
        (*proc) = (carriage);
}
    while (carriage != NULL && carriage->next != NULL)
    {

        if (!strcmp((carriage)->next->str, "1234"))
        {
            ft_killi(&carriage);
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
    (*prev)->next = node;

}

void ft_inisialistion_node(t_t **node, char *str)
{
    (*node) = (t_t*)malloc(sizeof(t_t));
    (*node)->str = strdup(str);
    (*node)->next = NULL;
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
