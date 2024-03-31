
#include "main.h"

int MAXSIZE = 0;

class OPERATIONS;
class Gojo;
class Sukuna;
class HuffTree_AVL;



class HuffTree_AVL{
	class Node;
private:
	Node* root = nullptr;
public:
	~HuffTree_AVL(){clear(root);}
	void clear(Node* node)
	{
		if(node)
		{
			clear(node->left);
			clear(node->right);
			delete node;
		}
	}

	vector<pair<char, int>> stringProcess(string& name)
	{
		if(name.size() < 3) return{};
		vector<pair<char, int>> string2Ceasar;
		int len = name.size();
		for(int i{0}; i < len; i++)
		{
			char currentchar = name[i];
			bool charFound = false;
			for(auto& check : string2Ceasar)
			{
				if(check.first == currentchar)
				{
					check.second++;
					charFound = true;
					break;
				}
			}
			if(!charFound)
			{
				string2Ceasar.emplace_back(currentchar,1);
			}
    }
		if(string2Ceasar.size() < 3) return {};
	string s = "";
    for(int i{0}; i < len; i++)
    {
        for(auto j : string2Ceasar)
        {
            if(name[i] == j.first)
            {
                char checkChar = islower(j.first) ? 'a' : 'A';
                s += char((j.first + j.second - checkChar) % 26 + checkChar);
            }
        }
    }
    name = s;
    for(auto &pair : string2Ceasar)
        {
            char checkChar = islower(pair.first) ? 'a' : 'A';
            pair.first = (pair.first + pair.second - checkChar) % 26 + checkChar;
        }
		
	vector<pair<char, int>> freq;
    for(vector<pair<char, int>>::size_type i{0}; i < string2Ceasar.size(); i++)
    {
        char currentchar = string2Ceasar[i].first;
        int freqCount = string2Ceasar[i].second;
        bool charFound = false;

        for(vector<pair<char, int>>::size_type j{0}; j < freq.size(); j++)
        {
            if(freq[j].first == currentchar)
            {
                freq[j].second += freqCount;
                charFound = true;
                break;
            }
        }
        if(!charFound)
        {
            freq.emplace_back(currentchar, freqCount);
        }
    }
	for(vector<pair<char, int>>::size_type i{0}; i < freq.size(); i++)
    {
        for(vector<pair<char, int>>::size_type j{i}; j < freq.size(); j++)
        {
            if(freq[i].second < freq[j].second) swap(freq[i], freq[j]);
            else if(freq[i].second == freq[j].second)
            {
                if((islower(freq[i].first)) && islower(freq[j].first) && (freq[i].first < freq[j].first)) swap(freq[i], freq[j]);
                else if((isupper(freq[i].first)) && isupper(freq[j].first) && (freq[i].first < freq[j].first)) swap(freq[i], freq[j]);
                else if(((islower(freq[i].first) && isupper(freq[j].first)))) swap(freq[i], freq[j]);
            }
        }
    }

    return freq;
	}

	int getHeightRec(Node * root)
	{
		if(root == NULL) return 0;
		int lh = getHeightRec(root->left);
		int rh = getHeightRec(root->right);
		return (lh > rh ? lh : rh) + 1;
	}
	Node * rotateLeft(Node * root)
	{
		Node * tmpPtr = root -> right;
		root -> right= tmpPtr -> left;
		tmpPtr -> left = root;
		return tmpPtr;
	}
	Node * rotateRight(Node * root)
	{
		Node * tmpPtr = root -> left;
		root -> left = tmpPtr -> right;
		tmpPtr -> right = root;
		return tmpPtr;
	}
	int getBalance(Node * root)
	{
		if(!root) return 0;
		return getHeightRec(root ->left) - getHeightRec(root -> right);
	}
	Node* balanceNode(Node* node, int& count)
	{
		int balance = getBalance(node);
    
    if (balance > 1) {
        if (getBalance(node->left) >= 0) {
            count += 1;
            return rotateRight(node);
        } else {
                count += 1;
                node->left = rotateLeft(node->left);
                return rotateRight(node);
            
        }
    } else if (balance < -1) {
        if (getBalance(node->right) <= 0) {
            count += 1;
            return rotateLeft(node);
        } else {
           
                count += 1;
                node->right = rotateRight(node->right);
                return rotateLeft(node);
            
        }
    }

    return node;
	}
	Node* balanceTree(Node* node,int count = 0)
	{
		
		if(count == 1 || node == nullptr) return node;
		node = balanceNode(node, count);
		node->left = balanceTree(node->left, count);
		node->right = balanceTree(node->right, count);
		return node;
	}
	Node* buildHuff(vector<pair<char, int>> freq)
	{
		vector<Node*> build;
		int len = freq.size();
    	for( int i = 0 ; i < len;i++){
        build.push_back(new Node(freq[i].second,freq[i].first));
    	}
		while(build.size() > 1)
		{
			Node* newNode = nullptr;
			Node * smallest1 = build.back();
			build.pop_back();
			Node * smallest2 = build.back();
			build.pop_back();
			newNode =  new Node(smallest1 -> weight + smallest2 -> weight,'\0', smallest1, smallest2);

			newNode = balanceTree(newNode);
			newNode = balanceTree(newNode);
			newNode = balanceTree(newNode);
			build.push_back(newNode);
			
			int len = build.size();
			for(int i{0}; i < len; i++)
			{
				for(int j{i}; j < len; j++)
				{
					if(build[i] -> weight < build[j] -> weight) swap(build[i],build[j]);
					else if(build[i] -> weight == build[j] -> weight)
					{
						if(j == len - 1)
						{
							swap(build[i], build[j]);
							break;
						} 
					}
				}
			}
		}		
		return build[0];
	}
	void encodingHuffman_rec(vector<string>& encoding, Node* node, string s = "")
	{
		if (node == nullptr) {
        return;
		}
		encodingHuffman_rec(encoding, node->left, s + "0");
		encodingHuffman_rec(encoding, node->right, s + "1");
		if (node->left == nullptr && node->right == nullptr) {
			encoding[node-> c] = s;
			return;
		}
	}
	int encodingHuffman(Node * root,string nameCaesar)
	{
		if(root->left == nullptr && root->right == nullptr) return 0;
		vector<string> encoding(256, "");
		encodingHuffman_rec(encoding, root);
		string binaryString = "";		
		int len = nameCaesar.size();
		for(int i{len-1}; i >= 0; i--)
		{
			int len_1 = encoding[nameCaesar[i]].size();
			for(int j{len_1 - 1}; j >= 0; j--)
			{
				binaryString += encoding[nameCaesar[i]][j];
				if(binaryString.size() == 10) break;
			}
			if(binaryString.size() == 10) break;
		}
		int result = 0;
		int base = 1;
		string num = binaryString;
		int binary_len = binaryString.size();
		for(int i{binary_len - 1}; i >= 0; i--)
		{
			if(num[i] == '1') result += base;
			base = base*2;
		}
		return result;
	}


	int encode(string name){
		vector<pair<char, int>> freq  = this->stringProcess(name);
		if(freq.size() == 0) return -1;

		this->clear(root);
		root = this->buildHuff(freq);
		if(root->left == nullptr && root->right == nullptr) return 0; 
		
		int result = this->encodingHuffman(root ,name);
		return result;
	}
	void printRecur(Node* node){
		if(node == nullptr) return;
		printRecur(node->left);
		if(node->c == '\0') cout << node->weight << "\n";
		else cout << node->c << "\n";
		printRecur(node->right);
	}
	void print_HAND(){printRecur(root);}

private:
	class Node{
	public:
		int weight;
		char c;
		Node* left;
		Node* right;
		friend class HuffTree_AVL;
	public:
		Node(int weight, char c = '\0',Node* left = nullptr, Node* right = nullptr ):  weight(weight), c(c), left(left), right(right) {}
	};
};


//GOJO
class Gojo{
	class Tree_BST;
private:
	vector<Tree_BST> areaTable;
public:
	Gojo():areaTable(MAXSIZE + 1){}
	void insertAreaTable(int result)
	{
		{
		int ID = result % MAXSIZE + 1;
		areaTable[ID].insert(result); 
	}
	}
	void remove_KOKUSEN()
	{
		for(int i = 1; i < MAXSIZE + 1; i++) areaTable[i].remove();
 	}

	void printLimitness(int number)
	{
		if(number <= 0 || number > MAXSIZE) return;
		areaTable[number].print();
	}
private:
	class Tree_BST{
		class Node;
	private:
		Node* root;	
		queue<int> queueTime; 
	public:
		Tree_BST():root(nullptr){}
		~Tree_BST()
		{
			while(!queueTime.empty())
			{
				int temp = queueTime.front();		
				queueTime.pop(); 						
				root = removeRecur(root ,temp);
			}
		}
		int size(){
			return queueTime.size();
		}
		Node* insertRecur(Node* &node, int result)
		{
			if(node == nullptr)
			{
				queueTime.push(result);
				return new Node(result);
			} 
			else
			{
				if(result < node -> result) node -> left = insertRecur(node -> left, result);
				else node -> right = insertRecur(node -> right, result);
			}
			return node;
		}
		void insert(int result)
		{
			root = insertRecur(root, result);
		}
		Node* removeRecur(Node* node,int result)
		{
			if(!node) return nullptr;
			if(result < node -> result) node -> left = removeRecur(node -> left, result);
			else if(result > node -> result) node -> right = removeRecur(node -> right, result);
			else
			{
				if(node -> left == nullptr && node -> right == nullptr)
				{
					delete node;
					return nullptr;
				}
				else if(node -> left == nullptr)
				{
					Node * tmp = node -> right;
					delete node;
					return tmp;
				}
				else if(node -> right == nullptr)
				{
					Node * tmp = node -> left;
					delete node;
					return tmp;
				}
					Node * tmp = node -> right;
					while(tmp -> left != nullptr)
						tmp = tmp -> left;
					node -> result = tmp -> result;
					node -> right = removeRecur(node -> right,  node -> result);
			}
			return node;
		}
		int CountNode(Node* node)
		{
			return node == NULL ? 0 : 1 + CountNode(node->left) + CountNode(node->right);
		}

		int  permutationFormula(unsigned long long x, unsigned long long n)
		{
			vector<vector<unsigned long long>>a(n+1, vector<unsigned long long>(x+1, 0));
			for(unsigned long long i{0}; i <= n; i++)
			{
				for(unsigned long long j{0}; j <=x  && j <= i; j++)
				{
					if(j == 0 || j == i)
					{
						a[i][j] = 1;
					}
					else 
					a[i][j] = (a[i-1][j-1] % MAXSIZE + a[i-1][j] % MAXSIZE);
				}
			}
			return a[n][x];
		}
		unsigned long long DFS(Node* node)
		{
			if(node == NULL) return 1;
			if(CountNode(node) <= 2) return 1;
			unsigned long long nodeLeft = CountNode(node -> left);
			unsigned long long nodeRight = CountNode(node -> right);
			return ((DFS(node -> left) % MAXSIZE) * (DFS(node -> right) % MAXSIZE)
			*permutationFormula(nodeLeft, nodeLeft + nodeRight) % MAXSIZE) % MAXSIZE;
 		}
		
		void remove(){
			if(queueTime.empty()) return;
			
			unsigned long long number = DFS(root) % MAXSIZE;
			
			while(number != 0 && !queueTime.empty())
			{
				int temp = queueTime.front();		
				queueTime.pop(); 					
				root = removeRecur(root ,temp);
				number --;
			}
		}
		void printRecur(Node* node)
		{
			if(node != NULL){
				printRecur(node->left);
				cout << node->result << "\n";
				printRecur(node->right);
			}
		}
		void print(){printRecur(root);}
	private:
		class Node{
		private:
			int result;
			Node* left;
			Node* right;
			friend class Tree_BST;
		public:
			Node(int result) : result(result), left(NULL), right(NULL) {}
		};
	};
};

//SUKUNA
class Sukuna{
	class Node;
private:
	vector<Node* > areaTable;
	list<Node* > LRU; 
private:
	bool Compare(int index1, int index2)
	{
		list<Node *>::iterator iter1 = find(LRU.begin(),LRU.end(),areaTable[index1]);
		list<Node *>::iterator iter2 = find(LRU.begin(),LRU.end(),areaTable[index2]);
		return iter1 == LRU.end() || (iter2 != LRU.end() && static_cast<int>(distance (LRU.begin(),iter1) > distance(LRU.begin(),iter2)));
	}
	void reheapDown(int index)
	{
		while(index <static_cast<int>(areaTable.size() / 2))
		{
			int left = index*2+1;
			int right = index*2+2;
			int k = index;
			if(static_cast<size_t>(left) < areaTable.size()&& (areaTable[left]->size() < areaTable[index]->size()) ) index = left;
			else if(static_cast<size_t>(left) < areaTable.size() &&(areaTable[left]->size() == areaTable[index]->size()) 
			&& Compare(left, index)) 
				index = left;
			if(static_cast<size_t>(right) < areaTable.size() && (areaTable[right] -> size() < areaTable[index] -> size())) index = right;
			else if(static_cast<size_t>(right) < areaTable.size() && (areaTable[right] -> size() == areaTable[index] -> size()) 
			&& Compare(right, index))
				index = right;
			if(index != left && index != right) return;
			else swap(areaTable[k], areaTable[index]);
		}
		return;
	}
	void reheapUp(int index)
	{
		while(index > 0)
		{
			int k = (index - 1)/2;
			if((areaTable[k]->size() > areaTable[index] -> size()) )
				swap(areaTable[k], areaTable[index]);
			index = k;
		}
		return;
	}
	void moveTop(Node* node)
	{
		auto it  = find(LRU.begin(), LRU.end(), node);
		if(it != LRU.end()) LRU.splice(LRU.begin(), LRU, it);
		else LRU.push_front(node);
	}
    void removeNode(Node* node)
	{
		auto it = find(LRU.begin(), LRU.end(), node);
		if(it == LRU.end()) return;
		LRU.remove(node);
	}
public:
	Sukuna(){}
	~Sukuna(){
		for(size_t i{0}; i < areaTable.size(); i++){
			delete areaTable[i];
		}
	}

	void insertAreaTable(int result)
	{
		int ID = result % MAXSIZE + 1;
		int index = -1;
		for(size_t i{0}; i < areaTable.size(); i++)
		{
			if(ID == areaTable[i] -> ID)
			{
				index = i;
				break;
			}
		}

		if(index == -1){
			areaTable.push_back(new Node(ID));
			index = areaTable.size() - 1;
			areaTable[index]->insert(result);
			this->moveTop(areaTable[index]);
			this->reheapUp(index);
		}
		else 
		{
			areaTable[index]->insert(result);
			this->moveTop(areaTable[index]);
			this->reheapDown(index);
		}
	}
	void remove_KEITEIKEN(int number)
	{
		if(areaTable.size() <= 0) return;


		vector<Node* > areaTableNew(areaTable.begin(), areaTable.end());
		queue<Node* > listDelete; 
		for(int i = 0;  areaTable.size() && i < number; i++)
		{
			Node* nodeDelete = areaTable[0];
			swap(areaTable[0], areaTable[areaTable.size() - 1]);
			areaTable.pop_back();
			this->reheapDown(0);

			listDelete.push(nodeDelete);
		}
		areaTable = areaTableNew;

		while(listDelete.size()){
			Node* nodeDelete = listDelete.front();
			listDelete.pop();

			nodeDelete->remove(number);
			int index = 0;
			while(areaTable[index] !=  nodeDelete) index++;

			if(nodeDelete->size() == 0)
			{
				swap(areaTable[index], areaTable[areaTable.size() - 1]);
				this->removeNode(areaTable[areaTable.size() - 1]);
				delete areaTable[areaTable.size() - 1];
				areaTable.pop_back();
			}
			this->reheapDown(index);
		}
	}

	void printPreorder(int index, int number)
	{	
		if(static_cast<size_t>(index) >= this->areaTable.size() || number <= 0) return;
		this->areaTable[index]->print(number);
		printPreorder(index * 2 + 1, number);
		printPreorder(index * 2 + 2, number);
	}
	void printLimitness(int number){printPreorder(0, number);}
private:
	class Node{
	private:
		int ID;					
		list<int> head; 	
		friend class Sukuna;
	public:
		Node(int ID) : ID(ID) {}
		int size() const { return head.size(); }
		void insert(int result){head.push_front(result);}
		void remove(int number)
		{
			while(number != 0 && !head.empty())
			{
				cout << head.back() << "-" <<ID << "\n";
				head.pop_back();
				number--;
			}
		}
		void print(int number)
		{
			for(list<int>::iterator it = head.begin(); number > 0 && it != head.end(); ++it, --number)
			{
				cout << ID << "-" << *it  << "\n";
			}
		}
	};
};
class OPERATIONS
{
private:
	HuffTree_AVL newCustomer;
	Gojo hash;
	Sukuna heap;
	
public:

	void LAPSE(string name)
	{
		int result = newCustomer.encode(name);
		if(result == -1) return;

		if(result % 2 == 1) hash.insertAreaTable(result);
		else heap.insertAreaTable(result);
	}	

	//* xử lí nhà hàng gojo
	void KOKUSEN(){
		hash.remove_KOKUSEN();
	}
	void LIMITLESS(int num){
		hash.printLimitness(num);
	}
	
	//* xử lí nhà hàng Sukuna
	void KEITEIKEN(int num){
		heap.remove_KEITEIKEN(num);
	}
	void CLEAVE(int num){
		heap.printLimitness(num);
	}

	void HAND(){
		newCustomer.print_HAND();
	}
};
void simulate(string filename)
{
	ifstream ss(filename);
	string str, name;
	int num;

	ss >> str; ss >> MAXSIZE;

	OPERATIONS* Restaurant = new OPERATIONS();
	// //* xử lí file
	while (ss >> str)
	{
		if (str == "LAPSE")
		{
			ss >> name;
			Restaurant->LAPSE(name);
		}
		else if (str == "KOKUSEN")
		{
			Restaurant->KOKUSEN();
		}
		else if (str == "KEITEIKEN") 
		{
			ss >> num;
			Restaurant->KEITEIKEN(num);
		}
		else if (str == "HAND")
		{
			Restaurant->HAND();
		}		
		else if (str == "LIMITLESS") 
		{
			ss >> num;
			Restaurant->LIMITLESS(num);
		}		
		else if (str == "CLEAVE") 
		{
			ss >> num;
			Restaurant->CLEAVE(num);
		}				
	}
	delete Restaurant;
}

