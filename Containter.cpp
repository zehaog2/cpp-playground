#include <iostream>
#include <queue>
#include <string> 
#include <map> 
#include <stdio.h> 
#include <stdlib.h> 
#include <time.h>
#include <vector>
#include <algorithm>
#include <cstdlib>
using namespace std;

int convert_key(int x){ // x's digits' sum
	int sum =0;
	int y = 0;
	while(x != 0){
		if(x <=0){break;}
    	y = x % 10;
    	sum += y;
    	x = x / 10;
	}
	return sum;
}

int digits(int x){ // return # of x's digits without 0
	int count = 0;
	while(x!=0){
		if(x%10== 0){
			count--;
		}
		x = x/10;
		count++;
		}
	return count;
}

int repetitions(int x){
	int y = 0;
	int once=0, twice=0, tri=0, qua = 0, fiv = 0;
	int arr[10] = {0};
	while(x>0){
		y = x%10;
		arr[y]++;
		x=x/10;
	}
	for(int i = 0;i<10;i++){
		if(arr[i] > 4){
			fiv++;
		}
		if(arr[i] == 4){
			qua++;
		}
		if(arr[i] == 3){
			tri++;
		}
		if(arr[i] == 2){
			twice++;
		}
		if(arr[i] == 1){
			once++;
		}
	}
	int result = once*10000 + twice*1000 + tri*100 + qua*10 + fiv;
	//more repeated digits will lead to a larger result
	return result;
}

void add(multimap<int,int>&mmap, int num){ 
	int key = convert_key(num);
	mmap.insert(pair<int,int>(key, num));
}

void Delete(multimap<int,int>&mmap, int value){
	// using iterator
	int key = convert_key(value);
	mmap.erase(key);
}

bool check_empty(multimap<int,int>&mmap){
	return mmap.empty();
}

void search(multimap<int,int> &mmap, vector<int>&vv,int num){
	int repeat = repetitions(num); // check for num 
	vv.clear();
	int thedigit = digits(num);
	int key = convert_key(num);
	for(int t = (key-3);t<=(key+3);t++){ // key can have an error range of 3
		pair <multimap<int,int>::iterator, 	multimap<int,int>::iterator> ret;
   		ret = mmap.equal_range(key);
   		for (multimap<int,int>::iterator it=ret.first; it!=ret.second; it++)
			vv.push_back(it->second);
	}
	sort(vv.begin(),vv.end()); // sort results by size
	vv.erase(unique(vv.begin(),vv.end()),vv.end());// remove duplicates in vector
	// the multimap container is not affected
	// using set is more efficient for large numbers of duplicates
	for (auto it = begin (vv); it != end (vv); ++it) {
		if(digits(*it) == thedigit){//#digits without 0
			if(repetitions(*it) == repeat){ //#repeated numbers
				// advanced search numbers with few digit repetitions 
				cout << *it << " ";
			}
		}
	}
	printf("\n"); // print not found under bad conditions
}

void menu(){
	cout << "               MENU\n";
	cout << "1 -> add           2 -> delete\n";        // done, done
	cout << "3 -> search        4 -> show size\n";     // done, done
	cout << "5 -> show all      6 -> show menu\n";     // done, done 
	cout << "7 -> clear         0 -> generator\n\n";   // done, done
}

int main() {
	multimap<int, int> SAYO;
	deque<int>A={};
	vector<int>vv;
	int instruction, num, rand_num,count, delete_, max_limit;
	char option;
	string answer;
	
	srand(time(NULL)); // random initialize
	menu(); //print menu
	
	
	while(true){
		cout << "USE ";
		cin >> instruction;
		switch(instruction){
			case 0:
				num = 0;
				//check map size
				printf("Numbers of elements to generate: "); // give two options: add to old generation, create new map
				scanf("%d",&num);
				while(num >= 100000000){ // int allows 8 digits
					count = 1;
					printf("A wise man said %d time: less is better...\n", count);
					count++;
					scanf("%d",&num);
					}
				printf("Give the maximum limit: ");
				cin >> max_limit;
				while(num>0){
					rand_num = rand()%max_limit + 1; // let user play around with this
					add(SAYO,rand_num);
					num--;
					}
				break;
			case 1:
				cout << "ADD (press 'enter' to add more, '0' to stop):\n";
				num = 1;
				while(num != 0){
					cin >>num;
					if(num ==0){break;}
					A.emplace_back(num);} // A is deque
				for(auto& x:A) // insert deque elements in map
					add(SAYO,x);
				break;
			case 2:// implementing the multimap erase function
				cout << "Delete options:\n";
				cout << "A: a number\n";
				cout << "B: all copies\n";
				cout << "C: key\n";
				cout << "--> ";
				cin >> option;
				if(option == 'A'){
					cout << "--> ";
					cin >> delete_;
					typedef multimap<int, int>::iterator iterator;
					pair<iterator, iterator> iterpair1 = SAYO.equal_range(convert_key(delete_)); // iterate through key
					iterator it2 = iterpair1.first;
					for (; it2 != iterpair1.second;) {
    					if (it2->second == delete_) { // deleting first number found
      	  					it2 = SAYO.erase(it2);
							printf(" Done.\n");
							break;
						}else{
							it2++; // delete one copy of the number
   							}
						} 
				} else if(option == 'B'){ // delete all copies of the element
					cout << "--> "; 
					cin >> delete_;
					typedef multimap<int, int>::iterator iterator;
					pair<iterator, iterator> iterpair2 = SAYO.equal_range(convert_key(delete_));
					iterator it3 = iterpair2.first;
					for (; it3 != iterpair2.second;) {
    					if (it3->second == delete_)
      	  					it3 = SAYO.erase(it3);
						else
							it3++;
					}
					printf("Done. \n");
				} else if(option =='C'){ // delete whole keys, should refrain from using
						cout << "Deleting a key will delete all elements associated with the key.";
						cout << "Which key to delete? (type 0 to return to menu) ";
						cin >> num;
						if(num==0){
							break; // return to menu
						} else{	
							SAYO.erase(num);
							printf("Done. \n");
							break;
						}
				} else{
					cout << "Please enter a valid option.\n";
				}
				break;
			case 3:
				cout << "Search ";
				cin >> num;
				search(SAYO,vv, num);
				break;
			case 4:
				cout <<SAYO.size() << " elements in container.\n"; // show size of container
				break;
			case 5:
				for (multimap<int,int>::iterator it=SAYO.begin(); it!=SAYO.end(); ++it)
    				cout << (*it).second << ' '; // display all numbers without keys
				cout <<"\n";
				break;
			case 6:
				menu(); // return to menu
				break;
			case 7:
				cout << "Are you sure you want to delete the container? (YES)\n";
				cin >> answer;
				if(answer=="YES"){
					SAYO.clear(); // delete container
				} break;
			default:
				cout<<"Please enter a valid instruction:\n";
		}
	}
	return 0;
}
