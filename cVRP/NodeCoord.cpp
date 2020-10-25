#include "Location.h"

NodeCoord::NodeCoord()
{
}

NodeCoord::NodeCoord(NodeCoord* coord)
{
	m_x = coord->getX();
	m_y = coord->getY();
}

NodeCoord::NodeCoord(int t_x, int t_y)
{
	m_x = t_x;
	m_y = t_y;
}

int NodeCoord::getX()
{
	return m_x;
}

int NodeCoord::getY()
{
	return m_y;
}
