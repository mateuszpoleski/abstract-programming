// // public class Piramidy {
// //     public static void main(String[] args) {
// //         System.out.println("test");
// //     }
// // }
// //package org.kodejava.example.geom;

// // Java program to draw a line in Applet

import java.awt.*;
import javax.swing.*;
import java.awt.geom.Line2D;
import java.awt.image.BufferedImage;
import javax.imageio.ImageIO;
import java.io.File;
import java.io.IOException;

class MyCanvas extends JComponent {

    public void paint(Graphics g) {

        // draw and display the line
        g.setColor(Color.RED);
        g.drawLine(30, 20, 80, 90);
    }
}

public class Piramidy {
    public static void main(String[] a) {

        // creating object of JFrame(Window popup)
        JFrame window = new JFrame();

        // setting closing operation
        window.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        // setting size of the pop window
        window.setBounds(30, 30, 200, 200);

        // setting canvas for draw
        window.getContentPane().add(new MyCanvas());

        // set visibility
        // window.setVisible(true);

        BufferedImage img = new BufferedImage(window.getWidth(), window.getHeight(), BufferedImage.TYPE_INT_RGB);
        // window.paint(img.getGraphics());
        Graphics2D g2d = img.createGraphics();
        window.printAll(g2d);
        g2d.dispose();

        try {
            paint(g2d);
            ImageIO.write(img, "png", new File("2.png"));
            System.out.println("Succes");
        } catch (IOException exception) {
            System.out.println(exception);
        }
    }
}

// import java.awt.Graphics;
// import java.awt.Graphics2D;
// import java.awt.geom.Line2D;

// import javax.swing.JFrame;
// import javax.swing.SwingUtilities;

// public class Piramidy extends JFrame {

// public Piramidy() {
// super("Lines Drawing Demo");

// setSize(480, 200);
// setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
// setLocationRelativeTo(null);
// }

// void drawLines(Graphics g) {
// Graphics2D g2d = (Graphics2D) g;

// g2d.drawLine(120, 50, 360, 50);

// g2d.draw(new Line2D.Double(59.2d, 99.8d, 419.1d, 99.8d));

// g2d.draw(new Line2D.Float(21.50f, 132.50f, 459.50f, 132.50f));

// }

// public void paint(Graphics g) {
// super.paint(g);
// drawLines(g);
// }

// public static void main(String[] args) {
// SwingUtilities.invokeLater(new Runnable() {
// @Override
// public void run() {
// new Piramidy().setVisible(true);
// }
// });
// }
// }