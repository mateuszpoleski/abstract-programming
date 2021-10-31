public class Piramidy {
    public static void main(String[] args) {
        Canvas canvas = new Canvas(200, 200, 10.f, 10.f);
        float base_1 = 10.f;
        float base_2 = 6.f;
        StepPiramid p1 = new StepPiramid(0.f, 0.f, base_2, 5.f, 10);
        SymetricPiramid p2 = new SymetricPiramid(base_2, 0, base_1 - base_2, 5);
        EquilateralPiramid p3 = new EquilateralPiramid(0, 0, base_1);
        p1.set_color(255, 191, 64);
        p2.set_color(255, 223, 64);
        p3.set_color(255, 255, 64);
        // Line l1 = new Line(new Point(0, 0), new Point(5, 5));
        Image img = new Image();
        // img.add(l1);
        img.add(p3);
        img.add(p2);
        img.add(p1);
        // img.resize(0.5f);
        // img.move(new Point(1, 1));
        img.draw(canvas);
        // System.out.println(p1.get_area());
        // System.out.println(p2.get_area());
        // System.out.println(p3.get_area());
        canvas.save("piramids.png");

    }
}