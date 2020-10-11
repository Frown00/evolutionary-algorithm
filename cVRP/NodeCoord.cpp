#include "Location.h"

NodeCoord::NodeCoord()
{
}

NodeCoord::NodeCoord(NodeCoord* coord)
{
	this->m_id = coord->getId();
	this->m_x = coord->getX();
	this->m_y = coord->getY();
}

NodeCoord::NodeCoord(int t_id, int t_x, int t_y)
{
	this->m_id = t_id;
	this->m_x = t_x;
	this->m_y = t_y;
}

int NodeCoord::getId()
{
	return this->m_id;
}

int NodeCoord::getX()
{
	return this->m_x;
}

int NodeCoord::getY()
{
	return this->m_y;
}
