public abstract class Piramid extends Printable {
    private float base_width;

    public Piramid(float x, float y, float base) {
        super(new Point(x, y));
        this.base_width = base;
    }

    public void set_base_width(float new_base_width) {
        base_width = new_base_width;
    }

    public float get_base_width() {
        return base_width;
    }

    public void move(Point vector) {

        set_position(get_position().add(vector));
    }

    public float get_area() {
        // Okazuje się, że wzór jest poprawny nawet dla piramidy schodkowej.
        return base_width * get_height() / 2.f;
    }

    public void resize(float scale) {
        base_width *= scale;
    }

    public abstract float get_height();
}
