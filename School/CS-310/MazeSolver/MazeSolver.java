/*  Trenton Green
    cssc0901
*/

import data_structures.*;

public class MazeSolver {
	private Queue<GridCell> queue;
	private Stack<GridCell> stack;
	private MazeGrid grid;
	private int dimension;
	
	public MazeSolver(int dimension) {
		grid  = new MazeGrid(this, dimension);
		queue = new Queue<GridCell>();
		stack = new Stack<GridCell>();
		this.dimension = dimension;
	}
	
	/*
	enqueue cell(0,0)
	while( the queue is not empty ) {
    		dequeue a GridCell from the queue.
    		mark each adjacent neighboring cell and enqueue it
    		}
	 */
	public void mark() {	
		GridCell origin = grid.getCell(0, 0);
		origin.setDistance(0);
		queue.enqueue(origin);
		grid.markDistance(origin);
		
		while(!queue.isEmpty()) {
			GridCell c = queue.dequeue();
			int x = c.getX();
			int y = c.getY();
			int distance = c.getDistance();
			
			GridCell north = grid.getCell(x, y - 1);
			if(grid.isValidMove(north) && !north.wasVisited()) {
				north.setDistance(distance + 1);
				grid.markDistance(north);
				queue.enqueue(north);
			}
			
			GridCell south = grid.getCell(x, y + 1);
			if(grid.isValidMove(south) && !south.wasVisited()) {
				south.setDistance(distance + 1);
				grid.markDistance(south);
				queue.enqueue(south);
			}
			
			GridCell east = grid.getCell(x + 1, y);
			if(grid.isValidMove(east) && !east.wasVisited()) {
				east.setDistance(distance + 1);
				grid.markDistance(east);
				queue.enqueue(east);
			}
			
			GridCell west = grid.getCell(x - 1, y);
			if(grid.isValidMove(west) && !west.wasVisited()) {
				west.setDistance(distance + 1);
				grid.markDistance(west);
				queue.enqueue(west);
			}
		}
	}
	
	/*
	distance = terminalCell.getDistance();
	if(distance == -1) return false;  // unreachable, puzzle has no solution
	push terminal cell onto the stack
	while(distance != 0) {
    		get distance from each cell adjacent to the top of the stack
    		select the cell with smallest distance and push on the stack
    		}
	while( stack is not empty ) {
    		pop grid cell off the stack and mark it
    		}
	 */
	public boolean move() {
		GridCell terminal = grid.getCell(dimension - 1, dimension - 1);
		if(terminal.getDistance() == -1)
			return false;
		
		stack.push(terminal);
		
		while(stack.peek().getDistance() != 0) {
			GridCell c = stack.peek();
			int x = c.getX();
			int y = c.getY();
			int distance = c.getDistance();
			
			GridCell north = grid.getCell(x, y - 1);
			if(grid.isValidMove(north) && north.getDistance() < distance) {
				stack.push(north);
				continue;
			}
			
			GridCell south = grid.getCell(x, y + 1);
			if(grid.isValidMove(south) && south.getDistance() < distance) {
				stack.push(south);
				continue;
			}
			
			GridCell east = grid.getCell(x + 1, y);
			if(grid.isValidMove(east) && east.getDistance() < distance) {
				stack.push(east);
				continue;
			}
			
			GridCell west = grid.getCell(x - 1, y);
			if(grid.isValidMove(west) && west.getDistance() < distance) {
				stack.push(west);
				continue;
			}
			
		}
		
		while(!stack.isEmpty()) {
			grid.markMove(stack.pop());
		}
		
		return true;
	}
	
	public void reset() {
		queue.makeEmpty();
		stack.makeEmpty();
	}
	
    public static void main(String [] args) {
        new MazeSolver(new Integer(30));
    }
	
}
