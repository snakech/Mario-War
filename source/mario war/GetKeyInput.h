#ifndef			GETKEYINPUT_H
#define			GETKEYINPUT_H
#define KEYDOWN(vk_code)   ((GetAsyncKeyState(vk_code)&0x8000?1:0)) 
extern bool		IsKeyDown(int _key);
extern bool		PressLeftButton(int *x, int *y);
extern bool		PressRightButton(int *x, int *y);
extern void		GetMousePos(int *x, int *y);
#endif