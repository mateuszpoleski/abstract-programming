public class App {
    public static void main(String[] args) {
        Canvas canvas = new Canvas();
        canvas.draw_line(100, 300, 200, 100);
        canvas.draw_line(200, 100, 300, 300);
        canvas.draw_line(300, 300, 100, 300);
        canvas.draw_line(200, 100, 200, 50);
        canvas.draw_line(200, 300, 200, 350);
        canvas.draw_line(0, 400, 50, 350);
        canvas.draw_line(0, 0, 50, 50);
        canvas.draw_line(400, 400, 350, 350);
        canvas.draw_line(400, 0, 350, 50);
        canvas.createAndShowGui();
    }
}