import grafica.*;


class MiGrafica {

  float scaleX, scaleY;
  String tit;
  String leyendaX;
  String leyendaY;
  float altura; 
  float origenY;
  int muestras = 0;
  int posicionX, posicionY;
  GPointsArray points;
  int nPoints;
  int i, kx, ky;
  
  MiGrafica(float h, String titulo, String x, String y, int posX, int posY, float escX, float escY, float oY) {

    tit = titulo;
    leyendaX = x;
    leyendaY = y;
    altura = h;  
    posicionX = posX;
    posicionY = posY;
    //GPointsArray points;
    scaleX = escX;
    scaleY = escY;
    nPoints = 50;
    origenY = oY;
    points = new GPointsArray(nPoints);
    i  = 0;
    kx = 1;
    ky = 10;
  }

  void dibujaGrafica(float valor) {

    plot.setPos(posicionX, posicionY);
    plot.setDim(300, 300);
    points.add(muestras, valor);
    i++;
    //points2.add(muestras, temperatura);
    muestras++;
    if (i > kx*scaleX){ //para que cambie la escala si supera las muestras iniciales.
      kx = kx + 3;
    
      }
    plot.setXLim(0, kx * scaleX);
    plot.setYLim(origenY, ky * scaleY);
    plot.setTitleText(tit);
    plot.getXAxis().setAxisLabelText(leyendaX);
    plot.getYAxis().setAxisLabelText(leyendaY);
    plot.setPoints(points);
    plot.beginDraw();
    plot.drawBox();
    plot.drawXAxis();
    plot.drawYAxis();
    plot.drawTitle();
    plot.getMainLayer().drawPoints();
    plot.drawLines();
    plot.endDraw();
    
  }
}
