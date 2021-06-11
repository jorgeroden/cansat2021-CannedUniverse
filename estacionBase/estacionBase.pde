import processing.serial.*;
import grafica.*;

GPlot plot, plot2;
MiGrafica gh, gt; //grafica de la altura
Lata gl;
float altitud, temperatura, altitudgraf;
float ancho, alto; //area caida lata
Serial myPort;
int lf = 10;
void setup() {

  size(800, 800);
  //Crea objetos para graficas
  plot = new GPlot(this); //El objeto plot se crea en el setup()
  //altitud, titulo, leyendaX, leyendaY, posicionX, posicion Y, escalaX, escalaY, ordenada en Y (para valores negativos)
  gh = new MiGrafica(altitud, "Altitud", "muestras", "Metros", 25, 25, 10, 100, 0);
  gt = new MiGrafica(temperatura, "Temperatura", "muestras", "Celsius ", 25, 400, 10, 5, -5);

  ancho = 200;
  alto = 700;
  //posicionX, posicionY, ancho, alto, escalaY
  gl = new Lata(400, 0, ancho, alto, 1000);
  //Configura puerto serie

  println(Serial.list());//Para localizar el numero de puerto
  // en mi caso el 32.
  myPort = new Serial(this, Serial.list()[32], 9600);
}

void draw() {

  while (myPort.available() > 0) {
    String lectura = myPort.readStringUntil(lf);
    background(255);
    if (lectura != null) { //Arduino envia Temperatura y altitud en una cadena.
      String lecturaT = lectura.substring(0, 5);
      String lecturaH = lectura.substring(5, lectura.length());//revisar si se reciben mas datos.
      temperatura = float(lecturaT);
      altitud = float(lecturaH);
      altitudgraf = map(altitud, 0, 1000, alto, 0);     
      gl.display(altitudgraf);
      gh.dibujaGrafica(altitud);
      gt.dibujaGrafica(temperatura);
      
      //envio de datos a la nube (dweet.io)
      loadStrings("https://dweet.io/dweet/for/canneduniverse?" + "Altitud" + "=" + lecturaH);
      // Para ver en internet: http://dweet.io/follow/canneduniverse
    }
  }
}
