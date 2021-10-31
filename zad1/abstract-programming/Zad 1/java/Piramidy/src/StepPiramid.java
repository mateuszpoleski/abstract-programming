import java.awt.Color;

public class StepPiramid extends SymetricPiramid {

    private int step_num;

    public StepPiramid(float x, float y, float base, float height, int step_num) {
        super(x, y, base, height);
        this.step_num = step_num;
    }

    public void draw(Canvas canvas) {
        float step_height = get_height() / step_num;
        float step_width = get_base_width() / (2 * step_num);
        // base
        Color color = get_color();
        Point a = get_position();
        Point b = get_position().add(new Point(get_base_width(), 0));
        canvas.draw_line(a, b, color);

        // sides
        Point curr_left = get_position().add(new Point(step_width / 2.f, 0));
        Point curr_right = curr_left.add(new Point(step_width * (2 * step_num - 1), 0));
        Point step_left = new Point(step_width, step_height);
        Point step_right = new Point(-step_width, step_height);
        Point next_left = curr_left.add(step_left);
        Point next_right = curr_right.add(step_right);

        for (int i = 0; i < step_num; i++) {
            Point vertex_left = new Point(curr_left.get_x(), next_left.get_y());
            Point vertex_right = new Point(curr_right.get_x(), next_right.get_y());

            canvas.draw_line(curr_left, vertex_left, color);
            canvas.draw_line(vertex_left, next_left, color);

            canvas.draw_line(curr_right, vertex_right, color);
            canvas.draw_line(vertex_right, next_right, color);

            curr_left = next_left;
            curr_right = next_right;
            next_left = next_left.add(step_left);
            next_right = next_right.add(step_right);
        }
    }
}
