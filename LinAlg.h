// ALGLIB++
// Based on ALGLIB: Copyright (c) Sergey Bochkanov (ALGLIB project).
// Revisions Copyright (c) Lydia Marie Williamson, Mark Hopkins Consulting
// Source License:
//	This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License
//	as published by the Free Software Foundation (www.fsf.org);
//	either version 2 of the License, or (at your option) any later version.
//
//	This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
//	without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
//	See the GNU General Public License for more details.
//
//	A copy of the GNU General Public License is available at http://www.fsf.org/licensing/licenses
#ifndef OnceOnlyLinAlg_h
#define OnceOnlyLinAlg_h

#include "AlgLibMisc.h"

// === SPARSE Package ===
// Depends on: (AlgLibInternal) ABLASMKL, TSORT
// Depends on: (AlgLibMisc) HQRND
namespace alglib_impl {
struct sparsematrix {
   ae_vector vals;
   ae_vector idx;
   ae_vector ridx;
   ae_vector didx;
   ae_vector uidx;
   ae_int_t matrixtype;
   ae_int_t m;
   ae_int_t n;
   ae_int_t nfree;
   ae_int_t ninitialized;
   ae_int_t tablesize;
};
void sparsematrix_init(void *_p, bool make_automatic);
void sparsematrix_copy(void *_dst, void *_src, bool make_automatic);
void sparsematrix_free(void *_p, bool make_automatic);

struct sparsebuffers {
   ae_vector d;
   ae_vector u;
   sparsematrix s;
};
void sparsebuffers_init(void *_p, bool make_automatic);
void sparsebuffers_copy(void *_dst, void *_src, bool make_automatic);
void sparsebuffers_free(void *_p, bool make_automatic);

void sparsecreate(ae_int_t m, ae_int_t n, ae_int_t k, sparsematrix *s);
void sparsecreatebuf(ae_int_t m, ae_int_t n, ae_int_t k, sparsematrix *s);
void sparsecreatecrs(ae_int_t m, ae_int_t n, ZVector *ner, sparsematrix *s);
void sparsecreatecrsbuf(ae_int_t m, ae_int_t n, ZVector *ner, sparsematrix *s);
void sparsecreatesks(ae_int_t m, ae_int_t n, ZVector *d, ZVector *u, sparsematrix *s);
void sparsecreatesksbuf(ae_int_t m, ae_int_t n, ZVector *d, ZVector *u, sparsematrix *s);
void sparsecreatesksband(ae_int_t m, ae_int_t n, ae_int_t bw, sparsematrix *s);
void sparsecreatesksbandbuf(ae_int_t m, ae_int_t n, ae_int_t bw, sparsematrix *s);
void sparsecopy(sparsematrix *s0, sparsematrix *s1);
void sparsecopybuf(sparsematrix *s0, sparsematrix *s1);
void sparseswap(sparsematrix *s0, sparsematrix *s1);
void sparseadd(sparsematrix *s, ae_int_t i, ae_int_t j, double v);
void sparseset(sparsematrix *s, ae_int_t i, ae_int_t j, double v);
double sparseget(sparsematrix *s, ae_int_t i, ae_int_t j);
double sparsegetdiagonal(sparsematrix *s, ae_int_t i);
void sparsemv(sparsematrix *s, RVector *x, RVector *y);
void sparsemtv(sparsematrix *s, RVector *x, RVector *y);
void sparsegemv(sparsematrix *s, double alpha, ae_int_t ops, RVector *x, ae_int_t ix, double beta, RVector *y, ae_int_t iy);
void sparsemv2(sparsematrix *s, RVector *x, RVector *y0, RVector *y1);
void sparsesmv(sparsematrix *s, bool isupper, RVector *x, RVector *y);
double sparsevsmv(sparsematrix *s, bool isupper, RVector *x);
void sparsemm(sparsematrix *s, RMatrix *a, ae_int_t k, RMatrix *b);
void sparsemtm(sparsematrix *s, RMatrix *a, ae_int_t k, RMatrix *b);
void sparsemm2(sparsematrix *s, RMatrix *a, ae_int_t k, RMatrix *b0, RMatrix *b1);
void sparsesmm(sparsematrix *s, bool isupper, RMatrix *a, ae_int_t k, RMatrix *b);
void sparsetrmv(sparsematrix *s, bool isupper, bool isunit, ae_int_t optype, RVector *x, RVector *y);
void sparsetrsv(sparsematrix *s, bool isupper, bool isunit, ae_int_t optype, RVector *x);
void sparseresizematrix(sparsematrix *s);
void sparseinitduidx(sparsematrix *s);
double sparsegetaveragelengthofchain(sparsematrix *s);
bool sparseenumerate(sparsematrix *s, ae_int_t *t0, ae_int_t *t1, ae_int_t *i, ae_int_t *j, double *v);
bool sparserewriteexisting(sparsematrix *s, ae_int_t i, ae_int_t j, double v);
void sparsegetrow(sparsematrix *s, ae_int_t i, RVector *irow);
void sparsegetcompressedrow(sparsematrix *s, ae_int_t i, ZVector *colidx, RVector *vals, ae_int_t *nzcnt);
void sparsetransposesks(sparsematrix *s);
void sparsetransposecrs(sparsematrix *s);
void sparsecopytransposecrs(sparsematrix *s0, sparsematrix *s1);
void sparsecopytransposecrsbuf(sparsematrix *s0, sparsematrix *s1);
void sparseconvertto(sparsematrix *s0, ae_int_t fmt);
void sparsecopytobuf(sparsematrix *s0, ae_int_t fmt, sparsematrix *s1);
void sparseconverttohash(sparsematrix *s);
void sparsecopytohash(sparsematrix *s0, sparsematrix *s1);
void sparsecopytohashbuf(sparsematrix *s0, sparsematrix *s1);
void sparseconverttocrs(sparsematrix *s);
void sparsecopytocrs(sparsematrix *s0, sparsematrix *s1);
void sparsecopytocrsbuf(sparsematrix *s0, sparsematrix *s1);
void sparseconverttosks(sparsematrix *s);
void sparsecopytosks(sparsematrix *s0, sparsematrix *s1);
void sparsecopytosksbuf(sparsematrix *s0, sparsematrix *s1);
void sparsecreatecrsinplace(sparsematrix *s);
ae_int_t sparsegetmatrixtype(sparsematrix *s);
bool sparseishash(sparsematrix *s);
bool sparseiscrs(sparsematrix *s);
bool sparseissks(sparsematrix *s);
void sparsefree(sparsematrix *s);
ae_int_t sparsegetnrows(sparsematrix *s);
ae_int_t sparsegetncols(sparsematrix *s);
ae_int_t sparsegetuppercount(sparsematrix *s);
ae_int_t sparsegetlowercount(sparsematrix *s);
} // end of namespace alglib_impl

namespace alglib {
// Sparse matrix structure.
//
// You should use ALGLIB functions to work with sparse matrix. Never  try  to
// access its fields directly!
//
// NOTES ON THE SPARSE STORAGE FORMATS
//
// Sparse matrices can be stored using several formats:
// * Hash-Table representation
// * Compressed Row Storage (CRS)
// * Skyline matrix storage (SKS)
//
// Each of the formats has benefits and drawbacks:
// * Hash-table is good for dynamic operations (insertion of new elements),
//   but does not support linear algebra operations
// * CRS is good for operations like matrix-vector or matrix-matrix products,
//   but its initialization is less convenient - you have to tell row   sizes
//   at the initialization, and you have to fill  matrix  only  row  by  row,
//   from left to right.
// * SKS is a special format which is used to store triangular  factors  from
//   Cholesky factorization. It does not support  dynamic  modification,  and
//   support for linear algebra operations is very limited.
//
// Tables below outline information about these two formats:
//
//     OPERATIONS WITH MATRIX      HASH        CRS         SKS
//     creation                    +           +           +
//     SparseGet                   +           +           +
//     SparseRewriteExisting       +           +           +
//     SparseSet                   +           +           +
//     SparseAdd                   +
//     SparseGetRow                            +           +
//     SparseGetCompressedRow                  +           +
//     sparse-dense linear algebra             +           +
DecClass(sparsematrix, EndD);

// Temporary buffers for sparse matrix operations.
//
// You should pass an instance of this structure to factorization  functions.
// It allows to reuse memory during repeated sparse  factorizations.  You  do
// not have to call some initialization function - simply passing an instance
// to factorization function is enough.
DecClass(sparsebuffers, EndD);

// This function creates sparse matrix in a Hash-Table format.
//
// This function creates Hast-Table matrix, which can be  converted  to  CRS
// format after its initialization is over. Typical  usage  scenario  for  a
// sparse matrix is:
// 1. creation in a Hash-Table format
// 2. insertion of the matrix elements
// 3. conversion to the CRS representation
// 4. matrix is passed to some linear algebra algorithm
//
// Some  information  about  different matrix formats can be found below, in
// the "NOTES" section.
//
// Inputs:
//     M           -   number of rows in a matrix, M >= 1
//     N           -   number of columns in a matrix, N >= 1
//     K           -   K >= 0, expected number of non-zero elements in a matrix.
//                     K can be inexact approximation, can be less than actual
//                     number  of  elements  (table will grow when needed) or
//                     even zero).
//                     It is important to understand that although hash-table
//                     may grow automatically, it is better to  provide  good
//                     estimate of data size.
//
// Outputs:
//     S           -   sparse M*N matrix in Hash-Table representation.
//                     All elements of the matrix are zero.
//
// NOTE 1
//
// Hash-tables use memory inefficiently, and they have to keep  some  amount
// of the "spare memory" in order to have good performance. Hash  table  for
// matrix with K non-zero elements will  need  C*K*(8+2*sizeof(int))  bytes,
// where C is a small constant, about 1.5-2 in magnitude.
//
// CRS storage, from the other side, is  more  memory-efficient,  and  needs
// just K*(8+sizeof(int))+M*sizeof(int) bytes, where M is a number  of  rows
// in a matrix.
//
// When you convert from the Hash-Table to CRS  representation, all unneeded
// memory will be freed.
//
// NOTE 2
//
// Comments of SparseMatrix structure outline  information  about  different
// sparse storage formats. We recommend you to read them before starting  to
// use ALGLIB sparse matrices.
//
// NOTE 3
//
// This function completely  overwrites S with new sparse matrix. Previously
// allocated storage is NOT reused. If you  want  to reuse already allocated
// memory, call SparseCreateBuf function.
//
// ALGLIB Project: Copyright 14.10.2011 by Sergey Bochkanov
void sparsecreate(const ae_int_t m, const ae_int_t n, const ae_int_t k, sparsematrix &s);
void sparsecreate(const ae_int_t m, const ae_int_t n, sparsematrix &s);

// This version of SparseCreate function creates sparse matrix in Hash-Table
// format, reusing previously allocated storage as much  as  possible.  Read
// comments for SparseCreate() for more information.
//
// Inputs:
//     M           -   number of rows in a matrix, M >= 1
//     N           -   number of columns in a matrix, N >= 1
//     K           -   K >= 0, expected number of non-zero elements in a matrix.
//                     K can be inexact approximation, can be less than actual
//                     number  of  elements  (table will grow when needed) or
//                     even zero).
//                     It is important to understand that although hash-table
//                     may grow automatically, it is better to  provide  good
//                     estimate of data size.
//     S           -   SparseMatrix structure which MAY contain some  already
//                     allocated storage.
//
// Outputs:
//     S           -   sparse M*N matrix in Hash-Table representation.
//                     All elements of the matrix are zero.
//                     Previously allocated storage is reused, if  its  size
//                     is compatible with expected number of non-zeros K.
//
// ALGLIB Project: Copyright 14.01.2014 by Sergey Bochkanov
void sparsecreatebuf(const ae_int_t m, const ae_int_t n, const ae_int_t k, const sparsematrix &s);
void sparsecreatebuf(const ae_int_t m, const ae_int_t n, const sparsematrix &s);

// This function creates sparse matrix in a CRS format (expert function for
// situations when you are running out of memory).
//
// This function creates CRS matrix. Typical usage scenario for a CRS matrix
// is:
// 1. creation (you have to tell number of non-zero elements at each row  at
//    this moment)
// 2. insertion of the matrix elements (row by row, from left to right)
// 3. matrix is passed to some linear algebra algorithm
//
// This function is a memory-efficient alternative to SparseCreate(), but it
// is more complex because it requires you to know in advance how large your
// matrix is. Some  information about  different matrix formats can be found
// in comments on SparseMatrix structure.  We recommend  you  to  read  them
// before starting to use ALGLIB sparse matrices..
//
// Inputs:
//     M           -   number of rows in a matrix, M >= 1
//     N           -   number of columns in a matrix, N >= 1
//     NER         -   number of elements at each row, array[M], NER[I] >= 0
//
// Outputs:
//     S           -   sparse M*N matrix in CRS representation.
//                     You have to fill ALL non-zero elements by calling
//                     SparseSet() BEFORE you try to use this matrix.
//
// NOTE: this function completely  overwrites  S  with  new  sparse  matrix.
//       Previously allocated storage is NOT reused. If you  want  to  reuse
//       already allocated memory, call SparseCreateCRSBuf function.
//
// ALGLIB Project: Copyright 14.10.2011 by Sergey Bochkanov
void sparsecreatecrs(const ae_int_t m, const ae_int_t n, const integer_1d_array &ner, sparsematrix &s);

// This function creates sparse matrix in a CRS format (expert function  for
// situations when you are running out  of  memory).  This  version  of  CRS
// matrix creation function may reuse memory already allocated in S.
//
// This function creates CRS matrix. Typical usage scenario for a CRS matrix
// is:
// 1. creation (you have to tell number of non-zero elements at each row  at
//    this moment)
// 2. insertion of the matrix elements (row by row, from left to right)
// 3. matrix is passed to some linear algebra algorithm
//
// This function is a memory-efficient alternative to SparseCreate(), but it
// is more complex because it requires you to know in advance how large your
// matrix is. Some  information about  different matrix formats can be found
// in comments on SparseMatrix structure.  We recommend  you  to  read  them
// before starting to use ALGLIB sparse matrices..
//
// Inputs:
//     M           -   number of rows in a matrix, M >= 1
//     N           -   number of columns in a matrix, N >= 1
//     NER         -   number of elements at each row, array[M], NER[I] >= 0
//     S           -   sparse matrix structure with possibly preallocated
//                     memory.
//
// Outputs:
//     S           -   sparse M*N matrix in CRS representation.
//                     You have to fill ALL non-zero elements by calling
//                     SparseSet() BEFORE you try to use this matrix.
//
// ALGLIB Project: Copyright 14.10.2011 by Sergey Bochkanov
void sparsecreatecrsbuf(const ae_int_t m, const ae_int_t n, const integer_1d_array &ner, const sparsematrix &s);

// This function creates sparse matrix in  a  SKS  format  (skyline  storage
// format). In most cases you do not need this function - CRS format  better
// suits most use cases.
//
// Inputs:
//     M, N        -   number of rows(M) and columns (N) in a matrix:
//                     * M=N (as for now, ALGLIB supports only square SKS)
//                     * N >= 1
//                     * M >= 1
//     D           -   "bottom" bandwidths, array[M], D[I] >= 0.
//                     I-th element stores number of non-zeros at I-th  row,
//                     below the diagonal (diagonal itself is not  included)
//     U           -   "top" bandwidths, array[N], U[I] >= 0.
//                     I-th element stores number of non-zeros  at I-th row,
//                     above the diagonal (diagonal itself  is not included)
//
// Outputs:
//     S           -   sparse M*N matrix in SKS representation.
//                     All elements are filled by zeros.
//                     You may use sparseset() to change their values.
//
// NOTE: this function completely  overwrites  S  with  new  sparse  matrix.
//       Previously allocated storage is NOT reused. If you  want  to  reuse
//       already allocated memory, call SparseCreateSKSBuf function.
//
// ALGLIB Project: Copyright 13.01.2014 by Sergey Bochkanov
void sparsecreatesks(const ae_int_t m, const ae_int_t n, const integer_1d_array &d, const integer_1d_array &u, sparsematrix &s);

// This is "buffered"  version  of  SparseCreateSKS()  which  reuses  memory
// previously allocated in S (of course, memory is reallocated if needed).
//
// This function creates sparse matrix in  a  SKS  format  (skyline  storage
// format). In most cases you do not need this function - CRS format  better
// suits most use cases.
//
// Inputs:
//     M, N        -   number of rows(M) and columns (N) in a matrix:
//                     * M=N (as for now, ALGLIB supports only square SKS)
//                     * N >= 1
//                     * M >= 1
//     D           -   "bottom" bandwidths, array[M], 0 <= D[I] <= I.
//                     I-th element stores number of non-zeros at I-th row,
//                     below the diagonal (diagonal itself is not included)
//     U           -   "top" bandwidths, array[N], 0 <= U[I] <= I.
//                     I-th element stores number of non-zeros at I-th row,
//                     above the diagonal (diagonal itself is not included)
//
// Outputs:
//     S           -   sparse M*N matrix in SKS representation.
//                     All elements are filled by zeros.
//                     You may use sparseset() to change their values.
//
// ALGLIB Project: Copyright 13.01.2014 by Sergey Bochkanov
void sparsecreatesksbuf(const ae_int_t m, const ae_int_t n, const integer_1d_array &d, const integer_1d_array &u, const sparsematrix &s);

// This function creates sparse matrix in  a  SKS  format  (skyline  storage
// format). Unlike more general  sparsecreatesks(),  this  function  creates
// sparse matrix with constant bandwidth.
//
// You may want to use this function instead of sparsecreatesks() when  your
// matrix has  constant  or  nearly-constant  bandwidth,  and  you  want  to
// simplify source code.
//
// Inputs:
//     M, N        -   number of rows(M) and columns (N) in a matrix:
//                     * M=N (as for now, ALGLIB supports only square SKS)
//                     * N >= 1
//                     * M >= 1
//     BW          -   matrix bandwidth, BW >= 0
//
// Outputs:
//     S           -   sparse M*N matrix in SKS representation.
//                     All elements are filled by zeros.
//                     You may use sparseset() to  change  their values.
//
// NOTE: this function completely  overwrites  S  with  new  sparse  matrix.
//       Previously allocated storage is NOT reused. If you  want  to  reuse
//       already allocated memory, call sparsecreatesksbandbuf function.
//
// ALGLIB Project: Copyright 25.12.2017 by Sergey Bochkanov
void sparsecreatesksband(const ae_int_t m, const ae_int_t n, const ae_int_t bw, sparsematrix &s);

// This is "buffered" version  of  sparsecreatesksband() which reuses memory
// previously allocated in S (of course, memory is reallocated if needed).
//
// You may want to use this function instead  of  sparsecreatesksbuf()  when
// your matrix has  constant or nearly-constant  bandwidth,  and you want to
// simplify source code.
//
// Inputs:
//     M, N        -   number of rows(M) and columns (N) in a matrix:
//                     * M=N (as for now, ALGLIB supports only square SKS)
//                     * N >= 1
//                     * M >= 1
//     BW          -   bandwidth, BW >= 0
//
// Outputs:
//     S           -   sparse M*N matrix in SKS representation.
//                     All elements are filled by zeros.
//                     You may use sparseset() to change their values.
//
// ALGLIB Project: Copyright 13.01.2014 by Sergey Bochkanov
void sparsecreatesksbandbuf(const ae_int_t m, const ae_int_t n, const ae_int_t bw, const sparsematrix &s);

// This function copies S0 to S1.
// This function completely deallocates memory owned by S1 before creating a
// copy of S0. If you want to reuse memory, use SparseCopyBuf.
//
// NOTE:  this  function  does  not verify its arguments, it just copies all
// fields of the structure.
//
// ALGLIB Project: Copyright 14.10.2011 by Sergey Bochkanov
void sparsecopy(const sparsematrix &s0, sparsematrix &s1);

// This function copies S0 to S1.
// Memory already allocated in S1 is reused as much as possible.
//
// NOTE:  this  function  does  not verify its arguments, it just copies all
// fields of the structure.
//
// ALGLIB Project: Copyright 14.10.2011 by Sergey Bochkanov
void sparsecopybuf(const sparsematrix &s0, const sparsematrix &s1);

// This function efficiently swaps contents of S0 and S1.
//
// ALGLIB Project: Copyright 16.01.2014 by Sergey Bochkanov
void sparseswap(const sparsematrix &s0, const sparsematrix &s1);

// This function adds value to S[i,j] - element of the sparse matrix. Matrix
// must be in a Hash-Table mode.
//
// In case S[i,j] already exists in the table, V i added to  its  value.  In
// case  S[i,j]  is  non-existent,  it  is  inserted  in  the  table.  Table
// automatically grows when necessary.
//
// Inputs:
//     S           -   sparse M*N matrix in Hash-Table representation.
//                     Exception will be thrown for CRS matrix.
//     I           -   row index of the element to modify, 0 <= I < M
//     J           -   column index of the element to modify, 0 <= J < N
//     V           -   value to add, must be finite number
//
// Outputs:
//     S           -   modified matrix
//
// NOTE 1:  when  S[i,j]  is exactly zero after modification, it is  deleted
// from the table.
//
// ALGLIB Project: Copyright 14.10.2011 by Sergey Bochkanov
void sparseadd(const sparsematrix &s, const ae_int_t i, const ae_int_t j, const double v);

// This function modifies S[i,j] - element of the sparse matrix.
//
// For Hash-based storage format:
// * this function can be called at any moment - during matrix initialization
//   or later
// * new value can be zero or non-zero.  In case new value of S[i,j] is zero,
//   this element is deleted from the table.
// * this  function  has  no  effect when called with zero V for non-existent
//   element.
//
// For CRS-bases storage format:
// * this function can be called ONLY DURING MATRIX INITIALIZATION
// * zero values are stored in the matrix similarly to non-zero ones
// * elements must be initialized in correct order -  from top row to bottom,
//   within row - from left to right.
//
// For SKS storage:
// * this function can be called at any moment - during matrix initialization
//   or later
// * zero values are stored in the matrix similarly to non-zero ones
// * this function CAN NOT be called for non-existent (outside  of  the  band
//   specified during SKS matrix creation) elements. Say, if you created  SKS
//   matrix  with  bandwidth=2  and  tried to call sparseset(s,0,10,VAL),  an
//   exception will be generated.
//
// Inputs:
//     S           -   sparse M*N matrix in Hash-Table, SKS or CRS format.
//     I           -   row index of the element to modify, 0 <= I < M
//     J           -   column index of the element to modify, 0 <= J < N
//     V           -   value to set, must be finite number, can be zero
//
// Outputs:
//     S           -   modified matrix
//
// ALGLIB Project: Copyright 14.10.2011 by Sergey Bochkanov
void sparseset(const sparsematrix &s, const ae_int_t i, const ae_int_t j, const double v);

// This function returns S[i,j] - element of the sparse matrix.  Matrix  can
// be in any mode (Hash-Table, CRS, SKS), but this function is less efficient
// for CRS matrices. Hash-Table and SKS matrices can find  element  in  O(1)
// time, while  CRS  matrices need O(log(RS)) time, where RS is an number of
// non-zero elements in a row.
//
// Inputs:
//     S           -   sparse M*N matrix in Hash-Table representation.
//                     Exception will be thrown for CRS matrix.
//     I           -   row index of the element to modify, 0 <= I < M
//     J           -   column index of the element to modify, 0 <= J < N
//
// Result:
//     value of S[I,J] or zero (in case no element with such index is found)
//
// ALGLIB Project: Copyright 14.10.2011 by Sergey Bochkanov
double sparseget(const sparsematrix &s, const ae_int_t i, const ae_int_t j);

// This function returns I-th diagonal element of the sparse matrix.
//
// Matrix can be in any mode (Hash-Table or CRS storage), but this  function
// is most efficient for CRS matrices - it requires less than 50 CPU  cycles
// to extract diagonal element. For Hash-Table matrices we still  have  O(1)
// query time, but function is many times slower.
//
// Inputs:
//     S           -   sparse M*N matrix in Hash-Table representation.
//                     Exception will be thrown for CRS matrix.
//     I           -   index of the element to modify, 0 <= I < min(M,N)
//
// Result:
//     value of S[I,I] or zero (in case no element with such index is found)
//
// ALGLIB Project: Copyright 14.10.2011 by Sergey Bochkanov
double sparsegetdiagonal(const sparsematrix &s, const ae_int_t i);

// This function calculates matrix-vector product  S*x.  Matrix  S  must  be
// stored in CRS or SKS format (exception will be thrown otherwise).
//
// Inputs:
//     S           -   sparse M*N matrix in CRS or SKS format.
//     X           -   array[N], input vector. For  performance  reasons  we
//                     make only quick checks - we check that array size  is
//                     at least N, but we do not check for NAN's or INF's.
//     Y           -   output buffer, possibly preallocated. In case  buffer
//                     size is too small to store  result,  this  buffer  is
//                     automatically resized.
//
// Outputs:
//     Y           -   array[M], S*x
//
// NOTE: this function throws exception when called for non-CRS/SKS  matrix.
// You must convert your matrix with SparseConvertToCRS/SKS()  before  using
// this function.
//
// ALGLIB Project: Copyright 14.10.2011 by Sergey Bochkanov
void sparsemv(const sparsematrix &s, const real_1d_array &x, real_1d_array &y);

// This function calculates matrix-vector product  S^T*x. Matrix S  must  be
// stored in CRS or SKS format (exception will be thrown otherwise).
//
// Inputs:
//     S           -   sparse M*N matrix in CRS or SKS format.
//     X           -   array[M], input vector. For  performance  reasons  we
//                     make only quick checks - we check that array size  is
//                     at least M, but we do not check for NAN's or INF's.
//     Y           -   output buffer, possibly preallocated. In case  buffer
//                     size is too small to store  result,  this  buffer  is
//                     automatically resized.
//
// Outputs:
//     Y           -   array[N], S^T*x
//
// NOTE: this function throws exception when called for non-CRS/SKS  matrix.
// You must convert your matrix with SparseConvertToCRS/SKS()  before  using
// this function.
//
// ALGLIB Project: Copyright 14.10.2011 by Sergey Bochkanov
void sparsemtv(const sparsematrix &s, const real_1d_array &x, real_1d_array &y);

// This function calculates generalized sparse matrix-vector product
//
//     y := alpha*op(S)*x + beta*y
//
// Matrix S must be stored in CRS or SKS format (exception  will  be  thrown
// otherwise). op(S) can be either S or S^T.
//
// NOTE: this  function  expects  Y  to  be  large enough to store result. No
//       automatic preallocation happens for smaller arrays.
//
// Inputs:
//     S           -   sparse matrix in CRS or SKS format.
//     Alpha       -   source coefficient
//     OpS         -   operation type:
//                     * OpS=0     =>  op(S) = S
//                     * OpS=1     =>  op(S) = S^T
//     X           -   input vector, must have at least Cols(op(S))+IX elements
//     IX          -   subvector offset
//     Beta        -   destination coefficient
//     Y           -   preallocated output array, must have at least Rows(op(S))+IY elements
//     IY          -   subvector offset
//
// Outputs:
//     Y           -   elements [IY...IY+Rows(op(S))-1] are replaced by result,
//                     other elements are not modified
//
// HANDLING OF SPECIAL CASES:
// * below M=Rows(op(S)) and N=Cols(op(S)). Although current  ALGLIB  version
//   does not allow you to  create  zero-sized  sparse  matrices,  internally
//   ALGLIB  can  deal  with  such matrices. So, comments for M or N equal to
//   zero are for internal use only.
// * if M=0, then subroutine does nothing. It does not even touch arrays.
// * if N=0 or Alpha=0.0, then:
//   * if Beta=0, then Y is filled by zeros. S and X are  not  referenced  at
//     all. Initial values of Y are ignored (we do not  multiply  Y by  zero,
//     we just rewrite it by zeros)
//   * if Beta != 0, then Y is replaced by Beta*Y
// * if M > 0, N > 0, Alpha != 0, but  Beta=0, then  Y is replaced by alpha*op(S)*x
//   initial state of Y  is ignored (rewritten without initial multiplication
//   by zeros).
//
// NOTE: this function throws exception when called for non-CRS/SKS  matrix.
// You must convert your matrix with SparseConvertToCRS/SKS()  before  using
// this function.
//
// ALGLIB Project: Copyright 10.12.2019 by Sergey Bochkanov
void sparsegemv(const sparsematrix &s, const double alpha, const ae_int_t ops, const real_1d_array &x, const ae_int_t ix, const double beta, const real_1d_array &y, const ae_int_t iy);

// This function simultaneously calculates two matrix-vector products:
//     S*x and S^T*x.
// S must be square (non-rectangular) matrix stored in  CRS  or  SKS  format
// (exception will be thrown otherwise).
//
// Inputs:
//     S           -   sparse N*N matrix in CRS or SKS format.
//     X           -   array[N], input vector. For  performance  reasons  we
//                     make only quick checks - we check that array size  is
//                     at least N, but we do not check for NAN's or INF's.
//     Y0          -   output buffer, possibly preallocated. In case  buffer
//                     size is too small to store  result,  this  buffer  is
//                     automatically resized.
//     Y1          -   output buffer, possibly preallocated. In case  buffer
//                     size is too small to store  result,  this  buffer  is
//                     automatically resized.
//
// Outputs:
//     Y0          -   array[N], S*x
//     Y1          -   array[N], S^T*x
//
// NOTE: this function throws exception when called for non-CRS/SKS  matrix.
// You must convert your matrix with SparseConvertToCRS/SKS()  before  using
// this function.
//
// ALGLIB Project: Copyright 14.10.2011 by Sergey Bochkanov
void sparsemv2(const sparsematrix &s, const real_1d_array &x, real_1d_array &y0, real_1d_array &y1);

// This function calculates matrix-vector product  S*x, when S is  symmetric
// matrix. Matrix S  must be stored in CRS or SKS format  (exception will be
// thrown otherwise).
//
// Inputs:
//     S           -   sparse M*M matrix in CRS or SKS format.
//     IsUpper     -   whether upper or lower triangle of S is given:
//                     * if upper triangle is given,  only   S[i,j] for j >= i
//                       are used, and lower triangle is ignored (it can  be
//                       empty - these elements are not referenced at all).
//                     * if lower triangle is given,  only   S[i,j] for j <= i
//                       are used, and upper triangle is ignored.
//     X           -   array[N], input vector. For  performance  reasons  we
//                     make only quick checks - we check that array size  is
//                     at least N, but we do not check for NAN's or INF's.
//     Y           -   output buffer, possibly preallocated. In case  buffer
//                     size is too small to store  result,  this  buffer  is
//                     automatically resized.
//
// Outputs:
//     Y           -   array[M], S*x
//
// NOTE: this function throws exception when called for non-CRS/SKS  matrix.
// You must convert your matrix with SparseConvertToCRS/SKS()  before  using
// this function.
//
// ALGLIB Project: Copyright 14.10.2011 by Sergey Bochkanov
void sparsesmv(const sparsematrix &s, const bool isupper, const real_1d_array &x, real_1d_array &y);

// This function calculates vector-matrix-vector product x'*S*x, where  S is
// symmetric matrix. Matrix S must be stored in CRS or SKS format (exception
// will be thrown otherwise).
//
// Inputs:
//     S           -   sparse M*M matrix in CRS or SKS format.
//     IsUpper     -   whether upper or lower triangle of S is given:
//                     * if upper triangle is given,  only   S[i,j] for j >= i
//                       are used, and lower triangle is ignored (it can  be
//                       empty - these elements are not referenced at all).
//                     * if lower triangle is given,  only   S[i,j] for j <= i
//                       are used, and upper triangle is ignored.
//     X           -   array[N], input vector. For  performance  reasons  we
//                     make only quick checks - we check that array size  is
//                     at least N, but we do not check for NAN's or INF's.
//
// Result:
//     x'*S*x
//
// NOTE: this function throws exception when called for non-CRS/SKS  matrix.
// You must convert your matrix with SparseConvertToCRS/SKS()  before  using
// this function.
//
// ALGLIB Project: Copyright 27.01.2014 by Sergey Bochkanov
double sparsevsmv(const sparsematrix &s, const bool isupper, const real_1d_array &x);

// This function calculates matrix-matrix product  S*A.  Matrix  S  must  be
// stored in CRS or SKS format (exception will be thrown otherwise).
//
// Inputs:
//     S           -   sparse M*N matrix in CRS or SKS format.
//     A           -   array[N][K], input dense matrix. For  performance reasons
//                     we make only quick checks - we check that array size
//                     is at least N, but we do not check for NAN's or INF's.
//     K           -   number of columns of matrix (A).
//     B           -   output buffer, possibly preallocated. In case  buffer
//                     size is too small to store  result,  this  buffer  is
//                     automatically resized.
//
// Outputs:
//     B           -   array[M][K], S*A
//
// NOTE: this function throws exception when called for non-CRS/SKS  matrix.
// You must convert your matrix with SparseConvertToCRS/SKS()  before  using
// this function.
//
// ALGLIB Project: Copyright 14.10.2011 by Sergey Bochkanov
void sparsemm(const sparsematrix &s, const real_2d_array &a, const ae_int_t k, real_2d_array &b);

// This function calculates matrix-matrix product  S^T*A. Matrix S  must  be
// stored in CRS or SKS format (exception will be thrown otherwise).
//
// Inputs:
//     S           -   sparse M*N matrix in CRS or SKS format.
//     A           -   array[M][K], input dense matrix. For performance reasons
//                     we make only quick checks - we check that array size  is
//                     at least M, but we do not check for NAN's or INF's.
//     K           -   number of columns of matrix (A).
//     B           -   output buffer, possibly preallocated. In case  buffer
//                     size is too small to store  result,  this  buffer  is
//                     automatically resized.
//
// Outputs:
//     B           -   array[N][K], S^T*A
//
// NOTE: this function throws exception when called for non-CRS/SKS  matrix.
// You must convert your matrix with SparseConvertToCRS/SKS()  before  using
// this function.
//
// ALGLIB Project: Copyright 14.10.2011 by Sergey Bochkanov
void sparsemtm(const sparsematrix &s, const real_2d_array &a, const ae_int_t k, real_2d_array &b);

// This function simultaneously calculates two matrix-matrix products:
//     S*A and S^T*A.
// S  must  be  square (non-rectangular) matrix stored in CRS or  SKS  format
// (exception will be thrown otherwise).
//
// Inputs:
//     S           -   sparse N*N matrix in CRS or SKS format.
//     A           -   array[N][K], input dense matrix. For performance reasons
//                     we make only quick checks - we check that array size  is
//                     at least N, but we do not check for NAN's or INF's.
//     K           -   number of columns of matrix (A).
//     B0          -   output buffer, possibly preallocated. In case  buffer
//                     size is too small to store  result,  this  buffer  is
//                     automatically resized.
//     B1          -   output buffer, possibly preallocated. In case  buffer
//                     size is too small to store  result,  this  buffer  is
//                     automatically resized.
//
// Outputs:
//     B0          -   array[N][K], S*A
//     B1          -   array[N][K], S^T*A
//
// NOTE: this function throws exception when called for non-CRS/SKS  matrix.
// You must convert your matrix with SparseConvertToCRS/SKS()  before  using
// this function.
//
// ALGLIB Project: Copyright 14.10.2011 by Sergey Bochkanov
void sparsemm2(const sparsematrix &s, const real_2d_array &a, const ae_int_t k, real_2d_array &b0, real_2d_array &b1);

// This function calculates matrix-matrix product  S*A, when S  is  symmetric
// matrix. Matrix S must be stored in CRS or SKS format  (exception  will  be
// thrown otherwise).
//
// Inputs:
//     S           -   sparse M*M matrix in CRS or SKS format.
//     IsUpper     -   whether upper or lower triangle of S is given:
//                     * if upper triangle is given,  only   S[i,j] for j >= i
//                       are used, and lower triangle is ignored (it can  be
//                       empty - these elements are not referenced at all).
//                     * if lower triangle is given,  only   S[i,j] for j <= i
//                       are used, and upper triangle is ignored.
//     A           -   array[N][K], input dense matrix. For performance reasons
//                     we make only quick checks - we check that array size is
//                     at least N, but we do not check for NAN's or INF's.
//     K           -   number of columns of matrix (A).
//     B           -   output buffer, possibly preallocated. In case  buffer
//                     size is too small to store  result,  this  buffer  is
//                     automatically resized.
//
// Outputs:
//     B           -   array[M][K], S*A
//
// NOTE: this function throws exception when called for non-CRS/SKS  matrix.
// You must convert your matrix with SparseConvertToCRS/SKS()  before  using
// this function.
//
// ALGLIB Project: Copyright 14.10.2011 by Sergey Bochkanov
void sparsesmm(const sparsematrix &s, const bool isupper, const real_2d_array &a, const ae_int_t k, real_2d_array &b);

// This function calculates matrix-vector product op(S)*x, when x is  vector,
// S is symmetric triangular matrix, op(S) is transposition or no  operation.
// Matrix S must be stored in CRS or SKS format  (exception  will  be  thrown
// otherwise).
//
// Inputs:
//     S           -   sparse square matrix in CRS or SKS format.
//     IsUpper     -   whether upper or lower triangle of S is used:
//                     * if upper triangle is given,  only   S[i,j] for  j >= i
//                       are used, and lower triangle is  ignored (it can  be
//                       empty - these elements are not referenced at all).
//                     * if lower triangle is given,  only   S[i,j] for  j <= i
//                       are used, and upper triangle is ignored.
//     IsUnit      -   unit or non-unit diagonal:
//                     * if True, diagonal elements of triangular matrix  are
//                       considered equal to 1.0. Actual elements  stored  in
//                       S are not referenced at all.
//                     * if False, diagonal stored in S is used
//     OpType      -   operation type:
//                     * if 0, S*x is calculated
//                     * if 1, (S^T)*x is calculated (transposition)
//     X           -   array[N] which stores input  vector.  For  performance
//                     reasons we make only quick  checks  -  we  check  that
//                     array  size  is  at  least  N, but we do not check for
//                     NAN's or INF's.
//     Y           -   possibly  preallocated  input   buffer.  Automatically
//                     resized if its size is too small.
//
// Outputs:
//     Y           -   array[N], op(S)*x
//
// NOTE: this function throws exception when called for non-CRS/SKS  matrix.
// You must convert your matrix with SparseConvertToCRS/SKS()  before  using
// this function.
//
// ALGLIB Project: Copyright 20.01.2014 by Sergey Bochkanov
void sparsetrmv(const sparsematrix &s, const bool isupper, const bool isunit, const ae_int_t optype, const real_1d_array &x, real_1d_array &y);

// This function solves linear system op(S)*y=x  where  x  is  vector,  S  is
// symmetric  triangular  matrix,  op(S)  is  transposition  or no operation.
// Matrix S must be stored in CRS or SKS format  (exception  will  be  thrown
// otherwise).
//
// Inputs:
//     S           -   sparse square matrix in CRS or SKS format.
//     IsUpper     -   whether upper or lower triangle of S is used:
//                     * if upper triangle is given,  only   S[i,j] for  j >= i
//                       are used, and lower triangle is  ignored (it can  be
//                       empty - these elements are not referenced at all).
//                     * if lower triangle is given,  only   S[i,j] for  j <= i
//                       are used, and upper triangle is ignored.
//     IsUnit      -   unit or non-unit diagonal:
//                     * if True, diagonal elements of triangular matrix  are
//                       considered equal to 1.0. Actual elements  stored  in
//                       S are not referenced at all.
//                     * if False, diagonal stored in S is used. It  is  your
//                       responsibility  to  make  sure  that   diagonal   is
//                       non-zero.
//     OpType      -   operation type:
//                     * if 0, S*x is calculated
//                     * if 1, (S^T)*x is calculated (transposition)
//     X           -   array[N] which stores input  vector.  For  performance
//                     reasons we make only quick  checks  -  we  check  that
//                     array  size  is  at  least  N, but we do not check for
//                     NAN's or INF's.
//
// Outputs:
//     X           -   array[N], inv(op(S))*x
//
// NOTE: this function throws exception when called for  non-CRS/SKS  matrix.
//       You must convert your matrix  with  SparseConvertToCRS/SKS()  before
//       using this function.
//
// NOTE: no assertion or tests are done during algorithm  operation.   It  is
//       your responsibility to provide invertible matrix to algorithm.
//
// ALGLIB Project: Copyright 20.01.2014 by Sergey Bochkanov
void sparsetrsv(const sparsematrix &s, const bool isupper, const bool isunit, const ae_int_t optype, const real_1d_array &x);

// This procedure resizes Hash-Table matrix. It can be called when you  have
// deleted too many elements from the matrix, and you want to  free unneeded
// memory.
//
// ALGLIB Project: Copyright 14.10.2011 by Sergey Bochkanov
void sparseresizematrix(const sparsematrix &s);

// This  function  is  used  to enumerate all elements of the sparse matrix.
// Before  first  call  user  initializes  T0 and T1 counters by zero. These
// counters are used to remember current position in a  matrix;  after  each
// call they are updated by the function.
//
// Subsequent calls to this function return non-zero elements of the  sparse
// matrix, one by one. If you enumerate CRS matrix, matrix is traversed from
// left to right, from top to bottom. In case you enumerate matrix stored as
// Hash table, elements are returned in random order.
//
// EXAMPLE
//     > T0=0
//     > T1=0
//     > while SparseEnumerate(S,T0,T1,I,J,V) do
//     >     ....do something with I,J,V
//
// Inputs:
//     S           -   sparse M*N matrix in Hash-Table or CRS representation.
//     T0          -   internal counter
//     T1          -   internal counter
//
// Outputs:
//     T0          -   new value of the internal counter
//     T1          -   new value of the internal counter
//     I           -   row index of non-zero element, 0 <= I < M.
//     J           -   column index of non-zero element, 0 <= J < N
//     V           -   value of the T-th element
//
// Result:
//     True in case of success (next non-zero element was retrieved)
//     False in case all non-zero elements were enumerated
//
// NOTE: you may call SparseRewriteExisting() during enumeration, but it  is
//       THE  ONLY  matrix  modification  function  you  can  call!!!  Other
//       matrix modification functions should not be called during enumeration!
//
// ALGLIB Project: Copyright 14.03.2012 by Sergey Bochkanov
bool sparseenumerate(const sparsematrix &s, ae_int_t &t0, ae_int_t &t1, ae_int_t &i, ae_int_t &j, double &v);

// This function rewrites existing (non-zero) element. It  returns  True   if
// element  exists  or  False,  when  it  is  called for non-existing  (zero)
// element.
//
// This function works with any kind of the matrix.
//
// The purpose of this function is to provide convenient thread-safe  way  to
// modify  sparse  matrix.  Such  modification  (already  existing element is
// rewritten) is guaranteed to be thread-safe without any synchronization, as
// long as different threads modify different elements.
//
// Inputs:
//     S           -   sparse M*N matrix in any kind of representation
//                     (Hash, SKS, CRS).
//     I           -   row index of non-zero element to modify, 0 <= I < M
//     J           -   column index of non-zero element to modify, 0 <= J < N
//     V           -   value to rewrite, must be finite number
//
// Outputs:
//     S           -   modified matrix
// Result:
//     True in case when element exists
//     False in case when element doesn't exist or it is zero
//
// ALGLIB Project: Copyright 14.03.2012 by Sergey Bochkanov
bool sparserewriteexisting(const sparsematrix &s, const ae_int_t i, const ae_int_t j, const double v);

// This function returns I-th row of the sparse matrix. Matrix must be stored
// in CRS or SKS format.
//
// Inputs:
//     S           -   sparse M*N matrix in CRS format
//     I           -   row index, 0 <= I < M
//     IRow        -   output buffer, can be  preallocated.  In  case  buffer
//                     size  is  too  small  to  store  I-th   row,   it   is
//                     automatically reallocated.
//
// Outputs:
//     IRow        -   array[M], I-th row.
//
// NOTE: this function has O(N) running time, where N is a  column  count. It
//       allocates and fills N-element  array,  even  although  most  of  its
//       elemets are zero.
//
// NOTE: If you have O(non-zeros-per-row) time and memory  requirements,  use
//       SparseGetCompressedRow() function. It  returns  data  in  compressed
//       format.
//
// NOTE: when  incorrect  I  (outside  of  [0,M-1]) or  matrix (non  CRS/SKS)
//       is passed, this function throws exception.
//
// ALGLIB Project: Copyright 10.12.2014 by Sergey Bochkanov
void sparsegetrow(const sparsematrix &s, const ae_int_t i, real_1d_array &irow);

// This function returns I-th row of the sparse matrix IN COMPRESSED FORMAT -
// only non-zero elements are returned (with their indexes). Matrix  must  be
// stored in CRS or SKS format.
//
// Inputs:
//     S           -   sparse M*N matrix in CRS format
//     I           -   row index, 0 <= I < M
//     ColIdx      -   output buffer for column indexes, can be preallocated.
//                     In case buffer size is too small to store I-th row, it
//                     is automatically reallocated.
//     Vals        -   output buffer for values, can be preallocated. In case
//                     buffer size is too small to  store  I-th  row,  it  is
//                     automatically reallocated.
//
// Outputs:
//     ColIdx      -   column   indexes   of  non-zero  elements,  sorted  by
//                     ascending. Symbolically non-zero elements are  counted
//                     (i.e. if you allocated place for element, but  it  has
//                     zero numerical value - it is counted).
//     Vals        -   values. Vals[K] stores value of  matrix  element  with
//                     indexes (I,ColIdx[K]). Symbolically non-zero  elements
//                     are counted (i.e. if you allocated place for  element,
//                     but it has zero numerical value - it is counted).
//     NZCnt       -   number of symbolically non-zero elements per row.
//
// NOTE: when  incorrect  I  (outside  of  [0,M-1]) or  matrix (non  CRS/SKS)
//       is passed, this function throws exception.
//
// NOTE: this function may allocate additional, unnecessary place for  ColIdx
//       and Vals arrays. It is dictated by  performance  reasons  -  on  SKS
//       matrices it is faster  to  allocate  space  at  the  beginning  with
//       some "extra"-space, than performing two passes over matrix  -  first
//       time to calculate exact space required for data, second  time  -  to
//       store data itself.
//
// ALGLIB Project: Copyright 10.12.2014 by Sergey Bochkanov
void sparsegetcompressedrow(const sparsematrix &s, const ae_int_t i, integer_1d_array &colidx, real_1d_array &vals, ae_int_t &nzcnt);

// This function performs efficient in-place  transpose  of  SKS  matrix.  No
// additional memory is allocated during transposition.
//
// This function supports only skyline storage format (SKS).
//
// Inputs:
//     S       -   sparse matrix in SKS format.
//
// Outputs:
//     S           -   sparse matrix, transposed.
//
// ALGLIB Project: Copyright 16.01.2014 by Sergey Bochkanov
void sparsetransposesks(const sparsematrix &s);

// This function performs transpose of CRS matrix.
//
// Inputs:
//     S       -   sparse matrix in CRS format.
//
// Outputs:
//     S           -   sparse matrix, transposed.
//
// NOTE: internal  temporary  copy  is  allocated   for   the   purposes   of
//       transposition. It is deallocated after transposition.
//
// ALGLIB Project: Copyright 30.01.2018 by Sergey Bochkanov
void sparsetransposecrs(const sparsematrix &s);

// This function performs copying with transposition of CRS matrix.
//
// Inputs:
//     S0      -   sparse matrix in CRS format.
//
// Outputs:
//     S1      -   sparse matrix, transposed
//
// ALGLIB Project: Copyright 23.07.2018 by Sergey Bochkanov
void sparsecopytransposecrs(const sparsematrix &s0, sparsematrix &s1);

// This function performs copying with transposition of CRS matrix  (buffered
// version which reuses memory already allocated by  the  target as  much  as
// possible).
//
// Inputs:
//     S0      -   sparse matrix in CRS format.
//
// Outputs:
//     S1      -   sparse matrix, transposed; previously allocated memory  is
//                 reused if possible.
//
// ALGLIB Project: Copyright 23.07.2018 by Sergey Bochkanov
void sparsecopytransposecrsbuf(const sparsematrix &s0, const sparsematrix &s1);

// This  function  performs  in-place  conversion  to  desired sparse storage
// format.
//
// Inputs:
//     S0      -   sparse matrix in any format.
//     Fmt     -   desired storage format  of  the  output,  as  returned  by
//                 SparseGetMatrixType() function:
//                 * 0 for hash-based storage
//                 * 1 for CRS
//                 * 2 for SKS
//
// Outputs:
//     S0          -   sparse matrix in requested format.
//
// NOTE: in-place conversion wastes a lot of memory which is  used  to  store
//       temporaries.  If  you  perform  a  lot  of  repeated conversions, we
//       recommend to use out-of-place buffered  conversion  functions,  like
//       SparseCopyToBuf(), which can reuse already allocated memory.
//
// ALGLIB Project: Copyright 16.01.2014 by Sergey Bochkanov
void sparseconvertto(const sparsematrix &s0, const ae_int_t fmt);

// This  function  performs out-of-place conversion to desired sparse storage
// format. S0 is copied to S1 and converted on-the-fly. Memory  allocated  in
// S1 is reused to maximum extent possible.
//
// Inputs:
//     S0      -   sparse matrix in any format.
//     Fmt     -   desired storage format  of  the  output,  as  returned  by
//                 SparseGetMatrixType() function:
//                 * 0 for hash-based storage
//                 * 1 for CRS
//                 * 2 for SKS
//
// Outputs:
//     S1          -   sparse matrix in requested format.
//
// ALGLIB Project: Copyright 16.01.2014 by Sergey Bochkanov
void sparsecopytobuf(const sparsematrix &s0, const ae_int_t fmt, const sparsematrix &s1);

// This function performs in-place conversion to Hash table storage.
//
// Inputs:
//     S           -   sparse matrix in CRS format.
//
// Outputs:
//     S           -   sparse matrix in Hash table format.
//
// NOTE: this  function  has   no  effect  when  called with matrix which  is
//       already in Hash table mode.
//
// NOTE: in-place conversion involves allocation of temporary arrays. If  you
//       perform a lot of repeated in- place  conversions,  it  may  lead  to
//       memory fragmentation. Consider using out-of-place SparseCopyToHashBuf()
//       function in this case.
//
// ALGLIB Project: Copyright 20.07.2012 by Sergey Bochkanov
void sparseconverttohash(const sparsematrix &s);

// This  function  performs  out-of-place  conversion  to  Hash table storage
// format. S0 is copied to S1 and converted on-the-fly.
//
// Inputs:
//     S0          -   sparse matrix in any format.
//
// Outputs:
//     S1          -   sparse matrix in Hash table format.
//
// NOTE: if S0 is stored as Hash-table, it is just copied without conversion.
//
// NOTE: this function de-allocates memory  occupied  by  S1 before  starting
//       conversion. If you perform a  lot  of  repeated  conversions, it may
//       lead to memory fragmentation. In this case we recommend you  to  use
//       SparseCopyToHashBuf() function which re-uses memory in S1 as much as
//       possible.
//
// ALGLIB Project: Copyright 20.07.2012 by Sergey Bochkanov
void sparsecopytohash(const sparsematrix &s0, sparsematrix &s1);

// This  function  performs  out-of-place  conversion  to  Hash table storage
// format. S0 is copied to S1 and converted on-the-fly. Memory  allocated  in
// S1 is reused to maximum extent possible.
//
// Inputs:
//     S0          -   sparse matrix in any format.
//
// Outputs:
//     S1          -   sparse matrix in Hash table format.
//
// NOTE: if S0 is stored as Hash-table, it is just copied without conversion.
//
// ALGLIB Project: Copyright 20.07.2012 by Sergey Bochkanov
void sparsecopytohashbuf(const sparsematrix &s0, const sparsematrix &s1);

// This function converts matrix to CRS format.
//
// Some  algorithms  (linear  algebra ones, for example) require matrices in
// CRS format. This function allows to perform in-place conversion.
//
// Inputs:
//     S           -   sparse M*N matrix in any format
//
// Outputs:
//     S           -   matrix in CRS format
//
// NOTE: this   function  has  no  effect  when  called with matrix which is
//       already in CRS mode.
//
// NOTE: this function allocates temporary memory to store a   copy  of  the
//       matrix. If you perform a lot of repeated conversions, we  recommend
//       you  to  use  SparseCopyToCRSBuf()  function,   which   can   reuse
//       previously allocated memory.
//
// ALGLIB Project: Copyright 14.10.2011 by Sergey Bochkanov
void sparseconverttocrs(const sparsematrix &s);

// This  function  performs  out-of-place  conversion  to  CRS format.  S0 is
// copied to S1 and converted on-the-fly.
//
// Inputs:
//     S0          -   sparse matrix in any format.
//
// Outputs:
//     S1          -   sparse matrix in CRS format.
//
// NOTE: if S0 is stored as CRS, it is just copied without conversion.
//
// NOTE: this function de-allocates memory occupied by S1 before starting CRS
//       conversion. If you perform a lot of repeated CRS conversions, it may
//       lead to memory fragmentation. In this case we recommend you  to  use
//       SparseCopyToCRSBuf() function which re-uses memory in S1 as much  as
//       possible.
//
// ALGLIB Project: Copyright 20.07.2012 by Sergey Bochkanov
void sparsecopytocrs(const sparsematrix &s0, sparsematrix &s1);

// This  function  performs  out-of-place  conversion  to  CRS format.  S0 is
// copied to S1 and converted on-the-fly. Memory allocated in S1 is reused to
// maximum extent possible.
//
// Inputs:
//     S0          -   sparse matrix in any format.
//     S1          -   matrix which may contain some pre-allocated memory, or
//                     can be just uninitialized structure.
//
// Outputs:
//     S1          -   sparse matrix in CRS format.
//
// NOTE: if S0 is stored as CRS, it is just copied without conversion.
//
// ALGLIB Project: Copyright 20.07.2012 by Sergey Bochkanov
void sparsecopytocrsbuf(const sparsematrix &s0, const sparsematrix &s1);

// This function performs in-place conversion to SKS format.
//
// Inputs:
//     S           -   sparse matrix in any format.
//
// Outputs:
//     S           -   sparse matrix in SKS format.
//
// NOTE: this  function  has   no  effect  when  called with matrix which  is
//       already in SKS mode.
//
// NOTE: in-place conversion involves allocation of temporary arrays. If  you
//       perform a lot of repeated in- place  conversions,  it  may  lead  to
//       memory fragmentation. Consider using out-of-place SparseCopyToSKSBuf()
//       function in this case.
//
// ALGLIB Project: Copyright 15.01.2014 by Sergey Bochkanov
void sparseconverttosks(const sparsematrix &s);

// This  function  performs  out-of-place  conversion  to SKS storage format.
// S0 is copied to S1 and converted on-the-fly.
//
// Inputs:
//     S0          -   sparse matrix in any format.
//
// Outputs:
//     S1          -   sparse matrix in SKS format.
//
// NOTE: if S0 is stored as SKS, it is just copied without conversion.
//
// NOTE: this function de-allocates memory  occupied  by  S1 before  starting
//       conversion. If you perform a  lot  of  repeated  conversions, it may
//       lead to memory fragmentation. In this case we recommend you  to  use
//       SparseCopyToSKSBuf() function which re-uses memory in S1 as much  as
//       possible.
//
// ALGLIB Project: Copyright 20.07.2012 by Sergey Bochkanov
void sparsecopytosks(const sparsematrix &s0, sparsematrix &s1);

// This  function  performs  out-of-place  conversion  to SKS format.  S0  is
// copied to S1 and converted on-the-fly. Memory  allocated  in S1 is  reused
// to maximum extent possible.
//
// Inputs:
//     S0          -   sparse matrix in any format.
//
// Outputs:
//     S1          -   sparse matrix in SKS format.
//
// NOTE: if S0 is stored as SKS, it is just copied without conversion.
//
// ALGLIB Project: Copyright 20.07.2012 by Sergey Bochkanov
void sparsecopytosksbuf(const sparsematrix &s0, const sparsematrix &s1);

// This function returns type of the matrix storage format.
//
// Inputs:
//     S           -   sparse matrix.
//
// Result:
//     sparse storage format used by matrix:
//         0   -   Hash-table
//         1   -   CRS (compressed row storage)
//         2   -   SKS (skyline)
//
// NOTE: future  versions  of  ALGLIB  may  include additional sparse storage
//       formats.
//
//
// ALGLIB Project: Copyright 20.07.2012 by Sergey Bochkanov
ae_int_t sparsegetmatrixtype(const sparsematrix &s);

// This function checks matrix storage format and returns True when matrix is
// stored using Hash table representation.
//
// Inputs:
//     S   -   sparse matrix.
//
// Result:
//     True if matrix type is Hash table
//     False if matrix type is not Hash table
//
// ALGLIB Project: Copyright 20.07.2012 by Sergey Bochkanov
bool sparseishash(const sparsematrix &s);

// This function checks matrix storage format and returns True when matrix is
// stored using CRS representation.
//
// Inputs:
//     S   -   sparse matrix.
//
// Result:
//     True if matrix type is CRS
//     False if matrix type is not CRS
//
// ALGLIB Project: Copyright 20.07.2012 by Sergey Bochkanov
bool sparseiscrs(const sparsematrix &s);

// This function checks matrix storage format and returns True when matrix is
// stored using SKS representation.
//
// Inputs:
//     S   -   sparse matrix.
//
// Result:
//     True if matrix type is SKS
//     False if matrix type is not SKS
//
// ALGLIB Project: Copyright 20.07.2012 by Sergey Bochkanov
bool sparseissks(const sparsematrix &s);

// The function frees all memory occupied by  sparse  matrix.  Sparse  matrix
// structure becomes unusable after this call.
//
// Outputs:
//     S   -   sparse matrix to delete
//
// ALGLIB Project: Copyright 24.07.2012 by Sergey Bochkanov
void sparsefree(sparsematrix &s);

// The function returns number of rows of a sparse matrix.
//
// Result: number of rows of a sparse matrix.
//
// ALGLIB Project: Copyright 23.08.2012 by Sergey Bochkanov
ae_int_t sparsegetnrows(const sparsematrix &s);

// The function returns number of columns of a sparse matrix.
//
// Result: number of columns of a sparse matrix.
//
// ALGLIB Project: Copyright 23.08.2012 by Sergey Bochkanov
ae_int_t sparsegetncols(const sparsematrix &s);

// The function returns number of strictly upper triangular non-zero elements
// in  the  matrix.  It  counts  SYMBOLICALLY non-zero elements, i.e. entries
// in the sparse matrix data structure. If some element  has  zero  numerical
// value, it is still counted.
//
// This function has different cost for different types of matrices:
// * for hash-based matrices it involves complete pass over entire hash-table
//   with O(NNZ) cost, where NNZ is number of non-zero elements
// * for CRS and SKS matrix types cost of counting is O(N) (N - matrix size).
//
// Result: number of non-zero elements strictly above main diagonal
//
// ALGLIB Project: Copyright 12.02.2014 by Sergey Bochkanov
ae_int_t sparsegetuppercount(const sparsematrix &s);

// The function returns number of strictly lower triangular non-zero elements
// in  the  matrix.  It  counts  SYMBOLICALLY non-zero elements, i.e. entries
// in the sparse matrix data structure. If some element  has  zero  numerical
// value, it is still counted.
//
// This function has different cost for different types of matrices:
// * for hash-based matrices it involves complete pass over entire hash-table
//   with O(NNZ) cost, where NNZ is number of non-zero elements
// * for CRS and SKS matrix types cost of counting is O(N) (N - matrix size).
//
// Result: number of non-zero elements strictly below main diagonal
//
// ALGLIB Project: Copyright 12.02.2014 by Sergey Bochkanov
ae_int_t sparsegetlowercount(const sparsematrix &s);
} // end of namespace alglib

// === ABLAS Package ===
// Depends on: (AlgLibInternal) APSERV, ABLASMKL, ABLASF
namespace alglib_impl {
void ablassplitlength(RMatrix *a, ae_int_t n, ae_int_t *n1, ae_int_t *n2);
void ablascomplexsplitlength(CMatrix *a, ae_int_t n, ae_int_t *n1, ae_int_t *n2);
ae_int_t gemmparallelsize();
ae_int_t ablasblocksize(RMatrix *a);
ae_int_t ablascomplexblocksize(CMatrix *a);
ae_int_t ablasmicroblocksize();
void generatereflection(RVector *x, ae_int_t n, double *tau);
void applyreflectionfromtheleft(RMatrix *c, double tau, RVector *v, ae_int_t m1, ae_int_t m2, ae_int_t n1, ae_int_t n2, RVector *work);
void applyreflectionfromtheright(RMatrix *c, double tau, RVector *v, ae_int_t m1, ae_int_t m2, ae_int_t n1, ae_int_t n2, RVector *work);
void cmatrixtranspose(ae_int_t m, ae_int_t n, CMatrix *a, ae_int_t ia, ae_int_t ja, CMatrix *b, ae_int_t ib, ae_int_t jb);
void rmatrixtranspose(ae_int_t m, ae_int_t n, RMatrix *a, ae_int_t ia, ae_int_t ja, RMatrix *b, ae_int_t ib, ae_int_t jb);
void rmatrixenforcesymmetricity(RMatrix *a, ae_int_t n, bool isupper);
void cmatrixcopy(ae_int_t m, ae_int_t n, CMatrix *a, ae_int_t ia, ae_int_t ja, CMatrix *b, ae_int_t ib, ae_int_t jb);
void rvectorcopy(ae_int_t n, RVector *a, ae_int_t ia, RVector *b, ae_int_t ib);
void rmatrixcopy(ae_int_t m, ae_int_t n, RMatrix *a, ae_int_t ia, ae_int_t ja, RMatrix *b, ae_int_t ib, ae_int_t jb);
void rmatrixgencopy(ae_int_t m, ae_int_t n, double alpha, RMatrix *a, ae_int_t ia, ae_int_t ja, double beta, RMatrix *b, ae_int_t ib, ae_int_t jb);
void rmatrixger(ae_int_t m, ae_int_t n, RMatrix *a, ae_int_t ia, ae_int_t ja, double alpha, RVector *u, ae_int_t iu, RVector *v, ae_int_t iv);
void cmatrixrank1(ae_int_t m, ae_int_t n, CMatrix *a, ae_int_t ia, ae_int_t ja, CVector *u, ae_int_t iu, CVector *v, ae_int_t iv);
void rmatrixrank1(ae_int_t m, ae_int_t n, RMatrix *a, ae_int_t ia, ae_int_t ja, RVector *u, ae_int_t iu, RVector *v, ae_int_t iv);
void rmatrixgemv(ae_int_t m, ae_int_t n, double alpha, RMatrix *a, ae_int_t ia, ae_int_t ja, ae_int_t opa, RVector *x, ae_int_t ix, double beta, RVector *y, ae_int_t iy);
void cmatrixmv(ae_int_t m, ae_int_t n, CMatrix *a, ae_int_t ia, ae_int_t ja, ae_int_t opa, CVector *x, ae_int_t ix, CVector *y, ae_int_t iy);
void rmatrixmv(ae_int_t m, ae_int_t n, RMatrix *a, ae_int_t ia, ae_int_t ja, ae_int_t opa, RVector *x, ae_int_t ix, RVector *y, ae_int_t iy);
void rmatrixsymv(ae_int_t n, double alpha, RMatrix *a, ae_int_t ia, ae_int_t ja, bool isupper, RVector *x, ae_int_t ix, double beta, RVector *y, ae_int_t iy);
double rmatrixsyvmv(ae_int_t n, RMatrix *a, ae_int_t ia, ae_int_t ja, bool isupper, RVector *x, ae_int_t ix, RVector *tmp);
void rmatrixtrsv(ae_int_t n, RMatrix *a, ae_int_t ia, ae_int_t ja, bool isupper, bool isunit, ae_int_t optype, RVector *x, ae_int_t ix);
void cmatrixrighttrsm(ae_int_t m, ae_int_t n, CMatrix *a, ae_int_t i1, ae_int_t j1, bool isupper, bool isunit, ae_int_t optype, CMatrix *x, ae_int_t i2, ae_int_t j2);
void cmatrixlefttrsm(ae_int_t m, ae_int_t n, CMatrix *a, ae_int_t i1, ae_int_t j1, bool isupper, bool isunit, ae_int_t optype, CMatrix *x, ae_int_t i2, ae_int_t j2);
void rmatrixrighttrsm(ae_int_t m, ae_int_t n, RMatrix *a, ae_int_t i1, ae_int_t j1, bool isupper, bool isunit, ae_int_t optype, RMatrix *x, ae_int_t i2, ae_int_t j2);
void rmatrixlefttrsm(ae_int_t m, ae_int_t n, RMatrix *a, ae_int_t i1, ae_int_t j1, bool isupper, bool isunit, ae_int_t optype, RMatrix *x, ae_int_t i2, ae_int_t j2);
void cmatrixherk(ae_int_t n, ae_int_t k, double alpha, CMatrix *a, ae_int_t ia, ae_int_t ja, ae_int_t optypea, double beta, CMatrix *c, ae_int_t ic, ae_int_t jc, bool isupper);
void rmatrixsyrk(ae_int_t n, ae_int_t k, double alpha, RMatrix *a, ae_int_t ia, ae_int_t ja, ae_int_t optypea, double beta, RMatrix *c, ae_int_t ic, ae_int_t jc, bool isupper);
void cmatrixgemm(ae_int_t m, ae_int_t n, ae_int_t k, ae_complex alpha, CMatrix *a, ae_int_t ia, ae_int_t ja, ae_int_t optypea, CMatrix *b, ae_int_t ib, ae_int_t jb, ae_int_t optypeb, ae_complex beta, CMatrix *c, ae_int_t ic, ae_int_t jc);
void rmatrixgemm(ae_int_t m, ae_int_t n, ae_int_t k, double alpha, RMatrix *a, ae_int_t ia, ae_int_t ja, ae_int_t optypea, RMatrix *b, ae_int_t ib, ae_int_t jb, ae_int_t optypeb, double beta, RMatrix *c, ae_int_t ic, ae_int_t jc);
void cmatrixsyrk(ae_int_t n, ae_int_t k, double alpha, CMatrix *a, ae_int_t ia, ae_int_t ja, ae_int_t optypea, double beta, CMatrix *c, ae_int_t ic, ae_int_t jc, bool isupper);
} // end of namespace alglib_impl

namespace alglib {
// Cache-oblivous complex "copy-and-transpose"
//
// Inputs:
//     M   -   number of rows
//     N   -   number of columns
//     A   -   source matrix, MxN submatrix is copied and transposed
//     IA  -   submatrix offset (row index)
//     JA  -   submatrix offset (column index)
//     B   -   destination matrix, must be large enough to store result
//     IB  -   submatrix offset (row index)
//     JB  -   submatrix offset (column index)
void cmatrixtranspose(const ae_int_t m, const ae_int_t n, const complex_2d_array &a, const ae_int_t ia, const ae_int_t ja, complex_2d_array &b, const ae_int_t ib, const ae_int_t jb);

// Cache-oblivous real "copy-and-transpose"
//
// Inputs:
//     M   -   number of rows
//     N   -   number of columns
//     A   -   source matrix, MxN submatrix is copied and transposed
//     IA  -   submatrix offset (row index)
//     JA  -   submatrix offset (column index)
//     B   -   destination matrix, must be large enough to store result
//     IB  -   submatrix offset (row index)
//     JB  -   submatrix offset (column index)
void rmatrixtranspose(const ae_int_t m, const ae_int_t n, const real_2d_array &a, const ae_int_t ia, const ae_int_t ja, const real_2d_array &b, const ae_int_t ib, const ae_int_t jb);

// This code enforces symmetricy of the matrix by copying Upper part to lower
// one (or vice versa).
//
// Inputs:
//     A   -   matrix
//     N   -   number of rows/columns
//     IsUpper - whether we want to copy upper triangle to lower one (True)
//             or vice versa (False).
void rmatrixenforcesymmetricity(const real_2d_array &a, const ae_int_t n, const bool isupper);

// Copy
//
// Inputs:
//     M   -   number of rows
//     N   -   number of columns
//     A   -   source matrix, MxN submatrix is copied and transposed
//     IA  -   submatrix offset (row index)
//     JA  -   submatrix offset (column index)
//     B   -   destination matrix, must be large enough to store result
//     IB  -   submatrix offset (row index)
//     JB  -   submatrix offset (column index)
void cmatrixcopy(const ae_int_t m, const ae_int_t n, const complex_2d_array &a, const ae_int_t ia, const ae_int_t ja, complex_2d_array &b, const ae_int_t ib, const ae_int_t jb);

// Copy
//
// Inputs:
//     N   -   subvector size
//     A   -   source vector, N elements are copied
//     IA  -   source offset (first element index)
//     B   -   destination vector, must be large enough to store result
//     IB  -   destination offset (first element index)
void rvectorcopy(const ae_int_t n, const real_1d_array &a, const ae_int_t ia, const real_1d_array &b, const ae_int_t ib);

// Copy
//
// Inputs:
//     M   -   number of rows
//     N   -   number of columns
//     A   -   source matrix, MxN submatrix is copied and transposed
//     IA  -   submatrix offset (row index)
//     JA  -   submatrix offset (column index)
//     B   -   destination matrix, must be large enough to store result
//     IB  -   submatrix offset (row index)
//     JB  -   submatrix offset (column index)
void rmatrixcopy(const ae_int_t m, const ae_int_t n, const real_2d_array &a, const ae_int_t ia, const ae_int_t ja, const real_2d_array &b, const ae_int_t ib, const ae_int_t jb);

// Performs generalized copy: B := Beta*B + Alpha*A.
//
// If Beta=0, then previous contents of B is simply ignored. If Alpha=0, then
// A is ignored and not referenced. If both Alpha and Beta  are  zero,  B  is
// filled by zeros.
//
// Inputs:
//     M   -   number of rows
//     N   -   number of columns
//     Alpha-  coefficient
//     A   -   source matrix, MxN submatrix is copied and transposed
//     IA  -   submatrix offset (row index)
//     JA  -   submatrix offset (column index)
//     Beta-   coefficient
//     B   -   destination matrix, must be large enough to store result
//     IB  -   submatrix offset (row index)
//     JB  -   submatrix offset (column index)
void rmatrixgencopy(const ae_int_t m, const ae_int_t n, const double alpha, const real_2d_array &a, const ae_int_t ia, const ae_int_t ja, const double beta, const real_2d_array &b, const ae_int_t ib, const ae_int_t jb);

// Rank-1 correction: A := A + alpha*u*v'
//
// NOTE: this  function  expects  A  to  be  large enough to store result. No
//       automatic preallocation happens for  smaller  arrays.  No  integrity
//       checks is performed for sizes of A, u, v.
//
// Inputs:
//     M   -   number of rows
//     N   -   number of columns
//     A   -   target matrix, MxN submatrix is updated
//     IA  -   submatrix offset (row index)
//     JA  -   submatrix offset (column index)
//     Alpha-  coefficient
//     U   -   vector #1
//     IU  -   subvector offset
//     V   -   vector #2
//     IV  -   subvector offset
//
//
// ALGLIB Routine: Copyright 16.10.2017 by Sergey Bochkanov
void rmatrixger(const ae_int_t m, const ae_int_t n, const real_2d_array &a, const ae_int_t ia, const ae_int_t ja, const double alpha, const real_1d_array &u, const ae_int_t iu, const real_1d_array &v, const ae_int_t iv);

// Rank-1 correction: A := A + u*v'
//
// Inputs:
//     M   -   number of rows
//     N   -   number of columns
//     A   -   target matrix, MxN submatrix is updated
//     IA  -   submatrix offset (row index)
//     JA  -   submatrix offset (column index)
//     U   -   vector #1
//     IU  -   subvector offset
//     V   -   vector #2
//     IV  -   subvector offset
void cmatrixrank1(const ae_int_t m, const ae_int_t n, complex_2d_array &a, const ae_int_t ia, const ae_int_t ja, complex_1d_array &u, const ae_int_t iu, complex_1d_array &v, const ae_int_t iv);

// IMPORTANT: this function is deprecated since ALGLIB 3.13. Use RMatrixGER()
//            which is more generic version of this function.
//
// Rank-1 correction: A := A + u*v'
//
// Inputs:
//     M   -   number of rows
//     N   -   number of columns
//     A   -   target matrix, MxN submatrix is updated
//     IA  -   submatrix offset (row index)
//     JA  -   submatrix offset (column index)
//     U   -   vector #1
//     IU  -   subvector offset
//     V   -   vector #2
//     IV  -   subvector offset
void rmatrixrank1(const ae_int_t m, const ae_int_t n, real_2d_array &a, const ae_int_t ia, const ae_int_t ja, real_1d_array &u, const ae_int_t iu, real_1d_array &v, const ae_int_t iv);

void rmatrixgemv(const ae_int_t m, const ae_int_t n, const double alpha, const real_2d_array &a, const ae_int_t ia, const ae_int_t ja, const ae_int_t opa, const real_1d_array &x, const ae_int_t ix, const double beta, const real_1d_array &y, const ae_int_t iy);

// Matrix-vector product: y := op(A)*x
//
// Inputs:
//     M   -   number of rows of op(A)
//             M >= 0
//     N   -   number of columns of op(A)
//             N >= 0
//     A   -   target matrix
//     IA  -   submatrix offset (row index)
//     JA  -   submatrix offset (column index)
//     OpA -   operation type:
//             * OpA=0     =>  op(A) = A
//             * OpA=1     =>  op(A) = A^T
//             * OpA=2     =>  op(A) = A^H
//     X   -   input vector
//     IX  -   subvector offset
//     IY  -   subvector offset
//     Y   -   preallocated matrix, must be large enough to store result
//
// Outputs:
//     Y   -   vector which stores result
//
// if M=0, then subroutine does nothing.
// if N=0, Y is filled by zeros.
//
//
// ALGLIB Routine: Copyright 28.01.2010 by Sergey Bochkanov
void cmatrixmv(const ae_int_t m, const ae_int_t n, const complex_2d_array &a, const ae_int_t ia, const ae_int_t ja, const ae_int_t opa, const complex_1d_array &x, const ae_int_t ix, complex_1d_array &y, const ae_int_t iy);

// IMPORTANT: this function is deprecated since ALGLIB 3.13. Use RMatrixGEMV()
//            which is more generic version of this function.
//
// Matrix-vector product: y := op(A)*x
//
// Inputs:
//     M   -   number of rows of op(A)
//     N   -   number of columns of op(A)
//     A   -   target matrix
//     IA  -   submatrix offset (row index)
//     JA  -   submatrix offset (column index)
//     OpA -   operation type:
//             * OpA=0     =>  op(A) = A
//             * OpA=1     =>  op(A) = A^T
//     X   -   input vector
//     IX  -   subvector offset
//     IY  -   subvector offset
//     Y   -   preallocated matrix, must be large enough to store result
//
// Outputs:
//     Y   -   vector which stores result
//
// if M=0, then subroutine does nothing.
// if N=0, Y is filled by zeros.
//
//
// ALGLIB Routine: Copyright 28.01.2010 by Sergey Bochkanov
void rmatrixmv(const ae_int_t m, const ae_int_t n, const real_2d_array &a, const ae_int_t ia, const ae_int_t ja, const ae_int_t opa, const real_1d_array &x, const ae_int_t ix, const real_1d_array &y, const ae_int_t iy);

void rmatrixsymv(const ae_int_t n, const double alpha, const real_2d_array &a, const ae_int_t ia, const ae_int_t ja, const bool isupper, const real_1d_array &x, const ae_int_t ix, const double beta, const real_1d_array &y, const ae_int_t iy);

double rmatrixsyvmv(const ae_int_t n, const real_2d_array &a, const ae_int_t ia, const ae_int_t ja, const bool isupper, const real_1d_array &x, const ae_int_t ix, const real_1d_array &tmp);

// This subroutine solves linear system op(A)*x=b where:
// * A is NxN upper/lower triangular/unitriangular matrix
// * X and B are Nx1 vectors
// * "op" may be identity transformation, transposition, conjugate transposition
//
// Solution replaces X.
//
// IMPORTANT: * no overflow/underflow/denegeracy tests is performed.
//            * no integrity checks for operand sizes, out-of-bounds accesses
//              and so on is performed
//
// Inputs:
//     N   -   matrix size, N >= 0
//     A       -   matrix, actial matrix is stored in A[IA:IA+N-1,JA:JA+N-1]
//     IA      -   submatrix offset
//     JA      -   submatrix offset
//     IsUpper -   whether matrix is upper triangular
//     IsUnit  -   whether matrix is unitriangular
//     OpType  -   transformation type:
//                 * 0 - no transformation
//                 * 1 - transposition
//     X       -   right part, actual vector is stored in X[IX:IX+N-1]
//     IX      -   offset
//
// Outputs:
//     X       -   solution replaces elements X[IX:IX+N-1]
//
// ALGLIB Routine: Copyright (c) 2017 by Sergey Bochkanov - converted to ALGLIB, remastered from LAPACK's DTRSV.
// Copyright (c) 2016 Reference BLAS level1 routine (LAPACK version 3.7.0)
//      Reference BLAS is a software package provided by Univ. of Tennessee,
//      Univ. of California Berkeley, Univ. of Colorado Denver and NAG Ltd.
void rmatrixtrsv(const ae_int_t n, const real_2d_array &a, const ae_int_t ia, const ae_int_t ja, const bool isupper, const bool isunit, const ae_int_t optype, const real_1d_array &x, const ae_int_t ix);

// This subroutine calculates X*op(A^-1) where:
// * X is MxN general matrix
// * A is NxN upper/lower triangular/unitriangular matrix
// * "op" may be identity transformation, transposition, conjugate transposition
// Multiplication result replaces X.
//
// Inputs:
//     N   -   matrix size, N >= 0
//     M   -   matrix size, N >= 0
//     A       -   matrix, actial matrix is stored in A[I1:I1+N-1,J1:J1+N-1]
//     I1      -   submatrix offset
//     J1      -   submatrix offset
//     IsUpper -   whether matrix is upper triangular
//     IsUnit  -   whether matrix is unitriangular
//     OpType  -   transformation type:
//                 * 0 - no transformation
//                 * 1 - transposition
//                 * 2 - conjugate transposition
//     X   -   matrix, actial matrix is stored in X[I2:I2+M-1,J2:J2+N-1]
//     I2  -   submatrix offset
//     J2  -   submatrix offset
//
// ALGLIB Routine: Copyright 20.01.2018 by Sergey Bochkanov
void cmatrixrighttrsm(const ae_int_t m, const ae_int_t n, const complex_2d_array &a, const ae_int_t i1, const ae_int_t j1, const bool isupper, const bool isunit, const ae_int_t optype, const complex_2d_array &x, const ae_int_t i2, const ae_int_t j2);

// This subroutine calculates op(A^-1)*X where:
// * X is MxN general matrix
// * A is MxM upper/lower triangular/unitriangular matrix
// * "op" may be identity transformation, transposition, conjugate transposition
// Multiplication result replaces X.
//
// Inputs:
//     N   -   matrix size, N >= 0
//     M   -   matrix size, N >= 0
//     A       -   matrix, actial matrix is stored in A[I1:I1+M-1,J1:J1+M-1]
//     I1      -   submatrix offset
//     J1      -   submatrix offset
//     IsUpper -   whether matrix is upper triangular
//     IsUnit  -   whether matrix is unitriangular
//     OpType  -   transformation type:
//                 * 0 - no transformation
//                 * 1 - transposition
//                 * 2 - conjugate transposition
//     X   -   matrix, actial matrix is stored in X[I2:I2+M-1,J2:J2+N-1]
//     I2  -   submatrix offset
//     J2  -   submatrix offset
//
// ALGLIB Routine: Copyright 15.12.2009-22.01.2018 by Sergey Bochkanov
void cmatrixlefttrsm(const ae_int_t m, const ae_int_t n, const complex_2d_array &a, const ae_int_t i1, const ae_int_t j1, const bool isupper, const bool isunit, const ae_int_t optype, const complex_2d_array &x, const ae_int_t i2, const ae_int_t j2);

// This subroutine calculates X*op(A^-1) where:
// * X is MxN general matrix
// * A is NxN upper/lower triangular/unitriangular matrix
// * "op" may be identity transformation, transposition
// Multiplication result replaces X.
//
// Inputs:
//     N   -   matrix size, N >= 0
//     M   -   matrix size, N >= 0
//     A       -   matrix, actial matrix is stored in A[I1:I1+N-1,J1:J1+N-1]
//     I1      -   submatrix offset
//     J1      -   submatrix offset
//     IsUpper -   whether matrix is upper triangular
//     IsUnit  -   whether matrix is unitriangular
//     OpType  -   transformation type:
//                 * 0 - no transformation
//                 * 1 - transposition
//     X   -   matrix, actial matrix is stored in X[I2:I2+M-1,J2:J2+N-1]
//     I2  -   submatrix offset
//     J2  -   submatrix offset
//
// ALGLIB Routine: Copyright 15.12.2009-22.01.2018 by Sergey Bochkanov
void rmatrixrighttrsm(const ae_int_t m, const ae_int_t n, const real_2d_array &a, const ae_int_t i1, const ae_int_t j1, const bool isupper, const bool isunit, const ae_int_t optype, const real_2d_array &x, const ae_int_t i2, const ae_int_t j2);

// This subroutine calculates op(A^-1)*X where:
// * X is MxN general matrix
// * A is MxM upper/lower triangular/unitriangular matrix
// * "op" may be identity transformation, transposition
// Multiplication result replaces X.
//
// Inputs:
//     N   -   matrix size, N >= 0
//     M   -   matrix size, N >= 0
//     A       -   matrix, actial matrix is stored in A[I1:I1+M-1,J1:J1+M-1]
//     I1      -   submatrix offset
//     J1      -   submatrix offset
//     IsUpper -   whether matrix is upper triangular
//     IsUnit  -   whether matrix is unitriangular
//     OpType  -   transformation type:
//                 * 0 - no transformation
//                 * 1 - transposition
//     X   -   matrix, actial matrix is stored in X[I2:I2+M-1,J2:J2+N-1]
//     I2  -   submatrix offset
//     J2  -   submatrix offset
//
// ALGLIB Routine: Copyright 15.12.2009-22.01.2018 by Sergey Bochkanov
void rmatrixlefttrsm(const ae_int_t m, const ae_int_t n, const real_2d_array &a, const ae_int_t i1, const ae_int_t j1, const bool isupper, const bool isunit, const ae_int_t optype, const real_2d_array &x, const ae_int_t i2, const ae_int_t j2);

// This subroutine calculates  C=alpha*A*A^H+beta*C  or  C=alpha*A^H*A+beta*C
// where:
// * C is NxN Hermitian matrix given by its upper/lower triangle
// * A is NxK matrix when A*A^H is calculated, KxN matrix otherwise
//
// Additional info:
// * multiplication result replaces C. If Beta=0, C elements are not used in
//   calculations (not multiplied by zero - just not referenced)
// * if Alpha=0, A is not used (not multiplied by zero - just not referenced)
// * if both Beta and Alpha are zero, C is filled by zeros.
//
// Inputs:
//     N       -   matrix size, N >= 0
//     K       -   matrix size, K >= 0
//     Alpha   -   coefficient
//     A       -   matrix
//     IA      -   submatrix offset (row index)
//     JA      -   submatrix offset (column index)
//     OpTypeA -   multiplication type:
//                 * 0 - A*A^H is calculated
//                 * 2 - A^H*A is calculated
//     Beta    -   coefficient
//     C       -   preallocated input/output matrix
//     IC      -   submatrix offset (row index)
//     JC      -   submatrix offset (column index)
//     IsUpper -   whether upper or lower triangle of C is updated;
//                 this function updates only one half of C, leaving
//                 other half unchanged (not referenced at all).
//
// ALGLIB Routine: Copyright 16.12.2009-22.01.2018 by Sergey Bochkanov
void cmatrixherk(const ae_int_t n, const ae_int_t k, const double alpha, const complex_2d_array &a, const ae_int_t ia, const ae_int_t ja, const ae_int_t optypea, const double beta, const complex_2d_array &c, const ae_int_t ic, const ae_int_t jc, const bool isupper);

// This subroutine calculates  C=alpha*A*A^T+beta*C  or  C=alpha*A^T*A+beta*C
// where:
// * C is NxN symmetric matrix given by its upper/lower triangle
// * A is NxK matrix when A*A^T is calculated, KxN matrix otherwise
//
// Additional info:
// * multiplication result replaces C. If Beta=0, C elements are not used in
//   calculations (not multiplied by zero - just not referenced)
// * if Alpha=0, A is not used (not multiplied by zero - just not referenced)
// * if both Beta and Alpha are zero, C is filled by zeros.
//
// Inputs:
//     N       -   matrix size, N >= 0
//     K       -   matrix size, K >= 0
//     Alpha   -   coefficient
//     A       -   matrix
//     IA      -   submatrix offset (row index)
//     JA      -   submatrix offset (column index)
//     OpTypeA -   multiplication type:
//                 * 0 - A*A^T is calculated
//                 * 2 - A^T*A is calculated
//     Beta    -   coefficient
//     C       -   preallocated input/output matrix
//     IC      -   submatrix offset (row index)
//     JC      -   submatrix offset (column index)
//     IsUpper -   whether C is upper triangular or lower triangular
//
// ALGLIB Routine: Copyright 16.12.2009-22.01.2018 by Sergey Bochkanov
void rmatrixsyrk(const ae_int_t n, const ae_int_t k, const double alpha, const real_2d_array &a, const ae_int_t ia, const ae_int_t ja, const ae_int_t optypea, const double beta, const real_2d_array &c, const ae_int_t ic, const ae_int_t jc, const bool isupper);

// This subroutine calculates C = alpha*op1(A)*op2(B) +beta*C where:
// * C is MxN general matrix
// * op1(A) is MxK matrix
// * op2(B) is KxN matrix
// * "op" may be identity transformation, transposition, conjugate transposition
//
// Additional info:
// * cache-oblivious algorithm is used.
// * multiplication result replaces C. If Beta=0, C elements are not used in
//   calculations (not multiplied by zero - just not referenced)
// * if Alpha=0, A is not used (not multiplied by zero - just not referenced)
// * if both Beta and Alpha are zero, C is filled by zeros.
//
// IMPORTANT:
//
// This function does NOT preallocate output matrix C, it MUST be preallocated
// by caller prior to calling this function. In case C does not have  enough
// space to store result, exception will be generated.
//
// Inputs:
//     M       -   matrix size, M > 0
//     N       -   matrix size, N > 0
//     K       -   matrix size, K > 0
//     Alpha   -   coefficient
//     A       -   matrix
//     IA      -   submatrix offset
//     JA      -   submatrix offset
//     OpTypeA -   transformation type:
//                 * 0 - no transformation
//                 * 1 - transposition
//                 * 2 - conjugate transposition
//     B       -   matrix
//     IB      -   submatrix offset
//     JB      -   submatrix offset
//     OpTypeB -   transformation type:
//                 * 0 - no transformation
//                 * 1 - transposition
//                 * 2 - conjugate transposition
//     Beta    -   coefficient
//     C       -   matrix (PREALLOCATED, large enough to store result)
//     IC      -   submatrix offset
//     JC      -   submatrix offset
//
// ALGLIB Routine: Copyright 2009-2019 by Sergey Bochkanov
void cmatrixgemm(const ae_int_t m, const ae_int_t n, const ae_int_t k, const complex alpha, const complex_2d_array &a, const ae_int_t ia, const ae_int_t ja, const ae_int_t optypea, const complex_2d_array &b, const ae_int_t ib, const ae_int_t jb, const ae_int_t optypeb, const complex beta, const complex_2d_array &c, const ae_int_t ic, const ae_int_t jc);

// This subroutine calculates C = alpha*op1(A)*op2(B) +beta*C where:
// * C is MxN general matrix
// * op1(A) is MxK matrix
// * op2(B) is KxN matrix
// * "op" may be identity transformation, transposition
//
// Additional info:
// * cache-oblivious algorithm is used.
// * multiplication result replaces C. If Beta=0, C elements are not used in
//   calculations (not multiplied by zero - just not referenced)
// * if Alpha=0, A is not used (not multiplied by zero - just not referenced)
// * if both Beta and Alpha are zero, C is filled by zeros.
//
// IMPORTANT:
//
// This function does NOT preallocate output matrix C, it MUST be preallocated
// by caller prior to calling this function. In case C does not have  enough
// space to store result, exception will be generated.
//
// Inputs:
//     M       -   matrix size, M > 0
//     N       -   matrix size, N > 0
//     K       -   matrix size, K > 0
//     Alpha   -   coefficient
//     A       -   matrix
//     IA      -   submatrix offset
//     JA      -   submatrix offset
//     OpTypeA -   transformation type:
//                 * 0 - no transformation
//                 * 1 - transposition
//     B       -   matrix
//     IB      -   submatrix offset
//     JB      -   submatrix offset
//     OpTypeB -   transformation type:
//                 * 0 - no transformation
//                 * 1 - transposition
//     Beta    -   coefficient
//     C       -   PREALLOCATED output matrix, large enough to store result
//     IC      -   submatrix offset
//     JC      -   submatrix offset
//
// ALGLIB Routine: Copyright 2009-2019 by Sergey Bochkanov
void rmatrixgemm(const ae_int_t m, const ae_int_t n, const ae_int_t k, const double alpha, const real_2d_array &a, const ae_int_t ia, const ae_int_t ja, const ae_int_t optypea, const real_2d_array &b, const ae_int_t ib, const ae_int_t jb, const ae_int_t optypeb, const double beta, const real_2d_array &c, const ae_int_t ic, const ae_int_t jc);

// This subroutine is an older version of CMatrixHERK(), one with wrong  name
// (it is HErmitian update, not SYmmetric). It  is  left  here  for  backward
// compatibility.
//
// ALGLIB Routine: Copyright 16.12.2009 by Sergey Bochkanov
void cmatrixsyrk(const ae_int_t n, const ae_int_t k, const double alpha, const complex_2d_array &a, const ae_int_t ia, const ae_int_t ja, const ae_int_t optypea, const double beta, const complex_2d_array &c, const ae_int_t ic, const ae_int_t jc, const bool isupper);
} // end of namespace alglib

// === DLU Package ===
// Depends on: ABLAS
namespace alglib_impl {
void cmatrixluprec(CMatrix *a, ae_int_t offs, ae_int_t m, ae_int_t n, ZVector *pivots, CVector *tmp);
void rmatrixluprec(RMatrix *a, ae_int_t offs, ae_int_t m, ae_int_t n, ZVector *pivots, RVector *tmp);
void cmatrixplurec(CMatrix *a, ae_int_t offs, ae_int_t m, ae_int_t n, ZVector *pivots, CVector *tmp);
void rmatrixplurec(RMatrix *a, ae_int_t offs, ae_int_t m, ae_int_t n, ZVector *pivots, RVector *tmp);
} // end of namespace alglib_impl

// === SPTRF Package ===
// Depends on: SPARSE, DLU
namespace alglib_impl {
struct sluv2list1matrix {
   ae_int_t nfixed;
   ae_int_t ndynamic;
   ae_vector idxfirst;
   ae_vector strgidx;
   ae_vector strgval;
   ae_int_t nallocated;
   ae_int_t nused;
};
void sluv2list1matrix_init(void *_p, bool make_automatic);
void sluv2list1matrix_copy(void *_dst, void *_src, bool make_automatic);
void sluv2list1matrix_free(void *_p, bool make_automatic);

struct sluv2sparsetrail {
   ae_int_t n;
   ae_int_t k;
   ae_vector nzc;
   ae_int_t maxwrkcnt;
   ae_int_t maxwrknz;
   ae_int_t wrkcnt;
   ae_vector wrkset;
   ae_vector colid;
   ae_vector isdensified;
   ae_vector slscolptr;
   ae_vector slsrowptr;
   ae_vector slsidx;
   ae_vector slsval;
   ae_int_t slsused;
   ae_vector tmp0;
};
void sluv2sparsetrail_init(void *_p, bool make_automatic);
void sluv2sparsetrail_copy(void *_dst, void *_src, bool make_automatic);
void sluv2sparsetrail_free(void *_p, bool make_automatic);

struct sluv2densetrail {
   ae_int_t n;
   ae_int_t ndense;
   ae_matrix d;
   ae_vector did;
};
void sluv2densetrail_init(void *_p, bool make_automatic);
void sluv2densetrail_copy(void *_dst, void *_src, bool make_automatic);
void sluv2densetrail_free(void *_p, bool make_automatic);

struct sluv2buffer {
   ae_int_t n;
   sparsematrix sparsel;
   sparsematrix sparseut;
   sluv2list1matrix bleft;
   sluv2list1matrix bupper;
   sluv2sparsetrail strail;
   sluv2densetrail dtrail;
   ae_vector rowpermrawidx;
   ae_matrix dbuf;
   ae_vector v0i;
   ae_vector v1i;
   ae_vector v0r;
   ae_vector v1r;
   ae_vector tmp0;
   ae_vector tmpi;
   ae_vector tmpp;
};
void sluv2buffer_init(void *_p, bool make_automatic);
void sluv2buffer_copy(void *_dst, void *_src, bool make_automatic);
void sluv2buffer_free(void *_p, bool make_automatic);

bool sptrflu(sparsematrix *a, ae_int_t pivottype, ZVector *pr, ZVector *pc, sluv2buffer *buf);
} // end of namespace alglib_impl

// === MATGEN Package ===
// Depends on: (AlgLibInternal) CREFLECTIONS
// Depends on: (AlgLibMisc) HQRND
// Depends on: ABLAS
namespace alglib_impl {
void rmatrixrndorthogonal(ae_int_t n, RMatrix *a);
void rmatrixrndcond(ae_int_t n, double c, RMatrix *a);
void cmatrixrndorthogonal(ae_int_t n, CMatrix *a);
void cmatrixrndcond(ae_int_t n, double c, CMatrix *a);
void smatrixrndcond(ae_int_t n, double c, RMatrix *a);
void spdmatrixrndcond(ae_int_t n, double c, RMatrix *a);
void hmatrixrndcond(ae_int_t n, double c, CMatrix *a);
void hpdmatrixrndcond(ae_int_t n, double c, CMatrix *a);
void rmatrixrndorthogonalfromtheright(RMatrix *a, ae_int_t m, ae_int_t n);
void rmatrixrndorthogonalfromtheleft(RMatrix *a, ae_int_t m, ae_int_t n);
void cmatrixrndorthogonalfromtheright(CMatrix *a, ae_int_t m, ae_int_t n);
void cmatrixrndorthogonalfromtheleft(CMatrix *a, ae_int_t m, ae_int_t n);
void smatrixrndmultiply(RMatrix *a, ae_int_t n);
void hmatrixrndmultiply(CMatrix *a, ae_int_t n);
} // end of namespace alglib_impl

namespace alglib {
// Generation of a random uniformly distributed (Haar) orthogonal matrix
//
// Inputs:
//     N   -   matrix size, N >= 1
//
// Outputs:
//     A   -   orthogonal NxN matrix, array[0..N-1,0..N-1]
//
// NOTE: this function uses algorithm  described  in  Stewart, G. W.  (1980),
//       "The Efficient Generation of  Random  Orthogonal  Matrices  with  an
//       Application to Condition Estimators".
//
//       Speaking short, to generate an (N+1)x(N+1) orthogonal matrix, it:
//       * takes an NxN one
//       * takes uniformly distributed unit vector of dimension N+1.
//       * constructs a Householder reflection from the vector, then applies
//         it to the smaller matrix (embedded in the larger size with a 1 at
//         the bottom right corner).
//
// ALGLIB Routine: Copyright 04.12.2009 by Sergey Bochkanov
void rmatrixrndorthogonal(const ae_int_t n, real_2d_array &a);

// Generation of random NxN matrix with given condition number and norm2(A)=1
//
// Inputs:
//     N   -   matrix size
//     C   -   condition number (in 2-norm)
//
// Outputs:
//     A   -   random matrix with norm2(A)=1 and cond(A)=C
//
// ALGLIB Routine: Copyright 04.12.2009 by Sergey Bochkanov
void rmatrixrndcond(const ae_int_t n, const double c, real_2d_array &a);

// Generation of a random Haar distributed orthogonal complex matrix
//
// Inputs:
//     N   -   matrix size, N >= 1
//
// Outputs:
//     A   -   orthogonal NxN matrix, array[0..N-1,0..N-1]
//
// NOTE: this function uses algorithm  described  in  Stewart, G. W.  (1980),
//       "The Efficient Generation of  Random  Orthogonal  Matrices  with  an
//       Application to Condition Estimators".
//
//       Speaking short, to generate an (N+1)x(N+1) orthogonal matrix, it:
//       * takes an NxN one
//       * takes uniformly distributed unit vector of dimension N+1.
//       * constructs a Householder reflection from the vector, then applies
//         it to the smaller matrix (embedded in the larger size with a 1 at
//         the bottom right corner).
//
// ALGLIB Routine: Copyright 04.12.2009 by Sergey Bochkanov
void cmatrixrndorthogonal(const ae_int_t n, complex_2d_array &a);

// Generation of random NxN complex matrix with given condition number C and
// norm2(A)=1
//
// Inputs:
//     N   -   matrix size
//     C   -   condition number (in 2-norm)
//
// Outputs:
//     A   -   random matrix with norm2(A)=1 and cond(A)=C
//
// ALGLIB Routine: Copyright 04.12.2009 by Sergey Bochkanov
void cmatrixrndcond(const ae_int_t n, const double c, complex_2d_array &a);

// Generation of random NxN symmetric matrix with given condition number  and
// norm2(A)=1
//
// Inputs:
//     N   -   matrix size
//     C   -   condition number (in 2-norm)
//
// Outputs:
//     A   -   random matrix with norm2(A)=1 and cond(A)=C
//
// ALGLIB Routine: Copyright 04.12.2009 by Sergey Bochkanov
void smatrixrndcond(const ae_int_t n, const double c, real_2d_array &a);

// Generation of random NxN symmetric positive definite matrix with given
// condition number and norm2(A)=1
//
// Inputs:
//     N   -   matrix size
//     C   -   condition number (in 2-norm)
//
// Outputs:
//     A   -   random SPD matrix with norm2(A)=1 and cond(A)=C
//
// ALGLIB Routine: Copyright 04.12.2009 by Sergey Bochkanov
void spdmatrixrndcond(const ae_int_t n, const double c, real_2d_array &a);

// Generation of random NxN Hermitian matrix with given condition number  and
// norm2(A)=1
//
// Inputs:
//     N   -   matrix size
//     C   -   condition number (in 2-norm)
//
// Outputs:
//     A   -   random matrix with norm2(A)=1 and cond(A)=C
//
// ALGLIB Routine: Copyright 04.12.2009 by Sergey Bochkanov
void hmatrixrndcond(const ae_int_t n, const double c, complex_2d_array &a);

// Generation of random NxN Hermitian positive definite matrix with given
// condition number and norm2(A)=1
//
// Inputs:
//     N   -   matrix size
//     C   -   condition number (in 2-norm)
//
// Outputs:
//     A   -   random HPD matrix with norm2(A)=1 and cond(A)=C
//
// ALGLIB Routine: Copyright 04.12.2009 by Sergey Bochkanov
void hpdmatrixrndcond(const ae_int_t n, const double c, complex_2d_array &a);

// Multiplication of MxN matrix by NxN random Haar distributed orthogonal matrix
//
// Inputs:
//     A   -   matrix, array[0..M-1, 0..N-1]
//     M, N-   matrix size
//
// Outputs:
//     A   -   A*Q, where Q is random NxN orthogonal matrix
//
// ALGLIB Routine: Copyright 04.12.2009 by Sergey Bochkanov
void rmatrixrndorthogonalfromtheright(real_2d_array &a, const ae_int_t m, const ae_int_t n);

// Multiplication of MxN matrix by MxM random Haar distributed orthogonal matrix
//
// Inputs:
//     A   -   matrix, array[0..M-1, 0..N-1]
//     M, N-   matrix size
//
// Outputs:
//     A   -   Q*A, where Q is random MxM orthogonal matrix
//
// ALGLIB Routine: Copyright 04.12.2009 by Sergey Bochkanov
void rmatrixrndorthogonalfromtheleft(real_2d_array &a, const ae_int_t m, const ae_int_t n);

// Multiplication of MxN complex matrix by NxN random Haar distributed
// complex orthogonal matrix
//
// Inputs:
//     A   -   matrix, array[0..M-1, 0..N-1]
//     M, N-   matrix size
//
// Outputs:
//     A   -   A*Q, where Q is random NxN orthogonal matrix
//
// ALGLIB Routine: Copyright 04.12.2009 by Sergey Bochkanov
void cmatrixrndorthogonalfromtheright(complex_2d_array &a, const ae_int_t m, const ae_int_t n);

// Multiplication of MxN complex matrix by MxM random Haar distributed
// complex orthogonal matrix
//
// Inputs:
//     A   -   matrix, array[0..M-1, 0..N-1]
//     M, N-   matrix size
//
// Outputs:
//     A   -   Q*A, where Q is random MxM orthogonal matrix
//
// ALGLIB Routine: Copyright 04.12.2009 by Sergey Bochkanov
void cmatrixrndorthogonalfromtheleft(complex_2d_array &a, const ae_int_t m, const ae_int_t n);

// Symmetric multiplication of NxN matrix by random Haar distributed
// orthogonal  matrix
//
// Inputs:
//     A   -   matrix, array[0..N-1, 0..N-1]
//     N   -   matrix size
//
// Outputs:
//     A   -   Q'*A*Q, where Q is random NxN orthogonal matrix
//
// ALGLIB Routine: Copyright 04.12.2009 by Sergey Bochkanov
void smatrixrndmultiply(real_2d_array &a, const ae_int_t n);

// Hermitian multiplication of NxN matrix by random Haar distributed
// complex orthogonal matrix
//
// Inputs:
//     A   -   matrix, array[0..N-1, 0..N-1]
//     N   -   matrix size
//
// Outputs:
//     A   -   Q^H*A*Q, where Q is random NxN orthogonal matrix
//
// ALGLIB Routine: Copyright 04.12.2009 by Sergey Bochkanov
void hmatrixrndmultiply(complex_2d_array &a, const ae_int_t n);
} // end of namespace alglib

// === TRFAC Package ===
// Depends on: (AlgLibInternal) ROTATIONS
// Depends on: SPTRF, MATGEN
namespace alglib_impl {
void rmatrixlu(RMatrix *a, ae_int_t m, ae_int_t n, ZVector *pivots);
void cmatrixlu(CMatrix *a, ae_int_t m, ae_int_t n, ZVector *pivots);
bool hpdmatrixcholesky(CMatrix *a, ae_int_t n, bool isupper);
bool spdmatrixcholesky(RMatrix *a, ae_int_t n, bool isupper);
void spdmatrixcholeskyupdateadd1(RMatrix *a, ae_int_t n, bool isupper, RVector *u);
void spdmatrixcholeskyupdatefix(RMatrix *a, ae_int_t n, bool isupper, BVector *fix);
void spdmatrixcholeskyupdateadd1buf(RMatrix *a, ae_int_t n, bool isupper, RVector *u, RVector *bufr);
void spdmatrixcholeskyupdatefixbuf(RMatrix *a, ae_int_t n, bool isupper, BVector *fix, RVector *bufr);
bool sparselu(sparsematrix *a, ae_int_t pivottype, ZVector *p, ZVector *q);
bool sparsecholeskyskyline(sparsematrix *a, ae_int_t n, bool isupper);
bool sparsecholeskyx(sparsematrix *a, ae_int_t n, bool isupper, ZVector *p0, ZVector *p1, ae_int_t ordering, ae_int_t algo, ae_int_t fmt, sparsebuffers *buf, sparsematrix *c);
void rmatrixlup(RMatrix *a, ae_int_t m, ae_int_t n, ZVector *pivots);
void cmatrixlup(CMatrix *a, ae_int_t m, ae_int_t n, ZVector *pivots);
void rmatrixplu(RMatrix *a, ae_int_t m, ae_int_t n, ZVector *pivots);
void cmatrixplu(CMatrix *a, ae_int_t m, ae_int_t n, ZVector *pivots);
bool spdmatrixcholeskyrec(RMatrix *a, ae_int_t offs, ae_int_t n, bool isupper, RVector *tmp);
} // end of namespace alglib_impl

namespace alglib {
// LU decomposition of a general real matrix with row pivoting
//
// A is represented as A = P*L*U, where:
// * L is lower unitriangular matrix
// * U is upper triangular matrix
// * P = P0*P1*...*PK, K=min(M,N)-1,
//   Pi - permutation matrix for I and Pivots[I]
//
// Inputs:
//     A       -   array[0..M-1, 0..N-1].
//     M       -   number of rows in matrix A.
//     N       -   number of columns in matrix A.
//
//
// Outputs:
//     A       -   matrices L and U in compact form:
//                 * L is stored under main diagonal
//                 * U is stored on and above main diagonal
//     Pivots  -   permutation matrix in compact form.
//                 array[0..Min(M-1,N-1)].
//
// ALGLIB Routine: Copyright 10.01.2010 by Sergey Bochkanov
void rmatrixlu(real_2d_array &a, const ae_int_t m, const ae_int_t n, integer_1d_array &pivots);

// LU decomposition of a general complex matrix with row pivoting
//
// A is represented as A = P*L*U, where:
// * L is lower unitriangular matrix
// * U is upper triangular matrix
// * P = P0*P1*...*PK, K=min(M,N)-1,
//   Pi - permutation matrix for I and Pivots[I]
//
// Inputs:
//     A       -   array[0..M-1, 0..N-1].
//     M       -   number of rows in matrix A.
//     N       -   number of columns in matrix A.
//
//
// Outputs:
//     A       -   matrices L and U in compact form:
//                 * L is stored under main diagonal
//                 * U is stored on and above main diagonal
//     Pivots  -   permutation matrix in compact form.
//                 array[0..Min(M-1,N-1)].
//
// ALGLIB Routine: Copyright 10.01.2010 by Sergey Bochkanov
void cmatrixlu(complex_2d_array &a, const ae_int_t m, const ae_int_t n, integer_1d_array &pivots);

// Cache-oblivious Cholesky decomposition
//
// The algorithm computes Cholesky decomposition  of  a  Hermitian  positive-
// definite matrix. The result of an algorithm is a representation  of  A  as
// A=U'*U  or A=L*L' (here X' denotes conj(X^T)).
//
// Inputs:
//     A       -   upper or lower triangle of a factorized matrix.
//                 array with elements [0..N-1, 0..N-1].
//     N       -   size of matrix A.
//     IsUpper -   if IsUpper=True, then A contains an upper triangle of
//                 a symmetric matrix, otherwise A contains a lower one.
//
// Outputs:
//     A       -   the result of factorization. If IsUpper=True, then
//                 the upper triangle contains matrix U, so that A = U'*U,
//                 and the elements below the main diagonal are not modified.
//                 Similarly, if IsUpper = False.
//
// Result:
//     If  the  matrix  is  positive-definite,  the  function  returns  True.
//     Otherwise, the function returns False. Contents of A is not determined
//     in such case.
//
// ALGLIB Routine: Copyright 15.12.2009-22.01.2018 by Sergey Bochkanov
bool hpdmatrixcholesky(complex_2d_array &a, const ae_int_t n, const bool isupper);

// Cache-oblivious Cholesky decomposition
//
// The algorithm computes Cholesky decomposition  of  a  symmetric  positive-
// definite matrix. The result of an algorithm is a representation  of  A  as
// A=U^T*U  or A=L*L^T
//
// Inputs:
//     A       -   upper or lower triangle of a factorized matrix.
//                 array with elements [0..N-1, 0..N-1].
//     N       -   size of matrix A.
//     IsUpper -   if IsUpper=True, then A contains an upper triangle of
//                 a symmetric matrix, otherwise A contains a lower one.
//
// Outputs:
//     A       -   the result of factorization. If IsUpper=True, then
//                 the upper triangle contains matrix U, so that A = U^T*U,
//                 and the elements below the main diagonal are not modified.
//                 Similarly, if IsUpper = False.
//
// Result:
//     If  the  matrix  is  positive-definite,  the  function  returns  True.
//     Otherwise, the function returns False. Contents of A is not determined
//     in such case.
//
// ALGLIB Routine: Copyright 15.12.2009 by Sergey Bochkanov
bool spdmatrixcholesky(real_2d_array &a, const ae_int_t n, const bool isupper);

// Update of Cholesky decomposition: rank-1 update to original A.  "Buffered"
// version which uses preallocated buffer which is saved  between  subsequent
// function calls.
//
// This function uses internally allocated buffer which is not saved  between
// subsequent  calls.  So,  if  you  perform  a lot  of  subsequent  updates,
// we  recommend   you   to   use   "buffered"   version   of  this function:
// SPDMatrixCholeskyUpdateAdd1Buf().
//
// Inputs:
//     A       -   upper or lower Cholesky factor.
//                 array with elements [0..N-1, 0..N-1].
//                 Exception is thrown if array size is too small.
//     N       -   size of matrix A, N > 0
//     IsUpper -   if IsUpper=True, then A contains  upper  Cholesky  factor;
//                 otherwise A contains a lower one.
//     U       -   array[N], rank-1 update to A: A_mod = A + u*u'
//                 Exception is thrown if array size is too small.
//     BufR    -   possibly preallocated  buffer;  automatically  resized  if
//                 needed. It is recommended to  reuse  this  buffer  if  you
//                 perform a lot of subsequent decompositions.
//
// Outputs:
//     A       -   updated factorization.  If  IsUpper=True,  then  the  upper
//                 triangle contains matrix U, and the elements below the main
//                 diagonal are not modified. Similarly, if IsUpper = False.
//
// NOTE: this function always succeeds, so it does not return completion code
//
// NOTE: this function checks sizes of input arrays, but it does  NOT  checks
//       for presence of infinities or NAN's.
// ALGLIB: Copyright 03.02.2014 by Sergey Bochkanov
void spdmatrixcholeskyupdateadd1(const real_2d_array &a, const ae_int_t n, const bool isupper, const real_1d_array &u);

// Update of Cholesky decomposition: "fixing" some variables.
//
// This function uses internally allocated buffer which is not saved  between
// subsequent  calls.  So,  if  you  perform  a lot  of  subsequent  updates,
// we  recommend   you   to   use   "buffered"   version   of  this function:
// SPDMatrixCholeskyUpdateFixBuf().
//
// "FIXING" EXPLAINED:
//
//     Suppose we have N*N positive definite matrix A. "Fixing" some variable
//     means filling corresponding row/column of  A  by  zeros,  and  setting
//     diagonal element to 1.
//
//     For example, if we fix 2nd variable in 4*4 matrix A, it becomes Af:
//
//         ( A00  A01  A02  A03 )      ( Af00  0   Af02 Af03 )
//         ( A10  A11  A12  A13 )      (  0    1    0    0   )
//         ( A20  A21  A22  A23 )  =>  ( Af20  0   Af22 Af23 )
//         ( A30  A31  A32  A33 )      ( Af30  0   Af32 Af33 )
//
//     If we have Cholesky decomposition of A, it must be recalculated  after
//     variables were  fixed.  However,  it  is  possible  to  use  efficient
//     algorithm, which needs O(K*N^2)  time  to  "fix"  K  variables,  given
//     Cholesky decomposition of original, "unfixed" A.
//
// Inputs:
//     A       -   upper or lower Cholesky factor.
//                 array with elements [0..N-1, 0..N-1].
//                 Exception is thrown if array size is too small.
//     N       -   size of matrix A, N > 0
//     IsUpper -   if IsUpper=True, then A contains  upper  Cholesky  factor;
//                 otherwise A contains a lower one.
//     Fix     -   array[N], I-th element is True if I-th  variable  must  be
//                 fixed. Exception is thrown if array size is too small.
//     BufR    -   possibly preallocated  buffer;  automatically  resized  if
//                 needed. It is recommended to  reuse  this  buffer  if  you
//                 perform a lot of subsequent decompositions.
//
// Outputs:
//     A       -   updated factorization.  If  IsUpper=True,  then  the  upper
//                 triangle contains matrix U, and the elements below the main
//                 diagonal are not modified. Similarly, if IsUpper = False.
//
// NOTE: this function always succeeds, so it does not return completion code
//
// NOTE: this function checks sizes of input arrays, but it does  NOT  checks
//       for presence of infinities or NAN's.
//
// NOTE: this  function  is  efficient  only  for  moderate amount of updated
//       variables - say, 0.1*N or 0.3*N. For larger amount of  variables  it
//       will  still  work,  but  you  may  get   better   performance   with
//       straightforward Cholesky.
// ALGLIB: Copyright 03.02.2014 by Sergey Bochkanov
void spdmatrixcholeskyupdatefix(const real_2d_array &a, const ae_int_t n, const bool isupper, const boolean_1d_array &fix);

// Update of Cholesky decomposition: rank-1 update to original A.  "Buffered"
// version which uses preallocated buffer which is saved  between  subsequent
// function calls.
//
// See comments for SPDMatrixCholeskyUpdateAdd1() for more information.
//
// Inputs:
//     A       -   upper or lower Cholesky factor.
//                 array with elements [0..N-1, 0..N-1].
//                 Exception is thrown if array size is too small.
//     N       -   size of matrix A, N > 0
//     IsUpper -   if IsUpper=True, then A contains  upper  Cholesky  factor;
//                 otherwise A contains a lower one.
//     U       -   array[N], rank-1 update to A: A_mod = A + u*u'
//                 Exception is thrown if array size is too small.
//     BufR    -   possibly preallocated  buffer;  automatically  resized  if
//                 needed. It is recommended to  reuse  this  buffer  if  you
//                 perform a lot of subsequent decompositions.
//
// Outputs:
//     A       -   updated factorization.  If  IsUpper=True,  then  the  upper
//                 triangle contains matrix U, and the elements below the main
//                 diagonal are not modified. Similarly, if IsUpper = False.
// ALGLIB: Copyright 03.02.2014 by Sergey Bochkanov
void spdmatrixcholeskyupdateadd1buf(const real_2d_array &a, const ae_int_t n, const bool isupper, const real_1d_array &u, real_1d_array &bufr);

// Update of Cholesky  decomposition:  "fixing"  some  variables.  "Buffered"
// version which uses preallocated buffer which is saved  between  subsequent
// function calls.
//
// See comments for SPDMatrixCholeskyUpdateFix() for more information.
//
// Inputs:
//     A       -   upper or lower Cholesky factor.
//                 array with elements [0..N-1, 0..N-1].
//                 Exception is thrown if array size is too small.
//     N       -   size of matrix A, N > 0
//     IsUpper -   if IsUpper=True, then A contains  upper  Cholesky  factor;
//                 otherwise A contains a lower one.
//     Fix     -   array[N], I-th element is True if I-th  variable  must  be
//                 fixed. Exception is thrown if array size is too small.
//     BufR    -   possibly preallocated  buffer;  automatically  resized  if
//                 needed. It is recommended to  reuse  this  buffer  if  you
//                 perform a lot of subsequent decompositions.
//
// Outputs:
//     A       -   updated factorization.  If  IsUpper=True,  then  the  upper
//                 triangle contains matrix U, and the elements below the main
//                 diagonal are not modified. Similarly, if IsUpper = False.
// ALGLIB: Copyright 03.02.2014 by Sergey Bochkanov
void spdmatrixcholeskyupdatefixbuf(const real_2d_array &a, const ae_int_t n, const bool isupper, const boolean_1d_array &fix, real_1d_array &bufr);

// Sparse LU decomposition with column pivoting for sparsity and row pivoting
// for stability. Input must be square sparse matrix stored in CRS format.
//
// The algorithm  computes  LU  decomposition  of  a  general  square  matrix
// (rectangular ones are not supported). The result  of  an  algorithm  is  a
// representation of A as A = P*L*U*Q, where:
// * L is lower unitriangular matrix
// * U is upper triangular matrix
// * P = P0*P1*...*PK, K=N-1, Pi - permutation matrix for I and P[I]
// * Q = QK*...*Q1*Q0, K=N-1, Qi - permutation matrix for I and Q[I]
//
// This function pivots columns for higher sparsity, and then pivots rows for
// stability (larger element at the diagonal).
//
// Inputs:
//     A       -   sparse NxN matrix in CRS format. An exception is generated
//                 if matrix is non-CRS or non-square.
//     PivotType-  pivoting strategy:
//                 * 0 for best pivoting available (2 in current version)
//                 * 1 for row-only pivoting (NOT RECOMMENDED)
//                 * 2 for complete pivoting which produces most sparse outputs
//
// Outputs:
//     A       -   the result of factorization, matrices L and U stored in
//                 compact form using CRS sparse storage format:
//                 * lower unitriangular L is stored strictly under main diagonal
//                 * upper triangilar U is stored ON and ABOVE main diagonal
//     P       -   row permutation matrix in compact form, array[N]
//     Q       -   col permutation matrix in compact form, array[N]
//
// This function always succeeds, i.e. it ALWAYS returns valid factorization,
// but for your convenience it also returns  boolean  value  which  helps  to
// detect symbolically degenerate matrices:
// * function returns TRUE, if the matrix was factorized AND symbolically
//   non-degenerate
// * function returns FALSE, if the matrix was factorized but U has strictly
//   zero elements at the diagonal (the factorization is returned anyway).
//
//
// ALGLIB Routine: Copyright 03.09.2018 by Sergey Bochkanov
bool sparselu(const sparsematrix &a, const ae_int_t pivottype, integer_1d_array &p, integer_1d_array &q);

// Sparse Cholesky decomposition for skyline matrixm using in-place algorithm
// without allocating additional storage.
//
// The algorithm computes Cholesky decomposition  of  a  symmetric  positive-
// definite sparse matrix. The result of an algorithm is a representation  of
// A as A=U^T*U or A=L*L^T
//
// This  function  is  a  more  efficient alternative to general, but  slower
// SparseCholeskyX(), because it does not  create  temporary  copies  of  the
// target. It performs factorization in-place, which gives  best  performance
// on low-profile matrices. Its drawback, however, is that it can not perform
// profile-reducing permutation of input matrix.
//
// Inputs:
//     A       -   sparse matrix in skyline storage (SKS) format.
//     N       -   size of matrix A (can be smaller than actual size of A)
//     IsUpper -   if IsUpper=True, then factorization is performed on  upper
//                 triangle. Another triangle is ignored (it may contant some
//                 data, but it is not changed).
//
//
// Outputs:
//     A       -   the result of factorization, stored in SKS. If IsUpper=True,
//                 then the upper  triangle  contains  matrix  U,  such  that
//                 A = U^T*U. Lower triangle is not changed.
//                 Similarly, if IsUpper = False. In this case L is returned,
//                 and we have A = L*(L^T).
//                 Note that THIS function does not  perform  permutation  of
//                 rows to reduce bandwidth.
//
// Result:
//     If  the  matrix  is  positive-definite,  the  function  returns  True.
//     Otherwise, the function returns False. Contents of A is not determined
//     in such case.
//
// NOTE: for  performance  reasons  this  function  does NOT check that input
//       matrix  includes  only  finite  values. It is your responsibility to
//       make sure that there are no infinite or NAN values in the matrix.
//
// ALGLIB Routine: Copyright 16.01.2014 by Sergey Bochkanov
bool sparsecholeskyskyline(const sparsematrix &a, const ae_int_t n, const bool isupper);
} // end of namespace alglib

// === RCOND Package ===
// Depends on: (AlgLibInternal) TRLINSOLVE, SAFESOLVE
// Depends on: TRFAC
namespace alglib_impl {
double rmatrixrcond1(RMatrix *a, ae_int_t n);
double rmatrixrcondinf(RMatrix *a, ae_int_t n);
double spdmatrixrcond(RMatrix *a, ae_int_t n, bool isupper);
double rmatrixtrrcond1(RMatrix *a, ae_int_t n, bool isupper, bool isunit);
double rmatrixtrrcondinf(RMatrix *a, ae_int_t n, bool isupper, bool isunit);
double hpdmatrixrcond(CMatrix *a, ae_int_t n, bool isupper);
double cmatrixrcond1(CMatrix *a, ae_int_t n);
double cmatrixrcondinf(CMatrix *a, ae_int_t n);
double rmatrixlurcond1(RMatrix *lua, ae_int_t n);
double rmatrixlurcondinf(RMatrix *lua, ae_int_t n);
double spdmatrixcholeskyrcond(RMatrix *a, ae_int_t n, bool isupper);
double hpdmatrixcholeskyrcond(CMatrix *a, ae_int_t n, bool isupper);
double cmatrixlurcond1(CMatrix *lua, ae_int_t n);
double cmatrixlurcondinf(CMatrix *lua, ae_int_t n);
double cmatrixtrrcond1(CMatrix *a, ae_int_t n, bool isupper, bool isunit);
double cmatrixtrrcondinf(CMatrix *a, ae_int_t n, bool isupper, bool isunit);
double rcondthreshold();
} // end of namespace alglib_impl

namespace alglib {
// Estimate of a matrix condition number (1-norm)
//
// The algorithm calculates a lower bound of the condition number. In this case,
// the algorithm does not return a lower bound of the condition number, but an
// inverse number (to avoid an overflow in case of a singular matrix).
//
// Inputs:
//     A   -   matrix. Array whose indexes range within [0..N-1, 0..N-1].
//     N   -   size of matrix A.
//
// Result: 1/LowerBound(cond(A))
//
// NOTE:
//     if k(A) is very large, then matrix is  assumed  degenerate,  k(A)=INF,
//     0.0 is returned in such cases.
double rmatrixrcond1(const real_2d_array &a, const ae_int_t n);

// Estimate of a matrix condition number (infinity-norm).
//
// The algorithm calculates a lower bound of the condition number. In this case,
// the algorithm does not return a lower bound of the condition number, but an
// inverse number (to avoid an overflow in case of a singular matrix).
//
// Inputs:
//     A   -   matrix. Array whose indexes range within [0..N-1, 0..N-1].
//     N   -   size of matrix A.
//
// Result: 1/LowerBound(cond(A))
//
// NOTE:
//     if k(A) is very large, then matrix is  assumed  degenerate,  k(A)=INF,
//     0.0 is returned in such cases.
double rmatrixrcondinf(const real_2d_array &a, const ae_int_t n);

// Condition number estimate of a symmetric positive definite matrix.
//
// The algorithm calculates a lower bound of the condition number. In this case,
// the algorithm does not return a lower bound of the condition number, but an
// inverse number (to avoid an overflow in case of a singular matrix).
//
// It should be noted that 1-norm and inf-norm of condition numbers of symmetric
// matrices are equal, so the algorithm doesn't take into account the
// differences between these types of norms.
//
// Inputs:
//     A       -   symmetric positive definite matrix which is given by its
//                 upper or lower triangle depending on the value of
//                 IsUpper. Array with elements [0..N-1, 0..N-1].
//     N       -   size of matrix A.
//     IsUpper -   storage format.
//
// Result:
//     1/LowerBound(cond(A)), if matrix A is positive definite,
//    -1, if matrix A is not positive definite, and its condition number
//     could not be found by this algorithm.
//
// NOTE:
//     if k(A) is very large, then matrix is  assumed  degenerate,  k(A)=INF,
//     0.0 is returned in such cases.
double spdmatrixrcond(const real_2d_array &a, const ae_int_t n, const bool isupper);

// Triangular matrix: estimate of a condition number (1-norm)
//
// The algorithm calculates a lower bound of the condition number. In this case,
// the algorithm does not return a lower bound of the condition number, but an
// inverse number (to avoid an overflow in case of a singular matrix).
//
// Inputs:
//     A       -   matrix. Array[0..N-1, 0..N-1].
//     N       -   size of A.
//     IsUpper -   True, if the matrix is upper triangular.
//     IsUnit  -   True, if the matrix has a unit diagonal.
//
// Result: 1/LowerBound(cond(A))
//
// NOTE:
//     if k(A) is very large, then matrix is  assumed  degenerate,  k(A)=INF,
//     0.0 is returned in such cases.
double rmatrixtrrcond1(const real_2d_array &a, const ae_int_t n, const bool isupper, const bool isunit);

// Triangular matrix: estimate of a matrix condition number (infinity-norm).
//
// The algorithm calculates a lower bound of the condition number. In this case,
// the algorithm does not return a lower bound of the condition number, but an
// inverse number (to avoid an overflow in case of a singular matrix).
//
// Inputs:
//     A   -   matrix. Array whose indexes range within [0..N-1, 0..N-1].
//     N   -   size of matrix A.
//     IsUpper -   True, if the matrix is upper triangular.
//     IsUnit  -   True, if the matrix has a unit diagonal.
//
// Result: 1/LowerBound(cond(A))
//
// NOTE:
//     if k(A) is very large, then matrix is  assumed  degenerate,  k(A)=INF,
//     0.0 is returned in such cases.
double rmatrixtrrcondinf(const real_2d_array &a, const ae_int_t n, const bool isupper, const bool isunit);

// Condition number estimate of a Hermitian positive definite matrix.
//
// The algorithm calculates a lower bound of the condition number. In this case,
// the algorithm does not return a lower bound of the condition number, but an
// inverse number (to avoid an overflow in case of a singular matrix).
//
// It should be noted that 1-norm and inf-norm of condition numbers of symmetric
// matrices are equal, so the algorithm doesn't take into account the
// differences between these types of norms.
//
// Inputs:
//     A       -   Hermitian positive definite matrix which is given by its
//                 upper or lower triangle depending on the value of
//                 IsUpper. Array with elements [0..N-1, 0..N-1].
//     N       -   size of matrix A.
//     IsUpper -   storage format.
//
// Result:
//     1/LowerBound(cond(A)), if matrix A is positive definite,
//    -1, if matrix A is not positive definite, and its condition number
//     could not be found by this algorithm.
//
// NOTE:
//     if k(A) is very large, then matrix is  assumed  degenerate,  k(A)=INF,
//     0.0 is returned in such cases.
double hpdmatrixrcond(const complex_2d_array &a, const ae_int_t n, const bool isupper);

// Estimate of a matrix condition number (1-norm)
//
// The algorithm calculates a lower bound of the condition number. In this case,
// the algorithm does not return a lower bound of the condition number, but an
// inverse number (to avoid an overflow in case of a singular matrix).
//
// Inputs:
//     A   -   matrix. Array whose indexes range within [0..N-1, 0..N-1].
//     N   -   size of matrix A.
//
// Result: 1/LowerBound(cond(A))
//
// NOTE:
//     if k(A) is very large, then matrix is  assumed  degenerate,  k(A)=INF,
//     0.0 is returned in such cases.
double cmatrixrcond1(const complex_2d_array &a, const ae_int_t n);

// Estimate of a matrix condition number (infinity-norm).
//
// The algorithm calculates a lower bound of the condition number. In this case,
// the algorithm does not return a lower bound of the condition number, but an
// inverse number (to avoid an overflow in case of a singular matrix).
//
// Inputs:
//     A   -   matrix. Array whose indexes range within [0..N-1, 0..N-1].
//     N   -   size of matrix A.
//
// Result: 1/LowerBound(cond(A))
//
// NOTE:
//     if k(A) is very large, then matrix is  assumed  degenerate,  k(A)=INF,
//     0.0 is returned in such cases.
double cmatrixrcondinf(const complex_2d_array &a, const ae_int_t n);

// Estimate of the condition number of a matrix given by its LU decomposition (1-norm)
//
// The algorithm calculates a lower bound of the condition number. In this case,
// the algorithm does not return a lower bound of the condition number, but an
// inverse number (to avoid an overflow in case of a singular matrix).
//
// Inputs:
//     LUA         -   LU decomposition of a matrix in compact form. Output of
//                     the RMatrixLU subroutine.
//     N           -   size of matrix A.
//
// Result: 1/LowerBound(cond(A))
//
// NOTE:
//     if k(A) is very large, then matrix is  assumed  degenerate,  k(A)=INF,
//     0.0 is returned in such cases.
double rmatrixlurcond1(const real_2d_array &lua, const ae_int_t n);

// Estimate of the condition number of a matrix given by its LU decomposition
// (infinity norm).
//
// The algorithm calculates a lower bound of the condition number. In this case,
// the algorithm does not return a lower bound of the condition number, but an
// inverse number (to avoid an overflow in case of a singular matrix).
//
// Inputs:
//     LUA     -   LU decomposition of a matrix in compact form. Output of
//                 the RMatrixLU subroutine.
//     N       -   size of matrix A.
//
// Result: 1/LowerBound(cond(A))
//
// NOTE:
//     if k(A) is very large, then matrix is  assumed  degenerate,  k(A)=INF,
//     0.0 is returned in such cases.
double rmatrixlurcondinf(const real_2d_array &lua, const ae_int_t n);

// Condition number estimate of a symmetric positive definite matrix given by
// Cholesky decomposition.
//
// The algorithm calculates a lower bound of the condition number. In this
// case, the algorithm does not return a lower bound of the condition number,
// but an inverse number (to avoid an overflow in case of a singular matrix).
//
// It should be noted that 1-norm and inf-norm condition numbers of symmetric
// matrices are equal, so the algorithm doesn't take into account the
// differences between these types of norms.
//
// Inputs:
//     CD  - Cholesky decomposition of matrix A,
//           output of SMatrixCholesky subroutine.
//     N   - size of matrix A.
//
// Result: 1/LowerBound(cond(A))
//
// NOTE:
//     if k(A) is very large, then matrix is  assumed  degenerate,  k(A)=INF,
//     0.0 is returned in such cases.
double spdmatrixcholeskyrcond(const real_2d_array &a, const ae_int_t n, const bool isupper);

// Condition number estimate of a Hermitian positive definite matrix given by
// Cholesky decomposition.
//
// The algorithm calculates a lower bound of the condition number. In this
// case, the algorithm does not return a lower bound of the condition number,
// but an inverse number (to avoid an overflow in case of a singular matrix).
//
// It should be noted that 1-norm and inf-norm condition numbers of symmetric
// matrices are equal, so the algorithm doesn't take into account the
// differences between these types of norms.
//
// Inputs:
//     CD  - Cholesky decomposition of matrix A,
//           output of SMatrixCholesky subroutine.
//     N   - size of matrix A.
//
// Result: 1/LowerBound(cond(A))
//
// NOTE:
//     if k(A) is very large, then matrix is  assumed  degenerate,  k(A)=INF,
//     0.0 is returned in such cases.
double hpdmatrixcholeskyrcond(const complex_2d_array &a, const ae_int_t n, const bool isupper);

// Estimate of the condition number of a matrix given by its LU decomposition (1-norm)
//
// The algorithm calculates a lower bound of the condition number. In this case,
// the algorithm does not return a lower bound of the condition number, but an
// inverse number (to avoid an overflow in case of a singular matrix).
//
// Inputs:
//     LUA         -   LU decomposition of a matrix in compact form. Output of
//                     the CMatrixLU subroutine.
//     N           -   size of matrix A.
//
// Result: 1/LowerBound(cond(A))
//
// NOTE:
//     if k(A) is very large, then matrix is  assumed  degenerate,  k(A)=INF,
//     0.0 is returned in such cases.
double cmatrixlurcond1(const complex_2d_array &lua, const ae_int_t n);

// Estimate of the condition number of a matrix given by its LU decomposition
// (infinity norm).
//
// The algorithm calculates a lower bound of the condition number. In this case,
// the algorithm does not return a lower bound of the condition number, but an
// inverse number (to avoid an overflow in case of a singular matrix).
//
// Inputs:
//     LUA     -   LU decomposition of a matrix in compact form. Output of
//                 the CMatrixLU subroutine.
//     N       -   size of matrix A.
//
// Result: 1/LowerBound(cond(A))
//
// NOTE:
//     if k(A) is very large, then matrix is  assumed  degenerate,  k(A)=INF,
//     0.0 is returned in such cases.
double cmatrixlurcondinf(const complex_2d_array &lua, const ae_int_t n);

// Triangular matrix: estimate of a condition number (1-norm)
//
// The algorithm calculates a lower bound of the condition number. In this case,
// the algorithm does not return a lower bound of the condition number, but an
// inverse number (to avoid an overflow in case of a singular matrix).
//
// Inputs:
//     A       -   matrix. Array[0..N-1, 0..N-1].
//     N       -   size of A.
//     IsUpper -   True, if the matrix is upper triangular.
//     IsUnit  -   True, if the matrix has a unit diagonal.
//
// Result: 1/LowerBound(cond(A))
//
// NOTE:
//     if k(A) is very large, then matrix is  assumed  degenerate,  k(A)=INF,
//     0.0 is returned in such cases.
double cmatrixtrrcond1(const complex_2d_array &a, const ae_int_t n, const bool isupper, const bool isunit);

// Triangular matrix: estimate of a matrix condition number (infinity-norm).
//
// The algorithm calculates a lower bound of the condition number. In this case,
// the algorithm does not return a lower bound of the condition number, but an
// inverse number (to avoid an overflow in case of a singular matrix).
//
// Inputs:
//     A   -   matrix. Array whose indexes range within [0..N-1, 0..N-1].
//     N   -   size of matrix A.
//     IsUpper -   True, if the matrix is upper triangular.
//     IsUnit  -   True, if the matrix has a unit diagonal.
//
// Result: 1/LowerBound(cond(A))
//
// NOTE:
//     if k(A) is very large, then matrix is  assumed  degenerate,  k(A)=INF,
//     0.0 is returned in such cases.
double cmatrixtrrcondinf(const complex_2d_array &a, const ae_int_t n, const bool isupper, const bool isunit);
} // end of namespace alglib

// === MATINV Package ===
// Depends on: RCOND
namespace alglib_impl {
struct matinvreport {
   double r1;
   double rinf;
};
void matinvreport_init(void *_p, bool make_automatic);
void matinvreport_copy(void *_dst, void *_src, bool make_automatic);
void matinvreport_free(void *_p, bool make_automatic);

void rmatrixluinverse(RMatrix *a, ZVector *pivots, ae_int_t n, ae_int_t *info, matinvreport *rep);
void rmatrixinverse(RMatrix *a, ae_int_t n, ae_int_t *info, matinvreport *rep);
void cmatrixluinverse(CMatrix *a, ZVector *pivots, ae_int_t n, ae_int_t *info, matinvreport *rep);
void cmatrixinverse(CMatrix *a, ae_int_t n, ae_int_t *info, matinvreport *rep);
void spdmatrixcholeskyinverse(RMatrix *a, ae_int_t n, bool isupper, ae_int_t *info, matinvreport *rep);
void spdmatrixinverse(RMatrix *a, ae_int_t n, bool isupper, ae_int_t *info, matinvreport *rep);
void hpdmatrixcholeskyinverse(CMatrix *a, ae_int_t n, bool isupper, ae_int_t *info, matinvreport *rep);
void hpdmatrixinverse(CMatrix *a, ae_int_t n, bool isupper, ae_int_t *info, matinvreport *rep);
void rmatrixtrinverse(RMatrix *a, ae_int_t n, bool isupper, bool isunit, ae_int_t *info, matinvreport *rep);
void cmatrixtrinverse(CMatrix *a, ae_int_t n, bool isupper, bool isunit, ae_int_t *info, matinvreport *rep);
void spdmatrixcholeskyinverserec(RMatrix *a, ae_int_t offs, ae_int_t n, bool isupper, RVector *tmp);
} // end of namespace alglib_impl

namespace alglib {
// Matrix inverse report:
// * R1    reciprocal of condition number in 1-norm
// * RInf  reciprocal of condition number in inf-norm
DecClass(matinvreport, double &r1; double &rinf;);

// Inversion of a matrix given by its LU decomposition.
//
// Inputs:
//     A       -   LU decomposition of the matrix
//                 (output of RMatrixLU subroutine).
//     Pivots  -   table of permutations
//                 (the output of RMatrixLU subroutine).
//     N       -   size of matrix A (optional) :
//                 * if given, only principal NxN submatrix is processed  and
//                   overwritten. other elements are unchanged.
//                 * if not given,  size  is  automatically  determined  from
//                   matrix size (A must be square matrix)
//
// Outputs:
//     Info    -   return code:
//                 * -3    A is singular, or VERY close to singular.
//                         it is filled by zeros in such cases.
//                 *  1    task is solved (but matrix A may be ill-conditioned,
//                         check R1/RInf parameters for condition numbers).
//     Rep     -   solver report, see below for more info
//     A       -   inverse of matrix A.
//                 Array whose indexes range within [0..N-1, 0..N-1].
//
// SOLVER REPORT
//
// Subroutine sets following fields of the Rep structure:
// * R1        reciprocal of condition number: 1/cond(A), 1-norm.
// * RInf      reciprocal of condition number: 1/cond(A), inf-norm.
//
// ALGLIB Routine: Copyright 05.02.2010 by Sergey Bochkanov
void rmatrixluinverse(real_2d_array &a, const integer_1d_array &pivots, const ae_int_t n, ae_int_t &info, matinvreport &rep);
void rmatrixluinverse(real_2d_array &a, const integer_1d_array &pivots, ae_int_t &info, matinvreport &rep);

// Inversion of a general matrix.
//
// Inputs:
//     A       -   matrix.
//     N       -   size of matrix A (optional) :
//                 * if given, only principal NxN submatrix is processed  and
//                   overwritten. other elements are unchanged.
//                 * if not given,  size  is  automatically  determined  from
//                   matrix size (A must be square matrix)
//
// Outputs:
//     Info    -   return code, same as in RMatrixLUInverse
//     Rep     -   solver report, same as in RMatrixLUInverse
//     A       -   inverse of matrix A, same as in RMatrixLUInverse
//
// Result:
//     True, if the matrix is not singular.
//     False, if the matrix is singular.
// ALGLIB: Copyright 2005-2010 by Sergey Bochkanov
void rmatrixinverse(real_2d_array &a, const ae_int_t n, ae_int_t &info, matinvreport &rep);
void rmatrixinverse(real_2d_array &a, ae_int_t &info, matinvreport &rep);

// Inversion of a matrix given by its LU decomposition.
//
// Inputs:
//     A       -   LU decomposition of the matrix
//                 (output of CMatrixLU subroutine).
//     Pivots  -   table of permutations
//                 (the output of CMatrixLU subroutine).
//     N       -   size of matrix A (optional) :
//                 * if given, only principal NxN submatrix is processed  and
//                   overwritten. other elements are unchanged.
//                 * if not given,  size  is  automatically  determined  from
//                   matrix size (A must be square matrix)
//
// Outputs:
//     Info    -   return code, same as in RMatrixLUInverse
//     Rep     -   solver report, same as in RMatrixLUInverse
//     A       -   inverse of matrix A, same as in RMatrixLUInverse
//
// ALGLIB Routine: Copyright 05.02.2010 by Sergey Bochkanov
void cmatrixluinverse(complex_2d_array &a, const integer_1d_array &pivots, const ae_int_t n, ae_int_t &info, matinvreport &rep);
void cmatrixluinverse(complex_2d_array &a, const integer_1d_array &pivots, ae_int_t &info, matinvreport &rep);

// Inversion of a general matrix.
//
// Inputs:
//     A       -   matrix
//     N       -   size of matrix A (optional) :
//                 * if given, only principal NxN submatrix is processed  and
//                   overwritten. other elements are unchanged.
//                 * if not given,  size  is  automatically  determined  from
//                   matrix size (A must be square matrix)
//
// Outputs:
//     Info    -   return code, same as in RMatrixLUInverse
//     Rep     -   solver report, same as in RMatrixLUInverse
//     A       -   inverse of matrix A, same as in RMatrixLUInverse
// ALGLIB: Copyright 2005 by Sergey Bochkanov
void cmatrixinverse(complex_2d_array &a, const ae_int_t n, ae_int_t &info, matinvreport &rep);
void cmatrixinverse(complex_2d_array &a, ae_int_t &info, matinvreport &rep);

// Inversion of a symmetric positive definite matrix which is given
// by Cholesky decomposition.
//
// Inputs:
//     A       -   Cholesky decomposition of the matrix to be inverted:
//                 A=U'*U or A = L*L'.
//                 Output of  SPDMatrixCholesky subroutine.
//     N       -   size of matrix A (optional) :
//                 * if given, only principal NxN submatrix is processed  and
//                   overwritten. other elements are unchanged.
//                 * if not given,  size  is  automatically  determined  from
//                   matrix size (A must be square matrix)
//     IsUpper -   storage type (optional):
//                 * if True, symmetric  matrix  A  is  given  by  its  upper
//                   triangle, and the lower triangle isn't  used/changed  by
//                   function
//                 * if False,  symmetric matrix  A  is  given  by  its lower
//                   triangle, and the  upper triangle isn't used/changed  by
//                   function
//                 * if not given, lower half is used.
//
// Outputs:
//     Info    -   return code, same as in RMatrixLUInverse
//     Rep     -   solver report, same as in RMatrixLUInverse
//     A       -   inverse of matrix A, same as in RMatrixLUInverse
//
// ALGLIB Routine: Copyright 10.02.2010 by Sergey Bochkanov
void spdmatrixcholeskyinverse(real_2d_array &a, const ae_int_t n, const bool isupper, ae_int_t &info, matinvreport &rep);
void spdmatrixcholeskyinverse(real_2d_array &a, ae_int_t &info, matinvreport &rep);

// Inversion of a symmetric positive definite matrix.
//
// Given an upper or lower triangle of a symmetric positive definite matrix,
// the algorithm generates matrix A^-1 and saves the upper or lower triangle
// depending on the input.
//
// Inputs:
//     A       -   matrix to be inverted (upper or lower triangle).
//                 Array with elements [0..N-1,0..N-1].
//     N       -   size of matrix A (optional) :
//                 * if given, only principal NxN submatrix is processed  and
//                   overwritten. other elements are unchanged.
//                 * if not given,  size  is  automatically  determined  from
//                   matrix size (A must be square matrix)
//     IsUpper -   storage type (optional):
//                 * if True, symmetric  matrix  A  is  given  by  its  upper
//                   triangle, and the lower triangle isn't  used/changed  by
//                   function
//                 * if False,  symmetric matrix  A  is  given  by  its lower
//                   triangle, and the  upper triangle isn't used/changed  by
//                   function
//                 * if not given,  both lower and upper  triangles  must  be
//                   filled.
//
// Outputs:
//     Info    -   return code, same as in RMatrixLUInverse
//     Rep     -   solver report, same as in RMatrixLUInverse
//     A       -   inverse of matrix A, same as in RMatrixLUInverse
//
// ALGLIB Routine: Copyright 10.02.2010 by Sergey Bochkanov
void spdmatrixinverse(real_2d_array &a, const ae_int_t n, const bool isupper, ae_int_t &info, matinvreport &rep);
void spdmatrixinverse(real_2d_array &a, ae_int_t &info, matinvreport &rep);

// Inversion of a Hermitian positive definite matrix which is given
// by Cholesky decomposition.
//
// Inputs:
//     A       -   Cholesky decomposition of the matrix to be inverted:
//                 A=U'*U or A = L*L'.
//                 Output of  HPDMatrixCholesky subroutine.
//     N       -   size of matrix A (optional) :
//                 * if given, only principal NxN submatrix is processed  and
//                   overwritten. other elements are unchanged.
//                 * if not given,  size  is  automatically  determined  from
//                   matrix size (A must be square matrix)
//     IsUpper -   storage type (optional):
//                 * if True, symmetric  matrix  A  is  given  by  its  upper
//                   triangle, and the lower triangle isn't  used/changed  by
//                   function
//                 * if False,  symmetric matrix  A  is  given  by  its lower
//                   triangle, and the  upper triangle isn't used/changed  by
//                   function
//                 * if not given, lower half is used.
//
// Outputs:
//     Info    -   return code, same as in RMatrixLUInverse
//     Rep     -   solver report, same as in RMatrixLUInverse
//     A       -   inverse of matrix A, same as in RMatrixLUInverse
//
// ALGLIB Routine: Copyright 10.02.2010 by Sergey Bochkanov
void hpdmatrixcholeskyinverse(complex_2d_array &a, const ae_int_t n, const bool isupper, ae_int_t &info, matinvreport &rep);
void hpdmatrixcholeskyinverse(complex_2d_array &a, ae_int_t &info, matinvreport &rep);

// Inversion of a Hermitian positive definite matrix.
//
// Given an upper or lower triangle of a Hermitian positive definite matrix,
// the algorithm generates matrix A^-1 and saves the upper or lower triangle
// depending on the input.
//
// Inputs:
//     A       -   matrix to be inverted (upper or lower triangle).
//                 Array with elements [0..N-1,0..N-1].
//     N       -   size of matrix A (optional) :
//                 * if given, only principal NxN submatrix is processed  and
//                   overwritten. other elements are unchanged.
//                 * if not given,  size  is  automatically  determined  from
//                   matrix size (A must be square matrix)
//     IsUpper -   storage type (optional):
//                 * if True, symmetric  matrix  A  is  given  by  its  upper
//                   triangle, and the lower triangle isn't  used/changed  by
//                   function
//                 * if False,  symmetric matrix  A  is  given  by  its lower
//                   triangle, and the  upper triangle isn't used/changed  by
//                   function
//                 * if not given,  both lower and upper  triangles  must  be
//                   filled.
//
// Outputs:
//     Info    -   return code, same as in RMatrixLUInverse
//     Rep     -   solver report, same as in RMatrixLUInverse
//     A       -   inverse of matrix A, same as in RMatrixLUInverse
//
// ALGLIB Routine: Copyright 10.02.2010 by Sergey Bochkanov
void hpdmatrixinverse(complex_2d_array &a, const ae_int_t n, const bool isupper, ae_int_t &info, matinvreport &rep);
void hpdmatrixinverse(complex_2d_array &a, ae_int_t &info, matinvreport &rep);

// Triangular matrix inverse (real)
//
// The subroutine inverts the following types of matrices:
//     * upper triangular
//     * upper triangular with unit diagonal
//     * lower triangular
//     * lower triangular with unit diagonal
//
// In case of an upper (lower) triangular matrix,  the  inverse  matrix  will
// also be upper (lower) triangular, and after the end of the algorithm,  the
// inverse matrix replaces the source matrix. The elements  below (above) the
// main diagonal are not changed by the algorithm.
//
// If  the matrix  has a unit diagonal, the inverse matrix also  has  a  unit
// diagonal, and the diagonal elements are not passed to the algorithm.
//
// Inputs:
//     A       -   matrix, array[0..N-1, 0..N-1].
//     N       -   size of matrix A (optional) :
//                 * if given, only principal NxN submatrix is processed  and
//                   overwritten. other elements are unchanged.
//                 * if not given,  size  is  automatically  determined  from
//                   matrix size (A must be square matrix)
//     IsUpper -   True, if the matrix is upper triangular.
//     IsUnit  -   diagonal type (optional):
//                 * if True, matrix has unit diagonal (a[i,i] are NOT used)
//                 * if False, matrix diagonal is arbitrary
//                 * if not given, False is assumed
//
// Outputs:
//     Info    -   same as for RMatrixLUInverse
//     Rep     -   same as for RMatrixLUInverse
//     A       -   same as for RMatrixLUInverse.
// ALGLIB: Copyright 05.02.2010 by Sergey Bochkanov
void rmatrixtrinverse(real_2d_array &a, const ae_int_t n, const bool isupper, const bool isunit, ae_int_t &info, matinvreport &rep);
void rmatrixtrinverse(real_2d_array &a, const bool isupper, ae_int_t &info, matinvreport &rep);

// Triangular matrix inverse (complex)
//
// The subroutine inverts the following types of matrices:
//     * upper triangular
//     * upper triangular with unit diagonal
//     * lower triangular
//     * lower triangular with unit diagonal
//
// In case of an upper (lower) triangular matrix,  the  inverse  matrix  will
// also be upper (lower) triangular, and after the end of the algorithm,  the
// inverse matrix replaces the source matrix. The elements  below (above) the
// main diagonal are not changed by the algorithm.
//
// If  the matrix  has a unit diagonal, the inverse matrix also  has  a  unit
// diagonal, and the diagonal elements are not passed to the algorithm.
//
// Inputs:
//     A       -   matrix, array[0..N-1, 0..N-1].
//     N       -   size of matrix A (optional) :
//                 * if given, only principal NxN submatrix is processed  and
//                   overwritten. other elements are unchanged.
//                 * if not given,  size  is  automatically  determined  from
//                   matrix size (A must be square matrix)
//     IsUpper -   True, if the matrix is upper triangular.
//     IsUnit  -   diagonal type (optional):
//                 * if True, matrix has unit diagonal (a[i,i] are NOT used)
//                 * if False, matrix diagonal is arbitrary
//                 * if not given, False is assumed
//
// Outputs:
//     Info    -   same as for RMatrixLUInverse
//     Rep     -   same as for RMatrixLUInverse
//     A       -   same as for RMatrixLUInverse.
// ALGLIB: Copyright 05.02.2010 by Sergey Bochkanov
void cmatrixtrinverse(complex_2d_array &a, const ae_int_t n, const bool isupper, const bool isunit, ae_int_t &info, matinvreport &rep);
void cmatrixtrinverse(complex_2d_array &a, const bool isupper, ae_int_t &info, matinvreport &rep);
} // end of namespace alglib

// === ORTFAC Package ===
// Depends on: (AlgLibInternal) CREFLECTIONS, HBLAS, SBLAS
// Depends on: (AlgLibMisc) HQRND
// Depends on: ABLAS
namespace alglib_impl {
void rmatrixqr(RMatrix *a, ae_int_t m, ae_int_t n, RVector *tau);
void rmatrixlq(RMatrix *a, ae_int_t m, ae_int_t n, RVector *tau);
void cmatrixqr(CMatrix *a, ae_int_t m, ae_int_t n, CVector *tau);
void cmatrixlq(CMatrix *a, ae_int_t m, ae_int_t n, CVector *tau);
void rmatrixqrunpackq(RMatrix *a, ae_int_t m, ae_int_t n, RVector *tau, ae_int_t qcolumns, RMatrix *q);
void rmatrixqrunpackr(RMatrix *a, ae_int_t m, ae_int_t n, RMatrix *r);
void rmatrixlqunpackq(RMatrix *a, ae_int_t m, ae_int_t n, RVector *tau, ae_int_t qrows, RMatrix *q);
void rmatrixlqunpackl(RMatrix *a, ae_int_t m, ae_int_t n, RMatrix *l);
void cmatrixqrunpackq(CMatrix *a, ae_int_t m, ae_int_t n, CVector *tau, ae_int_t qcolumns, CMatrix *q);
void cmatrixqrunpackr(CMatrix *a, ae_int_t m, ae_int_t n, CMatrix *r);
void cmatrixlqunpackq(CMatrix *a, ae_int_t m, ae_int_t n, CVector *tau, ae_int_t qrows, CMatrix *q);
void cmatrixlqunpackl(CMatrix *a, ae_int_t m, ae_int_t n, CMatrix *l);
void rmatrixqrbasecase(RMatrix *a, ae_int_t m, ae_int_t n, RVector *work, RVector *t, RVector *tau);
void rmatrixlqbasecase(RMatrix *a, ae_int_t m, ae_int_t n, RVector *work, RVector *t, RVector *tau);
void rmatrixbd(RMatrix *a, ae_int_t m, ae_int_t n, RVector *tauq, RVector *taup);
void rmatrixbdunpackq(RMatrix *qp, ae_int_t m, ae_int_t n, RVector *tauq, ae_int_t qcolumns, RMatrix *q);
void rmatrixbdmultiplybyq(RMatrix *qp, ae_int_t m, ae_int_t n, RVector *tauq, RMatrix *z, ae_int_t zrows, ae_int_t zcolumns, bool fromtheright, bool dotranspose);
void rmatrixbdunpackpt(RMatrix *qp, ae_int_t m, ae_int_t n, RVector *taup, ae_int_t ptrows, RMatrix *pt);
void rmatrixbdmultiplybyp(RMatrix *qp, ae_int_t m, ae_int_t n, RVector *taup, RMatrix *z, ae_int_t zrows, ae_int_t zcolumns, bool fromtheright, bool dotranspose);
void rmatrixbdunpackdiagonals(RMatrix *b, ae_int_t m, ae_int_t n, bool *isupper, RVector *d, RVector *e);
void rmatrixhessenberg(RMatrix *a, ae_int_t n, RVector *tau);
void rmatrixhessenbergunpackq(RMatrix *a, ae_int_t n, RVector *tau, RMatrix *q);
void rmatrixhessenbergunpackh(RMatrix *a, ae_int_t n, RMatrix *h);
void smatrixtd(RMatrix *a, ae_int_t n, bool isupper, RVector *tau, RVector *d, RVector *e);
void smatrixtdunpackq(RMatrix *a, ae_int_t n, bool isupper, RVector *tau, RMatrix *q);
void hmatrixtd(CMatrix *a, ae_int_t n, bool isupper, CVector *tau, RVector *d, RVector *e);
void hmatrixtdunpackq(CMatrix *a, ae_int_t n, bool isupper, CVector *tau, CMatrix *q);
} // end of namespace alglib_impl

namespace alglib {
// QR decomposition of a rectangular matrix of size MxN
//
// Inputs:
//     A   -   matrix A whose indexes range within [0..M-1, 0..N-1].
//     M   -   number of rows in matrix A.
//     N   -   number of columns in matrix A.
//
// Outputs:
//     A   -   matrices Q and R in compact form (see below).
//     Tau -   array of scalar factors which are used to form
//             matrix Q. Array whose index ranges within [0.. Min(M-1,N-1)].
//
// Matrix A is represented as A = QR, where Q is an orthogonal matrix of size
// MxM, R - upper triangular (or upper trapezoid) matrix of size M x N.
//
// The elements of matrix R are located on and above the main diagonal of
// matrix A. The elements which are located in Tau array and below the main
// diagonal of matrix A are used to form matrix Q as follows:
//
// Matrix Q is represented as a product of elementary reflections
//
// Q = H(0)*H(2)*...*H(k-1),
//
// where k = min(m,n), and each H(i) is in the form
//
// H(i) = 1 - tau * v * (v^T)
//
// where tau is a scalar stored in Tau[I]; v - real vector,
// so that v(0:i-1) = 0, v(i) = 1, v(i+1:m-1) stored in A(i+1:m-1,i).
//
// ALGLIB Routine: Copyright 17.02.2010 by Sergey Bochkanov
void rmatrixqr(real_2d_array &a, const ae_int_t m, const ae_int_t n, real_1d_array &tau);

// LQ decomposition of a rectangular matrix of size MxN
//
// Inputs:
//     A   -   matrix A whose indexes range within [0..M-1, 0..N-1].
//     M   -   number of rows in matrix A.
//     N   -   number of columns in matrix A.
//
// Outputs:
//     A   -   matrices L and Q in compact form (see below)
//     Tau -   array of scalar factors which are used to form
//             matrix Q. Array whose index ranges within [0..Min(M,N)-1].
//
// Matrix A is represented as A = LQ, where Q is an orthogonal matrix of size
// MxM, L - lower triangular (or lower trapezoid) matrix of size M x N.
//
// The elements of matrix L are located on and below  the  main  diagonal  of
// matrix A. The elements which are located in Tau array and above  the  main
// diagonal of matrix A are used to form matrix Q as follows:
//
// Matrix Q is represented as a product of elementary reflections
//
// Q = H(k-1)*H(k-2)*...*H(1)*H(0),
//
// where k = min(m,n), and each H(i) is of the form
//
// H(i) = 1 - tau * v * (v^T)
//
// where tau is a scalar stored in Tau[I]; v - real vector, so that v(0:i-1)=0,
// v(i) = 1, v(i+1:n-1) stored in A(i,i+1:n-1).
//
// ALGLIB Routine: Copyright 17.02.2010 by Sergey Bochkanov
void rmatrixlq(real_2d_array &a, const ae_int_t m, const ae_int_t n, real_1d_array &tau);

// QR decomposition of a rectangular complex matrix of size MxN
//
// Inputs:
//     A   -   matrix A whose indexes range within [0..M-1, 0..N-1]
//     M   -   number of rows in matrix A.
//     N   -   number of columns in matrix A.
//
// Outputs:
//     A   -   matrices Q and R in compact form
//     Tau -   array of scalar factors which are used to form matrix Q. Array
//             whose indexes range within [0.. Min(M,N)-1]
//
// Matrix A is represented as A = QR, where Q is an orthogonal matrix of size
// MxM, R - upper triangular (or upper trapezoid) matrix of size MxN.
//
//   -- LAPACK routine (version 3.0) --
//      Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd.,
//      Courant Institute, Argonne National Lab, and Rice University
//      September 30, 1994
void cmatrixqr(complex_2d_array &a, const ae_int_t m, const ae_int_t n, complex_1d_array &tau);

// LQ decomposition of a rectangular complex matrix of size MxN
//
// Inputs:
//     A   -   matrix A whose indexes range within [0..M-1, 0..N-1]
//     M   -   number of rows in matrix A.
//     N   -   number of columns in matrix A.
//
// Outputs:
//     A   -   matrices Q and L in compact form
//     Tau -   array of scalar factors which are used to form matrix Q. Array
//             whose indexes range within [0.. Min(M,N)-1]
//
// Matrix A is represented as A = LQ, where Q is an orthogonal matrix of size
// MxM, L - lower triangular (or lower trapezoid) matrix of size MxN.
//
//   -- LAPACK routine (version 3.0) --
//      Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd.,
//      Courant Institute, Argonne National Lab, and Rice University
//      September 30, 1994
void cmatrixlq(complex_2d_array &a, const ae_int_t m, const ae_int_t n, complex_1d_array &tau);

// Partial unpacking of matrix Q from the QR decomposition of a matrix A
//
// Inputs:
//     A       -   matrices Q and R in compact form.
//                 Output of RMatrixQR subroutine.
//     M       -   number of rows in given matrix A. M >= 0.
//     N       -   number of columns in given matrix A. N >= 0.
//     Tau     -   scalar factors which are used to form Q.
//                 Output of the RMatrixQR subroutine.
//     QColumns -  required number of columns of matrix Q. M >= QColumns >= 0.
//
// Outputs:
//     Q       -   first QColumns columns of matrix Q.
//                 Array whose indexes range within [0..M-1, 0..QColumns-1].
//                 If QColumns=0, the array remains unchanged.
//
// ALGLIB Routine: Copyright 17.02.2010 by Sergey Bochkanov
void rmatrixqrunpackq(const real_2d_array &a, const ae_int_t m, const ae_int_t n, const real_1d_array &tau, const ae_int_t qcolumns, real_2d_array &q);

// Unpacking of matrix R from the QR decomposition of a matrix A
//
// Inputs:
//     A       -   matrices Q and R in compact form.
//                 Output of RMatrixQR subroutine.
//     M       -   number of rows in given matrix A. M >= 0.
//     N       -   number of columns in given matrix A. N >= 0.
//
// Outputs:
//     R       -   matrix R, array[0..M-1, 0..N-1].
//
// ALGLIB Routine: Copyright 17.02.2010 by Sergey Bochkanov
void rmatrixqrunpackr(const real_2d_array &a, const ae_int_t m, const ae_int_t n, real_2d_array &r);

// Partial unpacking of matrix Q from the LQ decomposition of a matrix A
//
// Inputs:
//     A       -   matrices L and Q in compact form.
//                 Output of RMatrixLQ subroutine.
//     M       -   number of rows in given matrix A. M >= 0.
//     N       -   number of columns in given matrix A. N >= 0.
//     Tau     -   scalar factors which are used to form Q.
//                 Output of the RMatrixLQ subroutine.
//     QRows   -   required number of rows in matrix Q. N >= QRows >= 0.
//
// Outputs:
//     Q       -   first QRows rows of matrix Q. Array whose indexes range
//                 within [0..QRows-1, 0..N-1]. If QRows=0, the array remains
//                 unchanged.
//
// ALGLIB Routine: Copyright 17.02.2010 by Sergey Bochkanov
void rmatrixlqunpackq(const real_2d_array &a, const ae_int_t m, const ae_int_t n, const real_1d_array &tau, const ae_int_t qrows, real_2d_array &q);

// Unpacking of matrix L from the LQ decomposition of a matrix A
//
// Inputs:
//     A       -   matrices Q and L in compact form.
//                 Output of RMatrixLQ subroutine.
//     M       -   number of rows in given matrix A. M >= 0.
//     N       -   number of columns in given matrix A. N >= 0.
//
// Outputs:
//     L       -   matrix L, array[0..M-1, 0..N-1].
//
// ALGLIB Routine: Copyright 17.02.2010 by Sergey Bochkanov
void rmatrixlqunpackl(const real_2d_array &a, const ae_int_t m, const ae_int_t n, real_2d_array &l);

// Partial unpacking of matrix Q from QR decomposition of a complex matrix A.
//
// Inputs:
//     A           -   matrices Q and R in compact form.
//                     Output of CMatrixQR subroutine .
//     M           -   number of rows in matrix A. M >= 0.
//     N           -   number of columns in matrix A. N >= 0.
//     Tau         -   scalar factors which are used to form Q.
//                     Output of CMatrixQR subroutine .
//     QColumns    -   required number of columns in matrix Q. M >= QColumns >= 0.
//
// Outputs:
//     Q           -   first QColumns columns of matrix Q.
//                     Array whose index ranges within [0..M-1, 0..QColumns-1].
//                     If QColumns=0, array isn't changed.
//
// ALGLIB Routine: Copyright 17.02.2010 by Sergey Bochkanov
void cmatrixqrunpackq(const complex_2d_array &a, const ae_int_t m, const ae_int_t n, const complex_1d_array &tau, const ae_int_t qcolumns, complex_2d_array &q);

// Unpacking of matrix R from the QR decomposition of a matrix A
//
// Inputs:
//     A       -   matrices Q and R in compact form.
//                 Output of CMatrixQR subroutine.
//     M       -   number of rows in given matrix A. M >= 0.
//     N       -   number of columns in given matrix A. N >= 0.
//
// Outputs:
//     R       -   matrix R, array[0..M-1, 0..N-1].
//
// ALGLIB Routine: Copyright 17.02.2010 by Sergey Bochkanov
void cmatrixqrunpackr(const complex_2d_array &a, const ae_int_t m, const ae_int_t n, complex_2d_array &r);

// Partial unpacking of matrix Q from LQ decomposition of a complex matrix A.
//
// Inputs:
//     A           -   matrices Q and R in compact form.
//                     Output of CMatrixLQ subroutine .
//     M           -   number of rows in matrix A. M >= 0.
//     N           -   number of columns in matrix A. N >= 0.
//     Tau         -   scalar factors which are used to form Q.
//                     Output of CMatrixLQ subroutine .
//     QRows       -   required number of rows in matrix Q. N >= QColumns >= 0.
//
// Outputs:
//     Q           -   first QRows rows of matrix Q.
//                     Array whose index ranges within [0..QRows-1, 0..N-1].
//                     If QRows=0, array isn't changed.
//
// ALGLIB Routine: Copyright 17.02.2010 by Sergey Bochkanov
void cmatrixlqunpackq(const complex_2d_array &a, const ae_int_t m, const ae_int_t n, const complex_1d_array &tau, const ae_int_t qrows, complex_2d_array &q);

// Unpacking of matrix L from the LQ decomposition of a matrix A
//
// Inputs:
//     A       -   matrices Q and L in compact form.
//                 Output of CMatrixLQ subroutine.
//     M       -   number of rows in given matrix A. M >= 0.
//     N       -   number of columns in given matrix A. N >= 0.
//
// Outputs:
//     L       -   matrix L, array[0..M-1, 0..N-1].
//
// ALGLIB Routine: Copyright 17.02.2010 by Sergey Bochkanov
void cmatrixlqunpackl(const complex_2d_array &a, const ae_int_t m, const ae_int_t n, complex_2d_array &l);

// Reduction of a rectangular matrix to  bidiagonal form
//
// The algorithm reduces the rectangular matrix A to  bidiagonal form by
// orthogonal transformations P and Q: A = Q*B*(P^T).
//
// Inputs:
//     A       -   source matrix. array[0..M-1, 0..N-1]
//     M       -   number of rows in matrix A.
//     N       -   number of columns in matrix A.
//
// Outputs:
//     A       -   matrices Q, B, P in compact form (see below).
//     TauQ    -   scalar factors which are used to form matrix Q.
//     TauP    -   scalar factors which are used to form matrix P.
//
// The main diagonal and one of the  secondary  diagonals  of  matrix  A  are
// replaced with bidiagonal  matrix  B.  Other  elements  contain  elementary
// reflections which form MxM matrix Q and NxN matrix P, respectively.
//
// If M >= N, B is the upper  bidiagonal  MxN  matrix  and  is  stored  in  the
// corresponding  elements  of  matrix  A.  Matrix  Q  is  represented  as  a
// product   of   elementary   reflections   Q = H(0)*H(1)*...*H(n-1),  where
// H(i) = 1-tau*v*v'. Here tau is a scalar which is stored  in  TauQ[i],  and
// vector v has the following  structure:  v(0:i-1)=0, v(i)=1, v(i+1:m-1)  is
// stored   in   elements   A(i+1:m-1,i).   Matrix   P  is  as  follows:  P =
// G(0)*G(1)*...*G(n-2), where G(i) = 1 - tau*u*u'. Tau is stored in TauP[i],
// u(0:i)=0, u(i+1)=1, u(i+2:n-1) is stored in elements A(i,i+2:n-1).
//
// If M < N, B is the  lower  bidiagonal  MxN  matrix  and  is  stored  in  the
// corresponding   elements  of  matrix  A.  Q = H(0)*H(1)*...*H(m-2),  where
// H(i) = 1 - tau*v*v', tau is stored in TauQ, v(0:i)=0, v(i+1)=1, v(i+2:m-1)
// is    stored    in   elements   A(i+2:m-1,i).    P = G(0)*G(1)*...*G(m-1),
// G(i) = 1-tau*u*u', tau is stored in  TauP,  u(0:i-1)=0, u(i)=1, u(i+1:n-1)
// is stored in A(i,i+1:n-1).
//
// EXAMPLE:
//
// m=6, n=5 (m > n):               m=5, n=6 (m < n):
//
// (  d   e   u1  u1  u1 )         (  d   u1  u1  u1  u1  u1 )
// (  v1  d   e   u2  u2 )         (  e   d   u2  u2  u2  u2 )
// (  v1  v2  d   e   u3 )         (  v1  e   d   u3  u3  u3 )
// (  v1  v2  v3  d   e  )         (  v1  v2  e   d   u4  u4 )
// (  v1  v2  v3  v4  d  )         (  v1  v2  v3  e   d   u5 )
// (  v1  v2  v3  v4  v5 )
//
// Here vi and ui are vectors which form H(i) and G(i), and d and e -
// are the diagonal and off-diagonal elements of matrix B.
//
//   -- LAPACK routine (version 3.0) --
//      Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd.,
//      Courant Institute, Argonne National Lab, and Rice University
//      September 30, 1994.
//      Sergey Bochkanov, ALGLIB project, translation from FORTRAN to
//      pseudocode, 2007-2010.
void rmatrixbd(real_2d_array &a, const ae_int_t m, const ae_int_t n, real_1d_array &tauq, real_1d_array &taup);

// Unpacking matrix Q which reduces a matrix to bidiagonal form.
//
// Inputs:
//     QP          -   matrices Q and P in compact form.
//                     Output of ToBidiagonal subroutine.
//     M           -   number of rows in matrix A.
//     N           -   number of columns in matrix A.
//     TAUQ        -   scalar factors which are used to form Q.
//                     Output of ToBidiagonal subroutine.
//     QColumns    -   required number of columns in matrix Q.
//                     M >= QColumns >= 0.
//
// Outputs:
//     Q           -   first QColumns columns of matrix Q.
//                     Array[0..M-1, 0..QColumns-1]
//                     If QColumns=0, the array is not modified.
// ALGLIB: Copyright 2005-2010 by Sergey Bochkanov
void rmatrixbdunpackq(const real_2d_array &qp, const ae_int_t m, const ae_int_t n, const real_1d_array &tauq, const ae_int_t qcolumns, real_2d_array &q);

// Multiplication by matrix Q which reduces matrix A to  bidiagonal form.
//
// The algorithm allows pre- or post-multiply by Q or Q'.
//
// Inputs:
//     QP          -   matrices Q and P in compact form.
//                     Output of ToBidiagonal subroutine.
//     M           -   number of rows in matrix A.
//     N           -   number of columns in matrix A.
//     TAUQ        -   scalar factors which are used to form Q.
//                     Output of ToBidiagonal subroutine.
//     Z           -   multiplied matrix.
//                     array[0..ZRows-1,0..ZColumns-1]
//     ZRows       -   number of rows in matrix Z. If FromTheRight=False,
//                     ZRows=M, otherwise ZRows can be arbitrary.
//     ZColumns    -   number of columns in matrix Z. If FromTheRight=True,
//                     ZColumns=M, otherwise ZColumns can be arbitrary.
//     FromTheRight -  pre- or post-multiply.
//     DoTranspose -   multiply by Q or Q'.
//
// Outputs:
//     Z           -   product of Z and Q.
//                     Array[0..ZRows-1,0..ZColumns-1]
//                     If ZRows=0 or ZColumns=0, the array is not modified.
// ALGLIB: Copyright 2005-2010 by Sergey Bochkanov
void rmatrixbdmultiplybyq(const real_2d_array &qp, const ae_int_t m, const ae_int_t n, const real_1d_array &tauq, real_2d_array &z, const ae_int_t zrows, const ae_int_t zcolumns, const bool fromtheright, const bool dotranspose);

// Unpacking matrix P which reduces matrix A to bidiagonal form.
// The subroutine returns transposed matrix P.
//
// Inputs:
//     QP      -   matrices Q and P in compact form.
//                 Output of ToBidiagonal subroutine.
//     M       -   number of rows in matrix A.
//     N       -   number of columns in matrix A.
//     TAUP    -   scalar factors which are used to form P.
//                 Output of ToBidiagonal subroutine.
//     PTRows  -   required number of rows of matrix P^T. N >= PTRows >= 0.
//
// Outputs:
//     PT      -   first PTRows columns of matrix P^T
//                 Array[0..PTRows-1, 0..N-1]
//                 If PTRows=0, the array is not modified.
// ALGLIB: Copyright 2005-2010 by Sergey Bochkanov
void rmatrixbdunpackpt(const real_2d_array &qp, const ae_int_t m, const ae_int_t n, const real_1d_array &taup, const ae_int_t ptrows, real_2d_array &pt);

// Multiplication by matrix P which reduces matrix A to  bidiagonal form.
//
// The algorithm allows pre- or post-multiply by P or P'.
//
// Inputs:
//     QP          -   matrices Q and P in compact form.
//                     Output of RMatrixBD subroutine.
//     M           -   number of rows in matrix A.
//     N           -   number of columns in matrix A.
//     TAUP        -   scalar factors which are used to form P.
//                     Output of RMatrixBD subroutine.
//     Z           -   multiplied matrix.
//                     Array whose indexes range within [0..ZRows-1,0..ZColumns-1].
//     ZRows       -   number of rows in matrix Z. If FromTheRight=False,
//                     ZRows=N, otherwise ZRows can be arbitrary.
//     ZColumns    -   number of columns in matrix Z. If FromTheRight=True,
//                     ZColumns=N, otherwise ZColumns can be arbitrary.
//     FromTheRight -  pre- or post-multiply.
//     DoTranspose -   multiply by P or P'.
//
// Outputs:
//     Z - product of Z and P.
//                 Array whose indexes range within [0..ZRows-1,0..ZColumns-1].
//                 If ZRows=0 or ZColumns=0, the array is not modified.
// ALGLIB: Copyright 2005-2010 by Sergey Bochkanov
void rmatrixbdmultiplybyp(const real_2d_array &qp, const ae_int_t m, const ae_int_t n, const real_1d_array &taup, real_2d_array &z, const ae_int_t zrows, const ae_int_t zcolumns, const bool fromtheright, const bool dotranspose);

// Unpacking of the main and secondary diagonals of bidiagonal decomposition
// of matrix A.
//
// Inputs:
//     B   -   output of RMatrixBD subroutine.
//     M   -   number of rows in matrix B.
//     N   -   number of columns in matrix B.
//
// Outputs:
//     IsUpper -   True, if the matrix is upper bidiagonal.
//                 otherwise IsUpper is False.
//     D       -   the main diagonal.
//                 Array whose index ranges within [0..Min(M,N)-1].
//     E       -   the secondary diagonal (upper or lower, depending on
//                 the value of IsUpper).
//                 Array index ranges within [0..Min(M,N)-1], the last
//                 element is not used.
// ALGLIB: Copyright 2005-2010 by Sergey Bochkanov
void rmatrixbdunpackdiagonals(const real_2d_array &b, const ae_int_t m, const ae_int_t n, bool &isupper, real_1d_array &d, real_1d_array &e);

// Reduction of a square matrix to  upper Hessenberg form: Q'*A*Q = H,
// where Q is an orthogonal matrix, H - Hessenberg matrix.
//
// Inputs:
//     A       -   matrix A with elements [0..N-1, 0..N-1]
//     N       -   size of matrix A.
//
// Outputs:
//     A       -   matrices Q and P in  compact form (see below).
//     Tau     -   array of scalar factors which are used to form matrix Q.
//                 Array whose index ranges within [0..N-2]
//
// Matrix H is located on the main diagonal, on the lower secondary  diagonal
// and above the main diagonal of matrix A. The elements which are used to
// form matrix Q are situated in array Tau and below the lower secondary
// diagonal of matrix A as follows:
//
// Matrix Q is represented as a product of elementary reflections
//
// Q = H(0)*H(2)*...*H(n-2),
//
// where each H(i) is given by
//
// H(i) = 1 - tau * v * (v^T)
//
// where tau is a scalar stored in Tau[I]; v - is a real vector,
// so that v(0:i) = 0, v(i+1) = 1, v(i+2:n-1) stored in A(i+2:n-1,i).
//
//   -- LAPACK routine (version 3.0) --
//      Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd.,
//      Courant Institute, Argonne National Lab, and Rice University
//      October 31, 1992
void rmatrixhessenberg(real_2d_array &a, const ae_int_t n, real_1d_array &tau);

// Unpacking matrix Q which reduces matrix A to upper Hessenberg form
//
// Inputs:
//     A   -   output of RMatrixHessenberg subroutine.
//     N   -   size of matrix A.
//     Tau -   scalar factors which are used to form Q.
//             Output of RMatrixHessenberg subroutine.
//
// Outputs:
//     Q   -   matrix Q.
//             Array whose indexes range within [0..N-1, 0..N-1].
// ALGLIB: Copyright 2005-2010 by Sergey Bochkanov
void rmatrixhessenbergunpackq(const real_2d_array &a, const ae_int_t n, const real_1d_array &tau, real_2d_array &q);

// Unpacking matrix H (the result of matrix A reduction to upper Hessenberg form)
//
// Inputs:
//     A   -   output of RMatrixHessenberg subroutine.
//     N   -   size of matrix A.
//
// Outputs:
//     H   -   matrix H. Array whose indexes range within [0..N-1, 0..N-1].
// ALGLIB: Copyright 2005-2010 by Sergey Bochkanov
void rmatrixhessenbergunpackh(const real_2d_array &a, const ae_int_t n, real_2d_array &h);

// Reduction of a symmetric matrix which is given by its higher or lower
// triangular part to a tridiagonal matrix using orthogonal similarity
// transformation: Q'*A*Q=T.
//
// Inputs:
//     A       -   matrix to be transformed
//                 array with elements [0..N-1, 0..N-1].
//     N       -   size of matrix A.
//     IsUpper -   storage format. If IsUpper = True, then matrix A is given
//                 by its upper triangle, and the lower triangle is not used
//                 and not modified by the algorithm, and vice versa
//                 if IsUpper = False.
//
// Outputs:
//     A       -   matrices T and Q in  compact form (see lower)
//     Tau     -   array of factors which are forming matrices H(i)
//                 array with elements [0..N-2].
//     D       -   main diagonal of symmetric matrix T.
//                 array with elements [0..N-1].
//     E       -   secondary diagonal of symmetric matrix T.
//                 array with elements [0..N-2].
//
//
//   If IsUpper=True, the matrix Q is represented as a product of elementary
//   reflectors
//
//      Q = H(n-2) . . . H(2) H(0).
//
//   Each H(i) has the form
//
//      H(i) = I - tau * v * v'
//
//   where tau is a real scalar, and v is a real vector with
//   v(i+1:n-1) = 0, v(i) = 1, v(0:i-1) is stored on exit in
//   A(0:i-1,i+1), and tau in TAU(i).
//
//   If IsUpper=False, the matrix Q is represented as a product of elementary
//   reflectors
//
//      Q = H(0) H(2) . . . H(n-2).
//
//   Each H(i) has the form
//
//      H(i) = I - tau * v * v'
//
//   where tau is a real scalar, and v is a real vector with
//   v(0:i) = 0, v(i+1) = 1, v(i+2:n-1) is stored on exit in A(i+2:n-1,i),
//   and tau in TAU(i).
//
//   The contents of A on exit are illustrated by the following examples
//   with n = 5:
//
//   if UPLO = 'U':                       if UPLO = 'L':
//
//     (  d   e   v1  v2  v3 )              (  d                  )
//     (      d   e   v2  v3 )              (  e   d              )
//     (          d   e   v3 )              (  v0  e   d          )
//     (              d   e  )              (  v0  v1  e   d      )
//     (                  d  )              (  v0  v1  v2  e   d  )
//
//   where d and e denote diagonal and off-diagonal elements of T, and vi
//   denotes an element of the vector defining H(i).
//
//   -- LAPACK routine (version 3.0) --
//      Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd.,
//      Courant Institute, Argonne National Lab, and Rice University
//      October 31, 1992
void smatrixtd(real_2d_array &a, const ae_int_t n, const bool isupper, real_1d_array &tau, real_1d_array &d, real_1d_array &e);

// Unpacking matrix Q which reduces symmetric matrix to a tridiagonal
// form.
//
// Inputs:
//     A       -   the result of a SMatrixTD subroutine
//     N       -   size of matrix A.
//     IsUpper -   storage format (a parameter of SMatrixTD subroutine)
//     Tau     -   the result of a SMatrixTD subroutine
//
// Outputs:
//     Q       -   transformation matrix.
//                 array with elements [0..N-1, 0..N-1].
// ALGLIB: Copyright 2005-2010 by Sergey Bochkanov
void smatrixtdunpackq(const real_2d_array &a, const ae_int_t n, const bool isupper, const real_1d_array &tau, real_2d_array &q);

// Reduction of a Hermitian matrix which is given  by  its  higher  or  lower
// triangular part to a real  tridiagonal  matrix  using  unitary  similarity
// transformation: Q'*A*Q = T.
//
// Inputs:
//     A       -   matrix to be transformed
//                 array with elements [0..N-1, 0..N-1].
//     N       -   size of matrix A.
//     IsUpper -   storage format. If IsUpper = True, then matrix A is  given
//                 by its upper triangle, and the lower triangle is not  used
//                 and not modified by the algorithm, and vice versa
//                 if IsUpper = False.
//
// Outputs:
//     A       -   matrices T and Q in  compact form (see lower)
//     Tau     -   array of factors which are forming matrices H(i)
//                 array with elements [0..N-2].
//     D       -   main diagonal of real symmetric matrix T.
//                 array with elements [0..N-1].
//     E       -   secondary diagonal of real symmetric matrix T.
//                 array with elements [0..N-2].
//
//
//   If IsUpper=True, the matrix Q is represented as a product of elementary
//   reflectors
//
//      Q = H(n-2) . . . H(2) H(0).
//
//   Each H(i) has the form
//
//      H(i) = I - tau * v * v'
//
//   where tau is a complex scalar, and v is a complex vector with
//   v(i+1:n-1) = 0, v(i) = 1, v(0:i-1) is stored on exit in
//   A(0:i-1,i+1), and tau in TAU(i).
//
//   If IsUpper=False, the matrix Q is represented as a product of elementary
//   reflectors
//
//      Q = H(0) H(2) . . . H(n-2).
//
//   Each H(i) has the form
//
//      H(i) = I - tau * v * v'
//
//   where tau is a complex scalar, and v is a complex vector with
//   v(0:i) = 0, v(i+1) = 1, v(i+2:n-1) is stored on exit in A(i+2:n-1,i),
//   and tau in TAU(i).
//
//   The contents of A on exit are illustrated by the following examples
//   with n = 5:
//
//   if UPLO = 'U':                       if UPLO = 'L':
//
//     (  d   e   v1  v2  v3 )              (  d                  )
//     (      d   e   v2  v3 )              (  e   d              )
//     (          d   e   v3 )              (  v0  e   d          )
//     (              d   e  )              (  v0  v1  e   d      )
//     (                  d  )              (  v0  v1  v2  e   d  )
//
// where d and e denote diagonal and off-diagonal elements of T, and vi
// denotes an element of the vector defining H(i).
//
//   -- LAPACK routine (version 3.0) --
//      Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd.,
//      Courant Institute, Argonne National Lab, and Rice University
//      October 31, 1992
void hmatrixtd(complex_2d_array &a, const ae_int_t n, const bool isupper, complex_1d_array &tau, real_1d_array &d, real_1d_array &e);

// Unpacking matrix Q which reduces a Hermitian matrix to a real  tridiagonal
// form.
//
// Inputs:
//     A       -   the result of a HMatrixTD subroutine
//     N       -   size of matrix A.
//     IsUpper -   storage format (a parameter of HMatrixTD subroutine)
//     Tau     -   the result of a HMatrixTD subroutine
//
// Outputs:
//     Q       -   transformation matrix.
//                 array with elements [0..N-1, 0..N-1].
// ALGLIB: Copyright 2005-2010 by Sergey Bochkanov
void hmatrixtdunpackq(const complex_2d_array &a, const ae_int_t n, const bool isupper, const complex_1d_array &tau, complex_2d_array &q);
} // end of namespace alglib

// === FBLS Package ===
// Depends on: ORTFAC
namespace alglib_impl {
struct fblslincgstate {
   double e1;
   double e2;
   ae_vector x;
   ae_vector ax;
   double xax;
   ae_int_t n;
   ae_vector rk;
   ae_vector rk1;
   ae_vector xk;
   ae_vector xk1;
   ae_vector pk;
   ae_vector pk1;
   ae_vector b;
   ae_int_t PQ;
   ae_vector tmp2;
};
void fblslincgstate_init(void *_p, bool make_automatic);
void fblslincgstate_copy(void *_dst, void *_src, bool make_automatic);
void fblslincgstate_free(void *_p, bool make_automatic);

void fblscholeskysolve(RMatrix *cha, double sqrtscalea, ae_int_t n, bool isupper, RVector *xb, RVector *tmp);
void fblssolvecgx(RMatrix *a, ae_int_t m, ae_int_t n, double alpha, RVector *b, RVector *x, RVector *buf);
void fblscgcreate(RVector *x, RVector *b, ae_int_t n, fblslincgstate *state);
bool fblscgiteration(fblslincgstate *state);
void fblssolvels(RMatrix *a, RVector *b, ae_int_t m, ae_int_t n, RVector *tmp0, RVector *tmp1, RVector *tmp2);
} // end of namespace alglib_impl

// === BDSVD Package ===
// Depends on: (AlgLibInternal) ROTATIONS
// Depends on: (AlgLibMisc) HQRND
// Depends on: ABLAS
namespace alglib_impl {
bool rmatrixbdsvd(RVector *d, RVector *e, ae_int_t n, bool isupper, bool isfractionalaccuracyrequired, RMatrix *u, ae_int_t nru, RMatrix *c, ae_int_t ncc, RMatrix *vt, ae_int_t ncvt);
bool bidiagonalsvddecomposition(RVector *d, RVector *e, ae_int_t n, bool isupper, bool isfractionalaccuracyrequired, RMatrix *u, ae_int_t nru, RMatrix *c, ae_int_t ncc, RMatrix *vt, ae_int_t ncvt);
} // end of namespace alglib_impl

namespace alglib {
// Singular value decomposition of a bidiagonal matrix (extended algorithm)
//
// The algorithm performs the singular value decomposition  of  a  bidiagonal
// matrix B (upper or lower) representing it as B = Q*S*P^T, where Q and  P -
// orthogonal matrices, S - diagonal matrix with non-negative elements on the
// main diagonal, in descending order.
//
// The  algorithm  finds  singular  values.  In  addition,  the algorithm can
// calculate  matrices  Q  and P (more precisely, not the matrices, but their
// product  with  given  matrices U and VT - U*Q and (P^T)*VT)).  Of  course,
// matrices U and VT can be of any type, including identity. Furthermore, the
// algorithm can calculate Q'*C (this product is calculated more  effectively
// than U*Q,  because  this calculation operates with rows instead  of matrix
// columns).
//
// The feature of the algorithm is its ability to find  all  singular  values
// including those which are arbitrarily close to 0  with  relative  accuracy
// close to  machine precision. If the parameter IsFractionalAccuracyRequired
// is set to True, all singular values will have high relative accuracy close
// to machine precision. If the parameter is set to False, only  the  biggest
// singular value will have relative accuracy  close  to  machine  precision.
// The absolute error of other singular values is equal to the absolute error
// of the biggest singular value.
//
// Inputs:
//     D       -   main diagonal of matrix B.
//                 Array whose index ranges within [0..N-1].
//     E       -   superdiagonal (or subdiagonal) of matrix B.
//                 Array whose index ranges within [0..N-2].
//     N       -   size of matrix B.
//     IsUpper -   True, if the matrix is upper bidiagonal.
//     IsFractionalAccuracyRequired -
//                 THIS PARAMETER IS IGNORED SINCE ALGLIB 3.5.0
//                 SINGULAR VALUES ARE ALWAYS SEARCHED WITH HIGH ACCURACY.
//     U       -   matrix to be multiplied by Q.
//                 Array whose indexes range within [0..NRU-1, 0..N-1].
//                 The matrix can be bigger, in that case only the  submatrix
//                 [0..NRU-1, 0..N-1] will be multiplied by Q.
//     NRU     -   number of rows in matrix U.
//     C       -   matrix to be multiplied by Q'.
//                 Array whose indexes range within [0..N-1, 0..NCC-1].
//                 The matrix can be bigger, in that case only the  submatrix
//                 [0..N-1, 0..NCC-1] will be multiplied by Q'.
//     NCC     -   number of columns in matrix C.
//     VT      -   matrix to be multiplied by P^T.
//                 Array whose indexes range within [0..N-1, 0..NCVT-1].
//                 The matrix can be bigger, in that case only the  submatrix
//                 [0..N-1, 0..NCVT-1] will be multiplied by P^T.
//     NCVT    -   number of columns in matrix VT.
//
// Outputs:
//     D       -   singular values of matrix B in descending order.
//     U       -   if NRU > 0, contains matrix U*Q.
//     VT      -   if NCVT > 0, contains matrix (P^T)*VT.
//     C       -   if NCC > 0, contains matrix Q'*C.
//
// Result:
//     True, if the algorithm has converged.
//     False, if the algorithm hasn't converged (rare case).
//
// NOTE: multiplication U*Q is performed by means of transposition to internal
//       buffer, multiplication and backward transposition. It helps to avoid
//       costly columnwise operations and speed-up algorithm.
//
// Additional information:
//     The type of convergence is controlled by the internal  parameter  TOL.
//     If the parameter is greater than 0, the singular values will have
//     relative accuracy TOL. If TOL < 0, the singular values will have
//     absolute accuracy ABS(TOL)*norm(B).
//     By default, |TOL| falls within the range of 10*Epsilon and 100*Epsilon,
//     where Epsilon is the machine precision. It is not  recommended  to  use
//     TOL less than 10*Epsilon since this will  considerably  slow  down  the
//     algorithm and may not lead to error decreasing.
//
// History:
//     * 31 March, 2007.
//         changed MAXITR from 6 to 12.
//
//   -- LAPACK routine (version 3.0) --
//      Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd.,
//      Courant Institute, Argonne National Lab, and Rice University
//      October 31, 1999.
bool rmatrixbdsvd(real_1d_array &d, const real_1d_array &e, const ae_int_t n, const bool isupper, const bool isfractionalaccuracyrequired, real_2d_array &u, const ae_int_t nru, real_2d_array &c, const ae_int_t ncc, real_2d_array &vt, const ae_int_t ncvt);
} // end of namespace alglib

// === SVD Package ===
// Depends on: (AlgLibInternal) BLAS
// Depends on: ORTFAC, BDSVD
namespace alglib_impl {
bool rmatrixsvd(RMatrix *a, ae_int_t m, ae_int_t n, ae_int_t uneeded, ae_int_t vtneeded, ae_int_t additionalmemory, RVector *w, RMatrix *u, RMatrix *vt);
} // end of namespace alglib_impl

namespace alglib {
// Singular value decomposition of a rectangular matrix.
//
// The algorithm calculates the singular value decomposition of a matrix of
// size MxN: A = U * S * V^T
//
// The algorithm finds the singular values and, optionally, matrices U and V^T.
// The algorithm can find both first min(M,N) columns of matrix U and rows of
// matrix V^T (singular vectors), and matrices U and V^T wholly (of sizes MxM
// and NxN respectively).
//
// Take into account that the subroutine does not return matrix V but V^T.
//
// Inputs:
//     A           -   matrix to be decomposed.
//                     Array whose indexes range within [0..M-1, 0..N-1].
//     M           -   number of rows in matrix A.
//     N           -   number of columns in matrix A.
//     UNeeded     -   0, 1 or 2. See the description of the parameter U.
//     VTNeeded    -   0, 1 or 2. See the description of the parameter VT.
//     AdditionalMemory -
//                     If the parameter:
//                      * equals 0, the algorithm doesn't use additional
//                        memory (lower requirements, lower performance).
//                      * equals 1, the algorithm uses additional
//                        memory of size min(M,N)*min(M,N) of real numbers.
//                        It often speeds up the algorithm.
//                      * equals 2, the algorithm uses additional
//                        memory of size M*min(M,N) of real numbers.
//                        It allows to get a maximum performance.
//                     The recommended value of the parameter is 2.
//
// Outputs:
//     W           -   contains singular values in descending order.
//     U           -   if UNeeded=0, U isn't changed, the left singular vectors
//                     are not calculated.
//                     if Uneeded=1, U contains left singular vectors (first
//                     min(M,N) columns of matrix U). Array whose indexes range
//                     within [0..M-1, 0..Min(M,N)-1].
//                     if UNeeded=2, U contains matrix U wholly. Array whose
//                     indexes range within [0..M-1, 0..M-1].
//     VT          -   if VTNeeded=0, VT isn't changed, the right singular vectors
//                     are not calculated.
//                     if VTNeeded=1, VT contains right singular vectors (first
//                     min(M,N) rows of matrix V^T). Array whose indexes range
//                     within [0..min(M,N)-1, 0..N-1].
//                     if VTNeeded=2, VT contains matrix V^T wholly. Array whose
//                     indexes range within [0..N-1, 0..N-1].
// ALGLIB: Copyright 2005 by Sergey Bochkanov
bool rmatrixsvd(const real_2d_array &a, const ae_int_t m, const ae_int_t n, const ae_int_t uneeded, const ae_int_t vtneeded, const ae_int_t additionalmemory, real_1d_array &w, real_2d_array &u, real_2d_array &vt);
} // end of namespace alglib

// === NORMESTIMATOR Package ===
// Depends on: SPARSE, MATGEN
namespace alglib_impl {
struct normestimatorstate {
   ae_int_t n;
   ae_int_t m;
   ae_int_t nstart;
   ae_int_t nits;
   ae_int_t seedval;
   ae_vector x0;
   ae_vector x1;
   ae_vector t;
   ae_vector xbest;
   hqrndstate r;
   ae_vector x;
   ae_vector mv;
   ae_vector mtv;
   bool needmv;
   bool needmtv;
   double repnorm;
   ae_int_t PQ;
};
void normestimatorstate_init(void *_p, bool make_automatic);
void normestimatorstate_copy(void *_dst, void *_src, bool make_automatic);
void normestimatorstate_free(void *_p, bool make_automatic);

void normestimatorcreate(ae_int_t m, ae_int_t n, ae_int_t nstart, ae_int_t nits, normestimatorstate *state);
void normestimatorsetseed(normestimatorstate *state, ae_int_t seedval);
bool normestimatoriteration(normestimatorstate *state);
void normestimatorestimatesparse(normestimatorstate *state, sparsematrix *a);
void normestimatorresults(normestimatorstate *state, double *nrm);
void normestimatorrestart(normestimatorstate *state);
} // end of namespace alglib_impl

namespace alglib {
// This object stores state of the iterative norm estimation algorithm.
//
// You should use ALGLIB functions to work with this object.
DecClass(normestimatorstate, EndD);

// This procedure initializes matrix norm estimator.
//
// USAGE:
// 1. User initializes algorithm state with NormEstimatorCreate() call
// 2. User calls NormEstimatorEstimateSparse() (or NormEstimatorIteration())
// 3. User calls NormEstimatorResults() to get solution.
//
// Inputs:
//     M       -   number of rows in the matrix being estimated, M > 0
//     N       -   number of columns in the matrix being estimated, N > 0
//     NStart  -   number of random starting vectors
//                 recommended value - at least 5.
//     NIts    -   number of iterations to do with best starting vector
//                 recommended value - at least 5.
//
// Outputs:
//     State   -   structure which stores algorithm state
//
//
// NOTE: this algorithm is effectively deterministic, i.e. it always  returns
// same result when repeatedly called for the same matrix. In fact, algorithm
// uses randomized starting vectors, but internal  random  numbers  generator
// always generates same sequence of the random values (it is a  feature, not
// bug).
//
// Algorithm can be made non-deterministic with NormEstimatorSetSeed(0) call.
// ALGLIB: Copyright 06.12.2011 by Sergey Bochkanov
void normestimatorcreate(const ae_int_t m, const ae_int_t n, const ae_int_t nstart, const ae_int_t nits, normestimatorstate &state);

// This function changes seed value used by algorithm. In some cases we  need
// deterministic processing, i.e. subsequent calls must return equal results,
// in other cases we need non-deterministic algorithm which returns different
// results for the same matrix on every pass.
//
// Setting zero seed will lead to non-deterministic algorithm, while non-zero
// value will make our algorithm deterministic.
//
// Inputs:
//     State       -   norm estimator state, must be initialized with a  call
//                     to NormEstimatorCreate()
//     SeedVal     -   seed value, >= 0. Zero value = non-deterministic algo.
// ALGLIB: Copyright 06.12.2011 by Sergey Bochkanov
void normestimatorsetseed(const normestimatorstate &state, const ae_int_t seedval);

// This function estimates norm of the sparse M*N matrix A.
//
// Inputs:
//     State       -   norm estimator state, must be initialized with a  call
//                     to NormEstimatorCreate()
//     A           -   sparse M*N matrix, must be converted to CRS format
//                     prior to calling this function.
//
// After this function  is  over  you can call NormEstimatorResults() to get
// estimate of the norm(A).
// ALGLIB: Copyright 06.12.2011 by Sergey Bochkanov
void normestimatorestimatesparse(const normestimatorstate &state, const sparsematrix &a);

// Matrix norm estimation results
//
// Inputs:
//     State   -   algorithm state
//
// Outputs:
//     Nrm     -   estimate of the matrix norm, Nrm >= 0
// ALGLIB: Copyright 06.12.2011 by Sergey Bochkanov
void normestimatorresults(const normestimatorstate &state, double &nrm);
} // end of namespace alglib

// === HSSCHUR Package ===
// Depends on: (AlgLibInternal) ROTATIONS, BLAS
// Depends on: ABLAS
namespace alglib_impl {
void rmatrixinternalschurdecomposition(RMatrix *h, ae_int_t n, ae_int_t tneeded, ae_int_t zneeded, RVector *wr, RVector *wi, RMatrix *z, ae_int_t *info);
bool upperhessenbergschurdecomposition(RMatrix *h, ae_int_t n, RMatrix *s);
void internalschurdecomposition(RMatrix *h, ae_int_t n, ae_int_t tneeded, ae_int_t zneeded, RVector *wr, RVector *wi, RMatrix *z, ae_int_t *info);
} // end of namespace alglib_impl

// === EVD Package ===
// Depends on: (AlgLibInternal) BASICSTATOPS
// Depends on: SPARSE, MATGEN, ORTFAC, HSSCHUR
namespace alglib_impl {
struct eigsubspacestate {
   ae_int_t n;
   ae_int_t k;
   ae_int_t nwork;
   ae_int_t maxits;
   double eps;
   ae_int_t eigenvectorsneeded;
   ae_int_t matrixtype;
   bool usewarmstart;
   bool firstcall;
   hqrndstate rs;
   bool running;
   ae_vector tau;
   ae_matrix q0;
   ae_matrix qcur;
   ae_matrix qnew;
   ae_matrix znew;
   ae_matrix r;
   ae_matrix rz;
   ae_matrix tz;
   ae_matrix rq;
   ae_matrix dummy;
   ae_vector rw;
   ae_vector tw;
   ae_vector wcur;
   ae_vector wprev;
   ae_vector wrank;
   apbuffers buf;
   ae_matrix x;
   ae_matrix ax;
   ae_int_t requesttype;
   ae_int_t requestsize;
   ae_int_t repiterationscount;
   ae_int_t PQ;
};
void eigsubspacestate_init(void *_p, bool make_automatic);
void eigsubspacestate_copy(void *_dst, void *_src, bool make_automatic);
void eigsubspacestate_free(void *_p, bool make_automatic);

struct eigsubspacereport {
   ae_int_t iterationscount;
};
void eigsubspacereport_init(void *_p, bool make_automatic);
void eigsubspacereport_copy(void *_dst, void *_src, bool make_automatic);
void eigsubspacereport_free(void *_p, bool make_automatic);

void eigsubspacecreate(ae_int_t n, ae_int_t k, eigsubspacestate *state);
void eigsubspacecreatebuf(ae_int_t n, ae_int_t k, eigsubspacestate *state);
void eigsubspacesetcond(eigsubspacestate *state, double eps, ae_int_t maxits);
void eigsubspacesetwarmstart(eigsubspacestate *state, bool usewarmstart);
void eigsubspaceoocstart(eigsubspacestate *state, ae_int_t mtype);
bool eigsubspaceooccontinue(eigsubspacestate *state);
void eigsubspaceoocgetrequestinfo(eigsubspacestate *state, ae_int_t *requesttype, ae_int_t *requestsize);
void eigsubspaceoocgetrequestdata(eigsubspacestate *state, RMatrix *x);
void eigsubspaceoocsendresult(eigsubspacestate *state, RMatrix *ax);
void eigsubspaceoocstop(eigsubspacestate *state, RVector *w, RMatrix *z, eigsubspacereport *rep);
void eigsubspacesolvedenses(eigsubspacestate *state, RMatrix *a, bool isupper, RVector *w, RMatrix *z, eigsubspacereport *rep);
void eigsubspacesolvesparses(eigsubspacestate *state, sparsematrix *a, bool isupper, RVector *w, RMatrix *z, eigsubspacereport *rep);
bool eigsubspaceiteration(eigsubspacestate *state);
bool smatrixevd(RMatrix *a, ae_int_t n, ae_int_t zneeded, bool isupper, RVector *d, RMatrix *z);
bool smatrixevdr(RMatrix *a, ae_int_t n, ae_int_t zneeded, bool isupper, double b1, double b2, ae_int_t *m, RVector *w, RMatrix *z);
bool smatrixevdi(RMatrix *a, ae_int_t n, ae_int_t zneeded, bool isupper, ae_int_t i1, ae_int_t i2, RVector *w, RMatrix *z);
bool hmatrixevd(CMatrix *a, ae_int_t n, ae_int_t zneeded, bool isupper, RVector *d, CMatrix *z);
bool hmatrixevdr(CMatrix *a, ae_int_t n, ae_int_t zneeded, bool isupper, double b1, double b2, ae_int_t *m, RVector *w, CMatrix *z);
bool hmatrixevdi(CMatrix *a, ae_int_t n, ae_int_t zneeded, bool isupper, ae_int_t i1, ae_int_t i2, RVector *w, CMatrix *z);
bool smatrixtdevd(RVector *d, RVector *e, ae_int_t n, ae_int_t zneeded, RMatrix *z);
bool smatrixtdevdr(RVector *d, RVector *e, ae_int_t n, ae_int_t zneeded, double a, double b, ae_int_t *m, RMatrix *z);
bool smatrixtdevdi(RVector *d, RVector *e, ae_int_t n, ae_int_t zneeded, ae_int_t i1, ae_int_t i2, RMatrix *z);
bool rmatrixevd(RMatrix *a, ae_int_t n, ae_int_t vneeded, RVector *wr, RVector *wi, RMatrix *vl, RMatrix *vr);
} // end of namespace alglib_impl

namespace alglib {
// This object stores state of the subspace iteration algorithm.
//
// You should use ALGLIB functions to work with this object.
DecClass(eigsubspacestate, EndD);

// This object stores state of the subspace iteration algorithm.
//
// You should use ALGLIB functions to work with this object.
DecClass(eigsubspacereport, ae_int_t &iterationscount;);

// This function initializes subspace iteration solver. This solver  is  used
// to solve symmetric real eigenproblems where just a few (top K) eigenvalues
// and corresponding eigenvectors is required.
//
// This solver can be significantly faster than  complete  EVD  decomposition
// in the following case:
// * when only just a small fraction  of  top  eigenpairs  of dense matrix is
//   required. When K approaches N, this solver is slower than complete dense
//   EVD
// * when problem matrix is sparse (and/or is not known explicitly, i.e. only
//   matrix-matrix product can be performed)
//
// USAGE (explicit dense/sparse matrix):
// 1. User initializes algorithm state with eigsubspacecreate() call
// 2. [optional] User tunes solver parameters by calling eigsubspacesetcond()
//    or other functions
// 3. User  calls  eigsubspacesolvedense() or eigsubspacesolvesparse() methods,
//    which take algorithm state and 2D array or alglib.sparsematrix object.
//
// USAGE (out-of-core mode):
// 1. User initializes algorithm state with eigsubspacecreate() call
// 2. [optional] User tunes solver parameters by calling eigsubspacesetcond()
//    or other functions
// 3. User activates out-of-core mode of  the  solver  and  repeatedly  calls
//    communication functions in a loop like below:
//    > alglib.eigsubspaceoocstart(state)
//    > while alglib.eigsubspaceooccontinue(state) do
//    >     alglib.eigsubspaceoocgetrequestinfo(state, out RequestType, out M)
//    >     alglib.eigsubspaceoocgetrequestdata(state, out X)
//    >     [calculate  Y=A*X, with X=R^NxM]
//    >     alglib.eigsubspaceoocsendresult(state, in Y)
//    > alglib.eigsubspaceoocstop(state, out W, out Z, out Report)
//
// Inputs:
//     N       -   problem dimensionality, N > 0
//     K       -   number of top eigenvector to calculate, 0 < K <= N.
//
// Outputs:
//     State   -   structure which stores algorithm state
//
// NOTE: if you solve many similar EVD problems you may  find  it  useful  to
//       reuse previous subspace as warm-start point for new EVD problem.  It
//       can be done with eigsubspacesetwarmstart() function.
// ALGLIB: Copyright 16.01.2017 by Sergey Bochkanov
void eigsubspacecreate(const ae_int_t n, const ae_int_t k, eigsubspacestate &state);

// Buffered version of constructor which aims to reuse  previously  allocated
// memory as much as possible.
// ALGLIB: Copyright 16.01.2017 by Sergey Bochkanov
void eigsubspacecreatebuf(const ae_int_t n, const ae_int_t k, const eigsubspacestate &state);

// This function sets stopping critera for the solver:
// * error in eigenvector/value allowed by solver
// * maximum number of iterations to perform
//
// Inputs:
//     State       -   solver structure
//     Eps         -   eps >= 0,  with non-zero value used to tell solver  that
//                     it can  stop  after  all  eigenvalues  converged  with
//                     error  roughly  proportional  to  eps*MAX(LAMBDA_MAX),
//                     where LAMBDA_MAX is a maximum eigenvalue.
//                     Zero  value  means  that  no  check  for  precision is
//                     performed.
//     MaxIts      -   maxits >= 0,  with non-zero value used  to  tell  solver
//                     that it can stop after maxits  steps  (no  matter  how
//                     precise current estimate is)
//
// NOTE: passing  eps=0  and  maxits=0  results  in  automatic  selection  of
//       moderate eps as stopping criteria (1.0E-6 in current implementation,
//       but it may change without notice).
//
// NOTE: very small values of eps are possible (say, 1.0E-12),  although  the
//       larger problem you solve (N and/or K), the  harder  it  is  to  find
//       precise eigenvectors because rounding errors tend to accumulate.
//
// NOTE: passing non-zero eps results in  some performance  penalty,  roughly
//       equal to 2N*(2K)^2 FLOPs per iteration. These additional computations
//       are required in order to estimate current error in  eigenvalues  via
//       Rayleigh-Ritz process.
//       Most of this additional time is  spent  in  construction  of  ~2Kx2K
//       symmetric  subproblem  whose  eigenvalues  are  checked  with  exact
//       eigensolver.
//       This additional time is negligible if you search for eigenvalues  of
//       the large dense matrix, but may become noticeable on  highly  sparse
//       EVD problems, where cost of matrix-matrix product is low.
//       If you set eps to exactly zero,  Rayleigh-Ritz  phase  is completely
//       turned off.
// ALGLIB: Copyright 16.01.2017 by Sergey Bochkanov
void eigsubspacesetcond(const eigsubspacestate &state, const double eps, const ae_int_t maxits);

// This function sets warm-start mode of the solver: next call to the  solver
// will reuse previous subspace as warm-start  point.  It  can  significantly
// speed-up convergence when you solve many similar eigenproblems.
//
// Inputs:
//     State       -   solver structure
//     UseWarmStart-   either True or False
// ALGLIB: Copyright 12.11.2017 by Sergey Bochkanov
void eigsubspacesetwarmstart(const eigsubspacestate &state, const bool usewarmstart);

// This  function  initiates  out-of-core  mode  of  subspace eigensolver. It
// should be used in conjunction with other out-of-core-related functions  of
// this subspackage in a loop like below:
//
// > alglib.eigsubspaceoocstart(state)
// > while alglib.eigsubspaceooccontinue(state) do
// >     alglib.eigsubspaceoocgetrequestinfo(state, out RequestType, out M)
// >     alglib.eigsubspaceoocgetrequestdata(state, out X)
// >     [calculate  Y=A*X, with X=R^NxM]
// >     alglib.eigsubspaceoocsendresult(state, in Y)
// > alglib.eigsubspaceoocstop(state, out W, out Z, out Report)
//
// Inputs:
//     State       -   solver object
//     MType       -   matrix type:
//                     * 0 for real  symmetric  matrix  (solver  assumes that
//                       matrix  being   processed  is  symmetric;  symmetric
//                       direct eigensolver is used for  smaller  subproblems
//                       arising during solution of larger "full" task)
//                     Future versions of ALGLIB may  introduce  support  for
//                     other  matrix   types;   for   now,   only   symmetric
//                     eigenproblems are supported.
//
// ALGLIB: Copyright 16.01.2017 by Sergey Bochkanov
void eigsubspaceoocstart(const eigsubspacestate &state, const ae_int_t mtype);

// This function performs subspace iteration  in  the  out-of-core  mode.  It
// should be used in conjunction with other out-of-core-related functions  of
// this subspackage in a loop like below:
//
// > alglib.eigsubspaceoocstart(state)
// > while alglib.eigsubspaceooccontinue(state) do
// >     alglib.eigsubspaceoocgetrequestinfo(state, out RequestType, out M)
// >     alglib.eigsubspaceoocgetrequestdata(state, out X)
// >     [calculate  Y=A*X, with X=R^NxM]
// >     alglib.eigsubspaceoocsendresult(state, in Y)
// > alglib.eigsubspaceoocstop(state, out W, out Z, out Report)
//
// ALGLIB: Copyright 16.01.2017 by Sergey Bochkanov
bool eigsubspaceooccontinue(const eigsubspacestate &state);

// This function is used to retrieve information  about  out-of-core  request
// sent by solver to user code: request type (current version  of  the solver
// sends only requests for matrix-matrix products) and request size (size  of
// the matrices being multiplied).
//
// This function returns just request metrics; in order  to  get contents  of
// the matrices being multiplied, use eigsubspaceoocgetrequestdata().
//
// It should be used in conjunction with other out-of-core-related  functions
// of this subspackage in a loop like below:
//
// > alglib.eigsubspaceoocstart(state)
// > while alglib.eigsubspaceooccontinue(state) do
// >     alglib.eigsubspaceoocgetrequestinfo(state, out RequestType, out M)
// >     alglib.eigsubspaceoocgetrequestdata(state, out X)
// >     [calculate  Y=A*X, with X=R^NxM]
// >     alglib.eigsubspaceoocsendresult(state, in Y)
// > alglib.eigsubspaceoocstop(state, out W, out Z, out Report)
//
// Inputs:
//     State           -   solver running in out-of-core mode
//
// Outputs:
//     RequestType     -   type of the request to process:
//                         * 0 - for matrix-matrix product A*X, with A  being
//                           NxN matrix whose eigenvalues/vectors are needed,
//                           and X being NxREQUESTSIZE one which is  returned
//                           by the eigsubspaceoocgetrequestdata().
//     RequestSize     -   size of the X matrix (number of columns),  usually
//                         it is several times larger than number of  vectors
//                         K requested by user.
//
// ALGLIB: Copyright 16.01.2017 by Sergey Bochkanov
void eigsubspaceoocgetrequestinfo(const eigsubspacestate &state, ae_int_t &requesttype, ae_int_t &requestsize);

// This function is used to retrieve information  about  out-of-core  request
// sent by solver to user code: matrix X (array[N,RequestSize) which have  to
// be multiplied by out-of-core matrix A in a product A*X.
//
// This function returns just request data; in order to get size of  the data
// prior to processing requestm, use eigsubspaceoocgetrequestinfo().
//
// It should be used in conjunction with other out-of-core-related  functions
// of this subspackage in a loop like below:
//
// > alglib.eigsubspaceoocstart(state)
// > while alglib.eigsubspaceooccontinue(state) do
// >     alglib.eigsubspaceoocgetrequestinfo(state, out RequestType, out M)
// >     alglib.eigsubspaceoocgetrequestdata(state, out X)
// >     [calculate  Y=A*X, with X=R^NxM]
// >     alglib.eigsubspaceoocsendresult(state, in Y)
// > alglib.eigsubspaceoocstop(state, out W, out Z, out Report)
//
// Inputs:
//     State           -   solver running in out-of-core mode
//     X               -   possibly  preallocated   storage;  reallocated  if
//                         needed, left unchanged, if large enough  to  store
//                         request data.
//
// Outputs:
//     X               -   array[N,RequestSize] or larger, leading  rectangle
//                         is filled with dense matrix X.
//
// ALGLIB: Copyright 16.01.2017 by Sergey Bochkanov
void eigsubspaceoocgetrequestdata(const eigsubspacestate &state, real_2d_array &x);

// This function is used to send user reply to out-of-core  request  sent  by
// solver. Usually it is product A*X for returned by solver matrix X.
//
// It should be used in conjunction with other out-of-core-related  functions
// of this subspackage in a loop like below:
//
// > alglib.eigsubspaceoocstart(state)
// > while alglib.eigsubspaceooccontinue(state) do
// >     alglib.eigsubspaceoocgetrequestinfo(state, out RequestType, out M)
// >     alglib.eigsubspaceoocgetrequestdata(state, out X)
// >     [calculate  Y=A*X, with X=R^NxM]
// >     alglib.eigsubspaceoocsendresult(state, in Y)
// > alglib.eigsubspaceoocstop(state, out W, out Z, out Report)
//
// Inputs:
//     State           -   solver running in out-of-core mode
//     AX              -   array[N,RequestSize] or larger, leading  rectangle
//                         is filled with product A*X.
//
// ALGLIB: Copyright 16.01.2017 by Sergey Bochkanov
void eigsubspaceoocsendresult(const eigsubspacestate &state, const real_2d_array &ax);

// This  function  finalizes out-of-core  mode  of  subspace eigensolver.  It
// should be used in conjunction with other out-of-core-related functions  of
// this subspackage in a loop like below:
//
// > alglib.eigsubspaceoocstart(state)
// > while alglib.eigsubspaceooccontinue(state) do
// >     alglib.eigsubspaceoocgetrequestinfo(state, out RequestType, out M)
// >     alglib.eigsubspaceoocgetrequestdata(state, out X)
// >     [calculate  Y=A*X, with X=R^NxM]
// >     alglib.eigsubspaceoocsendresult(state, in Y)
// > alglib.eigsubspaceoocstop(state, out W, out Z, out Report)
//
// Inputs:
//     State       -   solver state
//
// Outputs:
//     W           -   array[K], depending on solver settings:
//                     * top  K  eigenvalues ordered  by  descending   -   if
//                       eigenvectors are returned in Z
//                     * zeros - if invariant subspace is returned in Z
//     Z           -   array[N,K], depending on solver settings either:
//                     * matrix of eigenvectors found
//                     * orthogonal basis of K-dimensional invariant subspace
//     Rep         -   report with additional parameters
// ALGLIB: Copyright 16.01.2017 by Sergey Bochkanov
void eigsubspaceoocstop(const eigsubspacestate &state, real_1d_array &w, real_2d_array &z, eigsubspacereport &rep);

// This  function runs eigensolver for dense NxN symmetric matrix A, given by
// upper or lower triangle.
//
// This function can not process nonsymmetric matrices.
//
// Inputs:
//     State       -   solver state
//     A           -   array[N,N], symmetric NxN matrix given by one  of  its
//                     triangles
//     IsUpper     -   whether upper or lower triangle of  A  is  given  (the
//                     other one is not referenced at all).
//
// Outputs:
//     W           -   array[K], top  K  eigenvalues ordered  by   descending
//                     of their absolute values
//     Z           -   array[N,K], matrix of eigenvectors found
//     Rep         -   report with additional parameters
//
// NOTE: internally this function allocates a copy of NxN dense A. You should
//       take it into account when working with very large matrices occupying
//       almost all RAM.
// ALGLIB: Copyright 16.01.2017 by Sergey Bochkanov
void eigsubspacesolvedenses(const eigsubspacestate &state, const real_2d_array &a, const bool isupper, real_1d_array &w, real_2d_array &z, eigsubspacereport &rep);

// This  function runs eigensolver for dense NxN symmetric matrix A, given by
// upper or lower triangle.
//
// This function can not process nonsymmetric matrices.
//
// Inputs:
//     State       -   solver state
//     A           -   NxN symmetric matrix given by one of its triangles
//     IsUpper     -   whether upper or lower triangle of  A  is  given  (the
//                     other one is not referenced at all).
//
// Outputs:
//     W           -   array[K], top  K  eigenvalues ordered  by   descending
//                     of their absolute values
//     Z           -   array[N,K], matrix of eigenvectors found
//     Rep         -   report with additional parameters
// ALGLIB: Copyright 16.01.2017 by Sergey Bochkanov
void eigsubspacesolvesparses(const eigsubspacestate &state, const sparsematrix &a, const bool isupper, real_1d_array &w, real_2d_array &z, eigsubspacereport &rep);

// Finding the eigenvalues and eigenvectors of a symmetric matrix
//
// The algorithm finds eigen pairs of a symmetric matrix by reducing it to
// tridiagonal form and using the QL/QR algorithm.
//
// Inputs:
//     A       -   symmetric matrix which is given by its upper or lower
//                 triangular part.
//                 Array whose indexes range within [0..N-1, 0..N-1].
//     N       -   size of matrix A.
//     ZNeeded -   flag controlling whether the eigenvectors are needed or not.
//                 If ZNeeded is equal to:
//                  * 0, the eigenvectors are not returned;
//                  * 1, the eigenvectors are returned.
//     IsUpper -   storage format.
//
// Outputs:
//     D       -   eigenvalues in ascending order.
//                 Array whose index ranges within [0..N-1].
//     Z       -   if ZNeeded is equal to:
//                  * 0, Z hasn't changed;
//                  * 1, Z contains the eigenvectors.
//                 Array whose indexes range within [0..N-1, 0..N-1].
//                 The eigenvectors are stored in the matrix columns.
//
// Result:
//     True, if the algorithm has converged.
//     False, if the algorithm hasn't converged (rare case).
// ALGLIB: Copyright 2005-2008 by Sergey Bochkanov
bool smatrixevd(const real_2d_array &a, const ae_int_t n, const ae_int_t zneeded, const bool isupper, real_1d_array &d, real_2d_array &z);

// Subroutine for finding the eigenvalues (and eigenvectors) of  a  symmetric
// matrix  in  a  given half open interval (A, B] by using  a  bisection  and
// inverse iteration
//
// Inputs:
//     A       -   symmetric matrix which is given by its upper or lower
//                 triangular part. Array [0..N-1, 0..N-1].
//     N       -   size of matrix A.
//     ZNeeded -   flag controlling whether the eigenvectors are needed or not.
//                 If ZNeeded is equal to:
//                  * 0, the eigenvectors are not returned;
//                  * 1, the eigenvectors are returned.
//     IsUpperA -  storage format of matrix A.
//     B1, B2 -    half open interval (B1, B2] to search eigenvalues in.
//
// Outputs:
//     M       -   number of eigenvalues found in a given half-interval (M >= 0).
//     W       -   array of the eigenvalues found.
//                 Array whose index ranges within [0..M-1].
//     Z       -   if ZNeeded is equal to:
//                  * 0, Z hasn't changed;
//                  * 1, Z contains eigenvectors.
//                 Array whose indexes range within [0..N-1, 0..M-1].
//                 The eigenvectors are stored in the matrix columns.
//
// Result:
//     True, if successful. M contains the number of eigenvalues in the given
//     half-interval (could be equal to 0), W contains the eigenvalues,
//     Z contains the eigenvectors (if needed).
//
//     False, if the bisection method subroutine wasn't able to find the
//     eigenvalues in the given interval or if the inverse iteration subroutine
//     wasn't able to find all the corresponding eigenvectors.
//     In that case, the eigenvalues and eigenvectors are not returned,
//     M is equal to 0.
// ALGLIB: Copyright 07.01.2006 by Sergey Bochkanov
bool smatrixevdr(const real_2d_array &a, const ae_int_t n, const ae_int_t zneeded, const bool isupper, const double b1, const double b2, ae_int_t &m, real_1d_array &w, real_2d_array &z);

// Subroutine for finding the eigenvalues and  eigenvectors  of  a  symmetric
// matrix with given indexes by using bisection and inverse iteration methods.
//
// Inputs:
//     A       -   symmetric matrix which is given by its upper or lower
//                 triangular part. Array whose indexes range within [0..N-1, 0..N-1].
//     N       -   size of matrix A.
//     ZNeeded -   flag controlling whether the eigenvectors are needed or not.
//                 If ZNeeded is equal to:
//                  * 0, the eigenvectors are not returned;
//                  * 1, the eigenvectors are returned.
//     IsUpperA -  storage format of matrix A.
//     I1, I2 -    index interval for searching (from I1 to I2).
//                 0 <= I1 <= I2 <= N-1.
//
// Outputs:
//     W       -   array of the eigenvalues found.
//                 Array whose index ranges within [0..I2-I1].
//     Z       -   if ZNeeded is equal to:
//                  * 0, Z hasn't changed;
//                  * 1, Z contains eigenvectors.
//                 Array whose indexes range within [0..N-1, 0..I2-I1].
//                 In that case, the eigenvectors are stored in the matrix columns.
//
// Result:
//     True, if successful. W contains the eigenvalues, Z contains the
//     eigenvectors (if needed).
//
//     False, if the bisection method subroutine wasn't able to find the
//     eigenvalues in the given interval or if the inverse iteration subroutine
//     wasn't able to find all the corresponding eigenvectors.
//     In that case, the eigenvalues and eigenvectors are not returned.
// ALGLIB: Copyright 07.01.2006 by Sergey Bochkanov
bool smatrixevdi(const real_2d_array &a, const ae_int_t n, const ae_int_t zneeded, const bool isupper, const ae_int_t i1, const ae_int_t i2, real_1d_array &w, real_2d_array &z);

// Finding the eigenvalues and eigenvectors of a Hermitian matrix
//
// The algorithm finds eigen pairs of a Hermitian matrix by  reducing  it  to
// real tridiagonal form and using the QL/QR algorithm.
//
// Inputs:
//     A       -   Hermitian matrix which is given  by  its  upper  or  lower
//                 triangular part.
//                 Array whose indexes range within [0..N-1, 0..N-1].
//     N       -   size of matrix A.
//     IsUpper -   storage format.
//     ZNeeded -   flag controlling whether the eigenvectors  are  needed  or
//                 not. If ZNeeded is equal to:
//                  * 0, the eigenvectors are not returned;
//                  * 1, the eigenvectors are returned.
//
// Outputs:
//     D       -   eigenvalues in ascending order.
//                 Array whose index ranges within [0..N-1].
//     Z       -   if ZNeeded is equal to:
//                  * 0, Z hasn't changed;
//                  * 1, Z contains the eigenvectors.
//                 Array whose indexes range within [0..N-1, 0..N-1].
//                 The eigenvectors are stored in the matrix columns.
//
// Result:
//     True, if the algorithm has converged.
//     False, if the algorithm hasn't converged (rare case).
//
// Note:
//     eigenvectors of Hermitian matrix are defined up to  multiplication  by
//     a complex number L, such that |L|=1.
// ALGLIB: Copyright 2005, 2007 March 23 by Sergey Bochkanov
bool hmatrixevd(const complex_2d_array &a, const ae_int_t n, const ae_int_t zneeded, const bool isupper, real_1d_array &d, complex_2d_array &z);

// Subroutine for finding the eigenvalues (and eigenvectors) of  a  Hermitian
// matrix  in  a  given half-interval (A, B] by using a bisection and inverse
// iteration
//
// Inputs:
//     A       -   Hermitian matrix which is given  by  its  upper  or  lower
//                 triangular  part.  Array  whose   indexes   range   within
//                 [0..N-1, 0..N-1].
//     N       -   size of matrix A.
//     ZNeeded -   flag controlling whether the eigenvectors  are  needed  or
//                 not. If ZNeeded is equal to:
//                  * 0, the eigenvectors are not returned;
//                  * 1, the eigenvectors are returned.
//     IsUpperA -  storage format of matrix A.
//     B1, B2 -    half-interval (B1, B2] to search eigenvalues in.
//
// Outputs:
//     M       -   number of eigenvalues found in a given half-interval, M >= 0
//     W       -   array of the eigenvalues found.
//                 Array whose index ranges within [0..M-1].
//     Z       -   if ZNeeded is equal to:
//                  * 0, Z hasn't changed;
//                  * 1, Z contains eigenvectors.
//                 Array whose indexes range within [0..N-1, 0..M-1].
//                 The eigenvectors are stored in the matrix columns.
//
// Result:
//     True, if successful. M contains the number of eigenvalues in the given
//     half-interval (could be equal to 0), W contains the eigenvalues,
//     Z contains the eigenvectors (if needed).
//
//     False, if the bisection method subroutine  wasn't  able  to  find  the
//     eigenvalues  in  the  given  interval  or  if  the  inverse  iteration
//     subroutine  wasn't  able  to  find all the corresponding eigenvectors.
//     In that case, the eigenvalues and eigenvectors are not returned, M  is
//     equal to 0.
//
// Note:
//     eigen vectors of Hermitian matrix are defined up to multiplication  by
//     a complex number L, such as |L|=1.
// ALGLIB: Copyright 07.01.2006, 24.03.2007 by Sergey Bochkanov
bool hmatrixevdr(const complex_2d_array &a, const ae_int_t n, const ae_int_t zneeded, const bool isupper, const double b1, const double b2, ae_int_t &m, real_1d_array &w, complex_2d_array &z);

// Subroutine for finding the eigenvalues and  eigenvectors  of  a  Hermitian
// matrix with given indexes by using bisection and inverse iteration methods
//
// Inputs:
//     A       -   Hermitian matrix which is given  by  its  upper  or  lower
//                 triangular part.
//                 Array whose indexes range within [0..N-1, 0..N-1].
//     N       -   size of matrix A.
//     ZNeeded -   flag controlling whether the eigenvectors  are  needed  or
//                 not. If ZNeeded is equal to:
//                  * 0, the eigenvectors are not returned;
//                  * 1, the eigenvectors are returned.
//     IsUpperA -  storage format of matrix A.
//     I1, I2 -    index interval for searching (from I1 to I2).
//                 0 <= I1 <= I2 <= N-1.
//
// Outputs:
//     W       -   array of the eigenvalues found.
//                 Array whose index ranges within [0..I2-I1].
//     Z       -   if ZNeeded is equal to:
//                  * 0, Z hasn't changed;
//                  * 1, Z contains eigenvectors.
//                 Array whose indexes range within [0..N-1, 0..I2-I1].
//                 In  that  case,  the eigenvectors are stored in the matrix
//                 columns.
//
// Result:
//     True, if successful. W contains the eigenvalues, Z contains the
//     eigenvectors (if needed).
//
//     False, if the bisection method subroutine  wasn't  able  to  find  the
//     eigenvalues  in  the  given  interval  or  if  the  inverse  iteration
//     subroutine wasn't able to find  all  the  corresponding  eigenvectors.
//     In that case, the eigenvalues and eigenvectors are not returned.
//
// Note:
//     eigen vectors of Hermitian matrix are defined up to multiplication  by
//     a complex number L, such as |L|=1.
// ALGLIB: Copyright 07.01.2006, 24.03.2007 by Sergey Bochkanov
bool hmatrixevdi(const complex_2d_array &a, const ae_int_t n, const ae_int_t zneeded, const bool isupper, const ae_int_t i1, const ae_int_t i2, real_1d_array &w, complex_2d_array &z);

// Finding the eigenvalues and eigenvectors of a tridiagonal symmetric matrix
//
// The algorithm finds the eigen pairs of a tridiagonal symmetric matrix by
// using an QL/QR algorithm with implicit shifts.
//
// Inputs:
//     D       -   the main diagonal of a tridiagonal matrix.
//                 Array whose index ranges within [0..N-1].
//     E       -   the secondary diagonal of a tridiagonal matrix.
//                 Array whose index ranges within [0..N-2].
//     N       -   size of matrix A.
//     ZNeeded -   flag controlling whether the eigenvectors are needed or not.
//                 If ZNeeded is equal to:
//                  * 0, the eigenvectors are not needed;
//                  * 1, the eigenvectors of a tridiagonal matrix
//                    are multiplied by the square matrix Z. It is used if the
//                    tridiagonal matrix is obtained by the similarity
//                    transformation of a symmetric matrix;
//                  * 2, the eigenvectors of a tridiagonal matrix replace the
//                    square matrix Z;
//                  * 3, matrix Z contains the first row of the eigenvectors
//                    matrix.
//     Z       -   if ZNeeded=1, Z contains the square matrix by which the
//                 eigenvectors are multiplied.
//                 Array whose indexes range within [0..N-1, 0..N-1].
//
// Outputs:
//     D       -   eigenvalues in ascending order.
//                 Array whose index ranges within [0..N-1].
//     Z       -   if ZNeeded is equal to:
//                  * 0, Z hasn't changed;
//                  * 1, Z contains the product of a given matrix (from the left)
//                    and the eigenvectors matrix (from the right);
//                  * 2, Z contains the eigenvectors.
//                  * 3, Z contains the first row of the eigenvectors matrix.
//                 If ZNeeded < 3, Z is the array whose indexes range within [0..N-1, 0..N-1].
//                 In that case, the eigenvectors are stored in the matrix columns.
//                 If ZNeeded=3, Z is the array whose indexes range within [0..0, 0..N-1].
//
// Result:
//     True, if the algorithm has converged.
//     False, if the algorithm hasn't converged.
//
//   -- LAPACK routine (version 3.0) --
//      Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd.,
//      Courant Institute, Argonne National Lab, and Rice University
//      September 30, 1994
bool smatrixtdevd(real_1d_array &d, const real_1d_array &e, const ae_int_t n, const ae_int_t zneeded, real_2d_array &z);

// Subroutine for finding the tridiagonal matrix eigenvalues/vectors in a
// given half-interval (A, B] by using bisection and inverse iteration.
//
// Inputs:
//     D       -   the main diagonal of a tridiagonal matrix.
//                 Array whose index ranges within [0..N-1].
//     E       -   the secondary diagonal of a tridiagonal matrix.
//                 Array whose index ranges within [0..N-2].
//     N       -   size of matrix, N >= 0.
//     ZNeeded -   flag controlling whether the eigenvectors are needed or not.
//                 If ZNeeded is equal to:
//                  * 0, the eigenvectors are not needed;
//                  * 1, the eigenvectors of a tridiagonal matrix are multiplied
//                    by the square matrix Z. It is used if the tridiagonal
//                    matrix is obtained by the similarity transformation
//                    of a symmetric matrix.
//                  * 2, the eigenvectors of a tridiagonal matrix replace matrix Z.
//     A, B    -   half-interval (A, B] to search eigenvalues in.
//     Z       -   if ZNeeded is equal to:
//                  * 0, Z isn't used and remains unchanged;
//                  * 1, Z contains the square matrix (array whose indexes range
//                    within [0..N-1, 0..N-1]) which reduces the given symmetric
//                    matrix to tridiagonal form;
//                  * 2, Z isn't used (but changed on the exit).
//
// Outputs:
//     D       -   array of the eigenvalues found.
//                 Array whose index ranges within [0..M-1].
//     M       -   number of eigenvalues found in the given half-interval (M >= 0).
//     Z       -   if ZNeeded is equal to:
//                  * 0, doesn't contain any information;
//                  * 1, contains the product of a given NxN matrix Z (from the
//                    left) and NxM matrix of the eigenvectors found (from the
//                    right). Array whose indexes range within [0..N-1, 0..M-1].
//                  * 2, contains the matrix of the eigenvectors found.
//                    Array whose indexes range within [0..N-1, 0..M-1].
//
// Result:
//
//     True, if successful. In that case, M contains the number of eigenvalues
//     in the given half-interval (could be equal to 0), D contains the eigenvalues,
//     Z contains the eigenvectors (if needed).
//     It should be noted that the subroutine changes the size of arrays D and Z.
//
//     False, if the bisection method subroutine wasn't able to find the
//     eigenvalues in the given interval or if the inverse iteration subroutine
//     wasn't able to find all the corresponding eigenvectors. In that case,
//     the eigenvalues and eigenvectors are not returned, M is equal to 0.
// ALGLIB: Copyright 31.03.2008 by Sergey Bochkanov
bool smatrixtdevdr(real_1d_array &d, const real_1d_array &e, const ae_int_t n, const ae_int_t zneeded, const double a, const double b, ae_int_t &m, real_2d_array &z);

// Subroutine for finding tridiagonal matrix eigenvalues/vectors with given
// indexes (in ascending order) by using the bisection and inverse iteraion.
//
// Inputs:
//     D       -   the main diagonal of a tridiagonal matrix.
//                 Array whose index ranges within [0..N-1].
//     E       -   the secondary diagonal of a tridiagonal matrix.
//                 Array whose index ranges within [0..N-2].
//     N       -   size of matrix. N >= 0.
//     ZNeeded -   flag controlling whether the eigenvectors are needed or not.
//                 If ZNeeded is equal to:
//                  * 0, the eigenvectors are not needed;
//                  * 1, the eigenvectors of a tridiagonal matrix are multiplied
//                    by the square matrix Z. It is used if the
//                    tridiagonal matrix is obtained by the similarity transformation
//                    of a symmetric matrix.
//                  * 2, the eigenvectors of a tridiagonal matrix replace
//                    matrix Z.
//     I1, I2  -   index interval for searching (from I1 to I2).
//                 0 <= I1 <= I2 <= N-1.
//     Z       -   if ZNeeded is equal to:
//                  * 0, Z isn't used and remains unchanged;
//                  * 1, Z contains the square matrix (array whose indexes range within [0..N-1, 0..N-1])
//                    which reduces the given symmetric matrix to  tridiagonal form;
//                  * 2, Z isn't used (but changed on the exit).
//
// Outputs:
//     D       -   array of the eigenvalues found.
//                 Array whose index ranges within [0..I2-I1].
//     Z       -   if ZNeeded is equal to:
//                  * 0, doesn't contain any information;
//                  * 1, contains the product of a given NxN matrix Z (from the left) and
//                    Nx(I2-I1) matrix of the eigenvectors found (from the right).
//                    Array whose indexes range within [0..N-1, 0..I2-I1].
//                  * 2, contains the matrix of the eigenvalues found.
//                    Array whose indexes range within [0..N-1, 0..I2-I1].
//
//
// Result:
//
//     True, if successful. In that case, D contains the eigenvalues,
//     Z contains the eigenvectors (if needed).
//     It should be noted that the subroutine changes the size of arrays D and Z.
//
//     False, if the bisection method subroutine wasn't able to find the eigenvalues
//     in the given interval or if the inverse iteration subroutine wasn't able
//     to find all the corresponding eigenvectors. In that case, the eigenvalues
//     and eigenvectors are not returned.
// ALGLIB: Copyright 25.12.2005 by Sergey Bochkanov
bool smatrixtdevdi(real_1d_array &d, const real_1d_array &e, const ae_int_t n, const ae_int_t zneeded, const ae_int_t i1, const ae_int_t i2, real_2d_array &z);

// Finding eigenvalues and eigenvectors of a general (unsymmetric) matrix
//
// The algorithm finds eigenvalues and eigenvectors of a general matrix by
// using the QR algorithm with multiple shifts. The algorithm can find
// eigenvalues and both left and right eigenvectors.
//
// The right eigenvector is a vector x such that A*x = w*x, and the left
// eigenvector is a vector y such that y'*A = w*y' (here y' implies a complex
// conjugate transposition of vector y).
//
// Inputs:
//     A       -   matrix. Array whose indexes range within [0..N-1, 0..N-1].
//     N       -   size of matrix A.
//     VNeeded -   flag controlling whether eigenvectors are needed or not.
//                 If VNeeded is equal to:
//                  * 0, eigenvectors are not returned;
//                  * 1, right eigenvectors are returned;
//                  * 2, left eigenvectors are returned;
//                  * 3, both left and right eigenvectors are returned.
//
// Outputs:
//     WR      -   real parts of eigenvalues.
//                 Array whose index ranges within [0..N-1].
//     WR      -   imaginary parts of eigenvalues.
//                 Array whose index ranges within [0..N-1].
//     VL, VR  -   arrays of left and right eigenvectors (if they are needed).
//                 If WI[i]=0, the respective eigenvalue is a real number,
//                 and it corresponds to the column number I of matrices VL/VR.
//                 If WI[i] > 0, we have a pair of complex conjugate numbers with
//                 positive and negative imaginary parts:
//                     the first eigenvalue WR[i] + sqrt(-1)*WI[i];
//                     the second eigenvalue WR[i+1] + sqrt(-1)*WI[i+1];
//                     WI[i] > 0
//                     WI[i+1] = -WI[i] < 0
//                 In that case, the eigenvector  corresponding to the first
//                 eigenvalue is located in i and i+1 columns of matrices
//                 VL/VR (the column number i contains the real part, and the
//                 column number i+1 contains the imaginary part), and the vector
//                 corresponding to the second eigenvalue is a complex conjugate to
//                 the first vector.
//                 Arrays whose indexes range within [0..N-1, 0..N-1].
//
// Result:
//     True, if the algorithm has converged.
//     False, if the algorithm has not converged.
//
// Note 1:
//     Some users may ask the following question: what if WI[N-1] > 0?
//     WI[N] must contain an eigenvalue which is complex conjugate to the
//     N-th eigenvalue, but the array has only size N?
//     The answer is as follows: such a situation cannot occur because the
//     algorithm finds a pairs of eigenvalues, therefore, if WI[i] > 0, I is
//     strictly less than N-1.
//
// Note 2:
//     The algorithm performance depends on the value of the internal parameter
//     NS of the InternalSchurDecomposition subroutine which defines the number
//     of shifts in the QR algorithm (similarly to the block width in block-matrix
//     algorithms of linear algebra). If you require maximum performance
//     on your machine, it is recommended to adjust this parameter manually.
//
//
// See also the InternalTREVC subroutine.
//
// The algorithm is based on the LAPACK 3.0 library.
bool rmatrixevd(const real_2d_array &a, const ae_int_t n, const ae_int_t vneeded, real_1d_array &wr, real_1d_array &wi, real_2d_array &vl, real_2d_array &vr);
} // end of namespace alglib

// === SCHUR Package ===
// Depends on: ORTFAC, HSSCHUR
namespace alglib_impl {
bool rmatrixschur(RMatrix *a, ae_int_t n, RMatrix *s);
} // end of namespace alglib_impl

namespace alglib {
// Subroutine performing the Schur decomposition of a general matrix by using
// the QR algorithm with multiple shifts.
//
// The source matrix A is represented as S'*A*S = T, where S is an orthogonal
// matrix (Schur vectors), T - upper quasi-triangular matrix (with blocks of
// sizes 1x1 and 2x2 on the main diagonal).
//
// Inputs:
//     A   -   matrix to be decomposed.
//             Array whose indexes range within [0..N-1, 0..N-1].
//     N   -   size of A, N >= 0.
//
//
// Outputs:
//     A   -   contains matrix T.
//             Array whose indexes range within [0..N-1, 0..N-1].
//     S   -   contains Schur vectors.
//             Array whose indexes range within [0..N-1, 0..N-1].
//
// Note 1:
//     The block structure of matrix T can be easily recognized: since all
//     the elements below the blocks are zeros, the elements a[i+1,i] which
//     are equal to 0 show the block border.
//
// Note 2:
//     The algorithm performance depends on the value of the internal parameter
//     NS of the InternalSchurDecomposition subroutine which defines the number
//     of shifts in the QR algorithm (similarly to the block width in block-matrix
//     algorithms in linear algebra). If you require maximum performance on
//     your machine, it is recommended to adjust this parameter manually.
//
// Result:
//     True,
//         if the algorithm has converged and parameters A and S contain the result.
//     False,
//         if the algorithm has not converged.
//
// Algorithm implemented on the basis of the DHSEQR subroutine (LAPACK 3.0 library).
bool rmatrixschur(real_2d_array &a, const ae_int_t n, real_2d_array &s);
} // end of namespace alglib

// === SPDGEVD Package ===
// Depends on: MATINV, EVD
namespace alglib_impl {
bool smatrixgevd(RMatrix *a, ae_int_t n, bool isuppera, RMatrix *b, bool isupperb, ae_int_t zneeded, ae_int_t problemtype, RVector *d, RMatrix *z);
bool smatrixgevdreduce(RMatrix *a, ae_int_t n, bool isuppera, RMatrix *b, bool isupperb, ae_int_t problemtype, RMatrix *r, bool *isupperr);
} // end of namespace alglib_impl

namespace alglib {
// Algorithm for solving the following generalized symmetric positive-definite
// eigenproblem:
//     A*x = lambda*B*x (1) or
//     A*B*x = lambda*x (2) or
//     B*A*x = lambda*x (3).
// where A is a symmetric matrix, B - symmetric positive-definite matrix.
// The problem is solved by reducing it to an ordinary  symmetric  eigenvalue
// problem.
//
// Inputs:
//     A           -   symmetric matrix which is given by its upper or lower
//                     triangular part.
//                     Array whose indexes range within [0..N-1, 0..N-1].
//     N           -   size of matrices A and B.
//     IsUpperA    -   storage format of matrix A.
//     B           -   symmetric positive-definite matrix which is given by
//                     its upper or lower triangular part.
//                     Array whose indexes range within [0..N-1, 0..N-1].
//     IsUpperB    -   storage format of matrix B.
//     ZNeeded     -   if ZNeeded is equal to:
//                      * 0, the eigenvectors are not returned;
//                      * 1, the eigenvectors are returned.
//     ProblemType -   if ProblemType is equal to:
//                      * 1, the following problem is solved: A*x = lambda*B*x;
//                      * 2, the following problem is solved: A*B*x = lambda*x;
//                      * 3, the following problem is solved: B*A*x = lambda*x.
//
// Outputs:
//     D           -   eigenvalues in ascending order.
//                     Array whose index ranges within [0..N-1].
//     Z           -   if ZNeeded is equal to:
//                      * 0, Z hasn't changed;
//                      * 1, Z contains eigenvectors.
//                     Array whose indexes range within [0..N-1, 0..N-1].
//                     The eigenvectors are stored in matrix columns. It should
//                     be noted that the eigenvectors in such problems do not
//                     form an orthogonal system.
//
// Result:
//     True, if the problem was solved successfully.
//     False, if the error occurred during the Cholesky decomposition of matrix
//     B (the matrix isn't positive-definite) or during the work of the iterative
//     algorithm for solving the symmetric eigenproblem.
//
// See also the GeneralizedSymmetricDefiniteEVDReduce subroutine.
// ALGLIB: Copyright 01.28.2006 by Sergey Bochkanov
bool smatrixgevd(const real_2d_array &a, const ae_int_t n, const bool isuppera, const real_2d_array &b, const bool isupperb, const ae_int_t zneeded, const ae_int_t problemtype, real_1d_array &d, real_2d_array &z);

// Algorithm for reduction of the following generalized symmetric positive-
// definite eigenvalue problem:
//     A*x = lambda*B*x (1) or
//     A*B*x = lambda*x (2) or
//     B*A*x = lambda*x (3)
// to the symmetric eigenvalues problem C*y = lambda*y (eigenvalues of this and
// the given problems are the same, and the eigenvectors of the given problem
// could be obtained by multiplying the obtained eigenvectors by the
// transformation matrix x = R*y).
//
// Here A is a symmetric matrix, B - symmetric positive-definite matrix.
//
// Inputs:
//     A           -   symmetric matrix which is given by its upper or lower
//                     triangular part.
//                     Array whose indexes range within [0..N-1, 0..N-1].
//     N           -   size of matrices A and B.
//     IsUpperA    -   storage format of matrix A.
//     B           -   symmetric positive-definite matrix which is given by
//                     its upper or lower triangular part.
//                     Array whose indexes range within [0..N-1, 0..N-1].
//     IsUpperB    -   storage format of matrix B.
//     ProblemType -   if ProblemType is equal to:
//                      * 1, the following problem is solved: A*x = lambda*B*x;
//                      * 2, the following problem is solved: A*B*x = lambda*x;
//                      * 3, the following problem is solved: B*A*x = lambda*x.
//
// Outputs:
//     A           -   symmetric matrix which is given by its upper or lower
//                     triangle depending on IsUpperA. Contains matrix C.
//                     Array whose indexes range within [0..N-1, 0..N-1].
//     R           -   upper triangular or low triangular transformation matrix
//                     which is used to obtain the eigenvectors of a given problem
//                     as the product of eigenvectors of C (from the right) and
//                     matrix R (from the left). If the matrix is upper
//                     triangular, the elements below the main diagonal
//                     are equal to 0 (and vice versa). Thus, we can perform
//                     the multiplication without taking into account the
//                     internal structure (which is an easier though less
//                     effective way).
//                     Array whose indexes range within [0..N-1, 0..N-1].
//     IsUpperR    -   type of matrix R (upper or lower triangular).
//
// Result:
//     True, if the problem was reduced successfully.
//     False, if the error occurred during the Cholesky decomposition of
//         matrix B (the matrix is not positive-definite).
// ALGLIB: Copyright 01.28.2006 by Sergey Bochkanov
bool smatrixgevdreduce(real_2d_array &a, const ae_int_t n, const bool isuppera, const real_2d_array &b, const bool isupperb, const ae_int_t problemtype, real_2d_array &r, bool &isupperr);
} // end of namespace alglib

// === INVERSEUPDATE Package ===
namespace alglib_impl {
void rmatrixinvupdatesimple(RMatrix *inva, ae_int_t n, ae_int_t updrow, ae_int_t updcolumn, double updval);
void rmatrixinvupdaterow(RMatrix *inva, ae_int_t n, ae_int_t updrow, RVector *v);
void rmatrixinvupdatecolumn(RMatrix *inva, ae_int_t n, ae_int_t updcolumn, RVector *u);
void rmatrixinvupdateuv(RMatrix *inva, ae_int_t n, RVector *u, RVector *v);
} // end of namespace alglib_impl

namespace alglib {
// Inverse matrix update by the Sherman-Morrison formula
//
// The algorithm updates matrix A^-1 when adding a number to an element
// of matrix A.
//
// Inputs:
//     InvA    -   inverse of matrix A.
//                 Array whose indexes range within [0..N-1, 0..N-1].
//     N       -   size of matrix A.
//     UpdRow  -   row where the element to be updated is stored.
//     UpdColumn - column where the element to be updated is stored.
//     UpdVal  -   a number to be added to the element.
//
//
// Outputs:
//     InvA    -   inverse of modified matrix A.
// ALGLIB: Copyright 2005 by Sergey Bochkanov
void rmatrixinvupdatesimple(real_2d_array &inva, const ae_int_t n, const ae_int_t updrow, const ae_int_t updcolumn, const double updval);

// Inverse matrix update by the Sherman-Morrison formula
//
// The algorithm updates matrix A^-1 when adding a vector to a row
// of matrix A.
//
// Inputs:
//     InvA    -   inverse of matrix A.
//                 Array whose indexes range within [0..N-1, 0..N-1].
//     N       -   size of matrix A.
//     UpdRow  -   the row of A whose vector V was added.
//                 0 <= Row <= N-1
//     V       -   the vector to be added to a row.
//                 Array whose index ranges within [0..N-1].
//
// Outputs:
//     InvA    -   inverse of modified matrix A.
// ALGLIB: Copyright 2005 by Sergey Bochkanov
void rmatrixinvupdaterow(real_2d_array &inva, const ae_int_t n, const ae_int_t updrow, const real_1d_array &v);

// Inverse matrix update by the Sherman-Morrison formula
//
// The algorithm updates matrix A^-1 when adding a vector to a column
// of matrix A.
//
// Inputs:
//     InvA        -   inverse of matrix A.
//                     Array whose indexes range within [0..N-1, 0..N-1].
//     N           -   size of matrix A.
//     UpdColumn   -   the column of A whose vector U was added.
//                     0 <= UpdColumn <= N-1
//     U           -   the vector to be added to a column.
//                     Array whose index ranges within [0..N-1].
//
// Outputs:
//     InvA        -   inverse of modified matrix A.
// ALGLIB: Copyright 2005 by Sergey Bochkanov
void rmatrixinvupdatecolumn(real_2d_array &inva, const ae_int_t n, const ae_int_t updcolumn, const real_1d_array &u);

// Inverse matrix update by the Sherman-Morrison formula
//
// The algorithm computes the inverse of matrix A+u*v' by using the given matrix
// A^-1 and the vectors u and v.
//
// Inputs:
//     InvA    -   inverse of matrix A.
//                 Array whose indexes range within [0..N-1, 0..N-1].
//     N       -   size of matrix A.
//     U       -   the vector modifying the matrix.
//                 Array whose index ranges within [0..N-1].
//     V       -   the vector modifying the matrix.
//                 Array whose index ranges within [0..N-1].
//
// Outputs:
//     InvA - inverse of matrix A + u*v'.
// ALGLIB: Copyright 2005 by Sergey Bochkanov
void rmatrixinvupdateuv(real_2d_array &inva, const ae_int_t n, const real_1d_array &u, const real_1d_array &v);
} // end of namespace alglib

// === MATDET Package ===
// Depends on: TRFAC
namespace alglib_impl {
double rmatrixludet(RMatrix *a, ZVector *pivots, ae_int_t n);
double rmatrixdet(RMatrix *a, ae_int_t n);
ae_complex cmatrixludet(CMatrix *a, ZVector *pivots, ae_int_t n);
ae_complex cmatrixdet(CMatrix *a, ae_int_t n);
double spdmatrixcholeskydet(RMatrix *a, ae_int_t n);
double spdmatrixdet(RMatrix *a, ae_int_t n, bool isupper);
} // end of namespace alglib_impl

namespace alglib {
// Determinant calculation of the matrix given by its LU decomposition.
//
// Inputs:
//     A       -   LU decomposition of the matrix (output of
//                 RMatrixLU subroutine).
//     Pivots  -   table of permutations which were made during
//                 the LU decomposition.
//                 Output of RMatrixLU subroutine.
//     N       -   (optional) size of matrix A:
//                 * if given, only principal NxN submatrix is processed and
//                   overwritten. other elements are unchanged.
//                 * if not given, automatically determined from matrix size
//                   (A must be square matrix)
//
// Result: matrix determinant.
// ALGLIB: Copyright 2005 by Sergey Bochkanov
double rmatrixludet(const real_2d_array &a, const integer_1d_array &pivots, const ae_int_t n);
double rmatrixludet(const real_2d_array &a, const integer_1d_array &pivots);

// Calculation of the determinant of a general matrix
//
// Inputs:
//     A       -   matrix, array[0..N-1, 0..N-1]
//     N       -   (optional) size of matrix A:
//                 * if given, only principal NxN submatrix is processed and
//                   overwritten. other elements are unchanged.
//                 * if not given, automatically determined from matrix size
//                   (A must be square matrix)
//
// Result: determinant of matrix A.
// ALGLIB: Copyright 2005 by Sergey Bochkanov
double rmatrixdet(const real_2d_array &a, const ae_int_t n);
double rmatrixdet(const real_2d_array &a);

// Determinant calculation of the matrix given by its LU decomposition.
//
// Inputs:
//     A       -   LU decomposition of the matrix (output of
//                 RMatrixLU subroutine).
//     Pivots  -   table of permutations which were made during
//                 the LU decomposition.
//                 Output of RMatrixLU subroutine.
//     N       -   (optional) size of matrix A:
//                 * if given, only principal NxN submatrix is processed and
//                   overwritten. other elements are unchanged.
//                 * if not given, automatically determined from matrix size
//                   (A must be square matrix)
//
// Result: matrix determinant.
// ALGLIB: Copyright 2005 by Sergey Bochkanov
complex cmatrixludet(const complex_2d_array &a, const integer_1d_array &pivots, const ae_int_t n);
complex cmatrixludet(const complex_2d_array &a, const integer_1d_array &pivots);

// Calculation of the determinant of a general matrix
//
// Inputs:
//     A       -   matrix, array[0..N-1, 0..N-1]
//     N       -   (optional) size of matrix A:
//                 * if given, only principal NxN submatrix is processed and
//                   overwritten. other elements are unchanged.
//                 * if not given, automatically determined from matrix size
//                   (A must be square matrix)
//
// Result: determinant of matrix A.
// ALGLIB: Copyright 2005 by Sergey Bochkanov
complex cmatrixdet(const complex_2d_array &a, const ae_int_t n);
complex cmatrixdet(const complex_2d_array &a);

// Determinant calculation of the matrix given by the Cholesky decomposition.
//
// Inputs:
//     A       -   Cholesky decomposition,
//                 output of SMatrixCholesky subroutine.
//     N       -   (optional) size of matrix A:
//                 * if given, only principal NxN submatrix is processed and
//                   overwritten. other elements are unchanged.
//                 * if not given, automatically determined from matrix size
//                   (A must be square matrix)
//
// As the determinant is equal to the product of squares of diagonal elements,
// it's not necessary to specify which triangle - lower or upper - the matrix
// is stored in.
//
// Result:
//     matrix determinant.
// ALGLIB: Copyright 2005-2008 by Sergey Bochkanov
double spdmatrixcholeskydet(const real_2d_array &a, const ae_int_t n);
double spdmatrixcholeskydet(const real_2d_array &a);

// Determinant calculation of the symmetric positive definite matrix.
//
// Inputs:
//     A       -   matrix. Array with elements [0..N-1, 0..N-1].
//     N       -   (optional) size of matrix A:
//                 * if given, only principal NxN submatrix is processed and
//                   overwritten. other elements are unchanged.
//                 * if not given, automatically determined from matrix size
//                   (A must be square matrix)
//     IsUpper -   (optional) storage type:
//                 * if True, symmetric matrix  A  is  given  by  its  upper
//                   triangle, and the lower triangle isn't used/changed  by
//                   function
//                 * if False, symmetric matrix  A  is  given  by  its lower
//                   triangle, and the upper triangle isn't used/changed  by
//                   function
//                 * if not given, both lower and upper  triangles  must  be
//                   filled.
//
// Result:
//     determinant of matrix A.
//     If matrix A is not positive definite, exception is thrown.
// ALGLIB: Copyright 2005-2008 by Sergey Bochkanov
double spdmatrixdet(const real_2d_array &a, const ae_int_t n, const bool isupper);
double spdmatrixdet(const real_2d_array &a);
} // end of namespace alglib

#endif // OnceOnly
