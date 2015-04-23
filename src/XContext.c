#include "XContext.h"

#include <stdlib.h>
#include <mlx.h>

XContext	*XContext_new()
{
	XContext	*this = malloc(sizeof(*this));

	this->server = mlx_init();
	if (this->server == NULL) {
		free(this);
		return NULL;
	}
	this->window = NULL;
	this->displayImage = NULL;
	return this;
}

void		XContext_delete(XContext *this)
{
	free(this);
}

int			XContext_createWindow(XContext *this, int width, int height, char *title)
{
	if (this->server != NULL && this->window == NULL && width > 0 && height > 0) {
		this->window = mlx_new_window(this->server, width, height, title);
		if (this->window == NULL) {
			return 0;
		}
		this->displayImage = Image_new(this, width, height);
		return 1;
	}
	return 0;
}

void		XContext_display(XContext *this)
{
	if (this->displayImage != NULL) {
		Image_putToWindow(this->displayImage, this, 0, 0);
	}
}