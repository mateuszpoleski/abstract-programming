import java.awt.Color;

//Klasa gromadząca obiekty które można rysować, np. piramidy, linie
public abstract class Printable {
    private Point position;
    private Color color;

    public Printable(Point position) {
        this.position = position;
        this.color = new Color(0, 0, 0);
    }

    public void set_color(int r, int g, int b) {
        color = new Color(r, g, b);
    }

    public Color get_color() {
        return color;
    }

    public void set_position(Point new_position) {
        position = new_position;
    }

    public Point get_position() {
        return position;
    }

    public abstract void draw(Canvas canvas);

    public abstract void resize(float scale);

    public abstract void move(Point vector);
}