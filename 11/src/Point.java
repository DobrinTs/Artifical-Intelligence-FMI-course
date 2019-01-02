
public class Point {
	public double x;
	public double y;
	public int clusterIdx;

	public Point(double x, double y) {
		this.x = x;
		this.y = y;
		clusterIdx = -1;
	}
	
	public Point(double x, double y, int clusterIdx) {
		this.x = x;
		this.y = y;
		this.clusterIdx = clusterIdx;
	}
	
	public double distanceTo(Point other) {
		return Math.sqrt( (x - other.x) * (x - other.x) + 
						  (y - other.y) * (y - other.y) );
	}
	
	public void print() {
		System.out.println(x + " " + y);
	}
	
	public Point copy() {
		return new Point(x, y, clusterIdx);
	}

}
