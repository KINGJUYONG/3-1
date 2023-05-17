import javax.swing.*;
import java.awt.*;

public class Potato extends JFrame{
Graphics2D g2d;
public static void main(String[] args) {
Potato po = new Potato();
}
public int Windowsize = 1100;
public Potato() {
setSize(Windowsize, Windowsize);
setVisible(true);
}

public void paint(Graphics g) {
Graphics2D g2d = (Graphics2D) g;
int xFirst = 0;
int yFirst = 5;
int x0 = xFirst;
int y0 = yFirst;
int gap = 10;
int r = yFirst;

int Pi = 1 - r ;


int padding = 30;

g2d.drawRect((x0+padding)*gap, (y0+padding) * gap, gap, gap);
g2d.drawRect((-x0+padding)*gap, (y0+padding) * gap, gap, gap);
g2d.drawRect((x0+padding)*gap, (-y0+padding) * gap, gap, gap);
g2d.drawRect((-x0+padding)*gap, (-y0+padding) * gap, gap, gap);
g2d.drawRect((y0+padding)*gap, (x0+padding) * gap, gap, gap);
g2d.drawRect((-y0+padding)*gap, (x0+padding) * gap, gap, gap);
g2d.drawRect((y0+padding)*gap, (-x0+padding) * gap, gap, gap);
g2d.drawRect((-y0+padding)*gap, (-x0+padding) * gap, gap, gap);



for(int i = 0;i < r-1; i++) {
x0 += 1;
if(Pi < 0){
int CD = 2 * x0 + 1;
Pi = Pi+ CD;


}
else if (Pi >= 0) {
y0 -= 1;
int AB = (2 * x0) + 1 - (2 * y0);
Pi += AB;
}

g2d.drawRect((x0+padding) * gap, (y0+padding) * gap, gap, gap);
g2d.drawRect((x0+padding) * gap, (-y0+padding) * gap, gap, gap);
g2d.drawRect((-x0+padding) * gap, (y0+padding) * gap, gap, gap);
g2d.drawRect((-x0+padding) * gap, (-y0+padding) * gap, gap, gap);

g2d.drawRect((y0+padding) * gap, (x0+padding) * gap, gap, gap);
g2d.drawRect((-y0+padding) * gap, (x0+padding) * gap, gap, gap);
g2d.drawRect((y0+padding) * gap, (-x0+padding) * gap, gap, gap);
g2d.drawRect((-y0+padding) * gap, (-x0+padding) * gap, gap, gap);


System.out.println(y0);








}



xFirst = 0;
yFirst = 10;
x0 = xFirst;
y0 = yFirst;
gap = 10;
r = yFirst;

Pi = 1 - r ;

padding = 70;

g2d.drawRect((x0+padding)*gap, (y0+padding) * gap, gap, gap);
g2d.drawRect((-x0+padding)*gap, (y0+padding) * gap, gap, gap);
g2d.drawRect((x0+padding)*gap, (-y0+padding) * gap, gap, gap);
g2d.drawRect((-x0+padding)*gap, (-y0+padding) * gap, gap, gap);
g2d.drawRect((y0+padding)*gap, (x0+padding) * gap, gap, gap);
g2d.drawRect((-y0+padding)*gap, (x0+padding) * gap, gap, gap);
g2d.drawRect((y0+padding)*gap, (-x0+padding) * gap, gap, gap);
g2d.drawRect((-y0+padding)*gap, (-x0+padding) * gap, gap, gap);



for(int i = 0;i < r-1; i++) {
x0 += 1;
if(Pi < 0){
int CD = 2 * x0 + 1;
Pi = Pi+ CD;


}
else if (Pi >= 0) {
y0 -= 1;
int AB = (2 * x0) + 1 - (2 * y0);
Pi += AB;
}

g2d.drawRect((x0+padding) * gap, (y0+padding) * gap, gap, gap);
g2d.drawRect((x0+padding) * gap, (-y0+padding) * gap, gap, gap);
g2d.drawRect((-x0+padding) * gap, (y0+padding) * gap, gap, gap);
g2d.drawRect((-x0+padding) * gap, (-y0+padding) * gap, gap, gap);

g2d.drawRect((y0+padding) * gap, (x0+padding) * gap, gap, gap);
g2d.drawRect((-y0+padding) * gap, (x0+padding) * gap, gap, gap);
g2d.drawRect((y0+padding) * gap, (-x0+padding) * gap, gap, gap);
g2d.drawRect((-y0+padding) * gap, (-x0+padding) * gap, gap, gap);


System.out.println(y0);








}





}

private int negative(int y) {
return -400 + Windowsize - y;
}
}