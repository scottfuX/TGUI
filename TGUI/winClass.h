#ifndef _WINCLASS_H_
#define _WINCLASS_H_ 

#include "TGUIConfig/tgui_drv_conf.h"
#include "ListClass.h"



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

/*//ex -----未实现
	bool WS_EX_NONE;//无扩展风格
	bool WS_EX_TOPMOST;//建立始终处于顶层的主窗口
	bool WS_EX_TOOLWINDOW;//建立 Tooltip 主窗口
	bool WS_EX_TRANSPARENT;//透明窗口风格
	bool WS_EX_USEPARENTFONT;//使用父窗口字体作为默认字体
	bool WS_EX_USEPARENTCURSOR;//使用父窗口光标作为默认光标
	bool WS_EX_NOCLOSEBOX;//主窗口标题栏上不带关闭按钮;
	bool WS_EX_CTRLASMAINWIN;//建立可显示在主窗口之外的控件
};
*/
class rootWin;
extern rootWin* currentWin; //指向当前界面

typedef enum {
	GUI_OK = 0,		/* 0: Successful */
	GUI_ERROR,		/* 1: R/W Error */
	GUI_NOMEM,		/* 2: No Memery */
	GUI_NOFIND
}retStatus;

/**-----------Message-------------**/
//class Message{};
typedef enum {
	MSG_CLOSE = 0,	
	MSG_DESTROY,	
	MSG_WINMOV,		
	MSG_FONTCHANGE,
	MSG_ERASURE,
	MSG_REPAINT
}Message;
/**---------dataMessage-----------**/

//dataMessage

/**----------rootWin-------------**/
class rootWin
{
protected:
    
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
    void updateWin();
    void showWin();
    bool isWinEnable();
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
	~controlWin();

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


	virtual bool isInArea(uint16 Xpos,uint16 Ypos) = 0;
	virtual retStatus sendMessage(Message msg) = 0;
	virtual void layoutControl() = 0;
	virtual void createControl() = 0;
	virtual retStatus execControl() = 0;
	

};

//按键
class button :public controlWin
{
public:
	button();
	button(uint8* winTitle,uint16 winXpos,uint16 winYpos,uint16 winWidth,uint16 winHigh);
	virtual bool isInArea(uint16 Xpos,uint16 Ypos);
	virtual retStatus sendMessage(Message msg);
	virtual void layoutControl();
	virtual void createControl();
	virtual retStatus execControl();
};
//网格
class gridView :public controlWin
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
	void moveWin(uint16 x,uint16 y,uint16 w,uint16 h);//移动窗口
	void changeFont();//改变字体
	void erasureWin();//清空数据
	void repaintWin();//重新绘画
};




#endif //!_WINCLASS_H_
