#ifndef WARP_H_
#define WARP_H_
#include "lozobj.h"

class Warp : public LoZObject { //It's pretty much like a door, so I won't say much here.
	private:
		int next;
	public:
		Warp(int x, int y, int n) : LoZObject(x, y), next(n) {
			id = '?';
		}
		
		void draw(QPainter& g) {
			g.setPen(QPen(QColor(144,104,40)));
			g.setBrush(QBrush(QColor(144,104,40), Qt::SolidPattern));
			g.drawRect(x, y, 29, 29);
			
			g.setPen(QPen(QColor(10,181,245)));
			g.setBrush(QBrush(QColor(10,181,245), Qt::SolidPattern));
			g.drawEllipse(x, y, 29, 29);
			
			g.setPen(QPen(QColor(144,104,40)));
			g.setBrush(QBrush(QColor(144,104,40), Qt::SolidPattern));
			g.drawEllipse(x+2, y+2, 25, 25);
			
			g.setPen(QPen(QColor(10,181,245)));
			g.setBrush(QBrush(QColor(10,181,245), Qt::SolidPattern));
			g.drawEllipse(x+5, y+5, 19, 19);
			
			g.setPen(QPen(QColor(144,104,40)));
			g.setBrush(QBrush(QColor(144,104,40), Qt::SolidPattern));
			g.drawEllipse(x+7, y+7, 15, 15);
			
			g.setPen(QPen(QColor(10,181,245)));
			g.setBrush(QBrush(QColor(10,181,245), Qt::SolidPattern));
			g.drawEllipse(x+10, y+10, 9, 9);
		}
		
		int getNext() {
			return next;
		}
};
#endif
