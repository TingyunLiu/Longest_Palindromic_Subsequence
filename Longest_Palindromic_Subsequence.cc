#include <iostream>
#include <string>
using namespace std;


static int **lps_table;	// Table to store current LPS values
static string **trace_table;	// Table for traceback
static char* lps; // Longest Palindromic Subsequence

// Find the length of the longest palindromic subsequence
int LPS(string S, int len) {

	// Reverse the string and save to R
	char R[len];
	for (int i = 0; i < len; ++i) {
		 R[i] = S[len-i-1];
	}

	// Base case
	for (int i = 0; i < len+1; ++i) {
		lps_table[i][0] = 0;
		trace_table[i][0] = "INVALID" ;
	}
	for (int j = 0; j < len+1; ++j) {
		lps_table[0][j] = 0;
		trace_table[0][j] = "INVALID";
	}

	// Recursive Relation
	for (int i = 1; i < len+1; ++i) {
		for (int j = 1; j < len+1; ++j) {
			if (S[i-1] == R[j-1]) {
				lps_table[i][j] = lps_table[i-1][j-1] + 1;
				trace_table[i][j] = "UL";
			} else if (lps_table[i][j-1] > lps_table[i-1][j]) {
				lps_table[i][j] = lps_table[i][j-1];
				trace_table[i][j] = "L";
			} else {
				lps_table[i][j] = lps_table[i-1][j];
				trace_table[i][j] = "U";
			}
		}
	}

	return lps_table[len][len];
}


// For traceback the sequence
void FindLPS(string seq, int len_seq, int len_lps) {

	int i = len_seq;
	int j = len_seq;
	int k = len_lps-1;

	while (i > 0 && j > 0) {
		if (trace_table[i][j] == "UL") {
			lps[k] = seq[i-1];
			--i;
			--j;
			--k;
		} else if (trace_table[i][j] == "L") {
			--j;
		} else {
			--i;
		}
	}
}


int main() {
	string seq; // store the sequence from stdin
	int len_seq, len_lps; // the length of the sequence and the length of the LPS
	
	cin >> seq;
	len_seq = seq.length();

	// initialize lps table and traceback table
	lps_table = new int*[len_seq+1];
	trace_table = new string*[len_seq+1];
	for (int i = 0; i < len_seq+1; ++i) {
		lps_table[i] = new int[len_seq+1];
		trace_table[i] = new string[len_seq+1];
	}

	len_lps = LPS(seq,len_seq);
	lps = new char[len_lps];
	FindLPS(seq,len_seq,len_lps);

	cout << len_lps << endl;
	for (int i = 0; i < len_lps; ++i) {
		cout << lps[i];
	}
	cout << endl;

	// Free two tables
	for (int i = 0; i < len_seq+1; ++i) {
		delete [] lps_table[i];
		delete [] trace_table[i];
	}
	delete [] lps_table;
	delete [] trace_table;
	delete [] lps;
}


