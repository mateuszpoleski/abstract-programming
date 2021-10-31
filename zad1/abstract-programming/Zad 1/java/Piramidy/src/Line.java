public class Line extends Printable {
    private Point stop;

    public Line(Point start, Point stop) {
        super(start);
        this.stop = stop;
    }

    public void set_start(Point start) {
        super.set_position(start);
    }

    public void set_stop(Point new_stop) {
        stop = new_stop;
    }

    public boolean is_point() {
        return get_position().equal(stop);
    }

    public Point get_middle() {
        return new Point((get_position().add(stop)).div(2.f));
    }

    public void draw(Canvas canvas) {
        canvas.draw_line(get_position(), stop, get_color());
    }

    public void resize(float scale) {
        stop = get_position().add((stop.sub(get_position())).mul(scale));
    }

    public void move(Point vector) {
        stop = stop.add(vector);
        set_position(get_position().add(vector));
    }
}
