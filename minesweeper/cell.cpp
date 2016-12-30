#include "cell.h"

char cell::getValue()
{	return value;}

void cell::setValue(char t)
{	value = t; }

void cell::incrementValue()
{value++;}

bool cell::isOpen()
{	return is_open;}

bool cell::open()
{
	bool was_open = is_open;
	is_open = true;
	return was_open ? 0 : 1 ;
}

bool cell::close()
{	
	bool was_open = is_open;
	is_open = false;
	return was_open ? 1 : 0;
}

bool cell::isFlaged()
{
	return is_flaged;
}

bool cell::setFlag()
{
	bool was_flaged = is_flaged;
	is_flaged = true;
	return was_flaged ? 0 : 1;
}

bool cell::unSetFlag()
{
	bool was_flaged = is_flaged;
	is_flaged = false;
	return was_flaged ? 1 : 0;
}