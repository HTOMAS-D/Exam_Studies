#ifndef List_h
#define List_h

typedef struct s_list
{
	struct s_list *next;
	void *data;
} t_list;

#endif