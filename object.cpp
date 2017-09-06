#include "object.h"

int Object::cnt = -1;

QGraphicsScene *Object::scene;

Object::Object(Vec2& pos, Vec2& vel, double size, double mass, bool solid) {
	id = cnt++;
	this->size = size;
	this->pos = pos;
	this->vel = vel;
	this->mass = mass;
	this->solid = solid;
	pic = NULL;
	if(id >= 0)
		pic = Object::scene->addEllipse(pos.x - 0.5 * size, pos.y - 0.5 * size,
						size, size, QPen(), QBrush(QColor("black")));
}

Object::~Object() {
}

Vec2 Object::coll_2d(const Object *other) {
	Vec2 mm = other->pos - pos;
	Vec2 mm_normal = mm.normal();

	double v1_par = vel.project_onto(mm);
	Vec2 v1_perp = mm_normal.normalize() * vel.project_onto(mm_normal);
	double v2_par = other->vel.project_onto(mm);
	Vec2 v2_perp = mm_normal.normalize() * other->vel.project_onto(mm_normal);

	double v_par_new = (mass * v1_par + other->mass * (2 * v2_par - v1_par)) / (mass + other->mass);
	Vec2 v1_par_new = mm.normalize() * v_par_new;

	return v1_par_new + v1_perp;
}

void Object::move(double dt) {
	Vec2 pos_tmp = pos + vel * dt;
	if(pos_tmp.x - size / 2 < 0) {
		pos_tmp.x = size - pos_tmp.x;
		vel.x = -vel.x;
	}
	if(pos_tmp.x + size / 2 > scene->width()) {
		pos_tmp.x = 2 * scene->width() - size - pos_tmp.x;
		vel.x = -vel.x;
	}
	if(pos_tmp.y - size / 2 < 0) {
		pos_tmp.y = size - pos_tmp.y;
		vel.y = -vel.y;
	}
	if(pos_tmp.y + size / 2 > scene->height()) {
		pos_tmp.y = 2 * scene->height() - size - pos_tmp.y;
		vel.y = -vel.y;
	}

	Vec2 mov = pos_tmp - pos;
	if(pic)
		pic->moveBy(mov.x, mov.y);

	pos = pos_tmp;
}

void Object::set_scene(QGraphicsScene *scene) {
	Object::scene = scene;
}
