package Simonish.components;
import javax.swing.JPanel;
import java.awt.Color;

public class SPanel extends JPanel{
	
	/**
	 * private Color color of the SPanel
	 */
	private Color panColor;
	/**
	 * public static int width of SPanel
	 */
	public static int width=200;
	/**
	 * public static int height of SPanel
	 */
	public static int height=200;
	
	/**
	 * Returns the color of the instance of SPanel
	 * @return Color
	 */
	public Color getColor(){
		return this.panColor;
	}
	
	/**
	 * Constructor that sets the panColor class variable of SPanel
	 * @param panColor Color object
	 */
	public SPanel(Color panColor){
		this.panColor = panColor;
	}
	
	/**Overriden toString()
	 * @return String rgb value of color
	 */
	public String toString(){
		return panColor.toString();
	}
	
	/**
	 * Blink operation specified for any instance of SPanel
	 */
	public void blink(){
		setBackground(getBackground().brighter());
		update(getGraphics());
		try {
			Thread.sleep(1000);
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			Thread.currentThread().interrupt();
		}
		setBackground(getBackground().darker());
		update(getGraphics());
		try {
			Thread.sleep(1000);
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			Thread.currentThread().interrupt();
		}
	}
		
}
