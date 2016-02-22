package Simonish.components;

import java.awt.GridLayout;

import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.SwingConstants;

import Simonish.game.Game;

public class ScoreBoard extends JPanel {
	private static int highScore;
	private static int curScore;
	private JButton startBtn;
	private JLabel curScoreLabel;
	private JLabel highScoreLabel;
	
	public ScoreBoard(){
		curScore = 0;
		highScore = 0;
		startBtn = new JButton("New Game");
		curScoreLabel = new JLabel("Current Score: " + curScore, SwingConstants.CENTER);
		highScoreLabel = new JLabel("High Score: " + highScore, SwingConstants.CENTER);
		
		this.setLayout(new GridLayout(1,3));
		
		setBounds(Game.width/2-250,50,500,75);
		
		add(curScoreLabel);
		add(startBtn);
		add(highScoreLabel);
	}
	
	public int incCurScore(){
		return curScore+=1;
	}
	
	public int getCurScore(){
		return curScore;
	}
	
	public int getHighScore(){
		return highScore;
	}
	
	public void setHighScore(int highScore){
		ScoreBoard.highScore = highScore;
	}
	
	public void resetCurScore(){
		curScore = 0;
	}
	
	public JButton getStartBtn(){
		return startBtn;
	}
	
	public void updateCurScoreLab(){
		curScoreLabel.setText("Current Score: " + curScore);
	}
	
	public void updateHighScoreLab(){
		highScoreLabel.setText("High Score: " + highScore);
	}

}
