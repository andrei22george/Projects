package application;
	
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.stage.Stage;
import javafx.scene.Group;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.input.KeyCombination;
import javafx.scene.layout.BorderPane;
import javafx.scene.paint.Color;
import javafx.scene.text.Font;
import javafx.scene.text.Text;


public class Main extends Application {
	
	public static void main(String[] args) {
		launch(args);
	}

	@Override
	public void start(Stage stage) throws Exception {
		// TODO Auto-generated method stub
		
		try {
			
			Parent root = FXMLLoader.load(getClass().getResource("Main.fxml"));
			//FXMLLoader loader = new FXMLLoader(getClass().getResource("Main.fxml"));
			//Controller controller = loader.getController();
			//Stage stage = new Stage();
			// add root node to scene, add scene to stage, show stage
			//Group root = new Group();
			Scene scene = new Scene(root, 1440, 900, Color.BROWN);
			Image icon = new Image("dke2.png");
			stage.getIcons().add(icon);
			stage.setTitle("Delta Kappa Epsilon Platform");
			stage.setWidth(1440);
			stage.setHeight(900);
			stage.setResizable(false);
			
			// app start position on screen
			//stage.setX(50);
			//stage.setY(50);
			
			// fullscreen start; standard exit key esc; custom exit key q
			//stage.setFullScreen(true);
			//stage.setFullScreenExitHint("YOU CAN'T ESCAPE UNLESS YOU PRESS Q");
			//stage.setFullScreenExitKeyCombination(KeyCombination.valueOf("q"));
			
			//Text text = new Text();
			//text.setText("WELCOME!");
			//text.setX(50);
			//text.setY(50);
			//text.setFont(Font.font("Verdana", 50));
			//text.setFill(Color.BLACK);
			//root.getChildren().add(text);
			
			//Image image = new Image("frat1.png", 600, 258, false, false);
			//ImageView imageView = new ImageView(image);
			//imageView.setX(50);
			//imageView.setY(100);
			
			//root.getChildren().add(imageView);
			
			stage.setScene(scene);
			stage.show();
		} catch(Exception e) {
			e.printStackTrace();
		}		
		
	}
}
