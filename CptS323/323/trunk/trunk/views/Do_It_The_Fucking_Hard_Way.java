package teama;

import java.util.Observable;
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

class Do_It_The_Fucking_Hard_Way extends Observable{
	

	 public Vector<String> states = new Vector<String>();
	 public Vector<String> rates = new Vector<String>();
	 
		public void loadFile() throws IOException{
			File file = new File("/home/beau/workspace/worldwind/Feeds.txt");
			BufferedReader reader = null;
			
			if(!file.exists()){
				return;
			}
			
			try{
				
				reader = new BufferedReader(new FileReader(file));
				String text[];
				String line;
				int i = 0;

				while((line = reader.readLine()) != null){
					text = line.split("\n");
					if(i == 0 || i%2 == 0){
						states.add(new String (line));
					}else if(i != 0 && i%2 != 0){
						rates.add(new String (line));
					}
					
					i++;
					
				}
				
				for(int index = 0; index < states.size(); index++){
					System.out.println(states.get(index).toString());
					System.out.println(rates.get(index).toString());
					System.out.println("In Hard way!");
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
	 
	
}