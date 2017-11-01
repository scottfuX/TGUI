#include "winClass.hpp"

message::message(
	rootWin* rw,
	MsgType  mt, 
	uint32_t data1,
	uint32_t data2,
	uint16_t time
)
{
	this->rw = rw;
	this->mt = mt;
	this->data1 = data1;
	this->data2 = data2;
	this->time = time;
}
message::~message()
{
	delete this;
}




