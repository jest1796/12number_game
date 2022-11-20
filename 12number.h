#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include<unistd.h>

int enemy_turn(void);

int p_attack(void);
int p_move(int p_locate);
int start(void);
int command(void);

int enemy_turn(void);
void shuffle(int e_a_point[],unsigned int size);
int e_attack(void);


	