#include "cell.h"

char cell::getValue()
{	return value;}

void cell::setValue(char t)
{	value = t; }

void cell::incrementValue()
{value++;}

bool cell::isOpen()
{	return is_open;}

void cell::open()
{	is_open = true;}

void cell::close()
{	is_open = false;}