
#include <iostream>
#include <queue>
#include <fstream>
using namespace std;
const int V = 8; //препроцессор для числа вершин в графе


/*путь от источника s до t (bool)
      vertex- наша вершина (+1/-1)   */

/*
* принимает граф (список вершин) и номера вершин, 
задающих исток и сток. Функция формирует путь (список дуг) и список посещенных вершин, возвращает true если путь удалось найти.
 */
int BFS(int Graph[V][V], int s, int t, int vertex[])
{
    //посещенный массив(с метками,что все вершины не посещ-ые)
    bool visited[V];  
    for (int i = 0; i < V; ++i)
       visited[i] = false;

    // добавили вершину V в очередь BFS
    //Получить все остальные вершины графа, которые смежны с вершиной V
    queue <int> q;
    q.push(s); 
    visited[s] = true; //первую вершину устанавливаем как посещ-ую 
    vertex[s] = -1; //  первая метка маршруто (a, from, vertex)

   //
    while (!q.empty()) //пока не дошли до стока
    {
        int u = q.front(); //ссылка на первый элемент в начале queue.
        q.pop();

        for (int v = 0; v < V; v++)
        {
            if (visited[v] == false && Graph[u][v] > 0)
            {
                q.push(v);
                vertex[v] = u;
                visited[v] = true;
            }
        }
    }

    // Если мы достигли t
    return (visited[t] == true);
}

// Функция на основе DFS для поиска всех достижимых вершин из s
//помечает посещенный[i] как true, если i доступен из s.
void dfs(int Graph[V][V], int s, bool visited[])
{
    visited[s] = true;
    for (int i = 0; i < V; i++)
        if (Graph[s][i] && !visited[i])
            dfs(Graph, i, visited);
}


void MAXFLOW(int graph[V][V], int s, int t)
{
    if (s == t ||graph==NULL)
    {
        throw std::runtime_error("!");
    }
    int u, v;
    int Graph[V][V]; 
    for (u = 0; u < V; u++)
        for (v = 0; v < V; v++)
            Graph[u][v] = graph[u][v];

    int vertex[V];  //для save puth

    int max_flow = 0;
    // Увеличиваем поток, пока есть путь от s к t
    while (BFS(Graph, s, t, vertex))
    {
        
         // Находим минимальную пропускную способность ребер 

        int path_flow = INT_MAX;
        for (v = t; v != s; v = vertex[v]) 
        {
            u = vertex[v];
            path_flow = min(path_flow, Graph[u][v]);
        }

        //# обновляем веса дуг
        for (v = t; v != s; v = vertex[v])
        {
            u = vertex[v];
            Graph[u][v] -= path_flow;
            Graph[v][u] += path_flow;
        }

        cout << "flow:" << path_flow << endl;
        max_flow += path_flow;
    }
    bool visited[V];
    for (int i = 0; i < V; ++i)
        visited[i] = false;






    dfs(Graph, s, visited);// для пок.пути 

    //выводим достижимые ребра
    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++) {
            if (visited[i] && !visited[j] && graph[i][j]) {
    //            cout << i << " -> " << j << endl;
    //            cout << graph[i][j] << endl;
            }
        }
    cout  << max_flow << endl;

    return;
}




void EdinichGraph(int graph[V][V], int s, int t)
{


    for (int u = 0; u < V; u++)
    {
        for (int v = 0; v < V; v++)
            if (graph[u][v] != 0)
            {
                graph[u][v] = 1;
            }
    }
    for (int u = 0; u < V; u++)
    {
        for (int v = 0; v < V; v++)
          
            {
               cout<< graph[u][v];
            }
    }

}





void EdgeConnect(int graph[V][V],int s,int t)
{
    

    for (int u = 0; u < V; u++)
        for (int v = 0; v < V; v++)
            if (graph[u][v] != 0)
            {
                graph[u][v] = 1;
           }
    MAXFLOW(graph, s, t);
    
}





int main()
{



   
                      //  1   2  3  4  5  6
    int graph[V][V] = {  {0, 2, 0, 3, 4, 0},
                         {0, 0, 2, 0, 0, 0},
                         {0, 0, 0, 0, 0, 2},
                         {0, 0, 0, 0, 0, 3},
                         {0, 0, 0, 0, 0, 4},
                         {0, 0, 0, 0, 0, 0}
    };
    cout << "max Flow="<<endl;
    MAXFLOW(graph, 0, 5);

   
    cout << "EdgeConnect="<<endl;
    EdgeConnect(graph,0,5);




    cout << "Graph1"<<endl;
    for (int i = 0; i < V-2; i++) {
        for (int j = 0; j < V-2; j++)
           std::cout << " " << graph[i][j];
       std::cout << std::endl;
   }
 //   FordF(graph, 0, 5);

    

    cout << "****************"<<endl;

    

    int graph2[V][V] = { {0, 2},
                         {0, 0},
    };
    MAXFLOW(graph2,0,1);


    for (int i = 0; i < V-6; i++) {
        for (int j = 0; j < V-6; j++)
            std::cout << " " << graph2[i][j];
        std::cout << std::endl;
    }

    cout << "*Edge Connectivity*"<<endl;
       EdgeConnect(graph2,0,1);


      cout <<"****************"<<endl;


  
       
       //граф нул.
       int graph4[V][V] = {   };
      
       for (int i = 0; i < V-2 ; i++) {
           for (int j = 0; j < V-2 ; j++)
               std::cout << " " << graph4[i][j];
           std::cout << std::endl;
       }

       MAXFLOW(graph4, 0, 1);


       cout << "*************" << endl;
       cout << "Graph6" << endl;

      int graph6[V][V] = { {0, 5, 0, 0},
                           {0, 0, 5, 2},
                           {0, 0, 0, 2},
                           {0, 0, 0, 0},
                           
                        
       };
      cout << "Flow"<<endl;
      MAXFLOW(graph6, 0, 3);
       cout << "EdgeConnect" << endl;
      EdgeConnect(graph6, 0, 3);



       cout << "*************" << endl;



     /*  int s, t;
       ifstream in;
       cout << " s = "; cin >> s;
       cout << " t = "; cin >> t;
       int A[V][V];
       in.open("input.txt", ios::_Nocreate);
       if (!in)
       {
           cout << "Файл не найден.";
       }
       while (!in.eof())
       {
        
       }
       in.close();
       FordF(A, s, t);
       */
       int vertex;
       cout << "Graph proizv "<<endl;
       cout << "*Enter the number of vertices*" << endl;
       cin >> vertex;
       int graph5[V][V] = {};
       
       for (int i = 0; i < vertex; i++)   
       {
           for (int j = 0; j < vertex; j++) 
           {
               cin >> graph5[i][j];              
           }
       }
       MAXFLOW(graph5, 0, vertex-1);
       EdgeConnect(graph5, 0, vertex - 1);
    
















    return 0;
}