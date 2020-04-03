#pragma once

class People

{
public:
	People(char* name,char* sex,float height);
	~People(void);
private:
	char name[10];
	char sex[10];
	float height;
public:
	void showInfo();
};

