#ifndef WALL_H_
#define WALL_H_
#include "lozobj.h"

class Wall : public LoZObject { //Walls used to look pretty, until Qt lagged too much. Now they're just squares. Link can't walk onto them, that's all that matters.
	private:
		QImage image[8];
		QRect rect[8];
		int type;
	public:
		Wall(int m, int n, int t) : LoZObject(m, n) {
			image[0].load("data/cornertl.png");
			image[1].load("data/cornertr.png");
			image[2].load("data/cornerbl.png");
			image[3].load("data/cornerbr.png");
			image[4].load("data/wallt.png");
			image[5].load("data/walll.png");
			image[6].load("data/wallr.png");
			image[7].load("data/wallb.png");
			for (int i = 0; i < 8; i++)
				rect[i] = image[i].rect();
				type = t;
			id = 'W';
		}
		
		void draw(QPainter& g) {
			//rect[type].moveTo(x, y);
			//g.drawImage(rect[type], image[type]);
			g.setPen(QPen(QColor(136,152,88)));
			g.setBrush(QBrush(QColor(136,152,88), Qt::SolidPattern));
			g.drawRect(x, y, 29, 29);
		}
};
#endif
