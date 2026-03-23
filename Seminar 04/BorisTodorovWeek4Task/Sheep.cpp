#include "Sheep.h"
#include <iostream>
#include <print>
using namespace std;
int Sheep::sheepCounter = 0;

Sheep::Sheep() :id(++sheepCounter),hasJumped(false) {}

bool Sheep::jump()
{
	if (hasJumped)
		return false;
	println("Sheep {} jumped!",id);
	hasJumped = true;
	return true;
}
int Sheep::getId() const
{
	return id;
}
