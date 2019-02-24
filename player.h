#pragma once

//玩家类
class PLAYER{
public:
	int score;//分数
	bool isbacker;//庄家
	int card_hand[14];//活牌
	int card_hand_locked[16];//死牌
	int hand; //活牌数量
	int hand_locked; //死牌数量
};

bool Hu(int*);//胡牌的判断
bool is_hu(int,int);//是否符合胡牌条件
bool is_peng(int,int*,int);//是否符合碰牌条件
bool is_gang(int,int*,int);//是否符合明杠条件(别人出牌)
bool is_gang_white(int,int);//是否符合明杠条件(自己摸牌)
bool is_gang_black(int,int*);//是否符合暗杠条件
void peng_computer(int);//电脑碰牌
void gang_computer(int);//电脑玩家明杠
void hu_computer(int);//电脑玩家胡牌
void gang_human();//真人玩家明杠(别人出牌)
void gang_human_white();//真人玩家明杠(自己摸牌)
void gang_human_black();//真人玩家暗杠
void peng_human();//真人玩家碰牌
void hu_human();//真人玩家平胡
void discard_computer(int,int);//电脑出牌
void Getcard_computer(int);//电脑摸牌
void Getcard_human();//真人玩家摸牌
void discard_human(int);//真人玩家出牌
void gang_computer_white(int);//电脑明杠(自己摸牌)
void gang_computer_black(int pnum);//电脑暗杠(自己摸牌)
void sound_card(int);//播放出牌音效(同步方式)
void sound_do(int);//播放操作音效(同步方式)
void sound_do_human(int);//播放操作音效(异步方式)
void sound_card_human(int);//播放出牌音效(异步方式)