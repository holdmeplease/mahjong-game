#pragma once

//枚举游戏进度，用于不同情况下的用户区刷新
enum MOMENT{
	create,//游戏初始化
	before_start,//游戏未开始
	playing,//电脑出牌阶段
	human,//玩家出牌阶段
	human_peng,//玩家碰牌
	human_gang,//玩家明杠(别人出牌)
	human_gang_black,//玩家暗杠
	human_gang_white,//玩家明杠(自己摸牌)
	human_hu,//玩家胡牌
	game_over,//游戏结束(有玩家胜利)
	no_winner //游戏结束(无人胜利)
};
extern MOMENT moment;