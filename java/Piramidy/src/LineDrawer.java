import java.awt.Graphics;

class LineDrawer {

    private int p1_x;
    private int p1_y;
    private int p2_x;
    private int p2_y;

    public LineDrawer(int _p1_x, int _p1_y, int _p2_x, int _p2_y) {
        p1_x = _p1_x;
        p1_y = _p1_y;
        p2_x = _p2_x;
        p2_y = _p2_y;
    }

    public void draw(Graphics g) {
        // g.setColor(Color.RED);
        g.drawLine(p1_x, p1_y, p2_x, p2_y);
    }
}