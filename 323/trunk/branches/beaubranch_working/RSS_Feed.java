package views;

import java.net.HttpURLConnection;
import java.net.URL;
import java.util.Iterator;
import java.util.List;

import javax.net.ssl.HttpsURLConnection;

import com.sun.syndication.feed.synd.SyndEntry;
import com.sun.syndication.feed.synd.SyndFeed;
import com.sun.syndication.io.SyndFeedInput;
import com.sun.syndication.io.XmlReader;

public class RSS_Feed{
	
	@SuppressWarnings("rawtypes")
	public void Reader(){
		
		try {
			URL url = new URL("https://alerts.weather.gov/cap/us.php?x=1");
			HttpURLConnection httpcon = (HttpURLConnection)url.openConnection();
			SyndFeedInput input = new SyndFeedInput();
			SyndFeed feed = input.build(new XmlReader(httpcon));
			List entries = feed.getEntries();
			Iterator itEntries = entries.iterator();
	 
			while (itEntries.hasNext()) {
				SyndEntry entry = (SyndEntry) itEntries.next();
				System.out.println("Title: " + entry.getTitle());
				System.out.println("Link: " + entry.getLink());
				System.out.println("Author: " + entry.getAuthor());
				System.out.println("Publish Date: " + entry.getPublishedDate());
				System.out.println("Description: " + entry.getDescription().getValue());
				System.out.println();
			}
		
		}
        catch (Exception e)
        {
            e.printStackTrace();
        }
	}
}
	