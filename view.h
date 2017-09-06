#ifndef __VIEW_H__
#define __VIEW_H__

#include "object.h"

#include <random>
#include <vector>
#include <chrono>
#include <thread>
#include <QApplication>
#include <QGraphicsView>
#include <QKeyEvent>
#include <QMouseEvent>

class View : public QGraphicsView {
	double dt;
	bool running;
	bool reset_velocity;
	double object_size;

	std::vector<Object *> objects;

	std::default_random_engine generator1;
	std::default_random_engine generator2;
	std::uniform_real_distribution<double> x_dist;
	std::uniform_real_distribution<double> y_dist;
	std::function<float()> rand_x;
	std::function<float()> rand_y;

	QGraphicsScene scene;

	void resizeEvent(QResizeEvent *event);
	void closeEvent(QCloseEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void mouseDoubleClickEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void keyPressEvent(QKeyEvent *event);

	void update();

public:
	View(std::string title, unsigned int res_x, unsigned int res_y, unsigned int num_objects);
	~View();

	void run();
};

#endif
