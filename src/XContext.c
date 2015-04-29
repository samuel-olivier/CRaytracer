#include "XContext.h"

#include <stdlib.h>
#include <mlx.h>

#include "Time.h"

static int	frameFunction(void *param);

typedef struct
{
	XContext			*this;
	int					fps;
	XContext_FrameHook	framePtr;
	void				*params;
	Time				timer;
}						FrameParam;

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

void		XContext_displayLoop(XContext *this, int fps, XContext_FrameHook frameFunc, void *params)
{
	FrameParam	data;

	data.this = this;
	data.fps = fps;
	data.framePtr = frameFunc;
	data.params = params;
	Time_init(&data.timer);
	mlx_loop_hook(this->server, &frameFunction, &data);
	mlx_loop(this->server);
}

static int	frameFunction(void *param)
{
	FrameParam *data = param;

	Time_update(&data->timer);
	if (data->framePtr != NULL) {
		data->framePtr(data->params);
	}
	XContext_display(data->this);
	float	toSleep = (1.f / data->fps) - Time_elapsed(&data->timer);
	if (toSleep > 0.f) {
		Time_sleep(toSleep);
	}
	return 0;
}