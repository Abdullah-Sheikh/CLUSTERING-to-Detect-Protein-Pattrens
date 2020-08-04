// SEMESTER PROJECT (CLUSTERING)
#include<iostream>
#include <chrono>  
#include<fstream>
#include <string>

using namespace std;
struct Edge_node
{

	string Link;
	double Weight;
	Edge_node* left, *right;
	Edge_node()
	{
		Link = "";
		Weight = 0;
		left = NULL;
		right = NULL;
	}

};

struct node
{
	string name;
	node* next;
};
struct neighbours_list
{
	string link;
	int count;
	neighbours_list * next;
	neighbours_list()
	{
		count = 1;
	}
};
struct Vertex_node
{
	string Vertex;
	int degree;
	double V_weight;
	Vertex_node *prev;
	Vertex_node *next;
	Edge_node *root;
	Vertex_node()
	{
		Vertex = "";
		degree = 0;
		V_weight=0;
		prev = next = NULL;
		root = NULL;
	}
	

};

class Graph
{
private:
	Vertex_node *head;
	Vertex_node *tail;
	node *Head_1;
	node* Tail_1;
public:
	Graph()
	{
		head = tail = NULL;
		Head_1 = Tail_1 = NULL;
	}
	void insert_Edge(string, double, Edge_node);


	//________________________________________________
	// This function insert Vertex
	void insert_Vertex(string vertex, string link, double w)
	{
		bool check = true;
		Vertex_node *p = head;
		Vertex_node *temp = new Vertex_node;

		while (p != NULL)
		{
			if (p->Vertex == vertex)
			{
				check = false;
				p->degree++;
				insert_Edge(link, w, p->root);
				break;
			}
			p = p->next;
		}
		if (check == true)
		{
			temp->Vertex = vertex;
			temp->next = NULL;
			temp->prev = NULL;
			if (head == NULL)
			{
				head = temp;
				tail = temp;
			}
			else
			{
				tail->next = temp;
				temp->prev = tail;
				tail = temp;
			}
			insert_Edge(link, w, temp->root);
			temp->degree++;
		}
	}
	void check_neighbour(string name,neighbours_list *& HEADN)
	{
		neighbours_list*p = HEADN;
		bool check = true;
		while (p != NULL)
		{
			if (name == p->link)
			{
				p->count++;
				check = false;
				break;
			}
			p = p->next;
		}
		if (check == true)
		{
			neighbours_list* temp = new neighbours_list;
			temp->link = name;
			temp->next = HEADN;
			HEADN = temp;
			cout << "Added in list : " << temp->link << endl;
		}
	}
	void traverse_edge_list(Edge_node *p,neighbours_list*& ptr)
	{
		if (p == NULL)
		{
			return;
		}
		traverse_edge_list(p->left, ptr);
		check_neighbour(p->Link, ptr);
		
		traverse_edge_list(p->right, ptr);
	}
	/*void insert_in_neighbouring_list(neighbours_list *headn)
		{
		
	}*/
	void Insert_Cluster(string Neighbor)
	{
		node *Ptr = new node;
		Ptr->name = Neighbor;
		Ptr->next = NULL;
		if (Head_1 == NULL)
		{
			Head_1 = Ptr;
			Tail_1 = Ptr;
		}
		else
		{

			Tail_1->next = Ptr;
			Tail_1 = Ptr;
			cout << "The tail is : " << Tail_1->name << endl;

		}
	}
	void Display_Neighbor()
	{
		node* Dis = Head_1;
		while (Dis != NULL)
		{
			cout << Dis->name << " ";
			Dis = Dis->next;
		}
	}
	void create_cluster(double threshold_de,double threshold_cp)
	{
	
		int n = 0;
		double density=0, cp=0;
		neighbours_list * headn=NULL,*tailn=NULL;
		
		
		while (1)
		
			{
				if (Head_1 == NULL)
				{
					n++;
					Insert_Cluster(head->Vertex);

					traverse_edge_list(head->root, headn);
				}
				else
				{
					Vertex_node *p = head;
					int e = 0;

					while (p != NULL)
					{
						if (headn->link == p->Vertex)
						{
							e = p->degree;
							break;
						}
						p = p->next;
					}

					density = e / ((n + 1)*n);
					cp = e / (density*n);
				/*	cout << "The value of density is : " << density << endl;
					cout << "The value of cp is : " << cp << endl;*/
					if (density >= threshold_de && cp >= threshold_cp)
					{
						headn = headn->next;
						Insert_Cluster(headn->link);
						traverse_edge_list(head->root, headn);

					}
				
			
					//string data = headn->link;
					//Vertex_node *p = head;
					//int e = 0;
					//while (p != NULL)
					//{
					//	if (data == p->Vertex)
					//	{
					//		e = p->degree;
					//		break;
					//	}
					//	p = p->next;
					//	}

					//	density = e / ((n + 1)*n);
					//	cp = e / (density*n);
					//	cout << "The value of density is : " << density << endl;
					//	cout << "The value of cp is : " << cp << endl;
					//	if (density >= threshold_de && cp >= threshold_cp)
					//	{
					//		
					//		 headn->link;
					//		headn = headn->next;
					//	//	cout << "The head is  :" << headn->link << endl;
					//		Insert_Cluster(head->Vertex);

					//		//cout << "The node added in cluster : " <<Head_1->name << endl;
					//		traverse_edge_list(head->root, headn);
					//	}

						else
						{
							break;
						}
					}
				}
			
		

		node * display = Head_1;
		cout << "Cluster 1 : " << endl;
		while (display != NULL)
			
		{
			cout << display->name << " --> ";
			display = display->next;
		}
		cout << endl;

	}
		void get_dataset()
		{
		ifstream Get_Data;
		string vertex, link;
		double weight;
		Get_Data.open("PPW.txt",ios ::out );
		// Record start time
		auto start = chrono::high_resolution_clock::now();

		// Portion of code to be timed
		

			// Record end time
		while (!Get_Data.eof())
		{


			Get_Data >> vertex >> link >> weight;
			insert_Vertex(vertex, link, weight);
			//Insert_Cluster(link);
		
		//	insert_Vertex(link, vertex, weight);
		}
		Get_Data.close();
		auto finish = chrono::high_resolution_clock::now();
		chrono::duration<double> elapsed = finish - start;
		cout << "Elapsed time: " << elapsed.count()/60 << " s\n";

	}

	//________________________________________________
	// This function insert edges

	void insert_Edge(string edge, double w, Edge_node * &root)
	{
		Edge_node *p = new Edge_node;
		p->Weight = w;
		p->Link = edge;
		p->left = p->right = NULL;
		if (root == NULL)
		{
			root = p;
		}
		else
		{
			Edge_node *ptr = root;
			while (ptr != NULL)
			{
				// for left 
				//
				if (w > ptr->Weight)
				{
					if (ptr->left == NULL)
					{

						ptr->left = p;
						break;
					}
					else
					{
						ptr = ptr->left;
					}
				}
				// for right
				//
				else
				{
					if (ptr->right == NULL)
					{

						ptr->right = p;
						break;
					}
					else
					{
						ptr = ptr->right;
					}
				}
			}
		}
	}

	void display_Cluster()
	{
		Vertex_node *ptr_vertex = head;
		while (ptr_vertex != NULL)
		{
			cout << "Vertex is : " << ptr_vertex->Vertex << endl;
			cout << "Degree is :" << ptr_vertex->degree << endl;
			Edge_node * ptr_edge = ptr_vertex->root;
			traverse(ptr_vertex->root);
			cout << endl;
			cout << endl;
			ptr_vertex = ptr_vertex->next;
		}

	}
	
	void traverse(Edge_node *ptr_edge)
	{
		if (ptr_edge == NULL)
		{
			return;
		}
		traverse(ptr_edge->left);
		cout << "(" << ptr_edge->Link << "->" << ptr_edge->Weight << ")  ";
		traverse(ptr_edge->right);
	}
	Vertex_node* get_head()
	{
		return head;
	}
	void sorting()
	{
		sorting_the_Cluster(head);
	}
	void sorting_the_Cluster(Vertex_node * & h)
	{
		// SORTING

		Vertex_node *ptr = h;
		
		while (ptr != NULL)
		{
			Vertex_node *p = ptr;
			p = p->next;
			while (p != NULL)
			{
				if (ptr->degree < p->degree)
				{
					Edge_node* temp_Edge=ptr->root;
					int temp_degree=ptr->degree;
					string temp_Vertex=ptr->Vertex;
					ptr->root = p->root;
					ptr->degree = p->degree;
					ptr->Vertex = p->Vertex;
					p->root = temp_Edge;
					p->degree = temp_degree;
					p->Vertex = temp_Vertex;
					
				}
				p = p->next;
			}
			ptr = ptr->next;
			
		}
		
	}
	//calculate_weight

	void calculate_weight()
	{
		Vertex_node *ptr_vertex = head;
		while (ptr_vertex != NULL)
		{
			
			Edge_node * ptr_edge = ptr_vertex->root;
			double sum = 0;
			traverse_node(ptr_vertex->root,sum);
			ptr_vertex->V_weight = sum;
			cout <<"The weight of node is :"<<ptr_vertex->V_weight<< endl;
			cout << endl;
			ptr_vertex = ptr_vertex->next;
		}

	}
	void traverse_node(Edge_node *ptr_edge,double& sum)
	{
		if (ptr_edge == NULL)
		{
			return;
		}
		traverse_node(ptr_edge->left,sum);
		sum = sum + ptr_edge->Weight;
		traverse_node(ptr_edge->right,sum);
	}

};






int main()
{
	auto start = chrono::high_resolution_clock::now();

	// Portion of code to be timed



	

	Graph Cluster;
	Cluster.get_dataset();
	Cluster.sorting();
	Cluster.display_Cluster();
	Cluster.calculate_weight();
	Cluster.create_cluster(0.8, 0.5);
	auto finish = chrono::high_resolution_clock::now();
	chrono::duration<double> elapsed = finish - start;
	cout << "Elapsed time: " << elapsed.count() / 60 << " s\n";
	//ifstream Get_Data;
	////Main_node* head = NULL, *tail = NULL;
	//string vertex, link;
	//double weight;
	//Get_Data.open("PPW.txt");

	//while (!Get_Data.eof())
	//{


	//	Get_Data >> vertex >> link >> weight;

	//}
	///*for (int i = 0; i < Vertices; i++)
	//{
	//Obj[i].Display();
	//cout << endl << endl;
	//cout << "DEGREE IS: " << Obj[i].get_degree()<<"\n\n\n";

	//}*/
	//// SORTING
	///*for (int i = 0; i < Vertices; i++)
	//{
	//for (int j = i+1; j < Vertices; j++)
	//{
	//if (Obj[i].get_degree()<Obj[j].get_degree())
	//{
	//List temp = Obj[i];
	//Obj[i] = Obj[j];
	//Obj[j] = temp;
	//}
	//}
	//}*/
	//cout << "After Sorting /n/n/n/n";
	///*for (int i = 0; i < Vertices; i++)
	//{
	//Obj[i].Display();
	//cout << endl << endl;
	//cout << "DEGREE IS: " << Obj[i].get_degree() << "\n\n\n";


	//}*/

	//Get_Data.close();
	cout << "EDGES LIST" << endl << endl << endl;
	Cluster.Display_Neighbor();
	
	system("pause");
}
