#ifndef __X_CONTEXT__
#define __X_CONTEXT__

#include "Image.h"

typedef struct	sXContext
{
	void		*server;
	void		*window;
	Image		*displayImage;
}				XContext;

typedef void	(*XContext_FrameHook)(void *params);

XContext	*XContext_new();
void		XContext_delete(XContext *this);

int			XContext_createWindow(XContext *this, int width, int height, char *title);
void		XContext_display(XContext *this);
void		XContext_displayLoop(XContext *this, int fps, XContext_FrameHook frameFunc, void *params);

#endif