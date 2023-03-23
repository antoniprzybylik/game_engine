#include "algebra.h"

Vector::Vector(bool dir) :
x(0),
y(0),
dir(dir)
{
}

Vector::Vector(double x, double y, bool dir) :
x(x),
y(y),
dir(dir)
{
}

Vector::Vector(const Vector &vector)
{
	this->x = vector.x;
	this->y = vector.y;
	this->dir = vector.dir;
}

Vector::~Vector(void)
{
	/* FIXME */
}

Vector& Vector::operator+=(const Vector& rhs)
{
	if (!rhs.is_dir()) {
		/* FIXME:
		 * RHS nie jest kierunkiem,
		 * a punktem: Zabronione.
		 */
	}

	this->x += rhs.x;
	this->y += rhs.y;

	return *this;
}

Vector& Vector::operator-=(const Vector& rhs)
{
	if (!rhs.is_dir()) {
		/* FIXME:
		 * RHS nie jest kierunkiem,
		 * a punktem: Zabronione.
		 */
	}

	this->x -= rhs.x;
	this->y -= rhs.y;

	return *this;
}

Vector& Vector::operator*=(const double& rhs)
{
	this->x *= rhs;
	this->y *= rhs;

	return *this;
}

Vector operator+(Vector lhs, const Vector &rhs)
{
	lhs += rhs;
	return lhs;	
}

Vector operator-(Vector lhs, const Vector &rhs)
{
	lhs -= rhs;
	return lhs;
}

std::ostream& operator<<(std::ostream &os,
			 const Vector &obj)
{
	os << (obj.dir ? '[' : '(');
	os << obj.x << ", " << obj.y;
	os << (obj.dir ? ']' : ')');

	return os;
}

void Vector::set_x(double x)
{
	this->x = x;
}

void Vector::set_y(double y)
{
	this->y = y;
}

double Vector::get_x(void) const
{
	return this->x;
}

double Vector::get_y(void) const
{
	return this->y;
}

bool Vector::is_dir(void) const
{
	return this->dir;
}

Point::Point(void) :
Vector(0, 0, 0)
{
}

Point::Point(double x, double y) :
Vector(x, y, 0)
{
}

Point::Point(const Point &podouble) :
Vector(podouble)
{
}

Point::~Point(void)
{
}

Rect::Rect(double x, double y,
     double sx, double sy)
{
	this->pos = Point(x, y);
	this->dims = Vector(sx, sy);
}

Rect::Rect(Point pos, Vector dims)
{
	this->pos = pos;
	this->dims = dims;
}

Rect::~Rect(void)
{
	/* FIXME */
}

void Rect::set_pos(Point pos)
{
	this->pos = pos;
}

void Rect::set_pos_x(double x)
{
	this->pos.set_x(x);
}

void Rect::set_pos_y(double y)
{
	this->pos.set_y(y);
}

void Rect::set_dims(Vector dims)
{
	this->dims = dims;
}

void Rect::set_dim_x(double x)
{
	this->dims.set_x(x);
}

void Rect::set_dim_y(double y)
{
	this->dims.set_y(y);
}

Point Rect::get_pos(void) const
{
	return this->pos;
}

double Rect::get_pos_x(void) const
{
	return this->pos.get_x();
}

double Rect::get_pos_y(void) const
{
	return this->pos.get_y();
}

Vector Rect::get_dims(void) const
{
	return this->dims;
}

double Rect::get_dim_x(void) const
{
	return this->dims.get_x();
}

double Rect::get_dim_y(void) const
{
	return this->dims.get_y();
}

double Rect::left(void) const
{
	return this->pos.get_x();
}

double Rect::right(void) const
{
	return this->pos.get_x() + this->dims.get_x();
}

double Rect::top(void) const
{
	return this->pos.get_y();
}

double Rect::bottom(void) const
{
	return this->pos.get_y() + this->dims.get_y();
}
