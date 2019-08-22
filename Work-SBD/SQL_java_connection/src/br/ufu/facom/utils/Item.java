package br.ufu.facom.utils;

public class Item {
	private int index;
	String id;
	
	public Item(int index, String id) {
		this.id = id;
		this.index = index;
	}
	
	public String getId() {
		return id;
	}
	
	public int getIndex() {
		return index;
	}
	
	public void setId(String id) {
		this.id = id;
	}
	
	public void setIndex(int index) {
		this.index = index;
	}
	
	public String toString() {
		return String.valueOf(this.index);
	}
}
