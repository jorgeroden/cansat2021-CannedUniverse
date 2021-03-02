class Lata {

  float x;
  float y;
  float scaleY;
  float posicionX, posicionY, dimX, dimY;
  String leyendaY;
  

  Lata(float posX, float posY, float dX, float dY, float esca) {

    x = (width / 2) * 1.5;
    scaleY = esca;
    leyendaY = "metros";
    posicionX = posX;
    posicionY = posY;
    dimX = dX;
    dimY = dY;
    
  }
  void display(float h) {

    
    plot.setPos(posicionX, posicionY);
    plot.setDim(dimX, dimY);
    plot.setXLim(0, 10);
    plot.setYLim(0, scaleY);
    plot.getYAxis().setAxisLabelText(leyendaY);
    plot.beginDraw();
    plot.drawBox();
    plot.drawYAxis();
    plot.endDraw();
    rect(x, h, 30, 50);
  }
}
