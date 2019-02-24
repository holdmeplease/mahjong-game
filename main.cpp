#include<stdio.h>
#include"main.h"
#include"scene.h"
#include"game.h"
#include"player.h"

MOMENT moment=create;//游戏进程变量
HWND hwnd; //窗口句柄

//窗口处理函数
LRESULT WINAPI WndProc(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam)
{
	PAINTSTRUCT ps;
	SetStretchBltMode(hdc, STRETCH_HALFTONE);
	switch(message)
	{
	case WM_CREATE:		
		hdc=GetDC(hwnd);
		hdcmem=CreateCompatibleDC(hdc);
		ReleaseDC(hwnd,hdc);
	case WM_PAINT:
		switch(moment)
		{
		case create:
			hdc=BeginPaint(hwnd,&ps);
			paint_name();
			paint_word(1);
		    EndPaint(hwnd,&ps);
			break;
		case before_start:
			hdc=BeginPaint(hwnd,&ps);         	
		    paint_name();
			paint_card_computer();
			paint_word(2);
			deal_card();
			BubbleSort(game.player[0].card_hand,game.player[0].hand+1);
			for(int i=0;i<game.player[0].hand;i++) //玩家手牌
				paint_card_hand(i);
		    EndPaint(hwnd,&ps);
			break;
		case playing:
			hdc=BeginPaint(hwnd,&ps);	
		    paint_name();
			paint_card_computer();
			paint_word(3);
			BubbleSort(game.player[0].card_hand,game.player[0].hand+1);
			for(int i=0;i<game.player[0].hand;i++) //玩家手牌
			{
				paint_card_hand(i);
			}
			for(int i=0,flag=0;i<desk_pos;i++) //已经打过的牌
			{
				paint_card_desk(game.card_desk[i],250+30*(i%23),110+50*(flag/23));
				flag++;
			}
			paint_card_locked();//碰过或杠过的牌
			EndPaint(hwnd,&ps);
			break;
		case human:
			hdc=BeginPaint(hwnd,&ps);		        	
		    paint_name();
			paint_card_computer();
			paint_word(4);
			if(just_peng)
			{
				BubbleSort(game.player[0].card_hand,game.player[0].hand+2);
			    for(int i=0;i<game.player[0].hand+1;i++) //玩家手牌
				    paint_card_hand(i);
				just_peng=0;
			}
			else
			{
			    BubbleSort(game.player[0].card_hand,game.player[0].hand+1);
			    for(int i=0;i<=game.player[0].hand;i++) //玩家手牌
				    paint_card_hand(i);
			 }
			for(int i=0,flag=0;i<desk_pos;i++) //已经打过的牌
			{
				paint_card_desk(game.card_desk[i],250+30*(i%23),110+50*(flag/23));
				flag++;
			}
			paint_card_locked();//碰过或杠过的牌
		    EndPaint(hwnd,&ps);
			break;
		case human_peng:
			hdc=BeginPaint(hwnd,&ps);       	
		    paint_name();
			paint_card_computer();
			paint_do(1);
			BubbleSort(game.player[0].card_hand,game.player[0].hand+1);
			for(int i=0;i<game.player[0].hand;i++) //真人玩家手牌
				paint_card_hand(i);
			for(int i=0,flag=0;i<desk_pos;i++) //已经打过的牌
			{
				paint_card_desk(game.card_desk[i],250+30*(i%23),110+50*(flag/23));
				flag++;
			}
			paint_card_locked();//碰过或杠过的牌
			EndPaint(hwnd,&ps);
			break;
		case human_gang:
			hdc=BeginPaint(hwnd,&ps);		 
		    paint_name();
			paint_card_computer();
			paint_do(4);
			BubbleSort(game.player[0].card_hand,game.player[0].hand+1);
			for(int i=0;i<game.player[0].hand;i++) //真人玩家手牌
				paint_card_hand(i);
			for(int i=0,flag=0;i<desk_pos;i++) //已经打过的牌
			{
				paint_card_desk(game.card_desk[i],250+30*(i%23),110+50*(flag/23));
				flag++;
			}
			paint_card_locked();//碰过或杠过的牌
			EndPaint(hwnd,&ps);
			break;
		case human_gang_black:
			hdc=BeginPaint(hwnd,&ps);   	
		    paint_name();
			paint_card_computer();
			paint_do(2);
			BubbleSort(game.player[0].card_hand,game.player[0].hand+1);
			for(int i=0;i<=game.player[0].hand;i++) //真人玩家手牌
				paint_card_hand(i);
			for(int i=0,flag=0;i<desk_pos;i++) //已经打过的牌
			{
				paint_card_desk(game.card_desk[i],250+30*(i%23),110+50*(flag/23));
				flag++;
			}
			paint_card_locked();//碰过或杠过的牌
			EndPaint(hwnd,&ps);
			break;
		case human_gang_white:
			hdc=BeginPaint(hwnd,&ps);   	
		    paint_name();
			paint_card_computer();
			paint_do(2);
			BubbleSort(game.player[0].card_hand,game.player[0].hand+1);
			for(int i=0;i<=game.player[0].hand;i++) //真人玩家手牌
				paint_card_hand(i);
			for(int i=0,flag=0;i<desk_pos;i++) //已经打过的牌
			{
				paint_card_desk(game.card_desk[i],250+30*(i%23),110+50*(flag/23));
				flag++;
			}
			paint_card_locked();//碰过或杠过的牌
			EndPaint(hwnd,&ps);
			break;
		case human_hu:
			hdc=BeginPaint(hwnd,&ps);		     	
		    paint_name();
			paint_card_computer();
			paint_do(3);
			BubbleSort(game.player[0].card_hand,game.player[0].hand+1);
			for(int i=0,j=50;i<game.player[0].hand;i++) //真人玩家手牌
				paint_card_hand(i);
			if(curr_player%4==0) //最后一张手牌
				paint_card_hand(game.player[0].hand);
			for(int i=0,flag=0;i<desk_pos;i++) //已经打过的牌
			{
				paint_card_desk(game.card_desk[i],250+30*(i%23),110+50*(flag/23));
				flag++;
			}
			paint_card_locked();//碰过或杠过的牌
			EndPaint(hwnd,&ps);
			break;
		case game_over:
			hdc=BeginPaint(hwnd,&ps);		        	
		    paint_name();
			paint_word(5);
			paint_result(1);
			if(curr_player==0)
			{
			    BubbleSort(game.player[0].card_hand,game.player[0].hand+2);
			    for(int i=0,j=50;i<=game.player[0].hand;i++) //真人玩家手牌
				    paint_card_hand(i);
			}
			else
			{
				BubbleSort(game.player[0].card_hand,game.player[0].hand+1);
			    for(int i=0,j=50;i<game.player[0].hand;i++) //真人玩家手牌
				    paint_card_hand(i);
			}
			for(int i=0,flag=0;i<desk_pos;i++) //已经打过的牌
			{
				paint_card_desk(game.card_desk[i],250+30*(i%23),110+50*(flag/23));
				flag++;
			}
			for(int i=0,j=30;i<game.player[0].hand_locked;i++) //碰过或杠过的牌
				paint_card_desk(game.player[0].card_hand_locked[i],250+30*i,610);
			for(int i=1;i<4;i++) //给电脑手牌排序
			{
				BubbleSort(game.player[i].card_hand,game.player[i].hand+1);
			}
			paint_computer_end();//绘制电脑的所有牌   
			if(curr_player==1)//单独绘制导致胡牌的一张牌
				paint_card_desk(game.player[1].card_hand[game.player[1].hand],970,275);
			else if(curr_player==2)
				paint_card_desk(game.player[2].card_hand[game.player[2].hand],790,50);
			else if(curr_player==3)
				paint_card_desk(game.player[3].card_hand[game.player[3].hand],200,275);
			else ;
			EndPaint(hwnd,&ps);
			break;
		case no_winner:
			hdc=BeginPaint(hwnd,&ps);		          	
		    paint_name();
			paint_word(5);
			paint_result(3);
			BubbleSort(game.player[0].card_hand,game.player[0].hand+1);
			for(int i=0,j=50;i<game.player[0].hand;i++) //真人玩家手牌
				paint_card_hand(i);
			for(int i=0,flag=0;i<desk_pos;i++) //已经打过的牌
			{
				paint_card_desk(game.card_desk[i],250+30*(i%23),110+50*(flag/23));
				flag++;
			}
			for(int i=0,j=30;i<game.player[0].hand_locked;i++) //碰过或杠过的牌
				paint_card_desk(game.player[0].card_hand_locked[i],250+30*i,610);
			for(int i=1;i<4;i++) //给电脑手牌排序
				BubbleSort(game.player[i].card_hand,game.player[i].hand+1);
			paint_computer_end();//绘制电脑的所有牌
			EndPaint(hwnd,&ps);
			break;
		}		
		return 0;
	case WM_LBUTTONDOWN:
		if(moment==create&&LOWORD(lParam)<=460&&LOWORD(lParam)>=340&&HIWORD(lParam)<=450&&HIWORD(lParam)>=350)
		{
			moment=before_start;
			InvalidateRect(hwnd,NULL,1);
			return 0;
		}
		else if(moment==before_start&&LOWORD(lParam)<=460&&LOWORD(lParam)>=340&&HIWORD(lParam)<=450&&HIWORD(lParam)>=350)
		{
			moment=playing;
			Getcard_computer(curr_player);
			InvalidateRect(hwnd,NULL,1);
			return 0;
		}
		else if(moment==playing&&LOWORD(lParam)<=340&&LOWORD(lParam)>=260&&HIWORD(lParam)<=450&&HIWORD(lParam)>=350)
		{
			curr_player++;
			if(curr_player%4)
			{
				Getcard_computer(curr_player%4);
			    InvalidateRect(hwnd,NULL,1);
			}
			else 
			{
				moment=human;
				Getcard_human();
				InvalidateRect(hwnd,NULL,1);
			}
			return 0;
		}
		else if(moment==human&&HIWORD(lParam)>=530&&HIWORD(lParam)<=610)
		{
			if((LOWORD(lParam)-250)/50<=game.player[0].hand)
			{
			    discard_human((LOWORD(lParam)-250)/50);
			    moment=playing;
			    InvalidateRect(hwnd,NULL,1);
				sound_card_human(game.card_desk[desk_pos-1]);
			}
			else ;
			return 0;
		}
		else if(moment==human_peng&&HIWORD(lParam)>=370&&HIWORD(lParam)<=430)
		{
			if(LOWORD(lParam)>=370&&LOWORD(lParam)<=430)
			{
			    peng_human();
			    moment=human;
			    InvalidateRect(hwnd,NULL,1);
				sound_do_human(1);
			    return 0;
			}
			else if(LOWORD(lParam)>=800&&LOWORD(lParam)<=900)
			{
				moment=playing;
				InvalidateRect(hwnd,NULL,1);
				return 0;
			}
			else return(DefWindowProc(hwnd,message,wParam,lParam));
		}
		else if(moment==human_gang&&HIWORD(lParam)>=370&&HIWORD(lParam)<=430)
		{
			if(LOWORD(lParam)>=370&&LOWORD(lParam)<=430)
			{
				peng_human();
			    moment=human;
			    InvalidateRect(hwnd,NULL,1);
				sound_do_human(1);
			    return 0;
			}
			else if(LOWORD(lParam)>=520&&LOWORD(lParam)<=580)
			{
				gang_human();
			    moment=human;
			    InvalidateRect(hwnd,NULL,1);
				sound_do_human(2);
			    return 0;
			}
			else if(LOWORD(lParam)>=800&&LOWORD(lParam)<=900)
			{
				moment=playing;
				InvalidateRect(hwnd,NULL,1);
				return 0;
			}
			else return(DefWindowProc(hwnd,message,wParam,lParam));
		}
		else if(moment==human_gang_black&&HIWORD(lParam)>=370&&HIWORD(lParam)<=430)
		{
			if(LOWORD(lParam)>=520&&LOWORD(lParam)<=580)
			{
				gang_human_black();
			    moment=human;
			    InvalidateRect(hwnd,NULL,1);
				sound_do_human(2);
			    return 0;
			}
			else if(LOWORD(lParam)>=800&&LOWORD(lParam)<=900)
			{
				moment=human;
				InvalidateRect(hwnd,NULL,1);
				return 0;
			}
			else return(DefWindowProc(hwnd,message,wParam,lParam));
		}
		else if(moment==human_gang_white&&HIWORD(lParam)>=370&&HIWORD(lParam)<=430)
		{
			if(LOWORD(lParam)>=520&&LOWORD(lParam)<=580)
			{
				gang_human_white();
			    moment=human;
			    InvalidateRect(hwnd,NULL,1);
				sound_do_human(2);
			    return 0;
			}
			else if(LOWORD(lParam)>=800&&LOWORD(lParam)<=900)
			{
				moment=human;
				InvalidateRect(hwnd,NULL,1);
				return 0;
			}
			else return(DefWindowProc(hwnd,message,wParam,lParam));
		}
		else if(moment==human_hu&&HIWORD(lParam)>=400&&HIWORD(lParam)<=500)
		{
			if(LOWORD(lParam)>=670&&LOWORD(lParam)<=730)
			{
                if(curr_player%4)
				    hu_human();
				moment=game_over;
				InvalidateRect(hwnd,NULL,1);
				sound_do_human(3);
				return 0;
			}
			else if(LOWORD(lParam)>=800&&LOWORD(lParam)<=900)
			{
				if(curr_player%4)
				    moment=playing;
				else moment=human;
				InvalidateRect(hwnd,NULL,1);
				return 0;
			}
			else return(DefWindowProc(hwnd,message,wParam,lParam));
		}
		else if(moment==game_over&&LOWORD(lParam)<=460&&LOWORD(lParam)>=340&&HIWORD(lParam)<=450&&HIWORD(lParam)>=350)
		{
			moment=create;
			InvalidateRect(hwnd,NULL,1);
			return 0;
		}
		else if(moment==no_winner&&LOWORD(lParam)<=460&&LOWORD(lParam)>=340&&HIWORD(lParam)<=450&&HIWORD(lParam)>=350)
		{
			moment=create;
			InvalidateRect(hwnd,NULL,1);
			return 0;
		}
		else return(DefWindowProc(hwnd,message,wParam,lParam));
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	default:
		return(DefWindowProc(hwnd,message,wParam,lParam));
	}
}

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow)
{
	MSG msg;
	WNDCLASS wndclass;
	hbitmap=LoadBitmap(hInstance,"background");
	hbrush=CreatePatternBrush(hbitmap);
	wndclass.cbClsExtra=0;
	wndclass.cbWndExtra=0;
	wndclass.hbrBackground=hbrush;
	wndclass.hCursor=LoadCursor(NULL,IDC_ARROW);
	wndclass.hIcon=LoadIcon(NULL,"END");
	wndclass.hInstance=hInstance;
	wndclass.lpfnWndProc=WndProc;
	wndclass.lpszClassName="WinFill";
	wndclass.lpszMenuName=NULL;
	wndclass.style=CS_HREDRAW|CS_VREDRAW;
	if(!RegisterClass(&wndclass))
	{
		MessageBox(NULL,"注册类出错","错误",MB_ICONERROR);
		return 0;
	}
	hwnd=CreateWindow("WinFill","游戏界面",WS_OVERLAPPEDWINDOW,0,0,1200,700,NULL,NULL,hInstance,NULL);
	if(!hwnd)
		return FALSE;
	ShowWindow(hwnd,nCmdShow);
	UpdateWindow(hwnd);
	while(GetMessage(&msg,0,0,0))
	{
		
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}