#include <string>
#include <tr1/unordered_map>
#include <limits>
#include <map>
#include <vector>
#include <iostream>
#include <stdexcept>

using std::vector;
using std::string;
using std::map;
using std::make_pair;
using std::cout;
using std::endl;
using std::out_of_range;
//typedef tr1::unordered_map map;

// TODO: upgrade it to process trace. Rule: char-->elem  string-->elem_list
class SuffixTree
{
public:
	/*
	SuffixTree(string str):active_point(root, Edge(0,0), 0)//, test_str(str)//, root(test_str)
	{
		
		pos = 0;
		
		//root(test_str);
	}*/
	// active point is initialized as (root, None, 0), remainder initialized as 1
	SuffixTree(string str):test_str(str), pos(0), root(test_str), active_point(&root, 0, 0), remainder(0) {}
	int construct(void);

	int print_tree(void);
private:
	string test_str;

	struct Node;
	typedef struct Node Node;

	struct Edge{
		// the begin and end pos of this edge, note that INT_MAX stands for #(the changing end pos of this entire string)
		int begin, end;
		// Is there a better way to find test_str?
		string& test_node_str;
		Edge(int b, int e, string& str):
			test_node_str(str) 
		{
			begin = b;
			end = e;
			std::cout << "Edge initialized" << std::endl;
		}
		Node * endpoint;

		int change_edge(int b, int e)
		{
			begin = b;
			end = e;
		}
		
		// needed by map
		friend bool operator<(const Edge& me, const Edge& other)
		{
			return me.begin < other.begin;
		}

		char operator[](int i)
		{
			i += begin;
			if (i > end)
				throw out_of_range("Edge [] out of range.");

			return test_node_str[i];
		}

		bool is_none(void) { return begin == 0 && end == 0; }
	};
	typedef struct Edge Edge;

	struct Node{
		string& test_node_str;
		map<int, int> testmap;
		map<Edge*, bool> edges;
		// find the edge quicky by storing the leading char of this edge
		map<char, Edge*> findedges;

		Node(string& str) : 
			test_node_str(str) { edges.clear(); std::cout << "Node initialized" << std::endl; }

		int add_edge(Edge* edge) { 
			edge->endpoint = new Node(test_node_str);
			make_pair(edge, true);
			cout << "node appended to edge" << endl;
			edges.insert(make_pair(edge, true)); 
			findedges.insert(make_pair(test_node_str[edge->begin], edge));
			cout << "edge added" << endl;
		}

		// find edge by the first char
		Edge* find_edge(char c)
		{
			map<char, Edge*>::iterator iter = findedges.find(c);
			if (iter != findedges.end()) 
				return iter->second;
			else
				return NULL;
		}

		bool isleaf() { return edges.empty(); }

		bool operator==(Node& other)
		{
			return (this) == (&other);
		}

	};
	//typedef struct Node Node;

	class ActivePoint{
	public:
		Node* active_node;
		char active_edge;
		int active_length;

		ActivePoint(Node* node, char edge, int length): 
			active_node(node), active_edge(edge), active_length(length) { std::cout << "ActivePoint initialized" << std::endl; }
	};

	Node root;
	ActivePoint active_point;

	Node* get_active_node(void) { return active_point.active_node; }
	void set_active_node(Node* node) { active_point.active_node = node; }
	char get_active_edge(void) { return active_point.active_edge; }
	void set_active_edge(char edge) { active_point.active_edge = edge; }
	int get_active_length(void) { return active_point.active_length; }
	void set_active_length(int len) { active_point.active_length = len; }
	void inc_active_len() { active_point.active_length++; }
	void dec_active_len() { active_point.active_length--; }
	
	// how many suffixes is to be inserted?
	int remainder;
	// how many characters inserted?
	int pos;
	char get_ele(int i) { return test_str[i]; }
	// insert a char from pos to suffix tree
	int insert();
	int insert_rule1();
	int print_node(Node* node, int level);

	// check if we can change active node
	void check_an(void)
	{
		Node* node = get_active_node();
		Edge* edge = node->find_edge(get_active_edge());

		if (edge == NULL)
			return;

		int edge_size = edge->end - edge->begin + 1;
		
		// update
		if (edge_size == get_active_length()) {
			set_active_node(edge->endpoint);
			set_active_edge(0);
			set_active_length(0);
		}
	}
};
