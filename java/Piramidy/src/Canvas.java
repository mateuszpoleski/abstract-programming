import java.awt.Dimension;
import java.awt.Graphics2D;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;

import javax.imageio.ImageIO;
import javax.swing.*;

public class Canvas {

    private LineDrawerPanel panel = new LineDrawerPanel();

    public void draw_line(int p1_x, int p1_y, int p2_x, int p2_y) {
        panel.addLine(new LineDrawer(p1_x, p1_y, p2_x, p2_y));
    }

    public void createAndShowGui() {
        JFrame frame = new JFrame("App");
        frame.setUndecorated(true);
        frame.setPreferredSize(new Dimension(400, 400));
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        frame.add(panel);
        frame.pack();
        frame.setLocationByPlatform(true);
        frame.setVisible(true);

        BufferedImage img = new BufferedImage(frame.getWidth(), frame.getHeight(), BufferedImage.TYPE_INT_RGB);
        Graphics2D g2d = img.createGraphics();
        frame.print(g2d);
        g2d.dispose();
        try {
            ImageIO.write(img, "png", new File("filename.png"));
        } catch (IOException log) {
            System.out.println(log);
        }

        frame.dispose();
    }
}