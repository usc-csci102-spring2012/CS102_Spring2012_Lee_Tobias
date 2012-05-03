#ifndef DOOR_H_
#define DOOR_H_
#include "lozobj.h"

class Door : public LoZObject { //A door that Link can go through
	private:
		int hash; //If 0, door is open. If not, hash is accessed in room.h to see the opening conditions.
		int next;
	public:
		Door(int x, int y, int i, int n) : LoZObject(x, y), hash(i), next(n) { //Constructor
			if (hash > 0) //Event-triggered doors
				id = 'X';
			else if (hash < 0) //Normal locked doors
				id = '*';
			else
				id = 'D';
		}
		
		void draw(QPainter& g) { //Draws the door, depending on what kind of door it is.
			if (hash != 0) {
				g.setPen(QPen(QColor(0,64,126)));
				g.setBrush(QBrush(QColor(0,64,126), Qt::SolidPattern));
				g.drawRect(x, y, 29, 29);
				if (id == '*') {
					g.setPen(QPen(QColor(0,0,0)));
					g.setBrush(QBrush(QColor(0,0,0), Qt::SolidPattern));
					g.drawEllipse(x+11, y+8, 8, 8);
					g.drawRect(x+13, y + 12, 4, 10);
				}
			}
			else {
				g.setPen(QPen(QColor(144,104,40)));
				g.setBrush(QBrush(QColor(144,104,40), Qt::SolidPattern));
				g.drawRect(x, y, 29, 29);
			}
		}
		
		void setHash(int i) { //Mainly for opening/unlocking
			hash = i;
			if (hash != 0)
				id = 'X';
			else
				id = 'D';
		}
		
		int getHash() { //For managing in room.h
			return hash;
		}
		
		int getNext() { //To know where to go
			if (hash != 0)
				return -1;
			else
				return next;
		}
};
#endif
