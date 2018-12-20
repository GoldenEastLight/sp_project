#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <time.h>



main(int ac,char *av[]){
	int fd;

	int bet =10;
	int bet_to = 0;
	int k=0;

	int id=0;
	int o_k= 0;


	FILE *bet1;
	FILE *bet2;
	FILE *con = fopen("con.txt","wr");

	FILE *card1=NULL;
	FILE *card2=NULL;
	char *con1 = "p1 is connected!";
	char *con2 = "p2 is connected!";

	char *your = "\n Opponent's card is ";
	char *blank = "\n";
	fd = open(av[1],O_WRONLY);
	char card[9][1];
	memset(card,'\0',8*1);
	card[0][0] ='1';
	card[1][0] ='2';
	card[2][0] ='3';
	card[3][0] ='4';
	card[4][0] ='5';
	card[5][0] ='6';
	card[6][0] ='7';
	card[7][0] ='8';
	card[8][0] ='9';

	if(strstr(av[1],"/1")!=NULL){
		fprintf(con,"%s\n","p1");
		write(fd,con1,strlen(con1));
		sleep(3);
		id = 1;
		
	}
	else if(strstr(av[1],"/0")!=NULL){
		fprintf(con,"%s\n","p2");
		write(fd,con2,strlen(con2));
		sleep(3);
		id = 2;
	}
	char *message = "\n-----------------Start Game-------------------\n";

	write(fd,message,strlen(message));
	sleep(5);

	while(bet>0){
		srand(time(NULL));
		k = rand()%9;
		if(id==1){
			card1 = fopen("card1.txt","wr");
			fprintf(card1,"%d\n",k+1);
			write(fd,your,strlen(your));
			write(fd,card[k],1);
			sleep(1);
			printf("\nyour bet is %d how?",bet);
			scanf("%d",&bet_to);
		}
		else if(id==2){
			card2 = fopen("card2.txt","wr");
			fprintf(card2,"%d\n",k+1);
			write(fd,your,strlen(your));
			write(fd,card[k],1);
			sleep(1);
			printf("\nyour bet is %d how?",bet);
			scanf("%d",&bet_to);

		}
		fclose(card1);
		fclose(card2);
	}
	
}
