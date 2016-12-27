#pragma once

class cell
{
public:
	cell() : value(' '),is_open(false)
	{}
	char getValue();
	void setValue(char t);
	void incrementValue();

	bool isOpen();
	void open();
	void close();
private:
	char value;
	bool is_open;
};
