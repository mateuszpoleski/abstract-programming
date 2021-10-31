import java.awt.Dimension;
import java.awt.Graphics2D;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import java.awt.Color;

import javax.imageio.ImageIO;
import javax.swing.*;

public class Canvas {
    private int px_h;
    private float px_in_size_w;
    private float px_in_size_h;
    private JFrame frame;
    private LineDrawerPanel panel;

    public Canvas(int px_w, int px_h, float size_w, float size_h) {
        this.px_h = px_h;

        this.px_in_size_w = px_w / size_w;
        this.px_in_size_h = px_h / size_h;

        this.frame = new JFrame("Piramidy");
        frame.setUndecorated(true);
        frame.setPreferredSize(new Dimension(px_w, px_h));
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        this.panel = new LineDrawerPanel();
    }

    public void save(String path) {
        frame.pack();
        frame.add(panel);
        frame.setLocationByPlatform(true);
        frame.setVisible(true);

        BufferedImage img = new BufferedImage(frame.getWidth(), frame.getHeight(), BufferedImage.TYPE_INT_RGB);
        Graphics2D g2d = img.createGraphics();
        frame.print(g2d);
        g2d.dispose();

        try {
            ImageIO.write(img, "png", new File(path));
        } catch (IOException log) {
            System.out.println(log);
        }

        frame.dispose();

    }

    public int size_to_px_w(float size) {
        return Math.round(size * px_in_size_w);
    }

    public int size_to_px_h(float size) {
        return Math.round(size * px_in_size_h);
    }

    public int fix_h_coord(int h) {
        return px_h - h - 1;
    }

    public void draw_line(Point p1, Point p2, Color color) {
        float w1 = p1.get_x();
        float h1 = p1.get_y();
        float w2 = p2.get_x();
        float h2 = p2.get_y();

        int x1 = size_to_px_w(w1);
        int y1 = fix_h_coord(size_to_px_h(h1));
        int x2 = size_to_px_w(w2);
        int y2 = fix_h_coord(size_to_px_h(h2));

        panel.addLine(new LineDrawer(x1, y1, x2, y2, color));
    }
}