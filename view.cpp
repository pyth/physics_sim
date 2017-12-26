#include "view.h"

View::View(std::string title, unsigned int res_x, unsigned int res_y, unsigned int num_objects) : QGraphicsView() {
	running = true;
	reset_velocity = false;
	object_size = 10.f;

	objects.resize(num_objects + 1);

	setWindowTitle(title.c_str());

	setScene(&scene);
	resize(res_x, res_y);
	setAlignment(Qt::AlignTop | Qt::AlignLeft);
	setViewportUpdateMode(QGraphicsView::NoViewportUpdate);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setRenderHint(QPainter::Antialiasing, true);

	Object::set_scene(&scene);

	generator1.seed(std::random_device()());
	generator2.seed(std::random_device()());
	x_dist = std::uniform_real_distribution<double>(object_size * 0.5f, res_x - object_size * 0.5f);
	y_dist = std::uniform_real_distribution<double>(object_size * 0.5f, res_y - object_size * 0.5f);
	rand_x = std::bind(x_dist, generator1);
	rand_y = std::bind(y_dist, generator2);

	Vec2 pos;
	Vec2 vel;
	objects[0] = new Object(pos, vel, 10.0, 0.0, false);

	bool occupied;
	for(unsigned int i = 1; i < num_objects + 1; i++) {
		do {
			occupied = false;
			pos = Vec2(rand_x(), rand_y());
			for(unsigned int j = 0; j < i; j++) {
				if(((objects[j]->pos - pos).length() <= object_size))
					occupied = true;
			}
		} while(occupied);
		objects[i] = new Object(pos, vel, 10.0, 1e12, true);
	}
}

View::~View() {
}

void View::resizeEvent(QResizeEvent *event) {
	scene.setSceneRect(QRect(QPoint(0, 0), event->size()));
   	QGraphicsView::resizeEvent(event);
}

void View::closeEvent(QCloseEvent *event) {
	running = false;
	QGraphicsView::closeEvent(event);
}

void View::mousePressEvent(QMouseEvent *event) {
	objects[0]->pos = Vec2(event->x(), event->y());
	if(event->button() == Qt::LeftButton) {
		objects[0]->mass = 1e14;
	} else if(event->button() == Qt::RightButton) {
		objects[0]->mass = -1e14;
	}
	event->ignore();
}

void View::mouseReleaseEvent(QMouseEvent *event) {
	objects[0]->mass = 0.0;
	event->ignore();
}

void View::mouseDoubleClickEvent(QMouseEvent *event) {
	event->ignore();
}

void View::mouseMoveEvent(QMouseEvent *event) {
	objects[0]->pos = Vec2(event->x(), event->y());
	event->ignore();
}

void View::keyPressEvent(QKeyEvent *event) {
	int key = event->key();
	switch(key) {
		case Qt::Key_Escape:
			running = false;
			break;
		case Qt::Key_R:
			reset_velocity = true;
			break;
		default:
			break;
	}
	event->ignore();
}

void View::update() {
	if(reset_velocity) {
		for(Object *obj : objects) {
			obj->vel = Vec2(0);
		}
		reset_velocity = false;
	} else {
		for(unsigned int i = 0; i < objects.size(); i++) {
			for(unsigned int j = 0; j < objects.size(); j++) {
				if((i == 0 || j == 0) && (objects[i]->pos + objects[i]->vel * dt - objects[j]->pos + objects[j]->vel * dt).length() <= object_size)
					continue;

				if(i == j)
					break;

				Vec2 dir = objects[j]->pos - objects[i]->pos;
				objects[i]->vel += dir.normalize() * 6.673e-11 *
							objects[j]->mass / pow(dir.length(), 2) * dt;
				objects[j]->vel += -dir.normalize() * 6.673e-11 *
							objects[i]->mass / pow(dir.length(), 2) * dt;
			}
			for(unsigned int j = 1; j < objects.size(); j++) {
				if(i == 0)
					continue;

				if(i == j)
					break;

				Vec2 pos1 = objects[i]->pos + objects[i]->vel * dt;
				Vec2 pos2 = objects[j]->pos + objects[j]->vel * dt;
				if((pos1 - pos2).length() <= object_size) {
					Vec2 mm = objects[j]->pos - objects[i]->pos;
					Vec2 mm_normal = mm.normal();

					double v1_par = objects[i]->vel.project_onto(mm);
					Vec2 v1_perp = mm_normal.normalize() * objects[i]->vel.project_onto(mm_normal);
					double v2_par = objects[j]->vel.project_onto(mm);
					Vec2 v2_perp = mm_normal.normalize() * objects[j]->vel.project_onto(mm_normal);

					Vec2 v1_par_new = mm.normalize() * (objects[i]->mass * v1_par + objects[j]->mass * (2 * v2_par - v1_par)) / (objects[i]->mass + objects[j]->mass);
					Vec2 v2_par_new = mm.normalize() * (objects[j]->mass * v2_par + objects[i]->mass * (2 * v1_par - v2_par)) / (objects[i]->mass + objects[j]->mass);

					objects[i]->vel = v1_par_new + v1_perp;
					objects[j]->vel = v2_par_new + v2_perp;
				}
			}
		}

		for(Object *obj : objects) {
			obj->move(dt);
		}
	}
	scene.update();
}

void View::run() {
	show();
	std::chrono::high_resolution_clock::time_point t1;
	std::chrono::duration<double> frame_duration(1.0 / 60);
	std::chrono::duration<double> duration;
	while(running) {
		QApplication::processEvents();
		t1 = std::chrono::high_resolution_clock::now();
		update();
		duration = std::chrono::high_resolution_clock::now() - t1;
		std::this_thread::sleep_for(frame_duration - duration);
		duration = std::chrono::high_resolution_clock::now() - t1;
		dt = duration.count();
	}
}
