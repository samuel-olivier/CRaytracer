#ifndef __LIST__
#define __LIST__

typedef struct		s_ListItem
{
  void				*data;
  struct s_ListItem	*next;
}					ListItem;

typedef ListItem* 	List;
typedef void 		(*List_foreachFunction)(int idx, void *data, void *param);
typedef int 		(*List_removeIfFunction)(int idx, void *data, void *param);
typedef void 		(*List_deleteFunction)(void *data);

List	List_new();
void	List_delete(List *this, List_deleteFunction funcPtr);

void	List_append(List *this, void *data);
void	List_prepend(List *this, void *data);
int		List_length(List *this);
void	List_foreach(List *this, List_foreachFunction funcPtr, void *param);
int		List_removeIf(List *this, List_removeIfFunction funcPtr, void *param);

#endif