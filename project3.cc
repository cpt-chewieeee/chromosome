//Assignment: CS141, Project 3
#include <fstream>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <map>
#include <utility>
#include <assert.h>
#include <iomanip>
#include <string>
#include <list>
#include <algorithm>   
using namespace std;

void write_vect(vector<char> A){
  for(vector<char>::iterator it = A.end(); it != A.begin(); --it){
    cout << *it << " ";
  }
}

typedef pair<int, int> air;
class graph{
  //public:
    
    //typedef int node_id;
  private:
    struct node{
      air id;
      
      list<node*> neighbors;
    };
    map<air,node*>id_index;
  public:
    void add_vertex(air A){
      node *newnode = new node();
      newnode->id = A;
      id_index.insert(pair<air,node*>(A, newnode));
    }
    void add_edge(air A, air B){
      id_index.at(A)->neighbors.push_back(id_index.at(B));
      //id_index.at(B)->neighbors.push_back(id_index.at(A));
    }
    bool adjacent(air A, air B){
      for(list<node*>::iterator i = id_index.at(A)->neighbors.begin();
          i != id_index.at(A)->neighbors.end(); ++i){
            if((*i)->id == B) return true;
          }
      return false;
    }
    int print_i(air A){
      
      int ith;
    
      //cout << A.first << ' ' << A.second << endl;
      for(list<node*>::iterator i = id_index.at(A)->neighbors.begin();
          i != id_index.at(A)->neighbors.end(); ++i){
            //cout << (*i)->id.first << ' ' << (*i)->id.second << endl;
            ith = (*i)->id.first;
            
          }
      return ith;
    }
    int print_j(air A){
      int jth;
      for(list<node*>::iterator i = id_index.at(A)->neighbors.begin();
          i != id_index.at(A)->neighbors.end(); ++i){
            //cout << (*i)->id.first << ' ' << (*i)->id.second << endl;
            jth = (*i)->id.second;
          }
      return jth;
    }
    
};

const int width = 4;
double get_penalty(const char& a, const char& b)
{
  if(a == b){
    return 1.0;
  }
  else if((a == 'T' && b == 'A') || (a == 'A' && b == 'T')){
    return -0.15;
  }
  else if((a == 'C' && b == 'G') || (a == 'G' && b == 'C')){
    return -0.15;
  }
  else{
    return -0.1;
  }
}
double max_value(double a, double b){
  if(a >= b) return a;
  return b;
}

void write_vect_string(vector<string> A){
  for(vector<string>::iterator it = A.begin(); it != A.end(); ++it){
    cout << *it << endl << endl;
  }
}

void write_2d_vect(const vector<vector<double> >&A, int row, int col){
  for(unsigned int i = 0; i < row; ++i){
    for(unsigned int j = 0; j < col; ++j){
      cout << '[' << i << ':' << j << ']' << setw(width) << A[i][j] << "   ";
    }
    cout << endl;
  }
}

void print_name_score(const vector<string>&A, const vector<double>B){
  if(A.size() != B.size()){
    cout << "WTF" << endl;
  }
  else{
    int size = A.size();
    for(unsigned int i = 0; i < size; ++i){
      cout << i << ' ' << B[i] << " * " << A[i] << endl;
    }
  }
}
double check_first(const double& A){
  double a = A+(-.05);
  return a;
}
bool incr_05(const double& A, const double& B){
  if((A+(-.05) == B) || (B+(-.05) == A)){
    
    return true;
  }
  return false;
}
bool incr_2(const double& A, const double& B){
  if((A+(-.2) == B) || (B+(-.2) == A)){
    
    return true;
  }
  return false;
}

bool pairCompare(const std::pair<double,string>& ele1, const std::pair<double,string>& ele2)
{
    return ele1.first < ele2.first;
}

void write_txt(char* file_open_ref, char* file_open_query, char* print_size, char* flag){
  vector<char>_ref;
  vector<char>_que;
  ifstream ifs_ref;
  ifstream ifs_que;
  vector<string>name;
  vector<double>final_score;
  vector<vector<double> >LOCATION_PEN;
  vector<double>tmp;
  int int_print_size = atoi(print_size);
  int int_flag = atoi(flag);
  
  int row, col;
  int run = 1;
  
  ifs_ref.open(file_open_ref);
  ifs_que.open(file_open_query);
 
  string str_tmp;
  char input_tmp;
  _que.push_back('-');
  while(ifs_que >> input_tmp || !ifs_que.eof()){
    _que.push_back(input_tmp);
  }
  
  
  //write_vect(_que);
  //cout << endl << endl;
  row = _que.size();
  
  while(getline(ifs_ref, str_tmp)){
    name.push_back(str_tmp);
    getline(ifs_ref, str_tmp);
    _ref.push_back('-');
    
    for(unsigned int i = 0; i < str_tmp.size(); ++i){
      _ref.push_back(str_tmp[i]);
    }
    
    col = _ref.size();
    
    //cout << "ROW: " << row << "::COL: " << col << endl;
    air tmp_pair;
    graph TRAVEL;
    double pen_incr = 0;
    //tmp.clear();
    for(unsigned i = 0; i < row; ++i){
      for(unsigned j = 0; j < col; ++j){
        tmp.push_back(0);
        tmp_pair = make_pair(i, j);
        TRAVEL.add_vertex(tmp_pair);
      }
      LOCATION_PEN.push_back(tmp);
      tmp.clear();
    }
    double max = 0;
    
    air tmp_prev;
    
    air tmp_up;
    air tmp_diag;
    air tmp_left;
    
    air tmp_k_up;
    air tmp_k_left;
    
    
    double _up;
    double _diag;
    double _left;
    for(unsigned k = 0; k < row; ++k){
      if(k == 0){
        LOCATION_PEN[k][0] =0;
      }else{
        tmp_pair = make_pair(k, 0);
        tmp_prev = make_pair(k-1,0);
          /**************[1][0]******************/
          if(k == 1){
            
            LOCATION_PEN[k][0] = -0.2;
          }else{
            LOCATION_PEN[k][0] = LOCATION_PEN[k-1][0] - 0.05;
            
          }
          TRAVEL.add_edge(tmp_pair, tmp_prev);
      }
      
    }
    for(unsigned t = 1; t < col; ++t){
      tmp_pair = make_pair(0,t);
      tmp_prev = make_pair(0, t-1);
      TRAVEL.add_edge(tmp_pair, tmp_prev);
    }
    for(unsigned j = 1; j < col; ++j){
      for(unsigned i = 1; i < row; ++i){
        if(j == 1){
          _left = LOCATION_PEN[i][j-1] + (-0.05);
          _diag = LOCATION_PEN[i-1][j-1] + get_penalty(_ref[j],_que[i]);
          //cout << "[" << _ref[j] << ":" << _que[i] << "]" << get_penalty(_ref[j], _que[i]);

          tmp_pair = make_pair(i, j);
          
          tmp_up = make_pair(i-1, j);
          tmp_left = make_pair(i,j-1);
          tmp_diag = make_pair(i-1,j-1);
          
          
            if(TRAVEL.adjacent(make_pair(i-1,j),make_pair(i-2,j))){
              _up = LOCATION_PEN[i-1][j] + (-0.05);
            }
            else{
              _up = LOCATION_PEN[i-1][j] + (-0.2);
            }
          
          max = max_value(_up, _diag);
          max = max_value(max, _left);
          LOCATION_PEN[i][j] = max;
        
          if(max == _up && max == _left && max == _diag){
            TRAVEL.adjacent(tmp_pair, tmp_up);
          }
          else if(max == _up && max == _left && max != _diag){
            TRAVEL.add_edge(tmp_pair, tmp_up);
          }
          else if(max != _up && max == _left && max == _diag){
            TRAVEL.add_edge(tmp_pair, tmp_left);
          }
          else if(max == _up && max != _left && max == _diag){
            TRAVEL.add_edge(tmp_pair, tmp_up);
          }
          else if(max == _up && max != _left && max != _diag){
            TRAVEL.add_edge(tmp_pair, tmp_up);
          }
          else if(max != _up && max == _left && max != _diag){
            TRAVEL.add_edge(tmp_pair, tmp_left);
          }
          else if(max != _up && max != _left && max == _diag){
            TRAVEL.add_edge(tmp_pair, tmp_diag);
          }
        
          
        }
        else{
          if(i == 1){
            _up = -0.2;
          }
          else{
            if(TRAVEL.adjacent(make_pair(i-1,j),make_pair(i-2,j))){
              _up = LOCATION_PEN[i-1][j] + (-0.05);
            }
            else{
              _up = LOCATION_PEN[i-1][j] + (-0.2);
            }
          }
          
           _diag = LOCATION_PEN[i-1][j-1] + get_penalty(_ref[j],_que[i]);
           
           if(TRAVEL.adjacent(make_pair(i,j-1), make_pair(i, j-2))){
             _left = LOCATION_PEN[i][j-1] + (-.05);
           }
           else{
             _left = LOCATION_PEN[i][j-1] + (-0.2);
           }
           tmp_pair = make_pair(i, j);
          
           tmp_up = make_pair(i-1, j);
           tmp_left = make_pair(i,j-1);
           tmp_diag = make_pair(i-1,j-1);
           //cout << _left << ' ' << _diag << ' ' << _up << endl;
           max = max_value(_up, _diag);
           max = max_value(max, _left);
           LOCATION_PEN[i][j] = max;
           if(max == _up && max == _left && max == _diag){
             TRAVEL.adjacent(tmp_pair, tmp_up);
           }
           else if(max == _up && max == _left && max != _diag){
             TRAVEL.add_edge(tmp_pair, tmp_up);
           }
           else if(max != _up && max == _left && max == _diag){
             TRAVEL.add_edge(tmp_pair, tmp_left);
           }
           else if(max == _up && max != _left && max == _diag){
             TRAVEL.add_edge(tmp_pair, tmp_up);
           }
           else if(max == _up && max != _left && max != _diag){
             TRAVEL.add_edge(tmp_pair, tmp_up);
           }
           else if(max != _up && max == _left && max != _diag){
             TRAVEL.add_edge(tmp_pair, tmp_left);
           }
           else if(max != _up && max != _left && max == _diag){
             TRAVEL.add_edge(tmp_pair, tmp_diag);
           }
        }       
      }
    }
    //cout << endl << endl;
    
    //cout << "ROW: " << row << "     " << "COL: " << col << endl;
    double tmp_double = 0;

    //write_2d_vect(LOCATION_PEN, row, col);
    final_score.push_back(LOCATION_PEN[row-1][col-1]);
    
    //display_dna(const vector<vector<double> >&A, const graph& B,
    
    if(int_flag == 1)
    {
      cout << "----------DNA SEQUENCE----------" << endl;
      vector<char>final_ref;
      vector<char>final_que;
      vector<char>gap;
      int ik = 0;
      int jk = 0;
      int cur_i = row-1;
      int cur_j = col-1;
    
        while(cur_i != 0 || cur_j != 0){
          
            ik = TRAVEL.print_i(make_pair(cur_i, cur_j));
            jk = TRAVEL.print_j(make_pair(cur_i, cur_j));
            //cout << '[' << cur_i << ':' << cur_j << ']';
            
            if((cur_i - ik == 1) && (cur_j -jk == 0)){
              final_ref.push_back('-');
              final_que.push_back(_que[cur_i]);
              gap.push_back(' ');
              //cout << "HERE";
            }else if((cur_i - ik == 1) && (cur_j-jk ==1)){
              final_ref.push_back(_ref[cur_j]);
              final_que.push_back(_que[cur_i]);
              gap.push_back('|');
              //cout << "eeee";
            }else if((cur_i-ik == 0) && (cur_j-jk == 1)){
              final_ref.push_back(_ref[cur_j]);
              final_que.push_back('-');
              gap.push_back(' ');
              //cout << "kkkk";
            }
            cur_i = ik;
            cur_j = jk;
            //cout << '[' << cur_i << ':' << cur_j << ']' << endl;
          
          
        }
        write_vect(final_ref);
        cout << endl;
        write_vect(gap);
        cout << endl;
        write_vect(final_que);
        cout << endl << LOCATION_PEN[row-1][col-1] << endl << name[name.size()-1] << endl << endl << endl;
    }
    
 //   --------------------------------------------------------alignment flag!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    _ref.clear();
    /*----------- CALCULATION BEFORE THIS LINE ------------------------*/
    
    LOCATION_PEN.clear();
  }
  //here, the graph is done.
  
  //-----------------FILL FINAL SORTED VECTOR--------------------------------
  vector< pair<double,string> > final_sorted;
  for(int i = 0; i < name.size(); ++i)
  {
      final_sorted.push_back(make_pair(final_score[i],name[i]));
  }
  //--------------SORT FINAL SORTED VECTOR-----------------------------------
  int size_of_final_sorted = final_sorted.size();
  std::sort(final_sorted.begin(),final_sorted.end(),pairCompare);
  //--------------OUTPUT FINAL SORTED VECTOR---------------------------------
  int i_output;
  int output_count = 1;
  bool output_flag = false;
  //int_print_size = argv[3]
  cout << "----------TOP SEQUENCE----------" << endl;
  if(int_print_size >= final_sorted.size())
  {
    output_flag = true;
    i_output = final_sorted.size()-1;
  }
  else
    i_output = int_print_size;
    
  if(output_flag == true)
  {
      for(; i_output >= 0; --i_output)
      {
        cout << output_count << " * " << final_sorted[i_output].first 
             << " * " << final_sorted[i_output].second << endl;
        output_count++;
      }
  }
  else
  {
      for(; i_output > 0; --i_output)
      {
        cout << output_count << " * " << final_sorted[i_output].first 
             << " * " << final_sorted[i_output].second << endl;
        output_count++;
        
        
        
      }
  }
  cout << endl;    
  
  ifs_ref.close();
  ifs_que.close();
  
}

int main(int argc, char* argv[]){
  /*
  for(unsigned int i = 0; i < argc; ++i){
    cout << argv[i] << ' ';
  }*/
  if(argc < 5){
    cout << "ERROR command line" << endl;
    return 0;
  }
  else{
  cout << endl;
  write_txt(argv[1], argv[2], argv[3], argv[4]);
}
  return 0;
}