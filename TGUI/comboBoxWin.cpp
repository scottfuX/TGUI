#include "winClass.hpp"

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
	delete rwList;
}
