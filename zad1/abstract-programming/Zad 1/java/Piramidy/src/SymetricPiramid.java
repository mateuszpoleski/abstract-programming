import java.awt.Color;

public class SymetricPiramid extends Piramid {
    private float height;

    public SymetricPiramid(float x, float y, float base, float height) {
        super(x, y, base);
        this.height = height;
    }

    public void set_height(float new_height) {
        height = new_height;
    }

    public float get_height() {
        return height;
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

    public void resize(float scale) {
        super.resize(scale);
        height *= scale;
    }
}
