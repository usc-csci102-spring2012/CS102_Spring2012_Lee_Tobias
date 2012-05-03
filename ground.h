#ifndef GROUND_H_
#define GROUND_H_
#include "lozobj.h"

class Ground : public LoZObject { //It's the ground. It's walkable on and that's the main important part. It's essentially the only walkable part.
	private:
		QImage image;
		QRect rect;
	public:
		Ground(int x, int y) : LoZObject(x, y) {
			image.load("data/ground.png");
			rect = image.rect();
			id = 'G';
		}
		
		void draw(QPainter& g) {
			//rect.moveTo(x, y);
			//g.drawImage(rect, image);
			g.setPen(QPen(QColor(144,104,40)));
			g.setBrush(QBrush(QColor(144,104,40), Qt::SolidPattern));
			g.drawRect(x, y, 29, 29);
		}
};
#endif
