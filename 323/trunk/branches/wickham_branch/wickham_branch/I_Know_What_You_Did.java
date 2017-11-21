package wickham_branch;

import java.util.Observable;
import java.util.Observer;

public class I_Know_What_You_Did implements Observer{
	
	void Search_Pressed(String state, String city, boolean severe, boolean moderate, boolean minor, boolean unknown, boolean expected, boolean greaterThan, boolean lessThan, boolean whoKnows){
		//add info on what to do when information is updated.
		
	}

	@Override
	public void update(Observable o, Object arg) {
		
		if(arg instanceof Search_Panel){
			
			Search_Panel search = (Search_Panel)arg;
			
			String state = search.stateField.getText();
			String city = search.cityField.getText();
			
			boolean severe = search.cb[0].isSelected();
			boolean moderate = search.cb[1].isSelected();
			boolean minor = search.cb[2].isSelected();
			boolean unknown = search.cb[3].isSelected();
			boolean expected = search.cb[4].isSelected();
			boolean greaterThan = search.cb[5].isSelected();
			boolean lessThan = search.cb[6].isSelected();
			boolean whoKnows = search.cb[7].isSelected();
			
			Search_Pressed(state, city, severe, moderate, minor, unknown, expected, greaterThan, lessThan, whoKnows);			
			
		}
		
		if(arg instanceof RSS_Panel){
			//RSS_Panel rss = (RSS_Panel)arg;
			
			//boolean add_remove = rss.addState;
			//String state = rss.stateList.getSelectedItem().toString();
		}
		
	}


	
}