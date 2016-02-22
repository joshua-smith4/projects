package Minesweeperish.gamecomponent;

import java.awt.BorderLayout;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.SwingConstants;
import javax.swing.Timer;

public class ScoreBoard extends JPanel {
	private int totalBombs;
	private int timeLapsed;
	private JLabel bombLabel;
	private JLabel timerLabel;
	private JButton resetBtn;
	
	public ScoreBoard(int bombsCnt) {
		totalBombs = bombsCnt;
		timeLapsed = 0;
		bombLabel = new JLabel("Bombs Left: " + Integer.toString(totalBombs), SwingConstants.CENTER);
		timerLabel = new JLabel("Time: " + timeLapsed + " seconds", SwingConstants.CENTER);
		resetBtn = new JButton("reset");
		
		setBounds(0, 0, 25*25, 3*25);
		
		this.setLayout(new GridLayout(1,3));
		
		add(bombLabel);
		add(resetBtn);
		add(timerLabel);
	}
	
	public void bombMarkedUpdate(int update) {
		bombLabel.setText("Bombs Left: " + Integer.toString(totalBombs - update));
	}
	
	private Timer timer = new Timer(1000, new ActionListener() {;
	    @Override
	    public void actionPerformed(ActionEvent e) {
	    	timeLapsed++;
	    	timerLabel.setText("Time: " + Integer.toString(timeLapsed) + " seconds");
	    }
	});
	
	public void startTimer() {
		timer.start();
	}
	
	public int getTime() {
		return timeLapsed;
	}
	
	public void stopTimer(){
		timer.stop();
	}
	
	public boolean timerRunning() {
		return timer.isRunning();
	}
	
	public JButton getResetBtn() {
		return resetBtn;
	}
}
