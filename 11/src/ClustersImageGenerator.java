import java.awt.Color;
import java.awt.Graphics2D;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Random;

import javax.imageio.ImageIO;

public class ClustersImageGenerator {
	private ArrayList<Point> points;
	
	static BufferedImage bi;
	static final String outputFile = "kMeans.png";
	static Color[] clusterColors;
	
	public ClustersImageGenerator(ArrayList<Point> points) {
		this.points = points;
	}

	public void generate(int width, int height) {
		bi = new BufferedImage(width, height, BufferedImage.TYPE_INT_RGB);
		makeBackgroundWhite();
		generateColors();
		drawPoints(height);
		
		try {
			ImageIO.write(bi, "PNG", new File(outputFile));
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	
	private void makeBackgroundWhite() {
		Graphics2D graphics = bi.createGraphics();
		graphics.setPaint ( new Color ( 255, 255, 255 ) );
		graphics.fillRect ( 0, 0, bi.getWidth(), bi.getHeight() );
	}
	
	private void generateColors() {
		Random rnd = new Random();
		ArrayList<Color> colors = new ArrayList<>(KMeans.k);
		int i = 0;
		while (i++ < KMeans.k) {
			colors.add(new Color(rnd.nextInt(255), rnd.nextInt(255), rnd.nextInt(255), 100));
		}
		clusterColors = colors.toArray(new Color[KMeans.k]);
	}
	
	private void drawPoints(int height) {
		for(Point p : points) {
			int pixelX = (int)( 10 + (p.x - KMeans.minX) );
			int pixelY = (int)( 10 + (p.y - KMeans.minY) );
			// we want (0, 0) to be bottom-left, not top-left
			int reversedPixelY = height - pixelY;
			
			int rgb = clusterColors[p.clusterIdx].getRGB();
			bi.setRGB(pixelX, reversedPixelY, rgb);
		}
	}
}
