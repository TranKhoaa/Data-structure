#include "main.h"

class imp_res : public Restaurant
{
	private:
		int CustomerInRes, CustomerinQueue;
		customer * CustomerX;
		customer * CustomerQueue;
	public:	
		class CusTime
		{
				
			public:
				customer * data;
				CusTime * next;
				CusTime * prev;
				bool inRes;
				CusTime(customer * data, bool inRes){
					this -> data = data;
					this -> inRes = inRes;
					next = nullptr;
					prev = nullptr;
				}
				~CusTime(){
					delete data;
				}
		};
	private:
		CusTime * CustomerFirst;
		CusTime * CustomerLast;
	public:
		imp_res() {
			CustomerinQueue = CustomerInRes = 0;
			CustomerX = CustomerQueue = nullptr;
			CustomerFirst = CustomerLast = nullptr;
		};
		~imp_res(){
			while(CustomerFirst != nullptr){
				CusTime * temp = CustomerFirst;
				CustomerFirst = CustomerFirst -> next;
				delete temp;
			}
		}
		void InsertQueuetoRes(){
			while(CustomerinQueue != 0 && CustomerInRes != MAXSIZE){
				customer * newCus = CustomerQueue;
				CusTime * temp = CustomerFirst;
				for(int i{0}; i < CustomerinQueue + CustomerInRes; i++){
					if(temp -> data == CustomerQueue){
						temp -> inRes = true;
						break;
					}
					temp = temp -> next;
				}
				if(CustomerinQueue == 1){
					CustomerQueue = nullptr;
					CustomerinQueue = 0;
				}
				else{
					CustomerQueue = newCus -> next;
					CustomerQueue -> prev = newCus -> prev;
					newCus -> prev -> next = CustomerQueue;
					CustomerinQueue--;
				}
				if(CustomerInRes == 0){
					CustomerX = newCus;
					newCus -> next = newCus -> prev = newCus;
				}
				else{
					if(CustomerInRes >= MAXSIZE /2){
						customer* temp = CustomerX;
						int res = newCus -> energy - temp -> energy;
						for(int i{0}; i < CustomerInRes; i++){
							if(abs(newCus -> energy - temp -> energy) > abs(newCus->energy - CustomerX-> energy)){
								res = newCus->energy - temp -> energy;
								CustomerX = temp;
							}
							temp = temp -> next;
						}
						if(res >= 0){
							newCus -> next = CustomerX -> next;
							newCus -> prev = CustomerX;
							CustomerX -> next = newCus;
							newCus -> next -> prev = newCus;
							
						}
						else{
							newCus -> next = CustomerX;
							newCus -> prev = CustomerX -> prev;
							CustomerX -> prev = newCus;
							newCus -> prev -> next = newCus;
							
						}
						goto label;
					}
					if(newCus -> energy >= CustomerX->energy){
						newCus -> next = CustomerX -> next;
						newCus -> prev = CustomerX;
						CustomerX -> next = newCus;
						newCus -> next -> prev = newCus;
						}
					else{
						newCus -> next = CustomerX;
						newCus -> prev = CustomerX -> prev;
						CustomerX -> prev = newCus;
						newCus -> prev -> next = newCus;
					}
						
				}
				label:
				CustomerX = newCus;
				CustomerInRes++;
			}
		}
		void printLastToFirst(CusTime * head, CusTime * tail){
			if(head == nullptr) return;
			CusTime * current = tail;
			while(true){
				current -> data -> print();
				current = current -> prev;
				if(current == nullptr) break;
			}
		}
		void swap(customer * a, customer * b){
			customer * temp = new customer();
			temp -> next = a -> next;
			temp -> prev = a -> prev;
			a -> next -> prev = temp;
			a -> prev -> next = temp;

			a -> next = b -> next;
			a -> prev = b -> prev;
			b -> prev -> next = a;
			b -> next -> prev = a;

			b -> next = temp -> next;
			b -> prev = temp -> prev;
			temp -> next -> prev = b;
			temp -> prev -> next = b;
			delete temp;
		}
		customer * getIncreUp(customer * a, int n){
			for(int i{0}; i < n; i++){
				a = a ->next;
			}
			return a;
		}
		customer * getIncreDown(customer * a, int n){
			for(int i{0}; i < n; i++){
				a = a -> prev;
			}
			return a;
		}
		bool Higher(customer * a, customer * b){
			CusTime * temp = CustomerFirst;
			while(temp != nullptr){
				if(temp -> inRes == false){
					if(temp ->data->energy == a ->energy) return false;
					else if(temp ->data -> energy == b -> energy) return true;
				}
				temp = temp -> next;
			}
			return true;
		}
		bool check(customer* x, customer* y){
			CusTime* temp = CustomerFirst;
			while(temp != NULL)
			{
				if(temp->data == x) return false;
				else if (temp->data == y) return true;
				temp = temp->next;
			}
			return true;
		}
		void inssort2(customer * head, int n, int incr, int &swapN){
			for(int i{incr}; i < n; i+= incr){
				for(int j{i}; j >= incr; j-=incr){
					customer * temp1 =  getIncreUp(head, j);
					customer * temp2 =  getIncreUp(head, j - incr);
					 if(abs(temp1 -> energy) > abs(temp2 -> energy)){
                        swap(temp1, temp2);
                        swapN++;
                        if(temp2 == CustomerQueue) CustomerQueue = temp1;
                        if(head == temp2) head = temp1; 
                    }
                    else if(abs(temp1 -> energy) == abs(temp2 -> energy)){
                        if(check(temp1, temp2) == false){
                            swap(temp1, temp2);
                            swapN++;
                            if(temp2 == CustomerQueue) CustomerQueue = temp1;
                            if(head == temp2) head = temp1; 
                        }
                        else break;
                    }
                    else break; 
				}
			}
		}
		void RED(string name, int energy)
		{
			if(energy == 0) return;
			else if(CustomerinQueue + CustomerInRes >= MAXSIZE * 2) return;
			else{
				customer * temp = CustomerX;
				for(int i{0}; i < CustomerInRes; i++){
					if(temp -> name == name) return;
					temp = temp -> next;
				}
				temp = CustomerQueue;
				for(int i{0}; i < CustomerinQueue; i++){
					if(temp -> name == name) return;
					temp = temp -> next;
				}
			}
			if(CustomerInRes == MAXSIZE){
				customer * newCus = new customer(name, energy, nullptr, nullptr);
				if(CustomerQueue == 0){
					CustomerQueue = newCus;
					CustomerQueue -> next = CustomerQueue -> prev = CustomerQueue;
				}
				else{
					newCus -> next = CustomerQueue;
					newCus -> prev = CustomerQueue -> prev;
					CustomerQueue -> prev = newCus;
					newCus-> prev -> next = newCus;
				}

				CusTime * newCustomer = new CusTime(newCus, false);
				CustomerLast -> next = newCustomer;
				newCustomer -> prev = CustomerLast;
				CustomerLast = CustomerLast -> next;

				CustomerinQueue++;
				return;
			}
			else if(CustomerInRes == 0){
				CustomerX = new customer(name, energy ,nullptr, nullptr);
				CustomerX -> next = CustomerX -> prev = CustomerX;

				CustomerFirst = CustomerLast = new CusTime(CustomerX, true);
				CustomerInRes++;
				return;
			}
			else if(CustomerInRes >= MAXSIZE / 2){
			customer * temp = CustomerX;
				int res = energy - temp -> energy;
				for(int i{0}; i < CustomerInRes; i++){
					if(abs(energy - temp -> energy) > abs(energy - CustomerX-> energy)){
						res = energy - temp -> energy;
						CustomerX = temp;
					}
					temp = temp -> next;
				}
				customer* cus = new customer (name, energy, nullptr, nullptr);
				if(res >= 0){
					cus -> next = CustomerX -> next;
					cus -> prev = CustomerX;
					CustomerX -> next = cus;
					cus -> next -> prev = cus;
				}
				else{
					cus -> next = CustomerX;
					cus -> prev = CustomerX -> prev;
					CustomerX -> prev = cus;
					cus -> prev -> next = cus;
				}
			CustomerX = cus;
			CustomerInRes++;

			CusTime* newCustomer = new CusTime(CustomerX, true);
			CustomerLast -> next = newCustomer;
			newCustomer -> prev = CustomerLast;
			CustomerLast = CustomerLast -> next;

			return;
			};
			customer* cus = new customer (name, energy, nullptr, nullptr);
			if(energy >= CustomerX -> energy){
				cus -> next = CustomerX -> next;
				cus -> prev = CustomerX;
				CustomerX -> next = cus;
				cus -> next -> prev = cus;
				
			}
			else{
				cus -> next = CustomerX;
				cus -> prev = CustomerX -> prev;
				CustomerX -> prev = cus;
				cus -> prev -> next = cus;
			}
			CustomerX = cus;
			CustomerInRes++;

			CusTime* newCustomer = new CusTime(CustomerX, true);
			CustomerLast -> next = newCustomer;
			newCustomer -> prev = CustomerLast;
			CustomerLast = CustomerLast -> next;
			
			return;
			
		}
		void BLUE(int num)
		{
			if(CustomerInRes == 0) return;
			if(num >= CustomerInRes || num > MAXSIZE) num = CustomerInRes;
			for(int i{0}; i < num; i++){
				CusTime * temp = CustomerFirst;
				for(int i{0}; i < CustomerInRes + CustomerinQueue; i++){
					if(temp -> inRes == true) break;
					temp = temp -> next;
				}
				if(CustomerInRes + CustomerinQueue == 1){
					CustomerFirst = CustomerLast = nullptr;
				}
				else if(temp == CustomerFirst){
					CustomerFirst = CustomerFirst -> next;
					CustomerFirst -> prev = nullptr;
				}
				else if(temp == CustomerLast){
					CustomerLast = CustomerLast -> prev;
					CustomerLast -> next = nullptr;
				}
				else{
					temp -> prev -> next = temp -> next;
					temp -> next -> prev = temp -> prev;
				}

				if(CustomerInRes == 1) CustomerX = nullptr;
				else{
					customer * CustomerDelete = temp -> data;
					if(CustomerDelete -> energy > 0) CustomerX = CustomerDelete -> next;
					else  CustomerX = CustomerDelete -> prev;

					CustomerDelete->next->prev = CustomerDelete -> prev;
					CustomerDelete -> prev -> next = CustomerDelete -> next;
				}
				delete temp;
				CustomerInRes--;
				
			}
			this -> InsertQueuetoRes();
		}
		void PURPLE()
		{
			if(CustomerinQueue <= 1) return;
			int SwapN = 0;
			customer * temp = CustomerQueue;
			customer * max = CustomerQueue;
			int n = 0;
			for(int i{0}; i < CustomerinQueue; i++){
				if(abs(temp -> energy) >= abs(max -> energy)){
					max = temp;
					n = i + 1;
				}
				temp = temp -> next;
			}

			for(int i{n/2}; i >2; i /= 2){
				for(int j{0}; j < i; j++){
					inssort2(getIncreUp(CustomerQueue, j), n - j, i, SwapN);
				}
			}
			inssort2(CustomerQueue,n, 1,SwapN);
			BLUE(SwapN % MAXSIZE);
		}
		void REVERSAL()
		{
			if(CustomerInRes <= 1) return;
			customer * head = nullptr;
			customer * tail = nullptr;
			customer * temp = CustomerX;
			head = CustomerX;

			for(int i{0}; i < CustomerInRes; i++){
				if(temp -> energy > 0) break;
				temp = temp -> prev;
			}
			for(int i{0}; i < CustomerInRes; i++){
				if(head -> energy < 0) break;
				head = head -> prev;
			}
			tail = CustomerX -> next;
			for(int i{0}; i < CustomerInRes; i++){
				if(tail -> energy < 0) break;
				tail = tail -> next;
			}
			if(head -> energy < 0 && head != tail){
				for(int i{0}; i < CustomerInRes/2; i++){
					this -> swap (head, tail);
					customer * temp = head;
					head = tail;
					tail = temp;
					
					head = head -> prev;
					for(int i{0}; i < CustomerInRes; i++){
						if(head -> energy < 0) break;
						head = head -> prev;
					}
					if(head == tail) break;
					tail = tail -> next;
					for(int i{0}; i < CustomerInRes; i++){
						if(tail -> energy < 0) break;
						tail = tail -> next;
					}
					if(head == tail) break;
				}
			}
			
			head = temp;
			for(int i{0}; i < CustomerInRes; i++){
				if(head -> energy > 0) break;
				head = head -> prev;
			}
			tail = temp-> next;
			for(int i{0}; i < CustomerInRes; i++){
				if(tail -> energy > 0) break;
				tail = tail -> next;
			}
			if(head -> energy > 0 && head != tail){
				for(int i{0}; i < CustomerInRes/2; i++){
					this -> swap (head, tail);
					customer * temp = head;
					head = tail;
					tail = temp;
					
					head = head -> prev;
					for(int i{0}; i < CustomerInRes; i++){
						if(head -> energy > 0) break;
						head = head -> prev;
					}
					if(head == tail) break;
					tail = tail -> next;
					for(int i{0}; i < CustomerInRes; i++){
						if(tail -> energy > 0) break;
						tail = tail -> next;
					}
					if(head == tail) break;
				}
			}
		}
		void UNLIMITED_VOID()
		{
			if(CustomerInRes <= 3 ) return;
			customer * head = nullptr;
			customer * tail = nullptr;
			int size_MAX = 4;
			int min;
			customer * tempi = CustomerX;
			for(int i{0}; i < 3; i++){
				min += tempi -> energy;
				tempi = tempi -> next;
			}
			tempi = CustomerX;
			for(int i{0}; i < CustomerInRes; i++)
			{
				int total = 0;
				customer * tempj = tempi;
				for(int j{0}; j < CustomerInRes; j++){
					total += tempj -> energy;
					if(j >= 3 && (min > total || min == total  && j + 1 >= size_MAX)){
						head = tempi;
						tail = tempj;
						size_MAX = j + 1;
						min = total;
					}
					tempj = tempj -> next;
				}
				tempi = tempi -> next;
			}
			customer * minNode = head;
			customer * temp = head -> next;
			int Head2minNode  = 1;
			int Head2Tail = 1;
			while(temp != tail->next){
				Head2Tail++;
				if(minNode -> energy > temp -> energy){
					minNode = temp;
					Head2minNode = Head2Tail;
				}
				temp = temp -> next;
			}
			for(int i{0}; i <= Head2Tail - Head2minNode;i++){
				minNode -> print();
				minNode = minNode -> next;
			}
			for(int i{0}; i < Head2minNode - 1; i++){
				head -> print();
				head = head -> next;
			}
		}
		
		void deleteCus(CusTime * CustomerTemp){
			if(CustomerTemp -> inRes == true){
			if(CustomerInRes == 1){
				CustomerInRes = 0;
				CustomerX = nullptr;
			}
			else{
				customer * CustomerDelete = CustomerTemp -> data;
				CustomerDelete -> next -> prev = CustomerDelete -> prev;
				CustomerDelete -> prev -> next = CustomerDelete -> next;
				if(CustomerDelete-> energy > 0) CustomerX = CustomerDelete -> next;
				else CustomerX = CustomerDelete -> prev;
				CustomerInRes--;
			}
		}
			else{
				if(CustomerinQueue == 1){
					CustomerinQueue = 0;
					CustomerQueue = nullptr;
				}
				else{
					customer * CustomerDelete = CustomerTemp -> data;
					if(CustomerDelete == CustomerQueue) CustomerQueue = CustomerQueue -> next;
					CustomerDelete -> next -> prev = CustomerDelete -> prev;
					CustomerDelete -> prev -> next = CustomerDelete -> next;
					CustomerinQueue--;
				}
			}
			delete CustomerTemp;
		}
		void DOMAIN_EXPANSION()
		{
			if(CustomerInRes == 0) return;
			int Curse_Spiprit = 0;
			int Jujutsu = 0;
			CusTime * temp = CustomerFirst;
			for(int i{0}; i < CustomerinQueue + CustomerInRes; i++){
				if(temp ->data ->energy > 0) Jujutsu += temp ->data->energy;
				else Curse_Spiprit += temp->data->energy;
				temp = temp -> next;
			}
			CusTime * last = CustomerLast;
			while(last != nullptr){
				if((Jujutsu >= abs(Curse_Spiprit)) && last -> data -> energy < 0){
					last -> data -> print();
				}
				else if((Jujutsu < abs(Curse_Spiprit)) && last -> data -> energy > 0){
					last -> data -> print();
				}
				last = last -> prev;
			}

			temp = CustomerFirst;
			if(Jujutsu >= abs(Curse_Spiprit)){
				while(temp != nullptr){
					CusTime * Customerdelete = temp;
					temp = temp -> next;
					if(Customerdelete -> data -> energy < 0){
					if(CustomerinQueue + CustomerInRes == 1)
					{
						CustomerFirst = CustomerLast = nullptr;
					}
					else if(Customerdelete == CustomerFirst)
					{
						CustomerFirst->next->prev = nullptr;
						CustomerFirst = CustomerFirst->next;
					}
					else if(Customerdelete == CustomerLast)
					{
						CustomerLast->prev->next = nullptr;
						CustomerLast = CustomerLast->prev;
					}
					else
					{
						Customerdelete->next->prev = Customerdelete->prev;
						Customerdelete->prev->next = Customerdelete->next;
					}		
					deleteCus(Customerdelete);
				}
				}
			}
			else{
				while(temp != nullptr){
					CusTime * Customerdelete = temp;
					temp = temp -> next;
					if(Customerdelete -> data -> energy > 0){
					if(CustomerinQueue + CustomerInRes == 1)
					{
						CustomerFirst = CustomerLast = nullptr;
					}
					else if(Customerdelete == CustomerFirst)
					{
						CustomerFirst->next->prev = nullptr;
						CustomerFirst = CustomerFirst->next;
					}
					else if(Customerdelete == CustomerLast)
					{
						CustomerLast->prev->next = nullptr;
						CustomerLast = CustomerLast->prev;
					}
					else
					{
						Customerdelete->next->prev = Customerdelete->prev;
						Customerdelete->prev->next = Customerdelete->next;
					}
						deleteCus(Customerdelete);
					}
				}
			}
			this -> InsertQueuetoRes();
		}
		void LIGHT(int num)
		{
				if(num == 0 && CustomerinQueue != 0){
					customer * temp = CustomerQueue;
					for(int i{0}; i < CustomerinQueue; i++){
						temp -> print();
						temp = temp-> next;
						if(temp == nullptr) break;
					}
				}
				else if(num > 0){
					customer * temp = CustomerX;
					for(int i{0}; i < CustomerInRes; i++){
						temp -> print();
						temp = temp -> next;
						if(temp == nullptr) break;
					}
				}
				else if(num < 0){
					customer * temp = CustomerX;
					for(int i{0}; i < CustomerInRes; i++){
						temp -> print();
						temp = temp -> prev;
						if(temp == nullptr) break;
					}
				}
			
		}
};