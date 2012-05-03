#include <QDesktopWidget>
#include <QApplication>
#include "loz.h"

void center(QWidget &widget)
{
  int x, y;
  int screenWidth;
  int screenHeight;

  int WIDTH = 450;
  int HEIGHT = 375;


  QDesktopWidget *desktop = QApplication::desktop();

  screenWidth = desktop->width();
  screenHeight = desktop->height();

  x = (screenWidth - WIDTH) / 2;
  y = (screenHeight - HEIGHT) / 2;

  widget.setGeometry(x, y, WIDTH, HEIGHT);
  widget.setFixedSize(WIDTH, HEIGHT);
}


int main(int argc, char *argv[])
{
  QApplication app(argc, argv);
  
  LoZ window;
  //Not much worth saying goes on in here. Moreso because this isn't my code here, it's Prof. Tejada's/Whoever she borrowed this code from.
  window.setWindowTitle("The Legend of Zelda: Oracle of Ages");
  window.show();
  center(window);

  return app.exec();
}
