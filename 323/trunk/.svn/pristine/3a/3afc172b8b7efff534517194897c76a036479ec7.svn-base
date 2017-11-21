package views;

import java.awt.EventQueue;

import javax.swing.JFrame;
import java.awt.GridBagLayout;
import java.awt.FlowLayout;
import javax.swing.JPanel;
import javax.swing.JCheckBox;
import java.awt.GridBagConstraints;
import java.awt.GridLayout;
import java.awt.BorderLayout;
import java.awt.Component;

import javax.swing.GroupLayout;
import javax.swing.GroupLayout.Alignment;

import gov.nasa.worldwind.BasicModel;
import gov.nasa.worldwind.awt.WorldWindowGLCanvas;

import javax.swing.JRadioButton;
import javax.swing.JLabel;
import javax.swing.SwingConstants;
import javax.swing.JComboBox;
import javax.swing.DefaultComboBoxModel;

public class GridTest {

	private JFrame frame;

	/**
	 * Launch the application.
	 */
	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					GridTest window = new GridTest();
					window.frame.setVisible(true);
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});
	}
	
	public Component addGlobe(){
		
		WorldWindowGLCanvas wwd = new WorldWindowGLCanvas();
        wwd.setPreferredSize(new java.awt.Dimension(1000, 800));
        //this.getContentPane().add(wwd, java.awt.BorderLayout.EAST);
        wwd.setModel(new BasicModel());
        
        return wwd;
	}

	/**
	 * Create the application.
	 */
	public GridTest() {
		initialize();
	}

	/**
	 * Initialize the contents of the frame.
	 */
	private void initialize() {
		frame = new JFrame();
		frame.setResizable(false);
		frame.setBounds(400, 400, 1500, 1000);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.getContentPane().setLayout(null);
		
		JPanel panel = new JPanel();
		panel.setBounds(12, 12, 500, 1000);
		frame.getContentPane().add(panel);
		panel.setLayout(null);
		
		JPanel panel_1 = new JPanel();
		panel_1.setBounds(0, 0, 500, 250);
		panel.add(panel_1);
		panel_1.setLayout(null);
		
		JLabel lblNewLabel = new JLabel("Select State");
		lblNewLabel.setHorizontalAlignment(SwingConstants.CENTER);
		lblNewLabel.setBounds(150, 0, 200, 50);
		panel_1.add(lblNewLabel);
		
		JComboBox comboBox = new JComboBox();
		comboBox.setModel(new DefaultComboBoxModel(new String[] {"Washington", "California", "Oregon", "Idaho", "Nevada", "Arizona", "Colorado"}));
		comboBox.setBounds(150, 50, 200, 30);
		panel_1.add(comboBox);
		
		JLabel lblPleaseSelect = new JLabel("Please Select Weather Notifications");
		lblPleaseSelect.setVerticalAlignment(SwingConstants.TOP);
		lblPleaseSelect.setHorizontalAlignment(SwingConstants.CENTER);
		lblPleaseSelect.setBounds(105, 223, 300, 30);
		panel_1.add(lblPleaseSelect);
		
		JPanel panel_2 = new JPanel();
		panel_2.setBounds(0, 250, 500, 250);
		panel.add(panel_2);
		panel_2.setLayout(new GridLayout(4, 2, 0, 0));
		
		JCheckBox chckbxNewCheckBox = new JCheckBox("Wind");
		chckbxNewCheckBox.setHorizontalAlignment(SwingConstants.CENTER);
		panel_2.add(chckbxNewCheckBox);
		
		JCheckBox chckbxNewCheckBox_2 = new JCheckBox("Nuclear Fallout");
		chckbxNewCheckBox_2.setHorizontalAlignment(SwingConstants.CENTER);
		panel_2.add(chckbxNewCheckBox_2);
		
		JCheckBox chckbxNewCheckBox_4 = new JCheckBox("Snow");
		chckbxNewCheckBox_4.setHorizontalAlignment(SwingConstants.CENTER);
		panel_2.add(chckbxNewCheckBox_4);
		
		JCheckBox chckbxNewCheckBox_1 = new JCheckBox("Zombie Apocalypse");
		chckbxNewCheckBox_1.setHorizontalAlignment(SwingConstants.CENTER);
		panel_2.add(chckbxNewCheckBox_1);
		
		JCheckBox chckbxNewCheckBox_6 = new JCheckBox("Flood");
		chckbxNewCheckBox_6.setHorizontalAlignment(SwingConstants.CENTER);
		panel_2.add(chckbxNewCheckBox_6);
		
		JCheckBox chckbxNewCheckBox_3 = new JCheckBox("Cloudy w/ Meatballs");
		chckbxNewCheckBox_3.setHorizontalAlignment(SwingConstants.CENTER);
		panel_2.add(chckbxNewCheckBox_3);
		
		JCheckBox chckbxNewCheckBox_5 = new JCheckBox("Blizzard");
		chckbxNewCheckBox_5.setHorizontalAlignment(SwingConstants.CENTER);
		panel_2.add(chckbxNewCheckBox_5);
		
		JCheckBox chckbxSkynet = new JCheckBox("Skynet");
		chckbxSkynet.setHorizontalAlignment(SwingConstants.CENTER);
		panel_2.add(chckbxSkynet);
		
		JPanel panel_3 = new JPanel();
		panel_3.setBounds(0, 500, 500, 250);
		panel.add(panel_3);
		panel_3.setLayout(null);
		
		JLabel lblSelectTime = new JLabel("Select Time (PST)");
		lblSelectTime.setVerticalAlignment(SwingConstants.TOP);
		lblSelectTime.setHorizontalAlignment(SwingConstants.CENTER);
		lblSelectTime.setBounds(160, 20, 150, 25);
		panel_3.add(lblSelectTime);
		
		JComboBox comboBox_1 = new JComboBox();
		comboBox_1.setModel(new DefaultComboBoxModel(new String[] {"0900", "1000", "1100", "1200", "1300", "1400", "1500", "1600"}));
		comboBox_1.setBounds(150, 55, 175, 25);
		panel_3.add(comboBox_1);
		
		JPanel panel_globe = new JPanel();
		panel_globe.setBounds(512, 12, 1000, 1000);
		panel_globe.add(addGlobe());
		frame.getContentPane().add(panel_globe);
	}
}
