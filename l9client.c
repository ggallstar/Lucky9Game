#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <time.h>
#define MAX_STRING_LEN 80
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_BLACK   "\033[22;30m "
#define ANSI_COLOR_RESET   "\x1b[0m"
#define ANSI_COLOR_GREEN  "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\e[33m"
void die_with_error(char *error_msg){
    printf("%s", error_msg);
    exit(-1);
}

int drawCard(int cards[]){
	int card;
	int randonNum = rand() % 12;
	card = cards[randonNum];
	
	return card;

}

char drawColors(int color[]){
	char colorvalue;
	int randonNum = rand() % 4;
	colorvalue = color[randonNum];
	
	return colorvalue;
}
char ask(char *ask,int pcard1,char pcardcolor1,int pcard2, char pcardcolor2,int pcard3,char pcardcolor3,int playersum){
			if(*(ask) == 'y'){
				printf("Your cards are: ");
					if(pcardcolor1 == 1){
						printf(ANSI_COLOR_RED " RD " ANSI_COLOR_RESET );
					}else if(pcardcolor1 == 2){
						printf(ANSI_COLOR_RED " RH " ANSI_COLOR_RESET );
					}else if(pcardcolor1 == 3){
						printf(ANSI_COLOR_BLACK " BC " ANSI_COLOR_RESET );
					}else if(pcardcolor1 == 4){
						printf(ANSI_COLOR_BLACK " BS " ANSI_COLOR_RESET );
					}
				printf("%d",pcard1);
					if(pcardcolor2 == 1){
						printf(ANSI_COLOR_RED " RD " ANSI_COLOR_RESET);
					}else if(pcardcolor2 == 2){
						printf(ANSI_COLOR_RED " RH " ANSI_COLOR_RESET );
					}else if(pcardcolor2 == 3){
						printf(ANSI_COLOR_BLACK " BC " ANSI_COLOR_RESET );
					}else if(pcardcolor2 == 4){
						printf(ANSI_COLOR_BLACK " BS " ANSI_COLOR_RESET );
					}
			 	printf("%d",pcard2);
					if(pcardcolor3 == 1){
						printf(ANSI_COLOR_RED " RD " ANSI_COLOR_RESET);
					}else if(pcardcolor3 == 2){
						printf(ANSI_COLOR_RED " RH " ANSI_COLOR_RESET );
					}else if(pcardcolor3 == 3){
						printf(ANSI_COLOR_BLACK " BC " ANSI_COLOR_RESET );
					}else if(pcardcolor3 == 4){
						printf(ANSI_COLOR_BLACK " BS " ANSI_COLOR_RESET );
					}
			 	printf("%d \n",pcard3);
				playersum = (pcard1+pcard2+pcard3)%10;
				printf("Your sum is: %d \n", playersum);
				return playersum;
			}
}
char show(int pcard1,char pcardcolor1,int pcard2, char pcardcolor2,int playersum){
	printf("Your cards are: ");
		if(pcardcolor1 == 1){
			printf(ANSI_COLOR_RED " RD " ANSI_COLOR_RESET );
		}else if(pcardcolor1 == 2){
			printf(ANSI_COLOR_RED " RH " ANSI_COLOR_RESET );
		}else if(pcardcolor1 == 3){
			printf(ANSI_COLOR_BLACK " BC " ANSI_COLOR_RESET );
		}else if(pcardcolor1 == 4){
			printf(ANSI_COLOR_BLACK " BS " ANSI_COLOR_RESET );
		}
	printf("%d",pcard1);
		if(pcardcolor2 == 1){
			printf(ANSI_COLOR_RED " RD " ANSI_COLOR_RESET);
		}else if(pcardcolor2 == 2){
			printf(ANSI_COLOR_RED " RH " ANSI_COLOR_RESET );
		}else if(pcardcolor2 == 3){
			printf(ANSI_COLOR_BLACK " BC " ANSI_COLOR_RESET );
		}else if(pcardcolor2 == 4){
			printf(ANSI_COLOR_BLACK " BS " ANSI_COLOR_RESET );
		}
	
	printf("%d \n",pcard2);
	playersum = (pcard1 + pcard2)%10;
	printf( "Your sum : %d \n", playersum);
	return playersum;
}			
int main(int argc,  char *argv[]){
    
    int client_sock,  port_no, r, s, n;
    struct sockaddr_in server_addr;
    struct hostent *server;
	time_t t;

	/* Intializes random number generator */
    	srand((unsigned) time(&t));	
	char currency[256], colorbuff[2],buffer[256], pcardctr[15];
	int cards[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10};
	int color[] = {1,2,3,4};
	char ans = 'y';
	int psum,bet,money=500, cardAtoi;
	int recvc,sendc,totalbet,recvAtoi,inputAtoi,sendrctr,sendbctr,recvrctr,recvbctr,psend,precv;
	


    
    if (argc < 3) {
        printf("Usage: %s hostname port_no",  argv[0]);
        exit(1);
    }

    printf("Client starting ...\n");
    // Create a socket using TCP
    client_sock = socket(AF_INET,  SOCK_STREAM,  0);
    if (client_sock < 0) 
        die_with_error("Error: socket() Failed.");

    printf("Looking for host '%s'...\n", argv[1]);
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        die_with_error("Error: No such host.");
    }
    printf("Host found!\n");

    // Establish a connection to server
    port_no = atoi(argv[2]);
    bzero((char *) &server_addr,  sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,  
         (char *)&server_addr.sin_addr.s_addr, 
         server->h_length);
         
    server_addr.sin_port = htons(port_no);

    printf("Connecting to server at port %d...\n", port_no);
    if (connect(client_sock, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) 
        die_with_error("Error: connect() Failed.");

    printf("Connection successful!\n");

    // Communicate
	
	
	system("clear");	
	while(1){
			recvc = recv(client_sock, currency, 255, 0);
			recvAtoi = atoi(currency);
			if (money <= 0){
				die_with_error(ANSI_COLOR_RED "No money left to play! Thank you for playing! BYE!!!!\n" ANSI_COLOR_RESET);
				close(client_sock);
				break;
			}else if (money >= 1000){
				close(client_sock);
				die_with_error(ANSI_COLOR_GREEN "Your opponent has no money left to play! Thank you for playing! BYE!!!!\n" ANSI_COLOR_RESET);
				break;
			}
				
				printf( "Your total money on hand left is: %d\n",money);
					printf( "How much do you want to bet?: ");	
					
						fgets(currency, 255, stdin);
						inputAtoi = atoi(currency);
					if(inputAtoi>money){
						die_with_error("You've entered invalid amount!\n");
						
					}
					
					sendc = send(client_sock, currency, strlen(currency), 0);

					printf("[Player1's bet is only]: %d\n", recvAtoi);
					
					totalbet = recvAtoi + inputAtoi;
					printf(ANSI_COLOR_GREEN "\n[Total winning pot: %d]\n\n"ANSI_COLOR_RESET, totalbet);
					
									
			while(1){
				int playersum, rctr=0, bctr=0, cardctr=0; //red and black counter	
				int pcard1 = drawCard(cards);
				char pcardcolor1 = drawColors(color);
				int pcard2 = drawCard(cards);
				char pcardcolor2 = drawColors(color);
				int pcard3 = drawCard(cards);
				char pcardcolor3 = drawColors(color);
				/*printf("pcardcolor1=%d\n", pcardcolor1);
				printf("pcardcolor2=%d\n", pcardcolor2);
				printf("pcardcolor3=%d\n", pcardcolor3);*/
				
				//counter for red cards on hand
				if(pcardcolor1 == 1){
					rctr++;
				}
				if(pcardcolor1 == 2){
					rctr++;
				}
				if(pcardcolor2 == 1){
					rctr++;
				}
				if(pcardcolor2 == 2){
					rctr++;
				}
			
			
				psum = show(pcard1,pcardcolor1,pcard2,pcardcolor2,playersum);
					recvrctr =  recv(client_sock, &pcardctr[14], 255, 0);
					int redAtoi = atoi(&pcardctr[14]);	
					
				printf( "Do you want to draw another card? [y]: YES , [n]: NO   :");
				fgets(&buffer[20], 255, stdin);
				if(buffer[20] == 'y'){
					if(pcardcolor3 == 1){
							rctr++;
						}
						if(pcardcolor3 == 2){
							rctr++;
						}
						snprintf(&colorbuff[0], 10, "%d\n", rctr);
						sendrctr = send(client_sock,&colorbuff[0], strlen(&colorbuff[0]), 0);
					psum = ask(&buffer[20],pcard1,pcardcolor1,pcard2,pcardcolor2,pcard3,pcardcolor3,playersum);
					snprintf(&buffer[5], 10, "%d\n", psum);
					n = send(client_sock, &buffer[5], strlen(&buffer[5]), 0);	
					cardctr = 3; 
						
				}else{
					snprintf(&colorbuff[0], 10, "%d\n", rctr);
					sendrctr = send(client_sock,&colorbuff[0], strlen(&colorbuff[0]), 0);
					snprintf(&buffer[5], 10, "%d\n", psum);
					n = send(client_sock, &buffer[5], strlen(&buffer[5]), 0);
					cardctr = 2; 
					
				}
			
					if(cardctr == 3){
						snprintf(&pcardctr[1], 10, "%d\n", cardctr);
						psend = send(client_sock, &pcardctr[1], strlen(&pcardctr[1]), 0);	
					}
				
					if(cardctr == 2){
						snprintf(&pcardctr[4], 10, "%d\n", cardctr);
						psend = send(client_sock, &pcardctr[4], strlen(&pcardctr[4]), 0);	
					} 
				
					
				n = recv(client_sock, &buffer[25], 255, 0);
				if (n < 0) die_with_error("Error: recv() Failed.");		
				int score = atoi(&buffer[25]);
				
				system("clear");
				printf("--------------------------------------------------------------------------------\n");
				printf("[player1's cards total value is:] : %d\n", score);
				precv = recv(client_sock, &pcardctr[3], 255, 0);
						cardAtoi = atoi(&pcardctr[3]);
				if(score < psum){
					printf("Your cards total value is: : %d\n", psum);
					printf(ANSI_COLOR_GREEN "You Win!\n" ANSI_COLOR_RESET);
					money = money + recvAtoi;
						if (money <= 0){
							n = send(client_sock, &buffer[5], strlen(&buffer[5]), 0);
							printf( "Your total money on hand left is: %d\n",money);
							die_with_error(ANSI_COLOR_RED "No money left to play! Thank you for playing! BYE!!!!\n" ANSI_COLOR_RESET);
							close(client_sock);
							break;
						}else if (money >= 1000){
							n = send(client_sock, &buffer[5], strlen(&buffer[5]), 0);
							printf( "Your total money on hand left is: %d\n",money);
							die_with_error(ANSI_COLOR_GREEN "Your opponent has no money left to play! Thank you for playing! BYE!!!!\n" ANSI_COLOR_RESET);
							close(client_sock);
							break;
						}else if(n <= 0){
							printf( "Your opponent disconnected\n");
						}
				}else if( score > psum ){
					printf("Your cards total value is: : %d\n", psum);
					printf(ANSI_COLOR_RED "You Lose!\n" ANSI_COLOR_RESET);
					money = money - inputAtoi;
						if (money <= 0 || n <= 0){
							n = send(client_sock, &buffer[5], strlen(&buffer[5]), 0);
							printf( "Your total money on hand left is: %d\n",money);
							die_with_error(ANSI_COLOR_RED "No money left to play! Thank you for playing! BYE!!!!\n" ANSI_COLOR_RESET);
							close(client_sock);
							break;
						}else if (money >= 1000|| n <= 0){
							n = send(client_sock, &buffer[5], strlen(&buffer[5]), 0);
							printf( "Your total money on hand left is: %d\n",money);
							die_with_error(ANSI_COLOR_GREEN "Your opponent has no money left to play! Thank you for playing! BYE!!!!\n" ANSI_COLOR_RESET);
							close(client_sock);
							break;
						}else if(n <= 0){
							printf( "Your opponent disconnected\n");
							return 0;
						}
				}else if ( score == psum){
					
					if(rctr == redAtoi && cardctr == cardAtoi || rctr == redAtoi){
						printf(ANSI_COLOR_YELLOW "ITS A DRAW!!!!!\n" ANSI_COLOR_RESET);					
					}else if(cardctr > cardAtoi){
						printf(ANSI_COLOR_RED "You Lose! Because you have 3 cards on hand.\n" ANSI_COLOR_RESET);
					}else if(rctr > redAtoi){
						printf(ANSI_COLOR_GREEN "You Win! Because you have %d red cards on hand.\n" ANSI_COLOR_RESET, rctr);
					}else if(rctr < redAtoi){
						printf(ANSI_COLOR_RED "You Lose! Because you have less than %d red cards on hand.\n" ANSI_COLOR_RESET, redAtoi);
					}else if(cardctr < cardAtoi){
						printf(ANSI_COLOR_GREEN "You Win! Because you only have 2 cards on hand.\n" ANSI_COLOR_RESET);
					}
				}
				
				//n = recv(client_sock,buffer, 255, 0);
						//cardAtoi = atoi(&pcardctr[3]);
					
					printf("redAtoi=%d\n",redAtoi);
							
				printf("--------------------------------------------------------------------------------\n");
				printf("\n\n\n");
				
				break;
		
			}
			
		}
		
    close(client_sock);
    
    return 0;
}







