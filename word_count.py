
 # ============================================================================
 # Name        : word_count.py
 # Author      : Nicholas Roethel
 # Description : A program which reads words and stores their frequencies. 
 # The program then has the ability to print them in ascending word length,
 # or descending frequencies. It is possible to print just the frequencies or 
 # the frequencies and the words that contributed. Repetitions and special 
 # characters are deleted. 
 # ============================================================================
 
import sys
import re
import operator
import argparse

parser = argparse.ArgumentParser() 
parser.add_argument('--infile', required = True) #makes infile a required argument
parser.add_argument('--print-words', action = 'store_true') #looks for print-words
parser.add_argument('--sort', action = 'store_true') #looks for sort
args = parser.parse_args()

def printWords(frequencies, words): #a function which prints words and their frequencies

	for item in frequencies:
			print(('Count[%02d]=%02d; (words: ' % item), end = '')
			x = 0
			for word in words:
				if len(word) == item[0]:
					x = x +1

			for word in words:
				if len(word) == item[0]:
					x = x - 1
					if(x==0):
						print("\"",end = '');
						print(word, end = '')
						print("\")");
					elif(x==1):
						print("\"",end = '');
						print(word, end = '')
						print("\" and ",end = '');
					else: 
						print("\"",end = '');
						print(word, end = '')
						print("\", ", end = '');


def printFrequencies(printList): #a function which prints the frequencies
		for item in printList:
			print('Count[%02d]=%02d;' % item)
	

def main(): #opens the file, makes lists of words and frequencies and calls the appropriate functions
	
	with open(args.infile, "r") as file: 
		thefile = file.read()
		delimfile = thefile.split()
		words = []
		theword = []
		for word in delimfile:
			theword = (re.sub('[^0-9a-zA-Z]', '', word))
			theword = theword.lower()
			words.append(theword) 

		sorted_words = sorted(words)
		words_once = sorted(list(set(sorted_words)))
		lengths = []
		lengths = list(map(len, words))
		the_frequencies = {y:lengths.count(y) for y in lengths}
		sorted_by_length = sorted(the_frequencies.items())
		reversed_lenghts = list(reversed(sorted_by_length))
		sorted_by_freq = sorted(reversed_lenghts, key=lambda tup: tup[1])
		sorted_by_freq = list(reversed(sorted_by_freq))

		if(args.print_words and args.sort):
		 	printWords(sorted_by_freq, words_once)

		elif(args.sort):
			printFrequencies(sorted_by_freq)

		elif(args.print_words):
			printWords(sorted_by_length, words_once)

		else:
			printFrequencies(sorted_by_length)


if __name__ == '__main__': #calls main
	main()



