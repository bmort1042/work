package wickham_branch;

import java.awt.Component;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Observable;
import javax.swing.BoxLayout;
import javax.swing.JButton;
import javax.swing.JCheckBox;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextField;
import com.github.lgooddatepicker.components.DateTimePicker;

public class Search_Panel extends Observable{
	
	public boolean Reset = false;
	
	public JTextField stateField;
	public JTextField cityField;
	public JCheckBox cb[] = {new JCheckBox("Extreme"), new JCheckBox("Severe"), new JCheckBox("Moderate"), new JCheckBox("Minor"), new JCheckBox("Unknown"), new JCheckBox("Observed"), new JCheckBox("Likely"), new JCheckBox("Possible"), new JCheckBox("Unlikely"), new JCheckBox("Unknown")};
	public Component datetimepick1;
	String time;
	//public DateTimePicker datetimepick2;
	
	
	//private boolean windowOpen;
	
	public void onSearch(){
		//windowOpen = false;
		setChanged();
		notifyObservers(this);
	}
	
	private void onClose(){
		
		//windowOpen = false;
	}
	
	public void create_frame(){
		
		System.out.println("Made it here help help help");
		
		//List<Checkbox> cb = new ArrayList<Checkbox>(); //create the list of checkboxes

		
		JFrame frame = new JFrame("Configuration Panel");
		frame.setVisible(true);
		frame.setSize(300, 500);
		
		JPanel control = new JPanel();
		
		control.setLayout(new BoxLayout(control, BoxLayout.Y_AXIS));
		control.setAlignmentY(Component.TOP_ALIGNMENT);

		datetimepick1 = new DateTimePicker();
		//datetimepick2 = new DateTimePicker();
		
		JLabel time_label = new JLabel("Pick time frame for reports");
		
		control.add(time_label);
		control.add(datetimepick1);
		//control.add(datetimepick2);
		time_label.setAlignmentX(Component.CENTER_ALIGNMENT);
		
		JLabel state = new JLabel("State");
		stateField = new JTextField();
		
		control.add(state);
		control.add(stateField);
		state.setAlignmentX(Component.CENTER_ALIGNMENT);
		
		JLabel city = new JLabel("City");
		cityField = new JTextField();
		
		control.add(city);
		control.add(cityField);
		city.setAlignmentX(Component.CENTER_ALIGNMENT);
		
		JLabel severity = new JLabel("Severity");
		control.add(severity);
		severity.setAlignmentX(Component.CENTER_ALIGNMENT);
		
		
		for(int i = 0; i < 5; i++){
			control.add(cb[i]);
			cb[i].setAlignmentX(Component.CENTER_ALIGNMENT);
		}

		JLabel warning = new JLabel("Possibility");
		control.add(warning);
		warning.setAlignmentX(Component.CENTER_ALIGNMENT);

		for(int i = 5; i < 10; i++){
			control.add(cb[i]);
			cb[i].setAlignmentX(Component.CENTER_ALIGNMENT);

		}
		
		JButton button1 = new JButton("Submit");
		JButton button2 = new JButton("Cancel");
		
		control.add(button1);
		button1.setAlignmentX(Component.CENTER_ALIGNMENT);
		control.add(button2);
		button2.setAlignmentX(Component.CENTER_ALIGNMENT);
		
		button2.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent event){
				onClose();
				frame.dispose();
				frame.setVisible(false);
			}
		});
		
		button1.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent event){
				onSearch();
				time = datetimepick1.toString();
				System.out.println(time);
				frame.dispose();
				frame.setVisible(false);
			}
		});
		
		
		frame.add(control); //add the panel to the frame
			
		
		
		//windowOpen = true;
	}
	
	
}