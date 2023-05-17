import javax.swing.*;
import java.awt.*;

public class Potato extends JFrame {
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
        int xFirst = 10;
        int yFirst = 30;
        int xSecond = 60;
        int ySecond = 50;
        int xLast = 50;
        int yLast = 20;
        int dx = 0, dy = 0;
        int x0 = 0, y0 = 0, x1 = 0, y1 = 0;
        int gap = 10;

        for (int fs = 0; fs < 4; fs++) {

            for (int i = 0; i < 3; i++) {
                if (i == 0) {
                    dx = xSecond - xFirst;
                    dy = ySecond - yFirst;
                    x0 = xFirst;
                    y0 = yFirst;
                    x1 = xSecond;
                    y1 = ySecond;
                } else if (i == 1) {
                    dx = xLast - xSecond;
                    dy = yLast - ySecond;
                    x0 = xSecond;
                    y0 = ySecond;
                    x1 = xLast;
                    y1 = yLast;
                } else if (i == 2) {
                    dx = xFirst - xLast;
                    dy = yFirst - yLast;
                    x0 = xLast;
                    y0 = yLast;
                    x1 = xFirst;
                    y1 = yFirst;
                }
                int Pi = 2 * dy - dx;


                if (fs == 1) {
                    g.setColor(Color.BLUE);
                    int[][] array = {{1, 0, 0}, {0, 1, 0}, {30, 40, 1}};
                    int[] origin = {x0, y0, 1};
                    int[] origin2 = {x1, y1, 1};
                    int[] tmp = {0, 0, 0}, tmp2 = {0, 0, 0};
                    for (int ss = 0; ss < 3; ss++) {
                        for (int k = 0; k < 3; k++) {
                            tmp[ss] += origin[k] * array[k][ss];
                        }
                    }
                    for (int ss = 0; ss < 3; ss++) {
                        for (int k = 0; k < 3; k++) {
                            tmp2[ss] += origin2[k] * array[k][ss];
                        }
                    }
                    x0 = tmp[0];
                    y0 = tmp[1];
                    x1 = tmp2[0];
                    y1 = tmp2[1];
                    //g.setColor(Color.YELLOW);
                }

                if (fs == 2) {
                    g.setColor(Color.RED);
                    double[][] scalearr = {{0.5, 0, 0}, {0, 0.5, 0}, {(1 - 0.5) * xLast, (1 - 0.5) * yLast, 1}};
                    int[] origin = {x0, y0, 1};
                    int[] origin2 = {x1, y1, 1};
                    int[] tmp = {0, 0, 0}, tmp2 = {0, 0, 0};
                    for (int ss = 0; ss < 3; ss++) {
                        for (int k = 0; k < 3; k++) {
                            tmp[ss] += origin[k] * scalearr[k][ss];
                        }
                    }
                    for (int ss = 0; ss < 3; ss++) {
                        for (int k = 0; k < 3; k++) {
                            tmp2[ss] += origin2[k] * scalearr[k][ss];
                        }
                    }
                    x0 = tmp[0] - 20;
                    y0 = tmp[1] + 30;
                    x1 = tmp2[0] - 20;
                    y1 = tmp2[1] + 30;
                    //g.setColor(Color.BLUE);
                }

                if (fs == 3) {
                    g.setColor(Color.GREEN);
                    int cosA = 0;
                    int sinA = 1;
                    int cx = (xFirst + xSecond + xLast) / 3;
                    int cy = (yFirst + ySecond + yLast) / 3;
                    double[][] rotatearr = {{cosA, sinA, 0}, {-sinA, cosA, 0}, {(1 - cosA) * cx + (cy * sinA), (1 - cosA) * cy - (cx * sinA), 1}};
                    int[] origin = {x0, y0, 1};
                    int[] origin2 = {x1, y1, 1};
                    int[] tmp = {0, 0, 0}, tmp2 = {0, 0, 0};
                    for (int ss = 0; ss < 3; ss++) {
                        for (int k = 0; k < 3; k++) {
                            tmp[ss] += origin[k] * rotatearr[k][ss];
                        }
                    }
                    for (int ss = 0; ss < 3; ss++) {
                        for (int k = 0; k < 3; k++) {
                            tmp2[ss] += origin2[k] * rotatearr[k][ss];
                        }
                    }
                    x0 = tmp[0] + 50;
                    y0 = tmp[1] + 5;
                    x1 = tmp2[0] + 50;
                    y1 = tmp2[1] + 5;
                    dx = x1 - x0;
                    dy = y1 - y0;
                    if(i == 0) {
                        System.out.println("x0 : " + x0);
                        System.out.println("y0 : " + y0);
                        System.out.println("x1 : " + x1);
                        System.out.println("y1 : " + y1);
                        System.out.println("dx : " + dx);
                        System.out.println("dy : " + dy);
                        System.out.println("시발감자련아");
                    }
                }

                g.drawRect(x0 * gap, y0 * gap, gap, gap);

                if (dx > 0 && dy > 0) {
                    for (int x = x0; x < x1; x++) {
                        if (Pi < 0) {
                            Pi += 2 * dy;
                            x0 += 1;
                        } else {
                            Pi += 2 * dy - 2 * dx;
                            x0 += 1;
                            y0 += 1;
                        }
                        g.drawRect(x0 * gap, y0 * gap, gap, gap);
                    }
                } else if (dx < 0 && dy < 0) {
                    Pi = 2 * dx - dy;
                    if(fs == 3) {
                        y0 += 3;
                        x0 += 1;
                    }
                    for (int y = y0-1; y > y1; y--) {
                        if (Pi < 0) {
                            Pi -= 2 * dx;
                            y0 -= 1;
                        } else {
                            Pi -= 2 * dx - 2 * dy;
                            x0 -= 1;
                            y0 -= 1;
                        }
                        g.drawRect(x0 * gap, y0 * gap, gap, gap);
                    }
                } else if (dx < 0 && dy > 0) {
                    if(fs == 3 && i == 0) {
                        Pi = 2 * dy - dx;
                        for (int y = y0; y < y1; y++) {
                            if (Pi < 0) {
                                Pi += 2 * dy;
                                y0 += 1;
                            } else {
                                Pi -= 2 * dy - 2 * dx;
                                y0 += 1;
                                x0 -= 1;
                            }
                            g.drawRect(x0 * gap, y0 * gap, gap, gap);
                        }
                    }
                    else {
                        Pi = 2 * dy - dx;
                        for (int x = x0; x > x1; x--) {
                            if (Pi < 0) {
                                Pi += 2 * dy;
                                x0 -= 1;
                            } else {
                                Pi -= 2 * dy - 2 * dx;
                                y0 += 1;
                                x0 -= 1;
                            }
                            g.drawRect(x0 * gap, y0 * gap, gap, gap);
                        }
                        g.drawRect((x0) * gap, (y0+1) * gap, gap, gap);
                    }
                }
                else {
                    for (int x = x0; x < x1; x++) {
                        if (Pi < 0) {
                            Pi -= 2 * dy;
                            x0 += 1;
                        } else {
                            Pi += 2 * dy - 2 * dx;
                            y0 -= 1;
                            x0 += 1;
                        }
                        g.drawRect(x0 * gap, (y0) * gap, gap, gap);
                    }
                    g.drawRect(x0 * gap, (y0-1) * gap, gap, gap);
                }
            }
        }
    }
}