import javax.swing.*;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;

public class ActionListener extends MouseAdapter
{
    private SlidingPuzzle puzzle;

    public ActionListener(SlidingPuzzle puzzle) {
        this.puzzle = puzzle;
    }

    @Override
    public void mouseClicked(MouseEvent event) {
        JLabel labelClicked = (JLabel)event.getSource();

        // daca tile-ul pe care am dat click nu este spatiul gol, muta tile-ul pe care am dat click
        // in locul liber de langa el
        if(labelClicked.getIcon() != null)
        {
            int pathLength = labelClicked.getIcon().toString().length();
            // pathLength este lungimea string-ului ce contine path-ul la imaginea din tile-ul
            // pe care s-a dat click
            // cum imaginile sunt denumite x.png, x intre 1 si 9, caracterul dinainte de . din pathLength
            // imi dau numarul imaginii, deci numarul tile-ului apasat
            // labelClicked.getIcon().toString() este path la locatia imaginii din tile-ul pe care
            // s-a dat click
            String number = labelClicked.getIcon().toString().substring(pathLength - 5, pathLength - 4);
            // fa slide al tile-ului cu numarul gasit din path-ul imaginii
            puzzle.slideTile(Integer.valueOf(number));
        }
    }


}
