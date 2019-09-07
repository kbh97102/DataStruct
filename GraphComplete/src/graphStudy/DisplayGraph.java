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
		//노드의 총개수 입력
		line = br.readLine();
		//문자열인 5를 정수로 짜잔
		nodeNum = Integer.parseInt(line);
		System.out.println(nodeNum);
		NodeType[] nodeSet = new NodeType[nodeNum];
		for(int i=0;i<nodeNum;i++) {
			nodeSet[i] = new NodeType();
		}
		if(is_graphFile) {
			
			//본격적으로 데이터 입력
			while(true){
				//node :
				line = br.readLine();
				//파일이 끝나면 종료
				if( line == null) {
					break;
				}
				//node값
				line = br.readLine();
				nodeNum = Integer.parseInt(line);
				//nullPointerException
				
				nodeSet[nodeIndex].inputData(nodeNum);
				nodeSet[nodeIndex].display_data();
				//목적지, cost
				while(true) {
					line = br.readLine();
					if(line.equals(is_nodeEnd)) {
						System.out.println(line);
						break;
					}
					String nodeTemp[] = line.split(",");
					//목적지
					nodeNum = Integer.parseInt(nodeTemp[0]);
					nodeSet[nodeIndex].inputDestination(nodeNum);
					nodeSet[nodeIndex].display_des();
					//cost
					nodeNum = Integer.parseInt(nodeTemp[1]);
					nodeSet[nodeIndex].inputCost(nodeNum);
					nodeSet[nodeIndex].display_cost();
				}
				//만약 파일이끝이면 또 증가시킬필요가없어서 맨아래로 빼놈
				nodeIndex++;
			}
		}
		else {
			System.out.println("함께폭사하자");
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
		//시작할 값의 노드 찾기
		for(int i=0;i<nodeSet.length;i++) {
			if(nodeSet[i].nodeData == start) {
				startIndex = i;
				break;
			}
		}
		destinationMaxIndex = nodeSet[startIndex].destination.size()-1;
		
		pathList.clear();
		//for(int j=0;j<= destinationMaxIndex;j++) {
			// 지나간 길 입력
		if(is_find == true) {
			return;
		}
		pathList.add(nodeSet[startIndex].nodeData);

		if(start == goal) {
			System.out.println(start+"와 "+goal+"이 서로 같습니다.");
			return;
		}
		else {
			while(true) {
				//한 노드에서 갈수 있는 목적지중 가장 마지막에 있는 값부터 비교
				destinationMaxIndex = nodeSet[startIndex].destination.size()-1;
				
				while(true) {
					compareData = nodeSet[startIndex].destination.get(destinationMaxIndex);
					//지나온 길왔던 길에 또 갈려고하면 다른길 모색
					if(pathList.contains(compareData)) {
						checkVisited[compareData]++;
						if(checkVisited[compareData] >= 3 && destinationMaxIndex <=0) {
							System.out.println(start+"에서 "+goal+"로 가는 길이 없습니다.");
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
					//비교할 노드 찾기
					for(int j1=0;j1<nodeSetMaxIndex;j1++) {
						if(nodeSet[j1].nodeData == compareData) {
							compareIndex = j1;
							break;
						}
					}
					//비교하기
					if(nodeSet[compareIndex].nodeData == goal) {
						System.out.println(start+"에서 "+goal+"까지 갈 수 있다.");
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
