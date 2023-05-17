#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <arpa/inet.h>

#include "board.h"

bool _WinCheck(int board[5][5], int player)
{
  bool w=false;
  for(int i=0; i<28; i++)
    if( (board[win[i][0][0]][win[i][0][1]]==player) && (board[win[i][1][0]][win[i][1][1]]==player) && (board[win[i][2][0]][win[i][2][1]]==player) && (board[win[i][3][0]][win[i][3][1]]==player) )
      w=true;
  return w;
}

bool _LoseCheck(int board[5][5], int player)
{
  bool l=false;
  for(int i=0; i<48; i++)
    if( (board[lose[i][0][0]][lose[i][0][1]]==player) && (board[lose[i][1][0]][lose[i][1][1]]==player) && (board[lose[i][2][0]][lose[i][2][1]]==player) )
      l=true;
  return l;
}

bool _DrawCheck(int board[5][5]){
  bool d=true;
  for(int i=0; i<5; i++){
    for(int j=0; j<5; j++){
      if(board[i][j]==0){
        d=false;
      }
    }
  }
  return d;
}

int heuristic(int board[5][5]){
  int score = 0;
  int block_score = 25;
  for(int i = 0; i<5; i++){
    for(int j = 0; j<5; j++){
      if(board[i][j]!=0){
        continue;
      }
      int blocked_for_1 = 0;
      int blocked_for_2 = 0;
      if(j<3){
        if(board[i][j+1]==1 && board[i][j+2]==1){
          blocked_for_1++;
        }else if(board[i][j+1]==2 && board[i][j+2]==2){
          blocked_for_2++;
        }
      }
      if(i<3){
        if(board[i+1][j]==1 && board[i+2][j]==1){
          blocked_for_1++;
        }else if(board[i+1][j]==2 && board[i+2][j]==2){
          blocked_for_2++;
        }
      }
      if(i<3 && j<3){
        if(board[i+1][j+1]==1 && board[i+2][j+2]==1){
          blocked_for_1++;
        }else if(board[i+1][j+1]==2 && board[i+2][j+2]==2){
          blocked_for_2++;
        }
      }
      if(i<3 && j>1){
        if(board[i+1][j-1]==1 && board[i+2][j-2]==1){
          blocked_for_1++;
        }else if(board[i+1][j-1]==2 && board[i+2][j-2]==2){
          blocked_for_2++;
        }
      }
      if(j>1){
        if(board[i][j-1]==1 && board[i][j-2]==1){
          blocked_for_1++;
        }else if(board[i][j-1]==2 && board[i][j-2]==2){
          blocked_for_2++;
        }
      }
      if(i>1){
        if(board[i-1][j]==1 && board[i-2][j]==1){
          blocked_for_1++;
        }else if(board[i-1][j]==2 && board[i-2][j]==2){
          blocked_for_2++;
        }
      }
      if(i>1 && j>1){
        if(board[i-1][j-1]==1 && board[i-2][j-2]==1){
          blocked_for_1++;
        }else if(board[i-1][j-1]==2 && board[i-2][j-2]==2){
          blocked_for_2++;
        }
      }
      if(i>1 && j<3){
        if(board[i-1][j+1]==1 && board[i-2][j+2]==1){
          blocked_for_1++;
        }else if(board[i-1][j+1]==2 && board[i-2][j+2]==2){
          blocked_for_2++;
        }
      }
      if(i>0 && i<4){
        if(board[i-1][j]==1 && board[i+1][j]==1){
          blocked_for_1++;
        }else if(board[i-1][j]==2 && board[i+1][j]==2){
          blocked_for_2++;
        }
      }
      if(j>0 && j<4){
        if(board[i][j-1]==1 && board[i][j+1]==1){
          blocked_for_1++;
        }else if(board[i][j-1]==2 && board[i][j+1]==2){
          blocked_for_2++;
        }
      }
      if(i>0 && i<4 && j>0 && j<4){
        if(board[i-1][j-1]==1 && board[i+1][j+1]==1){
          blocked_for_1++;
        }else if(board[i-1][j-1]==2 && board[i+1][j+1]==2){
          blocked_for_2++;
        }
      }
      if(i>0 && i<4 && j>0 && j<4){
        if(board[i-1][j+1]==1 && board[i+1][j-1]==1){
          blocked_for_1++;
        }else if(board[i-1][j+1]==2 && board[i+1][j-1]==2){
          blocked_for_2++;
        }
      }
      if(blocked_for_1){
        score -= block_score;
      }
      if(blocked_for_2){
        score += block_score;
      }
    }
  }
  int wages[5][5] = {
    {0,1,0,1,0},
    {1,3,3,3,1},
    {0,3,5,3,0},
    {1,3,3,3,1},
    {0,1,0,1,0}
  };
  for(int i = 0; i<5; i++){
    for(int j = 0; j<5; j++){
      if(board[i][j]==1){
        score += wages[i][j];
      }else if(board[i][j]==2){
        score -= wages[i][j];
      }
    }
  }
  return score;
}

int evaluate(int board[5][5]){
  int score = 0;
  if (_WinCheck(board, 1))
  {
    score = 500;
  }
  else if (_LoseCheck(board, 1))
  {
    score = -500;
  }
  else if (_WinCheck(board, 2))
  {
    score = -500;
  }
  else if (_LoseCheck(board, 2))
  {
    score = 500;
  }
  else if(_DrawCheck(board)){
    score = 0;
  }else
  {
    score = heuristic(board);
  }
  return score;
}

int minmax(int board[5][5], int depth, int alpha, int beta, int minPlayer, int* move){
  if(depth==0 || _WinCheck(board, 1) || _WinCheck(board, 2)
   || _LoseCheck(board, 1) || _LoseCheck(board, 2)|| _DrawCheck(board)){
    int score = evaluate(board);
    return score;
  }
  int bestMove;

  if(minPlayer){
    int bestScore = 1000;
    for(int i=0; i<5; i++){
      for(int j=0; j<5; j++){
        if(board[i][j]==0){
          board[i][j] = 2;
          int score = minmax(board, depth-1, alpha, beta, 0, move);
          board[i][j] = 0;
          if(score < bestScore){
            bestMove = (i+1)*10+(j+1);
            bestScore = score;
          }
          if(score < beta){
            beta = score;
          }
          if(beta <= alpha){
            break;
          }
        }
      }
    }
    (*move) = bestMove;
    return bestScore;
  }else{
    int bestScore = -1000;
    for(int i=0; i<5; i++){
      for(int j=0; j<5; j++){
        if(board[i][j]==0){
          board[i][j] = 1;
          int score = minmax(board, depth-1, alpha, beta, 1, move);
          board[i][j] = 0;
          if(score > bestScore){
            bestMove = (i+1)*10+(j+1);
            bestScore = score;
          }
          if(score > alpha){
            alpha = score;
          }
          
          if(beta <= alpha){
            break;
          }
        }
      }
    }
    (*move) = bestMove;
    return bestScore;
  }
  
}


int main(int argc, char *argv[])
{
  int socket_desc;
  struct sockaddr_in server_addr;
  char server_message[16], client_message[16];

  bool end_game;
  int player, msg, move;

  if( argc!=5 ) {
    printf("Wrong number of arguments\n");
    return -1;
  }

  // Create socket
  socket_desc = socket(AF_INET, SOCK_STREAM, 0);
  if( socket_desc<0 ) {
    printf("Unable to create socket\n");
    return -1;
  }
  printf("Socket created successfully\n");

  // Set port and IP the same as server-side
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(atoi(argv[2]));
  server_addr.sin_addr.s_addr = inet_addr(argv[1]);

  // Send connection request to server
  if( connect(socket_desc, (struct sockaddr*)&server_addr, sizeof(server_addr))<0 ) {
    printf("Unable to connect\n");
    return -1;
  }
  printf("Connected with server successfully\n");

  // Receive the server message
  memset(server_message, '\0', sizeof(server_message));
  if( recv(socket_desc, server_message, sizeof(server_message), 0)<0 ) {
    printf("Error while receiving server's message\n");
    return -1;
  }
  printf("Server message: %s\n",server_message);

  memset(client_message, '\0', sizeof(client_message));
  strcpy(client_message, argv[3]);
  // Send the message to server
  if( send(socket_desc, client_message, strlen(client_message), 0)<0 ) {
    printf("Unable to send message\n");
    return -1;
  }

  setBoard(); 
  end_game = false;
  player = atoi(argv[3]);
  int depth = atoi(argv[4]);

  while( !end_game ) {
    memset(server_message, '\0', sizeof(server_message));
    if( recv(socket_desc, server_message, sizeof(server_message), 0)<0 ) {
      printf("Error while receiving server's message\n");
      return -1;
    }
    printf("Server message: %s\n", server_message);
    msg = atoi(server_message);
    move = msg%100;
    msg = msg/100;
    if( move!=0 ) {
      setMove(move, 3-player);
      printBoard();
    }
    if( (msg==0) || (msg==6) ) {
      printf("Your move: \n");
      minmax(board, depth, -1000, 1000, player-1, &move);
      setMove(move, player);
      printBoard();
      memset(client_message, '\0', sizeof(client_message));
      sprintf(client_message, "%d", move);
      if( send(socket_desc, client_message, strlen(client_message), 0)<0 ) {
        printf("Unable to send message\n");
        return -1;
      }
      printf("Client message: %s\n", client_message);
     }
     else {
       end_game = true;
       switch( msg ) {
         case 1 : printf("You won.\n"); break;
         case 2 : printf("You lost.\n"); break;
         case 3 : printf("Draw.\n"); break;
         case 4 : printf("You won. Opponent error.\n"); break;
         case 5 : printf("You lost. Your error.\n"); break;
       }
     }
   }

  // Close socket
  close(socket_desc);

  return 0;
}
