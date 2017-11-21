package teama;

import java.awt.BorderLayout;
import java.awt.Window;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.List;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Observable;
import java.util.Observer;
import java.util.Vector;
import java.io.OutputStreamWriter;

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
	
	private int index = 0;
	private boolean repeat;
	 

	@SuppressWarnings("unchecked")
	@Override
	public void update(Observable arg0, Object arg1) {
		// TODO Auto-generated method stub
		
		if(arg0 instanceof RSS_Panel){
			
			repeat = false;
			
			RSS_Panel rss_info = (RSS_Panel)arg1;
			
			if(index == 0){
				try {
					loadFile();
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
				
				System.out.println("Here is the callConfigs: " + rss_info.callConfigs);

			}
				//Cause only the best cowboy code!!!!!!!
				for(int i = 0; i < states.size(); i++){
					if(states.get(i).equals(rss_info.state)){
						
						if(rss_info.ref_rate != null){
							rates.set(i, rss_info.ref_rate);
						}
						
						if(rss_info.addState){
							active.set(i, "On");
							
						}else{
							active.set(i, "Off");
						}
						
						repeat = true;
						//System.out.println(repeat);
					}

				}
				
				if(!repeat){
					
					states.add(new String(rss_info.state));
					
					if(rss_info.ref_rate != null){
						rates.add(new String(rss_info.ref_rate));
					}else{
						rates.addElement(new String("1hr"));
					}

					if(rss_info.addState){
						active.add(new String("On"));
						//rowList.add("On");
						
					}else{
						active.add(new String("Off"));
						//rowList.add("Off");
					}
					
					System.out.println(index);
					
					index++;

				}
			
			create_frame();

		}			
	}
	
	public void writeFile() throws IOException{
		File file = new File("/home/beau/workspace/worldwind/Feeds.txt");
		FileWriter fw = new FileWriter(file.getAbsoluteFile());
		System.out.printf("File is located at %s%n", file.getAbsolutePath());
		BufferedWriter bw = new BufferedWriter(fw);
		
		for(int i = 0;i < states.size(); i++){
			
			if(active.get(i).equals("On")){
				fw.write(states.get(i).toString() + "\n" + rates.get(i).toString() + "\n");
				System.out.println("In write file");
			}
		}
		bw.close();
		
	}
	
	@SuppressWarnings("unchecked")
	public void loadFile() throws IOException{
		File file = new File("/home/beau/workspace/worldwind/Feeds.txt");
		BufferedReader reader = null;
		
		if(!file.exists()){
			return;
		}
		
		try{
			reader = new BufferedReader(new FileReader(file));
			//String text[];
			String line;
			int i = 0;
			
			while((line = reader.readLine()) != null){
				//System.out.println(line);
				if(i == 0 || i%2 == 0){
					states.add(new String (line));
				}else{
					rates.add(new String(line));
					active.add(new String("On"));
				}
				
				i++;

				
			}
			
			index = states.size();
			
			for(int index = 0; index < states.size(); index++){
				System.out.println(states.get(index).toString());
				System.out.println(rates.get(index).toString());
				System.out.println(active.get(index).toString());
				System.out.println("In load");
			}
			
			
			
		}catch (FileNotFoundException e){
			e.printStackTrace();
		}catch (IOException e){
			e.printStackTrace();
		}finally{
			try{
				if(reader != null){
					reader.close();
				}
			}catch (IOException e){
				
			}
		}
		
		
	}
		
	
	public void create_frame(){
		
		JFrame frame = new JFrame("Feed Information");

			rowList = new String[index][3];
			
			for(int i = 0; i < states.size(); i++){
				rowList[i][0] = states.get(i).toString();
				rowList[i][1] = rates.get(i).toString();
				rowList[i][2] = active.get(i).toString();
			}
				
			System.out.println(index);
			
			table = new JTable(rowList, columnNames);
			
			
			frame.add(new JScrollPane(table));


			table.setVisible(true);
			
			frame.pack();
			frame.setVisible(true);
			
			try {
				writeFile();
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}


		
		
		
	}
	
	
}