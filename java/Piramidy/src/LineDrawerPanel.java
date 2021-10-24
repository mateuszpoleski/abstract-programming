import javax.swing.JPanel;
import java.awt.Graphics;
import java.util.ArrayList;
import java.util.List;

public class LineDrawerPanel extends JPanel {
    List<LineDrawer> lines;

    public LineDrawerPanel() {
        lines = new ArrayList<LineDrawer>();
    }

    public void addLine(LineDrawer line) {
        lines.add(line);
    }

    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);
        for (LineDrawer line : lines) {
            line.draw(g);
        }
    }
}