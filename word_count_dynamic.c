/*
 ============================================================================
 Name        : word_count.c
 Author      : Nicholas Roethel
 Description : A program which reads words their frequencies by length. 
 The program then has the ability to print them in ascending word length, 
 or descending frequencies. It is possible to print just the frequencies 
 or the frequencies and the words that contributed.  
 Repetitions and special characters are deleted.
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <ctype.h>
char delim[7] = {' ', ',', '\n', ';', '.', '(', ')'}; //characters to eliminate
typedef struct theWords theWords; //define the words
typedef struct frequencies frequencies; //defines frequency
int count = 0;

struct frequencies{
	int len;
	int freq;
	frequencies *next;
};

struct theWords{
	char *word;
	int length;
	theWords *next; 
};

int getMaxFrequency(frequencies *head){ //gets the highest frequency
	frequencies *tmp = head;
	int maxfreq = 0;
	while(tmp != NULL){
		if(tmp->freq > maxfreq){
			maxfreq = tmp->freq;
		}
		tmp = tmp->next;
	}
	free(tmp);
	return maxfreq;

}
void printSortedFrequencies(frequencies *front, theWords *head, theWords *head2, int maxfreq){ //print words that are sorted and their frequencies
	frequencies *temp = front;
	theWords *temporary = head;
	theWords *curr = head2;

	for(int i = maxfreq; i>0; i--){
		temp =front;
		while(temp != NULL){
			if(temp->freq == i){
				temporary = head;
				int invisfreq = 0;
				while(temporary != NULL){
					if(temporary->length == temp->len){
						invisfreq ++;
					}
					temporary = temporary->next;
				}
				curr = head2;
				int realfreq = 0;

				while(curr !=NULL){
					if(curr->length == temp->len){
						realfreq ++;
					}
					curr = curr->next;
				}

				printf("Count[%02d]=%02d;\n",temp->len,realfreq);
				temporary = head;
				count = 0;
			}
			temp = temp->next;
		}
	}
	free(temporary);
	free(temp);
	free(curr);
}

void printSortedWords(frequencies *front, theWords *head, theWords *head2, int maxfreq){ //print words that are sorted
	frequencies *temp = front;
	theWords *temporary = head;
	theWords *curr = head2;
	
	for(int i = maxfreq; i>0; i--){
		temp =front;
		while(temp != NULL){
			if(temp->freq == i){
				temporary = head;
				int invisfreq = 0;
				while(temporary != NULL){
					if(temporary->length == temp->len){
						invisfreq ++;
					}
					temporary = temporary->next;
				}
				curr = head2;
				int realfreq = 0;
				while(curr !=NULL){
					if(curr->length == temp->len){
						realfreq ++;
					}
					curr = curr->next;
				}
				printf("Count[%02d]=%02d; ",temp->len,realfreq);
				temporary = head;
				count = 0;
				while(temporary != NULL){
					if(temporary->length == temp->len){
						++count;
						if(count == 1){
							printf("(words: ");
						}

						if(count<invisfreq-1){
							printf("\"%s\", ",temporary->word);
						}
						else if(count<invisfreq){
							printf("\"%s\" and ",temporary->word );
						}

						if(count == invisfreq){
							printf("\"%s\")",temporary->word);
						}

					}
					temporary = temporary->next; 
				}
				printf("\n");
			}
			temp = temp->next;
		}
	}
	free(temporary);
	free(temp);
	free(curr);	
}

frequencies *appendFrequencies(frequencies *head, frequencies *newnode){ //appends the nodes that stores frequencies
	frequencies *curr = head;
	if(head == NULL){
		return newnode;
	}
	while(curr->next != NULL){
		curr = curr->next;
	}
	curr->next = newnode;
	return head;
}

void finalPrintWords(theWords *head, int freq, int length){ //prinds the sorted words
	int count = 0;
	theWords *current = head; 
	while(current != NULL){
		if(current->length == length){
			count ++;
			if(count == 1){
				printf(" (words: ");
			}
			if(count<freq-1){
				printf("\"%s\", ",current->word);
			}
			else if(count<freq){
				printf("\"%s\" and ",current->word );
			}

			if(count == freq){
				printf("\"%s\")",current->word);
			}
		}
		current = current->next;
	}
	free(current);
}


int getFrequencies(int size, theWords *head){ //gets the frequency of words in a list
	int frequency = 0;
	theWords *current = head; 
	while(current != NULL){
		if(current->length == size){
			frequency ++;
		}
		current = current->next;
	}
	free(current);
	return frequency;
}


void sortedInsert(theWords** head3, theWords* newnode){ //sorts words alphabetically upon insertion on list
	int repeat = 0;
	theWords *current;

	current = *head3;
	while(current!=NULL){
		if(strcmp(current->word,newnode->word)==0){ //checks for reapeats
			return;
		}
		current = current->next;
	}

	if (*head3 == NULL || strcasecmp((*head3)->word,newnode->word) >0){ //checks if head is null or if it needs to be inserted before head;
		newnode->next = *head3;
		*head3 = newnode;
		repeat ++;
		return;
	}
	else if((*head3)->word == newnode->word){ //checks if equal to head
		return;
	}
	else if((*head3)->next==NULL){ //appends if only head is present
		(*head3)->next = newnode;
		return;
	}

	else{

		if(((*head3)->next != NULL) && strcasecmp(newnode->word,(*head3)->next->word)<0){ //inserts after the head
			newnode->next = (*head3)->next;
			(*head3)->next = newnode;
			return;
		}

		if(((*head3)->next->next != NULL) && strcasecmp(newnode->word,(*head3)->next->next->word)<0){  //inserts in middle of list, two after the head
			newnode->next = (*head3)->next->next;
			(*head3)->next->next = newnode;
			return;
		}

		current = *head3;

		if(((*head3)->next) != NULL){
			current = (*head3)->next;
			while(current != NULL){
				if(strcasecmp(current->word,newnode->word)==0){ //checks for repeats
					return;
				}
				current = current->next;
			}
		}
		current = *head3;

		if (strcasecmp(current->next->next->word,newnode->word)>0){ //inserts after the head
			newnode->next = current->next->next;
			current->next = newnode;
			return;
		}

		while(current->next->next!=NULL && strcasecmp(current->next->next->word,newnode->word)<0){ //increments until inserted or near the end of the list
			if(strcasecmp(current->word,newnode->word)==0){ //returns if repeat
				return;
			}
			current = current->next;
		}

		if(current->next->next == NULL){ //if it should be appended 
			if(strcmp(newnode->word,current->next->word)==0){
				return;
			}
			current->next->next = newnode;
			newnode->next = NULL;
			return;
		}
		else if (strcasecmp(current->next->next->word,newnode->word)>0){ //if it should be inserted in the middle
			newnode->next = current->next->next;
			current->next->next = newnode;
			return;
		}
		return;

	}
}


void printFrequencies(theWords *head, int len){ //prints frequencies without a newline
	int frequency = 0;
	theWords* temp = head;
	for(; temp != NULL; temp = temp->next){
		if(temp->length == len){
			frequency ++;
		}
	}
	if(frequency != 0){
		printf("Count[%02d]=%02d;",len,frequency);
		
	}
	free(temp);
}

void onlyFrequencies(theWords *head, int len){ //prints frequencies followed by a newline
	int frequency = 0;
	theWords* temp = head;
	for(; temp != NULL; temp = temp->next){
		if(temp->length == len){
			frequency ++;
		}
	}
	if(frequency != 0){
		printf("Count[%02d]=%02d;\n",len,frequency);
		
	}
	free(temp);
}

void *customMalloc(size_t item){ //malloc size
	void *pointer;
	pointer = malloc(item);
	if (pointer == NULL) {
		fprintf(stderr, "malloc has %zu failed", item);
		exit(1);
	}
	return pointer;
}

theWords *noRepeats(theWords *head2, theWords *newnode){ //list with no repeats
	count ++;
	theWords *curr = head2;
	if(head2 == NULL){
		return newnode;
	}
	while(curr->next != NULL){
		if((strcasecmp(curr->word,newnode->word)==0)||(strcmp(curr->word,newnode->word))==0){
			curr->word = newnode->word;
			curr->length = newnode->length;
			return head2;
		}
		curr = curr->next;
	}

	if((strcasecmp(curr->word,newnode->word)==0)||(strcmp(curr->word,newnode->word))==0){
		curr->word = newnode->word;
		curr->length = newnode->length;
		return head2;
	}

	curr->next = newnode;
	return head2;	
	
}

theWords *append(theWords *head, theWords *newnode){ //append words into the list
	theWords *curr = head;
	if(head == NULL){
		return newnode;
	}
	while(curr->next != NULL){
		curr = curr->next;
	}
	curr->next = newnode;
	return head;
}

frequencies *NewNode (int frequency, int length){ //node which stores frequencies and lengths
	frequencies *theItem;
	theItem = (frequencies *) customMalloc(sizeof(frequencies));
	theItem->freq = frequency;
	theItem->len = length;
	theItem->next = NULL;
	return theItem;
}

theWords *createNewNode (char *word, int length){ //creates nodes to store length and words
	for(int i = 0; word[i]; i++){
		word[i] = tolower(word[i]);
	}
	theWords *theItem;
	theItem = (theWords *) customMalloc(sizeof(theWords));
	theItem->word = (char*)malloc(strlen(word)+1);
	strncpy(theItem->word, word, strlen(word)+1);
	theItem->length = length;
	theItem->next = NULL;
	return theItem;
}

void printWords(theWords *head){ //print words
	theWords* tmp = head;
	
	for(; tmp != NULL; tmp = tmp->next){
		printf("%s ",tmp->word);
	}
	printf("\n");
}


int main(int argc, char const *argv[]){	
	int count = 0;
	int sort = 0;
	int printwords = 0;
	int maxlen = 0;
	theWords *head = NULL;
	theWords *head2 = NULL;
	theWords *head3 = NULL;
	frequencies *head4 = NULL;
	char* tmpWord;
	int len = 0;
	FILE *input = NULL;

	if(argc <3){
		printf("NO FILE FOUND\n");
		return 1;
	}
	
	else{
		while(argv[count] != NULL){
			if(strcmp(argv[count],"--infile")==0){ //find the file
				input = fopen(argv[count+1], "r" ); //open the file
			}
			if(strcmp(argv[count],"--sort")==0){
				sort = 1;
			}
			if(strcmp(argv[count],"--print-words")==0){
				printwords = 1;
			}

			count ++;
		}
	}

	if(input == NULL){
		printf("NO FILE FOUND\n");
	}

	else{
		fseek(input, 0L, SEEK_END);
		size_t filesize = ftell(input);
		rewind(input);
				char* buffer = (char*)malloc(filesize+1); //create memory
				fread(buffer, 1,filesize,input); //insert words
				buffer[filesize] = '\0';
				int countPrint = 0;
				tmpWord = strtok(buffer,delim);
				while(tmpWord != NULL){ 
					countPrint++;
					len = strlen(tmpWord);
					if(len>maxlen){
						maxlen = len;
					}
					theWords *newnode = createNewNode(tmpWord, len);
					theWords *newnode2 = createNewNode(tmpWord, len);
					theWords *newnode3 = createNewNode(tmpWord, len);

					head = append(head, newnode);
					head2 = noRepeats(head2,newnode2);	
					sortedInsert(&head3,newnode3);
					tmpWord = strtok(NULL,delim);
				}
				if(sort == 0 && printwords == 0){ //if its just the file
					for (int i = 0; i<=maxlen; i ++)
					{
						onlyFrequencies(head, i);
					}
					return(0);
				}

				else if(sort == 0 && printwords == 1){ //file and printwords
					frequencies *tmp = NULL;
					for (int i = 0; i<=maxlen; i ++)
					{
						printFrequencies(head, i);
						int temp = getFrequencies(i, head3);
						int temp2 = getFrequencies(i, head);
						if(temp >0){
							tmp = NewNode(temp2,i);
							head4 = appendFrequencies(head4, tmp);
						}
						finalPrintWords(head3,temp,i);
						if(temp>0){
							printf("\n");
						}
					}

					return(0);
				}
						else if(sort == 1 && printwords ==0){ //file and sort
							frequencies *tmp = NULL;
							for (int i = 0; i<=maxlen; i ++)
							{
								int temp = getFrequencies(i, head3);
								int temp2 = getFrequencies(i, head);
								if(temp >0){
									tmp = NewNode(temp2,i);
									head4 = appendFrequencies(head4, tmp);
								}
							}

							int maxfreq = getMaxFrequency(head4);
							printSortedFrequencies(head4,head3,head,maxfreq);
							return (0);
						}
						else if(sort == 1 && printwords  == 1){ //if its file sort and print-words
							frequencies *tmp = NULL;
							for (int i = 0; i<=maxlen; i ++)
							{
								int temp = getFrequencies(i, head3);
								int temp2 = getFrequencies(i, head);
								if(temp >0){
									tmp = NewNode(temp2,i);
									head4 = appendFrequencies(head4, tmp);
								}
							}
							int maxfreq = getMaxFrequency(head4);
							printSortedWords(head4,head3,head,maxfreq);
							fclose(input);
							return(0);
						}
					}
				}
