#pragma once


class Point {
public:
	Point(int x, int y):
		m_x(x), m_y(y) {}
	Point(const Point& p):
		m_x(p.m_x), m_y(p.m_y) {}
	virtual ~Point() {}
	
	int x() const { return m_x; }
	int y() const { return m_y; }

protected:
	int m_x, m_y;
};


class Dimension {
public:
	Dimension(int w, int h):
		m_w(w), m_h(h) {}
	Dimension(const Dimension& d):
		m_w(d.m_w), m_h(d.m_h) {}
	virtual ~Dimension() {}
	
	int w() const { return m_w; }
	int h() const { return m_h; }

protected:
	int m_w, m_h;
};


class Box: public Dimension, public Point {
public:
	Box(int x, int y, int w, int h):
			Point(x, y), Dimension(w, h) {}
	Box(const Box& b):
			Point(b.m_x, b.m_y), Dimension(b.m_w, b.m_h) {}
	virtual ~Box() {}

	Point center() {
		return Point(
			m_x + m_w / 2,
			m_y + m_h / 2
		);
	}
};
