#ifndef __X_CONTEXT__
#define __X_CONTEXT__

#include "Image.h"

typedef struct	sXContext
{
	void		*server;
	void		*window;
	Image		*displayImage;
}				XContext;

XContext	*XContext_new();
void		XContext_delete(XContext *this);

int			XContext_createWindow(XContext *this, int width, int height, char *title);
void		XContext_display(XContext *this);

#endif