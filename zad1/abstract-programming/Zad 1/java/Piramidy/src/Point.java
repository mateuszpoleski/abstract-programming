public class Point {
    private float x;
    private float y;

    public Point(float x, float y) {
        this.x = x;
        this.y = y;
    }

    public Point(Point point) {
        this.x = point.x;
        this.y = point.y;
    }

    public float get_x() {
        return x;
    }

    public float get_y() {
        return y;
    }

    public boolean equal(Point p) {
        double eps = 1e-12;
        return Math.abs(this.x - p.x) < eps && Math.abs(this.y - p.y) < eps;
    }

    public Point add(Point p) {
        return new Point(this.x + p.x, this.y + p.y);
    }

    public Point sub(Point p) {
        return new Point(this.x - p.x, this.y - p.y);
    }

    public Point div(float scalar) {
        return new Point(this.x / scalar, this.y / scalar);
    }

    public Point mul(float scalar) {
        return new Point(this.x * scalar, this.y * scalar);
    }
}