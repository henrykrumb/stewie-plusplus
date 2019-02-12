#pragma once


class Box {
public:
	Box(int x, int y, int w, int h):
			m_x(x), m_y(y), m_w(w), m_h(h) {}
	Box(const Box& b):
			m_x(b.m_x), m_y(b.m_y), m_w(b.m_w), m_h(b.m_h) {}
	virtual ~Box() {}

	int x() const { return m_x; }
	int y() const { return m_y; }
	int w() const { return m_w; }
	int h() const { return m_h; }

private:
	int m_x, m_y, m_w, m_h;
};
