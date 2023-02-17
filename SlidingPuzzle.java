import javax.swing.*;
import javax.swing.border.EmptyBorder;
import java.awt.*;
import java.util.ArrayList;
import java.util.Random;

public class SlidingPuzzle extends JFrame {

    private ArrayList<Integer> puzzleBoard = new ArrayList<Integer>(9);
    private Tile[] tiles = new Tile[9];
    private int[] correctPosition = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    private JPanel panel;
    private int counter = 0;

    public SlidingPuzzle() {
        super();
        newRandomPuzzle();
        createPuzzleInterface();
    }

    // verifica daca configuratia generata a sirului de 3 x 3 este rezolvabila
    private boolean isSolvable() {
        int inversionsCounter = 0;

        for(int current : puzzleBoard)
            for(int i = puzzleBoard.indexOf(current); i < puzzleBoard.size(); i++)
                if(current > puzzleBoard.get(i) && current != 8 && puzzleBoard.get(i) != 8)
                    inversionsCounter++;

        return inversionsCounter % 2 == 0;
    }

    // genereaza un puzzle nou amestecat si verifica daca este rezolvabil
    private void newRandomPuzzle() {
        do
        {
            puzzleBoard.clear();

            while(puzzleBoard.size() < correctPosition.length)
            {
                Random random = new Random();
                int number = random.nextInt(9);
                if(!puzzleBoard.contains(number))
                    puzzleBoard.add(number);
            }
        } while (!isSolvable());
    }

    // pune tile-urile cu imagini pe board
    private void showTileOnBoard() {
        panel.removeAll();
        for(int tilePosition : puzzleBoard)
            panel.add(tiles[tilePosition].getImageLabel());
    }

    // verifica daca puzzle-ul a fost sau nu rezolvat
    private boolean puzzleSolved() {
        boolean solved = true;

        for(int i = 0; i < puzzleBoard.size(); i++)
            if(correctPosition[i] != puzzleBoard.get(i))
                solved = false;

        return solved;
    }

    // creeaza intergata puzzle-ului
    private void createPuzzleInterface() {
        panel = new JPanel();

        this.setLocation(950, 200);
        this.setIconImage(new ImageIcon(getClass().getResource("icon.png")).getImage());
        this.setContentPane(panel);
        this.setResizable(false);
        this.setTitle("Sliding Puzzle 3 x 3");
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        panel.setBackground(Color.BLACK);
        panel.setPreferredSize(new Dimension(630, 630));
        panel.setBorder(new EmptyBorder(15, 15, 15, 15));
        panel.setLayout(new GridLayout(3, 3));

        for(int i = 0; i < puzzleBoard.size(); i++)
        {
            if(i == 8)
                tiles[i] = new Tile(null);
            else
                tiles[i] = new Tile(new ImageIcon(getClass().getResource((i + 1) + ".png")));

            tiles[i].getImageLabel().addMouseListener(new ActionListener(this));
        }

        showTileOnBoard();
        this.pack();
        this.setVisible(true);
    }

    // functie care slide-uieste efectiv tile-ul pe tabla de joc
    public void slideTile(int number) {
        int tilePosition = puzzleBoard.indexOf(number - 1);
        int[] tileNeighbours;

        if(tilePosition == 0 || tilePosition == 3 || tilePosition == 6)
            tileNeighbours = new int[] {tilePosition - 3, tilePosition + 1, tilePosition + 3};
        else if(tilePosition == 2 || tilePosition == 5 || tilePosition == 8)
            tileNeighbours = new int[] {tilePosition - 3, tilePosition - 1, tilePosition + 3};
        else
            tileNeighbours = new int[] {tilePosition - 3, tilePosition - 1, tilePosition + 1, tilePosition + 3};

        //for(int i = 0; i < tileNeighbours.length; i++)
            //System.out.print(tileNeighbours[i] + " ");
        //System.out.println();

        for(int i : tileNeighbours)
            if(i >= 0 && i <= 8 && puzzleBoard.get(i) == 8)
            {
                puzzleBoard.set(i, puzzleBoard.get(tilePosition));
                puzzleBoard.set(tilePosition, 8);
                counter++;
            }

        createPuzzleInterface();

        // daca puzzle-ul a fost rezolvat, incepe joc nou sau iesi
        if(puzzleSolved() == true)
        {
            String[] options = {"Joc nou", "Exit"};
            int selection = JOptionPane.showOptionDialog(null, "Ai castigat!\nNumarul de mutari: " + counter, "Sliding Puzzle 3 x 3", 0, 1, null, options,
                    options[0]);

            if(selection == 1) // daca s-a apasat butonul de exit, inchide aplicatia
                System.exit(0);
            else if(selection == 0) // daca s-a apasat butonul de new game, deschide un puzzle nou
            {
                newRandomPuzzle();
                createPuzzleInterface();
            }
        }
    }

}
