#pragma once
class Sheep
{
private:
	static int sheepCounter;
	bool hasJumped;
	int id;
public:
	Sheep();
	int getId() const;
	bool jump();
};

