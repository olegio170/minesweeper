#pragma once

class cell
{
public:
	cell() : value(' '),is_open(false),is_flaged(false)
	{}
	char getValue();
	void setValue(char t);
	void incrementValue();

	bool isOpen();
	bool open();
	bool close();
	bool isFlaged();
	bool setFlag();
	bool unSetFlag();
private:
	char value;
	bool is_open,is_flaged;
};
