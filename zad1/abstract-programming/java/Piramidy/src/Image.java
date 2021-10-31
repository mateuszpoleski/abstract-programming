import java.util.ArrayList;
import java.util.List;

public class Image {
    private List<Printable> printables;

    public Image() {
        printables = new ArrayList<Printable>();
    }

    public void add(Printable printable) {
        printables.add(printable);
    }

    void resize(float scale) {
        for (Printable printable : printables) {
            printable.resize(scale);
        }
    }

    void draw(Canvas canvas) {
        for (Printable printable : printables) {
            printable.draw(canvas);
        }
    }

    void move(Point vector) {
        for (Printable printable : printables) {
            printable.move(vector);
        }
    }
}
