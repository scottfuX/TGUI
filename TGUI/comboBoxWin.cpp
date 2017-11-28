#include "winClass.h"

comboBoxWin::comboBoxWin()
{
	rwList = NULL;
	rwNum = 0;
}

comboBoxWin::~comboBoxWin()
{

}


void comboBoxWin::comboBoxInit()
{
	rwList = new rootWin*[rwNum];
}

void comboBoxWin::comboBoxDestroy()
{
	//不需要把里面的都注销，因为这些控件还在树中
	delete rwList;
}
