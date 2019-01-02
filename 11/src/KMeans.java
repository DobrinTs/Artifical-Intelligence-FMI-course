import java.io.*;
import java.util.ArrayList;
import java.util.Random;
import java.util.Scanner;

public class KMeans {
	static int k;
	static boolean changed;

	static double maxX;
	static double minX;
	static double maxY;
	static double minY;

	static ArrayList<Point> points;
	static ArrayList<Point> centroids;

	private static void initializeCentroids() {
		centroids = new ArrayList<Point>();
		for(int i=0; i<k; i++) {
			Random r = new Random();
			double x = minX + (maxX - minX) * r.nextDouble();
			double y = minY + (maxY - minY) * r.nextDouble();
			Point centroid = new Point(x, y, i);
			centroids.add(centroid);
		}
	}

	private static void clusterize() {
		for(Point p : points) {
			double nearestDistance = Double.MAX_VALUE;
			int nearestIdx = -1;
			for(int i=0; i<centroids.size(); i++) {
				double distanceToI = p.distanceTo(centroids.get(i));
				if(distanceToI < nearestDistance) {
					nearestDistance = distanceToI;
					nearestIdx = i;
				}
			}

			if(p.clusterIdx != nearestIdx) {
				changed = true;
				p.clusterIdx = nearestIdx;
			}
		}
	}

	private static void recalculateCentroids() {
		int[] counters = new int[k];
		
		for(Point c : centroids) {
			c.x = 0;
			c.y = 0;
		}

		for(Point p : points) {
			int cIdx = p.clusterIdx;
			Point centroidI = centroids.get(cIdx);
			centroidI.x += p.x / 10;
			centroidI.y += p.y / 10;
			counters[cIdx]++;
		}

		for(int i=0; i<k; i++) {
			Point centroidI = centroids.get(i);
			centroidI.x *= 10;
			centroidI.y *= 10;

			centroidI.x /= ++counters[i];
			centroidI.y /= ++counters[i];

		}
	}

	private static void kMeans() {
		double bestGoodness = Double.MAX_VALUE;
		ArrayList<Point> bestSolutionPoints = new ArrayList<Point>();
		ArrayList<Point> bestSolutionCentroids = new ArrayList<Point>();
		
		for(int i=0; i<150; i++) {
			initializeCentroids();
			unclusterizeAllPoints();
			changed = true;
			
			while(changed) {
				changed = false;
				clusterize();
				recalculateCentroids();
			}
			
			double eval = solutionGoodness();
			if(eval < bestGoodness) {
				bestGoodness = eval;
				bestSolutionPoints.clear();
				bestSolutionCentroids.clear();
				for(Point p : points) {
					bestSolutionPoints.add(p.copy());
				}
				for(Point centroid : centroids) {
					bestSolutionCentroids.add(centroid.copy());
				}
			}
		}
		points = bestSolutionPoints;
		centroids = bestSolutionCentroids;
	}
	
	private static void unclusterizeAllPoints() {
		for(Point p : points) {
			p.clusterIdx = -1;
		}
	}

	private static double solutionGoodness() {
		double withinPointScatter = 0;
		int[] clusterCounters = new int[k];

		for(Point p : points) {
			clusterCounters[p.clusterIdx]++;
		}
		
		for(Point centroid : centroids) {
			double centroidScatter = 0;
			for(Point p : points) {
				if(centroid.clusterIdx == p.clusterIdx) {
					centroidScatter += p.distanceTo(centroid) / 10;
				}
			}
			withinPointScatter += centroidScatter;
		}

		return withinPointScatter * 10;
	}

	private static void readPointsFromFile(String fileName) 
			throws FileNotFoundException  {

		File file = new File(fileName);
		double x, y;

		Scanner scan = new Scanner(file);

		while(scan.hasNextDouble())
		{
			x = scan.nextDouble();
			if(fileName.equals("normal.txt")) {
				x *= 10;
			}else if(fileName.equals("unbalance.txt")) {
				x /= 1000;
			}

			if(x > maxX) {
				maxX = x;
			}
			if(x < minX) {
				minX = x;
			}

			y = scan.nextDouble();
			if(fileName.equals("normal.txt")) {
				y *= 10;
			}else if(fileName.equals("unbalance.txt")) {
				y /= 1000;
			}

			if(y > maxY) {
				maxY = y;
			}
			if(y < minY) {
				minY = y;
			}
			Point p = new Point(x, y);
			points.add(p);
		}

		scan.close();
	}

	public static void printResults() {
		for(int i=0; i<k; i++) {
			System.out.println("---------------------------");
			System.out.println("Cluster " + i +":");
			for(Point p : points) {
				if(p.clusterIdx == i) {
					p.print();
				}
			}
		}
	}
	
	public static void main(String[] args) {
		Scanner sc;
		String fileName;
		ClustersImageGenerator generator;
		int width, height;
		
		sc = new Scanner(System.in);
		System.out.println("Enter file name: ");
		fileName = sc.nextLine();

		System.out.println("Enter k: ");
		k = sc.nextInt();
		sc.close();

		KMeans.maxX = Double.MIN_VALUE;
		KMeans.maxY = Double.MIN_VALUE;

		KMeans.minX = Double.MAX_VALUE;
		KMeans.minY = Double.MAX_VALUE;

		points = new ArrayList<Point>();

		try {
			readPointsFromFile(fileName);
		} 
		catch (FileNotFoundException e1) {
			e1.printStackTrace();
		}


		kMeans();
		printResults();

		height = (int)(20 +  (maxY - minY));
		width = (int)(20 +  (maxX - minX));
		
		generator = new ClustersImageGenerator(points);
		generator.generate(width, height);

		System.out.println("DONE");
	}

}
