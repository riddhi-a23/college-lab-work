#include<iostream>

namespace StackSystem
	struct Stack {
		int* element;
		int top;
		int size;
		int maxSize;
	};
	
	void initialize(Stack &s,int sz){
		s.top = -1;
		s.size = 0;
		s.maxSize = sz;
		s.element = new int[s.size];
	}

	bool isEmpty(const Stack &s){
		return s.top == -1;
	}

	void push(){	
		
	}

	int pop(){

	}

	int getMaxSize(){
		return s.maxSize;	
	}

	int currentSize(){
		return s.top + 1;
	}
	void inflate(){

	}

	

}
int main() {
	
	return 0;
}
