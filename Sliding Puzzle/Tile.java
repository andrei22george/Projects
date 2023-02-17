import javax.swing.ImageIcon;
import javax.swing.JLabel;

public class Tile {
    private JLabel imageLabel;

    public Tile(ImageIcon image) {
        imageLabel = new JLabel(image);
    }

    public JLabel getImageLabel() {
        return imageLabel;
    }

    public void setImageLabel(JLabel imageLabel) {
        this.imageLabel = imageLabel;
    }

}
