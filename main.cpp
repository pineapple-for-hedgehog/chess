#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <string>
#include <vector>
#include <algorithm>
#include <windows.h>

using namespace std;

char A[9][9]{
{'8','r','h','b','q','k','b','h','r'},
{'7','p','p','p','p','p','p','p','p'},
{'6','0','0','0','0','0','0','0','0'},
{'5','0','0','0','0','0','0','0','0'},
{'4','0','0','0','0','0','0','0','0'},
{'3','0','0','0','0','0','0','0','0'},
{'2','P','P','P','P','P','P','P','P'},
{'1','R','H','B','Q','K','B','H','R'},
{' ','A','B','C','D','E','F','G','H'}
};
vector <int> numbers_for_bishop = {2, 8, 18, 32, 50, 72, 98}; // для проверки на диагональ слона
string up = "PRHBQK0"; // для проверки на взятие своих фигур
string down = "prhbqk0";
int determine = 0; //счётчик для определения противника. Белые фигуры(Верхний регистр) - нечётные; чёрные фигуры(нижний регистр) - чётные

struct chess_figures{
	bool define_figure(int i, int j, int new_i, int new_j){ 
			/*определяет тип фигуры для последущего вызова конкретной функции. 
			Если ход возможен, то возвращает true; 
			если ход невозможен или клетка пуста, то - false */
			bool flag = false;
			if (A[i][j] == 'P' || A[i][j] == 'p') { return flag = pawn_move(i, j, new_i, new_j); }
			if (A[i][j] == 'R' || A[i][j] == 'r') { return flag = rook_move(i, j, new_i, new_j); }
			if (A[i][j] == 'B' || A[i][j] == 'b') { return flag = bishop_move(i, j, new_i, new_j); }
			if (A[i][j] == 'H' || A[i][j] == 'h') { return flag = horse_move(i, j, new_i, new_j); }
			if (A[i][j] == 'K' || A[i][j] == 'k') { return flag = king_move(i, j, new_i, new_j); }
			if (A[i][j] == 'Q' || A[i][j] == 'q') { return flag = queen_move(i, j, new_i, new_j); }
			return flag;
	}
	bool pawn_move(int i, int j, int new_i, int new_j){ //без учёта взятия на проходе
		if (!(determine % 2)){// black
	 		if (A[i][j] != 'p') return false; // проверка на регистр
			if (j == new_j){
				if (new_i == i+1) return true;
				if ((new_i == i + 2 && i == 1)&& A[i+1][j] == '0') return true;

			}
			else if (new_i == i + 1 && A[new_i][new_j] != '0'){
				if (new_j == j + 1 || new_j == j - 1){
					for (int k = 0; k < up.size(); k++){
						if (A[new_i][new_j] == up[k]) return true;
					}
				}
				else return false;
			}
			}
		if (determine % 2){ // WHITE
			if (A[i][j] != 'P') return false; // проверка на регистр
			if (j == new_j){
				if (new_i == i-1 ) return true;
				if ((new_i == i - 2 && i == 6) && A[i-1][j] == '0') return true;
			}
			else if (new_i == i - 1 && A[new_i][new_j] != '0'){
				if (new_j == j + 1 || new_j == j - 1){
					for (int k = 0; k < down.size(); k++){
						if (A[new_i][new_j] == down[k]) return true;
					}
				}
				else return false;
			}
			}
		return false;
	}

	bool rook_move(int i, int j, int new_i, int new_j) {
			if (!(determine % 2)){//black
				if (A[i][j] != 'r') return false; // проверка на регистр
				if (new_j == j){  //ход по вертикали
					if (i > new_i){
						for (int h = i - 1; h > new_i; h-- ) if (A[h][new_j] != '0') return false; //проверяется есть ли фигуры, мешающие перестановке
						for (int k = 0; k < up.size(); k++) if (A[new_i][new_j] == up[k]) return true;
					}
					else if (i < new_i){
						for (int h = i + 1; h < new_i; h++) if (A[h][new_j] != '0') return false;//проверяется есть ли фигуры, мешающие перестановке
						for (int k = 0; k < up.size(); k++) if (A[new_i][new_j] == up[k]) return true;
					} 
				}
				if (new_i == i){ //ход по горизонтали
					if (j > new_j){
						for (int h = j - 1; h > new_j; h--) if (A[new_i][h] != '0') return false;//проверяется есть ли фигуры, мешающие перестановке
						for (int k = 0; k < up.size(); k++) if (A[new_i][new_j] == up[k]) return true;
					}
					else if (j < new_j){
						for (int h = j + 1; h < new_j; h++) if (A[new_i][h] != '0') return false;//проверяется есть ли фигуры, мешающие перестановке
						for (int k = 0; k < up.size(); k++) if (A[new_i][new_j] == up[k]) return true;
					}	
				
				}
			}
			if (determine % 2){ // WHITE
				if (A[i][j] != 'R') return false;// проверка на регистр
				if (new_j == j){ //ход по вертикали
					if (i > new_i){
						for (int h = i - 1; h > new_i; h-- ) if (A[h][new_j] != '0') return false; //проверяется есть ли фигуры, мешающие перестановке
						for (int k = 0; k < down.size(); k++) if (A[new_i][new_j] == down[k]) return true;
					}
					else if (i < new_i){
						for (int h = i + 1; h < new_i; h++) if (A[h][new_j] != '0') return false; //проверяется есть ли фигуры, мешающие перестановке
						for (int k = 0; k < down.size(); k++) if (A[new_i][new_j] == down[k]) return true;
					} 
				}
				if (new_i == i){ // ход по горизонтали
					if (j > new_j){
						for (int h = j - 1; h > new_j; h--) if (A[new_i][h] != '0') return false; //проверяется есть ли фигуры, мешающие перестановке
						for (int k = 0; k < down.size(); k++) if (A[new_i][new_j] == down[k]) return true;
					}
					else if (j < new_j){
						for (int h = j + 1; h < new_j; h++) if (A[new_i][h] != '0') return false; //проверяется есть ли фигуры, мешающие перестановке
						for (int k = 0; k < down.size(); k++) if (A[new_i][new_j] == down[k]) return true;
					}	
				
				}
			}
			return false;
	}
	
	bool bishop_move(int i, int j, int new_i, int new_j) {
		bool flag = false;
		int square = (i - new_i)*(i - new_i) + (j-new_j)*(j-new_j);
		for (int m = 0; m < numbers_for_bishop.size(); m++){ //проверка на возможность хода по диагонали
			if (square == numbers_for_bishop[m]){
				flag = true; 
				break;
			}
		}
		if (flag){
			if (j < new_j){ // проверка на наличие фигур, мешающих перестановке
				if (i > new_i){
					for (int ii = i - 1,  jj = j + 1; ii > new_i, jj < new_j; ii--, jj++){
						if (A[ii][jj] != '0') return false;
					}
				}
				if (i < new_i){
					for (int ii = i + 1,  jj = j + 1; ii < new_i, jj < new_j; ii++, jj++){
						if (A[ii][jj] != '0') return false;
					}				
				}
			}
			else if (j > new_j){// проверка на наличие фигур, мешающих перестановке
				if (i > new_i){
					for (int ii = i - 1, jj = j - 1; ii > new_i, jj > new_j; ii-- , jj--){
						if (A[ii][jj] != '0') return false;
					}
				}
				if (i < new_i){
					for (int ii = i + 1, jj = j - 1; ii < new_i, jj > new_j; ii++ , jj--){
						if (A[ii][jj] != '0') return false;
					}
				}
			}

				if (!(determine % 2)){//black
					if (A[i][j] != 'b') return false; // проверка регистра
						for (int k = 0; k < up.size(); k++) 
							if (A[new_i][new_j] == up[k]) return true;
				}
				if(determine % 2) { //WHITE
					if (A[i][j] != 'B') return false; // проверка регистра
						for (int k = 0; k < down.size(); k++) 
							if (A[new_i][new_j] == down[k]) return true;
				}
		}
		return false;
	}

	bool horse_move(int i, int j, int new_i, int new_j) {
		if (!(determine % 2)){// black
			if (A[i][j] != 'h') return false; // проверка регистра
			bool flag = false;
			for (int k = 0; k < up.size(); k++){ // проверка на взятие своих фигур
					if (A[new_i][new_j] == up[k]){ 
						flag = true;
						break;
					}
				}
			if (flag){
				if (new_j == j + 1){
					if (new_i == i - 2) return true;
					if (new_i == i + 2) return true;
				}
				if (new_j == j - 1){
					if (new_i == i - 2) return true;
					if (new_i == i + 2) return true;
				}
				if (new_j == j + 2){
					if (new_i == i + 1) return true;
					if (new_i == i - 1) return true;
				}
				if (new_j == j - 2){
					if (new_i == i + 1) return true;
					if (new_i == i - 1) return true;
				}
				return false;
			}
			else return false;
			
		}
		if (determine % 2){ //WHITE
			if (A[i][j] != 'H') return false; // проверка регистра
			bool flag = false;
			for (int k = 0; k < down.size(); k++){ // проверка на взятие своих фигур
					if (A[new_i][new_j] == down[k]){
						flag = true;
						break;
					}
				}
			if (flag){
				if (new_j == j + 1){
					if (new_i == i - 2) return true;
					if (new_i == i + 2) return true;
				}
				if (new_j == j - 1){
					if (new_i == i - 2) return true;
					if (new_i == i + 2) return true;
				}
				if (new_j == j + 2){
					if (new_i == i + 1) return true;
					if (new_i == i - 1) return true;
				}
				if (new_j == j - 2){
					if (new_i == i + 1) return true;
					if (new_i == i - 1) return true;
				}
				return false;
			} 
			else return false;
		}
		return false;
	}

	bool king_move(int i, int j, int new_i, int new_j) {
        if (!(determine%2)){ //black
            if (A[i][j] != 'k') return false; // проверка на регистр
            if (new_j == j){
	        		if (new_i == i + 1){
	        			if (!(determine%2)) for (int k = 0; k < up.size(); k++) if (A[new_i][new_j] == up[k]) return true;
	        		}
	        		if (new_i == i - 1){
	        			if (!(determine%2)) for (int k = 0; k < up.size(); k++) if (A[new_i][new_j] == up[k]) return true;			
	        		}
	        		return false;
	        	}
	        if (new_j == j + 1){
	        	if (new_i == i + 1){
	        		if (!(determine%2)) for (int k = 0; k < up.size(); k++) if (A[new_i][new_j] == up[k]) return true;
	        	}
	        	if (new_i == i - 1){
	        		if (!(determine%2)) for (int k = 0; k < up.size(); k++) if (A[new_i][new_j] == up[k]) return true;
	        	}
	        	if (new_i == i){
	        		if (!(determine%2)) for (int k = 0; k < up.size(); k++) if (A[new_i][new_j] == up[k]) return true;
	        	}
	        	return false; 
	            }
	        if (new_j == j - 1){
		    	if (new_i == i + 1){
		    		if (!(determine%2)) for (int k = 0; k < up.size(); k++) if (A[new_i][new_j] == up[k]) return true;
		    	}
		    	if (new_i == i - 1){
		    		if (!(determine%2)) for (int k = 0; k < up.size(); k++) if (A[new_i][new_j] == up[k]) return true;
		    	}
		    	if (new_i == i){
		    		if (!(determine%2)) for (int k = 0; k < up.size(); k++) if (A[new_i][new_j] == up[k]) return true;
		    	}
		    	return false; 
                }
            }
        
        if (determine%2){ // WHITE
            if (A[i][j] != 'K') return false; // проверка регистра
 		    if (new_j == j){
		    	if (new_i == i + 1){
		    		if (determine%2) for (int k = 0; k < down.size(); k++) if (A[new_i][new_j] == down[k]) return true;
		    	}
		    	if (new_i == i - 1){
		    		if (determine%2) for (int k = 0; k < down.size(); k++) if (A[new_i][new_j] == down[k]) return true;				
		    	}
		    	return false; 
		    }
		    if (new_j == j + 1){
		    	if (new_i == i + 1){
		    		if (determine%2) for (int k = 0; k < down.size(); k++) if (A[new_i][new_j] == down[k]) return true; 
		    	}
		    	if (new_i == i - 1){
		    		if (determine%2) for (int k = 0; k < down.size(); k++) if (A[new_i][new_j] == down[k]) return true;
		    	}
		    	if (new_i == i){
		    		if (determine%2) for (int k = 0; k < down.size(); k++) if (A[new_i][new_j] == down[k]) return true;
		    	}
		    	return false; 
		    }
		    if (new_j == j - 1){
		    	if (new_i == i + 1){
		    		if (determine%2) for (int k = 0; k < down.size(); k++) if (A[new_i][new_j] == down[k]) return true;
		    	}
		    	if (new_i == i - 1){
		    		if (determine%2) for (int k = 0; k < down.size(); k++) if (A[new_i][new_j] == down[k]) return true;
		    	}
		    	if (new_i == i){
		    		if (determine%2) for (int k = 0; k < down.size(); k++) if (A[new_i][new_j] == down[k]) return true;
		    	}
		    	return false; 
		    }           
            }
        return false;
    }

	bool queen_move(int i, int j, int new_i, int new_j) {
    		if (!(determine%2)){ // black
        	if (A[i][j] != 'q') return false; // проверка на регистр
        	if (true){ //проверка на ход ладьи
        	    if (new_j == j){ // ход по вертикали
				if (i > new_i){
					for (int h = i - 1; h > new_i; h-- ) if (A[h][new_j] != '0') return false; // проверяется есть ли фигуры, мешающие перестановке(вертикаль)
					for (int k = 0; k < up.size(); k++) if (A[new_i][new_j] == up[k]) return true;
				}
				else if (i < new_i){
					for (int h = i + 1; h < new_i; h++) if (A[h][new_j] != '0') return false; // проверяется есть ли фигуры, мешающие перестановке(вертикаль)
					for (int k = 0; k < up.size(); k++) if (A[new_i][new_j] == up[k]) return true;
				} 
    			}
    			if (new_i == i){ // ход по горизонтали
				if (j > new_j){
					for (int h = j - 1; h > new_j; h--) if (A[new_i][h] != '0') return false; // проверяется есть ли фигуры, мешающие перестановке
					for (int k = 0; k < up.size(); k++) if (A[new_i][new_j] == up[k]) return true;
				    }
				else if (j < new_j){
					for (int h = j + 1; h < new_j; h++) if (A[new_i][h] != '0') return false;  // проверяется есть ли фигуры, мешающие перестановке
					for (int k = 0; k < up.size(); k++) if (A[new_i][new_j] == up[k]) return true; 
				    }	

    			}            
    	    }
    	    if (true){ //проверка на ход слона
    	        bool flag = false;
    	        int square = (i - new_i)*(i - new_i) + (j-new_j)*(j-new_j); // для проверки на ход по диагонали
    	        for (int m = 0; m < numbers_for_bishop.size(); m++){ //проверка на возможность хода по диагонали
    	        	if (square == numbers_for_bishop[m]){
    	        		flag = true; 
    	        		break;
    	        	}
    	        }
    	        if (flag){ // проверка на наличие фигур, мешающих перестановке
                if (j < new_j){ 
                	if (i > new_i){
            		for (int ii = i - 1,  jj = j + 1; ii > new_i, jj < new_j; ii--, jj++){
            			if (A[ii][jj] != '0') return false;
            		}
                	}
                	if (i < new_i){
            		for (int ii = i + 1,  jj = j + 1; ii < new_i, jj < new_j; ii++, jj++){
            			if (A[ii][jj] != '0') return false;
            		}				
                	}
                }
                else if (j > new_j){
            	if (i > new_i){
            		for (int ii = i - 1, jj = j - 1; ii > new_i, jj > new_j; ii-- , jj--){
            			if (A[ii][jj] != '0') return false;
            		}
            	}
            	if (i < new_i){
            		for (int ii = i + 1, jj = j - 1; ii < new_i, jj > new_j; ii++ , jj--){
            			if (A[ii][jj] != '0') return false;
            		}
            	}
                }
                }
    	        }
    			for (int k = 0; k < up.size(); k++) if (A[new_i][new_j] == up[k]) return true; //проверка на взятие фигур другого регистра
    	    return false;
    	}
    		if (determine%2){ // WHITE
        	if (A[i][j] != 'Q') return false; // проверка на регистр
        	if (true){ //проверка на ход ладьи
        	    if (new_j == j){ // ход по вертикали
				    if (i > new_i){
				    	for (int h = i - 1; h > new_i; h-- ) if (A[h][new_j] != '0') return false; // проверяется есть ли фигуры, мешающие перестановке(вертикаль)
				    	for (int k = 0; k < down.size(); k++) if (A[new_i][new_j] == down[k]) return true;
				    }
				    else if (i < new_i){
				    	for (int h = i + 1; h < new_i; h++) if (A[h][new_j] != '0') return false; // проверяется есть ли фигуры, мешающие перестановке(вертикаль)
				    	for (int k = 0; k < down.size(); k++) if (A[new_i][new_j] == down[k]) return true;
				    } 
    			}
    			if (new_i == i){ // ход по горизонтали
				    if (j > new_j){
				    	for (int h = j - 1; h > new_j; h--) if (A[new_i][h] != '0') return false; // проверяется есть ли фигуры, мешающие перестановке
				    	for (int k = 0; k < down.size(); k++) if (A[new_i][new_j] ==down[k]) return true;
				        }
				    else if (j < new_j){
				    	for (int h = j + 1; h < new_j; h++) if (A[new_i][h] != '0') return false;  // проверяется есть ли фигуры, мешающие перестановке
				    	for (int k = 0; k < down.size(); k++) if (A[new_i][new_j] == down[k]) return true; 
				        }	
    			}            
        	}
        	if (true){ //проверка на ход слона
        	    bool flag = false;
        	    int square = (i - new_i)*(i - new_i) + (j-new_j)*(j-new_j); // для проверки на ход по диагонали
        	    for (int m = 0; m < numbers_for_bishop.size(); m++){ //проверка на возможность хода по диагонали
        	    	if (square == numbers_for_bishop[m]){
        	    		flag = true; 
        	    		break;
        	    	}
        	    }
        	    if (flag){// проверка на наличие фигур, мешающих перестановке
        	        if (j < new_j){ 
        	        	if (i > new_i){
        	    		for (int ii = i - 1,  jj = j + 1; ii > new_i, jj < new_j; ii--, jj++){
        	    			if (A[ii][jj] != '0') return false;
        	    		}
        	        	}
        	        	if (i < new_i){
        	    		for (int ii = i + 1,  jj = j + 1; ii < new_i, jj < new_j; ii++, jj++){
        	    			if (A[ii][jj] != '0') return false;
        	    		}				
        	        	}
        	        }
        	        else if (j > new_j){
        	    		if (i > new_i){
        	    		for (int ii = i - 1, jj = j - 1; ii > new_i, jj > new_j; ii-- , jj--){
        	    			if (A[ii][jj] != '0') return false;
        	    		}
        	    		}
        	    		if (i < new_i){
        	    		for (int ii = i + 1, jj = j - 1; ii < new_i, jj > new_j; ii++ , jj--){
        	    			if (A[ii][jj] != '0') return false;
        	    		}
        	    		}
        	        }
        	        }
        	    }
    			for (int k = 0; k < down.size(); k++) if (A[new_i][new_j] == down[k]) return true; //проверка на взятие фигур другого регистра
        	return false;
    	}
    	return false;
	}
};

void print(){
		cout << "\n     A B C D E F G H" << endl;
		for (int i = 0; i < 9; i++) {
			cout << "  ";
        	for (int j = 0; j < 9; j++) cout << setw(2) << A[i][j];
			if (i != 8) cout << " " << 8 - i;
     		cout << endl;
		}
		cout << endl;
}

void rearranging(int i, int j, int new_i, int new_j){ //перестановка фигуры
		A[new_i][new_j] = A[i][j];
		A[i][j] = '0';
}

int switch_char (char ch, bool &flag){ 	//определяет j в матрице (столбец)
        int j;
		switch (ch){
			case 'A':{
				j = 1;
				break;
			}
			case 'a':{
				j = 1;
				break;
			}
			case 'B':{
				j = 2;
				break;
			}
			case 'b':{
				j = 2;
				break;
			}
			case 'C':{
				j = 3;
				break;
			}
			case 'c':{
				j = 3;
				break;
			}
			case 'D':{
				j = 4;
				break;
			}
			case 'd':{
				j = 4;
				break;
			}
			case 'E':{
				j = 5;
				break;
			}
			case 'e':{
				j = 5;
				break;
			}
			case 'F':{
				j = 6;
				break;
			}
			case 'f':{
				j = 6;
				break;
			}
			case 'G':{
				j = 7;
				break;
			}
			case 'g':{
				j = 7;
				break;
			}
			case 'H':{
				j = 8;
				break;
			}
			case 'h':{
				j = 8;
				break;
			}
			default:{
				flag = 0;
				cout << "wrong checkerboard cage.(char)" << endl;
				break;
			}
		}
    return j;
}

int switch_int (char int_, bool &flag){ // определяет i в матрице (строка) 
    int i;
	switch (int_){
		case '1':{
			i = 7;
			break;
		}
		case '2':{
			i = 6;
			break;
		}
		case '3':{
			i = 5;
			break;
		}
		case '4':{
			i = 4;
			break;
		}
		case '5':{
			i = 3;
			break;
		}
		case '6':{
			i = 2;
			break;
		}
		case '7':{
			i = 1;
			break;
		}
		case '8':{
			i = 0;
			break;
		}
		default:{
			flag = 0;
			cout << "wrong checkerboard cage.(int)" << endl;
			break;
		}
	}
    return i;
}

int main(){
	print(); // вывод матрицы на консоль
	/*determine = 0 - счётчик для определения противника
		белые фигуры(верхний регистр) - нечётные; 
		чёрные фигуры(нижний регистр) - чётные*/
	char ch, a, new_ch, new_a; // номера клетки, введёные с консоли
	/*  ch и a - координаты (буква и цифра) текущего местоположения фигуры
		new_ch и new_a - координаты (буква и цифра) клетки, на которую нужно переставить фигуру*/
    int i, j, new_i, new_j;	//обработаннные индексы матрицы (числа). 
	/*	i - строка (cooтветствует цифрам); 
		j - столбец (соответствует буквам);
		new_i и new_j - обработанные координаты клетки, на которую нужно переставить фигуру*/
	bool flag = 1, for_wrong_move; 
	chess_figures step;

	while(true){
		for_wrong_move = 1;
		determine++;
		if ((determine % 2)) cout << " white's move: ";
		else cout << " black's move: ";
		do{ // текущее местонахождение фигуры
		flag = 1;
		cin >> ch >> a;
		j = switch_char(ch, flag);
		if (flag) i = switch_int(a, flag);
		if (flag) {
			if (A[i][j] == '0'){
				cout << " error: empty cell.\n Re-entry: ";
				flag = 0;
			}
		}
		} while (!flag);
	
    	do{ // место, куда нужно переставить фигуру
		flag = 1;
		cin >> new_ch >> new_a;
		new_j = switch_char(new_ch, flag);
		if (flag) new_i = switch_int(new_a, flag);
		} while (!flag);
		
		if (step.define_figure(i, j, new_i, new_j)){
	    rearranging (i, j, new_i, new_j); // перемещение фигуры
		} 
		else {
		for_wrong_move = 0;
		cout << " wrong move" << endl;
		determine--;
		continue;
		}
		if (for_wrong_move) system("cls");
		print();
	}

    system("pause");
}