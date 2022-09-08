#include <string.h>

#define MAX_LENGTH (64)

enum Node {
	Off
	, On
};

typedef struct _Cell {
	struct _Cell *next;
	struct _Cell *sibling;
	enum Node data;
} Cell;

static Cell Nodes[MAX_LENGTH];

void init(Cell **p_seq, Cell **p_rem, int n_beat, int len)
{
	*p_seq = NULL;
	*p_rem = NULL;
	for (int i = 0; i < len; ++i) {
		memset(&Nodes[i], 0, sizeof(Cell));
		if (n_beat > 0) {
			Nodes[i].data = On;
			--n_beat;
		} else {
			Nodes[i].data = Off;
		}
	}

	
	for (int i = 0; i < len; ++i) {
		if (Nodes[i].data == On) {
			Nodes[i].sibling = *p_seq;
			*p_seq = &Nodes[i];
		} else {
			Nodes[i].sibling = *p_rem;
			*p_rem = &Nodes[i];
		}
	}
}


static void append(Cell *list, Cell *cell)
{
	for (; list; list = list->next) {
		if (!list->next) break;
	}
	list->next = cell;
}

void distribute(Cell *seq, Cell **p_rem)
{
	Cell *remainders = *p_rem;
	for (; seq; seq = seq->sibling) {

		append(seq, remainders);
		remainders = remainders->sibling;

		if (!remainders) {
			if (seq->sibling) {
				remainders = seq->sibling;
				seq->sibling = NULL;
			}
			break;
		}
	}

	*p_rem = remainders;
}

int length(Cell *list)
{
	int cnt = 0;
	for (; list; list = list->sibling) ++cnt;
	return cnt;
}

void concatenate(Cell **p_list, Cell *other)
{
	Cell *list = *p_list;
	if (!list) {
		list = other;
		*p_list = list;
	} else {
		for (; list; list = list->sibling) {
			if (!list->sibling) {
				list->sibling = other;
				break;
			}
		}
	}
}

void flat(Cell *p_list, int *rhythm)
{
	int cnt = 0;
	while (1) {
		Cell *current = p_list;
		for (; p_list; p_list = p_list->next) {
			rhythm[cnt++] = p_list->data == On ? 1 : 0;
		}
		if (!current->sibling) break;
		p_list = current->sibling;
	}
}

void show_rhythm(int *rhythm);

void shift(int *array, int len, int n_shift)
{
	int buf[MAX_LENGTH];
	int cnt = 0;
/*
	for (int i = n_shift; i < len; ++i) {
		buf[cnt++] = array[i];
	}
	for (int i = 0; i < n_shift; ++i) {
		if (cnt >= len) break;
		buf[cnt++] = array[i];
	}
*/
	for (int i = len-n_shift; i < len; ++i) {
		buf[cnt++] = array[i];
	}
	for (int i = 0; i < len-n_shift; ++i) {
		buf[cnt++] = array[i];
	}

	memcpy(array, buf, sizeof(int)*len);
}

void euclidean(int n_beat, int n_shift, int *rhythm, int len)
{
	Cell *sequences = NULL;
	Cell *remainders = NULL;

	init(&sequences, &remainders, n_beat, len);

	if (remainders && sequences) {
		while (1) {
/*
			show(sequences);
			show(remainders);
// */
			distribute(sequences, &remainders);
			if (length(remainders) <= 1) break;
		}
	}

/*
	show(sequences);
	show(remainders);
// */

	Cell *result = NULL;
	concatenate(&result, sequences);
	concatenate(&result, remainders);

//	show(result);

	flat(result, rhythm);
//	show_rhythm(rhythm);

	shift(rhythm, len, n_shift);
}

// --------------------------

/*
#include <stdio.h>
#include <stdlib.h>

void print(const Cell *p)
{
	printf(" [");
	for (; p; p = p->next) {
		printf(" %d", p->data);
	}
	printf(" ]");
}

void show(const Cell *p)
{
	int cnt = 0;
	for (; p; p = p->sibling) {
		printf("%d : ", cnt++);
		print(p);
		printf("\n");
	}
	printf("-----------\n");
}

void show_rhythm(int *rhythm)
{
	for (int i = 0; i < N_LENGTH; ++i) printf(" %d",  rhythm[i]);
	printf("\n");
}


int main(int argc, char **argv)
{
	int rhythm[N_LENGTH];
	int n_beat = 0;
	int n_shift = 0;

	if (argc >= 2) {
		n_beat = atoi(argv[1]);
	}
	if (argc >= 3) {
		n_shift = atoi(argv[2]);
	}

	euclidean(n_beat, n_shift, rhythm);
	show_rhythm(rhythm);

	return 0;
}

// */
