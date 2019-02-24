#include"scene.h"
#include"game.h"

//位图句柄
HBITMAP hbmwan_hand;
HBITMAP hbmtiao_hand;
HBITMAP hbmtong_hand;
HBITMAP hbmfeng_hand;
HBITMAP hbmwan_desk;
HBITMAP hbmtiao_desk;
HBITMAP hbmtong_desk;
HBITMAP hbmfeng_desk;
HBITMAP hbmcomputer_first;
HBITMAP hbmcomputer_second;
HBITMAP hbmcomputer_third;

BITMAP bm;
HINSTANCE hInstance=GetModuleHandle(NULL);
HDC hdc;
HDC hdcmem;
HBITMAP hbitmap;
HBRUSH hbrush;

//绘制玩家手牌
void paint_card_hand(int i)
{
	if(game.player[0].card_hand[i]<10)
	{	    
		hbmwan_hand=LoadBitmap(hInstance,"wan_hand");
		GetObject(hbmwan_hand,sizeof(BITMAP),(LPVOID)&bm);
		SelectObject(hdcmem,hbmwan_hand);
		StretchBlt(hdc,250+50*i,530,50,80,hdcmem,(9-game.player[0].card_hand[i])*(bm.bmWidth/9),0,bm.bmWidth/9,bm.bmHeight,SRCCOPY);
		DeleteObject(hbmwan_hand);
	}
	else if(game.player[0].card_hand[i]>10&&game.player[0].card_hand[i]<20)
	{	    
		hbmtiao_hand=LoadBitmap(hInstance,"tiao_hand");
		GetObject(hbmtiao_hand,sizeof(BITMAP),(LPVOID)&bm);
		SelectObject(hdcmem,hbmtiao_hand);		
		StretchBlt(hdc,250+50*i,530,50,80,hdcmem,(19-game.player[0].card_hand[i])*(bm.bmWidth/9),0,bm.bmWidth/9,bm.bmHeight,SRCCOPY);
		DeleteObject(hbmtiao_hand);
	}
	else if(game.player[0].card_hand[i]>20&&game.player[0].card_hand[i]<30)
	{	    
		hbmtong_hand=LoadBitmap(hInstance,"tong_hand");
		GetObject(hbmtong_hand,sizeof(BITMAP),(LPVOID)&bm);
		SelectObject(hdcmem,hbmtong_hand);
		StretchBlt(hdc,250+50*i,530,50,80,hdcmem,(29-game.player[0].card_hand[i])*(bm.bmWidth/9),0,bm.bmWidth/9,bm.bmHeight,SRCCOPY);
		DeleteObject(hbmtong_hand);
	}
	else
	{	    
		hbmfeng_hand=LoadBitmap(hInstance,"feng_hand");
		GetObject(hbmfeng_hand,sizeof(BITMAP),(LPVOID)&bm);
		SelectObject(hdcmem,hbmfeng_hand);
		StretchBlt(hdc,250+50*i,530,50,80,hdcmem,(36-game.player[0].card_hand[i])*(bm.bmWidth/6),0,bm.bmWidth/6,bm.bmHeight,SRCCOPY);
		DeleteObject(hbmfeng_hand);
	}
}

//绘制桌面上的牌
void paint_card_desk(int value,int x,int y)
{
		if(value<10)
	    {	    
		    hbmwan_desk=LoadBitmap(hInstance,"wan_desk");
			GetObject(hbmwan_desk,sizeof(BITMAP),(LPVOID)&bm);
		    SelectObject(hdcmem,hbmwan_desk);
		    StretchBlt(hdc,x,y,30,50,hdcmem,(value-1)*(bm.bmWidth/9),0,bm.bmWidth/9,bm.bmHeight,SRCCOPY);
		    DeleteObject(hbmwan_desk);
	    }
	    else if(value>10&&value<20)
	    {	    
		    hbmtiao_desk=LoadBitmap(hInstance,"tiao_desk");
			GetObject(hbmtiao_desk,sizeof(BITMAP),(LPVOID)&bm);
		    SelectObject(hdcmem,hbmtiao_desk);		
		    StretchBlt(hdc,x,y,30,50,hdcmem,(value-11)*(bm.bmWidth/9),0,bm.bmWidth/9,bm.bmHeight,SRCCOPY);
		    DeleteObject(hbmtiao_desk);
	    }
	    else if(value>20&&value<30)
	    {	    
		    hbmtong_desk=LoadBitmap(hInstance,"tong_desk");
			GetObject(hbmtong_desk,sizeof(BITMAP),(LPVOID)&bm);
		    SelectObject(hdcmem,hbmtong_desk);
		    StretchBlt(hdc,x,y,30,50,hdcmem,(value-21)*(bm.bmWidth/9),0,bm.bmWidth/9,bm.bmHeight,SRCCOPY);
		    DeleteObject(hbmtong_desk);
	    }
	    else
	    {	    
		    hbmfeng_desk=LoadBitmap(hInstance,"feng_desk");
			GetObject(hbmfeng_desk,sizeof(BITMAP),(LPVOID)&bm);
		    SelectObject(hdcmem,hbmfeng_desk);
		    StretchBlt(hdc,x,y,30,50,hdcmem,(value-31)*(bm.bmWidth/6),0,bm.bmWidth/6,bm.bmHeight,SRCCOPY);
		    DeleteObject(hbmfeng_hand);
	    }
}

//绘制电脑手牌
void paint_card_computer()
{
	hbmcomputer_first=LoadBitmap(hInstance,"computer_first"); //绘制电脑1手牌
	GetObject(hbmcomputer_first,sizeof(BITMAP),(LPVOID)&bm);
	SelectObject(hdcmem,hbmcomputer_first);		
	StretchBlt(hdc,1000,100,20,400,hdcmem,0,0,bm.bmWidth,bm.bmHeight,SRCCOPY);
    DeleteObject(hbmcomputer_first);
	hbmcomputer_second=LoadBitmap(hInstance,"computer_second"); //绘制电脑2手牌
	GetObject(hbmcomputer_second,sizeof(BITMAP),(LPVOID)&bm);
	SelectObject(hdcmem,hbmcomputer_second);		
	StretchBlt(hdc,450,50,300,30,hdcmem,0,0,bm.bmWidth,bm.bmHeight,SRCCOPY);
    DeleteObject(hbmcomputer_second);
	hbmcomputer_third=LoadBitmap(hInstance,"computer_third"); //绘制电脑3手牌
	GetObject(hbmcomputer_third,sizeof(BITMAP),(LPVOID)&bm);
	SelectObject(hdcmem,hbmcomputer_third);		
	StretchBlt(hdc,180,100,20,400,hdcmem,0,0,bm.bmWidth,bm.bmHeight,SRCCOPY);
    DeleteObject(hbmcomputer_third);
}

//绘制桌面上的矩形框和“电脑”、“玩家”字样
void paint_name()
{
	//绘制矩形框
	HPEN hpen;
	hpen=CreatePen(PS_SOLID,2,RGB(0,0,255));
    SelectObject(hdc,hpen);
	MoveToEx(hdc,250,100,NULL);
	LineTo(hdc,250,500);
	LineTo(hdc,950,500);
	LineTo(hdc,950,100);
	LineTo(hdc,250,100);
	DeleteObject(hpen);
	//绘制字体
	HFONT hfont, oldfont;
	COLORREF color = SetTextColor(hdc, RGB(255, 255, 0));
	SetBkMode(hdc, TRANSPARENT);
	TCHAR szText[8];
	UINT textalign;
	hfont = CreateFont(30, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, TEXT("华文新魏"));
	oldfont = (HFONT)SelectObject(hdc, hfont);
	textalign = SetTextAlign(hdc, TA_CENTER);
	TextOut(hdc, 900, 625, szText,wsprintf(szText, TEXT("%s"), TEXT("玩家")));
	TextOut(hdc, 1100, 300, szText, wsprintf(szText, TEXT("%s"), TEXT("电脑")));
	TextOut(hdc, 600, 10, szText, wsprintf(szText, TEXT("%s"), TEXT("电脑")));
	TextOut(hdc, 80, 300, szText, wsprintf(szText, TEXT("%s"), TEXT("电脑")));
	SetTextAlign(hdc, textalign);
	SelectObject(hdc, oldfont);
	DeleteObject(hfont);
	DeleteObject(oldfont);
}

//绘制其他字体
void paint_word(int i)
{
	HFONT hfont, oldfont;
	COLORREF color = SetTextColor(hdc, RGB(255, 255, 0));
	SetBkMode(hdc, TRANSPARENT);
	TCHAR szText[16];
	UINT textalign;
	hfont = CreateFont(30, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, TEXT("华文新魏"));
	oldfont = (HFONT)SelectObject(hdc, hfont);
	textalign = SetTextAlign(hdc, TA_CENTER);
	switch(i)
	{
	case 1://开始游戏
	    TextOut(hdc, 400, 400, szText,wsprintf(szText, TEXT("%s"), TEXT("开始游戏")));
		break;
	case 2://开始出牌
		TextOut(hdc, 400, 400, szText,wsprintf(szText, TEXT("%s"), TEXT("开始出牌")));
		break;
	case 3://继续
		TextOut(hdc, 300, 400, szText,wsprintf(szText, TEXT("%s"), TEXT("继续")));
		break;
	case 4://出牌
		TextOut(hdc, 400, 400, szText,wsprintf(szText, TEXT("%s"), TEXT("出牌")));
		break;
	case 5://开始下一局
		TextOut(hdc, 400, 400, szText,wsprintf(szText, TEXT("%s"), TEXT("开始下一局")));
		break;
	default:
		break;
	}
	SetTextAlign(hdc, textalign);
	SelectObject(hdc, oldfont);
	DeleteObject(hfont);
	DeleteObject(oldfont);
	return;
}

//绘制游戏结果
void paint_result(int i)
{
	HFONT hfont, oldfont;
	COLORREF color = SetTextColor(hdc, RGB(255, 0, 0));
	SetBkMode(hdc, TRANSPARENT);
	TCHAR szText[24];
	UINT textalign;
	hfont = CreateFont(30, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, TEXT("华文新魏"));
	oldfont = (HFONT)SelectObject(hdc, hfont);
	textalign = SetTextAlign(hdc, TA_CENTER);
	switch(i)
	{
	case 1://真人玩家胜利
	    TextOut(hdc, 600, 320, szText,wsprintf(szText, TEXT("%s"), TEXT("恭喜你，你赢了！")));
		break;
	case 2://电脑胜利
		TextOut(hdc, 600, 320, szText,wsprintf(szText, TEXT("%s"), TEXT("很遗憾，你输了！")));
		break;
	case 3://没有玩家胜利
		TextOut(hdc, 600, 320, szText,wsprintf(szText, TEXT("%s"), TEXT("本局没有玩家获得胜利")));
		break;
	default:
		break;
	}
	SetTextAlign(hdc, textalign);
	SelectObject(hdc, oldfont);
	DeleteObject(hfont);
	DeleteObject(oldfont);
	return;
}

//绘制碰牌等操作图标
void paint_do(int i)
{
	HFONT hfont, oldfont;
	COLORREF color = SetTextColor(hdc, RGB(255, 255, 0));
	SetBkMode(hdc, TRANSPARENT);
	TCHAR szText[6];
	UINT textalign;
	hfont = CreateFont(30, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, TEXT("华文新魏"));
	oldfont = (HFONT)SelectObject(hdc, hfont);
	textalign = SetTextAlign(hdc, TA_CENTER);
	switch(i)
	{
	case 1://碰
		TextOut(hdc, 400, 400, szText,wsprintf(szText, TEXT("%s"), TEXT("碰")));
		TextOut(hdc, 850, 400, szText, wsprintf(szText, TEXT("%s"), TEXT("放弃")));
		break;
	case 2://杠
		TextOut(hdc, 550, 400, szText, wsprintf(szText, TEXT("%s"), TEXT("杠")));
		TextOut(hdc, 850, 400, szText, wsprintf(szText, TEXT("%s"), TEXT("放弃")));
		break;
	case 3://胡
		TextOut(hdc, 700, 400, szText, wsprintf(szText, TEXT("%s"), TEXT("胡")));
		TextOut(hdc, 850, 400, szText, wsprintf(szText, TEXT("%s"), TEXT("放弃")));
		break;
	case 4://碰+杠
		TextOut(hdc, 400, 400, szText,wsprintf(szText, TEXT("%s"), TEXT("碰")));
	    TextOut(hdc, 550, 400, szText, wsprintf(szText, TEXT("%s"), TEXT("杠")));
		TextOut(hdc, 850, 400, szText, wsprintf(szText, TEXT("%s"), TEXT("放弃")));
		break;
	case 5://碰+胡
		TextOut(hdc, 400, 400, szText,wsprintf(szText, TEXT("%s"), TEXT("碰")));
		TextOut(hdc, 700, 400, szText, wsprintf(szText, TEXT("%s"), TEXT("胡")));
	    TextOut(hdc, 850, 400, szText, wsprintf(szText, TEXT("%s"), TEXT("放弃")));
		break;
	case 6://碰+杠+胡
		TextOut(hdc, 400, 400, szText,wsprintf(szText, TEXT("%s"), TEXT("碰")));
	    TextOut(hdc, 550, 400, szText, wsprintf(szText, TEXT("%s"), TEXT("杠")));
	    TextOut(hdc, 700, 400, szText, wsprintf(szText, TEXT("%s"), TEXT("胡")));
	    TextOut(hdc, 850, 400, szText, wsprintf(szText, TEXT("%s"), TEXT("放弃")));
		break;
	default:
		break;
	}
	SetTextAlign(hdc, textalign);
	SelectObject(hdc, oldfont);
	DeleteObject(hfont);
	DeleteObject(oldfont);
}

//绘制死牌
void paint_card_locked()
{
	for(int i=0;i<game.player[0].hand_locked;i++) //真人玩家
			paint_card_desk(game.player[0].card_hand_locked[i],250+30*i,610);
	for(int i=0;i<game.player[1].hand_locked;i++) //电脑1
			paint_card_desk(game.player[1].card_hand_locked[i],970,100+50*i);
	if(game.player[2].hand_locked<7) //电脑2
	{
        for(int i=0;i<game.player[2].hand_locked;i++)
		    paint_card_desk(game.player[2].card_hand_locked[i],250+30*i,50);
	}
	else 
	{
		for(int i=0;i<6;i++)
			paint_card_desk(game.player[2].card_hand_locked[i],250+30*i,50);
		for(int i=6;i<game.player[2].hand_locked;i++)
			paint_card_desk(game.player[2].card_hand_locked[i],760+30*i,50);
	}
	for(int i=0;i<game.player[3].hand_locked;i++) //电脑3
		paint_card_desk(game.player[3].card_hand_locked[i],200,100+50*i);
}

//游戏结束后绘制电脑所有牌
void paint_computer_end()
{
	for(int i=0;i<game.player[1].hand;i++) //电脑1手牌
		paint_card_desk(game.player[1].card_hand[i],1000,10+50*i);
	for(int i=0;i<game.player[1].hand_locked;i++) //电脑1死牌
		paint_card_desk(game.player[1].card_hand_locked[i],1000,10+50*(i+game.player[1].hand));
	for(int i=0;i<game.player[2].hand;i++) //电脑2手牌
		paint_card_desk(game.player[2].card_hand[i],400+30*i,50);
	for(int i=0;i<game.player[2].hand_locked;i++) //电脑2死牌
		paint_card_desk(game.player[2].card_hand_locked[i],400+30*(i+game.player[2].hand),50);
	for(int i=0;i<game.player[3].hand;i++) //电脑3手牌
		paint_card_desk(game.player[3].card_hand[i],150,10+50*i);
	for(int i=0;i<game.player[3].hand_locked;i++) //电脑3死牌
		paint_card_desk(game.player[3].card_hand_locked[i],150,10+50*(i+game.player[3].hand));
}