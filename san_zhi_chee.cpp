#include <iostream>
#include "san_zhi_chee.hpp"
#include <fstream>
#include <string>

using namespace std;
void print_board(int board[SIZE][SIZE]){
    for(int i =0 ; i <SIZE ;i++){
        for(int j = 0; j < SIZE; j++){
            if(board[i][j] == BLACK){
                cout << "\tB" ;
            }else if(board[i][j] == WHITE){
                cout << "\tW" ;
            }else{
                cout << "\t " ;
            }
        }
        cout << "\n" ;
    }
}

int is_win_lose(chess c[SIZE]){

    int dx = c[2].x - c[1].x;
    int dy = c[2].y - c[1].y;
    int dx2 = c[2].x - c[0].x;
    int dy2 = c[2].y - c[0].y;
    if(dx == 0 || dy == 0){
        if(dx == 0 && dx == dx2){
            cout << c[2].x << " Vertical Line" << endl;
            return c[2].color;
        }else if(dy == 0 && dy == dy2){
            cout << c[2].y << " Horizontal Line" << endl;
            return c[2].color;
        }
    }else{
        if(dx * dy2 == dx2 * dy){
            cout << "/ Line" << endl;
            return c[2].color;
        }

    }
    return 0;
    
}
void copy_chess(chess color_chess[SIZE],chess cp_chess[SIZE]){
    for(int i =0; i<SIZE;i++){
        chess c = color_chess[i];
        cp_chess[i].x = c.x;
        cp_chess[i].y = c.y;
        cp_chess[i].color = c.color;

    }
}
bool try_right(int board[SIZE][SIZE],chess c){
    return c.x+1 <SIZE && board[c.y][c.x+1] == 0;
}
bool try_left(int board[SIZE][SIZE],chess c){
    return c.x >0 && board[c.y][c.x-1] == 0;
}
bool try_up(int board[SIZE][SIZE],chess c){
    return c.y >0 && board[c.y-1][c.x] == 0;
}
bool try_down(int board[SIZE][SIZE],chess c){
    return c.y+1 <SIZE && board[c.y+1][c.x] == 0;
}
bool try_right_down(int board[SIZE][SIZE],chess c){
    return c.y+1 <SIZE && c.x+1 <SIZE && board[c.y+1][c.x+1] == 0;
}
bool try_right_up(int board[SIZE][SIZE],chess c){
    return c.y > 0&& c.x+1 <SIZE && board[c.y-1][c.x+1] == 0;
}
bool try_left_down(int board[SIZE][SIZE],chess c){
    return c.y+1 <SIZE && c.x > 0 && board[c.y+1][c.x-1] == 0;
}
bool try_left_up(int board[SIZE][SIZE],chess c){
    return c.y > 0 && c.x > 0 && board[c.y-1][c.x-1] == 0;
}
bool try_available_oblique(chess c){
    return ((c.y+c.x)&1) == 0;
}
int try_go(int board[SIZE][SIZE],chess my_chess[SIZE], int i){
    // try  go_right       
    if(try_right(board,my_chess[i])){
        
        go_right(board,my_chess,i);
        
        if (is_win_lose(my_chess) == my_chess[i].color){
            //win
            return RIGHT;
        }else{
            // go back
            go_left(board,my_chess,i);
        }
    }

    // try  go_left
    if(try_left(board,my_chess[i])){
        
        go_left(board,my_chess,i);
        
        if (is_win_lose(my_chess) == my_chess[i].color){
            //win
            return LEFT;
        }else{
            // go back
            go_right(board,my_chess,i);
        }
    }

    // try  go_up
    if(try_up(board,my_chess[i])){
        
        go_up(board,my_chess,i);
        
        if (is_win_lose(my_chess) == my_chess[i].color){
            //win
            return UP;
        }else{
            // go back
            go_down(board,my_chess,i);
        }
    }

    // try  go_down
    if(try_down(board,my_chess[i])){
        
        go_down(board,my_chess,i);
        
        if (is_win_lose(my_chess) == my_chess[i].color){
            //win
            return DOWN;
        }else{
            // go back
            go_up(board,my_chess,i);
        }
    }

    
    if(try_available_oblique(my_chess[i])){
        // try  go_right_down
        if(try_right_down(board,my_chess[i])){
            
            go_right_down(board,my_chess,i);
            
            if (is_win_lose(my_chess) == my_chess[i].color){
                //win
                return RIGHT_DOWN;
            }else{
                // go back
                go_left_up(board,my_chess,i);
            }
        }
        // try  go_right_up
        if(try_right_up(board,my_chess[i])){
            
            go_right_up(board,my_chess,i);
            
            if (is_win_lose(my_chess) == my_chess[i].color){
                //win
                return RIGHT_UP;
            }else{
                // go back
                go_left_down(board,my_chess,i);
            }
        }
        // try  go_left_down
        if(try_left_down(board,my_chess[i])){
            
            go_left_down(board,my_chess,i);
            
            if (is_win_lose(my_chess) == my_chess[i].color){
                //win
                return LEFT_DOWN;
            }else{
                // go back
                go_right_up(board,my_chess,i);
            }
        }
        // try  go_left_up
        if(try_left_up(board,my_chess[i])){
            
            go_left_up(board,my_chess,i);
            
            if (is_win_lose(my_chess) == my_chess[i].color){
                //win
                return LEFT_UP;
            }else{
                // go back
                go_right_down(board,my_chess,i);
            }
        }
    }
    return 0;
}
int block_line(int board[SIZE][SIZE],chess my_chess[SIZE], int i, int px, int py){
    //middle point
    
    for(int i = 0 ; i < SIZE ; i++){
        // one distance
        int dx = my_chess[i].x -px ;
        int dy = my_chess[i].y -py;
        
        if ( ((dx*dx ) ^  (dy*dy )) == 1){
            board[my_chess[i].y][my_chess[i].x] = 0;
            board[py][px] = my_chess[i].color;
            my_chess[i].x = px;
            my_chess[i].y = py;
            
            if(dx == 1){
                return LEFT;
            }
            if(dx == -1){
                return RIGHT;
            }
            if(dy == 1){
                return UP;
            }
            if(dy == -1){
                return DOWN;
            }
        }else if((((dx*dx ) &  (dy*dy )) == 1) && (((my_chess[i].x + my_chess[i].y)&1) == 0)){
            
            if(dx == 1){
                if(dy == 1){
                    return LEFT_UP;
                }
                if(dy == -1){
                    return LEFT_DOWN;
                }
                return LEFT;
            }
            if(dx == -1){
                if(dy == 1){
                    return RIGHT_UP;
                }
                if(dy == -1){
                    return RIGHT_DOWN;
                }
                return RIGHT;
            }
            
        }
        
        
    }
    return 0;
    
}
void previous_board(int board[SIZE][SIZE], chess ch[SIZE], int i, int dir){
    if(dir == RIGHT){
        go_left(board,ch,i);    
    }else if(dir == LEFT){
        go_right(board,ch,i);
    }else if(dir == UP){
        go_down(board,ch,i);
    }else if(dir == DOWN){
        go_up(board,ch,i);
    }else if(dir == RIGHT_DOWN){
        go_left_up(board,ch,i);
    }else if(dir == RIGHT_UP){
        go_left_down(board,ch,i);
    }else if(dir == LEFT_DOWN){
        go_right_up(board,ch,i);
    }else if(dir == LEFT_UP){
        go_right_down(board,ch,i);
    }
}
void sort_chess(chess my_chess[SIZE]){
    // middle chess should be last checked
    for(int i = 0 ; i < SIZE-1 ; i++){
        if((my_chess[i].x & my_chess[i].y) == 1){
            int tempX = my_chess[i].x;
            int tempY = my_chess[i].y;
            my_chess[i].x = my_chess[SIZE-1].x;
            my_chess[i].y = my_chess[SIZE-1].y;
            my_chess[SIZE-1].x = tempX;
            my_chess[SIZE-1].y = tempY;
            break;
        }
    }
}
step next_step(int board[SIZE][SIZE], int my_color, chess white[SIZE] , chess black[SIZE]){
    
    int result;
    chess my_chess[SIZE];
    chess en_chess[SIZE];
    if(my_color == WHITE){   
        copy_chess(white,my_chess);
        copy_chess(black,en_chess);
    }else{
        copy_chess(black,my_chess);
        copy_chess(white,en_chess);
    }
    result = is_win_lose(en_chess);
    
    // no win no lose
    if(result == 0){
        sort_chess(my_chess);
        cout << "before move : " << endl;
        print_board(board);
        // check robot win
        for(int i = 0; i < SIZE ; i++){
            int dir = try_go(board, my_chess,i);
            if (dir != 0){
                cout << "after move : "<< endl;
                print_board(board);
                previous_board(board, my_chess, i, dir);
                step s  = {.c = my_chess[i], .move = dir, .win = 1};
                return s;
            }
               
        }

        // find dangerous position
        cout << "after try : " << endl;
        for(int i = 0; i < SIZE ; i++){
            
            int dir = try_go(board, en_chess,i);
            if(dir != 0){
                int px = en_chess[i].x;
                int py = en_chess[i].y;
                previous_board(board, en_chess, i, dir);
                cout << "after block : " << endl;
                //block_line(board,my_chess,i,px,py);
                int block_dir = block_line(board,my_chess,i,px,py);
                if(block_dir !=0){
                    print_board(board);
                    previous_board(board, my_chess, i, block_dir);
                    step s  = {.c = my_chess[i], .move = block_dir, .win = 0};
                    return s;
                }
                break;
                
            }
        }

        //no dangerous  
        cout<< "next step" << endl;
        for(int i = 0 ; i <SIZE ;i++){
            if(try_available_oblique(my_chess[i])){
                if(try_right_up(board,my_chess[i])){
                    go_right_up(board,my_chess,i);
                    int dir = 0;
                    for(int j = 0; j < SIZE ; j++){
                        dir = try_go(board, en_chess,j);
                        if(dir != 0){
                            previous_board(board,en_chess,j,dir);
                            break;
                        }
                    }
                    go_left_down(board,my_chess,i);
                    if(dir == 0){

                        step s  = {.c = my_chess[i], .move = RIGHT_UP, .win = 0};
                        return s;
                    }
                }
                if(try_right_down(board,my_chess[i])){
                    go_right_down(board,my_chess,i);
                    int dir = 0;
                    for(int j = 0; j < SIZE ; j++){
                        dir = try_go(board, en_chess,j);
                        if(dir != 0){
                            previous_board(board,en_chess,j,dir);
                            break;
                        }
                    }
                    go_left_up(board,my_chess,i);
                    if(dir == 0){

                        step s  = {.c = my_chess[i], .move = RIGHT_DOWN, .win = 0};
                        return s;
                    }
                }
                if(try_left_up(board,my_chess[i])){
                    go_left_up(board,my_chess,i);
                    int dir = 0;
                    for(int j = 0; j < SIZE ; j++){
                        dir = try_go(board, en_chess,j);
                        if(dir != 0){
                            previous_board(board,en_chess,j,dir);
                            break;
                        }
                    }
                    go_right_down(board,my_chess,i);
                    if(dir == 0){

                        step s  = {.c = my_chess[i], .move = LEFT_UP, .win = 0};
                        return s;
                    }
                }
                if(try_left_down(board,my_chess[i])){
                    go_left_down(board,my_chess,i);
                    int dir = 0;
                    for(int j = 0; j < SIZE ; j++){
                        dir = try_go(board, en_chess,j);
                        if(dir != 0){
                            previous_board(board,en_chess,j,dir);
                            break;
                        }
                    }
                    go_right_up(board,my_chess,i);
                    if(dir == 0){

                        step s  = {.c = my_chess[i], .move = LEFT_DOWN, .win = 0};
                        return s;
                    }
                }
            }
            if(try_right(board,my_chess[i])){
                
                go_right(board,my_chess,i);
                int dir = 0;
                for(int j = 0; j < SIZE ; j++){
                    dir = try_go(board, en_chess,j);
                    if(dir != 0){
                        previous_board(board,en_chess,j,dir);
                        break;
                    }
                }
                go_left(board,my_chess,i);
                if(dir == 0){

                    step s  = {.c = my_chess[i], .move = RIGHT, .win = 0};
                    return s;
                }
            }
            if(try_left(board,my_chess[i])){
                go_left(board,my_chess,i);
                int dir = 0;
                for(int j = 0; j < SIZE ; j++){
                    dir = try_go(board, en_chess,j);
                    if(dir != 0){
                        previous_board(board,en_chess,j,dir);
                        break;
                    }
                }
                go_right(board,my_chess,i);
                if(dir == 0){

                    step s  = {.c = my_chess[i], .move = LEFT, .win = 0};
                    return s;
                }
            }
            if(try_up(board,my_chess[i])){
                go_up(board,my_chess,i);
                int dir = 0;
                for(int j = 0; j < SIZE ; j++){
                    dir = try_go(board, en_chess,j);
                    if(dir != 0){
                        previous_board(board,en_chess,j,dir);
                        break;
                    }
                }
                go_down(board,my_chess,i);
                if(dir == 0){

                    step s  = {.c = my_chess[i], .move = UP, .win = 0};
                    return s;
                }
            }
            if(try_down(board,my_chess[i])){
                go_down(board,my_chess,i);
                int dir = 0;
                for(int j = 0; j < SIZE ; j++){
                    dir = try_go(board, en_chess,j);
                    if(dir != 0){
                        previous_board(board,en_chess,j,dir);
                        break;
                    }
                }
                go_up(board,my_chess,i);
                if(dir == 0){

                    step s  = {.c = my_chess[i], .move = DOWN, .win = 0};
                    return s;
                }
            }    
        }
    }else if(result != my_color){
        // lose
        step s = {.c = my_color,.move = RIGHT, .win = -1};
        return s;
    }
}
// >>
void go_right(int board[SIZE][SIZE],chess c[SIZE], int i){
    board[c[i].y][c[i].x] = 0;
    c[i].x += 1 ; 
    board[c[i].y][c[i].x] = c[i].color;
}
// <<
void go_left(int board[SIZE][SIZE],chess c[SIZE], int i){
    board[c[i].y][c[i].x] = 0;
    c[i].x -= 1 ; 
    board[c[i].y][c[i].x] = c[i].color;
}
// ^^
void go_up(int board[SIZE][SIZE],chess c[SIZE], int i){
    board[c[i].y][c[i].x] = 0;
    c[i].y -= 1 ; 
    board[c[i].y][c[i].x] = c[i].color;
}
// VV
void go_down(int board[SIZE][SIZE],chess c[SIZE], int i){
    board[c[i].y][c[i].x] = 0;
    c[i].y += 1 ; 
    board[c[i].y][c[i].x] = c[i].color;
}
// right_up
void go_right_up(int board[SIZE][SIZE],chess c[SIZE], int i){
    board[c[i].y][c[i].x] = 0;
    c[i].y -= 1 ;
    c[i].x += 1 ; 
    board[c[i].y][c[i].x] = c[i].color;
}
// right down
void go_right_down(int board[SIZE][SIZE],chess c[SIZE], int i){
    board[c[i].y][c[i].x] = 0;
    c[i].y += 1 ;
    c[i].x += 1 ; 
    board[c[i].y][c[i].x] = c[i].color;
}
// left up
void go_left_up(int board[SIZE][SIZE],chess c[SIZE], int i){
    board[c[i].y][c[i].x] = 0;
    c[i].y -= 1 ;
    c[i].x -= 1 ; 
    board[c[i].y][c[i].x] = c[i].color;
}
// left down
void go_left_down(int board[SIZE][SIZE],chess c[SIZE], int i){
    board[c[i].y][c[i].x] = 0;
    c[i].y += 1 ;
    c[i].x -= 1 ; 
    board[c[i].y][c[i].x] = c[i].color;
}
int main(){
    
    ifstream infile("board.txt");
    int board[SIZE][SIZE];
    int w_c = 0;
    int b_c = 0;
    chess black[SIZE];
    chess white[SIZE];
    string move[] = {"RIGHT", "LEFT" , "UP" , "DOWN" ,"RIGHT_UP", "RIGHT_DOWN", "LEFT_UP", "LEFT_DOWN"}; 
    //initialize
    for (int i = 0 ; i < SIZE;i++){
        infile >> board[i][0] >> board[i][1] >> board[i][2]; 
    } 
    for (int i = 0 ; i < SIZE;i++){
        for (int j = 0 ; j < SIZE;j++){
            if(board[i][j] == BLACK){
                chess c;
                c.x = j;
                c.y = i;
                c.color = BLACK;
                black[b_c] = c;
                b_c += 1;
            }else if(board[i][j] == WHITE){
                chess c;
                c.x = j;
                c.y = i;
                c.color = WHITE;
                white[w_c] = c;
                w_c += 1;
            }
        }
    }
    
    //print_board(board);
    step n_p ;
    n_p = next_step(board,WHITE,white,black);
    cout <<" x : " << n_p.c.x << " , y :" << n_p.c.y <<  ", move : "<< move[n_p.move-11]<< endl;
    return 0;
}