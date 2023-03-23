#ifndef ALGEBRA_H_
#define ALGEBRA_H_

#include <ostream>

/* Klasa Vector.
 *
 * Reprezentuje dwuwymiarowy
 * wektor (gra działa w 2d).
 */
class Vector {
private:
	double x, y;
	bool dir;

public:
	Vector(bool dir=1);
	Vector(double x, double y, bool dir=1);
	Vector(const Vector&);
	~Vector(void);

	Vector& operator+=(const Vector& rhs);
	Vector& operator-=(const Vector& rhs);
	Vector& operator*=(const double &rhs);

	friend Vector operator+(Vector lhs, const Vector &rhs);
	friend Vector operator-(Vector lhs, const Vector &rhs);

	friend
	std::ostream& operator<<(std::ostream&,
				 const Vector&);

	void set_x(double);
	void set_y(double);

	double get_x(void) const;
	double get_y(void) const;

	bool is_dir(void) const;
};

class Point : public Vector {
public:
	Point(void);
	Point(double x, double y);
	Point(const Point&);
	~Point(void);
};

class Rect {
private:
	Point pos;
	Vector dims;

public:
	Rect(double x, double y,
	     double sx, double sy);
	Rect(Point pos, Vector dims);
	~Rect(void);

	void set_pos(Point);
	void set_pos_x(double x);
	void set_pos_y(double y);
	void set_dims(Vector);
	void set_dim_x(double x);
	void set_dim_y(double y);

	Point get_pos(void) const;
	double get_pos_x(void) const;
	double get_pos_y(void) const;
	Vector get_dims(void) const;
	double get_dim_x(void) const;
	double get_dim_y(void) const;

	double left(void) const;
	double right(void) const;
	double top(void) const;
	double bottom(void) const;
};

#endif /* ALGEBRA_H_ */
