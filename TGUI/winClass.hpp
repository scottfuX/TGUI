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
	MSG_CLOSE = 1,	
	MSG_DESTROY,	
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


//信息
class message
{
	private:
		rootWin* rw;
		MsgType  mt; // message type
		uint32_t data1;
		uint32_t data2;
		uint16_t time;//时间
	
	public:
		message(rootWin* rw,
		MsgType  mt, 
		uint32_t data1,
		uint32_t data2,
		uint16_t time);
		
		~message();   
	
		rootWin* getDestWin(){return this->rw;}
		MsgType getMsgType(){return this->mt;}
		uint32_t getData1(){return this->data1;}
		uint32_t getData2(){return this->data2;}
		uint16_t getTime(){return this->time;}
};


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
		void setWinProc(void (*winProc)(rootWin*, MsgType, uint32_t, uint32_t));
		void preTraversePaint(rootWin* rw);//先序重绘所有窗口 包括子窗口 
		void createWin();//创建窗口 -- 即加入树中
		void destroyWin();//窗口销毁 --（销毁所有子窗口和本身） 把自己和子类都从树中删除
		void destroyCAndB();
		bool isInArea(uint16_t wXpos,uint16_t wYpos);
		retStatus sendMSGtoBack(message* msg,xQueueHandle que);
		retStatus sendMSGtoFront(message* msg,xQueueHandle que);
		
		virtual void paintWin() = 0;//绘画 就自己 不同的窗口实现不同
		virtual void registerWin() = 0 ;//激活控件--注册 中间会调用createWin（） 其他根据不同的窗口变化
		virtual void unregisterWin() = 0;//注销控件  会调用destroy（）窗口 其他会根据不同窗口变化
		
		
		
	private:
		uint16_t absoluteX;
		uint16_t absoluteY;
		uint16_t winXpos;//相对路径
		uint16_t winYpos;
		uint16_t winWidth;
		uint16_t winHigh;
		char* name;
		uint8_t wsStyle;
		
		xQueueHandle queue;//要发送的消息队列
	
		void (*winProc) (rootWin*, MsgType, uint32_t, uint32_t);//窗口过程
	
		rootWin* parent;//父窗口
		rootWin* child;//子窗口
		rootWin* brother;//兄弟窗口		
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
	
	virtual void paintWin() = 0;//绘画 就自己 不同的窗口实现不同
	virtual void registerWin() = 0 ;//激活控件--注册 中间会调用createWin（） 其他根据不同的窗口变化
	virtual void unregisterWin() = 0;//注销控件  会调用destroy（）窗口 其他会根据不同窗口变化

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
			xQueueHandle queue,
			uint32_t winColor
	);
	virtual ~buttonWin();
			
	virtual void paintWin();//绘画 就自己 不同的窗口实现不同
	virtual void registerWin();//激活控件--注册 中间会调用createWin（） 其他根据不同的窗口变化
	virtual void unregisterWin();//注销控件  会调用destroy（）窗口 其他会根据不同窗口变化
	
	void defocusButton();	 //按钮失焦
	void pressButton(); 	 //按钮按下
	void releaseButton();	 //按钮释放
			
	private:
		uint32_t winColor;
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
			xQueueHandle queue,
			uint32_t winColor
	);
	virtual ~staticFrameWin();
			
	virtual void paintWin();//绘画 就自己 不同的窗口实现不同
	virtual void registerWin();//激活控件--注册 中间会调用createWin（） 其他根据不同的窗口变化
	virtual void unregisterWin();//注销控件  会调用destroy（）窗口 其他会根据不同窗口变化

	private:
		uint32_t winColor;
};

#endif //!_WINCLASS_HPP_
