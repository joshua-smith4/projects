package Simonish.game;
import java.awt.Color;
import java.awt.Container;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.util.Vector;
import java.util.Random;
import javax.swing.JOptionPane;
import javax.swing.JButton;
import javax.swing.JFrame;

import Simonish.components.*;

/**
 * Class containing the game's main frame and functionality instructions
 * @author JoshuaSmith
 *@version cs2410-2.1
 */
public class Game{
	/**
	 * Random: Random number generator
	 */
	Random randGen;
	JFrame frame;
	Container pane;
	SPanel yellow, green, blue, red;
	ScoreBoard scorePanel;
	ClickManager listener = new ClickManager();
	public static int height=700;
	public static int width=800;
	/**
	 * private Vector<SPanel>: record of past game movements
	 */
	private Vector<SPanel> memoryVec;
	/**
	 * private Vector: record of past user movements (temporary)
	 */
	private Vector<SPanel> inputVec;
	
	/**
	 * Constructor that initializes all the parts of the Simonish game
	 */
	public Game(){
		memoryVec = new Vector<SPanel>();
		inputVec = new Vector<SPanel>();
		
		randGen = new Random();
		frame = new JFrame("Simonish");
		frame.setSize(width,height);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setResizable(false);
		pane = frame.getContentPane();
		yellow = new SPanel(Color.YELLOW.darker());
		green = new SPanel(Color.GREEN.darker());
		blue = new SPanel(Color.BLUE.darker());
		red = new SPanel(Color.RED.darker());
		scorePanel = new ScoreBoard();
		
		scorePanel.getStartBtn().addActionListener(listener);
		
		pane.setLayout(null);
		pane.add(yellow);
		pane.add(green);
		pane.add(blue);
		pane.add(red);
		pane.add(scorePanel);
		
		
		frame.setVisible(true);
		
		yellow.setBounds(width/2-(SPanel.width+10),height/2-(SPanel.height+10),SPanel.width,SPanel.height);
		yellow.setBackground(yellow.getColor());
		yellow.addMouseListener(listener);
		
		green.setBounds(width/2+10,height/2-(SPanel.height+10),SPanel.width,SPanel.height);
		green.setBackground(green.getColor());
		green.addMouseListener(listener);

		blue.setBounds(width/2-(SPanel.width+10),height/2+10,SPanel.width,SPanel.height);
		blue.setBackground(blue.getColor());
		blue.addMouseListener(listener);

		red.setBounds(width/2+10,height/2+10,SPanel.width,SPanel.height);
		red.setBackground(red.getColor());
		red.addMouseListener(listener);
		
		setBtnsVis(true);
		
		scorePanel.setVisible(true);
	}
	
	/**
	 * Manages the actions of all the buttons and panels of the game
	 * @author JoshuaSmith
	 *
	 */
	class ClickManager implements MouseListener, ActionListener{

		@Override
		public void mouseClicked(MouseEvent e) {			
		}

		@Override
		public void mousePressed(MouseEvent e) {
			if(memoryVec.size()!=0){
				((SPanel)e.getSource()).setBackground(((SPanel)e.getSource()).getBackground().brighter());
				((SPanel)e.getSource()).update(((SPanel)e.getSource()).getGraphics());
			}
		}

		@Override
		public void mouseReleased(MouseEvent e) {
			if(memoryVec.size()!=0){
				((SPanel)e.getSource()).setBackground(((SPanel)e.getSource()).getBackground().darker());
				((SPanel)e.getSource()).update(((SPanel)e.getSource()).getGraphics());
				inputVec.add(((SPanel)e.getSource()));
				for(int i=0;i<inputVec.size();++i){
					if(memoryVec.get(i)!=inputVec.get(i)) endGame();
					if(i+1==memoryVec.size()){
						addRandBtn();
						scorePanel.incCurScore();
						scorePanel.updateCurScoreLab();
						inputVec.removeAllElements();
						blinkVec();
					}
				}
			}
		}

		@Override
		public void mouseEntered(MouseEvent e) {			
		}

		@Override
		public void mouseExited(MouseEvent e) {			
		}

		@Override
		public void actionPerformed(ActionEvent e) {
			if((JButton)e.getSource()==scorePanel.getStartBtn()){
				newGame();
			}
		}
		
	}
	
	/**
	 * Begins a new game
	 */
	public void newGame(){
		reset();
		addRandBtn();
		blinkVec();
	}
	
	/**
	 * Sets the visibility of each SPanel (yellow, red, green, blue) to the value of the parameter y
	 * @param y boolean input for visibility
	 */
	public void setBtnsVis(boolean y){
		yellow.setVisible(y);
		green.setVisible(y);
		blue.setVisible(y);
		red.setVisible(y);
	}
	
	/**
	 * resets all the values and labels of the game
	 */
	public void reset(){
		memoryVec.removeAllElements();
		inputVec.removeAllElements();
		scorePanel.resetCurScore();
		scorePanel.updateCurScoreLab();
	}
	
	/**
	 * Adds another random move to the game by loading it into the Vector memoryVec
	 */
	public void addRandBtn(){
		int x = randGen.nextInt(4)+1;
		switch (x){
		case 1: memoryVec.addElement(yellow);
				break;
		case 2: memoryVec.addElement(green);
				break;
		case 3: memoryVec.addElement(blue);
				break;
		case 4: memoryVec.addElement(red);
				break;
		}
	}
	
	/**
	 * Instructions to the computer on how to blink the correct SPanels 
	 */
	public void blinkVec(){
		for(SPanel i: memoryVec){
			i.blink();
		}
	}
	
	/**
	 * End game message and reset managed here
	 */
	public void endGame(){
		String rank = null;
		String achieved = "";
		if(scorePanel.getCurScore()>scorePanel.getHighScore()) {
			scorePanel.setHighScore(scorePanel.getCurScore());
			scorePanel.updateHighScoreLab();
			achieved = "You beat your high score!";
		}else if(scorePanel.getCurScore()==scorePanel.getHighScore() && scorePanel.getHighScore()!=0) achieved = "You met your high score!";
		if(scorePanel.getCurScore()<=3) rank = "House Cat";
		if(scorePanel.getCurScore()<=7 && scorePanel.getCurScore()>3) rank = "Bobcat";
		if(scorePanel.getCurScore()>7) rank = "Lion";
		JOptionPane.showMessageDialog(null,"You scored: " + scorePanel.getCurScore() +
				"\nYour rank is: " + rank + "\n" + achieved
				,"Nice Memory!",JOptionPane.INFORMATION_MESSAGE);
		reset();
	}
	
	public static void main(String[] args){
		new Game();
	}
	
}
