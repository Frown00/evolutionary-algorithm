#pragma once
class NodeCoord
{
	public:
		NodeCoord();
		NodeCoord(NodeCoord* coord);
		NodeCoord(int t_x, int t_y);
		int getX();
		int getY();
	private:
		int m_x = 0;
		int m_y = 0;
};

