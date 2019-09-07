package graphStudy;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;

import graphStudy.NodeType;



public class DisplayGraph {
	
	public static void main(String[] args) throws IOException{
		
		//int MAX_NODE;
		int nodeNum = 0;
		int nodeIndex = 0;
		boolean is_graphFile = false;
		String check_is_graphFile = "GraphFile";
		String is_nodeEnd = "--";
		String filePath = "C:\\Users\\GangBoHun\\Desktop\\helpme\\graph2-1.txt";
		BufferedReader br = new BufferedReader(new FileReader(filePath));
		//GraphFIle
		String line = br.readLine();
		if(line.equals(check_is_graphFile)) {
			is_graphFile = true;
		}
		//����� �Ѱ��� �Է�
		line = br.readLine();
		//���ڿ��� 5�� ������ ¥��
		nodeNum = Integer.parseInt(line);
		System.out.println(nodeNum);
		NodeType[] nodeSet = new NodeType[nodeNum];
		for(int i=0;i<nodeNum;i++) {
			nodeSet[i] = new NodeType();
		}
		if(is_graphFile) {
			
			//���������� ������ �Է�
			while(true){
				//node :
				line = br.readLine();
				//������ ������ ����
				if( line == null) {
					break;
				}
				//node��
				line = br.readLine();
				nodeNum = Integer.parseInt(line);
				//nullPointerException
				
				nodeSet[nodeIndex].inputData(nodeNum);
				nodeSet[nodeIndex].display_data();
				//������, cost
				while(true) {
					line = br.readLine();
					if(line.equals(is_nodeEnd)) {
						System.out.println(line);
						break;
					}
					String nodeTemp[] = line.split(",");
					//������
					nodeNum = Integer.parseInt(nodeTemp[0]);
					nodeSet[nodeIndex].inputDestination(nodeNum);
					nodeSet[nodeIndex].display_des();
					//cost
					nodeNum = Integer.parseInt(nodeTemp[1]);
					nodeSet[nodeIndex].inputCost(nodeNum);
					nodeSet[nodeIndex].display_cost();
				}
				//���� �����̳��̸� �� ������ų�ʿ䰡��� �ǾƷ��� ����
				nodeIndex++;
			}
		}
		else {
			System.out.println("�Բ���������");
		}
		
		
		for(int u=0;u<nodeSet.length;u++) {
			for(int o=0;o<nodeSet.length;o++) {
				canArrival(nodeSet, u, o);
			}
		}
		
		//canArrival(nodeSet, 1, 6);
		//canArrival(nodeSet, 4, 5);
		//canArrival(nodeSet, 5, 0);
		
		
	}
	
	public static void canArrival(NodeType nodeSet[], int start, int goal) {
		ArrayList<Integer> pathList = new ArrayList<Integer>();
		int destinationMaxIndex;
		int compareData;
		int compareIndex=0;
		int startIndex=0;
		int nodeSetMaxIndex = nodeSet.length;
		int checkVisited[] = new int[nodeSetMaxIndex];
		boolean is_find = false;
		boolean no_path = false;
		for(int i=0;i<checkVisited.length;i++) {
			checkVisited[i] = 0;
		}
		//������ ���� ��� ã��
		for(int i=0;i<nodeSet.length;i++) {
			if(nodeSet[i].nodeData == start) {
				startIndex = i;
				break;
			}
		}
		destinationMaxIndex = nodeSet[startIndex].destination.size()-1;
		
		pathList.clear();
		//for(int j=0;j<= destinationMaxIndex;j++) {
			// ������ �� �Է�
		if(is_find == true) {
			return;
		}
		pathList.add(nodeSet[startIndex].nodeData);

		if(start == goal) {
			System.out.println(start+"�� "+goal+"�� ���� �����ϴ�.");
			return;
		}
		else {
			while(true) {
				//�� ��忡�� ���� �ִ� �������� ���� �������� �ִ� ������ ��
				destinationMaxIndex = nodeSet[startIndex].destination.size()-1;
				
				while(true) {
					compareData = nodeSet[startIndex].destination.get(destinationMaxIndex);
					//������ ��Դ� �濡 �� �������ϸ� �ٸ��� ���
					if(pathList.contains(compareData)) {
						checkVisited[compareData]++;
						if(checkVisited[compareData] >= 3 && destinationMaxIndex <=0) {
							System.out.println(start+"���� "+goal+"�� ���� ���� �����ϴ�.");
							no_path = true;
							break;
						}
						else if(checkVisited[compareData] < 3 && destinationMaxIndex <=0){
							break;
						}
						else if(checkVisited[compareData] < 3 && destinationMaxIndex >=1) {
							destinationMaxIndex--;
							compareData = nodeSet[startIndex].destination.get(destinationMaxIndex);
						}
						
					}
					pathList.add(compareData);
					//���� ��� ã��
					for(int j1=0;j1<nodeSetMaxIndex;j1++) {
						if(nodeSet[j1].nodeData == compareData) {
							compareIndex = j1;
							break;
						}
					}
					//���ϱ�
					if(nodeSet[compareIndex].nodeData == goal) {
						System.out.println(start+"���� "+goal+"���� �� �� �ִ�.");
						is_find = true;
						break;
					}
					if(destinationMaxIndex >0) {
						destinationMaxIndex--;
					}
					else {
						break;
					}
				}
				if(is_find == false) {
					int tempData = nodeSet[startIndex].destination.get(destinationMaxIndex);
					if(no_path == true) {
						break;
					}
					for(int b = 0;b<nodeSet.length;b++) {
						if(nodeSet[b].nodeData == tempData) {
							startIndex = b;
							break;
						}
					}
				} 
				else {
					break;
				}

			}
		}
	}
	//}
}
