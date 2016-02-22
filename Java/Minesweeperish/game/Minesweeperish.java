package Minesweeperish.game;

import java.awt.Container;
import java.awt.Dimension;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.util.Random;

import javax.swing.JFrame;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.SwingUtilities;

import Minesweeperish.gamecomponent.MButton;
import Minesweeperish.gamecomponent.ScoreBoard;

public class Minesweeperish extends JFrame implements ActionListener, MouseListener{
	private MButton[][] btnBoard;
	private boolean gameOver;
	private int width = 25;
	private int height = 25;
	private int btnSize = 25;
	private int numBombs = width * height / 5; //change this to 100 to help with end of game testing
	
	Container pane;
	JPanel boardPanel;
	ScoreBoard scorePanel;
	
	private Minesweeperish() {
		this.setTitle("Minesweeperish");
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		this.setResizable(false);
		pane = this.getContentPane();
		pane.setLayout(null);
		resetGame();
	}
	
	private void resetGame() {
		gameOver = false;
		MButton.resetMButton();
		pane.removeAll();
		boardPanel = new JPanel();
		pane.setPreferredSize(new Dimension(width*btnSize, (height+3) * btnSize));
		scorePanel = new ScoreBoard(numBombs);
		scorePanel.getResetBtn().addActionListener(this);
		boardPanel.setLayout(null);
		boardPanel.setBounds(0, 3*btnSize, width*btnSize, height*btnSize);
		pane.add(scorePanel);
		pane.add(boardPanel);
		initBtns();
		setBombs();
		pane.update(pane.getGraphics());		
		this.pack();
		this.setLocationRelativeTo(null);	
		this.setVisible(true);
	}
	
	private void initBtns() {
		this.btnBoard = new MButton[width][height];
		
		for(int w = 0; w < width; w++) {
			for(int h = 0; h < height; h++) {
				MButton tmp = new MButton(w, h, btnSize, btnBoard);
				tmp.addMouseListener(this);
				btnBoard[w][h] = tmp;
				boardPanel.add(btnBoard[w][h]);
			}
		}
	}
	
	private void setBombs() {
		Random rnd = new Random();
		int tmpX;
		int tmpY;
		int cnt = 0;
		
		while (cnt < numBombs) {
			tmpX = rnd.nextInt(width);
			tmpY = rnd.nextInt(height);
			if (!btnBoard[tmpX][tmpY].hasBomb()) {
				btnBoard[tmpX][tmpY].setBomb();
				cnt++;
				
				try {
					btnBoard[tmpX-1][tmpY-1].addNeighborBomb();
				} catch (ArrayIndexOutOfBoundsException e) {}
				
				try {
					btnBoard[tmpX-1][tmpY].addNeighborBomb();
				} catch (ArrayIndexOutOfBoundsException e) {}
				
				try {
					btnBoard[tmpX-1][tmpY+1].addNeighborBomb();
				} catch (ArrayIndexOutOfBoundsException e) {}
				
				try {
					btnBoard[tmpX][tmpY-1].addNeighborBomb();
				} catch (ArrayIndexOutOfBoundsException e) {}
				
				try {
					btnBoard[tmpX][tmpY+1].addNeighborBomb();
				} catch (ArrayIndexOutOfBoundsException e) {}
				
				try {
					btnBoard[tmpX+1][tmpY-1].addNeighborBomb();
				} catch (ArrayIndexOutOfBoundsException e) {}
				
				try {
					btnBoard[tmpX+1][tmpY].addNeighborBomb();
				} catch (ArrayIndexOutOfBoundsException e) {}
				
				try {
					btnBoard[tmpX+1][tmpY+1].addNeighborBomb();
				} catch (ArrayIndexOutOfBoundsException e) {}				
			}
		}
	}
	
	private void clickNeighbors(MButton m) {
		int tmpX = m.getLocX()-1;
		int tmpY = m.getLocY()-1;
		try {
			if (!btnBoard[tmpX-1][tmpY-1].isDone())
				procClick(btnBoard[tmpX-1][tmpY-1]);
		} catch (ArrayIndexOutOfBoundsException e) {}
		
		try {
			if (!btnBoard[tmpX-1][tmpY].isDone())
				procClick(btnBoard[tmpX-1][tmpY]);
		} catch (ArrayIndexOutOfBoundsException e) {}
		
		try {
			if (!btnBoard[tmpX-1][tmpY+1].isDone())
				procClick(btnBoard[tmpX-1][tmpY+1]);
		} catch (ArrayIndexOutOfBoundsException e) {}
		
		try {
			if (!btnBoard[tmpX][tmpY+1].isDone())
				procClick(btnBoard[tmpX][tmpY+1]);
		} catch (ArrayIndexOutOfBoundsException e) {}
		
		try {
			if (!btnBoard[tmpX+1][tmpY+1].isDone())
				procClick(btnBoard[tmpX+1][tmpY+1]);
		} catch (ArrayIndexOutOfBoundsException e) {}
		
		try {
			if (!btnBoard[tmpX+1][tmpY].isDone())
				procClick(btnBoard[tmpX+1][tmpY]);
		} catch (ArrayIndexOutOfBoundsException e) {}
		
		try {
			if (!btnBoard[tmpX+1][tmpY-1].isDone())
				procClick(btnBoard[tmpX+1][tmpY-1]);
		} catch (ArrayIndexOutOfBoundsException e) {}
		
		try {
			if (!btnBoard[tmpX][tmpY-1].isDone())
				procClick(btnBoard[tmpX][tmpY-1]);
		} catch (ArrayIndexOutOfBoundsException e) {}
	}
	
	private void procGameOver() {
		gameOver = true;
		for(int w = 0; w < width; w++) {
			for(int h = 0; h < height; h++) {
				btnBoard[w][h].gameOver();
			}
		}
		scorePanel.stopTimer();
		gameOverMsg();
	}
	
	private boolean hasWon() {
		if (MButton.getClickEmptyCorrect() == (width * height - numBombs) && MButton.getMarkBombCorrect() == numBombs) {
			return true;
		} else
			return false;
	}
	
	private void gameOverMsg() {
		if (MButton.getMarkBombCorrect() == numBombs || hasWon()) {
			String msg = "Congratulations! You Win!\n" + "Winning Time: " + scorePanel.getTime() + " seconds";
			JOptionPane.showMessageDialog(this, msg);
		} else {
			String msg = "Sorry. You Lose!\n" + "Bombs Found: " + MButton.getMarkBombCorrect() + "\n"
					+ "Incorrectly Marked Bombs: " + MButton.getMarkBombWrong() + "\n"
					+ "Cleared Areas: " + MButton.getClickEmptyCorrect() + "\n"
					+ "Missed Bombs: " + (numBombs - MButton.getMarkBombCorrect());
			JOptionPane.showMessageDialog(this, msg);
		}
	}

	private void procClick(MButton m) {
		if(m.hasBomb()) return;
		m.clicked();
		if(m.noNeighborBombs() && !m.hasBomb() && !gameOver) {
			clickNeighbors(m);
		}
	}
	
	public static void main(String[] args) {
		new Minesweeperish();
	}
	
	@Override
	public void mouseClicked(MouseEvent e) {
		if(gameOver) {
			return;
		}
		MButton tmp = (MButton) e.getSource();
		if (tmp.isDone()) {
			return;
		}
		
		if (SwingUtilities.isRightMouseButton(e)) {
			tmp.rightClicked();		
			scorePanel.bombMarkedUpdate(tmp.updateMarked());
			if (hasWon()) {
				procGameOver();
			}
		} else {
			if (!scorePanel.timerRunning()) {
				scorePanel.startTimer();
			}
			procClick(tmp);
			tmp.clicked();
			if ((tmp.hasBomb() && tmp.isDone()) || hasWon()) {
				procGameOver();
			}
		}
	}

	@Override
	public void mousePressed(MouseEvent e) {}

	@Override
	public void mouseReleased(MouseEvent e) {}

	@Override
	public void mouseEntered(MouseEvent e) {}

	@Override
	public void mouseExited(MouseEvent e) {}

	@Override
	public void actionPerformed(ActionEvent e) {		
		if(e.getSource() == scorePanel.getResetBtn()) {
			resetGame();
		}		
	}
}
