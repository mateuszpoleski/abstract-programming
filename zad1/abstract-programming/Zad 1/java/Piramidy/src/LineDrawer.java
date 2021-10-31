import java.awt.Color;
import java.awt.Graphics;

class LineDrawer {

    private int p1_x;
    private int p1_y;
    private int p2_x;
    private int p2_y;
    private Color color;

    public LineDrawer(int p1_x, int p1_y, int p2_x, int p2_y, Color color) {
        this.p1_x = p1_x;
        this.p1_y = p1_y;
        this.p2_x = p2_x;
        this.p2_y = p2_y;
        this.color = color;
    }

    public void draw(Graphics g) {
        g.setColor(color);
        g.drawLine(p1_x, p1_y, p2_x, p2_y);
    }
}