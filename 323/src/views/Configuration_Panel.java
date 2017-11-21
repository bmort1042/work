package teama;

import java.awt.BorderLayout;
import java.awt.Window;
import java.util.List;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Observable;
import java.util.Observer;
import java.util.Vector;

import javax.swing.JFrame;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.event.TableModelEvent;
import javax.swing.event.TableModelListener;
import javax.swing.table.AbstractTableModel;
import javax.swing.table.TableModel;

public class Configuration_Panel implements Observer{
	
	public JTable table = null;
	
	 private String columnNames[] = {"State Feed", "Active", "Refresh Rate"};
	 @SuppressWarnings("rawtypes")
	Vector states = new Vector();
	 @SuppressWarnings("rawtypes")
	Vector rates = new Vector();
	@SuppressWarnings("rawtypes")
	Vector active = new Vector();
	String[][] rowList;
	
	private int index = 1;
	 

	@SuppressWarnings("unchecked")
	@Override
	public void update(Observable arg0, Object arg1) {
		// TODO Auto-generated method stub
		
		if(arg0 instanceof RSS_Panel){
			RSS_Panel rss_info = (RSS_Panel)arg1;
			states.add(new String(rss_info.state));
			rates.add(new String(rss_info.button.toString()));
			if(rss_info.addState){
				active.add(new String("On"));
				//rowList.add("On");
				
			}else{
				active.add(new String("Off"));
				//rowList.add("Off");
			}
			
			//rowList.add(rss_info.state);
			//rowList.add(rss_info.button.toString());
		
			create_frame();
			
			
		}
		
	}
	
	public void create_frame(){
		
		JFrame frame = new JFrame("Feed Information");
		frame.setVisible(true);
		
		for(int i = 0; i < states.size(); i++){
			index++;
		}
		rowList = new String[3][index];
		
		for(int i = 0; i < states.size(); i++){
			rowList[i][0] = (String) states.get(i);
			rowList[i][1] = (String) rates.get(i);
			rowList[i][2] = (String) active.get(i);
		}
			

		table = new JTable(rowList, columnNames);
		
		
		
		table.add(new JScrollPane(table));


		table.setVisible(true);
		
		frame.pack();
		frame.add(table);
		
		
	}
	
}