import java.awt.Color;

public class EquilateralPiramid extends Piramid {
    public EquilateralPiramid(float x, float y, float base) {
        super(x, y, base);
    }

    public float get_height() {
        return (float) (get_base_width() * Math.sqrt(3.f) / 2.f);
    }

    public void draw(Canvas canvas) {
        Color color = get_color();
        Point a = get_position();
        Point b = get_position().add(new Point(get_base_width(), 0));
        Point c = new Point(((a.add(b)).div(2.f)).get_x(), get_height() + get_position().get_y());
        canvas.draw_line(a, b, color);
        canvas.draw_line(b, c, color);
        canvas.draw_line(a, c, color);
    }
}
