#include "List.h"

#include <unistd.h>
#include <stdlib.h>

static ListItem	*List_newItem(void *data);


List	List_new()
{
	return NULL;
}

void	List_delete(List *this, List_deleteFunction funcPtr)
{
	ListItem	*it = *this;
	ListItem	*current = NULL;

	while (it != NULL) {
		if (funcPtr != NULL) {
			funcPtr(it->data);
		}
		current = it;
		it = it->next;
		free(current);
	}
}

void	List_append(List *this, void *data)
{
	ListItem	*item = List_newItem(data);

	if (*this == NULL) {
		*this = item;
		return ;
	}

	ListItem	*it = *this;
	while (it->next != NULL) {
		it = it->next;
	}
	it->next = item;
}

void	List_prepend(List *this, void *data)
{
	ListItem	*item = List_newItem(data);

	item->next = *this;
	*this = item;
}

int List_length(List *this)
{
	ListItem	*it = *this;
	int			length = 0;

	while (it != NULL) {
		it = it->next;
		++length;
	}
	return length;
}

void  List_foreach(List *this, List_foreachFunction funcPtr, void *param)
{
	if (funcPtr == NULL) {
		return ;
	}
	ListItem	*it = *this;
	int			idx = 0;

	while (it != NULL) {
		funcPtr(idx, it->data, param);
		it = it->next;
		++idx;
	}
}

int List_removeIf(List *this, List_removeIfFunction funcPtr, void *param)
{
	if (funcPtr == NULL) {
		return 0;
	}
	ListItem	*it = *this;
	ListItem	*prev = NULL;
	int			idx = 0;
	int			nbRemoved = 0;

	while (it != NULL) {
		if (funcPtr(idx, it->data, param)) {
			ListItem	*current = it;

			if (prev == NULL) {
				*this = current->next;
			} else {
				prev->next = current->next;
			}
			it = it->next;
			free(current);
			++nbRemoved;
		} else {
			prev = it;
			it = it->next;
			++idx;
		}
	}
	return nbRemoved;
}

static ListItem*  List_newItem(void* data)
{
	ListItem*	item = malloc(sizeof(*item));

	item->next = NULL;
	item->data = data;
	return item;
}