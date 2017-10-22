#ifndef _WINCLASS_H_
#define _WINCLASS_H_ 

#ifdef __cplusplus
extern "C"  {
#endif
	
#include "TGUIConfig/tgui_drv_conf.h"
		
#ifdef __cplusplus
}
#endif
	
#include "TGUIConfig/createWin_conf.h"
#include "ListClass.hpp"

extern uint8_t TouchUp;
extern uint8_t currentWin;
extern xTaskHandle app[APP_MAX_NUM];




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
	GUI_QFULL,
	GUI_APPOUT
}retStatus;

/**-----------Message-------------**/
typedef enum {
	MSG_EMPTY = 0,
	MSG_CLOSE = 1,	
	MSG_DESTROY,	
	MSG_WINMOV,		
	MSG_FONTCHANGE,
	MSG_ERASURE,
	MSG_REPAINT,
	MSG_APP,
	MSG_OTHER
}MsgType;
typedef struct{
	MsgType type;
	uint32_t  data;
}Message;




//预定义类。。。。
class rootWin;
class mainWin;
class controlWin;
class button;
class deskWin;
//class gridView;
//class scrollView;
//class icon;
//class trackBar;
//class progressBar;
//class listBar;
//class textBar;

extern deskWin* desktop;

/**----------rootWin-------------**/
class rootWin
{
	private:
    uint8_t id;
    uint8_t* winTitle;
    uint16_t winXpos;
    uint16_t winYpos;
    uint16_t winWidth;
    uint16_t winHigh;

	void *winIcon;
	uint32_t backColor;
	uint32_t statBarColor;
		//待定
    void *winProc;
    void *winMenu;
		//List listWin;
	public:
    rootWin();
    rootWin(uint8_t* winTitle,uint16_t winXpos,uint16_t winYpos,\
		uint16_t winWidth,uint16_t winHigh);
	~rootWin();
		
	void setWinID(uint8_t id){this->id = id;}
    void setWinTitle(uint8_t* winTitle){this->winTitle = winTitle;}
    void setWinXpos(uint16_t winXpos){this->winXpos = winXpos;}   
    void setWinYpos(uint16_t winYpos){this->winYpos = winYpos;}
    void setWinWidth(uint16_t winWidth){this->winWidth = winWidth;}
    void setWinHigh(uint16_t winHigh){this->winHigh = winHigh;}
	void setBackColor(uint32_t backColor){this->backColor = backColor;}
	void setStatBarColor(uint32_t statBarColor){this->statBarColor = statBarColor;}
		
	uint8_t	 getWinID(){return id;}
	uint8_t* getWinTitle(){return winTitle;}
	uint16_t getWinXpos(){return winXpos;}
	uint16_t getWinYpos(){return winYpos;}
	uint16_t getWinWidth(){return winWidth;}
    uint16_t getWinHigh(){return winHigh;}
	uint32_t getBackColor(){return backColor;}
	uint32_t getStatBarColor(){return statBarColor;}

};


/**----------mainWin-------------**/
class mainWin:rootWin
{
private:
	uint16_t winStyle;
	uint16_t Xpos;//传进来的指针
	uint16_t Ypos;
	void(*userFunc)();//存储用户函数的值
protected:
	CircularList<controlWin>* list;
	xQueueHandle queue;
public:
	
	mainWin();
	mainWin(void (*tempFunc)());
	mainWin(uint8_t* winTitle,uint16_t winStyle,uint16_t winXpos,uint16_t winYpos,uint16_t winWidth,uint16_t winHigh,void(*tempFunc)());
	~mainWin();

	void setWinStyle(uint16_t winStyle){this->winStyle = winStyle;}
	void setWinID(uint8_t id){rootWin::setWinID(id);}	
	void setWinXpos(uint16_t winXpos){rootWin::setWinXpos(winXpos);}   
	void setWinYpos(uint16_t winYpos){rootWin::setWinYpos(winYpos);}
	void setWinWidth(uint16_t winWidth){rootWin::setWinWidth(winWidth);}
	void setWinHigh(uint16_t winHigh){rootWin::setWinHigh(winHigh);}
	void setBackColor(uint32_t backColor){rootWin::setBackColor(backColor);}
	void setStatBarColor(uint32_t statBarColor){rootWin::setStatBarColor(statBarColor);}
	
	uint16_t getWinStyle(){return winStyle;}	
	uint8_t	 getWinID(){return rootWin::getWinID();}
	uint8_t* getWinTitle(){return rootWin::getWinTitle();}
	uint16_t getWinXpos(){return rootWin::getWinXpos();}
	uint16_t getWinYpos(){return rootWin::getWinYpos();}
	uint16_t getWinWidth(){return rootWin::getWinWidth();}
	uint16_t getWinHigh(){return rootWin::getWinHigh();}
	uint32_t getBackColor(){return rootWin::getBackColor();}
	uint32_t getStatBarColor(){return rootWin::getStatBarColor();}
	
	
	virtual xQueueHandle* getQueue(){return &queue;}
	virtual retStatus findExecControl(uint16_t Xpos,uint16_t Ypos);
	virtual retStatus addControl(controlWin* cw);
	virtual retStatus delControl(controlWin* cw);
	virtual retStatus getMessage(Message* buffer);
	virtual void layoutWin();
	virtual void execWin();
	
	bool isInArea(uint16_t Xpos,uint16_t Ypos);
	void closeWin();//在缩小到后端 
	void destroyWin();
	void moveWin(uint32_t data);//移动窗口
	void changeFont(uint32_t data);//改变字体
	void erasureWin();//清空数据
	void repaintWin();//重新绘画
};
/**--------deskWin-----------**/
class deskWin:mainWin
{
private:
	CircularList<mainWin>* winList;
public:
	deskWin();
	~deskWin();

	void setWinID(uint8_t id){mainWin::setWinID(id);}
	uint8_t getWinID(){return mainWin::getWinID();}	
	
	retStatus addAPP(mainWin* mw,uint8_t num);//传入win指针和相应第几个软件便于layout
	virtual xQueueHandle* getQueue(){return &queue;}

	virtual retStatus findExecControl(uint16_t Xpos,uint16_t Ypos);
	virtual retStatus getMessage(Message* buffer);
	virtual retStatus addControl(controlWin* cw);
	virtual retStatus delControl(controlWin* cw);
	virtual retStatus findWin(uint8_t winID);
	virtual retStatus addWin(mainWin* mw);
	virtual retStatus delWin(mainWin* mw);
	
	virtual void execDesk();
	virtual void layoutWin();
};

/**--------controlWin-----------**/
class controlWin:rootWin
{
private:
	Message* controlMsg;
public:
	controlWin(Message* controlMsg);
	controlWin(uint8_t* winTitle,uint16_t winXpos,uint16_t winYpos,uint16_t winWidth,uint16_t winHigh,Message* controlMsg);
	virtual ~controlWin();

	void setControlMsg(Message* MsgTemp);
	void setWinID(uint8_t id){rootWin::setWinID(id);}	
	void setWinTitle(uint8_t* winTitle){rootWin::setWinTitle(winTitle);}
	void setWinXpos(uint16_t winXpos){rootWin::setWinXpos(winXpos);}   
	void setWinYpos(uint16_t winYpos){rootWin::setWinYpos(winYpos);}
	void setWinWidth(uint16_t winWidth){rootWin::setWinWidth(winWidth);}
	void setWinHigh(uint16_t winHigh){rootWin::setWinHigh(winHigh);}
	void setBackColor(uint32_t backColor){rootWin::setBackColor(backColor);}
	void setStatBarColor(uint32_t statBarColor){rootWin::setStatBarColor(statBarColor);}
	
	Message* getControlMsg();	
	uint8_t	 getWinID(){return rootWin::getWinID();}
	uint8_t* getWinTitle(){return rootWin::getWinTitle();}
	uint16_t getWinXpos(){return rootWin::getWinXpos();}
	uint16_t getWinYpos(){return rootWin::getWinYpos();}
	uint16_t getWinWidth(){return rootWin::getWinWidth();}
	uint16_t getWinHigh(){return rootWin::getWinHigh();}
	uint32_t getBackColor(){return rootWin::getBackColor();}
	uint32_t getStatBarColor(){return rootWin::getStatBarColor();}


	virtual bool isInArea(uint16_t Xpos,uint16_t Ypos)=0;
	virtual retStatus sendMessage(Message msg,xQueueHandle* que)=0;
	virtual void layoutControl(mainWin* mw)=0;
	virtual retStatus execControl(mainWin* mw) =0;//
	virtual void triggerControl(mainWin* mw) = 0;//触发按键
	virtual void releaseControl(mainWin* mw) = 0;//释放按键
};


//按键
class button:public controlWin
{
public:
	button(Message* controlMsg);
	button(uint8_t* winTitle,uint16_t winXpos,uint16_t winYpos,uint16_t winWidth,uint16_t winHigh,Message* controlMsg);
	virtual ~button();
	
	void setControlMsg(Message* MsgTemp){controlWin::setControlMsg(MsgTemp);}
	void setWinID(uint8_t id){controlWin::setWinID(id);}	
	void setWinTitle(uint8_t* winTitle){controlWin::setWinTitle(winTitle);}
	void setWinXpos(uint16_t winXpos){controlWin::setWinXpos(winXpos);}   
	void setWinYpos(uint16_t winYpos){controlWin::setWinYpos(winYpos);}
	void setWinWidth(uint16_t winWidth){controlWin::setWinWidth(winWidth);}
	void setWinHigh(uint16_t winHigh){controlWin::setWinHigh(winHigh);}
	void setBackColor(uint32_t backColor){controlWin::setBackColor(backColor);}
	void setStatBarColor(uint32_t statBarColor){controlWin::setStatBarColor(statBarColor);}
	
	Message* getControlMsg(){return controlWin::getControlMsg();}
	uint8_t	 getWinID(){return controlWin::getWinID();}
	uint8_t* getWinTitle(){return controlWin::getWinTitle();}
	uint16_t getWinXpos(){return controlWin::getWinXpos();}
	uint16_t getWinYpos(){return controlWin::getWinYpos();}
	uint16_t getWinWidth(){return controlWin::getWinWidth();}
	uint16_t getWinHigh(){return controlWin::getWinHigh();}
	uint32_t getBackColor(){return controlWin::getBackColor();}
	uint32_t getStatBarColor(){return controlWin::getStatBarColor();}
	
	virtual bool isInArea(uint16_t iXpos,uint16_t iYpos);
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
