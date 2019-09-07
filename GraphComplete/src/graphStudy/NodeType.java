package graphStudy;

import java.util.ArrayList;

public class NodeType {
	
	int nodeData;
	ArrayList<Integer> destination = new ArrayList<Integer>();
	ArrayList<Integer> cost = new ArrayList<Integer>();
	
	public void inputData(int value) {
		this.nodeData = value;
	}
	public void inputDestination(int value) {
		this.destination.add(value);
	}
	public void inputCost(int value) {
		this.cost.add(value);
	}

	/*
	 * public int get_length_destination() { return destination.length }
	 */
	public void display_data() {
		System.out.println(nodeData);
	}
	public void display_des() {
		System.out.println(destination);
	}
	public void display_cost() {
		System.out.println(cost);
	}
	
}
