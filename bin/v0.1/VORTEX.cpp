#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stddef.h>

typedef struct matrix
{
   int rows;             //number of rows.
   int cols;             //number of columns.
   unsigned short *data;
}*bin_matrix;

typedef struct qc_mdpc
{
	unsigned short* row;
	int n0, p, w, t, n, k, r;
}*mdpc;

typedef struct mceliece
{
   mdpc code;
   bin_matrix public_key;
}*mcc;



void* safe_malloc(size_t n)
{
    void* p = malloc(n);
    if (!p)
    {
        fprintf(stderr, "Out of memory(%lu bytes)\n",(size_t)n);
        exit(EXIT_FAILURE);
    }
    return p;
}

//Reset all positions in the row to 0
void reset_row(unsigned short* row, int min, int max)
{
	int i;
	for(i = min; i < max + 1; i++)
	{
	  row[i] = 0;
	}
}
	
//Returns a random integer in the range [min, max]
int random_val(int min, int max, unsigned seed)
{
	int r;
	const unsigned int range = 1 + max - min;
	const unsigned int buckets = RAND_MAX / range;
	const unsigned int limit = buckets * range;
    
	do
	{
		r = rand();
	} while (r >= limit);

	return min + (r / buckets);
}

//Return the weight of the given row from the indices min to max
int get_row_weight(unsigned short* row, int min, int max)
{
	int weight = 0;
	int i;
	for(i = min; i < max + 1; i++)
	{
  		if(row[i] == 1)
		{
			weight++;
		}
	}
	return weight;
}

//initialize the matrix
bin_matrix mat_init(int rows, int cols)
{
  if(rows <= 0 || cols <= 0)
  {
    return NULL;
  }
  bin_matrix A;
  A = (bin_matrix)safe_malloc(sizeof(struct matrix));
  A->cols = cols;
  A->rows = rows; 
  A->data = (unsigned short *)safe_malloc(rows*cols*sizeof(unsigned short)); 
  return A;
}


#define mat_element(mat, row_idx, col_idx) \
  mat->data[row_idx * (mat->cols) + col_idx]

//Return the matrix element at position given by the indices
unsigned short get_matrix_element(bin_matrix mat, int row_idx, int col_idx)
{
  printf("%d < 0 || %d >= %u || %d < 0 || %d >= %d\n",row_idx, row_idx, mat->rows, col_idx, col_idx, mat->cols);
  if(row_idx < 0 || row_idx >= mat->rows || col_idx < 0 || col_idx >= mat->cols)
  {
    printf("Matrix index out of range\n");
    exit(0);
  }
  return mat->data[row_idx * (mat->cols) + col_idx];
}

//Set the value of matix element at position given by the indices to "val"
void set_matrix_element(bin_matrix A, int row_idx, int col_idx, unsigned short val)
{
  printf("set: %d < 0 || %d >= %u || %d < 0 || %d >= %d\n",row_idx, row_idx, A->rows, col_idx, col_idx, A->cols);
  if(row_idx < 0 || row_idx >= A->rows || col_idx < 0 || col_idx >= A->cols)
  {
    printf("Matrix index out of range\n");
    exit(0);
  }
  mat_element(A, row_idx, col_idx) = val;
}

//Set the indicated row of the matrix A equal to the vector vec
void set_matrix_row(bin_matrix A, int row, unsigned short* vec)
{
  if(row < 0 || row >= A->rows)
  {
    printf("Row index out of range\n");
    exit(0);
  }
  for(int i = 0; i < A->cols; i++)
  {
    set_matrix_element(A, row, i, vec[i]);
  }
}

//Delete the matrix and free the space in memory
void delete_matrix(bin_matrix A)
{
  free(A);
}

//Return the transpose of the matrix A
bin_matrix transpose(bin_matrix A)
{
  bin_matrix B;
  B = mat_init(A->cols, A->rows);
  for(int i = 0; i < A->rows; i++)
  {
    for(int j = 0; j < A->cols; j++)
    {
      set_matrix_element(B, j, i, mat_element(A, i, j));
    }
  }
  return B;
}

//Copy the data of matrix A to matrix B
bin_matrix mat_copy(bin_matrix A)
{
  bin_matrix B;
  int i;
  
  B = mat_init(A->rows, A->cols);                    
  memcpy(B->data, A->data, (A->rows)*(A->cols)*(sizeof(unsigned short)));
  return B;
}

//Add row1 to row2 of matrix A
bin_matrix add_rows(bin_matrix A,int row1, int row2)
{
  if(row1 < 0 || row1 >= A->rows || row2 < 0 || row2 >= A->rows)
  {
    printf("Matrix index out of range\n");
    exit(0);
  }
  for(int i = 0; i < A->cols; i++)
  {
    mat_element(A, row2, i) = (mat_element(A, row1, i) ^ mat_element(A, row2, i));
  }
  return A;
}

//Add two matrices
bin_matrix add_matrix(bin_matrix A, bin_matrix B)
{
  if(A->rows != B->rows || A->cols != B->cols)
  {
    printf("Incompatible dimenions for matrix addition.\n");
    exit(0);
  }
  bin_matrix temp = mat_init(A->rows, A->cols);
  for(int i = 0; i < A->rows; i++)
  {
    for(int j = 0; j < A->cols; j++)
    {
      set_matrix_element(temp, i, j, (mat_element(A, i, j) ^ mat_element(B, i, j)));
    }
  }
  return temp;
}

//Function to swap two rows of matrix A
void swap(bin_matrix A, int row1, int row2)
{
  if(row1 < 0 || row1 >= A->rows || row2 < 0 || row2 >= A->rows)
  {
    printf("Matrix index out of range\n");
    exit(0);
  }
  int temp;
  for(int i = 0; i < A->cols; i++)
  {
    temp = mat_element(A, row1, i);
    mat_element(A, row1, i) = mat_element(A, row2, i);
    mat_element(A, row2, i) = temp;
  }
}

//Function to obtain the row reduced echlon form of a matrix A
bin_matrix matrix_rref(bin_matrix A)
{
  int lead = 0;
  int row_count = A->rows;
  int col_count = A->cols;
  bin_matrix temp = mat_init(row_count, col_count);
  temp = mat_copy(A);

  int r = 0;
  while(r < row_count)
  {
    if(mat_element(temp, r, r) == 0)
    {
      int i;
      for(i = r + 1; i < temp->rows; i++)
      {
        if(mat_element(temp, i, r) == 1)
        {
          swap(temp, r, i);
          break;
        }
      }
      if(i == row_count)
      {
      	printf("Matix cannot be transformed into row echlon form...");
        exit(1);
      }
    }
    else
    {
      for(int i = 0; i < row_count; i++)
      {
        if(mat_element(temp, i, r) == 1 && i != r)
        {
          add_rows(temp, r, i);
        }
      }
      r++;
    }
  }
  return temp;
}


//Multiplication of two matrices A and B stored in C
bin_matrix matrix_mult(bin_matrix A, bin_matrix B)
{
  if (A->cols != B->rows)
  {
    printf("Matrices are incompatible, check dimensions...\n");
    exit(0);
  }
  
  bin_matrix C;
  C = mat_init(A->rows, B->cols);
  bin_matrix B_temp = transpose(B);

  for(int i = 0; i < A->rows; i++)
  {
    for(int j = 0  ; j < B->cols; j++)
    {
      unsigned short val = 0;
      for(int k = 0; k < B->rows; k++)
      {
        val = (val ^ (mat_element(A, i, k) & mat_element(B_temp, j, k)));
      }
      mat_element(C, i, j) = val;
    }
  }
    
  return C;
}

//Set matrix as identity matrix
void make_indentity(bin_matrix A)
{
  for(int i = 0; i < A->rows; i++)
  {
    for(int j = 0; j < A->cols; j++)
    {
      if(i == j)
      {
        mat_element(A, i, j) = 1;
      }
      else
      {
        mat_element(A, i, j) = 0;
      }
    }
  }
}

bool is_identity(bin_matrix A)
{
  bool flag = true;
  for(int i = 0; i < A->rows; i++)
  {
    for(int j = 0; j < A->cols; j++)
    {
      if(i == j)
      {
        if(mat_element(A, i, j) == 0)
        {
          flag = false;
          return flag;
        }
      }
      else
      {
        if(mat_element(A, i, j) == 1)
        {
          flag = false;
          return flag;
        }
      }
    }
  }
  return flag;
}

//Checks if the matrix is a zero matrix
int is_zero_matrix(bin_matrix A)
{
  int flag = 1;
  for(int i = 0; i < A->rows; i++)
  {
    for(int j = 0; j < A->cols; j++)
    {
      if(mat_element(A, i, j) != 0)
      {
        flag = 0;
        return flag;
      }
    }
  }
  return flag;
}

//Checks if two matrices are equal
int mat_is_equal(bin_matrix A, bin_matrix B)
{
  int flag = 1;
  if(A->rows != B->rows || A->cols != B->cols)
  {
    flag = 0;
    return flag;
  }
  for(int i = 0; i < A->rows; i++)
  {
    for(int j = 0; j < A->cols; j++)
    {
      if(mat_element(A, i, j) != mat_element(B, i, j))
      {
        flag = 0;
        return flag;
      }
    }
  }
  return flag;
}

//Add the elements of row1 to row2 in the column index range [a,b]  
bin_matrix add_rows_new(bin_matrix A,int row1, int row2, int a, int b)
{
  if(row1 < 0 || row1 >= A->rows || row2 < 0 || row2 >= A->cols)
  {
    printf("Matrix index out of range\n");
    exit(0);
  }
  for(int i = a; i < b; i++)
  {
    mat_element(A, row2, i) = (mat_element(A, row1, i) ^ mat_element(A, row2, i));
  }
  return A;
}

//Add col1 and col2 from in the row index range [a,b]
bin_matrix add_cols(bin_matrix A,int col1, int col2, int a, int b)
{
  if(col1 < 0 || col1 >= A->cols || col2 < 0 || col2 >= A->cols)
  {
    printf("Matrix index out of range\n");
    exit(0);
  }
  for(int i = a; i < b; i++)
  {
    mat_element(A, i, col2) = (mat_element(A, i, col1) ^ mat_element(A, i, col2));
  }
  return A;
}

//Inverse of matrix
bin_matrix circ_matrix_inverse(bin_matrix A)
{
  if(A->rows != A->cols)
  {
    printf("Inverse not possible...\n");
    exit(0);
  }

  if(is_identity(A))
  {
    return A;
  }

  bin_matrix B;
  B = mat_init(A->rows, A->cols);
  make_indentity(B);


  int i;
  int flag, prev_flag = 0;

  for(i = 0; i < A->cols; i++)
  {
    if(mat_element(A, i, i) == 1)
    {      
      for(int j = 0; j <  A->rows; j++)
      {
        if(i != j && mat_element(A, j, i) == 1)
        {
          add_rows_new(B, i, j, 0, A->cols);
          add_rows_new(A, i, j, i, A->cols);
        }
      }
    }
    else
    {
      int k;
      for(k = i + 1; k < A->rows; k++)
      {
        if(mat_element(A, k, i) == 1)
        {
          add_rows(B, k, i);
          add_rows(A, k, i);
          i = i - 1;
          break;
        } 
      }
    }
  }
  //printf("Out of for loop...\n");
  if(!is_identity(A))
  {
    printf("Could not find inverse, exiting...\n");  
    exit(-1);
  }

  
  return B;
}

//Obtain the specified number of rows and columns
bin_matrix mat_splice(bin_matrix A, int row1, int row2, int col1, int col2)
{
  int row_count = row2 - row1 + 1;
  int col_count = col2 - col1 + 1;
  int idx1, idx2;
  
  bin_matrix t = mat_init(row_count, col_count);
  for(int i = 0; i < row_count; i++)
  {
    idx1 = row1 + i;
    for(int j = 0; j < col_count; j++)
    {
      idx2 = col1 + j;
      set_matrix_element(t, i, j, mat_element(A, idx1, idx2));
    }
  }
  return t;
}

//Finding the basis of the kernel space of a matrix A
bin_matrix mat_kernel(bin_matrix A)
{
  int row_count = A->rows;
  int col_count = A->cols;

  bin_matrix temp = mat_init(col_count, row_count + col_count);

  bin_matrix ans = mat_init(col_count, col_count - row_count);
  for(int i = 0; i < temp->rows; i++)
  {
    for(int j = 0; j < row_count; j++)
    {
      set_matrix_element(temp, i, j, mat_element(A, j, i));
    }
  }

  for(int i = 0; i < col_count; i++)
  {
    set_matrix_element(temp, i, i + row_count, 1);
  }

  int r = 0;
  while(r < row_count)
  {
    if(mat_element(temp, r, r) == 0)
    {
      int i;
      for(i = r + 1; i < temp->rows; i++)
      {
        if(mat_element(temp, i, r))
        {
          swap(temp, r, i);
          break;
        }
      }
      if(i == temp->rows)
      {
        ans = mat_splice(temp, row_count, col_count - 1, row_count, row_count + col_count - 1);
        return (matrix_rref(ans));
      }
    }
    else
    {
      for(int i = 0; i < temp->rows; i++)
      {
        if(mat_element(temp, i, r) && i != r)
        {
          add_rows(temp, r, i);
        }
      }
      r++;
    }
  }
  ans = mat_splice(temp, row_count, col_count - 1, row_count, row_count + col_count - 1);
  return (matrix_rref(ans));
}

//Concatenate the matrices A and B as [A|B]
bin_matrix concat_horizontal(bin_matrix A, bin_matrix B)
{
  if(A->rows != B->rows)
  {
    printf("Incompatible dimensions of the two matrices. Number of rows should be same.\n");
    exit(0);
  }
  bin_matrix temp = mat_init(A->rows, A->cols + B->cols);
  for(int i = 0; i < temp->rows; i++)
  {
    for(int j = 0; j < temp->cols; j++)
    {
      if(j < A->cols)
      {
        set_matrix_element(temp, i, j, mat_element(A, i, j));
      }
      else
      {
        set_matrix_element(temp, i, j, mat_element(B, i, j - A->cols));
      }
    }
  }
  return temp;
}

//Concatenate the matrices A and B vertically
bin_matrix concat_vertical(bin_matrix A, bin_matrix B)
{
  if(A->cols != B->cols)
  {
    printf("Incompatible dimensions of the two matrices. Number of rows should be same.\n");
    exit(0);
  }
  bin_matrix temp = mat_init(A->rows + B->rows, A->cols);
  for(int i = 0; i < temp->rows; i++)
  {
    for(int j = 0; j < temp->cols; j++)
    {
      if(i < A->rows)
      {
        set_matrix_element(temp, i, j, mat_element(A, i, j));
      }
      else
      {
        set_matrix_element(temp, i, j, mat_element(B, i - A->rows, j));
      }
    }
  }
  return temp;
}

//Printing the matrix
void print_matrix(bin_matrix A)
{
  for(int i = 0; i < A->rows; i++)
  {
    for (int j = 0; j < A->cols; j++)
    {
      printf("%hu ", mat_element(A, i, j));
    }
    printf("\n");
  }
}



mdpc qc_mdpc_init(int n0, int p, int w, int t)
{
	mdpc code;
	code = (mdpc)safe_malloc(sizeof(struct qc_mdpc));
	code->n0 = n0;
	code->p = p;
	code->w = w;
	code->t = t;
	code->n = n0 * p;
	code->r = p;
	code->k = (n0 - 1) * p;
	unsigned seed;
	code->row = (unsigned short*)calloc(n0 * p, sizeof(unsigned short));
	printf("Input seed or -1 to use default seed: ");
	scanf("%u", &seed);
	time_t tx;
	if(seed == -1)
	{
	  srand((unsigned) time(&tx));
	}
 	else
  	{
    	srand(seed);
  	}

	while(1)
    {
    	int flag = 0;
    	int idx;
    	while(flag < w)
		{
			idx = random_val(0, (n0 * p) - 1, seed);
			if(!code->row[idx])
		    {
		      code->row[idx] = 1;
		      flag = flag + 1;
		    }
		}
    	if((get_row_weight(code->row, (n0 - 1) * p, (n0 * p)-1)) % 2 == 1)
		{
			break;
		}
    	reset_row(code->row, 0, n0 * p);
    }
	printf("MDPC code generated....\n");
	return code;
}

//Delete the qc-mdpc code
void delete_qc_mdpc(mdpc A)
{
  free(A);
}




//Rotate the row x positions to the right
unsigned short* shift(unsigned short* row, int x, int len)
{
	unsigned short* temp = (unsigned short*)calloc(len, sizeof(unsigned short));
	int i;
	for(i = 0; i < len; i++)
	{
	  temp[(i + x) % len] = row[i];
	}
	return temp;
}

//Create a binary circular matrix
bin_matrix make_matrix(int rows, int cols, unsigned short* vec, int x)
{
	bin_matrix mat = mat_init(rows, cols);
	set_matrix_row(mat, 0, vec);
	int i;
	for(i = 1; i < rows; i++)
	{
	  vec = shift(vec, x, cols);
	  set_matrix_row(mat, i, vec);
	}
	return mat;
}

//Splice the row for the given range (does not include max)
unsigned short* splice(unsigned short* row, int min, int max)
{
	unsigned short* temp = (unsigned short*)calloc(max - min, sizeof(unsigned short));
	int i;
	for(i = min; i < max; i++)
	{
	  temp[i - min] = row[i];
	}
	return temp;
}

//Constructing the pariy check matrix
bin_matrix parity_check_matrix(mdpc code)
{
	clock_t start, end;
	double cpu_time_used;
	start = clock();
	bin_matrix H = make_matrix(code->p, code->p, splice(code->row, 0, code->p), 1);
	int i;
	for(i = 1; i < code->n0; i++)
	{
	  bin_matrix M = make_matrix(code->p, code->p, splice(code->row, i * code->p, (i + 1) * code->p), 1);
	  H = concat_horizontal(H, M);
	}
	end = clock();
	cpu_time_used = ((double) (end - start))/ CLOCKS_PER_SEC;
	printf("Time for H: %f\n", cpu_time_used);
	// printf("H: \n");
	// print_matrix(H);
	//printf("Parity matrix generated...\n");
	return H;
}

//Constructing the generator matrix
bin_matrix generator_matrix(mdpc code)
{
	clock_t start, end;
	double cpu_time_used;
	start = clock();
	bin_matrix H = parity_check_matrix(code);


	//End of modified code
	printf("Construction of G started...\n");
	bin_matrix H_inv = circ_matrix_inverse(make_matrix(code->p, code->p, splice(code->row, (code->n0 - 1) * code->p, code->n), 1));
	//printf("H_inv generated...\n");
	//printf("stop\n");
	bin_matrix H_0 = make_matrix(code->p, code->p, splice(code->row, 0, code->p), 1);
	bin_matrix Q = transpose(matrix_mult(H_inv,  H_0));
	//printf("Transpose obtained...\n");
	bin_matrix M;
	int i;
	for(i = 1; i < code->n0 - 1; i++)
	{
	  M = make_matrix(code->p, code->p, splice(code->row, i * code->p, (i + 1) * code->p), 1);
	  M = transpose(matrix_mult(H_inv, M));
	  Q = concat_vertical(Q, M);
	}
	bin_matrix I = mat_init(code->k, code->k);
	make_indentity(I);
	bin_matrix G = concat_horizontal(I, Q);

	//bin_matrix G = mat_kernel(H);
	//G = matrix_rref(G);
	end = clock();
	cpu_time_used = ((double) (end - start))/ CLOCKS_PER_SEC;
	printf("Time for G: %f\n", cpu_time_used);
	printf("Generator matrix generated....\n");
	return G;
}

//Returns the maximum element of the array
int get_max(int* vec, int len)
{
	int max = vec[0];
	int i;
	for(i = 1; i < len; i++)
	{
		if(vec[i] > max)
		{
			max = vec[i];
		}
	}
	return max;
}

//Encoding the vector vec as a MDPC codeword
bin_matrix encode(bin_matrix vec, mdpc code)
{
  bin_matrix G = generator_matrix(code);
  bin_matrix msg = matrix_mult(vec, G);
  return msg;
}

//Decoding the codeword
bin_matrix decode(bin_matrix word, mdpc code)
{
  bin_matrix H = parity_check_matrix(code);
  bin_matrix syn  = matrix_mult(H, transpose(word));
  int limit = 10;
  int delta = 5;
  int i,j,k,x;

	for(i = 0; i < limit; i++)
	{
		//printf("Iteration: %d\n", i);
		int unsatisfied[word->cols];
		for(x = 0; x < word->cols; x++)
		{
			unsatisfied[x] = 0;
		}
		for(j = 0; j < word->cols; j++)
		{
			for(k = 0; k < H->rows; k++)
			{
				if(get_matrix_element(H, k, j) == 1)
				{
					if(get_matrix_element(syn, k, 0) == 1)
					{
						unsatisfied[j] = unsatisfied[j] + 1;
					}
				}
			}
		}
		// printf("No. of unsatisfied equations for each bit: \n");
		// for(int idx = 0; idx < word->cols; idx++)
		// {
		// 	printf("b%d: %d \n", idx, unsatisfied[idx]);
		// }
		int b = get_max(unsatisfied, word->cols) - delta;
		for(j = 0; j < word->cols; j++)
		{
			if(unsatisfied[j] >= b)
			{
				set_matrix_element(word, 0, j, (get_matrix_element(word, 0, j) ^ 1));
				syn = add_matrix(syn, mat_splice(H, 0, H->rows - 1, j, j));
			}
		}
		// printf("Syndrome: ");
		// print_matrix(syn);
		// printf("\n");
		//printf("Iteration: %d\n", i);
		if(is_zero_matrix(syn))
		{
			return word;
		}
	}
	printf("Decoding failure...\n");
	exit(0);
}


//Initialize the mceliece cryptosystem
mcc mceliece_init(int n0, int p, int w, int t)
{
	mcc crypt;
	crypt = (mcc)safe_malloc(sizeof(struct mceliece));
	crypt->code = qc_mdpc_init(n0, p, w, t);
	crypt->public_key = generator_matrix(crypt->code);
	//printf("mceliece generated...\n");
	return crypt;
}

//Delete the cryptosystem
void delete_mceliece(mcc A)
{
	delete_qc_mdpc(A->code);
	delete_matrix(A->public_key);
	free(A);
}
//Generate a random error vector of length len of weight t
bin_matrix get_error_vector(int len, int t)
{
	 bin_matrix error = mat_init(1, len);
	 int weight = 0;
	 int idx;
	 while(weight < t)
	 {
	 	idx = random_val(1, len - 1, -1);
	 	if(!get_matrix_element(error, 0, idx))
	 	{
	 		set_matrix_element(error, 0, idx, 1);
	 		weight++;
	 	}
	 }
	 return error;
}

//Encrypting the message to be sent
bin_matrix encrypt(bin_matrix msg, mcc crypt)
{
	if(msg->cols != crypt->public_key->rows)
	{
		printf("Length of message is incorrect.\n");
		exit(0);
	}
	bin_matrix error = get_error_vector(crypt->code->n, crypt->code->t);
	//printf("error generated...\n");
	bin_matrix word = add_matrix(matrix_mult(msg, crypt->public_key), error);
	//printf("Messsage encrypted....\n");
	return word;
}

//Decrypting the recieved message
bin_matrix decrypt(bin_matrix word, mcc crypt)
{
	if(word->cols != crypt->code->n)
	{
		printf("Length of message is incorrect.\n");
		exit(0);
	}
	//printf("Decryption started...\n");
	bin_matrix msg = decode(word, crypt->code);
	msg = mat_splice(msg, 0, msg->rows - 1, 0, crypt->code->k - 1);
	return msg;
}

int generate()
{

  int n0=4;
  int p = 6;
  int w =9;
  int t =12;
  
  /*	printf("Enter n0: ");
	scanf("%d", &n0);
	printf("Enter p: ");
	scanf("%d", &p);
	printf("Enter w: ");
	scanf("%d", &w);
	printf("Enter t: ");
	scanf("%d", &t);*/
	mdpc code = qc_mdpc_init(n0, p, w, t);
	bin_matrix H = parity_check_matrix(code);
	//printf("H Generated...\n");
	bin_matrix G = generator_matrix(code);
	//printf("G Generated...\n");
	FILE *fp1, *fp2;
	fp1 = fopen("Private_Key.txt", "a");
	fprintf(fp1, "Private Key: Parity Check Matrix: \n");
	for(int i = 0; i < H->rows; i++)
	{
		for(int j = 0; j < H->cols; j++)
		{
			fprintf(fp1, "%hu ", get_matrix_element(H, i, j));
		}
		fprintf(fp1, "\n \n");
	}
	fclose(fp1);

	fp2 = fopen("Public_Key.txt", "a");
	fprintf(fp2, "Public Key: Generator Matrix: \n");
	for(int i = 0; i < G->rows; i++)
	{
		for(int j = 0; j < G->cols; j++)
		{
			fprintf(fp2, "%hu ", get_matrix_element(G, i, j));
		}
		fprintf(fp2, "\n \n");
	}
	fclose(fp2);

	return 0;
}

int encrypt()
{
 int n0=4;
  int p = 6;
  int w =9;
  int t =12;
  /*	printf("Enter n0: ");
	scanf("%d", &n0);
	printf("Enter p: ");
	scanf("%d", &p);
	printf("Enter w: ");
	scanf("%d", &w);
	printf("Enter t: ");
	scanf("%d", &t);*/
	int k = (n0 - 1) * p;
	printf("Enter Message of length %d: \n", k);
	unsigned short inp;

	bin_matrix msg = mat_init(1, k);
	for(int i = 0; i < k; i++)
	{
	  inp=i;
	  set_matrix_element(msg, 0, i, inp);
	}

	mcc crypt = mceliece_init(n0, p, w, t);
	bin_matrix m = encrypt(msg, crypt);
	
	FILE *fp1;
	fp1 = fopen("Encryption.txt", "a");
	for(int i = 0; i < m->cols; i++)
	{
		fprintf(fp1, "%hu ", get_matrix_element(m, 0, i));
	}
	fclose(fp1);

	return 1;
}

int decrypt()
{
 int n0=4;
  int p = 6;
  int w =9;
  int t =12;
	/**printf("Enter n0: ");
	scanf("%d", &n0);
	printf("Enter p: ");
	scanf("%d", &p);
	printf("Enter w: ");
	scanf("%d", &w);
	printf("Enter t: ");
	scanf("%d", &t);**/
	int k = (n0 - 1) * p;
	printf("Enter code of length %d: ", k);
	unsigned short inp;
	bin_matrix msg = mat_init(1, k);
	FILE * f = fopen ("Encryption.txt", "rb");
	char * buffer;
	if (f)
	  {
	    fseek (f, 0, SEEK_END);
	    int length = ftell (f);
	    fseek (f, 0, SEEK_SET);
	    buffer = (char*)malloc (length);
	    if (buffer)
	      {
		fread (buffer, 1, length, f);
	      }
	    fclose (f);
	  }


   
    char **HEAP;
  char *start, *end;
  unsigned count = 0;

  // the cast to (char*) is because i'm going to change the pointer, not because i'm going to change the value.
  start = end = (char*)buffer; 

  while( (end = strchr(start, ' ')) ){
      printf("%d ", count++);
      set_matrix_element(msg, 0, count, (unsigned short)start);

      start = end + 1;

  }
  
  

      
        
	  
	 
	mcc crypt = mceliece_init(n0, p, w, t);
	bin_matrix m = decrypt(msg, crypt);
	
	FILE *fp1;
	fp1 = fopen("Decryption.txt", "a");
	fprintf(fp1, "Decrypted message: \n");
	for(int i = 0; i < m->cols; i++)
	{
		fprintf(fp1, "%hu ", get_matrix_element(m, 0, i));
	}
	fclose(fp1);

	return 1;
}

int main()
{
  encrypt();
  decrypt();
  return 1;
}

