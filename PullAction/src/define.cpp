#include "define.h"

void DrawImage(Math::Box2D draw, Math::Box2D src, int handle) {
	DrawRectExtendGraphF(draw.x, draw.y, draw.x + draw.w, draw.y + draw.h, (int)src.x, (int)src.y, int(src.x + src.w), int(src.y + src.h), handle, true);
}
void DrawImageRotate(Math::Box2D draw, Math::Box2D src, int handle, float radian) {
	Math::Vec center(draw.x, draw.y);
	Math::Rect drawrect(Math::Vec(draw.x - draw.w / 2.0f, draw.y - draw.h / 2.0f),
						Math::Vec(draw.x - draw.w / 2.0f + draw.w, draw.y - draw.h / 2.0f),
						Math::Vec(draw.x - draw.w / 2.0f, draw.y - draw.h / 2.0f + draw.h),
						Math::Vec(draw.x - draw.w / 2.0f + draw.w, draw.y - draw.h / 2.0f + draw.h));
	drawrect.Rotate(radian, center);
	DrawModiGraphF(drawrect.tl.x, drawrect.tl.y, drawrect.tr.x, drawrect.tr.y, drawrect.br.x, drawrect.br.y, drawrect.bl.x, drawrect.bl.y, handle, true);
}