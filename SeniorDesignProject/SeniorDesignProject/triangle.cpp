#include "Triangle.h"


Triangle::Triangle()
{
	points[0] = new Point();
	points[1] = new Point();
	points[2] = new Point();
}

Triangle::Triangle(Point* point1, Point* point2, Point* point3)
{
	points[0] = point1;
	points[1] = point2;
	points[2] = point3;
}
Triangle::Triangle(Point* points[3])
{
	setPoints(points);
}


Triangle::~Triangle()
{

}

void Triangle::setPoint(int index,Point* value){
	points[index] = value;
}

void Triangle::setPoints(Point* _points[3]){
	points[0] = _points[0];
	points[1] = _points[1];
	points[2] = _points[2];
}
Point** Triangle::getPoints(){
	return points;
}
Point* Triangle::getPoint(int index){
	return points[index];
}