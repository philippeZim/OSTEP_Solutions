
typedef struct {
    int *arr;
    int last;
    int size;
} vector;

vector *init_vector();

void append(vector *v, int x);


int get(vector *v, int index);

void free_vec(vector *v);