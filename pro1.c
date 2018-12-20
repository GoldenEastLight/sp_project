#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

void clear();
void openning(FILE *fd);
void win_me();
void win_you(FILE *fd);
void lose_me();
void lose_you(FILE *fd);

main(int ac,char *av[]){
	int fd;

	int bet =30;
	int bet_to = 0;
	int k=0;
	int betting = 0;

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
	char *op = "Opponent bet ";

	write(fd,message,strlen(message));
	openning(fd);
	sleep(5);

	int k_1=0;
	int k_2=0;

	struct stat st1;
	struct stat st2;

	int num_1=0;
	int num_2=0;

	char s1[10];
	memset(s1,'\0',10);
	int conti = 0;
	clear();
	int draw = 0;
	

	while(bet>0){
                if(conti==0 && draw ==0){
                    betting =0;
                }
		srand(time(NULL));
		k = rand()%9;
		stat("bet1.txt",&st1);
		stat("bet2.txt",&st2);
		printf("\n===================================================================\n NOW BETTING : %d\n",betting);
		if(conti==0){
		if(id==1){
			sleep(2);
			card1 = fopen("card1.txt","wr");
			fprintf(card1,"%d\n",k+1);
			fclose(card1);
			write(fd,your,strlen(your));
			write(fd,card[k],1);
			sleep(2);
			printf("\nTOTAL BET: %d\nENTER:",bet);
			scanf("%d",&bet_to);
			bet1 = fopen("bet1.txt","wr");
			fprintf(bet1,"%d\n",bet_to);
			fclose(bet1);
			stat("bet2.txt",&st2);
			bet = bet-bet_to;

			while((st2.st_size==0)){
				printf("wait...\n");
				sleep(1);
				stat("bet2.txt",&st2);
			}

			
		}
		else if(id==2){
			sleep(2);
			card2 = fopen("card2.txt","wr");
			fprintf(card2,"%d\n",k+1);
			fclose(card2);
			write(fd,your,strlen(your));
			write(fd,card[k],1);
			sleep(2);
			printf("\nTOTAL BET: %d\nENTER:",bet);
			scanf("%d",&bet_to);
			bet2 = fopen("bet2.txt","wr");
			fprintf(bet2,"%d\n",bet_to);
			fclose(bet2);
			stat("bet1.txt",&st1);
			bet = bet-bet_to;
			while((st1.st_size==0)){
				printf("wait....\n");
				sleep(1);
				stat("bet1.txt",&st1);
			}
		}
		}
		else if(conti ==1){
			if(id == 1){
				sleep(2);
				printf("\nTOTAL BET: %d\nENTER:",bet);
				scanf("%d",&bet_to);
				bet1 = fopen("bet1.txt","wr");
				fprintf(bet1,"%d\n",bet_to);
				fclose(bet1);
				stat("bet2.txt",&st2);
				bet = bet-bet_to;
				while((st2.st_size ==0)){
					printf("wait....\n");
					sleep(1);
					stat("bet2.txt",&st2);
				}
			}
			else if(id == 2){
				sleep(2);
				printf("\nTOTAL BET: %d\nENTER:",bet);
				scanf("%d",&bet_to);
				bet2 = fopen("bet2.txt","wr");
				fprintf(bet2,"%d\n",bet_to);
				fclose(bet2);
				stat("bet1.txt",&st1);
				bet = bet-bet_to;
				while((st1.st_size ==0)){
					printf("wait ....\n");
					sleep(1);
					stat("bet1.txt",&st1);
				}

			}
		}
		bet1 = fopen("bet1.txt","r");
		bet2 = fopen("bet2.txt","r");
		fscanf(bet1,"%d",&k_1);
		fscanf(bet2,"%d",&k_2);

		betting += k_1;
		betting += k_2;

		fclose(bet1);
		fclose(bet2);
		card1 = fopen("card1.txt","r");
		card2 = fopen("card2.txt","r");
		fscanf(card1,"%d",&num_1);
		fscanf(card2,"%d",&num_2);


		if(k_2 == k_1){
			draw =0;
			write(fd,op,strlen(op));
			sprintf(s1,"%d",k_2);
			write(fd,s1,strlen(s1));
			write(fd,blank,strlen(blank));
			conti =0;
			sleep(2);
			printf("set is end\n");
			if(id ==1){
				if(num_1>num_2){
			                printf("YOU WIN \n you get a %d point\n",betting);
					bet = bet + betting;
					betting =0;
					clear();
					sleep(2);
				}
				else if(num_1 == num_2){
					printf("DRAW! \n BET WILL BE MAINTAINED\n");
					draw = 1;
					clear();
					sleep(2);
				}
			}
			else if(id==2){
				if(num_2>num_1){
					printf("YOU WIN \n you get a %d point\n",betting);
					bet = bet + betting;
					betting = 0;
					clear();
					sleep(2);
				}
				else if(num_1 == num_2){
					printf("DRAW! \n BET WILL BE MAINTAINED\n");
					draw = 1;
					clear();
					sleep(2);
				}
			}
		}
		else if(k_2!=k_1){
			sleep(2);
			conti = 1;
			if(id==1){
				write(fd,op,strlen(op));
				sprintf(s1,"%d",k_1);
				write(fd,s1,strlen(s1));
				write(fd,blank,strlen(blank));
				clear();
				sleep(2);
			}
			else if(id ==2){
				write(fd,op,strlen(op));
				sprintf(s1,"%d",k_2);
				write(fd,s1,strlen(s1));
				write(fd,blank,strlen(blank));
				clear();
				sleep(2);
			}
		}
		sleep(5);

	}
	lose_me();
	win_you(fd);
	pause();
	
}

void clear(){

	FILE *bet1=NULL;
	FILE *bet2=NULL;
	bet1 = fopen("bet1.txt","w");
	bet2 = fopen("bet2.txt","w");
	fprintf(bet1,"%s","");
	fprintf(bet2,"%s","");
	fclose(bet1);
	fclose(bet2);
}

void openning(FILE *fd){
	char buf[400];
	memset(buf,'\0',400);
	FILE *openning=NULL;
	openning = fopen("openning.txt","r");
	while(fgets(buf,400,openning)){
		write(fd,buf,strlen(buf));
	}
	fclose(openning);
	
}

void win_me(){
	char buf[400];
	memset(buf,'\0',400);
	FILE *fp = fopen("win.txt","r");
	while(fgets(buf,400,fp)){
		puts(buf);
	}
	fclose(fp);
}

void win_you(FILE *fd){
	char buf[400];
	memset(buf,'\0',400);
	FILE *fp = fopen("win.txt","r");
	while(fgets(buf,400,fp)){
		write(fd,buf,strlen(buf));
	}
	fclose(fp);
}

void lose_me(){
        char buf[400];
	memset(buf,'\0',400);
	FILE *fp = fopen("lose.txt","r");
	while(fgets(buf,400,fp)){
		puts(buf);
	}
	fclose(fp);
}
void lose_you(FILE *fd){
        char buf[400];
	memset(buf,'\0',400);
	FILE *fp = fopen("lose.txt","r");
	while(fgets(buf,400,fp)){
		write(fd,buf,strlen(buf));
	}
	fclose(fp);
}

