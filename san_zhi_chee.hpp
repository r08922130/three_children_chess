#define SIZE 3
#define BLACK -1
#define WHITE 1
#define RIGHT 11
#define LEFT 12
#define UP 13
#define DOWN 14
#define RIGHT_UP 15
#define RIGHT_DOWN 16
#define LEFT_UP 17
#define LEFT_DOWN 18
struct chess{
    int x;
    int y;
    // -1 for black , 1 for white
    int color;    
};
struct step{
    int move;
    int win;
    // -1 for black , 1 for white
    chess c;   
};
step next_step(int board[SIZE][SIZE], int my_color, chess white[SIZE] , chess black[SIZE]);
void go_right(int board[SIZE][SIZE],chess c[SIZE], int i );
void go_left(int board[SIZE][SIZE],chess c[SIZE], int i);
void go_up(int board[SIZE][SIZE],chess c[SIZE], int i);
void go_down(int board[SIZE][SIZE],chess c[SIZE], int i);
void go_right_up(int board[SIZE][SIZE],chess c[SIZE], int i );
void go_left_up(int board[SIZE][SIZE],chess c[SIZE], int i);
void go_right_down(int board[SIZE][SIZE],chess c[SIZE], int i);
void go_left_down(int board[SIZE][SIZE],chess c[SIZE], int i);
void print_board(int board[SIZE][SIZE]);
int is_win_lose(chess c[SIZE]);
int try_go(int board[SIZE][SIZE],chess my_chess[SIZE], int i);
int block_line(int board[SIZE][SIZE],chess my_chess[SIZE], int i, int px, int py);