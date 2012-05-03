#ifndef SHOT_H_
#define SHOT_H_
#include "lozobj.h"
#include <cmath>

class Shot : public LoZObject { //A projectile "fired" by enemies
	private:
		double xx, yy, dx, dy;
		bool active;
	public:
		Shot(int x, int y) : LoZObject(x, y) {
			id = '.';
			active = false;
		}
		
		void draw(QPainter& g) {
			if (active) {
				g.setPen(QPen(QColor(255,255,255)));
				g.setBrush(QBrush(QColor(255,255,255), Qt::SolidPattern));
				g.drawEllipse(x, y, 10, 10);
			
				g.setPen(QPen(QColor(255,171,15)));
				g.setBrush(QBrush(QColor(255,171,15), Qt::SolidPattern));
				g.drawEllipse(x+1, y+1, 8, 8);
			
				g.setPen(QPen(QColor(255,33,33)));
				g.setBrush(QBrush(QColor(255,33,33), Qt::SolidPattern));
				g.drawEllipse(x+3, y+3, 4, 4);
			}
		}
		
		void repos(int m, int n) { //Moves projectile to provided space
			xx = m;
			yy = n;
		}
		
		void stop() { //Stops the projectile from moving
			dx = 0;
			dy = 0;
			active = false;
		}
		
		void move() { //Moves projectile along its course
			xx += dx;
			yy += dy;
			x = xx;
			y = yy;
		}
		
		void tick() { //Essentially move()
			move();
		}
		
		void target(int m, int n) { //Uses *Advanced Calculus* to calcualte the path to take to get to Link
			active = true;
			double dix = m - xx;
			double diy = n - yy;
			double hyp = sqrt(dix * dix + diy * diy);
			dx = dix / hyp;
			dy = diy / hyp;
			dx *= 10;
			dy *= 10;
		}
};
#endif
