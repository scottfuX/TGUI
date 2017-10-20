#ifndef _WINCLASS_H_
#define _WINCLASS_H_ 

#ifdef __cplusplus
extern "C"  {
#endif
	
#include "TGUIConfig/tgui_drv_conf.h"
	

	
#ifdef __cplusplus
}
#endif
	
#include "ListClass.hpp"
extern uint8 TouchUp;


#define  WS_DESKTOP 			0
#define	 WS_DEFAULT 			1
#define	 WS_VISIBLE 			2
#define	 WS_DISABLED 			4
#define	 WS_CAPTION 			8//创建含标题栏的主窗口;
#define	 WS_SYSMENU 			16//创建含系统菜单的主窗口
#define	 WS_BORDER 				32//创建有边框的窗口
#define	 WS_VSCROLL 			64//创建带垂直滚动条的窗口
#define	 WS_HSCROLL 			128//创建带水平滚动条的窗口
#define	 WS_MINIMIZEBOX 	256//标题栏上带最小化按钮
#define	 WS_MAXIMIZEBOX 	512//标题栏上带最大化按钮





typedef enum {
	GUI_OK = 0,		/* 0: Successful */
	GUI_ERROR,		/* 1: R/W Error */
	GUI_NOMEM,		/* 2: No Memery */
	GUI_NOFIND,
	GUI_QEMPTY,
	GUI_QFULL
}retStatus;

/**-----------Message-------------**/
typedef enum {
	MSG_EMPTY = 0,
	MSG_CLOSE = 1,	
	MSG_DESTROY,	
	MSG_WINMOV,		
	MSG_FONTCHANGE,
	MSG_ERASURE,
	MSG_REPAINT
}MsgType;
typedef struct{
	MsgType type;
	uint32  data;
}Message;




//预定义类。。。。
class rootWin;
class mainWin;
class controlWin;
//class button;
//class gridView;
//class scrollView;
//class icon;
//class trackBar;
//class progressBar;
//class listBar;
//class textBar;

extern rootWin* currentWin;
/**----------rootWin-------------**/
class rootWin
{
	private:
    
    uint8* winTitle;
    uint16 winXpos;
    uint16 winYpos;
    uint16 winWidth;
    uint16 winHigh;

	void *winIcon;
	uint32 backColor;
	uint32 statBarColor;
		//待定
    void *winProc;
    void *winMenu;
		//List listWin;
	public:
    rootWin();
    rootWin(uint8* winTitle,uint16 winXpos,uint16 winYpos,\
		uint16 winWidth,uint16 winHigh);
		~rootWin();
		
    void setWinTitle(uint8* winTitle){this->winTitle = winTitle;}
    void setWinXpos(uint16 winXpos){this->winXpos = winXpos;}   
    void setWinYpos(uint16 winYpos){this->winYpos = winYpos;}
    void setWinWidth(uint16 winWidth){this->winWidth = winWidth;}
    void setWinHigh(uint16 winHigh){this->winHigh = winHigh;}
		void setBackColor(uint32 backColor){this->backColor = backColor;}
		void setStatBarColor(uint32 statBarColor){this->statBarColor = statBarColor;}
		
		uint8* getWinTitle(){return winTitle;}
		uint16 getWinXpos(){return winXpos;}
		uint16 getWinYpos(){return winYpos;}
		uint16 getWinWidth(){return winWidth;}
    uint16 getWinHigh(){return winHigh;}
		uint32 getBackColor(){return backColor;}
		uint32 getStatBarColor(){return statBarColor;}
		//rootWin createWin();
//    void updateWin();
  //  void showWin();
   // bool isWinEnable();
};


/**----------mainWin-------------**/
class mainWin:rootWin
{
private:
	uint16 winStyle;
	uint16 Xpos;//传进来的指针
	uint16 Ypos;
	CircularList<controlWin>* list;
	xQueueHandle queue;
public:
	
	mainWin();
	mainWin(uint8* winTitle,uint16 winStyle,uint16 winXpos,uint16 winYpos,uint16 winWidth,uint16 winHigh);
	~mainWin();
	friend class button;

	void setWinStyle(uint16 winStyle){this->winStyle = winStyle;}
	void setWinTitle(uint8* winTitle){rootWin::setWinTitle(winTitle);}
	void setWinXpos(uint16 winXpos){rootWin::setWinXpos(winXpos);}   
	void setWinYpos(uint16 winYpos){rootWin::setWinYpos(winYpos);}
	void setWinWidth(uint16 winWidth){rootWin::setWinWidth(winWidth);}
	void setWinHigh(uint16 winHigh){rootWin::setWinHigh(winHigh);}
	void setBackColor(uint32 backColor){rootWin::setBackColor(backColor);}
	void setStatBarColor(uint32 statBarColor){rootWin::setStatBarColor(statBarColor);}
	
	uint16 getWinStyle(){return winStyle;}	
	uint8* getWinTitle(){return rootWin::getWinTitle();}
	uint16 getWinXpos(){return rootWin::getWinXpos();}
	uint16 getWinYpos(){return rootWin::getWinYpos();}
	uint16 getWinWidth(){return rootWin::getWinWidth();}
	uint16 getWinHigh(){return rootWin::getWinHigh();}
	uint32 getBackColor(){return rootWin::getBackColor();}
	uint32 getStatBarColor(){return rootWin::getStatBarColor();}
	
	bool isInArea(uint16 Xpos,uint16 Ypos);
	//retStatus creatList();
	retStatus findExecControl(uint16 Xpos,uint16 Ypos);
	retStatus addControl(controlWin* cw);
	retStatus delControl(controlWin* cw);
	retStatus getMessage(Message* buffer);
	void layoutWin();
	void execWin();
	
	void closeWin();//在缩小到后端 
	void moveWin(uint32 data);//移动窗口
	void changeFont(uint32 data);//改变字体
	void erasureWin();//清空数据
	void repaintWin();//重新绘画
};

/**--------controlWin-----------**/
class controlWin:rootWin
{
private:
	uint16 Xpos;//传进来的指针
	uint16 Ypos;
public:
	controlWin();
	controlWin(uint8* winTitle,uint16 winXpos,uint16 winYpos,uint16 winWidth,uint16 winHigh);
	virtual ~controlWin();

	void setWinTitle(uint8* winTitle){rootWin::setWinTitle(winTitle);}
	void setWinXpos(uint16 winXpos){rootWin::setWinXpos(winXpos);}   
	void setWinYpos(uint16 winYpos){rootWin::setWinYpos(winYpos);}
	void setWinWidth(uint16 winWidth){rootWin::setWinWidth(winWidth);}
	void setWinHigh(uint16 winHigh){rootWin::setWinHigh(winHigh);}
	void setBackColor(uint32 backColor){rootWin::setBackColor(backColor);}
	void setStatBarColor(uint32 statBarColor){rootWin::setStatBarColor(statBarColor);}
			
	uint8* getWinTitle(){return rootWin::getWinTitle();}
    uint16 getWinXpos(){return rootWin::getWinXpos();}
	uint16 getWinYpos(){return rootWin::getWinYpos();}
	uint16 getWinWidth(){return rootWin::getWinWidth();}
	uint16 getWinHigh(){return rootWin::getWinHigh();}
	uint32 getBackColor(){return rootWin::getBackColor();}
	uint32 getStatBarColor(){return rootWin::getStatBarColor();}


	virtual bool isInArea(uint16 Xpos,uint16 Ypos)=0;
	virtual retStatus sendMessage(Message msg,xQueueHandle* que)=0;
	virtual void layoutControl(mainWin* mw)=0;
	virtual retStatus execControl(mainWin* mw) =0;//??
	virtual void triggerControl(mainWin* mw) = 0;//触发按键
	virtual void releaseControl(mainWin* mw) = 0;//释放按键
	

};

//按键
class button:public controlWin
{
public:
	button();
	button(uint8* winTitle,uint16 winXpos,uint16 winYpos,uint16 winWidth,uint16 winHigh);
	virtual ~button();

	void setWinTitle(uint8* winTitle){controlWin::setWinTitle(winTitle);}
	void setWinXpos(uint16 winXpos){controlWin::setWinXpos(winXpos);}   
	void setWinYpos(uint16 winYpos){controlWin::setWinYpos(winYpos);}
	void setWinWidth(uint16 winWidth){controlWin::setWinWidth(winWidth);}
	void setWinHigh(uint16 winHigh){controlWin::setWinHigh(winHigh);}
	void setBackColor(uint32 backColor){controlWin::setBackColor(backColor);}
	void setStatBarColor(uint32 statBarColor){controlWin::setStatBarColor(statBarColor);}
	
	uint8* getWinTitle(){return controlWin::getWinTitle();}
	uint16 getWinXpos(){return controlWin::getWinXpos();}
	uint16 getWinYpos(){return controlWin::getWinYpos();}
	uint16 getWinWidth(){return controlWin::getWinWidth();}
	uint16 getWinHigh(){return controlWin::getWinHigh();}
	uint32 getBackColor(){return controlWin::getBackColor();}
	uint32 getStatBarColor(){return controlWin::getStatBarColor();}
	
	virtual bool isInArea(uint16 iXpos,uint16 iYpos);
	virtual retStatus sendMessage(Message msg,xQueueHandle* que);
	virtual void layoutControl(mainWin* mw);
	//virtual void createControl(mainWin* mw);
	virtual retStatus execControl(mainWin* mw);
	virtual void triggerControl(mainWin* mw);//触发按键
	virtual void releaseControl(mainWin* mw);//释放按键
};

//网格
class gridView:public controlWin
{
	
};
//滚轮
class scrollView:public controlWin
{
	
};
//图标
class icon :public controlWin
{
	
};
//滑块
class trackBar:public controlWin
{
	
};
//进度条
class progressBar :public controlWin
{
	
};
//列表
class listBar:public controlWin
{
	
};
//文本框
class textBar:public controlWin
{
	
};




#endif //!_WINCLASS_H_
