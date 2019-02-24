#include"player.h"
#pragma once

extern int card_front;//当前牌堆位置
extern int card_end;//牌堆末尾位置
extern int curr_player;//当前玩家
extern int desk_pos;//打过的牌有多少张
extern bool just_peng;//刚才是否碰过牌,影响玩家手牌的排序

//游戏类
class GAME{
public:
	int card_new[132]; //牌堆
	int card_desk[132];//出过的牌
	PLAYER player[4]; //player[0]表示真人玩家
	int backer;//庄家
};
extern GAME game;

void BubbleSort(int*,int);//冒泡排序，用于整理手牌
void random(int*,int);//洗牌算法
void deal_card();//发牌,对一些必要的量进行初始化
