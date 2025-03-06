#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define n_color 5
#define n_tile 100
#define n_ch 7
#define n_player 2
#define n_disc 5

void print_tile(int i) {
	switch (i) {
	case 0:
		printf("\x1b[106mX");
		break;
	case 1:
		printf("\x1b[43mX");
		break;
	case 2:
		printf("\x1b[101mX");
		break;
	case 3:
		printf("\x1b[100mX");
		break;
	case 4:
		printf("\x1b[107mX");
		break;
	}
	printf("\033[0m ");
}
void print_empty(int i) {
	switch (i) {
	case 0:
		printf("\x1b[96mX");
		break;
	case 1:
		printf("\x1b[33mX");
		break;
	case 2:
		printf("\x1b[91mX");
		break;
	case 3:
		printf("\x1b[90mX");
		break;
	case 4:
		printf("\x1b[97mX");
		break;
	}
	printf("\033[0m ");
}
int main() {
	int p[n_player];
	int result_only=1;
	int ai[2]= {1,1};
	char color[5][n_ch] = {"cyan", "orange", "red", "black", "white"};
	int bag[n_tile];
	int discard[n_tile];
	int disc[n_disc][4];
	int disc_selected[n_disc];
	int center_selected;
	int center_empty;
	int center[n_tile];
	int board[n_player][5][10];
	int wall[n_player][5][5];
	int wall_map[5][5];
	int penalty[n_player][7];
	int n_penalty[n_player];
	int penalty_map[7]= {-1,-1,-2,-2,-2,-3,-3};
	int n_bag, n_discard, n_center;
	int i,j,k,m,n,r,s,x,v;
	int flag;
	int game_end;
	int turn_end;
	int count;
	int max;
	int co[n_color];
	int valid,valid_color,n_pick,color_pick,row,ptr;
	char input[100],input_color[100],sure[100];
	int horizontal,vertical,points;
	int first,next_first,turn;	
	int value[5][5][5],temp_wall[5][5];
	double avg[n_player];
	int win[n_player];
	int pl, play = 100;
	int ai_only=1;
	if (play>1){
		for (i=0;i<n_player;i++){
			avg[i]=0;
			win[i]=0;
		}
	}
	first =0;
	for (pl=0;pl<play;pl++){
		if (pl>0){
			printf("Game %d\n",pl);
		}
		center_selected=0;
		center_empty=0;
		n_bag=100;
		n_discard=0;
		n_center=0;
		game_end=0;
		turn_end=0;
		
		if (result_only == 0){
			printf("Azul Game Start!\n");
		}
		for (i = 0; i<n_color; i++) {
			for (j=0; j<20; j++) {
				bag[i*20+j]=i;
			}
		}
		for (i=0; i<5; i++) {
			for (j=0; j<5; j++) {
				wall_map[i][j]=(-i+j+5)%5;
			}
		}
		for (j=0; j<n_player; j++) {
			for (i=0; i<5; i++) {
				for (k=0; k<5; k++) {
					if (k>3-i) {
						board[j][i][k]=-1;
					} else {
						board[j][i][k]=-2;
					}
					wall[j][i][k]=0;
				}
				for (k=5; k<10; k++) {
					board[j][i][k]=-2;
				}
			}
			p[j]=0;
		}
		unsigned seed = (unsigned)time(NULL) + pl;
        srand(seed);
		while (game_end == 0) {
			turn_end = 0;
			if (n_bag < n_disc * 4) {
				for (i=0; i<n_discard; i++) {
					bag[n_bag]=discard[i];
					n_bag++;
				}
				n_discard = 0;
			}

			for (int i = 0; i < n_disc; i++) {
				for (int j = 0; j < 4; j++) {
					int r = rand() % (n_bag);
					disc[i][j] = bag[r];
					for (int k = r; k < n_bag - 1; k++) {
						bag[k] = bag[k + 1];
					}
					n_bag--;
				}
			}

			for (int i =0; i<n_disc; i++) {
				disc_selected[i] = 0;
			}
			center_selected = 0;
			center_empty = 1;
			for (j=0; j<n_player; j++) {
				for (i=0; i<7; i++) {
					penalty[j][i]=-2;
				}
				n_penalty[j] = 0;
			}
			while (turn_end == 0) {
				for (x=0; x<n_player; x++) {
					turn = (first+x)%n_player;
					if (result_only ==0 ){
						for (i=0; i<24*n_player+2; i++) {
							printf("-");
						}
						printf("\n| ");
						for (i=0; i<n_disc; i++)
							printf("disc%d | ",i+1);
						printf("\n");

						for (i=0; i<n_disc; i++) {
							printf("|  ");
							for (j=0; j<2; j++) {
								if (disc_selected[i] == 0)
									print_tile(disc[i][j]);
								else
									printf("  ");
							}
							printf(" ");
						}
						printf("|\n");
						for (i=0; i<n_disc; i++) {
							printf("|  ");
							for (j=2; j<4; j++) {
								if (disc_selected[i] == 0)
									print_tile(disc[i][j]);
								else
									printf("  ");
							}
							printf(" ");
						}
						printf("|\n");
						for (i=0; i<24*n_player+2; i++) {
							printf("-");
						}
						printf("\ncenter: ");
						if (center_selected == 0) {
							printf("\x1b[47m1\033[0m ");
						}
						for (i=0; i<n_center; i++) {
							print_tile(center[i]);
						}
						printf("\n");
						for (i=0; i<24*n_player+2; i++) {
							printf("-");
						}
						printf("\n");
						for (j=0; j<n_player; j++) {
							printf("         Player %d       ",j+1);
						}
						printf("\n");
						for (i=0; i<5; i++) {
							printf("| ");
							for (j=0; j<n_player; j++) {
								for (k=0; k<5; k++) {
									if (board[j][i][k]==-1) {
										printf("X ");
									} else if (board[j][i][k]==-2) {
										printf("  ");
									} else {
										print_tile(board[j][i][k]);
									}
								}
								printf("| ");
								for (k=0; k<5; k++) {
									if (wall[j][i][k] == 0) {
										print_empty(wall_map[i][k]);
									} else {
										print_tile(wall_map[i][k]);
									}
								}
								printf("| ");
							}
							printf("\n");
						}
						for (j=0; j<n_player; j++) {
							printf("|  ");
							for (i=0; i<7; i++) {
								switch (penalty[j][i]) {
								case -2:
									printf("%d",penalty_map[i]);
									break;
								case -1:
									printf("\x1b[47m%d",penalty_map[i]);
									break;
								case 0:
									printf("\x1b[106m%d",penalty_map[i]);
									break;
								case 1:
									printf("\x1b[43m%d",penalty_map[i]);
									break;
								case 2:
									printf("\x1b[101m%d",penalty_map[i]);
									break;
								case 3:
									printf("\x1b[100m%d",penalty_map[i]);
									break;
								case 4:
									printf("\x1b[107m%d",penalty_map[i]);
									break;
								}
								printf("\033[0m ");
							}
						}
						printf("|\n");
						printf("Player %d turn\n",turn+1);
					}
					for (i=0; i<5; i++) {
						co[i]=0;
					}
					valid=0;
					valid_color = 0;
					n_pick=0;
					while (valid==0) {
						if (ai[turn]==0) {
							count = 0;
							flag =0;
							for (i=0;i<5;i++){
								if (disc_selected[i]==0){
									count++;
									flag=i;
								}
							}
							if (count==0){
								printf("You have to choose the center.\n");
								strcpy(input,"c");
							} else if (center_empty == 0) {
								printf("Please input a disc number or the center(c):");
								scanf("%s", input);
							} else if (count>1){
								printf("Please input a disc number:");
								scanf("%s", input);
							} else {
								printf("You have to choose disc %d\n.",flag+1);
								sprintf(input,"%d",flag+1);
							}				
						} else {
							for (i=0; i<5; i++) {
								for (j=0; j<5; j++) {
									for (n=0; n<5; n++) {
										if (wall[turn][j][(i+j)%5]==1 || (board[turn][j][4]!=i && board[turn][j][4]!= -1)) {
											value[i][j][n]=-1*(n+1);
										} else if (board[turn][j][4-j]==i && board[turn][j][4]==i){
											value[i][j][n]=-30;
										} else {
											k=0;
											while (board[turn][j][k+4-j]==-1 && k+4-j<5) {
												k++;
											}
											value[i][j][n]=(n+1-k)*-1;
											if (value[i][j][n]<0){
												value[i][j][n]=0;
											}
											for (k=0; k<5; k++) {
												for (m=0; m<5; m++) {
													temp_wall[k][m]=wall[turn][k][m];
													if (board[turn][k][4-k] == (m-k+5)%5 ) {
														temp_wall[k][m] =1;
													}
												}
												vertical = 1;
												horizontal = 1;
												s=0;
												valid = 1;
												while (s+k+1<5 && valid==1) {
													if (temp_wall[s+k+1][(s+i)%5]==1) {
														vertical++;
														s++;
													} else {
														valid=0;
													}
												}
												s=0;
												valid = 1;
												while (s+k-1>=0 && valid ==1) {
													if (temp_wall[s+k-1][(k+i)%5]==1) {
														vertical++;
														s--;
													} else {
														valid=0;
													}
												}
												s=0;
												valid=1;
												while (s+((k+i)%5)+1<5 && valid==1) {
													if (temp_wall[k][s+((k+i)%5)+1]==1) {
														horizontal++;
														s++;
													} else {
														valid=0;
													}
												}
												s=0;
												valid = 1;
												while (s+((k+i)%5)-1>=0 && valid ==1) {
													if (temp_wall[k][s+((k+i)%5)-1]==1) {
														horizontal++;
														s--;
													} else {
														valid=0;
													}
												}
												points = 0;
												if (vertical ==1 && horizontal ==1) {
													points = 1;
												} else if (vertical >1 && horizontal ==1) {
													points = vertical;
												} else if (vertical==1&&horizontal>1) {
													points = horizontal;
												} else {
													points = horizontal+vertical;
												}
												value[i][j][n]+=points;
												// printf("i:%d j:%d n:%d v:%d\n",i,j,n,points);
											}
																					
										}	
										count=0;
										k=4-j;
										while (k<5){
											if (board[turn][j][k]==-1){
												count++;
											} else {
												break;
											}
											k++;
										}
										if (n+1>count){
											// printf("%d %d %d\n",value[i][j][n],n+1,count);
											value[i][j][n]=value[i][j][n]*(j+1)-(n+1-count);
										} else if (n+1==count){
											value[i][j][n]=value[i][j][n]*(j+1)+10;
										} else {
											value[i][j][n]*=(j+1)/(count-n-1);
										}			
										// printf("i:%d j:%d n:%d v:%d\n",i,j,n,value[i][j][n]);
									}
								}
							}
							flag =0 ;
							max =-10;
							for (i=0; i<5; i++) {
								for (j=0; j<5; j++) {
									for (n=0; n<5; n++) {
										if (value[i][j][n]>max) {
											max=value[i][j][n];
										}
									}
								}
							}
							while (flag ==0) {
								if (result_only == 0){
									// printf("Player %d is trying to get %d\n",turn+1, max);
								}						
								for (n=27; n>=0; n--) {
									for (j=0; j<5; j++) {
										for (i=0; i<5; i++) {
											count=0;
											k=4-j;
											while (k<5){
												if (board[turn][j][k]==-1){
													count++;
												} else {
													break;
												}
												k++;
											}
											if (n+1>count){
												v=value[i][j][n]-(n+1-count);
											} else {
												v=value[i][j][n];
											}
											if ((v==max&&center_selected==1) || (v-1==max && center_selected==0)){
												count=0;
												if(n_center>=n+1) {
													for (s=0; s<n_center; s++) {
														if (center[s]==i) {
															count++;
														}
													}
													if (count==(n+1)) {
														// printf("center matched color:%d row:%d number:%d %d\n",i,j,n+1,count);
														flag=1;
														strcpy(input,"c");
														strcpy(input_color,color[i]);
														row =j;
														if (result_only == 0){
															// printf("Player %d picked center and put %d %s in row %d, it worths %d\n",turn+1,n+1,color[i],row+1,max);
														}
														break;
													}
												}
											}									
											if (v==max){
												// printf("TRYING color:%d row%d number:%d value:%d\n",i,j,n,max);
												if (n<4) {
													for (m=0; m<n_disc; m++) {
														if (disc_selected[m]==0){
															count =0;
															for (s=0; s<4; s++) {
																if (disc[m][s]==i) {
																	count++;
																}
															}
															if (count==(n+1)) {
																// printf("disc %d matched color:%d row:%d number:%d %d\n",m,i,j,n+1,count);
																flag=1;
																sprintf(input,"%d",m+1);
																strcpy(input_color,color[i]);
																row =j;
																if (result_only == 0){
																	// printf("Player %d picked disc%s and put %d %s in row %d, it worths %d\n",turn+1,input,n+1,color[i],row+1,max);
																}
																break;
															}
														}														
													}
												}																						
											}
											if (flag ==1) break;
										}
										if (flag ==1) break;
									}
									if (flag ==1) break;
								}
								max--;
							}
						}

						if (!(strcmp(input, "1") == 0 || strcmp(input, "2") == 0 || strcmp(input, "3") == 0 ||
								strcmp(input, "4") == 0 || strcmp(input, "5") == 0 || strcmp(input, "6") == 0 ||
								strcmp(input, "7") == 0 || strcmp(input, "8") == 0 || strcmp(input, "9") == 0 || strcmp(input, "c") == 0)) {
							printf("Input invalid!\n");
						} else if (strcmp(input,"c") ==0 ) {
							if (center_empty == 1) {
								printf("The center is empty!\n");
							} else {
								valid = 1;
								if (center_selected == 0) {
									penalty[turn][n_penalty[turn]] = -1;
									center_selected = 1;
									n_penalty[turn]++;
									next_first=turn;
								}
								for (i=0; i<n_center; i++) {
									co[center[i]]+=1;
								};
								while (valid_color ==0) {
									if (ai[turn]==0) {
										count = 0;
										for (i=0;i<n_color;i++){
											if (co[i] > 0){
												count++;
												flag = i;
											}
										}
										if (count==1){
											printf("You have to choose %s.\n",color[flag]);
											strcpy(input_color,color[flag]);
										} else {
											flag =0;
											printf("Please input a color from the center (");
											for (i=0; i<n_color; i++) {
												if (co[i] > 0) {
													if (flag == 1) {
														printf (", ");
													}
													printf("%s",color[i]);
													flag = 1;
												}
											}
											printf("):");
											scanf("%s", input_color);
										}								
									}
									flag = 0;
									for (i=0; i<n_color; i++) {
										if (strcmp(color[i],input_color) == 0) {
											flag = 1;
											if (co[i]>0) {
												valid_color = 1;
												n_pick = co[i];
												color_pick = i;
												for (j=0; j<n_center; j++) {
													if (center[j] == i) {
														for (k=j; k<n_center-1; k++) {
															center[k]=center[k+1];
														}
														n_center-=1;
														j--;
													}
												}
												if (n_center == 0) {
													center_empty = 1;
												}
											} else if (ai[turn]==0) {
												printf("There is no such color in the center!\n");
											}
										}
									}
									if (flag == 0) {
										printf("Please input a valid color!\n");
									}
								}
							}
						} else {
							int num = atoi(input) - 1;
							if (disc_selected[num] == 1) {
								printf("disc %s is empty!\n", input);
							} else {
								disc_selected[num] = 1;
								valid = 1;
								for (i=0; i<4; i++) {
									co[disc[num][i]]+=1;
								};
								count=0;
								flag=0;
								for (i=0;i<n_color;i++){
									if (co[i]>0){
										count++;
										flag=i;
									}
								}
								while (valid_color == 0) {
									if (ai[turn]==0){
										if (count==1){
											printf("You have to choose %s from disc %s.\n",color[flag],input);
											strcpy(input_color,color[flag]);
										}
										printf("Please input a color from disc %s (", input);
										flag = 0;
										for (i=0; i<n_color; i++) {
											if (co[i] > 0) {
												if (flag == 1) {
													printf (", ");
												}
												printf("%s",color[i]);
												flag = 1;
											}
										}
										printf("):");
										scanf("%s", input_color);
									}
									
									flag = 0;
									for (i=0; i<n_color; i++) {
										if (strcmp(color[i],input_color) == 0) {
											flag = 1;
											if (co[i]>0) {
												valid_color = 1;
												n_pick = co[i];
												color_pick = i;
												for (j=0; j<n_color; j++) {
													if (i!=j) {
														for (k=0; k<co[j]; k++) {
															center[n_center]=j;
															n_center+=1;
														}

													}
												}
												center_empty=0;
												disc_selected[num]=1;

											} else if (ai[turn]==0) {
												printf("There is no such color in the disc!\n");
											}
										}
									}
									if (flag == 0) {
										printf("Please input a valid color!\n");
									}
								}
							}
						}
					}
					valid = 0;
					valid_color = 1;
					while(valid == 0) {
						if (ai[turn]==0) {
							flag =0;
							for (i=0;i<n_color;i++){
								if (!(wall[turn][i][(i+color_pick)%5]==1 || (board[turn][i][4]!=color_pick && board[turn][i][4]!=-1) || board[turn][i][n_pick+3-i]!=-1)){
									flag =1;
									break;
								}
							}
							if (flag ==1){
								printf("You pick %d %s tile(s), please choose the row to fill(1-5): ",n_pick,color[color_pick]);
								scanf("%s", input);
							} else {
								printf("You are going to get penalty for all %d tiles.",n_pick);
								strcpy(input,"1");
							}
							
						}

						if (!(strcmp(input, "1") == 0 || strcmp(input, "2") == 0 || strcmp(input, "3") == 0 ||
								strcmp(input, "4") == 0 || strcmp(input, "5") == 0 || ai[turn]==1)) {
							printf("Input invalid!\n");
						} else {
							if (ai[turn]==0) {
								row = atoi(input)-1;
								printf("You are going to put the %s tile(s) into row %s from the right.\n",color[color_pick],input);
								if (wall[turn][row][(row+color_pick)%5]==1) {
									printf("However, row %s of your wall already holds a tile of %s. You must place %d tile(s) on the floor line corresponds to penalty.\n",input, color[color_pick], n_pick);
								} else if (board[turn][row][4]!=color_pick && board[turn][row][4]!=-1) {
									printf("However, row %s of your pattern lines already holds another color. You must place %d tile(s) on the floor line corresponds to penalty.\n",input, n_pick);
								} else if (board[turn][row][n_pick+3-row]!=-1) {
									printf("However, row %s of your pattern lines do not have enough spaces for putting all %d tile(s). ",input, n_pick);
									j=0;
									for (i=4-row; i<n_color; i++) {
										if (board[turn][row][i]==color_pick) {
											break;
										} else if (j!=4) {
											j++;
										}
									}
									printf("You must place %d tile(s) on the floor line corresponds to penalty.\n",n_pick-j);
								}
								valid = 1;
							} else {
								valid =1;
							}


						}
					}
					if (wall[turn][row][(row+color_pick)%5]==1 || (board[turn][row][4]!=color_pick && board[turn][row][4]!=-1)|| board[turn][row][4-row]==color_pick) {
						valid_color = 0;
					} else {
						ptr = 4;
						while (board[turn][row][ptr]!=-1) {
							ptr--;
						}
					}
					while (n_pick>0) {
						if (valid_color == 0) {
							if (n_penalty[turn]<7) {
								penalty[turn][n_penalty[turn]]=color_pick;
								n_penalty[turn]++;
							} else {
								discard[n_discard]=color_pick;
								n_discard++;
							}
							n_pick--;
						} else {
							if (ptr<4-row) {
								valid = 0;
							}

							ptr = 4;
							while (board[turn][row][ptr]!=-1) {
								ptr--;
							}
							board[turn][row][ptr]=color_pick;
							ptr--;
							n_pick--;
							if (ptr<4-row) {
								valid_color = 0;
							}
							if (result_only == 0){
								for (i=0; i<5; i++) {
									printf("| ");
									for (k=0; k<5; k++) {
										if (k>=4-i) {
											if (board[turn][i][k]==-1) {
												printf("X ");
											} else {
												print_tile(board[turn][i][k]);
											}
										} else {
											printf("  ");
										}
									}
									printf("| ");
									for (k=0; k<5; k++) {
										if (wall[turn][i][k] == 0) {
											print_empty(wall_map[i][k]);
										} else {
											print_tile(wall_map[i][k]);
										}
									}
									printf("|\n");
								}
								printf("\n");
							}
						}
					}
					turn_end = 1;
					for (i=0; i<n_disc; i++) {
						if (disc_selected[i] == 0) {
							turn_end = 0;
							break;
						}
					}
					if (n_center>0) {
						turn_end = 0;
					}
					if (turn_end == 1) {
						if (result_only == 0){
							printf("Turn ends!\n");
						}
						if (ai_only == 0){
							for (i=0; i<24*n_player+2; i++) {
								printf("-");
							}
							printf("\n| ");
							for (i=0; i<n_disc; i++)
								printf("disc%d | ",i+1);
							printf("\n");

							for (i=0; i<n_disc; i++) {
								printf("|  ");
								for (j=0; j<2; j++) {
									if (disc_selected[i] == 0)
										print_tile(disc[i][j]);
									else
										printf("  ");
								}
								printf(" ");
							}
							printf("|\n");
							for (i=0; i<n_disc; i++) {
								printf("|  ");
								for (j=2; j<4; j++) {
									if (disc_selected[i] == 0)
										print_tile(disc[i][j]);
									else
										printf("  ");
								}
								printf(" ");
							}
							printf("|\n");
							for (i=0; i<24*n_player+2; i++) {
								printf("-");
							}
							printf("\ncenter: ");
							if (center_selected == 0) {
								printf("\x1b[47m1\033[0m ");
							}
							for (i=0; i<n_center; i++) {
								print_tile(center[i]);
							}
							printf("\n");
							for (i=0; i<24*n_player+2; i++) {
								printf("-");
							}
							printf("\n");
							for (j=0; j<n_player; j++) {
								printf("         Player %d       ",j+1);
							}
							printf("\n");
							for (i=0; i<5; i++) {
								printf("| ");
								for (j=0; j<n_player; j++) {
									for (k=0; k<5; k++) {
										if (board[j][i][k]==-1) {
											printf("X ");
										} else if (board[j][i][k]==-2) {
											printf("  ");
										} else {
											print_tile(board[j][i][k]);
										}
									}
									printf("| ");
									for (k=0; k<5; k++) {
										if (wall[j][i][k] == 0) {
											print_empty(wall_map[i][k]);
										} else {
											print_tile(wall_map[i][k]);
										}
									}
									printf("| ");
								}
								printf("\n");
							}
						}
						if (ai_only==0){
							for (j=0; j<n_player; j++) {
								printf("|  ");
								for (i=0; i<7; i++) {
									switch (penalty[j][i]) {
									case -2:
										printf("%d",penalty_map[i]);
										break;
									case -1:
										printf("\x1b[47m%d",penalty_map[i]);
										break;
									case 0:
										printf("\x1b[106m%d",penalty_map[i]);
										break;
									case 1:
										printf("\x1b[43m%d",penalty_map[i]);
										break;
									case 2:
										printf("\x1b[101m%d",penalty_map[i]);
										break;
									case 3:
										printf("\x1b[100m%d",penalty_map[i]);
										break;
									case 4:
										printf("\x1b[107m%d",penalty_map[i]);
										break;
									}
									printf("\033[0m ");
								}
							}
							printf("|\n");
						}
						for (x=0; x<n_player; x++) {
							for (i=0; i<5; i++) {
								if (board[x][i][4-i] != -1) {
									color_pick = board[x][i][4-i];
									wall[x][i][(i+color_pick)%5]=1;
									vertical = 1;
									horizontal = 1;
									j=0;
									valid = 1;
									while (j+i+1<5 && valid==1) {
										if (wall[x][j+i+1][(i+color_pick)%5]==1) {
											vertical++;
											j++;
										} else {
											valid=0;
										}
									}
									j=0;
									valid = 1;
									while (j+i-1>=0 && valid ==1) {
										if (wall[x][j+i-1][(i+color_pick)%5]==1) {
											vertical++;
											j--;
										} else {
											valid=0;
										}
									}
									j=0;
									valid=1;
									while (j+((i+color_pick)%5)+1<5 && valid==1) {
										if (wall[x][i][j+((i+color_pick)%5)+1]==1) {
											horizontal++;
											j++;
										} else {
											valid=0;
										}
									}
									j=0;
									valid = 1;
									while (j+((i+color_pick)%5)-1>=0 && valid ==1) {
										if (wall[x][i][j+((i+color_pick)%5)-1]==1) {
											horizontal++;
											j--;
										} else {
											valid=0;
										}
									}
									points = 0;
									if (vertical ==1 && horizontal ==1) {
										points = 1;
									} else if (vertical >1 && horizontal ==1) {
										points = vertical;
									} else if (vertical==1&&horizontal>1) {
										points = horizontal;
									} else {
										points = horizontal+vertical;
									}
									p[x]+=points;
									if (result_only == 0){
										printf("Player %d row %d with color %s has %d vertical tile(s) and %d horizontal tile(s) and get %d point(s).\n",x+1,i+1,color[color_pick],vertical,horizontal,points);
									}
									for (j=4-i; j<5; j++) {
										board[x][i][j]=-1;
										discard[n_discard]=color_pick;
										n_discard++;
									}
								}
							}
							for (i=0; i<n_penalty[x]; i++) {
								p[x]+=penalty_map[i];
								if (result_only == 0){
									printf("Player %d gets %d penalty.\n",x+1,penalty_map[i]);
								}
								if (penalty[x][i]!=-1){
									discard[n_discard]=penalty[x][i];
									n_discard++;
								}								
							}
							if (p[x]<0) {
								p[x]=0;
							}
							if (result_only == 0){
								printf("Player %d has %d point(s)\n", x+1,p[x]);
							}
						}
						break;
					}
				}
			}
			for (x=0; x<n_player; x++) {
				for (i=0; i<5; i++) {
					flag = 0;
					for (j=0; j<5; j++) {
						if (wall[x][i][j] == 0) {
							flag = 1;
						}
					}
					if (flag ==0) {
						game_end =1;
						break;
					}
				}
				if (flag ==0) {
					break;
				}
			}
			if (flag == 1 && result_only ==0) {
				for (i=0;i<n_discard;i++){
					printf("%d, %d\n",i,discard[i]);
				}
				printf("Refilling discs...\n");
				printf("Next turn starts with player %d.\n",next_first+1);
			}
			first = next_first;

		}
		if (result_only ==0 ){
			printf("Game ends!\n");
		}
		for (x=0; x<n_player; x++) {
			for (i=0; i<5; i++) {
				count = 0;
				for(j=0; j<5; j++) {
					if (wall[x][i][j] == 0) {
						break;
					} else {
						count++;
					}
				}
				if (count==5) {
					p[x]+=2;
					if (result_only ==0 ){
						printf("Player %d gets a horizontal line for row %d and is awarded 2 points.\n",x+1,i+1);
					}
				}
			}
			for (j=0; j<5; j++) {
				count = 0;
				for(i=0; i<5; i++) {
					if (wall[x][i][j] == 0) {
						break;
					} else {
						count++;
					}
				}
				if (count==5) {
					p[x]+=7;
					if (result_only ==0 ){
						printf("Player %d gets a vertical line for column %d and is awarded 2 points.\n",x+1,j+1);
					}
				}
			}
			for (i=0; i<5; i++) {
				count = 0;
				for(j=0; j<5; j++) {
					if (wall[x][(i+j)%5][i] == 0) {
						break;
					} else {
						count++;
					}
				}
				if (count==5) {
					p[x]+=10;
					if (result_only ==0 ){
						printf("Player %d gets a whole set of color %s and is awarded 10 points.\n",x+1,color[i]);
					}
				}
			}
			if (play==1){
				printf ("Player %d has %d points!\n", x+1,p[x]);
			} else {
				avg[x]+=p[x];
			}
		}
		max = 0;
		for (x=0; x<n_player; x++) {
			if (p[x]>max) {
				max=p[x];
			}
		}
		count=0;
		flag = 0;
		for (x=0; x<n_player; x++) {
			if (p[x]==max) {
				flag=x;
				count++;
			}
		}
		if (count==1) {
			if (play ==1){
				printf("Player %d wins!\n",flag+1);
			} else {
				win[flag]+=1;
			}
		} else {
			flag =0 ;
			if (play==1){
				printf("Player ");
			}
			for (x=0; x<n_player; x++) {
				if (p[x]==max) {
					if (flag ==1 && play ==1) {
						printf("and ");
					}
					if (play==1){
						printf("%d ",x+1);
					}
					flag =1;
					win[x]+=1;
				}
			}
			if (play==1){
				printf ("wins!\n");
			}	
		}
		if (play==1){
			for (j=0; j<n_player; j++) {
				printf("         Player %d       ",j+1);
			}
			printf("\n");
			for (i=0; i<5; i++) {
				printf("| ");
				for (j=0; j<n_player; j++) {
					for (k=0; k<5; k++) {
						if (board[j][i][k]==-1) {
							printf("X ");
						} else if (board[j][i][k]==-2) {
							printf("  ");
						} else {
							print_tile(board[j][i][k]);
						}
					}
					printf("| ");
					for (k=0; k<5; k++) {
						if (wall[j][i][k] == 0) {
							print_empty(wall_map[i][k]);
						} else {
							print_tile(wall_map[i][k]);
						}
					}
					printf("| ");
				}
				printf("\n");
			}
		}
	}
	if (play>1){
		for (i=0;i<n_player;i++){
			avg[i]*=1.0/play;
			printf("Player %d gets %.2f on average and wins %d time(s).\n",i+1, avg[i],win[i]);
		}
	}
	return 0;
}
