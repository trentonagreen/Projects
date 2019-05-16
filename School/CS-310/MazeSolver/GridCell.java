/*  Class GridCell
    A wrapper class that holds the xy coordinates, and distance from the origin
    (0,0) of a cell in the Grid.
    Alan Riggins
    CS310 Fall 2017
*/    

public class GridCell implements Comparable<GridCell> {
    private int xCoordinate, yCoordinate, distanceFromOrigin;
    
    // Constructor should be called **ONLY** from the MazeGrid class
    // Distance is always set to -1, which indicates that it is
    // undefined.  It must be set explicitly by a call to setDistance.
    public GridCell(int x, int y) {
        xCoordinate = x;
        yCoordinate = y;
        distanceFromOrigin = -1;
        }
        
    private void setX(int x) {
        xCoordinate = x;
        }
        
    private void setY(int y) {
        yCoordinate = y;
        }
        
    public void setDistance(int d) {
        distanceFromOrigin = d;
        }                    
        
    public int getX() {
        return xCoordinate;
        }
        
    public int getY() {
        return yCoordinate;
        }
        
    public int getDistance() {
        return distanceFromOrigin;
        }          
        
    public boolean wasVisited() {
        return distanceFromOrigin != -1;
        }     
        
    public String toString() {
        return "X: " + xCoordinate + "   Y: " + yCoordinate;
        } 
        
    public boolean equals(GridCell c) {
        return c.xCoordinate == xCoordinate && c.yCoordinate == yCoordinate;
        }
        
    public int compareTo(GridCell c) {
        throw new UnsupportedOperationException();
        }       
}        
