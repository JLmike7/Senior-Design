#include "Box.h"


//By default, box is the unit cube centered around the origin
Box::Box(){
	setFromWHD(new Point(0.0f,0.0f,0.0f), 1.0f, 1.0f, 1.0f);
}

Box::Box(Point* center,float width, float height, float depth){
	setFromWHD(center,width,height,depth);
}

Box::Box(Point* _points[8]){
	for (int i = 0; i < 6; i++)
		points[i] = _points[i];
}

Box::~Box(){

}

//Triangle** Box::getInwardTriangles(){
//	Triangle* triangles[12];
//	rectanglesToTriangles(getInwardQuads(), triangles, 6);
//	return triangles;
//}
//Triangle** Box::getOutwardTriangles(){
//	Triangle* triangles[12];
//	rectanglesToTriangles(getOutwardQuads(), triangles, 6);
//	return triangles;
//}
//
//Quad** Box::getInwardQuads(){
//	Quad* rectangles[6];
//	rectangles[TOP_FACE] = getInwardTop();
//	rectangles[BOTTOM_FACE] = getInwardBottom();
//	rectangles[LEFT_FACE] = getInwardLeft();
//	rectangles[RIGHT_FACE] = getInwardRight();
//	rectangles[FRONT_FACE] = getInwardFront();
//	rectangles[BACK_FACE] = getInwardBack();
//	return rectangles;
//}
//Quad** Box::getOutwardQuads(){
//	Quad* rectangles[6];
//	rectangles[TOP_FACE] = getOutwardTop();
//	rectangles[BOTTOM_FACE] = getOutwardBottom();
//	rectangles[LEFT_FACE] = getOutwardLeft();
//	rectangles[RIGHT_FACE] = getOutwardRight();
//	rectangles[FRONT_FACE] = getOutwardFront();
//	rectangles[BACK_FACE] = getOutwardBack();
//	return rectangles;
//}
//
//Quad* Box::getOutwardFace(Direction d){
//	switch (d){
//	case Direction::FRONT:
//		return getOutwardFront();
//		break;
//	case Direction::BACK:
//		return getOutwardBack();
//		break;
//	case Direction::LEFT:
//		return getOutwardLeft();
//		break;
//	case Direction::RIGHT:
//		return getOutwardRight();
//		break;
//	case Direction::UP:
//		return getOutwardTop();
//		break;
//	case Direction::DOWN:
//		return getOutwardBottom();
//		break;
//	default:
//		throw std::invalid_argument("Invalid Face Direction");
//		break;
//	}
//}
//Quad* Box::getOutwardTop(){
//	return new Quad(points[4], points[5], points[6], points[7]);
//}
//Quad* Box::getOutwardBottom(){
//	return new Quad(points[0], points[1], points[2], points[3]);
//}
//Quad* Box::getOutwardLeft(){
//	return new Quad(points[7], points[4], points[0], points[3]);
//}
//Quad* Box::getOutwardRight(){
//	return new Quad(points[1], points[2], points[6], points[5]);
//}
//Quad* Box::getOutwardFront(){
//	return new Quad(points[3], points[2], points[6], points[7]);
//}
//Quad* Box::getOutwardBack(){
//	return new Quad(points[0], points[1], points[5], points[4]);
//}
//
//Quad* Box::getInwardFace(Direction d){
//	switch (d){
//	case Direction::FRONT:
//		return getInwardFront();
//		break;
//	case Direction::BACK:
//		return getInwardBack();
//		break;
//	case Direction::LEFT:
//		return getInwardLeft();
//		break;
//	case Direction::RIGHT:
//		return getInwardRight();
//		break;
//	case Direction::UP:
//		return getInwardTop();
//		break;
//	case Direction::DOWN:
//		return getInwardBottom();
//		break;
//	default:
//		throw std::invalid_argument("Invalid Face Direction");
//		break;
//	}
//}
//Quad* Box::getInwardTop(){
//	return new Quad(points[7], points[6], points[5], points[4]);
//}
//Quad* Box::getInwardBottom(){
//	return new Quad(points[3], points[2], points[1], points[0]);
//}
//Quad* Box::getInwardLeft(){
//	return new Quad(points[3], points[0], points[4], points[7]);
//}
//Quad* Box::getInwardRight(){
//	return new Quad(points[5], points[6], points[2], points[1]);
//}
//Quad* Box::getInwardFront(){
//	return new Quad(points[7], points[6], points[2], points[3]);
//}
//Quad* Box::getInwardBack(){
//	return new Quad(points[4], points[5], points[1], points[0]);
//}
//
////to array must be twice the size of from, because there will be twice as many triangles as rectangles.
//void Box::rectanglesToTriangles(Quad** from, Triangle** to, int size){
//	for (int i = 0; i < size; i++){
//		copyTriangles(from[i]->getTriangles(), to, 2);
//	}
//}

//void Box::copyTriangles(Triangle** from, Triangle** to, int size){
//	for (int i = 0; i < size; i++)
//		to[i] = from[i];
//}

void Box::setFromWHD(Point* center,float width, float height, float depth){
	width /= 2;
	height /= 2;
	depth /= 2;
	float x = center->getX();
	float y = center->getY();
	float z = center->getZ();

	points[0] = new Point({ x - width, y + height, z + depth });
	points[1] = new Point({ x + width, y + height, z + depth });
	points[2] = new Point({ x + width, y + height, z - depth });
	points[3] = new Point({ x - width, y + height, z - depth });
	points[4] = new Point({ x - width, y - height, z + depth });
	points[5] = new Point({ x + width, y - height, z + depth });
	points[6] = new Point({ x + width, y - height, z - depth });
	points[7] = new Point({ x - width, y - height, z - depth });
}