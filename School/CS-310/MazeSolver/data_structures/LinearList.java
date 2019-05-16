/*  Trenton Green
    cssc0901
*/

package data_structures;

import java.util.Iterator;
import java.util.NoSuchElementException;
import java.util.ConcurrentModificationException;

public class LinearList<E extends Comparable<E>> implements LinearListADT<E>{
	private Node<E> head, tail;
	private int size;
	private long modCounter;
	
	class Node<E> {
		E data;
		Node next;
		Node prev;
		
		public Node(E data) {
			next = prev = null;
			data = null;
		}
	}
	
	public LinearList() {
		head = tail = null;
		size = 0;
		modCounter = 0;
		clear();
	}
	
	public boolean addFirst(E obj) {
		Node<E> newNode = new Node<E>(obj);
		if(head == null) {					
			head = tail = newNode;
			head.data = obj;
		}
		else {
			newNode.data = obj;
			newNode.next = head;
			head.prev = newNode;
			head = newNode;
		}
		size++;
		modCounter++;
		return true;
	}
	
	public boolean addLast(E obj) {
		Node<E> newNode = new Node<E>(obj);
		if(head == null) {
			head = tail = newNode;
			head.data = obj;
		}
		else {
			newNode.data = obj;
			newNode.prev = tail;
			tail.next = newNode;
			tail = newNode;
		}
		size++;
		modCounter++;
		return true;
	}
	
	public E removeFirst() {
		Node<E> current = head;
		if(current == null) return null;
		if(current == tail) {
			head = head.next;
			tail = tail.next;
		}
		else {
			current.next.prev = current.prev;
			head = current.next;
		}
		size--;
		modCounter++;
		return current.data;
	}
	
	public E removeLast() {
		Node<E> current = tail;
		if(current == null) return null;
		if(current == head) {
			head = head.next;
			tail = tail.next;
		}
		else {
			current.prev.next = current.next;
			tail = current.prev;
		}
		size--;
		modCounter++;
		return current.data;
	}
	
	public E remove(E obj) {
		Node<E> current = head;
		while(current != null && obj.compareTo(current.data) != 0)
			current = current.next;
		if(current == null) return null;
		else if(current == head) removeFirst();
		else if(current == tail) removeLast();
		else {
			current.prev.next = current.next;
			current.next.prev = current.prev;
			size--;
			modCounter++;
		}
		return current.data;
	}
	
	public E peekFirst() {
		return head.data;
	}
	
	public E peekLast() {
		return tail.data;
	}
	
	public boolean contains(E obj) {
		return (find(obj) != null);
	}

	public E find(E obj) {
		for(E tmp : this) 
			if(obj.compareTo(tmp) == 0)
				return tmp;	
		return null;
	}

	public void clear() {
		head = tail = null;
		size = 0;
		modCounter = 0;
	}

	public boolean isEmpty() {
		return (size == 0);
	}

	//List will never be full
	public boolean isFull() {
		return false;
	}

	public int size() {
		return size;
	}

	public Iterator<E> iterator() {
		return new IteratorHelper();
	}
	
	class IteratorHelper implements Iterator<E> {
		private Node<E> iterPtr;
		private long modCheck;
		
		public IteratorHelper() {
			modCheck = modCounter;
			iterPtr = head;
		}
		
		public boolean hasNext() {
			if(modCheck != modCounter)
				throw new ConcurrentModificationException();
			return iterPtr != null;
		}

		public E next() {
			if(!hasNext())
				throw new NoSuchElementException();
			E tmp = iterPtr.data;
			iterPtr = iterPtr.next;
			return tmp;
		}
		
		public void remove() {
			throw new UnsupportedOperationException();
		}
		
	}

}
