package wickham_branch;

import java.awt.BorderLayout;
import java.awt.Component;
import java.awt.FlowLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Observable;
import javax.swing.BoxLayout;
import javax.swing.ButtonGroup;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JRadioButton;

public class RSS_Panel extends Observable{
	
	//private boolean windowOpen;
	public boolean addState;
	public String state;
	
	public String states[] = {"Alabama", "Alaska", "Arizona", "Arkansas", "California", "Connecticut",
			"Delaware", "Florida", "Georgia", "Hawaii", "Idaho", "Illinois", "Indiana", "Iowa",
			"Kansas", "Kentucky", "Louisiana", "Maine", "Maryland", "Massachusetts", "Michigan",
			"Minnesota", "Mississippi", "Missouri", "Montana", "Nebraska", "Nevada", "New Hampshire",
			"New Jersey", "New Mexico", "New York", "North Carolina", "North Dakota", "Ohio",
			"Oklahoma", "Oregon", "Pennsylvania", "Rhode Island", "South Carolina", "South Dakota",
			"Tennessee", "Texans", "Utah", "Vermont", "Virginia", "Washington", "West Virginia",
			"Wisconsin", "Wyoming"
	};
	
	public JRadioButton button[] = {new JRadioButton("8hr"), new JRadioButton("4hr"), new JRadioButton("1hr"), new JRadioButton("30min"), new JRadioButton("5min"), new JRadioButton("1min")};
	
	public ButtonGroup button_group = new ButtonGroup();
	
	JComboBox stateList;
	
	public void onAdd(){
		//windowOpen = false;
		setChanged();
		notifyObservers(this);
	}
	
	public void onRemove(){
		setChanged();
		notifyObservers(this);
	}
	
	public void create_frame(){
		JFrame frame = new JFrame();
		frame.setVisible(true);
		frame.setSize(300, 225);
		frame.setLayout(new BorderLayout());
		
		JPanel controlTop = new JPanel();
		JPanel middle = new JPanel();
		JPanel controlBottom = new JPanel();
		controlTop.setLayout(new BorderLayout());
		middle.setLayout(new BoxLayout(middle, BoxLayout.Y_AXIS));
		controlBottom.setLayout(new FlowLayout(FlowLayout.CENTER));
		
		stateList = new JComboBox(states);
		controlTop.add(stateList);
		
		JLabel refresh = new JLabel("Refresh RSS Feed Time");
		middle.add(refresh);
		refresh.setAlignmentX(Component.CENTER_ALIGNMENT);
		
		for(int i = 0; i < 6; i++){
			button_group.add(button[i]);
			middle.add(button[i]);
			button[i].setAlignmentX(Component.CENTER_ALIGNMENT);
		}
		
		JButton add = new JButton("Add Feed");
		

		JButton remove = new JButton("Remove");
		
		controlBottom.add(add);
		controlBottom.add(remove);
		
		add.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent event){
				addState = true;
				state = (String) stateList.getSelectedItem();
				System.out.println(state);
				onAdd();
				frame.dispose();
				frame.setVisible(false);
			}
		});
		
		remove.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent event){
				addState = false;
				state = (String) stateList.getSelectedItem();
				onRemove();
				frame.dispose();
				frame.setVisible(false);
			}
		});

		
		frame.add(controlTop, BorderLayout.NORTH);
		frame.add(middle, BorderLayout.CENTER);
		frame.add(controlBottom, BorderLayout.SOUTH);
		
		
		
		
	}
	
}