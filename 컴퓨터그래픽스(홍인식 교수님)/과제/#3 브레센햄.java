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
        int xFirst = 5;
        int yFirst = 5;
        int xLast = 70;
        int yLast = 35;
        int deltaX = xLast-xFirst;
        int deltaY = yLast-yFirst;
        int x0 = xFirst;
        double y0 = yFirst;
        int x1 = xFirst;
        double y1 = yFirst;
        double m = deltaY / (double) deltaX;
        int gap = 10;

        int AB = 2 * (deltaY - deltaX);
        int CD = 2 * deltaY;
        int Pi = 2 * deltaY - deltaX ;


        int drawY = negative((int) Math.round(y0) * gap);
        g2d.drawRect(x0, drawY, gap, gap);


        for(int i = 0;i < deltaX; i++) {
            if(Pi < 0){
                Pi += CD;

                x0 += gap;
                drawY = negative((int) Math.round(y0) * gap);
                g2d.setColor(Color.BLACK);
                g2d.drawRect(x0, drawY, gap, gap);
            }
            else if (Pi >= 0) {
                Pi += AB;

                x0 += gap;
                y0 += 1;
                drawY = negative((int) Math.round(y0) * gap);
                g2d.setColor(Color.BLACK);
                g2d.drawRect(x0, drawY, gap, gap);
            }

            x1 += gap;
            y1 += m;

            int drawYY = negative((int) Math.round(y1) * gap);
            g2d.setColor(Color.RED);
            g2d.drawRect(x1, drawYY - 100, gap, gap);
        }
    }

    private int negative(int y) {
        return -100 + Windowsize - y;
    }
}