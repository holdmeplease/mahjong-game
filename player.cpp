#include"player.h"
#include"game.h"
#include"main.h"
#include"scene.h"
#pragma comment(lib, "winmm") 

//胡牌的判断
 bool Hu(int b[])
{
	 int i,j,k,x,flat=0;
     int a[14]={0};
     for(i=0; i<14; i++)
             a[i]=b[i];

     for (x=0; x<13; x++)  //在数组最后位置加一个数，便以下判断是否全部清0
    {
         if(a[x]==a[x+1]&& a[x]!=0 )//改变策略，除掉将牌
        {          
           a[x]=0;
           a[x+1]=0;
         }
        else continue;
      
         for(i=0; i<14; i++)                     //找出连续或相同的三个数，并标记为0
            for(j=0; j<14; j++)
                 for(k=0; k<14; k++) 
                 {
                     if(i==j||j==k||i==k) continue;
                     if( a[i]==a[j] && a[k]==a[j]||a[i]+1==a[j] && a[j]+1==a[k]&& a[i]!=0  )
                     {
                         a[i]=0; a[j]=0; a[k]=0;
                     }
                 }             
                 int    s=0; 
                 for(i=0;i<14;i++) 
                   {
                 s+=a[i];
                     }
                if(s!=0) //若加的将不胡，则下次试其他将时还回原值。
                {
                          for(i=0; i<14; i++)
                          a[i]=b[i];
                 
                 }
                if(s==0)
                 {
                    flat=1;
                    break;
                 }
    }
           if(flat)  
			   return 1;
           else     return 0;
}

 //是否符合胡牌条件
bool is_hu(int pnum,int c)
{
	int judge[14];
	for(int ii=0;ii<game.player[pnum].hand;ii++)
		judge[ii]=game.player[pnum].card_hand[ii];
	judge[game.player[pnum].hand]=c;
	for(int ii=game.player[pnum].hand+1;ii<14;ii++)
		judge[ii]=37;
	BubbleSort(judge,15) ;
	return Hu(judge);
}

//是否符合碰牌条件
bool is_peng(int pnum,int array[],int c)
{
	int flag=0;
	for(int i=0;i<game.player[pnum].hand;i++)
		if(array[i]==c)
			flag++;
	if(flag==2)
		return TRUE;
	else return FALSE;
}

//是否符合明杠条件(别人出牌)
bool is_gang(int pnum,int array[],int c)
{
	int flag=0;
	for(int i=0;i<game.player[pnum].hand;i++)
		if(array[i]==c)
			flag++;
	if(flag==3)
		return TRUE;
	else return FALSE;
}

//是否符合明杠条件(自己摸牌)
bool is_gang_white(int pnum,int c)
{
	int flag=0;
	for(int i=0;i<game.player[pnum].hand_locked;i++)
		if(game.player[pnum].card_hand_locked[i]==c)
			flag++;
	if(flag==3)
		return TRUE;
	else return FALSE;
}

//是否符合暗杠条件
bool is_gang_black(int pnum,int array[])
{
	int flag=0;
	for(int i=0;i<game.player[pnum].hand;i++)
		if(array[i]==array[game.player[pnum].hand])
			flag++;
	if(flag==3)
		return TRUE;
	else return FALSE;
}

//电脑碰牌
void peng_computer(int pnum)
{
	int _end=game.player[pnum].hand;
	curr_player=pnum;
	for(int i=0,flag=0;i<_end,flag<2;i++)
		if(game.player[pnum].card_hand[i]==game.card_desk[desk_pos-1])
		{
			game.player[pnum].card_hand_locked[game.player[pnum].hand_locked]=game.card_desk[desk_pos-1];
			game.player[pnum].card_hand[i]=game.player[pnum].card_hand[game.player[pnum].hand-1];
			game.player[pnum].hand--;
			game.player[pnum].hand_locked++;
			flag++;
		}
	game.player[pnum].card_hand_locked[game.player[pnum].hand_locked]=game.card_desk[desk_pos-1];
	game.player[pnum].hand--;
	game.player[pnum].hand_locked++;
	desk_pos--;
	sound_do_human(1);
}

//电脑明杠(别人出牌)
void gang_computer(int pnum)
{
	int _end=game.player[pnum].hand;
	curr_player=pnum;
	for(int i=0,flag=0;i<_end,flag<3;i++)
		if(game.player[pnum].card_hand[i]==game.card_desk[desk_pos-1])
		{
			game.player[pnum].card_hand_locked[game.player[pnum].hand_locked]=game.card_desk[desk_pos-1];
			game.player[pnum].card_hand[i]=game.player[pnum].card_hand[game.player[pnum].hand-1];
			game.player[pnum].hand--;
			game.player[pnum].hand_locked++;
			flag++;
		}
	game.player[pnum].card_hand_locked[game.player[pnum].hand_locked]=game.card_desk[desk_pos-1];
	game.player[pnum].card_hand[game.player[pnum].hand]=game.card_new[card_end]; //从牌尾摸牌
	card_end--;
	game.player[pnum].hand_locked++;
	desk_pos--;
	sound_do_human(2);
}

//电脑明杠(自己摸牌)
void gang_computer_white(int pnum)
{
	curr_player=pnum;
	game.player[pnum].card_hand_locked[game.player[pnum].hand_locked]=game.player[pnum].card_hand[game.player[pnum].hand];
	game.player[pnum].hand_locked++;
	BubbleSort(game.player[pnum].card_hand_locked,game.player[pnum].hand_locked+1);
	game.player[pnum].card_hand[game.player[pnum].hand]=game.card_new[card_end];
	card_end--;
	sound_do_human(2);
}

//电脑暗杠(自己摸牌)
void gang_computer_black(int pnum)
{
	int _end=game.player[pnum].hand;
	curr_player=pnum;
	int c=game.player[pnum].card_hand[game.player[pnum].hand];
	for(int i=0,flag=0;i<_end,flag<3;i++)
		if(game.player[pnum].card_hand[i]==c)
		{
			game.player[pnum].card_hand_locked[game.player[pnum].hand_locked]=c;
			game.player[pnum].card_hand[i]=game.player[pnum].card_hand[game.player[pnum].hand-1];
			game.player[pnum].hand--;
			game.player[pnum].hand_locked++;
			flag++;
		}
	game.player[pnum].card_hand_locked[game.player[pnum].hand_locked]=c;
	game.player[pnum].card_hand[game.player[pnum].hand]=game.card_new[card_end]; //从牌尾摸牌
	card_end--;
	game.player[pnum].hand_locked++;
	sound_do_human(2);
}

//电脑玩家平胡
void hu_computer(int pnum)
{
	curr_player=pnum;
	game.player[pnum].card_hand[game.player[pnum].hand]=game.card_desk[desk_pos-1];
	desk_pos--;
	sound_do_human(3);
}

//真人玩家明杠(别人出牌)
void gang_human()
{
	int _end=game.player[0].hand;
	curr_player=0;
	for(int i=0,flag=0;i<_end,flag<3;i++)
		if(game.player[0].card_hand[i]==game.card_desk[desk_pos-1])
		{
			game.player[0].card_hand_locked[game.player[0].hand_locked]=game.card_desk[desk_pos-1];
			game.player[0].card_hand[i]=game.player[0].card_hand[game.player[0].hand-1];
			game.player[0].hand--;
			game.player[0].hand_locked++;
			flag++;
		}
	game.player[0].card_hand_locked[game.player[0].hand_locked]=game.card_desk[desk_pos-1];
	game.player[0].card_hand[game.player[0].hand]=game.card_new[card_end]; //从牌尾摸牌
	card_end--;
	game.player[0].hand_locked++;
	desk_pos--;
}

//真人玩家明杠(自己摸牌)
void gang_human_white()
{
	curr_player=0;
	game.player[0].card_hand_locked[game.player[0].hand_locked]=game.player[0].card_hand[game.player[0].hand];
	game.player[0].hand_locked++;
	BubbleSort(game.player[0].card_hand_locked,game.player[0].hand_locked+1);
	game.player[0].card_hand[game.player[0].hand]=game.card_new[card_end];
	card_end--;
}

//真人玩家暗杠
void gang_human_black()
{
	int _end=game.player[0].hand;
	curr_player=0;
	int c=game.player[0].card_hand[game.player[0].hand];
	for(int i=0,flag=0;i<_end,flag<3;i++)
		if(game.player[0].card_hand[i]==c)
		{
			game.player[0].card_hand_locked[game.player[0].hand_locked]=c;
			game.player[0].card_hand[i]=game.player[0].card_hand[game.player[0].hand-1];
			game.player[0].hand--;
			game.player[0].hand_locked++;
			flag++;
		}
	game.player[0].card_hand_locked[game.player[0].hand_locked]=c;
	game.player[0].card_hand[game.player[0].hand]=game.card_new[card_end]; //从牌尾摸牌
	card_end--;
	game.player[0].hand_locked++;
}

//真人玩家碰牌
void peng_human()
{
	int _end=game.player[0].hand;
	curr_player=0;
	just_peng=1;
	for(int i=0,flag=0;i<_end,flag<2;i++)
		if(game.player[0].card_hand[i]==game.card_desk[desk_pos-1])
		{
			game.player[0].card_hand_locked[game.player[0].hand_locked]=game.card_desk[desk_pos-1];
			game.player[0].card_hand[i]=game.player[0].card_hand[game.player[0].hand-1];
			game.player[0].hand--;
			game.player[0].hand_locked++;
			flag++;
		}
	game.player[0].card_hand_locked[game.player[0].hand_locked]=game.card_desk[desk_pos-1];
	game.player[0].hand--;
	game.player[0].hand_locked++;
	desk_pos--;
}

//真人玩家平胡
void hu_human()
{
	curr_player=0;
	game.player[0].card_hand[game.player[0].hand]=game.card_desk[desk_pos-1];
	desk_pos--;
}

//电脑出牌
void discard_computer(int pnum,int cnum)
{
	game.card_desk[desk_pos]=game.player[pnum].card_hand[game.player[pnum].hand];
	sound_card_human(game.card_desk[desk_pos]);
	game.player[pnum].card_hand[game.player[pnum].hand]=0;
	desk_pos++;
	for(int i=curr_player+1;i<curr_player+4;i++)
	{
		if(is_hu((i)%4,game.card_desk[desk_pos-1]))
		{
			if((i)%4==0)
			{
				moment=human_hu;
				InvalidateRect(hwnd,NULL,1);
				return;
			}
			else
			{    
				hu_computer(i%4);
				moment=game_over;
				InvalidateRect(hwnd,NULL,1);
				return;
			}
		}
	}
	for(int i=curr_player+1;i<curr_player+4;i++)
	{
		if(is_gang(i%4,game.player[i%4].card_hand,game.card_desk[desk_pos-1]))
		{
			if(i%4==0)
			{
				moment=human_gang;
				InvalidateRect(hwnd,NULL,1);
				return;
			}
			else
			{
				gang_computer(i%4);
				discard_computer(curr_player,0);
				moment=playing;
				InvalidateRect(hwnd,NULL,1);
				return;
			}
		}
	}
	for(int i=curr_player+1;i<curr_player+4;i++)
	{
		if(is_peng(i%4,game.player[i%4].card_hand,game.card_desk[desk_pos-1]))
		{
			if(i%4==0)
			{
				moment=human_peng;
				InvalidateRect(hwnd,NULL,1);
				return;
			}
			else
			{
				peng_computer(i%4);
				discard_computer(curr_player,0);
				moment=playing;
				InvalidateRect(hwnd,NULL,1);
				return;
			}
		}
	}
}

//电脑摸牌
void Getcard_computer(int pnum)
{
		if(card_front>card_end)
		{
			moment=no_winner;
			InvalidateRect(hwnd,NULL,1);
		}
		curr_player=pnum;
	    game.player[pnum].card_hand[game.player[pnum].hand]=game.card_new[card_front];
	    card_front++;
		if(is_hu(pnum,game.player[pnum].card_hand[game.player[pnum].hand]))
	    {
			moment=game_over;
		    InvalidateRect(hwnd,NULL,1);
			sound_do_human(3);
		    return;
	    }
		if(is_gang_black(pnum,game.player[pnum].card_hand))
	    {
		    gang_computer_black(pnum);
			discard_computer(pnum,0);
			moment=playing;
		    InvalidateRect(hwnd,NULL,1);
		    return;
	    }
	    if(is_gang_white(pnum,game.player[pnum].card_hand[game.player[pnum].hand]))
	    {
		    gang_computer_white(pnum);
			discard_computer(pnum,0);
			moment=playing;
		    InvalidateRect(hwnd,NULL,1);
		    return;
	    }
		discard_computer(pnum,game.player[pnum].hand);
}

//真人玩家摸牌
void Getcard_human()
{
	if(card_front>card_end)
	{
		moment=no_winner;
		InvalidateRect(hwnd,NULL,1);
		return;
	}
	curr_player=0;
	game.player[0].card_hand[game.player[0].hand]=game.card_new[card_front];
	card_front++;
	if(is_hu(0,game.player[0].card_hand[game.player[0].hand]))
	{
		moment=human_hu;
		InvalidateRect(hwnd,NULL,1);
		return;
	}
	if(is_gang_black(0,game.player[0].card_hand))
	{
		moment=human_gang_black;
		InvalidateRect(hwnd,NULL,1);
		return;
	}
	if(is_gang_white(0,game.player[0].card_hand[game.player[0].hand]))
	{
		moment=human_gang_white;
		InvalidateRect(hwnd,NULL,1);
		return;
	}
}

//真人玩家出牌
void discard_human(int pos)
{
	game.card_desk[desk_pos]=game.player[0].card_hand[pos];	
	game.player[0].card_hand[pos]=game.player[0].card_hand[game.player[0].hand];
	game.player[0].card_hand[game.player[0].hand]=0;
	desk_pos++;	
}

//播放出牌音效(异步方式)
void sound_card_human(int i)
{
	switch(i)
	{
	case 1:
		PlaySound("sound\\一万.wav",NULL,SND_ASYNC);
		break;
	case 2:
		PlaySound("sound\\二万.wav",NULL,SND_ASYNC);
		break;
	case 3:
		PlaySound("sound\\三万.wav",NULL,SND_ASYNC);
		break;
	case 4:
		PlaySound("sound\\四万.wav",NULL,SND_ASYNC);
		break;
	case 5:
		PlaySound("sound\\五万.wav",NULL,SND_ASYNC);
		break;
	case 6:
		PlaySound("sound\\六万.wav",NULL,SND_ASYNC);
		break;
	case 7:
		PlaySound("sound\\七万.wav",NULL,SND_ASYNC);
		break;
	case 8:
		PlaySound("sound\\八万.wav",NULL,SND_ASYNC);
		break;
	case 9:
		PlaySound("sound\\九万.wav",NULL,SND_ASYNC);
		break;
	case 11:
		PlaySound("sound\\一条.wav",NULL,SND_ASYNC);
		break;
	case 12:
		PlaySound("sound\\二条.wav",NULL,SND_ASYNC);
		break;
	case 13:
		PlaySound("sound\\三条.wav",NULL,SND_ASYNC);
		break;
	case 14:
		PlaySound("sound\\四条.wav",NULL,SND_ASYNC);
		break;
	case 15:
		PlaySound("sound\\五条.wav",NULL,SND_ASYNC);
		break;
	case 16:
		PlaySound("sound\\六条.wav",NULL,SND_ASYNC);
		break;
	case 17:
		PlaySound("sound\\七条.wav",NULL,SND_ASYNC);
		break;
	case 18:
		PlaySound("sound\\八条.wav",NULL,SND_ASYNC);
		break;
	case 19:
		PlaySound("sound\\九条.wav",NULL,SND_ASYNC);
		break;
	case 21:
		PlaySound("sound\\一筒.wav",NULL,SND_ASYNC);
		break;
	case 22:
		PlaySound("sound\\二筒.wav",NULL,SND_ASYNC);
		break;
	case 23:
		PlaySound("sound\\三筒.wav",NULL,SND_ASYNC);
		break;
	case 24:
		PlaySound("sound\\四筒.wav",NULL,SND_ASYNC);
		break;
	case 25:
		PlaySound("sound\\五筒.wav",NULL,SND_ASYNC);
		break;
	case 26:
		PlaySound("sound\\六筒.wav",NULL,SND_ASYNC);
		break;
	case 27:
		PlaySound("sound\\七筒.wav",NULL,SND_ASYNC);
		break;
	case 28:
		PlaySound("sound\\八筒.wav",NULL,SND_ASYNC);
		break;
	case 29:
		PlaySound("sound\\九筒.wav",NULL,SND_ASYNC);
		break;
	case 31:
		PlaySound("sound\\东风.wav",NULL,SND_ASYNC);
		break;
	case 32:
		PlaySound("sound\\南风.wav",NULL,SND_ASYNC);
		break;
	case 33:
		PlaySound("sound\\西风.wav",NULL,SND_ASYNC);
		break;
	case 34:
		PlaySound("sound\\北风.wav",NULL,SND_ASYNC);
		break;
	case 35:
		PlaySound("sound\\红中.wav",NULL,SND_ASYNC);
		break;
	case 36:
		PlaySound("sound\\发财.wav",NULL,SND_ASYNC);
		break;
	default:
		break;
	}
}

//播放出牌音效(同步方式)
void sound_card(int i)
{
	switch(i)
	{
	case 1:
		PlaySound("sound\\一万.wav",NULL,SND_SYNC);
		break;
	case 2:
		PlaySound("sound\\二万.wav",NULL,SND_SYNC);
		break;
	case 3:
		PlaySound("sound\\三万.wav",NULL,SND_SYNC);
		break;
	case 4:
		PlaySound("sound\\四万.wav",NULL,SND_SYNC);
		break;
	case 5:
		PlaySound("sound\\五万.wav",NULL,SND_SYNC);
		break;
	case 6:
		PlaySound("sound\\六万.wav",NULL,SND_SYNC);
		break;
	case 7:
		PlaySound("sound\\七万.wav",NULL,SND_SYNC);
		break;
	case 8:
		PlaySound("sound\\八万.wav",NULL,SND_SYNC);
		break;
	case 9:
		PlaySound("sound\\九万.wav",NULL,SND_SYNC);
		break;
	case 11:
		PlaySound("sound\\一条.wav",NULL,SND_SYNC);
		break;
	case 12:
		PlaySound("sound\\二条.wav",NULL,SND_SYNC);
		break;
	case 13:
		PlaySound("sound\\三条.wav",NULL,SND_SYNC);
		break;
	case 14:
		PlaySound("sound\\四条.wav",NULL,SND_SYNC);
		break;
	case 15:
		PlaySound("sound\\五条.wav",NULL,SND_SYNC);
		break;
	case 16:
		PlaySound("sound\\六条.wav",NULL,SND_SYNC);
		break;
	case 17:
		PlaySound("sound\\七条.wav",NULL,SND_SYNC);
		break;
	case 18:
		PlaySound("sound\\八条.wav",NULL,SND_SYNC);
		break;
	case 19:
		PlaySound("sound\\九条.wav",NULL,SND_SYNC);
		break;
	case 21:
		PlaySound("sound\\一筒.wav",NULL,SND_SYNC);
		break;
	case 22:
		PlaySound("sound\\二筒.wav",NULL,SND_SYNC);
		break;
	case 23:
		PlaySound("sound\\三筒.wav",NULL,SND_SYNC);
		break;
	case 24:
		PlaySound("sound\\四筒.wav",NULL,SND_SYNC);
		break;
	case 25:
		PlaySound("sound\\五筒.wav",NULL,SND_SYNC);
		break;
	case 26:
		PlaySound("sound\\六筒.wav",NULL,SND_SYNC);
		break;
	case 27:
		PlaySound("sound\\七筒.wav",NULL,SND_SYNC);
		break;
	case 28:
		PlaySound("sound\\八筒.wav",NULL,SND_SYNC);
		break;
	case 29:
		PlaySound("sound\\九筒.wav",NULL,SND_SYNC);
		break;
	case 31:
		PlaySound("sound\\东风.wav",NULL,SND_SYNC);
		break;
	case 32:
		PlaySound("sound\\南风.wav",NULL,SND_SYNC);
		break;
	case 33:
		PlaySound("sound\\西风.wav",NULL,SND_SYNC);
		break;
	case 34:
		PlaySound("sound\\北风.wav",NULL,SND_SYNC);
		break;
	case 35:
		PlaySound("sound\\红中.wav",NULL,SND_SYNC);
		break;
	case 36:
		PlaySound("sound\\发财.wav",NULL,SND_SYNC);
		break;
	default:
		break;
	}
}

//播放操作音效(同步方式)
void sound_do(int i)
{
	switch(i)
	{
	case 1:
		PlaySound("sound\\碰.wav",NULL,SND_SYNC);
		break;
	case 2:
		PlaySound("sound\\杠.wav",NULL,SND_SYNC);
		break;
	case 3:
		PlaySound("sound\\胡.wav",NULL,SND_SYNC);
		break;
	default:
		break;
	}
}

//播放操作音效(异步方式)
void sound_do_human(int i)
{
	switch(i)
	{
	case 1:
		PlaySound("sound\\碰.wav",NULL,SND_ASYNC);
		break;
	case 2:
		PlaySound("sound\\杠.wav",NULL,SND_ASYNC);
		break;
	case 3:
		PlaySound("sound\\胡.wav",NULL,SND_ASYNC);
		break;
	default:
		break;
	}
}