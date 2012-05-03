#ifndef SWORD_H_
#define SWORD_H_
#include "lozobj.h"

class Sword : public LoZObject { //Link's trusty sword. That is all. It exists in the square in front of Link.
	private:
		int dir;
	public:
		Sword(int m, int n) : LoZObject(m, n) {
			dir = 6;
			id = 'l';
		}
		
		void reposition(int m, int n, int d) {
			dir = d;
			switch (d) {
				case 2:	y = n + 30;
						x = m + 10;
						break;
				case 4:	y = n + 10;
						x = m - 30;
						break;
				case 6:	y = n + 10;
						x = m + 30;
						break;
				case 8:	y = n - 30;
						x = m + 10;
						break;
			}
		}
		
		void draw(QPainter& g) {
			g.setPen(QPen(QColor(50,50,50)));
			g.setBrush(QBrush(QColor(177,177,177), Qt::SolidPattern));
			
			if (dir == 4 || dir == 6) {
				g.drawRect(x, y, 30, 10);
			}
			else {
				g.drawRect(x, y, 10, 30);
			}
		}
		
		QRect getWrecked() {
			if (dir == 4 || dir == 6)
				return QRect(x, y, 30, 10);
			return QRect(x, y, 10, 30);
		}
};
#endif
