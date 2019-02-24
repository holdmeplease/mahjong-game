#include<Windows.h>
#pragma once

extern HWND hwnd;
extern HDC hdc;
extern HDC hdcmem;
extern HBITMAP hbitmap;
extern HBRUSH hbrush;

void paint_card_hand(int); //绘制玩家手牌
void paint_card_desk(int,int,int);//绘制桌面上的牌
void paint_card_computer();//绘制电脑手牌
void paint_name();//绘制桌面上的矩形框和“电脑”、“玩家”字样
void paint_word(int);//绘制其他字体
void paint_result(int);//绘制游戏结果
void paint_do(int);//绘制碰牌等操作图标
void paint_card_locked();//绘制死牌
void paint_computer_end();//游戏结束后绘制电脑所有牌

