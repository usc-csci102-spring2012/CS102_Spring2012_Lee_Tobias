#ifndef HOLE_H_
#define HOLE_H_
#include "lozobj.h"

class Hole : public LoZObject { //A hole that Link can fall into and take damage.
	private:
		
	public:
		Hole(int x, int y) : LoZObject(x, y) {
			id = 'H';
		}
		
		void draw(QPainter& g) {
			g.setPen(QPen(QColor(0,0,0)));
			g.setBrush(QBrush(QColor(0,0,0), Qt::SolidPattern));
			g.drawRect(x, y, 29, 29);
		}
};
#endif
