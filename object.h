#ifndef __OBJECT_H__
#define __OBJECT_H__

#include "vec2.h"

#include <QGraphicsScene>
#include <QGraphicsEllipseItem>

class Object {
	static int cnt;
	static QGraphicsScene *scene;


	QGraphicsEllipseItem *pic;

public:
	int id;
	bool solid;
	double mass;
	double size;
	Vec2 pos;
	Vec2 vel;

	static void set_scene(QGraphicsScene *scene);

	Object(Vec2& pos, Vec2& vel, double size, double mass, bool solid);
	~Object();

	Vec2 coll_2d(const Object *other);

	void move(double dt);
};

#endif //__OBJECT_H__
