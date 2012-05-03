#ifndef SWITCH_H_
#define SWITCH_H_
#include "lozobj.h"

class Switch: public LoZObject { //A switch. Like a Door, has a hash. In fact, is pretty much the same as a door in that everything else is figured out in room.h
	private:
		bool pressed;
		bool stays;
		int hash;
	public:
		Switch(int x, int y, bool t, int h) : LoZObject(x, y) {
			id = 'S';
			pressed = false;
			stays = t;
			hash = h;
		}
		
		void draw(QPainter& g) {
			g.setPen(QPen(QColor(144,104,40)));
			g.setBrush(QBrush(QColor(144,104,40), Qt::SolidPattern));
			g.drawRect(x, y, 29, 29);
			
			if (pressed) {
				g.setPen(QPen(QColor(0,0,0)));
				g.setBrush(QBrush(QColor(143,103,41), Qt::SolidPattern));
				g.drawEllipse(x+10, y+10, 10, 10);
			}
			else {
				g.setPen(QPen(QColor(0,0,0)));
				g.setBrush(QBrush(QColor(205,154,88), Qt::SolidPattern));
				g.drawEllipse(x+10, y+10, 10, 10);
			}
		}
		
		int getHash() {
			return hash;
		}
		
		void press() {
			pressed = true;
		}
		
		void unpress() {
			pressed = false;
		}
		
		bool getPressed() {
			return pressed;
		}
		
		bool getStays() {
			return stays;
		}
		
};
#endif
