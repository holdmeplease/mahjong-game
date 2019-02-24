#include<time.h>
#include<Windows.h>
#include"game.h"

int card_front;//当前牌堆位置
int card_end;//牌堆末尾位置
int curr_player;//当前玩家
int desk_pos;//打过的牌有多少张
bool just_peng;//刚才是否碰过牌,影响玩家手牌的排序

GAME game;

//冒泡排序，用于整理手牌
void BubbleSort(int array[], int n)  
{  
    int temp;
	for (int i = 0; i < n-1; i++)  
    {  
        for (int j = i + 1; j < n-1; j++)  
        {  
            if (array[i]>array[j])  
			{
				temp = array[i];  
				array[i] = array[j];  
                array[j] = temp; 
			}  
        }  
    }  
}  

//洗牌算法
void random(int a[], int n)  
{  
   int index, tmp, i;  
   srand(unsigned(time(NULL)));    
    for(i=n-1; i>0; i--)  
    {  
        index=rand()%i;  
        tmp=a[i];  
        a[i]=a[index];  
        a[index]=tmp;  
    }  
}

//发牌,对一些必要的量进行初始化
void deal_card() 
{
    card_front=0;//当前牌堆位置
    card_end=131;//牌堆末尾位置
    curr_player=1;//当前玩家
    desk_pos=0;//打过的牌有多少张
	just_peng=0;
	for(int i=0;i<4;i++)
	{
		game.player[i].hand=13;
		game.player[i].hand_locked=0;
	}
	for(int i=0,j=0;i<33;i++,j++)
	{
		if((j+1)%10==0)
			j++;
		game.card_new[i]=j+1;
	}
	for(int i=33;i<132;i++)
		game.card_new[i]=game.card_new[i%33];
	random(game.card_new,132);//洗牌
	for(int i=0;i<13;i++)
	{
		game.player[0].card_hand[i]=game.card_new[i];
	}
	for(int i=13;i<26;i++)
	{
		game.player[1].card_hand[i%13]=game.card_new[i];
	}
	for(int i=26;i<39;i++)
	{
		game.player[2].card_hand[i%13]=game.card_new[i];
	}
	for(int i=39;i<52;i++)
	{
		game.player[3].card_hand[i%13]=game.card_new[i];
	}
	for(int i=0;i<52;i++)
		game.card_new[i]=0;
	card_front=52;
}