#include <stdlib.h>
#include <ft_list.h>

void ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)())
{
	t_list **list = begin_list;
	while (list)
	{
		if(!(cmp(data_ref, list->data)))
			free(list);
		list = list->next;
	}
}