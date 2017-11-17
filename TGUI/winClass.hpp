#ifndef _WINCLASS_HPP_
#define _WINCLASS_HPP_ 

#ifdef __cplusplus
extern "C"  {
#endif

#include "interface_conf/tgui_conf.h"
#include "includes_all.h"
	
extern uint16_t win_id;
extern uint8_t win_buffer[];	
extern uint8_t LCD_BUFADDR[];
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
#define	 WS_MINIMIZEBOX 		256//标题栏上带最小化按钮
#define	 WS_MAXIMIZEBOX 		512//标题栏上带最大化按钮



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
	MSG_RELEASECLICK,	//释放
	MSG_UNCLICK,
	MSG_CLOSE,	  		//关闭
	MSG_REDUCTION,		//缩小
	MSG_KEYBOARD,			//键盘
	MSG_RADIOBTN,			//单选
	MSG_ITEM,					//列表
	MSG_SLIDERMOV,		//滑块
	MSG_CHAR,					//字符
	MSG_DIALOG,
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

typedef struct node{
	rootWin* win;
	struct node* next;
}winListNode;

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
			rootWin* parent,
			xQueueHandle queue
		);
		virtual ~rootWin();//设置为虚函数 delete时 就会删除子类
		
		uint16_t getWinXpos(){return winXpos;}
		uint16_t getWinYpos(){return winYpos;}
		uint16_t getWinWidth(){return winWidth;}
		uint16_t getWinHigh(){return winHigh;}
		char* getWinName(){return name;}
		xQueueHandle getQueue(){return this->queue;}
		void setWinXpos(uint16_t winXpos){this->winXpos = winXpos;this->setAbsoluteXY();}   
		void setWinYpos(uint16_t winYpos){this->winYpos = winYpos;this->setAbsoluteXY();}
		void setWinWidth(uint16_t winWidth){this->winWidth = winWidth;}
		void setWinHigh(uint16_t winHigh){this->winHigh = winHigh;}
		void setName(char* name){this->name = name;}
		rootWin* getParent(){return  parent;};//查找父亲节点
		rootWin* getBrother(){return brother;};//查找下一个兄弟节点
		rootWin* getChild(){return child;};//查找第一个孩子节点
		void setParent(rootWin* rw){this->parent = rw;};
		void setBrother(rootWin* rw){ this->brother = rw;};
		void setChild(rootWin* rw){this->child = rw;};
		uint16_t getAbsoluteX(){return absoluteX;}
		uint16_t getAbsoluteY(){return absoluteY;}
		
		void setWinID(uint16_t id){this->winID = id;}
		uint16_t getWinID(){return winID;}
		
		void setAbsoluteXY();		//设置绝对x，y
		bool isWinSelected(){return winSelectedStat;}//是否被选中
		void changSelectedStat();
		void setWinSelectedStat(bool winSelectedStat){this->winSelectedStat = winSelectedStat;}
		bool isInArea(uint16_t wXpos,uint16_t wYpos);
		bool isHaveWinProc(){return this->WinProcSign;}//是否有窗口过程函数
		rootWin* locateWin(uint16_t x,uint16_t y);//定位 然后返回其中最接近的win指针
		void movtoFront();  //移到最前端 -- 保证该对象在兄弟对象中最先被访问 
		void movtoBack();
		retStatus sendMSGtoBack(message* msg,xQueueHandle que);
		retStatus sendMSGtoFront(message* msg,xQueueHandle que);
		
		void markCovered();
		void markDelete();
		void setCoverHead(winListNode* wln){coverHead = wln;}
		winListNode* getCoverHead(){return coverHead;}
		bool getIsMutable(){return isMutable;}
		void setIsMutable(bool m){isMutable = m;}
		
		void (*winProc)(rootWin* , rootWin* , MsgType , uint32_t , uint32_t );//窗口过程
		void setWinProc(void (*winProc)(rootWin* , rootWin* rw, MsgType mt, uint32_t d1, uint32_t d2));
		bool isRegisterWin(){return isAddTree;}
		void paintAll();
		virtual void paintWin()=0;//绘画 就自己 不同的窗口实现不同
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
		xQueueHandle queue;//要发送的消息队列
		uint16_t winID;
		rootWin* parent;//父窗口
		rootWin* child;//子窗口
		rootWin* brother;//兄弟窗口		
		bool winSelectedStat;//窗口是否被选中 //用于显示当前点击点是否在win上
	  bool WinProcSign;//窗口过程标志 表示是否需要
		bool isAddTree;//是否加入树
	
		bool isMutable;//窗口是否可变 ---可变就去找覆盖的窗口
		winListNode* coverHead;//覆盖的窗口 链表映像
	
		void preTraversePaint(rootWin* rw);//先序重绘所有窗口 包括子窗口 和兄弟窗口
		void destroyCAndB();
		void addWintoTree();//创建窗口 -- 即加入树中
		void remWinfromTree();//从树中移除
		
		void travMark(rootWin* rw,uint16_t x,uint16_t y);//遍历标记被覆盖
		void travDelMark(rootWin* rw,uint16_t x,uint16_t y);//遍历删除标记
};

//组合框类
class comboBoxWin
{
public:
	comboBoxWin();
	virtual ~comboBoxWin();
	
	rootWin** getRwList(){return rwList;}
	uint16_t  getRwNum(){return rwNum;}
	void setRwNum(uint16_t num){this->rwNum = num;}
	void comboBoxInit();
	void comboBoxDestroy();
private:
	rootWin** rwList;
	uint16_t 	rwNum;
};

//主窗口--默认没有 //容器安排布局的
class mainWin:public rootWin ,public comboBoxWin
{ 
	public:
	mainWin(
			uint16_t winXpos,
			uint16_t winYpos,
			uint16_t winWidth,
			uint16_t winHigh,
			char* name,
			rootWin* parent,
			xQueueHandle queue,
				uint8_t wsStyle
	);
	virtual ~mainWin();
			
	uint16_t getWinStyle(){return wsStyle;}	
	void setWinStyle(uint8_t wsStyle){this->wsStyle =  wsStyle;}	
	
	void styleInit();
	virtual void paintWin();//绘画 就自己 不同的窗口实现不同
	virtual void registerWin();//激活控件--注册 中间会调用createWin（） 其他根据不同的窗口变化
	virtual void unregisterWin();//注销控件  会调用destroy（）窗口 其他会根据不同窗口变化
	virtual	void destroyWin();	
	
	rootWin* getBackWin();//返回其中的背景窗口

	private:
		uint8_t wsStyle;
		rootWin* backWin;
};

//对话框 ------------
class dialogWin:public mainWin 
{
public:
	dialogWin(
		uint16_t winXpos,
		uint16_t winYpos,
		uint16_t winWidth,
		uint16_t winHigh,
		char* name,
		rootWin* parent,
		xQueueHandle queue,
		uint8_t wsStyle
	);
	virtual ~dialogWin();
		
	virtual void registerWin();
	void closeDialog();	
	void dialogInit();		

private:
	void saveToBuf();
	void readFromBuf();
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
			rootWin* parent,
			xQueueHandle queue
			);
	virtual ~controlWin();
	void displayStrCenter(sFONT font,uint32_t textColor,uint32_t backColor,char* str);    //显示字符串	
	void displayStrNormal(sFONT font,uint32_t textColor,uint32_t backColor,char* str);	
	void setTextColor(uint32_t winColor){this->textColor = winColor;}
	void setBackColor(uint32_t winColor){this->backColor = winColor;}
	void setFont(sFONT f){this->font = f;}	
	uint32_t getTextColor(){return this->textColor;}
	uint32_t getBackColor(){return this->backColor;}
	sFONT getFont(){return this->font;}
	
	virtual void paintWin()=0 ;//绘画 就自己 不同的窗口实现不同
	virtual void registerWin(){} ;//激活控件--注册 中间会调用createWin（） 其他根据不同的窗口变化
	virtual void unregisterWin(){} ;//注销控件  会调用destroy（）窗口 其他会根据不同窗口变化
	virtual	void destroyWin(){};
	
	private:
		uint32_t textColor;
		uint32_t backColor;
		sFONT 	 font;
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


//选项
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
			rootWin* parent,
			xQueueHandle queue,
			bool RadioorCheck
		);
		virtual ~optionWin();
		virtual void paintWin();	 	//绘画 就自己 不同的窗口实现不同
		virtual void registerWin();	  	//激活控件--注册 中间会调用createWin（） 其他根据不同的窗口变化
		virtual void unregisterWin();	//注销控件  会调用destroy（）窗口 其他会根据不同窗口变化
		virtual	void destroyWin();
			
		void defocusOption()	; //选项失焦
		void clickOption();	 	//改变选项
		bool isSelect(){ return selectStat;}
		void setSelectStat(bool stat){this->selectStat = stat;}
			
private:
	bool selectStat;
	void paintOption();//只重绘选项图标
	void changSelectStat();

	bool RadioorCheck;
};

//滑块
class trackBarWin:public controlWin
{
public:
	trackBarWin(
		uint16_t winXpos,
		uint16_t winYpos,
		uint16_t winWidth,
		uint16_t winHigh,
		char* name,
		rootWin* parent,
		xQueueHandle queue,
		bool HorizorVert
	);
	virtual ~trackBarWin();
	virtual void paintWin();	 	//绘画 就自己 不同的窗口实现不同
	virtual void registerWin();	  	//激活控件--注册 中间会调用createWin（） 其他根据不同的窗口变化
	virtual void unregisterWin();	//注销控件  会调用destroy（）窗口 其他会根据不同窗口变化
	virtual	void destroyWin();
	
	
	bool getHorizorVert(){return HorizorVert;}
	void generateValue(); //根据现在的位置求 百分比
	void setSliderWidth(uint16_t sliderWidth){this->sliderWidth = sliderWidth;}
	void sliderSliding(uint16_t xpos,uint16_t ypos);
	void releaseSlider();
	uint8_t getSliderValue(){generateValue();return sliderValue;}
	
private:
	uint8_t sliderValue; //现在滑块位置所代表的值
	uint32_t sliderStat; //前16位为x，后16位为y
	bool HorizorVert; //true 为水平 false为垂直
	uint16_t sliderWidth; //滑块宽度
	void paintSlider(uint16_t xpos,uint16_t ypos);
	
};


//进度条
class progressBarWin :public controlWin
{
public:
	progressBarWin(
		uint16_t winXpos,
		uint16_t winYpos,
		uint16_t winWidth,
		uint16_t winHigh,
		char* name,
		rootWin* parent,
		xQueueHandle queue
	);
	virtual ~progressBarWin();
	
	virtual void paintWin();	 	//绘画 就自己 不同的窗口实现不同
	virtual void registerWin();	  	//激活控件--注册 中间会调用createWin（） 其他根据不同的窗口变化
	virtual void unregisterWin();	//注销控件  会调用destroy（）窗口 其他会根据不同窗口变化
	virtual	void destroyWin();
	
	void paintBarWin();	 //只画进度条
	void setProgressValue(uint8_t pv);//传入 百分比*100 的值
	
private:
	uint16_t pBarWidth;//进度条的宽度
	uint8_t progressValue;//进度条的百分比值
};

//文本框
class textBarWin:public controlWin
{
public:
	textBarWin(
		uint16_t winXpos,
		uint16_t winYpos,
		uint16_t winWidth,
		uint16_t winHigh,
		char* name,
		rootWin* parent,
		xQueueHandle queue
	);
	virtual ~textBarWin();
	virtual void paintWin();	 	//绘画 就自己 不同的窗口实现不同
	virtual void registerWin();	  	//激活控件--注册 中间会调用createWin（） 其他根据不同的窗口变化
	virtual void unregisterWin();	//注销控件  会调用destroy（）窗口 其他会根据不同窗口变化
	virtual	void destroyWin();
	
	void writeChar(char c);
	void writeString(char* s,uint16_t n);
	void setTextBuf(char* s,uint16_t n);
	char*	getTextBuf(){return textBuf;}
	
	

private:
	char* textBuf;
	uint16_t bufSize;
	uint8_t bufIndicator;
	uint16_t charX;//下一个字符的x
	uint16_t charY;//下一个字符的y
	
	void returnLine();
	void deleteChar();
	void displayChar(char c);
};


//图片框-----------未完成
class pictureBoxWin:public controlWin
{
public:
	pictureBoxWin(
		uint16_t winXpos,
		uint16_t winYpos,
		uint16_t winWidth,
		uint16_t winHigh,
		char* name,
		rootWin* parent,
		xQueueHandle queue
	);
	virtual ~pictureBoxWin();
	virtual void paintWin();	 	//绘画 就自己 不同的窗口实现不同
	virtual void registerWin();	  	//激活控件--注册 中间会调用createWin（） 其他根据不同的窗口变化
	virtual void unregisterWin();	//注销控件  会调用destroy（）窗口 其他会根据不同窗口变化
	virtual	void destroyWin();
		
	void setBMPAddress(uint32_t addr){BmpAddress = addr;}
private:
	uint32_t BmpAddress;
};


//列表
class listBarWin:public controlWin, comboBoxWin
{

	public:
		listBarWin(
			uint16_t winXpos,
			uint16_t winYpos,
			uint16_t winWidth,
			uint16_t winHigh,
			char* name,
			rootWin* parent,
			xQueueHandle queue
		);

		virtual ~listBarWin();
		virtual void paintWin();	 	//绘画 就自己 不同的窗口实现不同
		virtual void registerWin();	  	//激活控件--注册 中间会调用createWin（） 其他根据不同的窗口变化
		virtual void unregisterWin();	//注销控件  会调用destroy（）窗口 其他会根据不同窗口变化
		virtual	void destroyWin();
		
		void defocusListBar();	 	//按钮失焦
		void pressListBar(); 	 	//按钮按下
		void releaseListBar();	 	//按钮释放
		void changeOpenList();
		bool isOpen(){return openStat;}
		void changeOpenState();
		void itemInit(char**  itemList, uint8_t num);//--------------------------???????
		
		uint8_t*  getCoverBuffer(){return coverBuffer;}
		uint32_t  getCoverBufLen(){return coverBufLen;}
		char** 	  getItemList(){return itemList;}
		uint16_t  getItemHigh(){return this->itemHigh;}
	private:
		//并存入相应的列表里	
		uint16_t itemHigh;
		char** itemList;//存储每一项字符数据的指针的数组
		uint32_t winColor;
		bool openStat;
		//还未填写
		uint8_t* coverBuffer;//被覆盖的数据的 存储区
		uint32_t coverBufLen;
	
		void saveToBuf();
		void readFromBuf();

};

//单选
class radioBtnWin:public controlWin, comboBoxWin
{
	public:
		radioBtnWin(
			uint16_t winXpos,
			uint16_t winYpos,
			uint16_t winWidth,
			uint16_t winHigh,
			char* name,
			rootWin* parent,
			xQueueHandle queue
		);
		virtual ~radioBtnWin();
		virtual void paintWin();	 	//绘画 就自己 不同的窗口实现不同
		virtual void registerWin();	  	//激活控件--注册 中间会调用createWin（） 其他根据不同的窗口变化
		virtual void unregisterWin();	//注销控件  会调用destroy（）窗口 其他会根据不同窗口变化
		virtual	void destroyWin();
		
		void 	radioBtnInit(char**,uint8_t num,bool hv);

		void 	optionSelect(optionWin* opw);
			
	private:
	char** nameList;
	bool HorizorVert; //true 为水平 false为垂直排列
		
};

//滑块带text显示
class trackTextWin:public controlWin, comboBoxWin
{
public:
	trackTextWin(
		uint16_t winXpos,
		uint16_t winYpos,
		uint16_t winWidth,
		uint16_t winHigh,
		char* name,
		rootWin* parent,
		xQueueHandle queue
			);
	virtual ~trackTextWin();
	virtual void paintWin();	 	//绘画 就自己 不同的窗口实现不同
	virtual void registerWin();	  	//激活控件--注册 中间会调用createWin（） 其他根据不同的窗口变化
	virtual void unregisterWin();	//注销控件  会调用destroy（）窗口 其他会根据不同窗口变化
	virtual	void destroyWin();
		
	void trackTextInit();
	void sliderSliding(uint16_t xpos,uint16_t ypos);
	void releaseSlider();
	void paintText();
private:	
		char* textStr;

};

//虚拟键盘
class virKeyboardWin:public controlWin, comboBoxWin
{
public:
	virKeyboardWin(
		uint16_t winXpos,
		uint16_t winYpos,
		uint16_t winWidth,
		uint16_t winHigh,
		char* name,
		rootWin* parent,
		xQueueHandle queue
	);
	virtual ~virKeyboardWin();
	virtual void paintWin();	 	//绘画 就自己 不同的窗口实现不同
	virtual void registerWin();	  	//激活控件--注册 中间会调用createWin（） 其他根据不同的窗口变化
	virtual void unregisterWin();	//注销控件  会调用destroy（）窗口 其他会根据不同窗口变化
	virtual	void destroyWin(); 
		
	void keyBoardInit();
	void intConverChar(uint32_t data1,uint32_t data2,char *c);//数值转换为字符
	void setDestWorkWin(rootWin* rw){destWorkWin = rw;}
	void keyboardSendChar(char c);
	void wakeupAndConnect(rootWin*rw);//唤醒键盘
private:
	bool shiftStat;
	bool capsLockStat;
	rootWin* destWorkWin; 
	
	
	void saveToBuf();
	void readFromBuf();
};

//布局窗口类 -- 方便控件布局
class layoutWin
{
public:
	layoutWin(
		rootWin* backWin,	//要被布局的对象
		uint16_t X,			//所要布局的范围
		uint16_t Y,
		uint16_t Width,
		uint16_t High
	);
	virtual ~layoutWin();

	rootWin* getBackWin(){return backWin;}
	uint16_t getLayoutX(){return layoutX;}
	uint16_t getLayoutY(){return layoutY;}
	uint16_t getLayoutWidth(){return layoutWidth;}
	uint16_t getLayoutHigh(){return layoutHigh;}
	
	uint16_t getHorizGap(){return horizGap;}
	uint16_t getVertGap(){return vertGap;}
	void setHorizGap(uint16_t horizGap){this->horizGap = horizGap;}
	void setVertGap(uint16_t vertGap){this->vertGap = vertGap;}
	virtual void addWin(rootWin* rw) = 0;
private:
	rootWin* backWin;//要被布局的对象
	uint16_t layoutX;//所要布局的范围
	uint16_t layoutY;
	uint16_t layoutWidth;
	uint16_t layoutHigh;

	uint16_t horizGap; //horizontal间隙
	uint16_t vertGap; //vertical间隙
};

//流式布局
class flowLayoutWin:public layoutWin
{
public:
	flowLayoutWin(
		rootWin* backWin,	//要被布局的对象
		uint16_t X,			//所要布局的范围
		uint16_t Y,
		uint16_t Width,
		uint16_t High,
		uint16_t Hgap,
		uint16_t Vgap
	);
	virtual ~flowLayoutWin();

	virtual void addWin(rootWin* rw);
private:
	uint16_t residualW;//剩余宽度
	uint16_t residualH;//剩余高度
	uint16_t maxH; //一行中最长的高

};

//边界布局
class borderLayoutWin:public layoutWin
{
public:
	borderLayoutWin(
		rootWin* backWin,	//要被布局的对象
		uint16_t X,			//所要布局的范围
		uint16_t Y,
		uint16_t Width,
		uint16_t High
	);
	virtual ~borderLayoutWin();
	virtual void addWin(rootWin* rw);
	void addWin(rootWin* rw,uint16_t seat);
	void setBorderSize(uint16_t northH,uint16_t southH,uint16_t westW,uint16_t eastW);
private:	
	uint16_t northH;
	uint16_t southH;
	uint16_t westW;
	uint16_t eastW;
	uint8_t layoutStat;//布局状态 那几个已经布局了

};

//网格布局
class gridLayoutWin:public layoutWin
{
public:
	gridLayoutWin(
		rootWin* backWin,	//要被布局的对象
		uint16_t X,			//所要布局的范围相对位移
		uint16_t Y,
		uint16_t Width,
		uint16_t High,
		uint8_t  row,
		uint8_t  column
	);
	virtual ~gridLayoutWin();
	virtual void addWin(rootWin* rw);
	void generateGridWH(uint16_t horizGap,uint16_t vertGap);
private:
	uint8_t row; //行
	uint8_t column; //列
	uint8_t currSeat;
	uint16_t gridW;
	uint16_t gridH;
};

#endif //!_WINCLASS_HPP_
