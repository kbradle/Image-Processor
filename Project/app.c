#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct buff{
	char imageName[15];
	char name[15];
	unsigned char* img;
	int width, height, channels;
};

#include "read.c"
#include "write.c"

void addBuffer(struct buff buffer, struct buff* buffers, int* buffCount);
struct buff buffSearch(char* buffName, struct buff* buffers, int buffCount);
void printBuffer(struct buff* buffer, int buffCount);
void printMenu();


int main() {
	printf("Welcome to the UNIX Image Manipulation tool.\n");
	printf("Type \"menu\" to view the list of commands or \"list\" to view your buffers.\n\n");


	struct buff buffers[10];
	int buffCount = 0;

	char p[100];
	gets(p);

	while(1){
		char *command;
		char *imageName;
		char *buffName;

		command = strtok(p," ");


		if(strcmp(command,"menu")==0){
                        printMenu();
                }
		else if(strcmp(command, "read")==0){
			imageName = strtok(NULL," ");
			strtok(NULL," ");
			buffName = strtok(NULL," ");
			struct buff temp = readToBuff(imageName, buffName);
			addBuffer(temp, buffers, &buffCount);
		}
		else if(strcmp(command, "write")==0){
			buffName = strtok(NULL," ");
                        strtok(NULL," ");
                        imageName = strtok(NULL," ");
			writeToImage(buffSearch(buffName, buffers,buffCount), imageName);
		}
		else if(strcmp(command, "list")==0){
			printBuffer(buffers, buffCount);
		}
		else if(strcmp(command, "quit")==0){
			break;
		}
		else{
			printf("\nError: command not found.\n");
		}

		gets(p);
	}

   	return 0;
}

void printMenu(){
	printf("\n----- Commands -----\n");
	printf("\"quit\"\n");
	printf("\"read <image-name> into <buffer-name>\"\n");
	printf("\"write <buffer-name> into <image-name>\"\n\n");
}


void printBuffer(struct buff* buffers, int buffCount){
	printf("\n----- Buffers -----\n");
 	for (int i = 0; i < buffCount; i++){
                printf("%s contains %s\n", buffers[i].name, buffers[i].imageName);
        }
}

void addBuffer(struct buff buffer, struct buff* buffers, int* buffCount){
	int k = -1;
        for (int i = 0; i < *buffCount; i++){
        	if(strcmp(buffers[i].name, buffer.name)==0){
                        k = i;
                	break;
        	}
        }
	if(k == -1){
                buffers[*buffCount].img = buffer.img;
                strcpy(buffers[*buffCount].imageName, buffer.imageName);
		strcpy(buffers[*buffCount].name, buffer.name);
		buffers[*buffCount].width = buffer.width;
        	buffers[*buffCount].height = buffer.height;
        	buffers[*buffCount].channels = buffer.channels;
		(*buffCount)++;
        }
        else{
                buffers[k].img = buffer.img;
                strcpy(buffers[k].imageName, buffer.imageName);
                strcpy(buffers[k].name, buffer.name);
                buffers[k].width = buffer.width;
                buffers[k].height = buffer.height;
                buffers[k].channels = buffer.channels;
	}
}

struct buff buffSearch(char* buffName, struct buff* buffers, int buffCount){
	for (int i = 0; i < buffCount; i++){
                if(strcmp(buffers[i].name, buffName)==0){
                       	return buffers[i];
                }
        }
	printf("Error: buffer not found.\n");
	struct buff temp;
	return temp;
}
