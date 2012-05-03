#ifndef TORCH_H_
#define TORCH_H_
#include "lozobj.h"

class Torch : public LoZObject { //A decorative Torch. Serves no other real purpose.
	private:
		QImage image;
		QRect rect;
	public:
		Torch(int x, int y) : LoZObject(x, y) {
			image.load("data/torch.png");
			rect = image.rect();
			id = '@';
		}
		
		void draw(QPainter& g) {
			rect.moveTo(x, y);
			g.drawImage(rect, image);
			/*g.setPen(QPen(QColor(0,255,0)));
			g.setBrush(QBrush(QColor(0,255,0), Qt::SolidPattern));
			g.drawRect(x, y, 29, 29);*/
		}
		
};
#endif
