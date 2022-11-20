#include "12number.h"


// ステージの広さ
#define NUMBER 12

// ゲーム説明
int info();

// 自分の位置
int p_locate;

// こちらの攻撃の当たり判定
int judge;

// こちらの行動　攻撃なら１，移動か待機なら2
int p_action;

// 敵の位置
int e_locate;

// 敵が攻撃するポイントの配列
int e_a_point[NUMBER];

// 何ターン目か
int turn;

// 敵側の当たり判定変数
int e_judge;
	
// 攻撃がシャッフル後に連続何回目かをカウント
int n;



int main (void){
	srand((unsigned int)time(NULL));

	printf("GAME START\n");
	printf("説明を読みますか？ (はい  1  / いいえ  2)\n>>");
	int a;
	scanf("%d",&a);
	if(a == 1)info();
	start();
	printf("現在位置は%dです。\n",p_locate);
	turn = 1;
	
	command();
	return 0;
}

int info(void){
	printf("あなたとコンピュータはそれぞれ、1～%dのどこか1つに陣取ります。\n\n",NUMBER);
	// fflush( stdout ); 
	sleep(2);
	printf("互いに攻撃し、相手のいる場所を射止めたら勝ちです。\n\n");
	// fflush( stdout ); 
	sleep(2);
	printf("攻撃したポイントから前後2つ以内に相手がいた場合は「反応あり」のメッセージが出ます。\n\n");
	// fflush( stdout ); 
	sleep(2);
	printf("また、移動もしくはその場で何もせずにターンを終えることも出来ます。\n\n");
	// fflush( stdout ); 
	sleep(2);
	printf("移動したのか、その場に留まったのかは相手にはわかりません。\n\n");
	// fflush( stdout ); 
	sleep(2);
	printf("%dターン経過しても決着しない場合は引き分けとして終了します。\n\n",NUMBER*2);
	sleep(2);
	printf("なお、入力は全て数字とリターンキーで入力してください。\n\n");
	return 0;
}

int start(void){
	
	// 入力位置がオッケーかやり直すかの変数
	int y=0;
	
	do{
		do{
			printf("自分の位置を決めてください（1 - %d）\n>>",NUMBER);
			scanf("%d",&p_locate);
			if(p_locate <1 || p_locate>NUMBER){
				printf("範囲内の数を入力してください\n");
			}
		}while(p_locate <1 || p_locate>NUMBER);	
	
	
		printf("%dでよろしいですか？\n>>",p_locate);
		printf("(OK  1/ NO  2)\n>>");
		scanf("%d",&y);

		if(y != 1){
			printf("入力しなおします\n>>");
		}
	}while(y != 1);
	
	// 敵の位置をランダムに決める
		e_locate = rand()%NUMBER +1;
	
	// 敵の攻撃地点配列に1～NUMBERをセット
	   for(int i = 0;i < NUMBER;i++){
			e_a_point[i] = i + 1;
		} 
			
}

int command(void){
	int c;
	printf("%dターン目\n",turn);
	do{
		printf("命令をどうぞ\n");
		printf("1  攻撃　/  2  移動　/ 3 待機　/ 4 ゲームを終了\n>>");
		scanf("%d",&c);
		
		if(c<1 || c>4){
			printf("１から4の数字で入力してください。\n>>");
		}
	}while(c<1 || c>4);
		
	switch(c){
		case 1:
			printf("攻撃します。\n>>");
			p_attack();
			break;
		case 2:
			printf("移動します。\n>>");
			p_locate = p_move(p_locate);
			break;
		case 3:	
			printf("待機します。\n\n>>");
			
			// プレイヤーが待機したフラグ
			p_action = 2;
			break;
		case 4:
			printf("ゲーム終了します。\n");
			exit(0);	
	}
	enemy_turn();
	
	return 0;	   
	}

// 移動
int p_move(int p_locate){
	
	// 移動選択肢の変数
	int m;
	
	// 移動フェーズを終えるかどうかのフラグ 1なら完了　０ならやり直し
	int f = 0;
	
	
	do{
		printf("現在位置は%dです。\n",p_locate);
		printf("移動先を選択してください。\n");
		printf("マイナス方向に移動なら１を　　プラス方向なら２を入力してください。\n");
		
		if(p_locate == 1){
			printf("今は移動可能なのは２だけです。\n>>");
		}
		else if(p_locate == NUMBER){
			printf("今は移動可能なのは%dだけです。\n>>",NUMBER - 1);
		}else{
		printf("(ポイント%dに移動なら１を　　ポイント%dに移動なら２を　入力してください）\n>>",p_locate-1,p_locate+1);
		}
		
		do{
			scanf("%d",&m);
			if(m<1 || m>2)printf("入力が正しくありません。");
		}while(m<1 || m>2);
		
		switch(m){
			case 1:
				p_locate-- ;
				printf("%d\n",p_locate);
				break;
			case 2:
				p_locate++ ;
		}
		
		if (p_locate<1){
			printf("０へは移動不可能です。やり直してください。\n");
			p_locate++ ;
		}
		else if(p_locate>NUMBER){
			printf("%dへは移動できません。やり直してください。\n",NUMBER+1);
			p_locate--;
		}else{
			printf("%dへ移動しました。\n\n",p_locate);
			f = 1;
		}
		
	}while(f == 0);
	
		// プレイヤーが移動したフラグ
		p_action = 2;
	
		return p_locate;
}

// プレイヤーの攻撃
int p_attack(void){
	
	// 攻撃ポイント変数
	int point;
	
	do{
		printf("どこへ撃ちますか？\n");
		scanf("%d",&point);

		if(point > NUMBER || point <1){
			printf("範囲外です。\n");
		}
	}while(point > NUMBER);
	
	// 当たり判定 0なら当たり
	judge = abs(point - e_locate);
	
	printf("%dへ撃ちました！\n",point);
	fflush( stdout ); 
	sleep(1);
	
	if (judge == 0){
		printf("命中！あなたの勝利です！\n");
		exit(1);
		}
	
	if (judge > 2)printf("外れました\n\n");
	if (judge >0 && judge <= 2)printf("反応あり！　近かったようです\n\n");
	
	// プレイヤーが攻撃したフラグ
	p_action = 1;
	
	enemy_turn();
		
}

// 敵の行動
	// 行動パターンは基本的に攻撃。一度撃った位置以外に撃つ。
	// ただし、こちらからの砲撃がなかった場合、移動した可能性があるので「今までに撃った位置」はリセットする。
	// また、近くに砲撃された場合（誤差が２以下の時）は、「移動か待機」、砲撃を２分の１の確率でランダムに選択。
int enemy_turn(void){
	// 敵の行動選択　１は攻撃、２は待機もしくは移動
	int e_action;
	
	// 移動先の候補変数
	int new_e_locate;
	
	printf("敵のターンです\n");
	if(judge<=2){
		e_action =rand()%2+ 1;
	}else{
		e_action = 1;
	}
	
	switch(e_action){
		case 1:
			printf("砲撃してきました！\n");
			e_attack();
			break;
			
		case 2:
			printf("移動か待機のようです。\n\n");
			// 乱数で移動数をー１，０（待機）、＋１の内から選択。もしも移動先が範囲外ならループしてやり直し
			do{
				new_e_locate = 0;
				new_e_locate = e_locate + (rand()%3-1);
			}while(new_e_locate<1 || new_e_locate>NUMBER);
			
			// 移動先を範囲内で決定出来たらe_locateに代入
			e_locate = new_e_locate;
			
			turn ++;
			// プレイヤーのターンへ
			command();
	}
	
}

// 敵の攻撃ポイントの順序をシャッフルする関数
void shuffle(int e_a_point[],unsigned int size){
	unsigned int i,j;
	int tmp;
	
	i = NUMBER - 1;
	
	while(i>0){
		j = rand() % (i + 1);
		
		tmp = e_a_point[j];
		e_a_point[j] = e_a_point[i];
		e_a_point[i] = tmp;
		
		i--;
	}
	
}

// 敵の攻撃関数
int e_attack(void){
	
	// 1ターン目、もしくはプレイヤーが移動・待機した場合は攻撃ポイントをシャッフルする。
	// 	（一度攻撃したポイントに移動した可能性があるから）
	if(turn ==1 || p_action == 2){
	
		// 攻撃ポイントをランダムかつ重ならないようにシャッフル
		shuffle(e_a_point,NUMBER);
		
		// シャッフル後の1回目の攻撃なので１を代入
		n = 1;
	}
	
	fflush( stdout ); 
	sleep(1);
	
	printf("%dに着弾！",e_a_point[n]);
	
	fflush( stdout ); 
	sleep(1);
	
	e_judge = abs(e_a_point[n] - p_locate);
	if (e_judge == 0){
		printf("命中！あなたの負けです……\n");
		exit(0);
		}
	
	if (e_judge > 2)printf("外れました\n\n");
	if (e_judge >0 && e_judge <= 2)printf("危ないところでした。\n\n");
	
	n++;
	
	if(n>NUMBER)n=0;
	
	turn++;
	
	if(turn>NUMBER*2){
		printf("時間切れにより引き分けです。お疲れさまでした。\n");
		exit(0);
	}
	command();

}
