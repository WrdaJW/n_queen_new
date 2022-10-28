#include <iostream>
#include<algorithm>
#include<time.h>
using namespace std;

//전역변수
int input_n;
int cnt = 0;
char print_board;

//보드출력
void print_NQueen(int** board) {
    for (int i = 0; i < input_n; i++)
    {
        for (int j = 0; j < input_n; j++)
            cout << " "<< board[i][j] <<" ";
        cout << endl;
    }
    cout << "\n";
}


bool erase_board(int** board, int row, int col) {
    int i, j;
    int sum = 0;

    //좌우제거
    for (i = 0; i < input_n; i++) {
        board[row][i] = 0;
    }
    //상하제거
    for (j = 0; j < input_n; j++) {
        board[j][col] = 0;
    }
    //오른쪽 아래대각선 제거
    for (i = row, j = col; j < input_n && i < input_n; i++, j++) {
        board[i][j] = 0;
    }
    //오른쪽 위대각선 제거
    for (i = row, j = col; j < input_n && i >= 0; i--, j++) {
        board[i][j] = 0;
    }
    //퀸이 놓일곳은 1로 변경
    board[row][col] = 1;

    //배열의 뒷부분을 검사해서 놓을자리가 없는 세로열이 존재하면 false를 리턴해 백트래킹
    for(j=col+1; j<input_n; j++){
        for (i = 0; i < input_n; i++) {
            sum += board[i][j];
       }
        if (sum == 0) return false; 
        sum = 0;
    }
    return true;
}


//배열을 복사
void copy_board(int** input, int **copy) {
    for (int i = 0; i < input_n; i++) {
        for (int j = 0; j < input_n; j++) {
            copy[i][j] = input[i][j];
        }
    }
}

void solve(int** board, int col) {
    int** temp_board = new int* [input_n];
    //백트래킹시 되돌릴 배열을 temp_board로 선언
    for (int i = 0; i < input_n; i++) {
        temp_board[i] = new int[input_n];
    }
    
    if (col >= input_n) {
        if (print_board == 'y') {
            print_NQueen(board);
        }
        cnt++;
        return;
    }

    //임시배열 temp_board에 현재배열 복사
    copy_board(board, temp_board);

    for (int i = 0; i < input_n; i++) {
        if (temp_board[i][col]) {   //세로줄에 퀸을 놓을 자리가 있는 확인
            //놓을자리가 있으면 퀸의 공격범위에 해당하는 위치의 1을 모두 0으로 지운다
            //단 앞으로 검사할 배열의 세로줄이 모두 0(놓을수없는상태)인 세로줄이 있으면 백트래킹 실시
            if (erase_board(board, i, col)) 
                solve(board, col + 1);  //다음세로줄 검사
            }
        //백트래킹
        copy_board(temp_board, board);
    }
        
        
}


void N_Queen() {
    //보드생성
    int** N_board = new int* [input_n];
   
    for (int i = 0; i < input_n; i++) {
        N_board[i] = new int[input_n];
        fill_n(N_board[i], input_n, 1);
    }
    
    solve(N_board, 0);
    
}

int main()
{
    clock_t start, end;
    double result;
    char fin = 'y';
    while (1) {
        cout << "N을 입력하세요 >> ";
        cin >> input_n;
        cout << "결과물 출력? y/n >> ";
        cin >> print_board;
        start = clock();
        N_Queen();
        end = clock();
        result = double(end - start) / CLOCKS_PER_SEC;
        cout << "찾은 해답 개수 >> " << cnt << endl;
        cout << "걸린 시간 >> " << result << endl<<endl;
        cout << "다른 N으로 찾으려면 y/ 종료하려면 n >> ";
        cin >> fin;
        cout << endl;
        cnt = 0;
        if (fin == 'n')break;
        
    }

    return 0;
}

