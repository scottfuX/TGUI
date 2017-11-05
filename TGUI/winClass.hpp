#ifndef _WINCLASS_HPP_
#define _WINCLASS_HPP_ 

#ifdef __cplusplus
extern "C"  {
#endif
	
#include "interface_conf/tgui_conf.h"
	
#ifdef __cplusplus
}
#endif

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

//*-------------message_type-----------------
typedef enum {
	MSG_EMPTY = 0,
	MSG_CLICK = 1,
	MSG_UNCLICK,
	MSG_CLOSE ,	
	MSG_DESTROY,
	MSG_ITEM,	
	MSG_WINMOV,		
	MSG_FONTCHANGE,
	MSG_ERASURE,
	MSG_REPAINT,
	MSG_APP,
	MSG_OTHER
}MsgType;


class rootWin;
class mainWin;
class controlWin;

typedef struct{
	rootWin* destWin;//目标窗口
	rootWin* fromWin;//来源窗口
	MsgType type;
	uint32_t  data1;
	uint32_t data2;
}message;

//根窗口
class rootWin
{
	public:
		rootWin(
			uint16_t winXpos,
			uint16_t winYpos,
			uint16_t winWidth,
			uint16_t winHigh,
			char* name,
			uint8_t wsStyle,
			rootWin* parent,
			xQueueHandle queue
		);
		virtual ~rootWin();//设置为虚函数 delete时 就会删除子类
		
		uint16_t getWinXpos(){return winXpos;}
		uint16_t getWinYpos(){return winYpos;}
		uint16_t getWinWidth(){return winWidth;}
		uint16_t getWinHigh(){return winHigh;}
		char* getWinName(){return name;}
		uint16_t getWinStyle(){return wsStyle;}	
		xQueueHandle getQueue(){return this->queue;}
		
		void setWinXpos(uint16_t winXpos){this->winXpos = winXpos;}   
		void setWinYpos(uint16_t winYpos){this->winYpos = winYpos;}
		void setWinWidth(uint16_t winWidth){this->winWidth = winWidth;}
		void setWinHigh(uint16_t winHigh){this->winHigh = winHigh;}
		void setName(char* name){this->name = name;}
		void setWinStyle(uint8_t wsStyle){this->wsStyle =  wsStyle;}	
		
		rootWin* getParent(){return  parent;};//查找父亲节点
		rootWin* getBrother(){return brother;};//查找下一个兄弟节点
		rootWin* getChild(){return child;};//查找第一个孩子节点
		void setParent(rootWin* rw){this->parent = rw;};
		void setBrother(rootWin* rw){ this->brother = rw;};
		void setChild(rootWin* rw){this->child = rw;};
		uint16_t getAbsoluteX(){return absoluteX;}
		uint16_t getAbsoluteY(){return absoluteY;}
		
		void setAbsoluteXY();		//设置绝对x，y
		
				
		bool isInArea(uint16_t wXpos,uint16_t wYpos);
		bool isHaveWinProc(){return this->WinProcSign;}//是否有窗口过程函数
		rootWin* locateWin(uint16_t x,uint16_t y);//定位 然后返回其中最接近的win指针
		
		retStatus sendMSGtoBack(message* msg,xQueueHandle que);
		retStatus sendMSGtoFront(message* msg,xQueueHandle que);
		
		void (*winProc)(rootWin* , rootWin* , MsgType , uint32_t , uint32_t );//窗口过程
		void setWinProc(void (*winProc)(rootWin* , rootWin* rw, MsgType mt, uint32_t d1, uint32_t d2));
		
		void paintAll();
		virtual void paintWin() = 0;//绘画 就自己 不同的窗口实现不同
		virtual void registerWin() ;//激活控件--注册 中间会调用createWin（） 其他根据不同的窗口变化
		virtual void unregisterWin() ;//注销控件  会调用destroy（）窗口 其他会根据不同窗口变化
		virtual	void destroyWin();//窗口销毁 --（销毁所有子窗口和本身） 把自己和子类都从树中删除
		
	private:
		uint16_t absoluteX;//绝对路径
		uint16_t absoluteY;
		uint16_t winXpos;//相对与父亲的路径
		uint16_t winYpos;//相对与父亲的路径
		uint16_t winWidth;
		uint16_t winHigh;
		char* name;
		uint8_t wsStyle;
		xQueueHandle queue;//要发送的消息队列
	
		rootWin* parent;//父窗口
		rootWin* child;//子窗口
		rootWin* brother;//兄弟窗口		
	
	    bool WinProcSign;//窗口过程标志 表示是否需要
		
		void preTraversePaint(rootWin* rw);//先序重绘所有窗口 包括子窗口 和兄弟窗口
		void destroyCAndB();
		void addWintoTree();//创建窗口 -- 即加入树中
		void remWinfromTree();//从树中移除
};

//主窗口--默认没有 //容器安排布局的
class mainWin:public rootWin
{
	public:
	mainWin(
			uint16_t winXpos,
			uint16_t winYpos,
			uint16_t winWidth,
			uint16_t winHigh,
			char* name,
			uint8_t wsStyle,
			rootWin* parent,
			xQueueHandle queue
	);
	virtual ~mainWin();
			
	virtual void paintWin();//绘画 就自己 不同的窗口实现不同
	virtual void registerWin();//激活控件--注册 中间会调用createWin（） 其他根据不同的窗口变化
	virtual void unregisterWin();//注销控件  会调用destroy（）窗口 其他会根据不同窗口变化
	virtual	void destroyWin();		
};

//控件
class controlWin:public rootWin
{
	public:
	controlWin(
			uint16_t winXpos,
			uint16_t winYpos,
			uint16_t winWidth,
			uint16_t winHigh,
			char* name,
			uint8_t wsStyle,
			rootWin* parent,
			xQueueHandle queue
			);
	virtual ~controlWin();
	void displayStrCenter(sFONT font,uint32_t textColor,uint32_t backColor,char* str);    //显示字符串	
	void displayStrNormal(sFONT font,uint32_t textColor,uint32_t backColor,char* str);	
	void setTextColor(uint32_t winColor){this->textColor = winColor;}
	void setBackColor(uint32_t winColor){this->backColor = winColor;}
	uint32_t getTextColor(){return this->textColor;}
	uint32_t getBackColor(){return this->backColor;}
	
	virtual void paintWin()=0 ;//绘画 就自己 不同的窗口实现不同
	virtual void registerWin(){} ;//激活控件--注册 中间会调用createWin（） 其他根据不同的窗口变化
	virtual void unregisterWin(){} ;//注销控件  会调用destroy（）窗口 其他会根据不同窗口变化
	virtual	void destroyWin(){};
	
	private:
		uint32_t textColor;
		uint32_t backColor;
	
};

//按钮
class buttonWin:public controlWin
{
	public:
		buttonWin(
			uint16_t winXpos,
			uint16_t winYpos,
			uint16_t winWidth,
			uint16_t winHigh,
			char* name,
			uint8_t wsStyle,
			rootWin* parent,
			xQueueHandle queue
	);
	virtual ~buttonWin();
			
	virtual void paintWin();//绘画 就自己 不同的窗口实现不同
	virtual void registerWin();//激活控件--注册 中间会调用createWin（） 其他根据不同的窗口变化
	virtual void unregisterWin();//注销控件  会调用destroy（）窗口 其他会根据不同窗口变化
	virtual	void destroyWin();
	
	
	void defocusButton();	 //按钮失焦
	void pressButton(); 	 //按钮按下
	void releaseButton();	 //按钮释放
			
};

//静态框
class staticFrameWin:public controlWin
{
	public:
	staticFrameWin(
			uint16_t winXpos,
			uint16_t winYpos,
			uint16_t winWidth,
			uint16_t winHigh,
			char* name,
			uint8_t wsStyle,
			rootWin* parent,
			xQueueHandle queue
			);
	virtual ~staticFrameWin();
	virtual void paintWin();//绘画 就自己 不同的窗口实现不同
	virtual void registerWin();//激活控件--注册 中间会调用createWin（） 其他根据不同的窗口变化
	virtual void unregisterWin();//注销控件  会调用destroy（）窗口 其他会根据不同窗口变化
	virtual	void destroyWin();
	
	private:

		void winWeakProc(rootWin* rw, MsgType mt, uint32_t d1, uint32_t d2);
};

//列表
class listBarWin:public controlWin
{

	public:
		listBarWin(
			uint16_t winXpos,
			uint16_t winYpos,
			uint16_t winWidth,
			uint16_t winHigh,
			char* name,
			uint8_t wsStyle,
			rootWin* parent,
			xQueueHandle queue,
			char**  itemList, 
			uint8_t num
		);

		virtual ~listBarWin();
			
		virtual void paintWin(){};	 	//绘画 就自己 不同的窗口实现不同
		virtual void registerWin();	  	//激活控件--注册 中间会调用createWin（） 其他根据不同的窗口变化
		virtual void unregisterWin();	//注销控件  会调用destroy（）窗口 其他会根据不同窗口变化
		virtual	void destroyWin();
		
		void defocusListBar();	 	//按钮失焦
		void pressListBar(); 	 	//按钮按下
		void releaseListBar();	 	//按钮释放
 
		bool isOpen(){return openStat;}
		void changeOpenState();
		
		void initItem();
		char** getItemList(){return itemList;}
		rootWin** getRwList(){return rwList;}
		uint8_t getItemNum(){return itemNum;}
		uint16_t getItemHigh(){return this->itemHigh;}
	private:
		//并存入相应的列表里	
		uint8_t itemNum;
		uint16_t itemHigh;
		char** itemList;//存储每一项字符数据的指针的数组
		rootWin** rwList;
		uint32_t winColor;
		bool openStat;
};

//列表
class optionWin:public controlWin
{
public:
	public:
		optionWin(
			uint16_t winXpos,
			uint16_t winYpos,
			uint16_t winWidth,
			uint16_t winHigh,
			char* name,
			uint8_t wsStyle,
			rootWin* parent,
			xQueueHandle queue
		);
		virtual ~optionWin();
			

private:
	
};

#endif //!_WINCLASS_HPP_
