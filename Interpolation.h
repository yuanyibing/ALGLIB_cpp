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
#ifndef OnceOnlyInterpolation_h
#define OnceOnlyInterpolation_h

#include "Integration.h"
#include "Optimization.h"

// === IDW Package ===
// Depends on: (AlgLibMisc) HQRND, NEARESTNEIGHBOR
// Depends on: (LinAlg) ABLAS
namespace alglib_impl {
struct idwcalcbuffer {
   ae_vector x;
   ae_vector y;
   ae_vector tsyw;
   ae_vector tsw;
   ae_matrix tsxy;
   ae_vector tsdist;
   kdtreerequestbuffer requestbuffer;
};
void idwcalcbuffer_init(void *_p, bool make_automatic);
void idwcalcbuffer_copy(void *_dst, void *_src, bool make_automatic);
void idwcalcbuffer_free(void *_p, bool make_automatic);

struct idwmodel {
   ae_int_t nx;
   ae_int_t ny;
   ae_vector globalprior;
   ae_int_t algotype;
   ae_int_t nlayers;
   double r0;
   double rdecay;
   double lambda0;
   double lambdalast;
   double lambdadecay;
   double shepardp;
   kdtree tree;
   ae_int_t npoints;
   ae_vector shepardxy;
   idwcalcbuffer buffer;
};
void idwmodel_init(void *_p, bool make_automatic);
void idwmodel_copy(void *_dst, void *_src, bool make_automatic);
void idwmodel_free(void *_p, bool make_automatic);

struct idwbuilder {
   ae_int_t priortermtype;
   ae_vector priortermval;
   ae_int_t algotype;
   ae_int_t nlayers;
   double r0;
   double rdecay;
   double lambda0;
   double lambdalast;
   double lambdadecay;
   double shepardp;
   ae_vector xy;
   ae_int_t npoints;
   ae_int_t nx;
   ae_int_t ny;
   ae_matrix tmpxy;
   ae_matrix tmplayers;
   ae_vector tmptags;
   ae_vector tmpdist;
   ae_vector tmpx;
   ae_vector tmpwy;
   ae_vector tmpw;
   kdtree tmptree;
   ae_vector tmpmean;
};
void idwbuilder_init(void *_p, bool make_automatic);
void idwbuilder_copy(void *_dst, void *_src, bool make_automatic);
void idwbuilder_free(void *_p, bool make_automatic);

struct idwreport {
   double rmserror;
   double avgerror;
   double maxerror;
   double r2;
};
void idwreport_init(void *_p, bool make_automatic);
void idwreport_copy(void *_dst, void *_src, bool make_automatic);
void idwreport_free(void *_p, bool make_automatic);
void idwalloc(ae_serializer *s, idwmodel *model);
void idwserialize(ae_serializer *s, idwmodel *model);
void idwunserialize(ae_serializer *s, idwmodel *model);

void idwcreatecalcbuffer(idwmodel *s, idwcalcbuffer *buf);
void idwbuildercreate(ae_int_t nx, ae_int_t ny, idwbuilder *state);
void idwbuildersetnlayers(idwbuilder *state, ae_int_t nlayers);
void idwbuildersetpoints(idwbuilder *state, RMatrix *xy, ae_int_t n);
void idwbuildersetalgomstab(idwbuilder *state, double srad);
void idwbuildersetalgotextbookshepard(idwbuilder *state, double p);
void idwbuildersetalgotextbookmodshepard(idwbuilder *state, double r);
void idwbuildersetuserterm(idwbuilder *state, double v);
void idwbuildersetconstterm(idwbuilder *state);
void idwbuildersetzeroterm(idwbuilder *state);
double idwcalc1(idwmodel *s, double x0);
double idwcalc2(idwmodel *s, double x0, double x1);
double idwcalc3(idwmodel *s, double x0, double x1, double x2);
void idwcalc(idwmodel *s, RVector *x, RVector *y);
void idwcalcbuf(idwmodel *s, RVector *x, RVector *y);
void idwtscalcbuf(idwmodel *s, idwcalcbuffer *buf, RVector *x, RVector *y);
void idwfit(idwbuilder *state, idwmodel *model, idwreport *rep);
} // end of namespace alglib_impl

namespace alglib {
// Buffer  object  which  is  used  to  perform  evaluation  requests  in  the
// multithreaded mode (multiple threads working with same IDW object).
//
// This object should be created with idwcreatecalcbuffer().
DecClass(idwcalcbuffer, EndD);

// IDW (Inverse Distance Weighting) model object.
DecClass(idwmodel, EndD);

// Builder object used to generate IDW (Inverse Distance Weighting) model.
DecClass(idwbuilder, EndD);

// IDW fitting report:
//     rmserror        RMS error
//     avgerror        average error
//     maxerror        maximum error
//     r2              coefficient of determination,  R-squared, 1-RSS/TSS
DecClass(idwreport, double &rmserror; double &avgerror; double &maxerror; double &r2;);

// These functions serialize a data structure to a C++ string or stream.
// * serialization can be freely moved across 32-bit and 64-bit systems,
//   and different byte orders. For example, you can serialize a string
//   on a SPARC and unserialize it on an x86.
// * ALGLIB++ serialization is compatible with serialization in ALGLIB,
//   in both directions.
// Important properties of s_out:
// * it contains alphanumeric characters, dots, underscores, minus signs
// * these symbols are grouped into words, which are separated by spaces
//   and Windows-style (CR+LF) newlines
void idwserialize(idwmodel &obj, std::string &s_out);
void idwserialize(idwmodel &obj, std::ostream &s_out);

// These functions unserialize a data structure from a C++ string or stream.
// Important properties of s_in:
// * any combination of spaces, tabs, Windows or Unix stype newlines can
//   be used as separators, so as to allow flexible reformatting of the
//   stream or string from text or XML files.
// * But you should not insert separators into the middle of the "words"
//   nor you should change case of letters.
void idwunserialize(const std::string &s_in, idwmodel &obj);
void idwunserialize(const std::istream &s_in, idwmodel &obj);

// This function creates buffer  structure  which  can  be  used  to  perform
// parallel  IDW  model  evaluations  (with  one  IDW  model  instance  being
// used from multiple threads, as long as  different  threads  use  different
// instances of buffer).
//
// This buffer object can be used with  idwtscalcbuf()  function  (here  "ts"
// stands for "thread-safe", "buf" is a suffix which denotes  function  which
// reuses previously allocated output space).
//
// How to use it:
// * create IDW model structure or load it from file
// * call idwcreatecalcbuffer(), once per thread working with IDW model  (you
//   should call this function only AFTER model initialization, see below for
//   more information)
// * call idwtscalcbuf() from different threads,  with  each  thread  working
//   with its own copy of buffer object.
//
// Inputs:
//     S           -   IDW model
//
// Outputs:
//     Buf         -   external buffer.
//
//
// IMPORTANT: buffer object should be used only with  IDW model object  which
//            was used to initialize buffer. Any attempt to use buffer   with
//            different object is dangerous - you may  get  memory  violation
//            error because sizes of internal arrays do not fit to dimensions
//            of the IDW structure.
//
// IMPORTANT: you  should  call  this function only for model which was built
//            with model builder (or unserialized from file). Sizes  of  some
//            internal structures are determined only after model  is  built,
//            so buffer object created before model construction  stage  will
//            be useless (and any attempt to use it will result in exception).
// ALGLIB: Copyright 22.10.2018 by Sergey Bochkanov
void idwcreatecalcbuffer(const idwmodel &s, idwcalcbuffer &buf);

// This subroutine creates builder object used  to  generate IDW  model  from
// irregularly sampled (scattered) dataset.  Multidimensional  scalar/vector-
// -valued are supported.
//
// Builder object is used to fit model to data as follows:
// * builder object is created with idwbuildercreate() function
// * dataset is added with idwbuildersetpoints() function
// * one of the modern IDW algorithms is chosen with either:
//   * idwbuildersetalgomstab()            - Multilayer STABilized algorithm (interpolation)
//   Alternatively, one of the textbook algorithms can be chosen (not recommended):
//   * idwbuildersetalgotextbookshepard()  - textbook Shepard algorithm
//   * idwbuildersetalgotextbookmodshepard()-textbook modified Shepard algorithm
// * finally, model construction is performed with idwfit() function.
//
// Inputs:
//     NX  -   dimensionality of the argument, NX >= 1
//     NY  -   dimensionality of the function being modeled, NY >= 1;
//             NY=1 corresponds to classic scalar function, NY >= 1 corresponds
//             to vector-valued function.
//
// Outputs:
//     State-  builder object
//
// ALGLIB Project: Copyright 22.10.2018 by Sergey Bochkanov
void idwbuildercreate(const ae_int_t nx, const ae_int_t ny, idwbuilder &state);

// This function changes number of layers used by IDW-MSTAB algorithm.
//
// The more layers you have, the finer details can  be  reproduced  with  IDW
// model. The less layers you have, the less memory and CPU time is  consumed
// by the model.
//
// Memory consumption grows linearly with layers count,  running  time  grows
// sub-linearly.
//
// The default number of layers is 16, which allows you to reproduce  details
// at distance down to SRad/65536. You will rarely need to change it.
//
// Inputs:
//     State   -   builder object
//     NLayers -   NLayers >= 1, the number of layers used by the model.
// ALGLIB: Copyright 22.10.2018 by Sergey Bochkanov
void idwbuildersetnlayers(const idwbuilder &state, const ae_int_t nlayers);

// This function adds dataset to the builder object.
//
// This function overrides results of the previous calls, i.e. multiple calls
// of this function will result in only the last set being added.
//
// Inputs:
//     State   -   builder object
//     XY      -   points, array[N,NX+NY]. One row  corresponds to  one point
//                 in the dataset. First NX elements  are  coordinates,  next
//                 NY elements are function values. Array may  be larger than
//                 specified, in  this  case  only leading [N,NX+NY] elements
//                 will be used.
//     N       -   number of points in the dataset, N >= 0.
// ALGLIB: Copyright 22.10.2018 by Sergey Bochkanov
void idwbuildersetpoints(const idwbuilder &state, const real_2d_array &xy, const ae_int_t n);
void idwbuildersetpoints(const idwbuilder &state, const real_2d_array &xy);

// This function sets IDW model  construction  algorithm  to  the  Multilayer
// Stabilized IDW method (IDW-MSTAB), a  latest  incarnation  of  the inverse
// distance weighting interpolation which fixes shortcomings of  the original
// and modified Shepard's variants.
//
// The distinctive features of IDW-MSTAB are:
// 1) exact interpolation  is  pursued  (as  opposed  to  fitting  and  noise
//    suppression)
// 2) improved robustness when compared with that of other algorithms:
//    * MSTAB shows almost no strange  fitting  artifacts  like  ripples  and
//      sharp spikes (unlike N-dimensional splines and HRBFs)
//    * MSTAB does not return function values far from the  interval  spanned
//      by the dataset; say, if all your points have |f| <= 1, you  can be sure
//      that model value won't deviate too much from [-1,+1]
// 3) good model construction time competing with that of HRBFs  and  bicubic
//    splines
// 4) ability to work with any number of dimensions, starting from NX=1
//
// The drawbacks of IDW-MSTAB (and all IDW algorithms in general) are:
// 1) dependence of the model evaluation time on the search radius
// 2) bad extrapolation properties, models built by this method  are  usually
//    conservative in their predictions
//
// Thus, IDW-MSTAB is  a  good  "default"  option  if  you  want  to  perform
// scattered multidimensional interpolation. Although it has  its  drawbacks,
// it is easy to use and robust, which makes it a good first step.
//
//
// Inputs:
//     State   -   builder object
//     SRad    -   initial search radius, SRad > 0 is required. A model  value
//                 is obtained by "smart" averaging  of  the  dataset  points
//                 within search radius.
//
// NOTE 1: IDW interpolation can  correctly  handle  ANY  dataset,  including
//         datasets with non-distinct points. In case non-distinct points are
//         found, an average value for this point will be calculated.
//
// NOTE 2: the memory requirements for model storage are O(NPoints*NLayers).
//         The model construction needs twice as much memory as model storage.
//
// NOTE 3: by default 16 IDW layers are built which is enough for most cases.
//         You can change this parameter with idwbuildersetnlayers()  method.
//         Larger values may be necessary if you need to reproduce  extrafine
//         details at distances smaller than SRad/65536.  Smaller value   may
//         be necessary if you have to save memory and  computing  time,  and
//         ready to sacrifice some model quality.
//
//
// ALGORITHM DESCRIPTION
//
// ALGLIB implementation of IDW is somewhat similar to the modified Shepard's
// method (one with search radius R) but overcomes several of its  drawbacks,
// namely:
// 1) a tendency to show stepwise behavior for uniform datasets
// 2) a tendency to show terrible interpolation properties for highly
//    nonuniform datasets which often arise in geospatial tasks
//   (function values are densely sampled across multiple separated
//   "tracks")
//
// IDW-MSTAB method performs several passes over dataset and builds a sequence
// of progressively refined IDW models  (layers),  which starts from one with
// largest search radius SRad  and continues to smaller  search  radii  until
// required number of  layers  is  built.  Highest  layers  reproduce  global
// behavior of the target function at larger distances  whilst  lower  layers
// reproduce fine details at smaller distances.
//
// Each layer is an IDW model built with following modifications:
// * weights go to zero when distance approach to the current search radius
// * an additional regularizing term is added to the distance: w=1/(d^2+lambda)
// * an additional fictional term with unit weight and zero function value is
//   added in order to promote continuity  properties  at  the  isolated  and
//   boundary points
//
// By default, 16 layers is built, which is enough for most  cases.  You  can
// change this parameter with idwbuildersetnlayers() method.
// ALGLIB: Copyright 22.10.2018 by Sergey Bochkanov
void idwbuildersetalgomstab(const idwbuilder &state, const double srad);

// This function sets  IDW  model  construction  algorithm  to  the  textbook
// Shepard's algorithm with custom (user-specified) power parameter.
//
// IMPORTANT: we do NOT recommend using textbook IDW algorithms because  they
//            have terrible interpolation properties. Use MSTAB in all cases.
//
// Inputs:
//     State   -   builder object
//     P       -   power parameter, P > 0; good value to start with is 2.0
//
// NOTE 1: IDW interpolation can  correctly  handle  ANY  dataset,  including
//         datasets with non-distinct points. In case non-distinct points are
//         found, an average value for this point will be calculated.
// ALGLIB: Copyright 22.10.2018 by Sergey Bochkanov
void idwbuildersetalgotextbookshepard(const idwbuilder &state, const double p);

// This function sets  IDW  model  construction  algorithm  to the 'textbook'
// modified Shepard's algorithm with user-specified search radius.
//
// IMPORTANT: we do NOT recommend using textbook IDW algorithms because  they
//            have terrible interpolation properties. Use MSTAB in all cases.
//
// Inputs:
//     State   -   builder object
//     R       -   search radius
//
// NOTE 1: IDW interpolation can  correctly  handle  ANY  dataset,  including
//         datasets with non-distinct points. In case non-distinct points are
//         found, an average value for this point will be calculated.
// ALGLIB: Copyright 22.10.2018 by Sergey Bochkanov
void idwbuildersetalgotextbookmodshepard(const idwbuilder &state, const double r);

// This function sets prior term (model value at infinity) as  user-specified
// value.
//
// Inputs:
//     S       -   spline builder
//     V       -   value for user-defined prior
//
// NOTE: for vector-valued models all components of the prior are set to same
//       user-specified value
// ALGLIB: Copyright 29.10.2018 by Sergey Bochkanov
void idwbuildersetuserterm(const idwbuilder &state, const double v);

// This function sets constant prior term (model value at infinity).
//
// Constant prior term is determined as mean value over dataset.
//
// Inputs:
//     S       -   spline builder
// ALGLIB: Copyright 29.10.2018 by Sergey Bochkanov
void idwbuildersetconstterm(const idwbuilder &state);

// This function sets zero prior term (model value at infinity).
//
// Inputs:
//     S       -   spline builder
// ALGLIB: Copyright 29.10.2018 by Sergey Bochkanov
void idwbuildersetzeroterm(const idwbuilder &state);

// IDW interpolation: scalar target, 1-dimensional argument
//
// NOTE: this function modifies internal temporaries of the  IDW  model, thus
//       IT IS NOT  THREAD-SAFE!  If  you  want  to  perform  parallel  model
//       evaluation from the multiple threads, use idwtscalcbuf()  with  per-
//       thread buffer object.
//
// Inputs:
//     S   -   IDW interpolant built with IDW builder
//     X0  -   argument value
//
// Result:
//     IDW interpolant S(X0)
// ALGLIB: Copyright 22.10.2018 by Sergey Bochkanov
double idwcalc1(const idwmodel &s, const double x0);

// IDW interpolation: scalar target, 2-dimensional argument
//
// NOTE: this function modifies internal temporaries of the  IDW  model, thus
//       IT IS NOT  THREAD-SAFE!  If  you  want  to  perform  parallel  model
//       evaluation from the multiple threads, use idwtscalcbuf()  with  per-
//       thread buffer object.
//
// Inputs:
//     S       -   IDW interpolant built with IDW builder
//     X0, X1  -   argument value
//
// Result:
//     IDW interpolant S(X0,X1)
// ALGLIB: Copyright 22.10.2018 by Sergey Bochkanov
double idwcalc2(const idwmodel &s, const double x0, const double x1);

// IDW interpolation: scalar target, 3-dimensional argument
//
// NOTE: this function modifies internal temporaries of the  IDW  model, thus
//       IT IS NOT  THREAD-SAFE!  If  you  want  to  perform  parallel  model
//       evaluation from the multiple threads, use idwtscalcbuf()  with  per-
//       thread buffer object.
//
// Inputs:
//     S       -   IDW interpolant built with IDW builder
//     X0,X1,X2-   argument value
//
// Result:
//     IDW interpolant S(X0,X1,X2)
// ALGLIB: Copyright 22.10.2018 by Sergey Bochkanov
double idwcalc3(const idwmodel &s, const double x0, const double x1, const double x2);

// This function calculates values of the IDW model at the given point.
//
// This is general function which can be used for arbitrary NX (dimension  of
// the space of arguments) and NY (dimension of the function itself). However
// when  you  have  NY=1  you  may  find more convenient to  use  idwcalc1(),
// idwcalc2() or idwcalc3().
//
// NOTE: this function modifies internal temporaries of the  IDW  model, thus
//       IT IS NOT  THREAD-SAFE!  If  you  want  to  perform  parallel  model
//       evaluation from the multiple threads, use idwtscalcbuf()  with  per-
//       thread buffer object.
//
// Inputs:
//     S       -   IDW model
//     X       -   coordinates, array[NX]. X may have more than NX  elements,
//                 in this case only leading NX will be used.
//
// Outputs:
//     Y       -   function value, array[NY]. Y is out-parameter and will  be
//                 reallocated after call to this function. In case you  want
//                 to reuse previously allocated Y, you may use idwcalcbuf(),
//                 which reallocates Y only when it is too small.
// ALGLIB: Copyright 22.10.2018 by Sergey Bochkanov
void idwcalc(const idwmodel &s, const real_1d_array &x, real_1d_array &y);

// This function calculates values of the IDW model at the given point.
//
// Same as idwcalc(), but does not reallocate Y when in is large enough to
// store function values.
//
// NOTE: this function modifies internal temporaries of the  IDW  model, thus
//       IT IS NOT  THREAD-SAFE!  If  you  want  to  perform  parallel  model
//       evaluation from the multiple threads, use idwtscalcbuf()  with  per-
//       thread buffer object.
//
// Inputs:
//     S       -   IDW model
//     X       -   coordinates, array[NX]. X may have more than NX  elements,
//                 in this case only leading NX will be used.
//     Y       -   possibly preallocated array
//
// Outputs:
//     Y       -   function value, array[NY]. Y is not reallocated when it
//                 is larger than NY.
// ALGLIB: Copyright 22.10.2018 by Sergey Bochkanov
void idwcalcbuf(const idwmodel &s, const real_1d_array &x, real_1d_array &y);

// This function calculates values of the IDW model at the given point, using
// external  buffer  object  (internal  temporaries  of  IDW  model  are  not
// modified).
//
// This function allows to use same IDW model object  in  different  threads,
// assuming  that  different   threads  use different instances of the buffer
// structure.
//
// Inputs:
//     S       -   IDW model, may be shared between different threads
//     Buf     -   buffer object created for this particular instance of  IDW
//                 model with idwcreatecalcbuffer().
//     X       -   coordinates, array[NX]. X may have more than NX  elements,
//                 in this case only  leading NX will be used.
//     Y       -   possibly preallocated array
//
// Outputs:
//     Y       -   function value, array[NY]. Y is not reallocated when it
//                 is larger than NY.
// ALGLIB: Copyright 13.12.2011 by Sergey Bochkanov
void idwtscalcbuf(const idwmodel &s, const idwcalcbuffer &buf, const real_1d_array &x, real_1d_array &y);

// This function fits IDW model to the dataset using current IDW construction
// algorithm. A model being built and fitting report are returned.
//
// Inputs:
//     State   -   builder object
//
// Outputs:
//     Model   -   an IDW model built with current algorithm
//     Rep     -   model fitting report, fields of this structure contain
//                 information about average fitting errors.
//
// NOTE: although IDW-MSTAB algorithm is an  interpolation  method,  i.e.  it
//       tries to fit the model exactly, it can  handle  datasets  with  non-
//       distinct points which can not be fit exactly; in such  cases  least-
//       squares fitting is performed.
// ALGLIB: Copyright 22.10.2018 by Sergey Bochkanov
void idwfit(const idwbuilder &state, idwmodel &model, idwreport &rep);
} // end of namespace alglib

// === RATINT Package ===
// Depends on: (AlgLibInternal) TSORT
namespace alglib_impl {
struct barycentricinterpolant {
   ae_int_t n;
   double sy;
   ae_vector x;
   ae_vector y;
   ae_vector w;
};
void barycentricinterpolant_init(void *_p, bool make_automatic);
void barycentricinterpolant_copy(void *_dst, void *_src, bool make_automatic);
void barycentricinterpolant_free(void *_p, bool make_automatic);

double barycentriccalc(barycentricinterpolant *b, double t);
void barycentricdiff1(barycentricinterpolant *b, double t, double *f, double *df);
void barycentricdiff2(barycentricinterpolant *b, double t, double *f, double *df, double *d2f);
void barycentriclintransx(barycentricinterpolant *b, double ca, double cb);
void barycentriclintransy(barycentricinterpolant *b, double ca, double cb);
void barycentricunpack(barycentricinterpolant *b, ae_int_t *n, RVector *x, RVector *y, RVector *w);
void barycentricbuildxyw(RVector *x, RVector *y, RVector *w, ae_int_t n, barycentricinterpolant *b);
void barycentricbuildfloaterhormann(RVector *x, RVector *y, ae_int_t n, ae_int_t d, barycentricinterpolant *b);
void barycentriccopy(barycentricinterpolant *b, barycentricinterpolant *b2);
} // end of namespace alglib_impl

namespace alglib {
// Barycentric interpolant.
DecClass(barycentricinterpolant, EndD);

// Rational interpolation using barycentric formula
//
// F(t) = SUM(i=0,n-1,w[i]*f[i]/(t-x[i])) / SUM(i=0,n-1,w[i]/(t-x[i]))
//
// Inputs:
//     B   -   barycentric interpolant built with one of model building
//             subroutines.
//     T   -   interpolation point
//
// Result:
//     barycentric interpolant F(t)
// ALGLIB: Copyright 17.08.2009 by Sergey Bochkanov
double barycentriccalc(const barycentricinterpolant &b, const double t);

// Differentiation of barycentric interpolant: first derivative.
//
// Algorithm used in this subroutine is very robust and should not fail until
// provided with values too close to MaxRealNumber  (usually  MaxRealNumber/N
// or greater will overflow).
//
// Inputs:
//     B   -   barycentric interpolant built with one of model building
//             subroutines.
//     T   -   interpolation point
//
// Outputs:
//     F   -   barycentric interpolant at T
//     DF  -   first derivative
//
// NOTE
//
// ALGLIB: Copyright 17.08.2009 by Sergey Bochkanov
void barycentricdiff1(const barycentricinterpolant &b, const double t, double &f, double &df);

// Differentiation of barycentric interpolant: first/second derivatives.
//
// Inputs:
//     B   -   barycentric interpolant built with one of model building
//             subroutines.
//     T   -   interpolation point
//
// Outputs:
//     F   -   barycentric interpolant at T
//     DF  -   first derivative
//     D2F -   second derivative
//
// NOTE: this algorithm may fail due to overflow/underflor if  used  on  data
// whose values are close to MaxRealNumber or MinRealNumber.  Use more robust
// BarycentricDiff1() subroutine in such cases.
//
// ALGLIB: Copyright 17.08.2009 by Sergey Bochkanov
void barycentricdiff2(const barycentricinterpolant &b, const double t, double &f, double &df, double &d2f);

// This subroutine performs linear transformation of the argument.
//
// Inputs:
//     B       -   rational interpolant in barycentric form
//     CA, CB  -   transformation coefficients: x = CA*t + CB
//
// Outputs:
//     B       -   transformed interpolant with X replaced by T
//
// ALGLIB Project: Copyright 19.08.2009 by Sergey Bochkanov
void barycentriclintransx(const barycentricinterpolant &b, const double ca, const double cb);

// This  subroutine   performs   linear  transformation  of  the  barycentric
// interpolant.
//
// Inputs:
//     B       -   rational interpolant in barycentric form
//     CA, CB  -   transformation coefficients: B2(x) = CA*B(x) + CB
//
// Outputs:
//     B       -   transformed interpolant
//
// ALGLIB Project: Copyright 19.08.2009 by Sergey Bochkanov
void barycentriclintransy(const barycentricinterpolant &b, const double ca, const double cb);

// Extracts X/Y/W arrays from rational interpolant
//
// Inputs:
//     B   -   barycentric interpolant
//
// Outputs:
//     N   -   nodes count, N > 0
//     X   -   interpolation nodes, array[0..N-1]
//     F   -   function values, array[0..N-1]
//     W   -   barycentric weights, array[0..N-1]
// ALGLIB: Copyright 17.08.2009 by Sergey Bochkanov
void barycentricunpack(const barycentricinterpolant &b, ae_int_t &n, real_1d_array &x, real_1d_array &y, real_1d_array &w);

// Rational interpolant from X/Y/W arrays
//
// F(t) = SUM(i=0,n-1,w[i]*f[i]/(t-x[i])) / SUM(i=0,n-1,w[i]/(t-x[i]))
//
// Inputs:
//     X   -   interpolation nodes, array[0..N-1]
//     F   -   function values, array[0..N-1]
//     W   -   barycentric weights, array[0..N-1]
//     N   -   nodes count, N > 0
//
// Outputs:
//     B   -   barycentric interpolant built from (X, Y, W)
// ALGLIB: Copyright 17.08.2009 by Sergey Bochkanov
void barycentricbuildxyw(const real_1d_array &x, const real_1d_array &y, const real_1d_array &w, const ae_int_t n, barycentricinterpolant &b);

// Rational interpolant without poles
//
// The subroutine constructs the rational interpolating function without real
// poles  (see  'Barycentric rational interpolation with no  poles  and  high
// rates of approximation', Michael S. Floater. and  Kai  Hormann,  for  more
// information on this subject).
//
// Inputs:
//     X   -   interpolation nodes, array[0..N-1].
//     Y   -   function values, array[0..N-1].
//     N   -   number of nodes, N > 0.
//     D   -   order of the interpolation scheme, 0 <= D <= N-1.
//             D < 0 will cause an error.
//             D >= N it will be replaced with D=N-1.
//             if you don't know what D to choose, use small value about 3-5.
//
// Outputs:
//     B   -   barycentric interpolant.
//
// Note:
//     this algorithm always succeeds and calculates the weights  with  close
//     to machine precision.
//
// ALGLIB Project: Copyright 17.06.2007 by Sergey Bochkanov
void barycentricbuildfloaterhormann(const real_1d_array &x, const real_1d_array &y, const ae_int_t n, const ae_int_t d, barycentricinterpolant &b);
} // end of namespace alglib

// === FITSPHERE Package ===
// Depends on: (Optimization) MINNLC, MINLM
namespace alglib_impl {
struct fitsphereinternalreport {
   ae_int_t nfev;
   ae_int_t iterationscount;
};
void fitsphereinternalreport_init(void *_p, bool make_automatic);
void fitsphereinternalreport_copy(void *_dst, void *_src, bool make_automatic);
void fitsphereinternalreport_free(void *_p, bool make_automatic);

void fitspherels(RMatrix *xy, ae_int_t npoints, ae_int_t nx, RVector *cx, double *r);
void fitspheremc(RMatrix *xy, ae_int_t npoints, ae_int_t nx, RVector *cx, double *rhi);
void fitspheremi(RMatrix *xy, ae_int_t npoints, ae_int_t nx, RVector *cx, double *rlo);
void fitspheremz(RMatrix *xy, ae_int_t npoints, ae_int_t nx, RVector *cx, double *rlo, double *rhi);
void fitspherex(RMatrix *xy, ae_int_t npoints, ae_int_t nx, ae_int_t problemtype, double epsx, ae_int_t aulits, double penalty, RVector *cx, double *rlo, double *rhi);
void fitsphereinternal(RMatrix *xy, ae_int_t npoints, ae_int_t nx, ae_int_t problemtype, ae_int_t solvertype, double epsx, ae_int_t aulits, double penalty, RVector *cx, double *rlo, double *rhi, fitsphereinternalreport *rep);
} // end of namespace alglib_impl

namespace alglib {
// Fits least squares (LS) circle (or NX-dimensional sphere) to data  (a  set
// of points in NX-dimensional space).
//
// Least squares circle minimizes sum of squared deviations between distances
// from points to the center and  some  "candidate"  radius,  which  is  also
// fitted to the data.
//
// Inputs:
//     XY      -   array[NPoints,NX] (or larger), contains dataset.
//                 One row = one point in NX-dimensional space.
//     NPoints -   dataset size, NPoints > 0
//     NX      -   space dimensionality, NX > 0 (1, 2, 3, 4, 5 and so on)
//
// Outputs:
//     CX      -   central point for a sphere
//     R       -   radius
// ALGLIB: Copyright 07.05.2018 by Sergey Bochkanov
void fitspherels(const real_2d_array &xy, const ae_int_t npoints, const ae_int_t nx, real_1d_array &cx, double &r);

// Fits minimum circumscribed (MC) circle (or NX-dimensional sphere) to  data
// (a set of points in NX-dimensional space).
//
// Inputs:
//     XY      -   array[NPoints,NX] (or larger), contains dataset.
//                 One row = one point in NX-dimensional space.
//     NPoints -   dataset size, NPoints > 0
//     NX      -   space dimensionality, NX > 0 (1, 2, 3, 4, 5 and so on)
//
// Outputs:
//     CX      -   central point for a sphere
//     RHi     -   radius
//
// NOTE: this function is an easy-to-use wrapper around more powerful "expert"
//       function fitspherex().
//
//       This  wrapper  is optimized  for  ease of use and stability - at the
//       cost of somewhat lower  performance  (we  have  to  use  very  tight
//       stopping criteria for inner optimizer because we want to  make  sure
//       that it will converge on any dataset).
//
//       If you are ready to experiment with settings of  "expert"  function,
//       you can achieve ~2-4x speedup over standard "bulletproof" settings.
//
// ALGLIB: Copyright 14.04.2017 by Sergey Bochkanov
void fitspheremc(const real_2d_array &xy, const ae_int_t npoints, const ae_int_t nx, real_1d_array &cx, double &rhi);

// Fits maximum inscribed circle (or NX-dimensional sphere) to data (a set of
// points in NX-dimensional space).
//
// Inputs:
//     XY      -   array[NPoints,NX] (or larger), contains dataset.
//                 One row = one point in NX-dimensional space.
//     NPoints -   dataset size, NPoints > 0
//     NX      -   space dimensionality, NX > 0 (1, 2, 3, 4, 5 and so on)
//
// Outputs:
//     CX      -   central point for a sphere
//     RLo     -   radius
//
// NOTE: this function is an easy-to-use wrapper around more powerful "expert"
//       function fitspherex().
//
//       This  wrapper  is optimized  for  ease of use and stability - at the
//       cost of somewhat lower  performance  (we  have  to  use  very  tight
//       stopping criteria for inner optimizer because we want to  make  sure
//       that it will converge on any dataset).
//
//       If you are ready to experiment with settings of  "expert"  function,
//       you can achieve ~2-4x speedup over standard "bulletproof" settings.
//
// ALGLIB: Copyright 14.04.2017 by Sergey Bochkanov
void fitspheremi(const real_2d_array &xy, const ae_int_t npoints, const ae_int_t nx, real_1d_array &cx, double &rlo);

// Fits minimum zone circle (or NX-dimensional sphere)  to  data  (a  set  of
// points in NX-dimensional space).
//
// Inputs:
//     XY      -   array[NPoints,NX] (or larger), contains dataset.
//                 One row = one point in NX-dimensional space.
//     NPoints -   dataset size, NPoints > 0
//     NX      -   space dimensionality, NX > 0 (1, 2, 3, 4, 5 and so on)
//
// Outputs:
//     CX      -   central point for a sphere
//     RLo     -   radius of inscribed circle
//     RHo     -   radius of circumscribed circle
//
// NOTE: this function is an easy-to-use wrapper around more powerful "expert"
//       function fitspherex().
//
//       This  wrapper  is optimized  for  ease of use and stability - at the
//       cost of somewhat lower  performance  (we  have  to  use  very  tight
//       stopping criteria for inner optimizer because we want to  make  sure
//       that it will converge on any dataset).
//
//       If you are ready to experiment with settings of  "expert"  function,
//       you can achieve ~2-4x speedup over standard "bulletproof" settings.
//
// ALGLIB: Copyright 14.04.2017 by Sergey Bochkanov
void fitspheremz(const real_2d_array &xy, const ae_int_t npoints, const ae_int_t nx, real_1d_array &cx, double &rlo, double &rhi);

// Fitting minimum circumscribed, maximum inscribed or minimum  zone  circles
// (or NX-dimensional spheres)  to  data  (a  set of points in NX-dimensional
// space).
//
// This  is  expert  function  which  allows  to  tweak  many  parameters  of
// underlying nonlinear solver:
// * stopping criteria for inner iterations
// * number of outer iterations
// * penalty coefficient used to handle  nonlinear  constraints  (we  convert
//   unconstrained nonsmooth optimization problem ivolving max() and/or min()
//   operations to quadratically constrained smooth one).
//
// You may tweak all these parameters or only some  of  them,  leaving  other
// ones at their default state - just specify zero  value,  and  solver  will
// fill it with appropriate default one.
//
// These comments also include some discussion of  approach  used  to  handle
// such unusual fitting problem,  its  stability,  drawbacks  of  alternative
// methods, and convergence properties.
//
// Inputs:
//     XY      -   array[NPoints,NX] (or larger), contains dataset.
//                 One row = one point in NX-dimensional space.
//     NPoints -   dataset size, NPoints > 0
//     NX      -   space dimensionality, NX > 0 (1, 2, 3, 4, 5 and so on)
//     ProblemType-used to encode problem type:
//                 * 0 for least squares circle
//                 * 1 for minimum circumscribed circle/sphere fitting (MC)
//                 * 2 for  maximum inscribed circle/sphere fitting (MI)
//                 * 3 for minimum zone circle fitting (difference between
//                     Rhi and Rlo is minimized), denoted as MZ
//     EpsX    -   stopping condition for NLC optimizer:
//                 * must be non-negative
//                 * use 0 to choose default value (1.0E-12 is used by default)
//                 * you may specify larger values, up to 1.0E-6, if you want
//                   to   speed-up   solver;   NLC   solver  performs several
//                   preconditioned  outer  iterations,   so   final   result
//                   typically has precision much better than EpsX.
//     AULIts  -   number of outer iterations performed by NLC optimizer:
//                 * must be non-negative
//                 * use 0 to choose default value (20 is used by default)
//                 * you may specify values smaller than 20 if you want to
//                   speed up solver; 10 often results in good combination of
//                   precision and speed; sometimes you may get good results
//                   with just 6 outer iterations.
//                 Ignored for ProblemType=0.
//     Penalty -   penalty coefficient for NLC optimizer:
//                 * must be non-negative
//                 * use 0 to choose default value (1.0E6 in current version)
//                 * it should be really large, 1.0E6...1.0E7 is a good value
//                   to start from;
//                 * generally, default value is good enough
//                 Ignored for ProblemType=0.
//
// Outputs:
//     CX      -   central point for a sphere
//     RLo     -   radius:
//                 * for ProblemType=2,3, radius of the inscribed sphere
//                 * for ProblemType=0 - radius of the least squares sphere
//                 * for ProblemType=1 - zero
//     RHo     -   radius:
//                 * for ProblemType=1,3, radius of the circumscribed sphere
//                 * for ProblemType=0 - radius of the least squares sphere
//                 * for ProblemType=2 - zero
//
// NOTE: ON THE UNIQUENESS OF SOLUTIONS
//
// ALGLIB provides solution to several related circle fitting  problems:   MC
// (minimum circumscribed), MI (maximum inscribed)   and   MZ  (minimum zone)
// fitting, LS (least squares) fitting.
//
// It  is  important  to  note  that  among these problems only MC and LS are
// convex and have unique solution independently from starting point.
//
// As  for MI,  it  may (or  may  not, depending on dataset properties)  have
// multiple solutions, and it always  has  one degenerate solution C=infinity
// which corresponds to infinitely large radius. Thus, there are no guarantees
// that solution to  MI returned by this solver will be the best one (and  no
// one can provide you with such guarantee because problem is  NP-hard).  The
// only guarantee you have is that this solution is locally optimal, i.e.  it
// can not be improved by infinitesimally small tweaks in the parameters.
//
// It  is  also  possible  to "run away" to infinity when  started  from  bad
// initial point located outside of point cloud (or when point cloud does not
// span entire circumference/surface of the sphere).
//
// Finally,  MZ (minimum zone circle) stands somewhere between MC  and  MI in
// stability. It is somewhat regularized by "circumscribed" term of the merit
// function; however, solutions to  MZ may be non-unique, and in some unlucky
// cases it is also possible to "run away to infinity".
//
//
// NOTE: ON THE NONLINEARLY CONSTRAINED PROGRAMMING APPROACH
//
// The problem formulation for MC  (minimum circumscribed   circle;  for  the
// sake of simplicity we omit MZ and MI here) is:
//
//         [     [         ]2 ]
//     min [ max [ XY[i]-C ]  ]
//      C  [  i  [         ]  ]
//
// i.e. it is unconstrained nonsmooth optimization problem of finding  "best"
// central point, with radius R being unambiguously  determined  from  C.  In
// order to move away from non-smoothness we use following reformulation:
//
//         [   ]                    [         ]2
//     min [ R ] subject to R >= 0, [ XY[i]-C ] <= R^2
//     C,R [   ]                    [         ]
//
// i.e. it becomes smooth quadratically constrained optimization problem with
// linear target function. Such problem statement is 100% equivalent  to  the
// original nonsmooth one, but much easier  to  approach.  We solve  it  with
// MinNLC solver provided by ALGLIB.
//
//
// NOTE: ON INSTABILITY OF SEQUENTIAL LINEARIZATION APPROACH
//
// ALGLIB  has  nonlinearly  constrained  solver which proved to be stable on
// such problems. However, some authors proposed to linearize constraints  in
// the vicinity of current approximation (Ci,Ri) and to get next  approximate
// solution (Ci+1,Ri+1) as solution to linear programming problem. Obviously,
// LP problems are easier than nonlinearly constrained ones.
//
// Indeed,  such approach  to   MC/MI/MZ   resulted   in  ~10-20x increase in
// performance (when compared with NLC solver). However, it turned  out  that
// in some cases linearized model fails to predict correct direction for next
// step and tells us that we converged to solution even when we are still 2-4
// digits of precision away from it.
//
// It is important that it is not failure of LP solver - it is failure of the
// linear model;  even  when  solved  exactly,  it  fails  to  handle  subtle
// nonlinearities which arise near the solution. We validated it by comparing
// results returned by ALGLIB linear solver with that of MATLAB.
//
// In our experiments with linearization:
// * MC failed most often, at both realistic and synthetic datasets
// * MI sometimes failed, but sometimes succeeded
// * MZ often  succeeded; our guess is that presence of two independent  sets
//   of constraints (one set for Rlo and another one for Rhi) and  two  terms
//   in the target function (Rlo and Rhi) regularizes task,  so  when  linear
//   model fails to handle nonlinearities from Rlo, it uses  Rhi  as  a  hint
//   (and vice versa).
//
// Because linearization approach failed to achieve stable results, we do not
// include it in ALGLIB.
//
// ALGLIB: Copyright 14.04.2017 by Sergey Bochkanov
void fitspherex(const real_2d_array &xy, const ae_int_t npoints, const ae_int_t nx, const ae_int_t problemtype, const double epsx, const ae_int_t aulits, const double penalty, real_1d_array &cx, double &rlo, double &rhi);
} // end of namespace alglib

// === INTFITSERV Package ===
// Depends on: (LinAlg) TRFAC
namespace alglib_impl {
void lsfitscalexy(RVector *x, RVector *y, RVector *w, ae_int_t n, RVector *xc, RVector *yc, ZVector *dc, ae_int_t k, double *xa, double *xb, double *sa, double *sb, RVector *xoriginal, RVector *yoriginal);
void buildpriorterm(RMatrix *xy, ae_int_t n, ae_int_t nx, ae_int_t ny, ae_int_t modeltype, double priorval, RMatrix *v);
void buildpriorterm1(RVector *xy1, ae_int_t n, ae_int_t nx, ae_int_t ny, ae_int_t modeltype, double priorval, RMatrix *v);
} // end of namespace alglib_impl

// === SPLINE1D Package ===
// Depends on: (LinAlg) FBLS
// Depends on: (Solvers) LINLSQR
// Depends on: INTFITSERV
namespace alglib_impl {
struct spline1dinterpolant {
   bool periodic;
   ae_int_t n;
   ae_int_t k;
   ae_int_t continuity;
   ae_vector x;
   ae_vector c;
};
void spline1dinterpolant_init(void *_p, bool make_automatic);
void spline1dinterpolant_copy(void *_dst, void *_src, bool make_automatic);
void spline1dinterpolant_free(void *_p, bool make_automatic);

struct spline1dfitreport {
   double taskrcond;
   double rmserror;
   double avgerror;
   double avgrelerror;
   double maxerror;
};
void spline1dfitreport_init(void *_p, bool make_automatic);
void spline1dfitreport_copy(void *_dst, void *_src, bool make_automatic);
void spline1dfitreport_free(void *_p, bool make_automatic);

void spline1dbuildlinear(RVector *x, RVector *y, ae_int_t n, spline1dinterpolant *c);
void spline1dbuildcubic(RVector *x, RVector *y, ae_int_t n, ae_int_t boundltype, double boundl, ae_int_t boundrtype, double boundr, spline1dinterpolant *c);
void spline1dgriddiffcubic(RVector *x, RVector *y, ae_int_t n, ae_int_t boundltype, double boundl, ae_int_t boundrtype, double boundr, RVector *d);
void spline1dgriddiff2cubic(RVector *x, RVector *y, ae_int_t n, ae_int_t boundltype, double boundl, ae_int_t boundrtype, double boundr, RVector *d1, RVector *d2);
void spline1dconvcubic(RVector *x, RVector *y, ae_int_t n, ae_int_t boundltype, double boundl, ae_int_t boundrtype, double boundr, RVector *x2, ae_int_t n2, RVector *y2);
void spline1dconvdiffcubic(RVector *x, RVector *y, ae_int_t n, ae_int_t boundltype, double boundl, ae_int_t boundrtype, double boundr, RVector *x2, ae_int_t n2, RVector *y2, RVector *d2);
void spline1dconvdiff2cubic(RVector *x, RVector *y, ae_int_t n, ae_int_t boundltype, double boundl, ae_int_t boundrtype, double boundr, RVector *x2, ae_int_t n2, RVector *y2, RVector *d2, RVector *dd2);
void spline1dbuildcatmullrom(RVector *x, RVector *y, ae_int_t n, ae_int_t boundtype, double tension, spline1dinterpolant *c);
void spline1dbuildhermite(RVector *x, RVector *y, RVector *d, ae_int_t n, spline1dinterpolant *c);
void spline1dbuildakima(RVector *x, RVector *y, ae_int_t n, spline1dinterpolant *c);
double spline1dcalc(spline1dinterpolant *c, double x);
void spline1ddiff(spline1dinterpolant *c, double x, double *s, double *ds, double *d2s);
void spline1dcopy(spline1dinterpolant *c, spline1dinterpolant *cc);
void spline1dunpack(spline1dinterpolant *c, ae_int_t *n, RMatrix *tbl);
void spline1dlintransx(spline1dinterpolant *c, double a, double b);
void spline1dlintransy(spline1dinterpolant *c, double a, double b);
double spline1dintegrate(spline1dinterpolant *c, double x);
void spline1dfitpenalized(RVector *x, RVector *y, ae_int_t n, ae_int_t m, double rho, ae_int_t *info, spline1dinterpolant *s, spline1dfitreport *rep);
void spline1dfitpenalizedw(RVector *x, RVector *y, RVector *w, ae_int_t n, ae_int_t m, double rho, ae_int_t *info, spline1dinterpolant *s, spline1dfitreport *rep);
void spline1dfit(RVector *x, RVector *y, ae_int_t n, ae_int_t m, double lambdans, spline1dinterpolant *s, spline1dfitreport *rep);
void spline1dconvdiffinternal(RVector *xold, RVector *yold, RVector *dold, ae_int_t n, RVector *x2, ae_int_t n2, RVector *y, bool needy, RVector *d1, bool needd1, RVector *d2, bool needd2);
void spline1drootsandextrema(spline1dinterpolant *c, RVector *r, ae_int_t *nr, bool *dr, RVector *e, ZVector *et, ae_int_t *ne, bool *de);
void heapsortdpoints(RVector *x, RVector *y, RVector *d, ae_int_t n);
void solvepolinom2(double p0, double m0, double p1, double m1, double *x0, double *x1, ae_int_t *nr);
void solvecubicpolinom(double pa, double ma, double pb, double mb, double a, double b, double *x0, double *x1, double *x2, double *ex0, double *ex1, ae_int_t *nr, ae_int_t *ne, RVector *tempdata);
ae_int_t bisectmethod(double pa, double ma, double pb, double mb, double a, double b, double *x);
void spline1dbuildmonotone(RVector *x, RVector *y, ae_int_t n, spline1dinterpolant *c);
} // end of namespace alglib_impl

namespace alglib {
// 1-dimensional spline interpolant
DecClass(spline1dinterpolant, EndD);

// Spline fitting report:
//     RMSError        RMS error
//     AvgError        average error
//     AvgRelError     average relative error (for non-zero Y[I])
//     MaxError        maximum error
//
// Fields  below are  filled  by   obsolete    functions   (Spline1DFitCubic,
// Spline1DFitHermite). Modern fitting functions do NOT fill these fields:
//     TaskRCond       reciprocal of task's condition number
DecClass(spline1dfitreport, double &taskrcond; double &rmserror; double &avgerror; double &avgrelerror; double &maxerror;);

// This subroutine builds linear spline interpolant
//
// Inputs:
//     X   -   spline nodes, array[0..N-1]
//     Y   -   function values, array[0..N-1]
//     N   -   points count (optional):
//             * N >= 2
//             * if given, only first N points are used to build spline
//             * if not given, automatically detected from X/Y sizes
//               (len(X) must be equal to len(Y))
//
// Outputs:
//     C   -   spline interpolant
//
//
// ORDER OF POINTS
//
// Subroutine automatically sorts points, so caller may pass unsorted array.
//
// ALGLIB Project: Copyright 24.06.2007 by Sergey Bochkanov
void spline1dbuildlinear(const real_1d_array &x, const real_1d_array &y, const ae_int_t n, spline1dinterpolant &c);
void spline1dbuildlinear(const real_1d_array &x, const real_1d_array &y, spline1dinterpolant &c);

// This subroutine builds cubic spline interpolant.
//
// Inputs:
//     X           -   spline nodes, array[0..N-1].
//     Y           -   function values, array[0..N-1].
//
// OPTIONAL PARAMETERS:
//     N           -   points count:
//                     * N >= 2
//                     * if given, only first N points are used to build spline
//                     * if not given, automatically detected from X/Y sizes
//                       (len(X) must be equal to len(Y))
//     BoundLType  -   boundary condition type for the left boundary
//     BoundL      -   left boundary condition (first or second derivative,
//                     depending on the BoundLType)
//     BoundRType  -   boundary condition type for the right boundary
//     BoundR      -   right boundary condition (first or second derivative,
//                     depending on the BoundRType)
//
// Outputs:
//     C           -   spline interpolant
//
// ORDER OF POINTS
//
// Subroutine automatically sorts points, so caller may pass unsorted array.
//
// SETTING BOUNDARY VALUES:
//
// The BoundLType/BoundRType parameters can have the following values:
//     * -1, which corresonds to the periodic (cyclic) boundary conditions.
//           In this case:
//           * both BoundLType and BoundRType must be equal to -1.
//           * BoundL/BoundR are ignored
//           * Y[last] is ignored (it is assumed to be equal to Y[first]).
//     *  0, which  corresponds  to  the  parabolically   terminated  spline
//           (BoundL and/or BoundR are ignored).
//     *  1, which corresponds to the first derivative boundary condition
//     *  2, which corresponds to the second derivative boundary condition
//     *  by default, BoundType=0 is used
//
// PROBLEMS WITH PERIODIC BOUNDARY CONDITIONS:
//
// Problems with periodic boundary conditions have Y[first_point]=Y[last_point].
// However, this subroutine doesn't require you to specify equal  values  for
// the first and last points - it automatically forces them  to  be  equal by
// copying  Y[first_point]  (corresponds  to the leftmost,  minimal  X[])  to
// Y[last_point]. However it is recommended to pass consistent values of Y[],
// i.e. to make Y[first_point]=Y[last_point].
//
// ALGLIB Project: Copyright 23.06.2007 by Sergey Bochkanov
void spline1dbuildcubic(const real_1d_array &x, const real_1d_array &y, const ae_int_t n, const ae_int_t boundltype, const double boundl, const ae_int_t boundrtype, const double boundr, spline1dinterpolant &c);
void spline1dbuildcubic(const real_1d_array &x, const real_1d_array &y, spline1dinterpolant &c);

// This function solves following problem: given table y[] of function values
// at nodes x[], it calculates and returns table of function derivatives  d[]
// (calculated at the same nodes x[]).
//
// This function yields same result as Spline1DBuildCubic() call followed  by
// sequence of Spline1DDiff() calls, but it can be several times faster  when
// called for ordered X[] and X2[].
//
// Inputs:
//     X           -   spline nodes
//     Y           -   function values
//
// OPTIONAL PARAMETERS:
//     N           -   points count:
//                     * N >= 2
//                     * if given, only first N points are used
//                     * if not given, automatically detected from X/Y sizes
//                       (len(X) must be equal to len(Y))
//     BoundLType  -   boundary condition type for the left boundary
//     BoundL      -   left boundary condition (first or second derivative,
//                     depending on the BoundLType)
//     BoundRType  -   boundary condition type for the right boundary
//     BoundR      -   right boundary condition (first or second derivative,
//                     depending on the BoundRType)
//
// Outputs:
//     D           -   derivative values at X[]
//
// ORDER OF POINTS
//
// Subroutine automatically sorts points, so caller may pass unsorted array.
// Derivative values are correctly reordered on return, so  D[I]  is  always
// equal to S'(X[I]) independently of points order.
//
// SETTING BOUNDARY VALUES:
//
// The BoundLType/BoundRType parameters can have the following values:
//     * -1, which corresonds to the periodic (cyclic) boundary conditions.
//           In this case:
//           * both BoundLType and BoundRType must be equal to -1.
//           * BoundL/BoundR are ignored
//           * Y[last] is ignored (it is assumed to be equal to Y[first]).
//     *  0, which  corresponds  to  the  parabolically   terminated  spline
//           (BoundL and/or BoundR are ignored).
//     *  1, which corresponds to the first derivative boundary condition
//     *  2, which corresponds to the second derivative boundary condition
//     *  by default, BoundType=0 is used
//
// PROBLEMS WITH PERIODIC BOUNDARY CONDITIONS:
//
// Problems with periodic boundary conditions have Y[first_point]=Y[last_point].
// However, this subroutine doesn't require you to specify equal  values  for
// the first and last points - it automatically forces them  to  be  equal by
// copying  Y[first_point]  (corresponds  to the leftmost,  minimal  X[])  to
// Y[last_point]. However it is recommended to pass consistent values of Y[],
// i.e. to make Y[first_point]=Y[last_point].
//
// ALGLIB Project: Copyright 03.09.2010 by Sergey Bochkanov
void spline1dgriddiffcubic(const real_1d_array &x, const real_1d_array &y, const ae_int_t n, const ae_int_t boundltype, const double boundl, const ae_int_t boundrtype, const double boundr, real_1d_array &d);
void spline1dgriddiffcubic(const real_1d_array &x, const real_1d_array &y, real_1d_array &d);

// This function solves following problem: given table y[] of function values
// at  nodes  x[],  it  calculates  and  returns  tables  of first and second
// function derivatives d1[] and d2[] (calculated at the same nodes x[]).
//
// This function yields same result as Spline1DBuildCubic() call followed  by
// sequence of Spline1DDiff() calls, but it can be several times faster  when
// called for ordered X[] and X2[].
//
// Inputs:
//     X           -   spline nodes
//     Y           -   function values
//
// OPTIONAL PARAMETERS:
//     N           -   points count:
//                     * N >= 2
//                     * if given, only first N points are used
//                     * if not given, automatically detected from X/Y sizes
//                       (len(X) must be equal to len(Y))
//     BoundLType  -   boundary condition type for the left boundary
//     BoundL      -   left boundary condition (first or second derivative,
//                     depending on the BoundLType)
//     BoundRType  -   boundary condition type for the right boundary
//     BoundR      -   right boundary condition (first or second derivative,
//                     depending on the BoundRType)
//
// Outputs:
//     D1          -   S' values at X[]
//     D2          -   S'' values at X[]
//
// ORDER OF POINTS
//
// Subroutine automatically sorts points, so caller may pass unsorted array.
// Derivative values are correctly reordered on return, so  D[I]  is  always
// equal to S'(X[I]) independently of points order.
//
// SETTING BOUNDARY VALUES:
//
// The BoundLType/BoundRType parameters can have the following values:
//     * -1, which corresonds to the periodic (cyclic) boundary conditions.
//           In this case:
//           * both BoundLType and BoundRType must be equal to -1.
//           * BoundL/BoundR are ignored
//           * Y[last] is ignored (it is assumed to be equal to Y[first]).
//     *  0, which  corresponds  to  the  parabolically   terminated  spline
//           (BoundL and/or BoundR are ignored).
//     *  1, which corresponds to the first derivative boundary condition
//     *  2, which corresponds to the second derivative boundary condition
//     *  by default, BoundType=0 is used
//
// PROBLEMS WITH PERIODIC BOUNDARY CONDITIONS:
//
// Problems with periodic boundary conditions have Y[first_point]=Y[last_point].
// However, this subroutine doesn't require you to specify equal  values  for
// the first and last points - it automatically forces them  to  be  equal by
// copying  Y[first_point]  (corresponds  to the leftmost,  minimal  X[])  to
// Y[last_point]. However it is recommended to pass consistent values of Y[],
// i.e. to make Y[first_point]=Y[last_point].
//
// ALGLIB Project: Copyright 03.09.2010 by Sergey Bochkanov
void spline1dgriddiff2cubic(const real_1d_array &x, const real_1d_array &y, const ae_int_t n, const ae_int_t boundltype, const double boundl, const ae_int_t boundrtype, const double boundr, real_1d_array &d1, real_1d_array &d2);
void spline1dgriddiff2cubic(const real_1d_array &x, const real_1d_array &y, real_1d_array &d1, real_1d_array &d2);

// This function solves following problem: given table y[] of function values
// at old nodes x[]  and new nodes  x2[],  it calculates and returns table of
// function values y2[] (calculated at x2[]).
//
// This function yields same result as Spline1DBuildCubic() call followed  by
// sequence of Spline1DDiff() calls, but it can be several times faster  when
// called for ordered X[] and X2[].
//
// Inputs:
//     X           -   old spline nodes
//     Y           -   function values
//     X2           -  new spline nodes
//
// OPTIONAL PARAMETERS:
//     N           -   points count:
//                     * N >= 2
//                     * if given, only first N points from X/Y are used
//                     * if not given, automatically detected from X/Y sizes
//                       (len(X) must be equal to len(Y))
//     BoundLType  -   boundary condition type for the left boundary
//     BoundL      -   left boundary condition (first or second derivative,
//                     depending on the BoundLType)
//     BoundRType  -   boundary condition type for the right boundary
//     BoundR      -   right boundary condition (first or second derivative,
//                     depending on the BoundRType)
//     N2          -   new points count:
//                     * N2 >= 2
//                     * if given, only first N2 points from X2 are used
//                     * if not given, automatically detected from X2 size
//
// Outputs:
//     F2          -   function values at X2[]
//
// ORDER OF POINTS
//
// Subroutine automatically sorts points, so caller  may pass unsorted array.
// Function  values  are correctly reordered on  return, so F2[I]  is  always
// equal to S(X2[I]) independently of points order.
//
// SETTING BOUNDARY VALUES:
//
// The BoundLType/BoundRType parameters can have the following values:
//     * -1, which corresonds to the periodic (cyclic) boundary conditions.
//           In this case:
//           * both BoundLType and BoundRType must be equal to -1.
//           * BoundL/BoundR are ignored
//           * Y[last] is ignored (it is assumed to be equal to Y[first]).
//     *  0, which  corresponds  to  the  parabolically   terminated  spline
//           (BoundL and/or BoundR are ignored).
//     *  1, which corresponds to the first derivative boundary condition
//     *  2, which corresponds to the second derivative boundary condition
//     *  by default, BoundType=0 is used
//
// PROBLEMS WITH PERIODIC BOUNDARY CONDITIONS:
//
// Problems with periodic boundary conditions have Y[first_point]=Y[last_point].
// However, this subroutine doesn't require you to specify equal  values  for
// the first and last points - it automatically forces them  to  be  equal by
// copying  Y[first_point]  (corresponds  to the leftmost,  minimal  X[])  to
// Y[last_point]. However it is recommended to pass consistent values of Y[],
// i.e. to make Y[first_point]=Y[last_point].
//
// ALGLIB Project: Copyright 03.09.2010 by Sergey Bochkanov
void spline1dconvcubic(const real_1d_array &x, const real_1d_array &y, const ae_int_t n, const ae_int_t boundltype, const double boundl, const ae_int_t boundrtype, const double boundr, const real_1d_array &x2, const ae_int_t n2, real_1d_array &y2);
void spline1dconvcubic(const real_1d_array &x, const real_1d_array &y, const real_1d_array &x2, real_1d_array &y2);

// This function solves following problem: given table y[] of function values
// at old nodes x[]  and new nodes  x2[],  it calculates and returns table of
// function values y2[] and derivatives d2[] (calculated at x2[]).
//
// This function yields same result as Spline1DBuildCubic() call followed  by
// sequence of Spline1DDiff() calls, but it can be several times faster  when
// called for ordered X[] and X2[].
//
// Inputs:
//     X           -   old spline nodes
//     Y           -   function values
//     X2           -  new spline nodes
//
// OPTIONAL PARAMETERS:
//     N           -   points count:
//                     * N >= 2
//                     * if given, only first N points from X/Y are used
//                     * if not given, automatically detected from X/Y sizes
//                       (len(X) must be equal to len(Y))
//     BoundLType  -   boundary condition type for the left boundary
//     BoundL      -   left boundary condition (first or second derivative,
//                     depending on the BoundLType)
//     BoundRType  -   boundary condition type for the right boundary
//     BoundR      -   right boundary condition (first or second derivative,
//                     depending on the BoundRType)
//     N2          -   new points count:
//                     * N2 >= 2
//                     * if given, only first N2 points from X2 are used
//                     * if not given, automatically detected from X2 size
//
// Outputs:
//     F2          -   function values at X2[]
//     D2          -   first derivatives at X2[]
//
// ORDER OF POINTS
//
// Subroutine automatically sorts points, so caller  may pass unsorted array.
// Function  values  are correctly reordered on  return, so F2[I]  is  always
// equal to S(X2[I]) independently of points order.
//
// SETTING BOUNDARY VALUES:
//
// The BoundLType/BoundRType parameters can have the following values:
//     * -1, which corresonds to the periodic (cyclic) boundary conditions.
//           In this case:
//           * both BoundLType and BoundRType must be equal to -1.
//           * BoundL/BoundR are ignored
//           * Y[last] is ignored (it is assumed to be equal to Y[first]).
//     *  0, which  corresponds  to  the  parabolically   terminated  spline
//           (BoundL and/or BoundR are ignored).
//     *  1, which corresponds to the first derivative boundary condition
//     *  2, which corresponds to the second derivative boundary condition
//     *  by default, BoundType=0 is used
//
// PROBLEMS WITH PERIODIC BOUNDARY CONDITIONS:
//
// Problems with periodic boundary conditions have Y[first_point]=Y[last_point].
// However, this subroutine doesn't require you to specify equal  values  for
// the first and last points - it automatically forces them  to  be  equal by
// copying  Y[first_point]  (corresponds  to the leftmost,  minimal  X[])  to
// Y[last_point]. However it is recommended to pass consistent values of Y[],
// i.e. to make Y[first_point]=Y[last_point].
//
// ALGLIB Project: Copyright 03.09.2010 by Sergey Bochkanov
void spline1dconvdiffcubic(const real_1d_array &x, const real_1d_array &y, const ae_int_t n, const ae_int_t boundltype, const double boundl, const ae_int_t boundrtype, const double boundr, const real_1d_array &x2, const ae_int_t n2, real_1d_array &y2, real_1d_array &d2);
void spline1dconvdiffcubic(const real_1d_array &x, const real_1d_array &y, const real_1d_array &x2, real_1d_array &y2, real_1d_array &d2);

// This function solves following problem: given table y[] of function values
// at old nodes x[]  and new nodes  x2[],  it calculates and returns table of
// function  values  y2[],  first  and  second  derivatives  d2[]  and  dd2[]
// (calculated at x2[]).
//
// This function yields same result as Spline1DBuildCubic() call followed  by
// sequence of Spline1DDiff() calls, but it can be several times faster  when
// called for ordered X[] and X2[].
//
// Inputs:
//     X           -   old spline nodes
//     Y           -   function values
//     X2           -  new spline nodes
//
// OPTIONAL PARAMETERS:
//     N           -   points count:
//                     * N >= 2
//                     * if given, only first N points from X/Y are used
//                     * if not given, automatically detected from X/Y sizes
//                       (len(X) must be equal to len(Y))
//     BoundLType  -   boundary condition type for the left boundary
//     BoundL      -   left boundary condition (first or second derivative,
//                     depending on the BoundLType)
//     BoundRType  -   boundary condition type for the right boundary
//     BoundR      -   right boundary condition (first or second derivative,
//                     depending on the BoundRType)
//     N2          -   new points count:
//                     * N2 >= 2
//                     * if given, only first N2 points from X2 are used
//                     * if not given, automatically detected from X2 size
//
// Outputs:
//     F2          -   function values at X2[]
//     D2          -   first derivatives at X2[]
//     DD2         -   second derivatives at X2[]
//
// ORDER OF POINTS
//
// Subroutine automatically sorts points, so caller  may pass unsorted array.
// Function  values  are correctly reordered on  return, so F2[I]  is  always
// equal to S(X2[I]) independently of points order.
//
// SETTING BOUNDARY VALUES:
//
// The BoundLType/BoundRType parameters can have the following values:
//     * -1, which corresonds to the periodic (cyclic) boundary conditions.
//           In this case:
//           * both BoundLType and BoundRType must be equal to -1.
//           * BoundL/BoundR are ignored
//           * Y[last] is ignored (it is assumed to be equal to Y[first]).
//     *  0, which  corresponds  to  the  parabolically   terminated  spline
//           (BoundL and/or BoundR are ignored).
//     *  1, which corresponds to the first derivative boundary condition
//     *  2, which corresponds to the second derivative boundary condition
//     *  by default, BoundType=0 is used
//
// PROBLEMS WITH PERIODIC BOUNDARY CONDITIONS:
//
// Problems with periodic boundary conditions have Y[first_point]=Y[last_point].
// However, this subroutine doesn't require you to specify equal  values  for
// the first and last points - it automatically forces them  to  be  equal by
// copying  Y[first_point]  (corresponds  to the leftmost,  minimal  X[])  to
// Y[last_point]. However it is recommended to pass consistent values of Y[],
// i.e. to make Y[first_point]=Y[last_point].
//
// ALGLIB Project: Copyright 03.09.2010 by Sergey Bochkanov
void spline1dconvdiff2cubic(const real_1d_array &x, const real_1d_array &y, const ae_int_t n, const ae_int_t boundltype, const double boundl, const ae_int_t boundrtype, const double boundr, const real_1d_array &x2, const ae_int_t n2, real_1d_array &y2, real_1d_array &d2, real_1d_array &dd2);
void spline1dconvdiff2cubic(const real_1d_array &x, const real_1d_array &y, const real_1d_array &x2, real_1d_array &y2, real_1d_array &d2, real_1d_array &dd2);

// This subroutine builds Catmull-Rom spline interpolant.
//
// Inputs:
//     X           -   spline nodes, array[0..N-1].
//     Y           -   function values, array[0..N-1].
//
// OPTIONAL PARAMETERS:
//     N           -   points count:
//                     * N >= 2
//                     * if given, only first N points are used to build spline
//                     * if not given, automatically detected from X/Y sizes
//                       (len(X) must be equal to len(Y))
//     BoundType   -   boundary condition type:
//                     * -1 for periodic boundary condition
//                     *  0 for parabolically terminated spline (default)
//     Tension     -   tension parameter:
//                     * tension=0   corresponds to classic Catmull-Rom spline (default)
//                     * 0 < tension < 1 corresponds to more general form - cardinal spline
//
// Outputs:
//     C           -   spline interpolant
//
//
// ORDER OF POINTS
//
// Subroutine automatically sorts points, so caller may pass unsorted array.
//
// PROBLEMS WITH PERIODIC BOUNDARY CONDITIONS:
//
// Problems with periodic boundary conditions have Y[first_point]=Y[last_point].
// However, this subroutine doesn't require you to specify equal  values  for
// the first and last points - it automatically forces them  to  be  equal by
// copying  Y[first_point]  (corresponds  to the leftmost,  minimal  X[])  to
// Y[last_point]. However it is recommended to pass consistent values of Y[],
// i.e. to make Y[first_point]=Y[last_point].
//
// ALGLIB Project: Copyright 23.06.2007 by Sergey Bochkanov
void spline1dbuildcatmullrom(const real_1d_array &x, const real_1d_array &y, const ae_int_t n, const ae_int_t boundtype, const double tension, spline1dinterpolant &c);
void spline1dbuildcatmullrom(const real_1d_array &x, const real_1d_array &y, spline1dinterpolant &c);

// This subroutine builds Hermite spline interpolant.
//
// Inputs:
//     X           -   spline nodes, array[0..N-1]
//     Y           -   function values, array[0..N-1]
//     D           -   derivatives, array[0..N-1]
//     N           -   points count (optional):
//                     * N >= 2
//                     * if given, only first N points are used to build spline
//                     * if not given, automatically detected from X/Y sizes
//                       (len(X) must be equal to len(Y))
//
// Outputs:
//     C           -   spline interpolant.
//
//
// ORDER OF POINTS
//
// Subroutine automatically sorts points, so caller may pass unsorted array.
//
// ALGLIB Project: Copyright 23.06.2007 by Sergey Bochkanov
void spline1dbuildhermite(const real_1d_array &x, const real_1d_array &y, const real_1d_array &d, const ae_int_t n, spline1dinterpolant &c);
void spline1dbuildhermite(const real_1d_array &x, const real_1d_array &y, const real_1d_array &d, spline1dinterpolant &c);

// This subroutine builds Akima spline interpolant
//
// Inputs:
//     X           -   spline nodes, array[0..N-1]
//     Y           -   function values, array[0..N-1]
//     N           -   points count (optional):
//                     * N >= 2
//                     * if given, only first N points are used to build spline
//                     * if not given, automatically detected from X/Y sizes
//                       (len(X) must be equal to len(Y))
//
// Outputs:
//     C           -   spline interpolant
//
//
// ORDER OF POINTS
//
// Subroutine automatically sorts points, so caller may pass unsorted array.
//
// ALGLIB Project: Copyright 24.06.2007 by Sergey Bochkanov
void spline1dbuildakima(const real_1d_array &x, const real_1d_array &y, const ae_int_t n, spline1dinterpolant &c);
void spline1dbuildakima(const real_1d_array &x, const real_1d_array &y, spline1dinterpolant &c);

// This subroutine calculates the value of the spline at the given point X.
//
// Inputs:
//     C   -   spline interpolant
//     X   -   point
//
// Result:
//     S(x)
//
// ALGLIB Project: Copyright 23.06.2007 by Sergey Bochkanov
double spline1dcalc(const spline1dinterpolant &c, const double x);

// This subroutine differentiates the spline.
//
// Inputs:
//     C   -   spline interpolant.
//     X   -   point
//
// Result:
//     S   -   S(x)
//     DS  -   S'(x)
//     D2S -   S''(x)
//
// ALGLIB Project: Copyright 24.06.2007 by Sergey Bochkanov
void spline1ddiff(const spline1dinterpolant &c, const double x, double &s, double &ds, double &d2s);

// This subroutine unpacks the spline into the coefficients table.
//
// Inputs:
//     C   -   spline interpolant.
//     X   -   point
//
// Outputs:
//     Tbl -   coefficients table, unpacked format, array[0..N-2, 0..5].
//             For I = 0...N-2:
//                 Tbl[I,0] = X[i]
//                 Tbl[I,1] = X[i+1]
//                 Tbl[I,2] = C0
//                 Tbl[I,3] = C1
//                 Tbl[I,4] = C2
//                 Tbl[I,5] = C3
//             On [x[i], x[i+1]] spline is equals to:
//                 S(x) = C0 + C1*t + C2*t^2 + C3*t^3
//                 t = x-x[i]
//
// NOTE:
//     You  can rebuild spline with  Spline1DBuildHermite()  function,  which
//     accepts as inputs function values and derivatives at nodes, which  are
//     easy to calculate when you have coefficients.
//
// ALGLIB Project: Copyright 29.06.2007 by Sergey Bochkanov
void spline1dunpack(const spline1dinterpolant &c, ae_int_t &n, real_2d_array &tbl);

// This subroutine performs linear transformation of the spline argument.
//
// Inputs:
//     C   -   spline interpolant.
//     A, B-   transformation coefficients: x = A*t + B
// Result:
//     C   -   transformed spline
//
// ALGLIB Project: Copyright 30.06.2007 by Sergey Bochkanov
void spline1dlintransx(const spline1dinterpolant &c, const double a, const double b);

// This subroutine performs linear transformation of the spline.
//
// Inputs:
//     C   -   spline interpolant.
//     A, B-   transformation coefficients: S2(x) = A*S(x) + B
// Result:
//     C   -   transformed spline
//
// ALGLIB Project: Copyright 30.06.2007 by Sergey Bochkanov
void spline1dlintransy(const spline1dinterpolant &c, const double a, const double b);

// This subroutine integrates the spline.
//
// Inputs:
//     C   -   spline interpolant.
//     X   -   right bound of the integration interval [a, x],
//             here 'a' denotes min(x[])
// Result:
//     integral(S(t)dt,a,x)
//
// ALGLIB Project: Copyright 23.06.2007 by Sergey Bochkanov
double spline1dintegrate(const spline1dinterpolant &c, const double x);

// This function is an obsolete and deprecated version of fitting by
// penalized cubic spline.
//
// It was superseded by spline1dfit(), which is an orders of magnitude faster
// and more memory-efficient implementation.
//
// Do NOT use this function in the new code!
//
// ALGLIB Project: Copyright 18.08.2009 by Sergey Bochkanov
void spline1dfitpenalized(const real_1d_array &x, const real_1d_array &y, const ae_int_t n, const ae_int_t m, const double rho, ae_int_t &info, spline1dinterpolant &s, spline1dfitreport &rep);
void spline1dfitpenalized(const real_1d_array &x, const real_1d_array &y, const ae_int_t m, const double rho, ae_int_t &info, spline1dinterpolant &s, spline1dfitreport &rep);

// This function is an obsolete and deprecated version of fitting by
// penalized cubic spline.
//
// It was superseded by spline1dfit(), which is an orders of magnitude faster
// and more memory-efficient implementation.
//
// Do NOT use this function in the new code!
//
// ALGLIB Project: Copyright 19.10.2010 by Sergey Bochkanov
void spline1dfitpenalizedw(const real_1d_array &x, const real_1d_array &y, const real_1d_array &w, const ae_int_t n, const ae_int_t m, const double rho, ae_int_t &info, spline1dinterpolant &s, spline1dfitreport &rep);
void spline1dfitpenalizedw(const real_1d_array &x, const real_1d_array &y, const real_1d_array &w, const ae_int_t m, const double rho, ae_int_t &info, spline1dinterpolant &s, spline1dfitreport &rep);

// Fitting by smoothing (penalized) cubic spline.
//
// This function approximates N scattered points (some of X[] may be equal to
// each other) by cubic spline with M  nodes  at  equidistant  grid  spanning
// interval [min(x,xc),max(x,xc)].
//
// The problem is regularized by adding nonlinearity penalty to  usual  least
// squares penalty function:
//
//     MERIT_FUNC = F_LS + F_NL
//
// where F_LS is a least squares error  term,  and  F_NL  is  a  nonlinearity
// penalty which is roughly proportional to LambdaNS*integral{ S''(x)^2*dx }.
// Algorithm applies automatic renormalization of F_NL  which  makes  penalty
// term roughly invariant to scaling of X[] and changes in M.
//
// This function is a new edition  of  penalized  regression  spline fitting,
// a fast and compact one which needs much less resources that  its  previous
// version: just O(maxMN) memory and O(maxMN*log(maxMN)) time.
//
// NOTE: it is OK to run this function with both M << N and M >> N;  say,  it  is
//       possible to process 100 points with 1000-node spline.
//
// Inputs:
//     X           -   points, array[0..N-1].
//     Y           -   function values, array[0..N-1].
//     N           -   number of points (optional):
//                     * N > 0
//                     * if given, only first N elements of X/Y are processed
//                     * if not given, automatically determined from lengths
//     M           -   number of basis functions ( = number_of_nodes), M >= 4.
//     LambdaNS    -   LambdaNS >= 0, regularization  constant  passed by user.
//                     It penalizes nonlinearity in the regression spline.
//                     Possible values to start from are 0.00001, 0.1, 1
//
// Outputs:
//     S   -   spline interpolant.
//     Rep -   Following fields are set:
//             * RMSError      rms error on the (X,Y).
//             * AvgError      average error on the (X,Y).
//             * AvgRelError   average relative error on the non-zero Y
//             * MaxError      maximum error
//
// ALGLIB Project: Copyright 27.08.2019 by Sergey Bochkanov
void spline1dfit(const real_1d_array &x, const real_1d_array &y, const ae_int_t n, const ae_int_t m, const double lambdans, spline1dinterpolant &s, spline1dfitreport &rep);
void spline1dfit(const real_1d_array &x, const real_1d_array &y, const ae_int_t m, const double lambdans, spline1dinterpolant &s, spline1dfitreport &rep);

// This function builds monotone cubic Hermite interpolant. This interpolant
// is monotonic in [x(0),x(n-1)] and is constant outside of this interval.
//
// In  case  y[]  form  non-monotonic  sequence,  interpolant  is  piecewise
// monotonic.  Say, for x=(0,1,2,3,4)  and  y=(0,1,2,1,0)  interpolant  will
// monotonically grow at [0..2] and monotonically decrease at [2..4].
//
// Inputs:
//     X           -   spline nodes, array[0..N-1]. Subroutine automatically
//                     sorts points, so caller may pass unsorted array.
//     Y           -   function values, array[0..N-1]
//     N           -   the number of points(N >= 2).
//
// Outputs:
//     C           -   spline interpolant.
//
// ALGLIB Project: Copyright 21.06.2012 by Sergey Bochkanov
void spline1dbuildmonotone(const real_1d_array &x, const real_1d_array &y, const ae_int_t n, spline1dinterpolant &c);
void spline1dbuildmonotone(const real_1d_array &x, const real_1d_array &y, spline1dinterpolant &c);
} // end of namespace alglib

// === PARAMETRIC Package ===
// Depends on: (Integration) AUTOGK
// Depends on: SPLINE1D
namespace alglib_impl {
struct pspline2interpolant {
   ae_int_t n;
   bool periodic;
   ae_vector p;
   spline1dinterpolant x;
   spline1dinterpolant y;
};
void pspline2interpolant_init(void *_p, bool make_automatic);
void pspline2interpolant_copy(void *_dst, void *_src, bool make_automatic);
void pspline2interpolant_free(void *_p, bool make_automatic);

struct pspline3interpolant {
   ae_int_t n;
   bool periodic;
   ae_vector p;
   spline1dinterpolant x;
   spline1dinterpolant y;
   spline1dinterpolant z;
};
void pspline3interpolant_init(void *_p, bool make_automatic);
void pspline3interpolant_copy(void *_dst, void *_src, bool make_automatic);
void pspline3interpolant_free(void *_p, bool make_automatic);

void pspline2build(RMatrix *xy, ae_int_t n, ae_int_t st, ae_int_t pt, pspline2interpolant *p);
void pspline3build(RMatrix *xy, ae_int_t n, ae_int_t st, ae_int_t pt, pspline3interpolant *p);
void pspline2buildperiodic(RMatrix *xy, ae_int_t n, ae_int_t st, ae_int_t pt, pspline2interpolant *p);
void pspline3buildperiodic(RMatrix *xy, ae_int_t n, ae_int_t st, ae_int_t pt, pspline3interpolant *p);
void pspline2parametervalues(pspline2interpolant *p, ae_int_t *n, RVector *t);
void pspline3parametervalues(pspline3interpolant *p, ae_int_t *n, RVector *t);
void pspline2calc(pspline2interpolant *p, double t, double *x, double *y);
void pspline3calc(pspline3interpolant *p, double t, double *x, double *y, double *z);
void pspline2tangent(pspline2interpolant *p, double t, double *x, double *y);
void pspline3tangent(pspline3interpolant *p, double t, double *x, double *y, double *z);
void pspline2diff(pspline2interpolant *p, double t, double *x, double *dx, double *y, double *dy);
void pspline3diff(pspline3interpolant *p, double t, double *x, double *dx, double *y, double *dy, double *z, double *dz);
void pspline2diff2(pspline2interpolant *p, double t, double *x, double *dx, double *d2x, double *y, double *dy, double *d2y);
void pspline3diff2(pspline3interpolant *p, double t, double *x, double *dx, double *d2x, double *y, double *dy, double *d2y, double *z, double *dz, double *d2z);
double pspline2arclength(pspline2interpolant *p, double a, double b);
double pspline3arclength(pspline3interpolant *p, double a, double b);
void parametricrdpfixed(RMatrix *x, ae_int_t n, ae_int_t d, ae_int_t stopm, double stopeps, RMatrix *x2, ZVector *idx2, ae_int_t *nsections);
} // end of namespace alglib_impl

namespace alglib {
// Parametric spline inteprolant: 2-dimensional curve.
//
// You should not try to access its members directly - use PSpline2XXXXXXXX()
// functions instead.
DecClass(pspline2interpolant, EndD);

// Parametric spline inteprolant: 3-dimensional curve.
//
// You should not try to access its members directly - use PSpline3XXXXXXXX()
// functions instead.
DecClass(pspline3interpolant, EndD);

// This function  builds  non-periodic 2-dimensional parametric spline  which
// starts at (X[0],Y[0]) and ends at (X[N-1],Y[N-1]).
//
// Inputs:
//     XY  -   points, array[0..N-1,0..1].
//             XY[I,0:1] corresponds to the Ith point.
//             Order of points is important!
//     N   -   points count, N >= 5 for Akima splines, N >= 2 for other types  of
//             splines.
//     ST  -   spline type:
//             * 0     Akima spline
//             * 1     parabolically terminated Catmull-Rom spline (Tension=0)
//             * 2     parabolically terminated cubic spline
//     PT  -   parameterization type:
//             * 0     uniform
//             * 1     chord length
//             * 2     centripetal
//
// Outputs:
//     P   -   parametric spline interpolant
//
//
// NOTES:
// * this function  assumes  that  there all consequent points  are distinct.
//   I.e. (x0,y0) != (x1,y1),  (x1,y1) != (x2,y2),  (x2,y2) != (x3,y3)  and  so on.
//   However, non-consequent points may coincide, i.e. we can  have  (x0,y0)=
//   =(x2,y2).
//
// ALGLIB Project: Copyright 28.05.2010 by Sergey Bochkanov
void pspline2build(const real_2d_array &xy, const ae_int_t n, const ae_int_t st, const ae_int_t pt, pspline2interpolant &p);

// This function  builds  non-periodic 3-dimensional parametric spline  which
// starts at (X[0],Y[0],Z[0]) and ends at (X[N-1],Y[N-1],Z[N-1]).
//
// Same as PSpline2Build() function, but for 3D, so we  won't  duplicate  its
// description here.
//
// ALGLIB Project: Copyright 28.05.2010 by Sergey Bochkanov
void pspline3build(const real_2d_array &xy, const ae_int_t n, const ae_int_t st, const ae_int_t pt, pspline3interpolant &p);

// This  function  builds  periodic  2-dimensional  parametric  spline  which
// starts at (X[0],Y[0]), goes through all points to (X[N-1],Y[N-1]) and then
// back to (X[0],Y[0]).
//
// Inputs:
//     XY  -   points, array[0..N-1,0..1].
//             XY[I,0:1] corresponds to the Ith point.
//             XY[N-1,0:1] must be different from XY[0,0:1].
//             Order of points is important!
//     N   -   points count, N >= 3 for other types of splines.
//     ST  -   spline type:
//             * 1     Catmull-Rom spline (Tension=0) with cyclic boundary conditions
//             * 2     cubic spline with cyclic boundary conditions
//     PT  -   parameterization type:
//             * 0     uniform
//             * 1     chord length
//             * 2     centripetal
//
// Outputs:
//     P   -   parametric spline interpolant
//
//
// NOTES:
// * this function  assumes  that there all consequent points  are  distinct.
//   I.e. (x0,y0) != (x1,y1), (x1,y1) != (x2,y2),  (x2,y2) != (x3,y3)  and  so  on.
//   However, non-consequent points may coincide, i.e. we can  have  (x0,y0)=
//   =(x2,y2).
// * last point of sequence is NOT equal to the first  point.  You  shouldn't
//   make curve "explicitly periodic" by making them equal.
//
// ALGLIB Project: Copyright 28.05.2010 by Sergey Bochkanov
void pspline2buildperiodic(const real_2d_array &xy, const ae_int_t n, const ae_int_t st, const ae_int_t pt, pspline2interpolant &p);

// This  function  builds  periodic  3-dimensional  parametric  spline  which
// starts at (X[0],Y[0],Z[0]), goes through all points to (X[N-1],Y[N-1],Z[N-1])
// and then back to (X[0],Y[0],Z[0]).
//
// Same as PSpline2Build() function, but for 3D, so we  won't  duplicate  its
// description here.
//
// ALGLIB Project: Copyright 28.05.2010 by Sergey Bochkanov
void pspline3buildperiodic(const real_2d_array &xy, const ae_int_t n, const ae_int_t st, const ae_int_t pt, pspline3interpolant &p);

// This function returns vector of parameter values correspoding to points.
//
// I.e. for P created from (X[0],Y[0])...(X[N-1],Y[N-1]) and U=TValues(P)  we
// have
//     (X[0],Y[0]) = PSpline2Calc(P,U[0]),
//     (X[1],Y[1]) = PSpline2Calc(P,U[1]),
//     (X[2],Y[2]) = PSpline2Calc(P,U[2]),
//     ...
//
// Inputs:
//     P   -   parametric spline interpolant
//
// Outputs:
//     N   -   array size
//     T   -   array[0..N-1]
//
//
// NOTES:
// * for non-periodic splines U[0]=0, U[0] < U[1] < ... < U[N-1], U[N-1]=1
// * for periodic splines     U[0]=0, U[0] < U[1] < ... < U[N-1], U[N-1] < 1
//
// ALGLIB Project: Copyright 28.05.2010 by Sergey Bochkanov
void pspline2parametervalues(const pspline2interpolant &p, ae_int_t &n, real_1d_array &t);

// This function returns vector of parameter values correspoding to points.
//
// Same as PSpline2ParameterValues(), but for 3D.
//
// ALGLIB Project: Copyright 28.05.2010 by Sergey Bochkanov
void pspline3parametervalues(const pspline3interpolant &p, ae_int_t &n, real_1d_array &t);

// This function  calculates  the value of the parametric spline for a  given
// value of parameter T
//
// Inputs:
//     P   -   parametric spline interpolant
//     T   -   point:
//             * T in [0,1] corresponds to interval spanned by points
//             * for non-periodic splines T < 0 (or T > 1) correspond to parts of
//               the curve before the first (after the last) point
//             * for periodic splines T < 0 (or T > 1) are projected  into  [0,1]
//               by making T=T-floor(T).
//
// Outputs:
//     X   -   X-position
//     Y   -   Y-position
//
//
// ALGLIB Project: Copyright 28.05.2010 by Sergey Bochkanov
void pspline2calc(const pspline2interpolant &p, const double t, double &x, double &y);

// This function  calculates  the value of the parametric spline for a  given
// value of parameter T.
//
// Inputs:
//     P   -   parametric spline interpolant
//     T   -   point:
//             * T in [0,1] corresponds to interval spanned by points
//             * for non-periodic splines T < 0 (or T > 1) correspond to parts of
//               the curve before the first (after the last) point
//             * for periodic splines T < 0 (or T > 1) are projected  into  [0,1]
//               by making T=T-floor(T).
//
// Outputs:
//     X   -   X-position
//     Y   -   Y-position
//     Z   -   Z-position
//
//
// ALGLIB Project: Copyright 28.05.2010 by Sergey Bochkanov
void pspline3calc(const pspline3interpolant &p, const double t, double &x, double &y, double &z);

// This function  calculates  tangent vector for a given value of parameter T
//
// Inputs:
//     P   -   parametric spline interpolant
//     T   -   point:
//             * T in [0,1] corresponds to interval spanned by points
//             * for non-periodic splines T < 0 (or T > 1) correspond to parts of
//               the curve before the first (after the last) point
//             * for periodic splines T < 0 (or T > 1) are projected  into  [0,1]
//               by making T=T-floor(T).
//
// Outputs:
//     X    -   X-component of tangent vector (normalized)
//     Y    -   Y-component of tangent vector (normalized)
//
// NOTE:
//     X^2+Y^2 is either 1 (for non-zero tangent vector) or 0.
//
//
// ALGLIB Project: Copyright 28.05.2010 by Sergey Bochkanov
void pspline2tangent(const pspline2interpolant &p, const double t, double &x, double &y);

// This function  calculates  tangent vector for a given value of parameter T
//
// Inputs:
//     P   -   parametric spline interpolant
//     T   -   point:
//             * T in [0,1] corresponds to interval spanned by points
//             * for non-periodic splines T < 0 (or T > 1) correspond to parts of
//               the curve before the first (after the last) point
//             * for periodic splines T < 0 (or T > 1) are projected  into  [0,1]
//               by making T=T-floor(T).
//
// Outputs:
//     X    -   X-component of tangent vector (normalized)
//     Y    -   Y-component of tangent vector (normalized)
//     Z    -   Z-component of tangent vector (normalized)
//
// NOTE:
//     X^2+Y^2+Z^2 is either 1 (for non-zero tangent vector) or 0.
//
//
// ALGLIB Project: Copyright 28.05.2010 by Sergey Bochkanov
void pspline3tangent(const pspline3interpolant &p, const double t, double &x, double &y, double &z);

// This function calculates derivative, i.e. it returns (dX/dT,dY/dT).
//
// Inputs:
//     P   -   parametric spline interpolant
//     T   -   point:
//             * T in [0,1] corresponds to interval spanned by points
//             * for non-periodic splines T < 0 (or T > 1) correspond to parts of
//               the curve before the first (after the last) point
//             * for periodic splines T < 0 (or T > 1) are projected  into  [0,1]
//               by making T=T-floor(T).
//
// Outputs:
//     X   -   X-value
//     DX  -   X-derivative
//     Y   -   Y-value
//     DY  -   Y-derivative
//
//
// ALGLIB Project: Copyright 28.05.2010 by Sergey Bochkanov
void pspline2diff(const pspline2interpolant &p, const double t, double &x, double &dx, double &y, double &dy);

// This function calculates derivative, i.e. it returns (dX/dT,dY/dT,dZ/dT).
//
// Inputs:
//     P   -   parametric spline interpolant
//     T   -   point:
//             * T in [0,1] corresponds to interval spanned by points
//             * for non-periodic splines T < 0 (or T > 1) correspond to parts of
//               the curve before the first (after the last) point
//             * for periodic splines T < 0 (or T > 1) are projected  into  [0,1]
//               by making T=T-floor(T).
//
// Outputs:
//     X   -   X-value
//     DX  -   X-derivative
//     Y   -   Y-value
//     DY  -   Y-derivative
//     Z   -   Z-value
//     DZ  -   Z-derivative
//
//
// ALGLIB Project: Copyright 28.05.2010 by Sergey Bochkanov
void pspline3diff(const pspline3interpolant &p, const double t, double &x, double &dx, double &y, double &dy, double &z, double &dz);

// This function calculates first and second derivative with respect to T.
//
// Inputs:
//     P   -   parametric spline interpolant
//     T   -   point:
//             * T in [0,1] corresponds to interval spanned by points
//             * for non-periodic splines T < 0 (or T > 1) correspond to parts of
//               the curve before the first (after the last) point
//             * for periodic splines T < 0 (or T > 1) are projected  into  [0,1]
//               by making T=T-floor(T).
//
// Outputs:
//     X   -   X-value
//     DX  -   derivative
//     D2X -   second derivative
//     Y   -   Y-value
//     DY  -   derivative
//     D2Y -   second derivative
//
//
// ALGLIB Project: Copyright 28.05.2010 by Sergey Bochkanov
void pspline2diff2(const pspline2interpolant &p, const double t, double &x, double &dx, double &d2x, double &y, double &dy, double &d2y);

// This function calculates first and second derivative with respect to T.
//
// Inputs:
//     P   -   parametric spline interpolant
//     T   -   point:
//             * T in [0,1] corresponds to interval spanned by points
//             * for non-periodic splines T < 0 (or T > 1) correspond to parts of
//               the curve before the first (after the last) point
//             * for periodic splines T < 0 (or T > 1) are projected  into  [0,1]
//               by making T=T-floor(T).
//
// Outputs:
//     X   -   X-value
//     DX  -   derivative
//     D2X -   second derivative
//     Y   -   Y-value
//     DY  -   derivative
//     D2Y -   second derivative
//     Z   -   Z-value
//     DZ  -   derivative
//     D2Z -   second derivative
//
//
// ALGLIB Project: Copyright 28.05.2010 by Sergey Bochkanov
void pspline3diff2(const pspline3interpolant &p, const double t, double &x, double &dx, double &d2x, double &y, double &dy, double &d2y, double &z, double &dz, double &d2z);

// This function  calculates  arc length, i.e. length of  curve  between  t=a
// and t=b.
//
// Inputs:
//     P   -   parametric spline interpolant
//     A,B -   parameter values corresponding to arc ends:
//             * B > A will result in positive length returned
//             * B < A will result in negative length returned
//
// Result:
//     length of arc starting at T=A and ending at T=B.
//
//
// ALGLIB Project: Copyright 30.05.2010 by Sergey Bochkanov
double pspline2arclength(const pspline2interpolant &p, const double a, const double b);

// This function  calculates  arc length, i.e. length of  curve  between  t=a
// and t=b.
//
// Inputs:
//     P   -   parametric spline interpolant
//     A,B -   parameter values corresponding to arc ends:
//             * B > A will result in positive length returned
//             * B < A will result in negative length returned
//
// Result:
//     length of arc starting at T=A and ending at T=B.
//
//
// ALGLIB Project: Copyright 30.05.2010 by Sergey Bochkanov
double pspline3arclength(const pspline3interpolant &p, const double a, const double b);

// This  subroutine fits piecewise linear curve to points with Ramer-Douglas-
// Peucker algorithm. This  function  performs PARAMETRIC fit, i.e. it can be
// used to fit curves like circles.
//
// On  input  it  accepts dataset which describes parametric multidimensional
// curve X(t), with X being vector, and t taking values in [0,N), where N  is
// a number of points in dataset. As result, it returns reduced  dataset  X2,
// which can be used to build  parametric  curve  X2(t),  which  approximates
// X(t) with desired precision (or has specified number of sections).
//
//
// Inputs:
//     X       -   array of multidimensional points:
//                 * at least N elements, leading N elements are used if more
//                   than N elements were specified
//                 * order of points is IMPORTANT because  it  is  parametric
//                   fit
//                 * each row of array is one point which has D coordinates
//     N       -   number of elements in X
//     D       -   number of dimensions (elements per row of X)
//     StopM   -   stopping condition - desired number of sections:
//                 * at most M sections are generated by this function
//                 * less than M sections can be generated if we have N < M
//                   (or some X are non-distinct).
//                 * zero StopM means that algorithm does not stop after
//                   achieving some pre-specified section count
//     StopEps -   stopping condition - desired precision:
//                 * algorithm stops after error in each section is at most Eps
//                 * zero Eps means that algorithm does not stop after
//                   achieving some pre-specified precision
//
// Outputs:
//     X2      -   array of corner points for piecewise approximation,
//                 has length NSections+1 or zero (for NSections=0).
//     Idx2    -   array of indexes (parameter values):
//                 * has length NSections+1 or zero (for NSections=0).
//                 * each element of Idx2 corresponds to same-numbered
//                   element of X2
//                 * each element of Idx2 is index of  corresponding  element
//                   of X2 at original array X, i.e. I-th  row  of  X2  is
//                   Idx2[I]-th row of X.
//                 * elements of Idx2 can be treated as parameter values
//                   which should be used when building new parametric curve
//                 * Idx2[0]=0, Idx2[NSections]=N-1
//     NSections-  number of sections found by algorithm, NSections <= M,
//                 NSections can be zero for degenerate datasets
//                 (N <= 1 or all X[] are non-distinct).
//
// NOTE: algorithm stops after:
//       a) dividing curve into StopM sections
//       b) achieving required precision StopEps
//       c) dividing curve into N-1 sections
//       If both StopM and StopEps are non-zero, algorithm is stopped by  the
//       FIRST criterion which is satisfied. In case both StopM  and  StopEps
//       are zero, algorithm stops because of (c).
// ALGLIB: Copyright 02.10.2014 by Sergey Bochkanov
void parametricrdpfixed(const real_2d_array &x, const ae_int_t n, const ae_int_t d, const ae_int_t stopm, const double stopeps, real_2d_array &x2, integer_1d_array &idx2, ae_int_t &nsections);
} // end of namespace alglib

// === SPLINE3D Package ===
// Depends on: SPLINE1D
namespace alglib_impl {
struct spline3dinterpolant {
   ae_int_t k;
   ae_int_t stype;
   ae_int_t n;
   ae_int_t m;
   ae_int_t l;
   ae_int_t d;
   ae_vector x;
   ae_vector y;
   ae_vector z;
   ae_vector f;
};
void spline3dinterpolant_init(void *_p, bool make_automatic);
void spline3dinterpolant_copy(void *_dst, void *_src, bool make_automatic);
void spline3dinterpolant_free(void *_p, bool make_automatic);

double spline3dcalc(spline3dinterpolant *c, double x, double y, double z);
void spline3dlintransxyz(spline3dinterpolant *c, double ax, double bx, double ay, double by, double az, double bz);
void spline3dlintransf(spline3dinterpolant *c, double a, double b);
void spline3dcopy(spline3dinterpolant *c, spline3dinterpolant *cc);
void spline3dresampletrilinear(RVector *a, ae_int_t oldzcount, ae_int_t oldycount, ae_int_t oldxcount, ae_int_t newzcount, ae_int_t newycount, ae_int_t newxcount, RVector *b);
void spline3dbuildtrilinearv(RVector *x, ae_int_t n, RVector *y, ae_int_t m, RVector *z, ae_int_t l, RVector *f, ae_int_t d, spline3dinterpolant *c);
void spline3dcalcvbuf(spline3dinterpolant *c, double x, double y, double z, RVector *f);
void spline3dcalcv(spline3dinterpolant *c, double x, double y, double z, RVector *f);
void spline3dunpackv(spline3dinterpolant *c, ae_int_t *n, ae_int_t *m, ae_int_t *l, ae_int_t *d, ae_int_t *stype, RMatrix *tbl);
} // end of namespace alglib_impl

namespace alglib {
// 3-dimensional spline inteprolant
DecClass(spline3dinterpolant, EndD);

// This subroutine calculates the value of the trilinear or tricubic spline at
// the given point (X,Y,Z).
//
// Inputs:
//     C   -   coefficients table.
//             Built by BuildBilinearSpline or BuildBicubicSpline.
//     X, Y,
//     Z   -   point
//
// Result:
//     S(x,y,z)
//
// ALGLIB Project: Copyright 26.04.2012 by Sergey Bochkanov
double spline3dcalc(const spline3dinterpolant &c, const double x, const double y, const double z);

// This subroutine performs linear transformation of the spline argument.
//
// Inputs:
//     C       -   spline interpolant
//     AX, BX  -   transformation coefficients: x = A*u + B
//     AY, BY  -   transformation coefficients: y = A*v + B
//     AZ, BZ  -   transformation coefficients: z = A*w + B
//
// Outputs:
//     C   -   transformed spline
//
// ALGLIB Project: Copyright 26.04.2012 by Sergey Bochkanov
void spline3dlintransxyz(const spline3dinterpolant &c, const double ax, const double bx, const double ay, const double by, const double az, const double bz);

// This subroutine performs linear transformation of the spline.
//
// Inputs:
//     C   -   spline interpolant.
//     A, B-   transformation coefficients: S2(x,y) = A*S(x,y,z) + B
//
// Outputs:
//     C   -   transformed spline
//
// ALGLIB Project: Copyright 26.04.2012 by Sergey Bochkanov
void spline3dlintransf(const spline3dinterpolant &c, const double a, const double b);

// Trilinear spline resampling
//
// Inputs:
//     A           -   array[0..OldXCount*OldYCount*OldZCount-1], function
//                     values at the old grid, :
//                         A[0]        x=0,y=0,z=0
//                         A[1]        x=1,y=0,z=0
//                         A[..]       ...
//                         A[..]       x=oldxcount-1,y=0,z=0
//                         A[..]       x=0,y=1,z=0
//                         A[..]       ...
//                         ...
//     OldZCount   -   old Z-count, OldZCount > 1
//     OldYCount   -   old Y-count, OldYCount > 1
//     OldXCount   -   old X-count, OldXCount > 1
//     NewZCount   -   new Z-count, NewZCount > 1
//     NewYCount   -   new Y-count, NewYCount > 1
//     NewXCount   -   new X-count, NewXCount > 1
//
// Outputs:
//     B           -   array[0..NewXCount*NewYCount*NewZCount-1], function
//                     values at the new grid:
//                         B[0]        x=0,y=0,z=0
//                         B[1]        x=1,y=0,z=0
//                         B[..]       ...
//                         B[..]       x=newxcount-1,y=0,z=0
//                         B[..]       x=0,y=1,z=0
//                         B[..]       ...
//                         ...
//
// ALGLIB Routine: Copyright 26.04.2012 by Sergey Bochkanov
void spline3dresampletrilinear(const real_1d_array &a, const ae_int_t oldzcount, const ae_int_t oldycount, const ae_int_t oldxcount, const ae_int_t newzcount, const ae_int_t newycount, const ae_int_t newxcount, real_1d_array &b);

// This subroutine builds trilinear vector-valued spline.
//
// Inputs:
//     X   -   spline abscissas,  array[0..N-1]
//     Y   -   spline ordinates,  array[0..M-1]
//     Z   -   spline applicates, array[0..L-1]
//     F   -   function values, array[0..M*N*L*D-1]:
//             * first D elements store D values at (X[0],Y[0],Z[0])
//             * next D elements store D values at (X[1],Y[0],Z[0])
//             * next D elements store D values at (X[2],Y[0],Z[0])
//             * ...
//             * next D elements store D values at (X[0],Y[1],Z[0])
//             * next D elements store D values at (X[1],Y[1],Z[0])
//             * next D elements store D values at (X[2],Y[1],Z[0])
//             * ...
//             * next D elements store D values at (X[0],Y[0],Z[1])
//             * next D elements store D values at (X[1],Y[0],Z[1])
//             * next D elements store D values at (X[2],Y[0],Z[1])
//             * ...
//             * general form - D function values at (X[i],Y[j]) are stored
//               at F[D*(N*(M*K+J)+I)...D*(N*(M*K+J)+I)+D-1].
//     M,N,
//     L   -   grid size, M >= 2, N >= 2, L >= 2
//     D   -   vector dimension, D >= 1
//
// Outputs:
//     C   -   spline interpolant
//
// ALGLIB Project: Copyright 26.04.2012 by Sergey Bochkanov
void spline3dbuildtrilinearv(const real_1d_array &x, const ae_int_t n, const real_1d_array &y, const ae_int_t m, const real_1d_array &z, const ae_int_t l, const real_1d_array &f, const ae_int_t d, spline3dinterpolant &c);

// This subroutine calculates bilinear or bicubic vector-valued spline at the
// given point (X,Y,Z).
//
// Inputs:
//     C   -   spline interpolant.
//     X, Y,
//     Z   -   point
//     F   -   output buffer, possibly preallocated array. In case array size
//             is large enough to store result, it is not reallocated.  Array
//             which is too short will be reallocated
//
// Outputs:
//     F   -   array[D] (or larger) which stores function values
//
// ALGLIB Project: Copyright 26.04.2012 by Sergey Bochkanov
void spline3dcalcvbuf(const spline3dinterpolant &c, const double x, const double y, const double z, real_1d_array &f);

// This subroutine calculates trilinear or tricubic vector-valued spline at the
// given point (X,Y,Z).
//
// Inputs:
//     C   -   spline interpolant.
//     X, Y,
//     Z   -   point
//
// Outputs:
//     F   -   array[D] which stores function values.  F is out-parameter and
//             it  is  reallocated  after  call to this function. In case you
//             want  to    reuse  previously  allocated  F,   you   may   use
//             Spline2DCalcVBuf(),  which  reallocates  F only when it is too
//             small.
//
// ALGLIB Project: Copyright 26.04.2012 by Sergey Bochkanov
void spline3dcalcv(const spline3dinterpolant &c, const double x, const double y, const double z, real_1d_array &f);

// This subroutine unpacks tri-dimensional spline into the coefficients table
//
// Inputs:
//     C   -   spline interpolant.
//
// Result:
//     N   -   grid size (X)
//     M   -   grid size (Y)
//     L   -   grid size (Z)
//     D   -   number of components
//     SType-  spline type. Currently, only one spline type is supported:
//             trilinear spline, as indicated by SType=1.
//     Tbl -   spline coefficients: [0..(N-1)*(M-1)*(L-1)*D-1, 0..13].
//             For T=0..D-1 (component index), I = 0...N-2 (x index),
//             J=0..M-2 (y index), K=0..L-2 (z index):
//                 Q := T + I*D + J*D*(N-1) + K*D*(N-1)*(M-1),
//
//                 Q-th row stores decomposition for T-th component of the
//                 vector-valued function
//
//                 Tbl[Q,0] = X[i]
//                 Tbl[Q,1] = X[i+1]
//                 Tbl[Q,2] = Y[j]
//                 Tbl[Q,3] = Y[j+1]
//                 Tbl[Q,4] = Z[k]
//                 Tbl[Q,5] = Z[k+1]
//
//                 Tbl[Q,6] = C000
//                 Tbl[Q,7] = C100
//                 Tbl[Q,8] = C010
//                 Tbl[Q,9] = C110
//                 Tbl[Q,10]= C001
//                 Tbl[Q,11]= C101
//                 Tbl[Q,12]= C011
//                 Tbl[Q,13]= C111
//             On each grid square spline is equals to:
//                 S(x) = SUM(c[i,j,k]*(x^i)*(y^j)*(z^k), i=0..1, j=0..1, k=0..1)
//                 t = x-x[j]
//                 u = y-y[i]
//                 v = z-z[k]
//
//             NOTE: format of Tbl is given for SType=1. Future versions of
//                   ALGLIB can use different formats for different values of
//                   SType.
//
// ALGLIB Project: Copyright 26.04.2012 by Sergey Bochkanov
void spline3dunpackv(const spline3dinterpolant &c, ae_int_t &n, ae_int_t &m, ae_int_t &l, ae_int_t &d, ae_int_t &stype, real_2d_array &tbl);
} // end of namespace alglib

// === POLINT Package ===
// Depends on: RATINT
namespace alglib_impl {
void polynomialbar2cheb(barycentricinterpolant *p, double a, double b, RVector *t);
void polynomialcheb2bar(RVector *t, ae_int_t n, double a, double b, barycentricinterpolant *p);
void polynomialbar2pow(barycentricinterpolant *p, double c, double s, RVector *a);
void polynomialpow2bar(RVector *a, ae_int_t n, double c, double s, barycentricinterpolant *p);
void polynomialbuild(RVector *x, RVector *y, ae_int_t n, barycentricinterpolant *p);
void polynomialbuildeqdist(double a, double b, RVector *y, ae_int_t n, barycentricinterpolant *p);
void polynomialbuildcheb1(double a, double b, RVector *y, ae_int_t n, barycentricinterpolant *p);
void polynomialbuildcheb2(double a, double b, RVector *y, ae_int_t n, barycentricinterpolant *p);
double polynomialcalceqdist(double a, double b, RVector *f, ae_int_t n, double t);
double polynomialcalccheb1(double a, double b, RVector *f, ae_int_t n, double t);
double polynomialcalccheb2(double a, double b, RVector *f, ae_int_t n, double t);
} // end of namespace alglib_impl

namespace alglib {
// Conversion from barycentric representation to Chebyshev basis.
// This function has O(N^2) complexity.
//
// Inputs:
//     P   -   polynomial in barycentric form
//     A,B -   base interval for Chebyshev polynomials (see below)
//             A != B
//
// Outputs:
//     T   -   coefficients of Chebyshev representation;
//             P(x) = sum { T[i]*Ti(2*(x-A)/(B-A)-1), i=0..N-1 },
//             where Ti - I-th Chebyshev polynomial.
//
// NOTES:
//     barycentric interpolant passed as P may be either polynomial  obtained
//     from  polynomial  interpolation/ fitting or rational function which is
//     NOT polynomial. We can't distinguish between these two cases, and this
//     algorithm just tries to work assuming that P IS a polynomial.  If not,
//     algorithm will return results, but they won't have any meaning.
// ALGLIB: Copyright 30.09.2010 by Sergey Bochkanov
void polynomialbar2cheb(const barycentricinterpolant &p, const double a, const double b, real_1d_array &t);

// Conversion from Chebyshev basis to barycentric representation.
// This function has O(N^2) complexity.
//
// Inputs:
//     T   -   coefficients of Chebyshev representation;
//             P(x) = sum { T[i]*Ti(2*(x-A)/(B-A)-1), i=0..N },
//             where Ti - I-th Chebyshev polynomial.
//     N   -   number of coefficients:
//             * if given, only leading N elements of T are used
//             * if not given, automatically determined from size of T
//     A,B -   base interval for Chebyshev polynomials (see above)
//             A < B
//
// Outputs:
//     P   -   polynomial in barycentric form
// ALGLIB: Copyright 30.09.2010 by Sergey Bochkanov
void polynomialcheb2bar(const real_1d_array &t, const ae_int_t n, const double a, const double b, barycentricinterpolant &p);
void polynomialcheb2bar(const real_1d_array &t, const double a, const double b, barycentricinterpolant &p);

// Conversion from barycentric representation to power basis.
// This function has O(N^2) complexity.
//
// Inputs:
//     P   -   polynomial in barycentric form
//     C   -   offset (see below); 0.0 is used as default value.
//     S   -   scale (see below);  1.0 is used as default value. S != 0.
//
// Outputs:
//     A   -   coefficients, P(x) = sum { A[i]*((X-C)/S)^i, i=0..N-1 }
//     N   -   number of coefficients (polynomial degree plus 1)
//
// NOTES:
// 1.  this function accepts offset and scale, which can be  set  to  improve
//     numerical properties of polynomial. For example, if P was obtained  as
//     result of interpolation on [-1,+1],  you  can  set  C=0  and  S=1  and
//     represent  P  as sum of 1, x, x^2, x^3 and so on. In most cases you it
//     is exactly what you need.
//
//     However, if your interpolation model was built on [999,1001], you will
//     see significant growth of numerical errors when using {1, x, x^2, x^3}
//     as basis. Representing P as sum of 1, (x-1000), (x-1000)^2, (x-1000)^3
//     will be better option. Such representation can be  obtained  by  using
//     1000.0 as offset C and 1.0 as scale S.
//
// 2.  power basis is ill-conditioned and tricks described above can't  solve
//     this problem completely. This function  will  return  coefficients  in
//     any  case,  but  for  N > 8  they  will  become unreliable. However, N's
//     less than 5 are pretty safe.
//
// 3.  barycentric interpolant passed as P may be either polynomial  obtained
//     from  polynomial  interpolation/ fitting or rational function which is
//     NOT polynomial. We can't distinguish between these two cases, and this
//     algorithm just tries to work assuming that P IS a polynomial.  If not,
//     algorithm will return results, but they won't have any meaning.
// ALGLIB: Copyright 30.09.2010 by Sergey Bochkanov
void polynomialbar2pow(const barycentricinterpolant &p, const double c, const double s, real_1d_array &a);
void polynomialbar2pow(const barycentricinterpolant &p, real_1d_array &a);

// Conversion from power basis to barycentric representation.
// This function has O(N^2) complexity.
//
// Inputs:
//     A   -   coefficients, P(x) = sum { A[i]*((X-C)/S)^i, i=0..N-1 }
//     N   -   number of coefficients (polynomial degree plus 1)
//             * if given, only leading N elements of A are used
//             * if not given, automatically determined from size of A
//     C   -   offset (see below); 0.0 is used as default value.
//     S   -   scale (see below);  1.0 is used as default value. S != 0.
//
// Outputs:
//     P   -   polynomial in barycentric form
//
//
// NOTES:
// 1.  this function accepts offset and scale, which can be  set  to  improve
//     numerical properties of polynomial. For example, if you interpolate on
//     [-1,+1],  you  can  set C=0 and S=1 and convert from sum of 1, x, x^2,
//     x^3 and so on. In most cases you it is exactly what you need.
//
//     However, if your interpolation model was built on [999,1001], you will
//     see significant growth of numerical errors when using {1, x, x^2, x^3}
//     as  input  basis.  Converting  from  sum  of  1, (x-1000), (x-1000)^2,
//     (x-1000)^3 will be better option (you have to specify 1000.0 as offset
//     C and 1.0 as scale S).
//
// 2.  power basis is ill-conditioned and tricks described above can't  solve
//     this problem completely. This function  will  return barycentric model
//     in any case, but for N > 8 accuracy well degrade. However, N's less than
//     5 are pretty safe.
// ALGLIB: Copyright 30.09.2010 by Sergey Bochkanov
void polynomialpow2bar(const real_1d_array &a, const ae_int_t n, const double c, const double s, barycentricinterpolant &p);
void polynomialpow2bar(const real_1d_array &a, barycentricinterpolant &p);

// Lagrange intepolant: generation of the model on the general grid.
// This function has O(N^2) complexity.
//
// Inputs:
//     X   -   abscissas, array[0..N-1]
//     Y   -   function values, array[0..N-1]
//     N   -   number of points, N >= 1
//
// Outputs:
//     P   -   barycentric model which represents Lagrange interpolant
//             (see ratint unit info and BarycentricCalc() description for
//             more information).
// ALGLIB: Copyright 02.12.2009 by Sergey Bochkanov
void polynomialbuild(const real_1d_array &x, const real_1d_array &y, const ae_int_t n, barycentricinterpolant &p);
void polynomialbuild(const real_1d_array &x, const real_1d_array &y, barycentricinterpolant &p);

// Lagrange intepolant: generation of the model on equidistant grid.
// This function has O(N) complexity.
//
// Inputs:
//     A   -   left boundary of [A,B]
//     B   -   right boundary of [A,B]
//     Y   -   function values at the nodes, array[0..N-1]
//     N   -   number of points, N >= 1
//             for N=1 a constant model is constructed.
//
// Outputs:
//     P   -   barycentric model which represents Lagrange interpolant
//             (see ratint unit info and BarycentricCalc() description for
//             more information).
// ALGLIB: Copyright 03.12.2009 by Sergey Bochkanov
void polynomialbuildeqdist(const double a, const double b, const real_1d_array &y, const ae_int_t n, barycentricinterpolant &p);
void polynomialbuildeqdist(const double a, const double b, const real_1d_array &y, barycentricinterpolant &p);

// Lagrange intepolant on Chebyshev grid (first kind).
// This function has O(N) complexity.
//
// Inputs:
//     A   -   left boundary of [A,B]
//     B   -   right boundary of [A,B]
//     Y   -   function values at the nodes, array[0..N-1],
//             Y[I] = Y(0.5*(B+A) + 0.5*(B-A)*cos(PI*(2*i+1)/(2*n)))
//     N   -   number of points, N >= 1
//             for N=1 a constant model is constructed.
//
// Outputs:
//     P   -   barycentric model which represents Lagrange interpolant
//             (see ratint unit info and BarycentricCalc() description for
//             more information).
// ALGLIB: Copyright 03.12.2009 by Sergey Bochkanov
void polynomialbuildcheb1(const double a, const double b, const real_1d_array &y, const ae_int_t n, barycentricinterpolant &p);
void polynomialbuildcheb1(const double a, const double b, const real_1d_array &y, barycentricinterpolant &p);

// Lagrange intepolant on Chebyshev grid (second kind).
// This function has O(N) complexity.
//
// Inputs:
//     A   -   left boundary of [A,B]
//     B   -   right boundary of [A,B]
//     Y   -   function values at the nodes, array[0..N-1],
//             Y[I] = Y(0.5*(B+A) + 0.5*(B-A)*cos(PI*i/(n-1)))
//     N   -   number of points, N >= 1
//             for N=1 a constant model is constructed.
//
// Outputs:
//     P   -   barycentric model which represents Lagrange interpolant
//             (see ratint unit info and BarycentricCalc() description for
//             more information).
// ALGLIB: Copyright 03.12.2009 by Sergey Bochkanov
void polynomialbuildcheb2(const double a, const double b, const real_1d_array &y, const ae_int_t n, barycentricinterpolant &p);
void polynomialbuildcheb2(const double a, const double b, const real_1d_array &y, barycentricinterpolant &p);

// Fast equidistant polynomial interpolation function with O(N) complexity
//
// Inputs:
//     A   -   left boundary of [A,B]
//     B   -   right boundary of [A,B]
//     F   -   function values, array[0..N-1]
//     N   -   number of points on equidistant grid, N >= 1
//             for N=1 a constant model is constructed.
//     T   -   position where P(x) is calculated
//
// Result:
//     value of the Lagrange interpolant at T
//
// IMPORTANT
//     this function provides fast interface which is not overflow-safe
//     nor it is very precise.
//     the best option is to use  PolynomialBuildEqDist()/BarycentricCalc()
//     subroutines unless you are pretty sure that your data will not result
//     in overflow.
// ALGLIB: Copyright 02.12.2009 by Sergey Bochkanov
double polynomialcalceqdist(const double a, const double b, const real_1d_array &f, const ae_int_t n, const double t);
double polynomialcalceqdist(const double a, const double b, const real_1d_array &f, const double t);

// Fast polynomial interpolation function on Chebyshev points (first kind)
// with O(N) complexity.
//
// Inputs:
//     A   -   left boundary of [A,B]
//     B   -   right boundary of [A,B]
//     F   -   function values, array[0..N-1]
//     N   -   number of points on Chebyshev grid (first kind),
//             X[i] = 0.5*(B+A) + 0.5*(B-A)*cos(PI*(2*i+1)/(2*n))
//             for N=1 a constant model is constructed.
//     T   -   position where P(x) is calculated
//
// Result:
//     value of the Lagrange interpolant at T
//
// IMPORTANT
//     this function provides fast interface which is not overflow-safe
//     nor it is very precise.
//     the best option is to use  PolIntBuildCheb1()/BarycentricCalc()
//     subroutines unless you are pretty sure that your data will not result
//     in overflow.
// ALGLIB: Copyright 02.12.2009 by Sergey Bochkanov
double polynomialcalccheb1(const double a, const double b, const real_1d_array &f, const ae_int_t n, const double t);
double polynomialcalccheb1(const double a, const double b, const real_1d_array &f, const double t);

// Fast polynomial interpolation function on Chebyshev points (second kind)
// with O(N) complexity.
//
// Inputs:
//     A   -   left boundary of [A,B]
//     B   -   right boundary of [A,B]
//     F   -   function values, array[0..N-1]
//     N   -   number of points on Chebyshev grid (second kind),
//             X[i] = 0.5*(B+A) + 0.5*(B-A)*cos(PI*i/(n-1))
//             for N=1 a constant model is constructed.
//     T   -   position where P(x) is calculated
//
// Result:
//     value of the Lagrange interpolant at T
//
// IMPORTANT
//     this function provides fast interface which is not overflow-safe
//     nor it is very precise.
//     the best option is to use PolIntBuildCheb2()/BarycentricCalc()
//     subroutines unless you are pretty sure that your data will not result
//     in overflow.
// ALGLIB: Copyright 02.12.2009 by Sergey Bochkanov
double polynomialcalccheb2(const double a, const double b, const real_1d_array &f, const ae_int_t n, const double t);
double polynomialcalccheb2(const double a, const double b, const real_1d_array &f, const double t);
} // end of namespace alglib

// === LSFIT Package ===
// Depends on: (Optimization) MINLM
// Depends on: SPLINE1D, POLINT
namespace alglib_impl {
struct polynomialfitreport {
   double taskrcond;
   double rmserror;
   double avgerror;
   double avgrelerror;
   double maxerror;
};
void polynomialfitreport_init(void *_p, bool make_automatic);
void polynomialfitreport_copy(void *_dst, void *_src, bool make_automatic);
void polynomialfitreport_free(void *_p, bool make_automatic);

struct barycentricfitreport {
   double taskrcond;
   ae_int_t dbest;
   double rmserror;
   double avgerror;
   double avgrelerror;
   double maxerror;
};
void barycentricfitreport_init(void *_p, bool make_automatic);
void barycentricfitreport_copy(void *_dst, void *_src, bool make_automatic);
void barycentricfitreport_free(void *_p, bool make_automatic);

struct lsfitreport {
   double taskrcond;
   ae_int_t iterationscount;
   ae_int_t varidx;
   double rmserror;
   double avgerror;
   double avgrelerror;
   double maxerror;
   double wrmserror;
   ae_matrix covpar;
   ae_vector errpar;
   ae_vector errcurve;
   ae_vector noise;
   double r2;
};
void lsfitreport_init(void *_p, bool make_automatic);
void lsfitreport_copy(void *_dst, void *_src, bool make_automatic);
void lsfitreport_free(void *_p, bool make_automatic);

struct lsfitstate {
   ae_int_t optalgo;
   ae_int_t m;
   ae_int_t k;
   double epsx;
   ae_int_t maxits;
   double stpmax;
   bool xrep;
   ae_vector c0;
   ae_vector c1;
   ae_vector s;
   ae_vector bndl;
   ae_vector bndu;
   ae_matrix taskx;
   ae_vector tasky;
   ae_int_t npoints;
   ae_vector taskw;
   ae_int_t nweights;
   ae_int_t wkind;
   ae_int_t wits;
   double diffstep;
   double teststep;
   ae_matrix cleic;
   ae_int_t nec;
   ae_int_t nic;
   bool xupdated;
   bool needf;
   bool needfg;
   bool needfgh;
   ae_int_t pointindex;
   ae_vector x;
   ae_vector c;
   double f;
   ae_vector g;
   ae_matrix h;
   ae_vector wcur;
   ae_vector tmpct;
   ae_vector tmp;
   ae_vector tmpf;
   ae_matrix tmpjac;
   ae_matrix tmpjacw;
   double tmpnoise;
   matinvreport invrep;
   ae_int_t repiterationscount;
   ae_int_t repterminationtype;
   ae_int_t repvaridx;
   double reprmserror;
   double repavgerror;
   double repavgrelerror;
   double repmaxerror;
   double repwrmserror;
   lsfitreport rep;
   minlmstate optstate;
   minlmreport optrep;
   ae_int_t prevnpt;
   ae_int_t prevalgo;
   ae_int_t PQ;
};
void lsfitstate_init(void *_p, bool make_automatic);
void lsfitstate_copy(void *_dst, void *_src, bool make_automatic);
void lsfitstate_free(void *_p, bool make_automatic);

void lstfitpiecewiselinearrdpfixed(RVector *x, RVector *y, ae_int_t n, ae_int_t m, RVector *x2, RVector *y2, ae_int_t *nsections);
void lstfitpiecewiselinearrdp(RVector *x, RVector *y, ae_int_t n, double eps, RVector *x2, RVector *y2, ae_int_t *nsections);
void polynomialfit(RVector *x, RVector *y, ae_int_t n, ae_int_t m, ae_int_t *info, barycentricinterpolant *p, polynomialfitreport *rep);
void polynomialfitwc(RVector *x, RVector *y, RVector *w, ae_int_t n, RVector *xc, RVector *yc, ZVector *dc, ae_int_t k, ae_int_t m, ae_int_t *info, barycentricinterpolant *p, polynomialfitreport *rep);
double logisticcalc4(double x, double a, double b, double c, double d);
double logisticcalc5(double x, double a, double b, double c, double d, double g);
void logisticfit4(RVector *x, RVector *y, ae_int_t n, double *a, double *b, double *c, double *d, lsfitreport *rep);
void logisticfit4ec(RVector *x, RVector *y, ae_int_t n, double cnstrleft, double cnstrright, double *a, double *b, double *c, double *d, lsfitreport *rep);
void logisticfit5(RVector *x, RVector *y, ae_int_t n, double *a, double *b, double *c, double *d, double *g, lsfitreport *rep);
void logisticfit5ec(RVector *x, RVector *y, ae_int_t n, double cnstrleft, double cnstrright, double *a, double *b, double *c, double *d, double *g, lsfitreport *rep);
void logisticfit45x(RVector *x, RVector *y, ae_int_t n, double cnstrleft, double cnstrright, bool is4pl, double lambdav, double epsx, ae_int_t rscnt, double *a, double *b, double *c, double *d, double *g, lsfitreport *rep);
void barycentricfitfloaterhormannwc(RVector *x, RVector *y, RVector *w, ae_int_t n, RVector *xc, RVector *yc, ZVector *dc, ae_int_t k, ae_int_t m, ae_int_t *info, barycentricinterpolant *b, barycentricfitreport *rep);
void barycentricfitfloaterhormann(RVector *x, RVector *y, ae_int_t n, ae_int_t m, ae_int_t *info, barycentricinterpolant *b, barycentricfitreport *rep);
void spline1dfitcubicwc(RVector *x, RVector *y, RVector *w, ae_int_t n, RVector *xc, RVector *yc, ZVector *dc, ae_int_t k, ae_int_t m, ae_int_t *info, spline1dinterpolant *s, spline1dfitreport *rep);
void spline1dfithermitewc(RVector *x, RVector *y, RVector *w, ae_int_t n, RVector *xc, RVector *yc, ZVector *dc, ae_int_t k, ae_int_t m, ae_int_t *info, spline1dinterpolant *s, spline1dfitreport *rep);
void spline1dfitcubic(RVector *x, RVector *y, ae_int_t n, ae_int_t m, ae_int_t *info, spline1dinterpolant *s, spline1dfitreport *rep);
void spline1dfithermite(RVector *x, RVector *y, ae_int_t n, ae_int_t m, ae_int_t *info, spline1dinterpolant *s, spline1dfitreport *rep);
void lsfitlinearw(RVector *y, RVector *w, RMatrix *fmatrix, ae_int_t n, ae_int_t m, ae_int_t *info, RVector *c, lsfitreport *rep);
void lsfitlinearwc(RVector *y, RVector *w, RMatrix *fmatrix, RMatrix *cmatrix, ae_int_t n, ae_int_t m, ae_int_t k, ae_int_t *info, RVector *c, lsfitreport *rep);
void lsfitlinear(RVector *y, RMatrix *fmatrix, ae_int_t n, ae_int_t m, ae_int_t *info, RVector *c, lsfitreport *rep);
void lsfitlinearc(RVector *y, RMatrix *fmatrix, RMatrix *cmatrix, ae_int_t n, ae_int_t m, ae_int_t k, ae_int_t *info, RVector *c, lsfitreport *rep);
void lsfitcreatewf(RMatrix *x, RVector *y, RVector *w, RVector *c, ae_int_t n, ae_int_t m, ae_int_t k, double diffstep, lsfitstate *state);
void lsfitcreatef(RMatrix *x, RVector *y, RVector *c, ae_int_t n, ae_int_t m, ae_int_t k, double diffstep, lsfitstate *state);
void lsfitcreatewfg(RMatrix *x, RVector *y, RVector *w, RVector *c, ae_int_t n, ae_int_t m, ae_int_t k, bool cheapfg, lsfitstate *state);
void lsfitcreatefg(RMatrix *x, RVector *y, RVector *c, ae_int_t n, ae_int_t m, ae_int_t k, bool cheapfg, lsfitstate *state);
void lsfitcreatewfgh(RMatrix *x, RVector *y, RVector *w, RVector *c, ae_int_t n, ae_int_t m, ae_int_t k, lsfitstate *state);
void lsfitcreatefgh(RMatrix *x, RVector *y, RVector *c, ae_int_t n, ae_int_t m, ae_int_t k, lsfitstate *state);
void lsfitsetcond(lsfitstate *state, double epsx, ae_int_t maxits);
void lsfitsetstpmax(lsfitstate *state, double stpmax);
void lsfitsetxrep(lsfitstate *state, bool needxrep);
void lsfitsetscale(lsfitstate *state, RVector *s);
void lsfitsetbc(lsfitstate *state, RVector *bndl, RVector *bndu);
void lsfitsetlc(lsfitstate *state, RMatrix *c, ZVector *ct, ae_int_t k);
bool lsfititeration(lsfitstate *state);
void lsfitresults(lsfitstate *state, ae_int_t *info, RVector *c, lsfitreport *rep);
void lsfitsetgradientcheck(lsfitstate *state, double teststep);
} // end of namespace alglib_impl

namespace alglib {
// Polynomial fitting report:
//     TaskRCond       reciprocal of task's condition number
//     RMSError        RMS error
//     AvgError        average error
//     AvgRelError     average relative error (for non-zero Y[I])
//     MaxError        maximum error
DecClass(polynomialfitreport, double &taskrcond; double &rmserror; double &avgerror; double &avgrelerror; double &maxerror;);

// Barycentric fitting report:
//     RMSError        RMS error
//     AvgError        average error
//     AvgRelError     average relative error (for non-zero Y[I])
//     MaxError        maximum error
//     TaskRCond       reciprocal of task's condition number
DecClass(barycentricfitreport, double &taskrcond; ae_int_t &dbest; double &rmserror; double &avgerror; double &avgrelerror; double &maxerror;);

// Least squares fitting report. This structure contains informational fields
// which are set by fitting functions provided by this unit.
//
// Different functions initialize different sets of  fields,  so  you  should
// read documentation on specific function you used in order  to  know  which
// fields are initialized.
//
//     TaskRCond       reciprocal of task's condition number
//     IterationsCount number of internal iterations
//
//     VarIdx          if user-supplied gradient contains errors  which  were
//                     detected by nonlinear fitter, this  field  is  set  to
//                     index  of  the  first  component  of gradient which is
//                     suspected to be spoiled by bugs.
//
//     RMSError        RMS error
//     AvgError        average error
//     AvgRelError     average relative error (for non-zero Y[I])
//     MaxError        maximum error
//
//     WRMSError       weighted RMS error
//
//     CovPar          covariance matrix for parameters, filled by some solvers
//     ErrPar          vector of errors in parameters, filled by some solvers
//     ErrCurve        vector of fit errors -  variability  of  the  best-fit
//                     curve, filled by some solvers.
//     Noise           vector of per-point noise estimates, filled by
//                     some solvers.
//     R2              coefficient of determination (non-weighted, non-adjusted),
//                     filled by some solvers.
DecClass(lsfitreport, double &taskrcond; ae_int_t &iterationscount; ae_int_t &varidx; double &rmserror; double &avgerror; double &avgrelerror; double &maxerror; double &wrmserror; real_2d_array covpar; real_1d_array errpar; real_1d_array errcurve; real_1d_array noise; double &r2;);

// Nonlinear fitter.
//
// You should use ALGLIB functions to work with fitter.
// Never try to access its fields directly!
DecClass(lsfitstate, bool &needf; bool &needfg; bool &needfgh; bool &xupdated; real_1d_array c; double &f; real_1d_array g; real_2d_array h; real_1d_array x;);

// This  subroutine fits piecewise linear curve to points with Ramer-Douglas-
// Peucker algorithm, which stops after generating specified number of linear
// sections.
//
// IMPORTANT:
// * it does NOT perform least-squares fitting; it  builds  curve,  but  this
//   curve does not minimize some least squares metric.  See  description  of
//   RDP algorithm (say, in Wikipedia) for more details on WHAT is performed.
// * this function does NOT work with parametric curves  (i.e.  curves  which
//   can be represented as {X(t),Y(t)}. It works with curves   which  can  be
//   represented as Y(X). Thus,  it  is  impossible  to  model  figures  like
//   circles  with  this  functions.
//   If  you  want  to  work  with  parametric   curves,   you   should   use
//   ParametricRDPFixed() function provided  by  "Parametric"  subpackage  of
//   "Interpolation" package.
//
// Inputs:
//     X       -   array of X-coordinates:
//                 * at least N elements
//                 * can be unordered (points are automatically sorted)
//                 * this function may accept non-distinct X (see below for
//                   more information on handling of such inputs)
//     Y       -   array of Y-coordinates:
//                 * at least N elements
//     N       -   number of elements in X/Y
//     M       -   desired number of sections:
//                 * at most M sections are generated by this function
//                 * less than M sections can be generated if we have N < M
//                   (or some X are non-distinct).
//
// Outputs:
//     X2      -   X-values of corner points for piecewise approximation,
//                 has length NSections+1 or zero (for NSections=0).
//     Y2      -   Y-values of corner points,
//                 has length NSections+1 or zero (for NSections=0).
//     NSections-  number of sections found by algorithm, NSections <= M,
//                 NSections can be zero for degenerate datasets
//                 (N <= 1 or all X[] are non-distinct).
//
// NOTE: X2/Y2 are ordered arrays, i.e. (X2[0],Y2[0]) is  a  first  point  of
//       curve, (X2[NSection-1],Y2[NSection-1]) is the last point.
// ALGLIB: Copyright 02.10.2014 by Sergey Bochkanov
void lstfitpiecewiselinearrdpfixed(const real_1d_array &x, const real_1d_array &y, const ae_int_t n, const ae_int_t m, real_1d_array &x2, real_1d_array &y2, ae_int_t &nsections);

// This  subroutine fits piecewise linear curve to points with Ramer-Douglas-
// Peucker algorithm, which stops after achieving desired precision.
//
// IMPORTANT:
// * it performs non-least-squares fitting; it builds curve, but  this  curve
//   does not minimize some least squares  metric.  See  description  of  RDP
//   algorithm (say, in Wikipedia) for more details on WHAT is performed.
// * this function does NOT work with parametric curves  (i.e.  curves  which
//   can be represented as {X(t),Y(t)}. It works with curves   which  can  be
//   represented as Y(X). Thus, it is impossible to model figures like circles
//   with this functions.
//   If  you  want  to  work  with  parametric   curves,   you   should   use
//   ParametricRDPFixed() function provided  by  "Parametric"  subpackage  of
//   "Interpolation" package.
//
// Inputs:
//     X       -   array of X-coordinates:
//                 * at least N elements
//                 * can be unordered (points are automatically sorted)
//                 * this function may accept non-distinct X (see below for
//                   more information on handling of such inputs)
//     Y       -   array of Y-coordinates:
//                 * at least N elements
//     N       -   number of elements in X/Y
//     Eps     -   positive number, desired precision.
//
//
// Outputs:
//     X2      -   X-values of corner points for piecewise approximation,
//                 has length NSections+1 or zero (for NSections=0).
//     Y2      -   Y-values of corner points,
//                 has length NSections+1 or zero (for NSections=0).
//     NSections-  number of sections found by algorithm,
//                 NSections can be zero for degenerate datasets
//                 (N <= 1 or all X[] are non-distinct).
//
// NOTE: X2/Y2 are ordered arrays, i.e. (X2[0],Y2[0]) is  a  first  point  of
//       curve, (X2[NSection-1],Y2[NSection-1]) is the last point.
// ALGLIB: Copyright 02.10.2014 by Sergey Bochkanov
void lstfitpiecewiselinearrdp(const real_1d_array &x, const real_1d_array &y, const ae_int_t n, const double eps, real_1d_array &x2, real_1d_array &y2, ae_int_t &nsections);

// Fitting by polynomials in barycentric form. This function provides  simple
// unterface for unconstrained unweighted fitting. See  PolynomialFitWC()  if
// you need constrained fitting.
//
// Task is linear, so linear least squares solver is used. Complexity of this
// computational scheme is O(N*M^2), mostly dominated by least squares solver
//
// SEE ALSO:
//     PolynomialFitWC()
//
// NOTES:
//     you can convert P from barycentric form  to  the  power  or  Chebyshev
//     basis with PolynomialBar2Pow() or PolynomialBar2Cheb() functions  from
//     POLINT subpackage.
//
// Inputs:
//     X   -   points, array[0..N-1].
//     Y   -   function values, array[0..N-1].
//     N   -   number of points, N > 0
//             * if given, only leading N elements of X/Y are used
//             * if not given, automatically determined from sizes of X/Y
//     M   -   number of basis functions (= polynomial_degree + 1), M >= 1
//
// Outputs:
//     Info-   same format as in LSFitLinearW() subroutine:
//             * Info > 0    task is solved
//             * Info <= 0   an error occured:
//                         -4 means inconvergence of internal SVD
//     P   -   interpolant in barycentric form.
//     Rep -   report, same format as in LSFitLinearW() subroutine.
//             Following fields are set:
//             * RMSError      rms error on the (X,Y).
//             * AvgError      average error on the (X,Y).
//             * AvgRelError   average relative error on the non-zero Y
//             * MaxError      maximum error
//                             NON-WEIGHTED ERRORS ARE CALCULATED
//
// ALGLIB Project: Copyright 10.12.2009 by Sergey Bochkanov
void polynomialfit(const real_1d_array &x, const real_1d_array &y, const ae_int_t n, const ae_int_t m, ae_int_t &info, barycentricinterpolant &p, polynomialfitreport &rep);
void polynomialfit(const real_1d_array &x, const real_1d_array &y, const ae_int_t m, ae_int_t &info, barycentricinterpolant &p, polynomialfitreport &rep);

// Weighted  fitting by polynomials in barycentric form, with constraints  on
// function values or first derivatives.
//
// Small regularizing term is used when solving constrained tasks (to improve
// stability).
//
// Task is linear, so linear least squares solver is used. Complexity of this
// computational scheme is O(N*M^2), mostly dominated by least squares solver
//
// SEE ALSO:
//     PolynomialFit()
//
// NOTES:
//     you can convert P from barycentric form  to  the  power  or  Chebyshev
//     basis with PolynomialBar2Pow() or PolynomialBar2Cheb() functions  from
//     POLINT subpackage.
//
// Inputs:
//     X   -   points, array[0..N-1].
//     Y   -   function values, array[0..N-1].
//     W   -   weights, array[0..N-1]
//             Each summand in square  sum  of  approximation deviations from
//             given  values  is  multiplied  by  the square of corresponding
//             weight. Fill it by 1's if you don't  want  to  solve  weighted
//             task.
//     N   -   number of points, N > 0.
//             * if given, only leading N elements of X/Y/W are used
//             * if not given, automatically determined from sizes of X/Y/W
//     XC  -   points where polynomial values/derivatives are constrained,
//             array[0..K-1].
//     YC  -   values of constraints, array[0..K-1]
//     DC  -   array[0..K-1], types of constraints:
//             * DC[i]=0   means that P(XC[i])=YC[i]
//             * DC[i]=1   means that P'(XC[i])=YC[i]
//             SEE BELOW FOR IMPORTANT INFORMATION ON CONSTRAINTS
//     K   -   number of constraints, 0 <= K < M.
//             K=0 means no constraints (XC/YC/DC are not used in such cases)
//     M   -   number of basis functions (= polynomial_degree + 1), M >= 1
//
// Outputs:
//     Info-   same format as in LSFitLinearW() subroutine:
//             * Info > 0    task is solved
//             * Info <= 0   an error occured:
//                         -4 means inconvergence of internal SVD
//                         -3 means inconsistent constraints
//     P   -   interpolant in barycentric form.
//     Rep -   report, same format as in LSFitLinearW() subroutine.
//             Following fields are set:
//             * RMSError      rms error on the (X,Y).
//             * AvgError      average error on the (X,Y).
//             * AvgRelError   average relative error on the non-zero Y
//             * MaxError      maximum error
//                             NON-WEIGHTED ERRORS ARE CALCULATED
//
// IMPORTANT:
//     this subroitine doesn't calculate task's condition number for K != 0.
//
// SETTING CONSTRAINTS - DANGERS AND OPPORTUNITIES:
//
// Setting constraints can lead  to undesired  results,  like ill-conditioned
// behavior, or inconsistency being detected. From the other side,  it allows
// us to improve quality of the fit. Here we summarize  our  experience  with
// constrained regression splines:
// * even simple constraints can be inconsistent, see  Wikipedia  article  on
//   this subject: http://en.wikipedia.org/wiki/Birkhoff_interpolation
// * the  greater  is  M (given  fixed  constraints),  the  more chances that
//   constraints will be consistent
// * in the general case, consistency of constraints is NOT GUARANTEED.
// * in the one special cases, however, we can  guarantee  consistency.  This
//   case  is:  M > 1  and constraints on the function values (NOT DERIVATIVES)
//
// Our final recommendation is to use constraints  WHEN  AND  ONLY  when  you
// can't solve your task without them. Anything beyond  special  cases  given
// above is not guaranteed and may result in inconsistency.
//
// ALGLIB Project: Copyright 10.12.2009 by Sergey Bochkanov
void polynomialfitwc(const real_1d_array &x, const real_1d_array &y, const real_1d_array &w, const ae_int_t n, const real_1d_array &xc, const real_1d_array &yc, const integer_1d_array &dc, const ae_int_t k, const ae_int_t m, ae_int_t &info, barycentricinterpolant &p, polynomialfitreport &rep);
void polynomialfitwc(const real_1d_array &x, const real_1d_array &y, const real_1d_array &w, const real_1d_array &xc, const real_1d_array &yc, const integer_1d_array &dc, const ae_int_t m, ae_int_t &info, barycentricinterpolant &p, polynomialfitreport &rep);

// This function calculates value of four-parameter logistic (4PL)  model  at
// specified point X. 4PL model has following form:
//
//     F(x|A,B,C,D) = D+(A-D)/(1+power(x/C,B))
//
// Inputs:
//     X       -   current point, X >= 0:
//                 * zero X is correctly handled even for B <= 0
//                 * negative X results in exception.
//     A, B, C, D- parameters of 4PL model:
//                 * A is unconstrained
//                 * B is unconstrained; zero or negative values are handled
//                   correctly.
//                 * C > 0, non-positive value results in exception
//                 * D is unconstrained
//
// Result:
//     model value at X
//
// NOTE: if B=0, denominator is assumed to be equal to 2.0 even  for  zero  X
//       (strictly speaking, 0^0 is undefined).
//
// NOTE: this function also throws exception  if  all  input  parameters  are
//       correct, but overflow was detected during calculations.
//
// NOTE: this function performs a lot of checks;  if  you  need  really  high
//       performance, consider evaluating model  yourself,  without  checking
//       for degenerate cases.
//
//
// ALGLIB Project: Copyright 14.05.2014 by Sergey Bochkanov
double logisticcalc4(const double x, const double a, const double b, const double c, const double d);

// This function calculates value of five-parameter logistic (5PL)  model  at
// specified point X. 5PL model has following form:
//
//     F(x|A,B,C,D,G) = D+(A-D)/power(1+power(x/C,B),G)
//
// Inputs:
//     X       -   current point, X >= 0:
//                 * zero X is correctly handled even for B <= 0
//                 * negative X results in exception.
//     A, B, C, D, G- parameters of 5PL model:
//                 * A is unconstrained
//                 * B is unconstrained; zero or negative values are handled
//                   correctly.
//                 * C > 0, non-positive value results in exception
//                 * D is unconstrained
//                 * G > 0, non-positive value results in exception
//
// Result:
//     model value at X
//
// NOTE: if B=0, denominator is assumed to be equal to power(2.0,G) even  for
//       zero X (strictly speaking, 0^0 is undefined).
//
// NOTE: this function also throws exception  if  all  input  parameters  are
//       correct, but overflow was detected during calculations.
//
// NOTE: this function performs a lot of checks;  if  you  need  really  high
//       performance, consider evaluating model  yourself,  without  checking
//       for degenerate cases.
//
//
// ALGLIB Project: Copyright 14.05.2014 by Sergey Bochkanov
double logisticcalc5(const double x, const double a, const double b, const double c, const double d, const double g);

// This function fits four-parameter logistic (4PL) model  to  data  provided
// by user. 4PL model has following form:
//
//     F(x|A,B,C,D) = D+(A-D)/(1+power(x/C,B))
//
// Here:
//     * A, D - unconstrained (see LogisticFit4EC() for constrained 4PL)
//     * B >= 0
//     * C > 0
//
// IMPORTANT: output of this function is constrained in  such  way that  B > 0.
//            Because 4PL model is symmetric with respect to B, there  is  no
//            need to explore  B < 0.  Constraining  B  makes  algorithm easier
//            to stabilize and debug.
//            Users  who  for  some  reason  prefer to work with negative B's
//            should transform output themselves (swap A and D, replace B  by
//            -B).
//
// 4PL fitting is implemented as follows:
// * we perform small number of restarts from random locations which helps to
//   solve problem of bad local extrema. Locations are only partially  random
//   - we use input data to determine good  initial  guess,  but  we  include
//   controlled amount of randomness.
// * we perform Levenberg-Marquardt fitting with very  tight  constraints  on
//   parameters B and C - it allows us to find good  initial  guess  for  the
//   second stage without risk of running into "flat spot".
// * second  Levenberg-Marquardt  round  is   performed   without   excessive
//   constraints. Results from the previous round are used as initial guess.
// * after fitting is done, we compare results with best values found so far,
//   rewrite "best solution" if needed, and move to next random location.
//
// Overall algorithm is very stable and is not prone to  bad  local  extrema.
// Furthermore, it automatically scales when input data have  very  large  or
// very small range.
//
// Inputs:
//     X       -   array[N], stores X-values.
//                 MUST include only non-negative numbers  (but  may  include
//                 zero values). Can be unsorted.
//     Y       -   array[N], values to fit.
//     N       -   number of points. If N is less than  length  of  X/Y, only
//                 leading N elements are used.
//
// Outputs:
//     A, B, C, D- parameters of 4PL model
//     Rep     -   fitting report. This structure has many fields,  but  ONLY
//                 ONES LISTED BELOW ARE SET:
//                 * Rep.IterationsCount - number of iterations performed
//                 * Rep.RMSError - root-mean-square error
//                 * Rep.AvgError - average absolute error
//                 * Rep.AvgRelError - average relative error (calculated for
//                   non-zero Y-values)
//                 * Rep.MaxError - maximum absolute error
//                 * Rep.R2 - coefficient of determination,  R-squared.  This
//                   coefficient   is  calculated  as  R2=1-RSS/TSS  (in case
//                   of nonlinear  regression  there  are  multiple  ways  to
//                   define R2, each of them giving different results).
//
// NOTE: for stability reasons the B parameter is restricted by [1/1000,1000]
//       range. It prevents  algorithm from making trial steps  deep into the
//       area of bad parameters.
//
// NOTE: after  you  obtained  coefficients,  you  can  evaluate  model  with
//       LogisticCalc4() function.
//
// NOTE: if you need better control over fitting process than provided by this
//       function, you may use LogisticFit45X().
//
// NOTE: step is automatically scaled according to scale of parameters  being
//       fitted before we compare its length with EpsX. Thus,  this  function
//       can be used to fit data with very small or very large values without
//       changing EpsX.
//
//
// ALGLIB Project: Copyright 14.02.2014 by Sergey Bochkanov
void logisticfit4(const real_1d_array &x, const real_1d_array &y, const ae_int_t n, double &a, double &b, double &c, double &d, lsfitreport &rep);

// This function fits four-parameter logistic (4PL) model  to  data  provided
// by user, with optional constraints on parameters A and D.  4PL  model  has
// following form:
//
//     F(x|A,B,C,D) = D+(A-D)/(1+power(x/C,B))
//
// Here:
//     * A, D - with optional equality constraints
//     * B >= 0
//     * C > 0
//
// IMPORTANT: output of this function is constrained in  such  way that  B > 0.
//            Because 4PL model is symmetric with respect to B, there  is  no
//            need to explore  B < 0.  Constraining  B  makes  algorithm easier
//            to stabilize and debug.
//            Users  who  for  some  reason  prefer to work with negative B's
//            should transform output themselves (swap A and D, replace B  by
//            -B).
//
// 4PL fitting is implemented as follows:
// * we perform small number of restarts from random locations which helps to
//   solve problem of bad local extrema. Locations are only partially  random
//   - we use input data to determine good  initial  guess,  but  we  include
//   controlled amount of randomness.
// * we perform Levenberg-Marquardt fitting with very  tight  constraints  on
//   parameters B and C - it allows us to find good  initial  guess  for  the
//   second stage without risk of running into "flat spot".
// * second  Levenberg-Marquardt  round  is   performed   without   excessive
//   constraints. Results from the previous round are used as initial guess.
// * after fitting is done, we compare results with best values found so far,
//   rewrite "best solution" if needed, and move to next random location.
//
// Overall algorithm is very stable and is not prone to  bad  local  extrema.
// Furthermore, it automatically scales when input data have  very  large  or
// very small range.
//
// Inputs:
//     X       -   array[N], stores X-values.
//                 MUST include only non-negative numbers  (but  may  include
//                 zero values). Can be unsorted.
//     Y       -   array[N], values to fit.
//     N       -   number of points. If N is less than  length  of  X/Y, only
//                 leading N elements are used.
//     CnstrLeft-  optional equality constraint for model value at the   left
//                 boundary (at X=0). Specify NAN (Not-a-Number)  if  you  do
//                 not need constraint on the model value at X=0 (in C++  you
//                 can pass NAN as parameter, in  C#  it  will  be
//                 Double.NaN).
//                 See  below,  section  "EQUALITY  CONSTRAINTS"   for   more
//                 information about constraints.
//     CnstrRight- optional equality constraint for model value at X=infinity.
//                 Specify NAN (Not-a-Number) if you do not  need  constraint
//                 on the model value (in C++  you can pass NAN as
//                 parameter, in  C# it will  be Double.NaN).
//                 See  below,  section  "EQUALITY  CONSTRAINTS"   for   more
//                 information about constraints.
//
// Outputs:
//     A, B, C, D- parameters of 4PL model
//     Rep     -   fitting report. This structure has many fields,  but  ONLY
//                 ONES LISTED BELOW ARE SET:
//                 * Rep.IterationsCount - number of iterations performed
//                 * Rep.RMSError - root-mean-square error
//                 * Rep.AvgError - average absolute error
//                 * Rep.AvgRelError - average relative error (calculated for
//                   non-zero Y-values)
//                 * Rep.MaxError - maximum absolute error
//                 * Rep.R2 - coefficient of determination,  R-squared.  This
//                   coefficient   is  calculated  as  R2=1-RSS/TSS  (in case
//                   of nonlinear  regression  there  are  multiple  ways  to
//                   define R2, each of them giving different results).
//
// NOTE: for stability reasons the B parameter is restricted by [1/1000,1000]
//       range. It prevents  algorithm from making trial steps  deep into the
//       area of bad parameters.
//
// NOTE: after  you  obtained  coefficients,  you  can  evaluate  model  with
//       LogisticCalc4() function.
//
// NOTE: if you need better control over fitting process than provided by this
//       function, you may use LogisticFit45X().
//
// NOTE: step is automatically scaled according to scale of parameters  being
//       fitted before we compare its length with EpsX. Thus,  this  function
//       can be used to fit data with very small or very large values without
//       changing EpsX.
//
// EQUALITY CONSTRAINTS ON PARAMETERS
//
// 4PL/5PL solver supports equality constraints on model values at  the  left
// boundary (X=0) and right  boundary  (X=infinity).  These  constraints  are
// completely optional and you can specify both of them, only  one  -  or  no
// constraints at all.
//
// Parameter  CnstrLeft  contains  left  constraint (or NAN for unconstrained
// fitting), and CnstrRight contains right  one.  For  4PL,  left  constraint
// ALWAYS corresponds to parameter A, and right one is ALWAYS  constraint  on
// D. That's because 4PL model is normalized in such way that B >= 0.
//
//
// ALGLIB Project: Copyright 14.02.2014 by Sergey Bochkanov
void logisticfit4ec(const real_1d_array &x, const real_1d_array &y, const ae_int_t n, const double cnstrleft, const double cnstrright, double &a, double &b, double &c, double &d, lsfitreport &rep);

// This function fits five-parameter logistic (5PL) model  to  data  provided
// by user. 5PL model has following form:
//
//     F(x|A,B,C,D,G) = D+(A-D)/power(1+power(x/C,B),G)
//
// Here:
//     * A, D - unconstrained
//     * B - unconstrained
//     * C > 0
//     * G > 0
//
// IMPORTANT: unlike in  4PL  fitting,  output  of  this  function   is   NOT
//            constrained in  such  way that B is guaranteed to be  positive.
//            Furthermore,  unlike  4PL,  5PL  model  is  NOT  symmetric with
//            respect to B, so you can NOT transform model to equivalent one,
//            with B having desired sign (> 0 or < 0).
//
// 5PL fitting is implemented as follows:
// * we perform small number of restarts from random locations which helps to
//   solve problem of bad local extrema. Locations are only partially  random
//   - we use input data to determine good  initial  guess,  but  we  include
//   controlled amount of randomness.
// * we perform Levenberg-Marquardt fitting with very  tight  constraints  on
//   parameters B and C - it allows us to find good  initial  guess  for  the
//   second stage without risk of running into "flat spot".  Parameter  G  is
//   fixed at G=1.
// * second  Levenberg-Marquardt  round  is   performed   without   excessive
//   constraints on B and C, but with G still equal to 1.  Results  from  the
//   previous round are used as initial guess.
// * third Levenberg-Marquardt round relaxes constraints on G  and  tries  two
//   different models - one with B > 0 and one with B < 0.
// * after fitting is done, we compare results with best values found so far,
//   rewrite "best solution" if needed, and move to next random location.
//
// Overall algorithm is very stable and is not prone to  bad  local  extrema.
// Furthermore, it automatically scales when input data have  very  large  or
// very small range.
//
// Inputs:
//     X       -   array[N], stores X-values.
//                 MUST include only non-negative numbers  (but  may  include
//                 zero values). Can be unsorted.
//     Y       -   array[N], values to fit.
//     N       -   number of points. If N is less than  length  of  X/Y, only
//                 leading N elements are used.
//
// Outputs:
//     A,B,C,D,G-  parameters of 5PL model
//     Rep     -   fitting report. This structure has many fields,  but  ONLY
//                 ONES LISTED BELOW ARE SET:
//                 * Rep.IterationsCount - number of iterations performed
//                 * Rep.RMSError - root-mean-square error
//                 * Rep.AvgError - average absolute error
//                 * Rep.AvgRelError - average relative error (calculated for
//                   non-zero Y-values)
//                 * Rep.MaxError - maximum absolute error
//                 * Rep.R2 - coefficient of determination,  R-squared.  This
//                   coefficient   is  calculated  as  R2=1-RSS/TSS  (in case
//                   of nonlinear  regression  there  are  multiple  ways  to
//                   define R2, each of them giving different results).
//
// NOTE: for better stability B  parameter is restricted by [+-1/1000,+-1000]
//       range, and G is restricted by [1/10,10] range. It prevents algorithm
//       from making trial steps deep into the area of bad parameters.
//
// NOTE: after  you  obtained  coefficients,  you  can  evaluate  model  with
//       LogisticCalc5() function.
//
// NOTE: if you need better control over fitting process than provided by this
//       function, you may use LogisticFit45X().
//
// NOTE: step is automatically scaled according to scale of parameters  being
//       fitted before we compare its length with EpsX. Thus,  this  function
//       can be used to fit data with very small or very large values without
//       changing EpsX.
//
//
// ALGLIB Project: Copyright 14.02.2014 by Sergey Bochkanov
void logisticfit5(const real_1d_array &x, const real_1d_array &y, const ae_int_t n, double &a, double &b, double &c, double &d, double &g, lsfitreport &rep);

// This function fits five-parameter logistic (5PL) model  to  data  provided
// by user, subject to optional equality constraints on parameters A  and  D.
// 5PL model has following form:
//
//     F(x|A,B,C,D,G) = D+(A-D)/power(1+power(x/C,B),G)
//
// Here:
//     * A, D - with optional equality constraints
//     * B - unconstrained
//     * C > 0
//     * G > 0
//
// IMPORTANT: unlike in  4PL  fitting,  output  of  this  function   is   NOT
//            constrained in  such  way that B is guaranteed to be  positive.
//            Furthermore,  unlike  4PL,  5PL  model  is  NOT  symmetric with
//            respect to B, so you can NOT transform model to equivalent one,
//            with B having desired sign (> 0 or < 0).
//
// 5PL fitting is implemented as follows:
// * we perform small number of restarts from random locations which helps to
//   solve problem of bad local extrema. Locations are only partially  random
//   - we use input data to determine good  initial  guess,  but  we  include
//   controlled amount of randomness.
// * we perform Levenberg-Marquardt fitting with very  tight  constraints  on
//   parameters B and C - it allows us to find good  initial  guess  for  the
//   second stage without risk of running into "flat spot".  Parameter  G  is
//   fixed at G=1.
// * second  Levenberg-Marquardt  round  is   performed   without   excessive
//   constraints on B and C, but with G still equal to 1.  Results  from  the
//   previous round are used as initial guess.
// * third Levenberg-Marquardt round relaxes constraints on G  and  tries  two
//   different models - one with B > 0 and one with B < 0.
// * after fitting is done, we compare results with best values found so far,
//   rewrite "best solution" if needed, and move to next random location.
//
// Overall algorithm is very stable and is not prone to  bad  local  extrema.
// Furthermore, it automatically scales when input data have  very  large  or
// very small range.
//
// Inputs:
//     X       -   array[N], stores X-values.
//                 MUST include only non-negative numbers  (but  may  include
//                 zero values). Can be unsorted.
//     Y       -   array[N], values to fit.
//     N       -   number of points. If N is less than  length  of  X/Y, only
//                 leading N elements are used.
//     CnstrLeft-  optional equality constraint for model value at the   left
//                 boundary (at X=0). Specify NAN (Not-a-Number)  if  you  do
//                 not need constraint on the model value at X=0 (in C++  you
//                 can pass NAN as parameter, in  C#  it  will  be
//                 Double.NaN).
//                 See  below,  section  "EQUALITY  CONSTRAINTS"   for   more
//                 information about constraints.
//     CnstrRight- optional equality constraint for model value at X=infinity.
//                 Specify NAN (Not-a-Number) if you do not  need  constraint
//                 on the model value (in C++  you can pass NAN as
//                 parameter, in  C# it will  be Double.NaN).
//                 See  below,  section  "EQUALITY  CONSTRAINTS"   for   more
//                 information about constraints.
//
// Outputs:
//     A,B,C,D,G-  parameters of 5PL model
//     Rep     -   fitting report. This structure has many fields,  but  ONLY
//                 ONES LISTED BELOW ARE SET:
//                 * Rep.IterationsCount - number of iterations performed
//                 * Rep.RMSError - root-mean-square error
//                 * Rep.AvgError - average absolute error
//                 * Rep.AvgRelError - average relative error (calculated for
//                   non-zero Y-values)
//                 * Rep.MaxError - maximum absolute error
//                 * Rep.R2 - coefficient of determination,  R-squared.  This
//                   coefficient   is  calculated  as  R2=1-RSS/TSS  (in case
//                   of nonlinear  regression  there  are  multiple  ways  to
//                   define R2, each of them giving different results).
//
// NOTE: for better stability B  parameter is restricted by [+-1/1000,+-1000]
//       range, and G is restricted by [1/10,10] range. It prevents algorithm
//       from making trial steps deep into the area of bad parameters.
//
// NOTE: after  you  obtained  coefficients,  you  can  evaluate  model  with
//       LogisticCalc5() function.
//
// NOTE: if you need better control over fitting process than provided by this
//       function, you may use LogisticFit45X().
//
// NOTE: step is automatically scaled according to scale of parameters  being
//       fitted before we compare its length with EpsX. Thus,  this  function
//       can be used to fit data with very small or very large values without
//       changing EpsX.
//
// EQUALITY CONSTRAINTS ON PARAMETERS
//
// 5PL solver supports equality constraints on model  values  at   the   left
// boundary (X=0) and right  boundary  (X=infinity).  These  constraints  are
// completely optional and you can specify both of them, only  one  -  or  no
// constraints at all.
//
// Parameter  CnstrLeft  contains  left  constraint (or NAN for unconstrained
// fitting), and CnstrRight contains right  one.
//
// Unlike 4PL one, 5PL model is NOT symmetric with respect to  change in sign
// of B. Thus, negative B's are possible, and left constraint  may  constrain
// parameter A (for positive B's)  -  or  parameter  D  (for  negative  B's).
// Similarly changes meaning of right constraint.
//
// You do not have to decide what parameter to  constrain  -  algorithm  will
// automatically determine correct parameters as fitting progresses. However,
// question highlighted above is important when you interpret fitting results.
//
//
// ALGLIB Project: Copyright 14.02.2014 by Sergey Bochkanov
void logisticfit5ec(const real_1d_array &x, const real_1d_array &y, const ae_int_t n, const double cnstrleft, const double cnstrright, double &a, double &b, double &c, double &d, double &g, lsfitreport &rep);

// This is "expert" 4PL/5PL fitting function, which can be used if  you  need
// better control over fitting process than provided  by  LogisticFit4()  or
// LogisticFit5().
//
// This function fits model of the form
//
//     F(x|A,B,C,D)   = D+(A-D)/(1+power(x/C,B))           (4PL model)
//
// or
//
//     F(x|A,B,C,D,G) = D+(A-D)/power(1+power(x/C,B),G)    (5PL model)
//
// Here:
//     * A, D - unconstrained
//     * B >= 0 for 4PL, unconstrained for 5PL
//     * C > 0
//     * G > 0 (if present)
//
// Inputs:
//     X       -   array[N], stores X-values.
//                 MUST include only non-negative numbers  (but  may  include
//                 zero values). Can be unsorted.
//     Y       -   array[N], values to fit.
//     N       -   number of points. If N is less than  length  of  X/Y, only
//                 leading N elements are used.
//     CnstrLeft-  optional equality constraint for model value at the   left
//                 boundary (at X=0). Specify NAN (Not-a-Number)  if  you  do
//                 not need constraint on the model value at X=0 (in C++  you
//                 can pass NAN as parameter, in  C#  it  will  be
//                 Double.NaN).
//                 See  below,  section  "EQUALITY  CONSTRAINTS"   for   more
//                 information about constraints.
//     CnstrRight- optional equality constraint for model value at X=infinity.
//                 Specify NAN (Not-a-Number) if you do not  need  constraint
//                 on the model value (in C++  you can pass NAN as
//                 parameter, in  C# it will  be Double.NaN).
//                 See  below,  section  "EQUALITY  CONSTRAINTS"   for   more
//                 information about constraints.
//     Is4PL   -   whether 4PL or 5PL models are fitted
//     LambdaV -   regularization coefficient, LambdaV >= 0.
//                 Set it to zero unless you know what you are doing.
//     EpsX    -   stopping condition (step size), EpsX >= 0.
//                 Zero value means that small step is automatically chosen.
//                 See notes below for more information.
//     RsCnt   -   number of repeated restarts from  random  points.  4PL/5PL
//                 models are prone to problem of bad local extrema. Utilizing
//                 multiple random restarts allows  us  to  improve algorithm
//                 convergence.
//                 RsCnt >= 0.
//                 Zero value means that function automatically choose  small
//                 amount of restarts (recommended).
//
// Outputs:
//     A, B, C, D- parameters of 4PL model
//     G       -   parameter of 5PL model; for Is4PL=True, G=1 is returned.
//     Rep     -   fitting report. This structure has many fields,  but  ONLY
//                 ONES LISTED BELOW ARE SET:
//                 * Rep.IterationsCount - number of iterations performed
//                 * Rep.RMSError - root-mean-square error
//                 * Rep.AvgError - average absolute error
//                 * Rep.AvgRelError - average relative error (calculated for
//                   non-zero Y-values)
//                 * Rep.MaxError - maximum absolute error
//                 * Rep.R2 - coefficient of determination,  R-squared.  This
//                   coefficient   is  calculated  as  R2=1-RSS/TSS  (in case
//                   of nonlinear  regression  there  are  multiple  ways  to
//                   define R2, each of them giving different results).
//
// NOTE: for better stability B  parameter is restricted by [+-1/1000,+-1000]
//       range, and G is restricted by [1/10,10] range. It prevents algorithm
//       from making trial steps deep into the area of bad parameters.
//
// NOTE: after  you  obtained  coefficients,  you  can  evaluate  model  with
//       LogisticCalc5() function.
//
// NOTE: step is automatically scaled according to scale of parameters  being
//       fitted before we compare its length with EpsX. Thus,  this  function
//       can be used to fit data with very small or very large values without
//       changing EpsX.
//
// EQUALITY CONSTRAINTS ON PARAMETERS
//
// 4PL/5PL solver supports equality constraints on model values at  the  left
// boundary (X=0) and right  boundary  (X=infinity).  These  constraints  are
// completely optional and you can specify both of them, only  one  -  or  no
// constraints at all.
//
// Parameter  CnstrLeft  contains  left  constraint (or NAN for unconstrained
// fitting), and CnstrRight contains right  one.  For  4PL,  left  constraint
// ALWAYS corresponds to parameter A, and right one is ALWAYS  constraint  on
// D. That's because 4PL model is normalized in such way that B >= 0.
//
// For 5PL model things are different. Unlike  4PL  one,  5PL  model  is  NOT
// symmetric with respect to  change  in  sign  of  B. Thus, negative B's are
// possible, and left constraint may constrain parameter A (for positive B's)
// - or parameter D (for negative B's). Similarly changes  meaning  of  right
// constraint.
//
// You do not have to decide what parameter to  constrain  -  algorithm  will
// automatically determine correct parameters as fitting progresses. However,
// question highlighted above is important when you interpret fitting results.
//
//
// ALGLIB Project: Copyright 14.02.2014 by Sergey Bochkanov
void logisticfit45x(const real_1d_array &x, const real_1d_array &y, const ae_int_t n, const double cnstrleft, const double cnstrright, const bool is4pl, const double lambdav, const double epsx, const ae_int_t rscnt, double &a, double &b, double &c, double &d, double &g, lsfitreport &rep);

// Weghted rational least  squares  fitting  using  Floater-Hormann  rational
// functions  with  optimal  D  chosen  from  [0,9],  with  constraints   and
// individual weights.
//
// Equidistant  grid  with M node on [min(x),max(x)]  is  used to build basis
// functions. Different values of D are tried, optimal D (least WEIGHTED root
// mean square error) is chosen.  Task  is  linear,  so  linear least squares
// solver  is  used.  Complexity  of  this  computational  scheme is O(N*M^2)
// (mostly dominated by the least squares solver).
//
// SEE ALSO
// * BarycentricFitFloaterHormann(), "lightweight" fitting without invididual
//   weights and constraints.
//
// Inputs:
//     X   -   points, array[0..N-1].
//     Y   -   function values, array[0..N-1].
//     W   -   weights, array[0..N-1]
//             Each summand in square  sum  of  approximation deviations from
//             given  values  is  multiplied  by  the square of corresponding
//             weight. Fill it by 1's if you don't  want  to  solve  weighted
//             task.
//     N   -   number of points, N > 0.
//     XC  -   points where function values/derivatives are constrained,
//             array[0..K-1].
//     YC  -   values of constraints, array[0..K-1]
//     DC  -   array[0..K-1], types of constraints:
//             * DC[i]=0   means that S(XC[i])=YC[i]
//             * DC[i]=1   means that S'(XC[i])=YC[i]
//             SEE BELOW FOR IMPORTANT INFORMATION ON CONSTRAINTS
//     K   -   number of constraints, 0 <= K < M.
//             K=0 means no constraints (XC/YC/DC are not used in such cases)
//     M   -   number of basis functions ( = number_of_nodes), M >= 2.
//
// Outputs:
//     Info-   same format as in LSFitLinearWC() subroutine.
//             * Info > 0    task is solved
//             * Info <= 0   an error occured:
//                         -4 means inconvergence of internal SVD
//                         -3 means inconsistent constraints
//                         -1 means another errors in parameters passed
//                            (N <= 0, for example)
//     B   -   barycentric interpolant.
//     Rep -   report, same format as in LSFitLinearWC() subroutine.
//             Following fields are set:
//             * DBest         best value of the D parameter
//             * RMSError      rms error on the (X,Y).
//             * AvgError      average error on the (X,Y).
//             * AvgRelError   average relative error on the non-zero Y
//             * MaxError      maximum error
//                             NON-WEIGHTED ERRORS ARE CALCULATED
//
// IMPORTANT:
//     this subroutine doesn't calculate task's condition number for K != 0.
//
// SETTING CONSTRAINTS - DANGERS AND OPPORTUNITIES:
//
// Setting constraints can lead  to undesired  results,  like ill-conditioned
// behavior, or inconsistency being detected. From the other side,  it allows
// us to improve quality of the fit. Here we summarize  our  experience  with
// constrained barycentric interpolants:
// * excessive  constraints  can  be  inconsistent.   Floater-Hormann   basis
//   functions aren't as flexible as splines (although they are very smooth).
// * the more evenly constraints are spread across [min(x),max(x)],  the more
//   chances that they will be consistent
// * the  greater  is  M (given  fixed  constraints),  the  more chances that
//   constraints will be consistent
// * in the general case, consistency of constraints IS NOT GUARANTEED.
// * in the several special cases, however, we CAN guarantee consistency.
// * one of this cases is constraints on the function  VALUES at the interval
//   boundaries. Note that consustency of the  constraints  on  the  function
//   DERIVATIVES is NOT guaranteed (you can use in such cases  cubic  splines
//   which are more flexible).
// * another  special  case  is ONE constraint on the function value (OR, but
//   not AND, derivative) anywhere in the interval
//
// Our final recommendation is to use constraints  WHEN  AND  ONLY  WHEN  you
// can't solve your task without them. Anything beyond  special  cases  given
// above is not guaranteed and may result in inconsistency.
//
// ALGLIB Project: Copyright 18.08.2009 by Sergey Bochkanov
void barycentricfitfloaterhormannwc(const real_1d_array &x, const real_1d_array &y, const real_1d_array &w, const ae_int_t n, const real_1d_array &xc, const real_1d_array &yc, const integer_1d_array &dc, const ae_int_t k, const ae_int_t m, ae_int_t &info, barycentricinterpolant &b, barycentricfitreport &rep);

// Rational least squares fitting using  Floater-Hormann  rational  functions
// with optimal D chosen from [0,9].
//
// Equidistant  grid  with M node on [min(x),max(x)]  is  used to build basis
// functions. Different values of D are tried, optimal  D  (least  root  mean
// square error) is chosen.  Task  is  linear, so linear least squares solver
// is used. Complexity  of  this  computational  scheme is  O(N*M^2)  (mostly
// dominated by the least squares solver).
//
// Inputs:
//     X   -   points, array[0..N-1].
//     Y   -   function values, array[0..N-1].
//     N   -   number of points, N > 0.
//     M   -   number of basis functions ( = number_of_nodes), M >= 2.
//
// Outputs:
//     Info-   same format as in LSFitLinearWC() subroutine.
//             * Info > 0    task is solved
//             * Info <= 0   an error occured:
//                         -4 means inconvergence of internal SVD
//                         -3 means inconsistent constraints
//     B   -   barycentric interpolant.
//     Rep -   report, same format as in LSFitLinearWC() subroutine.
//             Following fields are set:
//             * DBest         best value of the D parameter
//             * RMSError      rms error on the (X,Y).
//             * AvgError      average error on the (X,Y).
//             * AvgRelError   average relative error on the non-zero Y
//             * MaxError      maximum error
//                             NON-WEIGHTED ERRORS ARE CALCULATED
//
// ALGLIB Project: Copyright 18.08.2009 by Sergey Bochkanov
void barycentricfitfloaterhormann(const real_1d_array &x, const real_1d_array &y, const ae_int_t n, const ae_int_t m, ae_int_t &info, barycentricinterpolant &b, barycentricfitreport &rep);

// Weighted fitting by cubic  spline,  with constraints on function values or
// derivatives.
//
// Equidistant grid with M-2 nodes on [min(x,xc),max(x,xc)] is  used to build
// basis functions. Basis functions are cubic splines with continuous  second
// derivatives  and  non-fixed first  derivatives  at  interval  ends.  Small
// regularizing term is used  when  solving  constrained  tasks  (to  improve
// stability).
//
// Task is linear, so linear least squares solver is used. Complexity of this
// computational scheme is O(N*M^2), mostly dominated by least squares solver
//
// SEE ALSO
//     Spline1DFitHermiteWC()  -   fitting by Hermite splines (more flexible,
//                                 less smooth)
//     Spline1DFitCubic()      -   "lightweight" fitting  by  cubic  splines,
//                                 without invididual weights and constraints
//
// Inputs:
//     X   -   points, array[0..N-1].
//     Y   -   function values, array[0..N-1].
//     W   -   weights, array[0..N-1]
//             Each summand in square  sum  of  approximation deviations from
//             given  values  is  multiplied  by  the square of corresponding
//             weight. Fill it by 1's if you don't  want  to  solve  weighted
//             task.
//     N   -   number of points (optional):
//             * N > 0
//             * if given, only first N elements of X/Y/W are processed
//             * if not given, automatically determined from X/Y/W sizes
//     XC  -   points where spline values/derivatives are constrained,
//             array[0..K-1].
//     YC  -   values of constraints, array[0..K-1]
//     DC  -   array[0..K-1], types of constraints:
//             * DC[i]=0   means that S(XC[i])=YC[i]
//             * DC[i]=1   means that S'(XC[i])=YC[i]
//             SEE BELOW FOR IMPORTANT INFORMATION ON CONSTRAINTS
//     K   -   number of constraints (optional):
//             * 0 <= K < M.
//             * K=0 means no constraints (XC/YC/DC are not used)
//             * if given, only first K elements of XC/YC/DC are used
//             * if not given, automatically determined from XC/YC/DC
//     M   -   number of basis functions ( = number_of_nodes+2), M >= 4.
//
// Outputs:
//     Info-   same format as in LSFitLinearWC() subroutine.
//             * Info > 0    task is solved
//             * Info <= 0   an error occured:
//                         -4 means inconvergence of internal SVD
//                         -3 means inconsistent constraints
//     S   -   spline interpolant.
//     Rep -   report, same format as in LSFitLinearWC() subroutine.
//             Following fields are set:
//             * RMSError      rms error on the (X,Y).
//             * AvgError      average error on the (X,Y).
//             * AvgRelError   average relative error on the non-zero Y
//             * MaxError      maximum error
//                             NON-WEIGHTED ERRORS ARE CALCULATED
//
// IMPORTANT:
//     this subroitine doesn't calculate task's condition number for K != 0.
//
//
// ORDER OF POINTS
//
// Subroutine automatically sorts points, so caller may pass unsorted array.
//
// SETTING CONSTRAINTS - DANGERS AND OPPORTUNITIES:
//
// Setting constraints can lead  to undesired  results,  like ill-conditioned
// behavior, or inconsistency being detected. From the other side,  it allows
// us to improve quality of the fit. Here we summarize  our  experience  with
// constrained regression splines:
// * excessive constraints can be inconsistent. Splines are  piecewise  cubic
//   functions, and it is easy to create an example, where  large  number  of
//   constraints  concentrated  in  small  area will result in inconsistency.
//   Just because spline is not flexible enough to satisfy all of  them.  And
//   same constraints spread across the  [min(x),max(x)]  will  be  perfectly
//   consistent.
// * the more evenly constraints are spread across [min(x),max(x)],  the more
//   chances that they will be consistent
// * the  greater  is  M (given  fixed  constraints),  the  more chances that
//   constraints will be consistent
// * in the general case, consistency of constraints IS NOT GUARANTEED.
// * in the several special cases, however, we CAN guarantee consistency.
// * one of this cases is constraints  on  the  function  values  AND/OR  its
//   derivatives at the interval boundaries.
// * another  special  case  is ONE constraint on the function value (OR, but
//   not AND, derivative) anywhere in the interval
//
// Our final recommendation is to use constraints  WHEN  AND  ONLY  WHEN  you
// can't solve your task without them. Anything beyond  special  cases  given
// above is not guaranteed and may result in inconsistency.
//
//
// ALGLIB Project: Copyright 18.08.2009 by Sergey Bochkanov
void spline1dfitcubicwc(const real_1d_array &x, const real_1d_array &y, const real_1d_array &w, const ae_int_t n, const real_1d_array &xc, const real_1d_array &yc, const integer_1d_array &dc, const ae_int_t k, const ae_int_t m, ae_int_t &info, spline1dinterpolant &s, spline1dfitreport &rep);
void spline1dfitcubicwc(const real_1d_array &x, const real_1d_array &y, const real_1d_array &w, const real_1d_array &xc, const real_1d_array &yc, const integer_1d_array &dc, const ae_int_t m, ae_int_t &info, spline1dinterpolant &s, spline1dfitreport &rep);

// Weighted  fitting  by Hermite spline,  with constraints on function values
// or first derivatives.
//
// Equidistant grid with M nodes on [min(x,xc),max(x,xc)] is  used  to  build
// basis functions. Basis functions are Hermite splines.  Small  regularizing
// term is used when solving constrained tasks (to improve stability).
//
// Task is linear, so linear least squares solver is used. Complexity of this
// computational scheme is O(N*M^2), mostly dominated by least squares solver
//
// SEE ALSO
//     Spline1DFitCubicWC()    -   fitting by Cubic splines (less flexible,
//                                 more smooth)
//     Spline1DFitHermite()    -   "lightweight" Hermite fitting, without
//                                 invididual weights and constraints
//
// Inputs:
//     X   -   points, array[0..N-1].
//     Y   -   function values, array[0..N-1].
//     W   -   weights, array[0..N-1]
//             Each summand in square  sum  of  approximation deviations from
//             given  values  is  multiplied  by  the square of corresponding
//             weight. Fill it by 1's if you don't  want  to  solve  weighted
//             task.
//     N   -   number of points (optional):
//             * N > 0
//             * if given, only first N elements of X/Y/W are processed
//             * if not given, automatically determined from X/Y/W sizes
//     XC  -   points where spline values/derivatives are constrained,
//             array[0..K-1].
//     YC  -   values of constraints, array[0..K-1]
//     DC  -   array[0..K-1], types of constraints:
//             * DC[i]=0   means that S(XC[i])=YC[i]
//             * DC[i]=1   means that S'(XC[i])=YC[i]
//             SEE BELOW FOR IMPORTANT INFORMATION ON CONSTRAINTS
//     K   -   number of constraints (optional):
//             * 0 <= K < M.
//             * K=0 means no constraints (XC/YC/DC are not used)
//             * if given, only first K elements of XC/YC/DC are used
//             * if not given, automatically determined from XC/YC/DC
//     M   -   number of basis functions (= 2 * number of nodes),
//             M >= 4,
//             M IS EVEN!
//
// Outputs:
//     Info-   same format as in LSFitLinearW() subroutine:
//             * Info > 0    task is solved
//             * Info <= 0   an error occured:
//                         -4 means inconvergence of internal SVD
//                         -3 means inconsistent constraints
//                         -2 means odd M was passed (which is not supported)
//                         -1 means another errors in parameters passed
//                            (N <= 0, for example)
//     S   -   spline interpolant.
//     Rep -   report, same format as in LSFitLinearW() subroutine.
//             Following fields are set:
//             * RMSError      rms error on the (X,Y).
//             * AvgError      average error on the (X,Y).
//             * AvgRelError   average relative error on the non-zero Y
//             * MaxError      maximum error
//                             NON-WEIGHTED ERRORS ARE CALCULATED
//
// IMPORTANT:
//     this subroitine doesn't calculate task's condition number for K != 0.
//
// IMPORTANT:
//     this subroitine supports only even M's
//
//
// ORDER OF POINTS
//
// Subroutine automatically sorts points, so caller may pass unsorted array.
//
// SETTING CONSTRAINTS - DANGERS AND OPPORTUNITIES:
//
// Setting constraints can lead  to undesired  results,  like ill-conditioned
// behavior, or inconsistency being detected. From the other side,  it allows
// us to improve quality of the fit. Here we summarize  our  experience  with
// constrained regression splines:
// * excessive constraints can be inconsistent. Splines are  piecewise  cubic
//   functions, and it is easy to create an example, where  large  number  of
//   constraints  concentrated  in  small  area will result in inconsistency.
//   Just because spline is not flexible enough to satisfy all of  them.  And
//   same constraints spread across the  [min(x),max(x)]  will  be  perfectly
//   consistent.
// * the more evenly constraints are spread across [min(x),max(x)],  the more
//   chances that they will be consistent
// * the  greater  is  M (given  fixed  constraints),  the  more chances that
//   constraints will be consistent
// * in the general case, consistency of constraints is NOT GUARANTEED.
// * in the several special cases, however, we can guarantee consistency.
// * one of this cases is  M >= 4  and   constraints  on   the  function  value
//   (AND/OR its derivative) at the interval boundaries.
// * another special case is M >= 4  and  ONE  constraint on the function value
//   (OR, BUT NOT AND, derivative) anywhere in [min(x),max(x)]
//
// Our final recommendation is to use constraints  WHEN  AND  ONLY  when  you
// can't solve your task without them. Anything beyond  special  cases  given
// above is not guaranteed and may result in inconsistency.
//
// ALGLIB Project: Copyright 18.08.2009 by Sergey Bochkanov
void spline1dfithermitewc(const real_1d_array &x, const real_1d_array &y, const real_1d_array &w, const ae_int_t n, const real_1d_array &xc, const real_1d_array &yc, const integer_1d_array &dc, const ae_int_t k, const ae_int_t m, ae_int_t &info, spline1dinterpolant &s, spline1dfitreport &rep);
void spline1dfithermitewc(const real_1d_array &x, const real_1d_array &y, const real_1d_array &w, const real_1d_array &xc, const real_1d_array &yc, const integer_1d_array &dc, const ae_int_t m, ae_int_t &info, spline1dinterpolant &s, spline1dfitreport &rep);

// Least squares fitting by cubic spline.
//
// This subroutine is "lightweight" alternative for more complex and feature-
// rich Spline1DFitCubicWC().  See  Spline1DFitCubicWC() for more information
// about subroutine parameters (we don't duplicate it here because of length)
//
// ALGLIB Project: Copyright 18.08.2009 by Sergey Bochkanov
void spline1dfitcubic(const real_1d_array &x, const real_1d_array &y, const ae_int_t n, const ae_int_t m, ae_int_t &info, spline1dinterpolant &s, spline1dfitreport &rep);
void spline1dfitcubic(const real_1d_array &x, const real_1d_array &y, const ae_int_t m, ae_int_t &info, spline1dinterpolant &s, spline1dfitreport &rep);

// Least squares fitting by Hermite spline.
//
// This subroutine is "lightweight" alternative for more complex and feature-
// rich Spline1DFitHermiteWC().  See Spline1DFitHermiteWC()  description  for
// more information about subroutine parameters (we don't duplicate  it  here
// because of length).
//
// ALGLIB Project: Copyright 18.08.2009 by Sergey Bochkanov
void spline1dfithermite(const real_1d_array &x, const real_1d_array &y, const ae_int_t n, const ae_int_t m, ae_int_t &info, spline1dinterpolant &s, spline1dfitreport &rep);
void spline1dfithermite(const real_1d_array &x, const real_1d_array &y, const ae_int_t m, ae_int_t &info, spline1dinterpolant &s, spline1dfitreport &rep);

// Weighted linear least squares fitting.
//
// QR decomposition is used to reduce task to MxM, then triangular solver  or
// SVD-based solver is used depending on condition number of the  system.  It
// allows to maximize speed and retain decent accuracy.
//
// IMPORTANT: if you want to perform  polynomial  fitting,  it  may  be  more
//            convenient to use PolynomialFit() function. This function gives
//            best  results  on  polynomial  problems  and  solves  numerical
//            stability  issues  which  arise  when   you   fit   high-degree
//            polynomials to your data.
//
// Inputs:
//     Y       -   array[0..N-1] Function values in  N  points.
//     W       -   array[0..N-1]  Weights  corresponding to function  values.
//                 Each summand in square  sum  of  approximation  deviations
//                 from  given  values  is  multiplied  by  the   square   of
//                 corresponding weight.
//     FMatrix -   a table of basis functions values, array[0..N-1, 0..M-1].
//                 FMatrix[I, J] - value of J-th basis function in I-th point.
//     N       -   number of points used. N >= 1.
//     M       -   number of basis functions, M >= 1.
//
// Outputs:
//     Info    -   error code:
//                 * -4    internal SVD decomposition subroutine failed (very
//                         rare and for degenerate systems only)
//                 * -1    incorrect N/M were specified
//                 *  1    task is solved
//     C       -   decomposition coefficients, array[0..M-1]
//     Rep     -   fitting report. Following fields are set:
//                 * Rep.TaskRCond     reciprocal of condition number
//                 * R2                non-adjusted coefficient of determination
//                                     (non-weighted)
//                 * RMSError          rms error on the (X,Y).
//                 * AvgError          average error on the (X,Y).
//                 * AvgRelError       average relative error on the non-zero Y
//                 * MaxError          maximum error
//                                     NON-WEIGHTED ERRORS ARE CALCULATED
//
// ERRORS IN PARAMETERS
//
// This  solver  also  calculates different kinds of errors in parameters and
// fills corresponding fields of report:
// * Rep.CovPar        covariance matrix for parameters, array[K,K].
// * Rep.ErrPar        errors in parameters, array[K],
//                     errpar = sqrt(diag(CovPar))
// * Rep.ErrCurve      vector of fit errors - standard deviations of empirical
//                     best-fit curve from "ideal" best-fit curve built  with
//                     infinite number of samples, array[N].
//                     errcurve = sqrt(diag(F*CovPar*F')),
//                     where F is functions matrix.
// * Rep.Noise         vector of per-point estimates of noise, array[N]
//
// NOTE:       noise in the data is estimated as follows:
//             * for fitting without user-supplied  weights  all  points  are
//               assumed to have same level of noise, which is estimated from
//               the data
//             * for fitting with user-supplied weights we assume that  noise
//               level in I-th point is inversely proportional to Ith weight.
//               Coefficient of proportionality is estimated from the data.
//
// NOTE:       we apply small amount of regularization when we invert squared
//             Jacobian and calculate covariance matrix. It  guarantees  that
//             algorithm won't divide by zero  during  inversion,  but  skews
//             error estimates a bit (fractional error is about 10^-9).
//
//             However, we believe that this difference is insignificant  for
//             all practical purposes except for the situation when you  want
//             to compare ALGLIB results with "reference"  implementation  up
//             to the last significant digit.
//
// NOTE:       covariance matrix is estimated using  correction  for  degrees
//             of freedom (covariances are divided by N-M instead of dividing
//             by N).
// ALGLIB: Copyright 17.08.2009 by Sergey Bochkanov
void lsfitlinearw(const real_1d_array &y, const real_1d_array &w, const real_2d_array &fmatrix, const ae_int_t n, const ae_int_t m, ae_int_t &info, real_1d_array &c, lsfitreport &rep);
void lsfitlinearw(const real_1d_array &y, const real_1d_array &w, const real_2d_array &fmatrix, ae_int_t &info, real_1d_array &c, lsfitreport &rep);

// Weighted constained linear least squares fitting.
//
// This  is  variation  of LSFitLinearW(), which searchs for min|A*x=b| given
// that  K  additional  constaints  C*x=bc are satisfied. It reduces original
// task to modified one: min|B*y-d| WITHOUT constraints,  then LSFitLinearW()
// is called.
//
// IMPORTANT: if you want to perform  polynomial  fitting,  it  may  be  more
//            convenient to use PolynomialFit() function. This function gives
//            best  results  on  polynomial  problems  and  solves  numerical
//            stability  issues  which  arise  when   you   fit   high-degree
//            polynomials to your data.
//
// Inputs:
//     Y       -   array[0..N-1] Function values in  N  points.
//     W       -   array[0..N-1]  Weights  corresponding to function  values.
//                 Each summand in square  sum  of  approximation  deviations
//                 from  given  values  is  multiplied  by  the   square   of
//                 corresponding weight.
//     FMatrix -   a table of basis functions values, array[0..N-1, 0..M-1].
//                 FMatrix[I,J] - value of J-th basis function in I-th point.
//     CMatrix -   a table of constaints, array[0..K-1,0..M].
//                 I-th row of CMatrix corresponds to I-th linear constraint:
//                 CMatrix[I,0]*C[0] + ... + CMatrix[I,M-1]*C[M-1] = CMatrix[I,M]
//     N       -   number of points used. N >= 1.
//     M       -   number of basis functions, M >= 1.
//     K       -   number of constraints, 0 <= K < M
//                 K=0 corresponds to absence of constraints.
//
// Outputs:
//     Info    -   error code:
//                 * -4    internal SVD decomposition subroutine failed (very
//                         rare and for degenerate systems only)
//                 * -3    either   too   many  constraints  (M   or   more),
//                         degenerate  constraints   (some   constraints  are
//                         repetead twice) or inconsistent  constraints  were
//                         specified.
//                 *  1    task is solved
//     C       -   decomposition coefficients, array[0..M-1]
//     Rep     -   fitting report. Following fields are set:
//                 * R2                non-adjusted coefficient of determination
//                                     (non-weighted)
//                 * RMSError          rms error on the (X,Y).
//                 * AvgError          average error on the (X,Y).
//                 * AvgRelError       average relative error on the non-zero Y
//                 * MaxError          maximum error
//                                     NON-WEIGHTED ERRORS ARE CALCULATED
//
// IMPORTANT:
//     this subroitine doesn't calculate task's condition number for K != 0.
//
// ERRORS IN PARAMETERS
//
// This  solver  also  calculates different kinds of errors in parameters and
// fills corresponding fields of report:
// * Rep.CovPar        covariance matrix for parameters, array[K,K].
// * Rep.ErrPar        errors in parameters, array[K],
//                     errpar = sqrt(diag(CovPar))
// * Rep.ErrCurve      vector of fit errors - standard deviations of empirical
//                     best-fit curve from "ideal" best-fit curve built  with
//                     infinite number of samples, array[N].
//                     errcurve = sqrt(diag(F*CovPar*F')),
//                     where F is functions matrix.
// * Rep.Noise         vector of per-point estimates of noise, array[N]
//
// IMPORTANT:  errors  in  parameters  are  calculated  without  taking  into
//             account boundary/linear constraints! Presence  of  constraints
//             changes distribution of errors, but there is no  easy  way  to
//             account for constraints when you calculate covariance matrix.
//
// NOTE:       noise in the data is estimated as follows:
//             * for fitting without user-supplied  weights  all  points  are
//               assumed to have same level of noise, which is estimated from
//               the data
//             * for fitting with user-supplied weights we assume that  noise
//               level in I-th point is inversely proportional to Ith weight.
//               Coefficient of proportionality is estimated from the data.
//
// NOTE:       we apply small amount of regularization when we invert squared
//             Jacobian and calculate covariance matrix. It  guarantees  that
//             algorithm won't divide by zero  during  inversion,  but  skews
//             error estimates a bit (fractional error is about 10^-9).
//
//             However, we believe that this difference is insignificant  for
//             all practical purposes except for the situation when you  want
//             to compare ALGLIB results with "reference"  implementation  up
//             to the last significant digit.
//
// NOTE:       covariance matrix is estimated using  correction  for  degrees
//             of freedom (covariances are divided by N-M instead of dividing
//             by N).
// ALGLIB: Copyright 07.09.2009 by Sergey Bochkanov
void lsfitlinearwc(const real_1d_array &y, const real_1d_array &w, const real_2d_array &fmatrix, const real_2d_array &cmatrix, const ae_int_t n, const ae_int_t m, const ae_int_t k, ae_int_t &info, real_1d_array &c, lsfitreport &rep);
void lsfitlinearwc(const real_1d_array &y, const real_1d_array &w, const real_2d_array &fmatrix, const real_2d_array &cmatrix, ae_int_t &info, real_1d_array &c, lsfitreport &rep);

// Linear least squares fitting.
//
// QR decomposition is used to reduce task to MxM, then triangular solver  or
// SVD-based solver is used depending on condition number of the  system.  It
// allows to maximize speed and retain decent accuracy.
//
// IMPORTANT: if you want to perform  polynomial  fitting,  it  may  be  more
//            convenient to use PolynomialFit() function. This function gives
//            best  results  on  polynomial  problems  and  solves  numerical
//            stability  issues  which  arise  when   you   fit   high-degree
//            polynomials to your data.
//
// Inputs:
//     Y       -   array[0..N-1] Function values in  N  points.
//     FMatrix -   a table of basis functions values, array[0..N-1, 0..M-1].
//                 FMatrix[I, J] - value of J-th basis function in I-th point.
//     N       -   number of points used. N >= 1.
//     M       -   number of basis functions, M >= 1.
//
// Outputs:
//     Info    -   error code:
//                 * -4    internal SVD decomposition subroutine failed (very
//                         rare and for degenerate systems only)
//                 *  1    task is solved
//     C       -   decomposition coefficients, array[0..M-1]
//     Rep     -   fitting report. Following fields are set:
//                 * Rep.TaskRCond     reciprocal of condition number
//                 * R2                non-adjusted coefficient of determination
//                                     (non-weighted)
//                 * RMSError          rms error on the (X,Y).
//                 * AvgError          average error on the (X,Y).
//                 * AvgRelError       average relative error on the non-zero Y
//                 * MaxError          maximum error
//                                     NON-WEIGHTED ERRORS ARE CALCULATED
//
// ERRORS IN PARAMETERS
//
// This  solver  also  calculates different kinds of errors in parameters and
// fills corresponding fields of report:
// * Rep.CovPar        covariance matrix for parameters, array[K,K].
// * Rep.ErrPar        errors in parameters, array[K],
//                     errpar = sqrt(diag(CovPar))
// * Rep.ErrCurve      vector of fit errors - standard deviations of empirical
//                     best-fit curve from "ideal" best-fit curve built  with
//                     infinite number of samples, array[N].
//                     errcurve = sqrt(diag(F*CovPar*F')),
//                     where F is functions matrix.
// * Rep.Noise         vector of per-point estimates of noise, array[N]
//
// NOTE:       noise in the data is estimated as follows:
//             * for fitting without user-supplied  weights  all  points  are
//               assumed to have same level of noise, which is estimated from
//               the data
//             * for fitting with user-supplied weights we assume that  noise
//               level in I-th point is inversely proportional to Ith weight.
//               Coefficient of proportionality is estimated from the data.
//
// NOTE:       we apply small amount of regularization when we invert squared
//             Jacobian and calculate covariance matrix. It  guarantees  that
//             algorithm won't divide by zero  during  inversion,  but  skews
//             error estimates a bit (fractional error is about 10^-9).
//
//             However, we believe that this difference is insignificant  for
//             all practical purposes except for the situation when you  want
//             to compare ALGLIB results with "reference"  implementation  up
//             to the last significant digit.
//
// NOTE:       covariance matrix is estimated using  correction  for  degrees
//             of freedom (covariances are divided by N-M instead of dividing
//             by N).
// ALGLIB: Copyright 17.08.2009 by Sergey Bochkanov
void lsfitlinear(const real_1d_array &y, const real_2d_array &fmatrix, const ae_int_t n, const ae_int_t m, ae_int_t &info, real_1d_array &c, lsfitreport &rep);
void lsfitlinear(const real_1d_array &y, const real_2d_array &fmatrix, ae_int_t &info, real_1d_array &c, lsfitreport &rep);

// Constained linear least squares fitting.
//
// This  is  variation  of LSFitLinear(),  which searchs for min|A*x=b| given
// that  K  additional  constaints  C*x=bc are satisfied. It reduces original
// task to modified one: min|B*y-d| WITHOUT constraints,  then  LSFitLinear()
// is called.
//
// IMPORTANT: if you want to perform  polynomial  fitting,  it  may  be  more
//            convenient to use PolynomialFit() function. This function gives
//            best  results  on  polynomial  problems  and  solves  numerical
//            stability  issues  which  arise  when   you   fit   high-degree
//            polynomials to your data.
//
// Inputs:
//     Y       -   array[0..N-1] Function values in  N  points.
//     FMatrix -   a table of basis functions values, array[0..N-1, 0..M-1].
//                 FMatrix[I,J] - value of J-th basis function in I-th point.
//     CMatrix -   a table of constaints, array[0..K-1,0..M].
//                 I-th row of CMatrix corresponds to I-th linear constraint:
//                 CMatrix[I,0]*C[0] + ... + CMatrix[I,M-1]*C[M-1] = CMatrix[I,M]
//     N       -   number of points used. N >= 1.
//     M       -   number of basis functions, M >= 1.
//     K       -   number of constraints, 0 <= K < M
//                 K=0 corresponds to absence of constraints.
//
// Outputs:
//     Info    -   error code:
//                 * -4    internal SVD decomposition subroutine failed (very
//                         rare and for degenerate systems only)
//                 * -3    either   too   many  constraints  (M   or   more),
//                         degenerate  constraints   (some   constraints  are
//                         repetead twice) or inconsistent  constraints  were
//                         specified.
//                 *  1    task is solved
//     C       -   decomposition coefficients, array[0..M-1]
//     Rep     -   fitting report. Following fields are set:
//                 * R2                non-adjusted coefficient of determination
//                                     (non-weighted)
//                 * RMSError          rms error on the (X,Y).
//                 * AvgError          average error on the (X,Y).
//                 * AvgRelError       average relative error on the non-zero Y
//                 * MaxError          maximum error
//                                     NON-WEIGHTED ERRORS ARE CALCULATED
//
// IMPORTANT:
//     this subroitine doesn't calculate task's condition number for K != 0.
//
// ERRORS IN PARAMETERS
//
// This  solver  also  calculates different kinds of errors in parameters and
// fills corresponding fields of report:
// * Rep.CovPar        covariance matrix for parameters, array[K,K].
// * Rep.ErrPar        errors in parameters, array[K],
//                     errpar = sqrt(diag(CovPar))
// * Rep.ErrCurve      vector of fit errors - standard deviations of empirical
//                     best-fit curve from "ideal" best-fit curve built  with
//                     infinite number of samples, array[N].
//                     errcurve = sqrt(diag(F*CovPar*F')),
//                     where F is functions matrix.
// * Rep.Noise         vector of per-point estimates of noise, array[N]
//
// IMPORTANT:  errors  in  parameters  are  calculated  without  taking  into
//             account boundary/linear constraints! Presence  of  constraints
//             changes distribution of errors, but there is no  easy  way  to
//             account for constraints when you calculate covariance matrix.
//
// NOTE:       noise in the data is estimated as follows:
//             * for fitting without user-supplied  weights  all  points  are
//               assumed to have same level of noise, which is estimated from
//               the data
//             * for fitting with user-supplied weights we assume that  noise
//               level in I-th point is inversely proportional to Ith weight.
//               Coefficient of proportionality is estimated from the data.
//
// NOTE:       we apply small amount of regularization when we invert squared
//             Jacobian and calculate covariance matrix. It  guarantees  that
//             algorithm won't divide by zero  during  inversion,  but  skews
//             error estimates a bit (fractional error is about 10^-9).
//
//             However, we believe that this difference is insignificant  for
//             all practical purposes except for the situation when you  want
//             to compare ALGLIB results with "reference"  implementation  up
//             to the last significant digit.
//
// NOTE:       covariance matrix is estimated using  correction  for  degrees
//             of freedom (covariances are divided by N-M instead of dividing
//             by N).
// ALGLIB: Copyright 07.09.2009 by Sergey Bochkanov
void lsfitlinearc(const real_1d_array &y, const real_2d_array &fmatrix, const real_2d_array &cmatrix, const ae_int_t n, const ae_int_t m, const ae_int_t k, ae_int_t &info, real_1d_array &c, lsfitreport &rep);
void lsfitlinearc(const real_1d_array &y, const real_2d_array &fmatrix, const real_2d_array &cmatrix, ae_int_t &info, real_1d_array &c, lsfitreport &rep);

// Weighted nonlinear least squares fitting using function values only.
//
// Combination of numerical differentiation and secant updates is used to
// obtain function Jacobian.
//
// Nonlinear task min(F(c)) is solved, where
//
//     F(c) = (w[0]*(f(c,x[0])-y[0]))^2 + ... + (w[n-1]*(f(c,x[n-1])-y[n-1]))^2,
//
//     * N is a number of points,
//     * M is a dimension of a space points belong to,
//     * K is a dimension of a space of parameters being fitted,
//     * w is an N-dimensional vector of weight coefficients,
//     * x is a set of N points, each of them is an M-dimensional vector,
//     * c is a K-dimensional vector of parameters being fitted
//
// This subroutine uses only f(c,x[i]).
//
// Inputs:
//     X       -   array[0..N-1,0..M-1], points (one row = one point)
//     Y       -   array[0..N-1], function values.
//     W       -   weights, array[0..N-1]
//     C       -   array[0..K-1], initial approximation to the solution,
//     N       -   number of points, N > 1
//     M       -   dimension of space
//     K       -   number of parameters being fitted
//     DiffStep-   numerical differentiation step;
//                 should not be very small or large;
//                 large = loss of accuracy
//                 small = growth of round-off errors
//
// Outputs:
//     State   -   structure which stores algorithm state
// ALGLIB: Copyright 18.10.2008 by Sergey Bochkanov
void lsfitcreatewf(const real_2d_array &x, const real_1d_array &y, const real_1d_array &w, const real_1d_array &c, const ae_int_t n, const ae_int_t m, const ae_int_t k, const double diffstep, lsfitstate &state);
void lsfitcreatewf(const real_2d_array &x, const real_1d_array &y, const real_1d_array &w, const real_1d_array &c, const double diffstep, lsfitstate &state);

// Nonlinear least squares fitting using function values only.
//
// Combination of numerical differentiation and secant updates is used to
// obtain function Jacobian.
//
// Nonlinear task min(F(c)) is solved, where
//
//     F(c) = (f(c,x[0])-y[0])^2 + ... + (f(c,x[n-1])-y[n-1])^2,
//
//     * N is a number of points,
//     * M is a dimension of a space points belong to,
//     * K is a dimension of a space of parameters being fitted,
//     * w is an N-dimensional vector of weight coefficients,
//     * x is a set of N points, each of them is an M-dimensional vector,
//     * c is a K-dimensional vector of parameters being fitted
//
// This subroutine uses only f(c,x[i]).
//
// Inputs:
//     X       -   array[0..N-1,0..M-1], points (one row = one point)
//     Y       -   array[0..N-1], function values.
//     C       -   array[0..K-1], initial approximation to the solution,
//     N       -   number of points, N > 1
//     M       -   dimension of space
//     K       -   number of parameters being fitted
//     DiffStep-   numerical differentiation step;
//                 should not be very small or large;
//                 large = loss of accuracy
//                 small = growth of round-off errors
//
// Outputs:
//     State   -   structure which stores algorithm state
// ALGLIB: Copyright 18.10.2008 by Sergey Bochkanov
void lsfitcreatef(const real_2d_array &x, const real_1d_array &y, const real_1d_array &c, const ae_int_t n, const ae_int_t m, const ae_int_t k, const double diffstep, lsfitstate &state);
void lsfitcreatef(const real_2d_array &x, const real_1d_array &y, const real_1d_array &c, const double diffstep, lsfitstate &state);

// Weighted nonlinear least squares fitting using gradient only.
//
// Nonlinear task min(F(c)) is solved, where
//
//     F(c) = (w[0]*(f(c,x[0])-y[0]))^2 + ... + (w[n-1]*(f(c,x[n-1])-y[n-1]))^2,
//
//     * N is a number of points,
//     * M is a dimension of a space points belong to,
//     * K is a dimension of a space of parameters being fitted,
//     * w is an N-dimensional vector of weight coefficients,
//     * x is a set of N points, each of them is an M-dimensional vector,
//     * c is a K-dimensional vector of parameters being fitted
//
// This subroutine uses only f(c,x[i]) and its gradient.
//
// Inputs:
//     X       -   array[0..N-1,0..M-1], points (one row = one point)
//     Y       -   array[0..N-1], function values.
//     W       -   weights, array[0..N-1]
//     C       -   array[0..K-1], initial approximation to the solution,
//     N       -   number of points, N > 1
//     M       -   dimension of space
//     K       -   number of parameters being fitted
//     CheapFG -   boolean flag, which is:
//                 * True  if both function and gradient calculation complexity
//                         are less than O(M^2).  An improved  algorithm  can
//                         be  used  which corresponds  to  FGJ  scheme  from
//                         MINLM unit.
//                 * False otherwise.
//                         Standard Jacibian-bases  Levenberg-Marquardt  algo
//                         will be used (FJ scheme).
//
// Outputs:
//     State   -   structure which stores algorithm state
//
// See also:
//     LSFitResults
//     LSFitCreateFG (fitting without weights)
//     LSFitCreateWFGH (fitting using Hessian)
//     LSFitCreateFGH (fitting using Hessian, without weights)
// ALGLIB: Copyright 17.08.2009 by Sergey Bochkanov
void lsfitcreatewfg(const real_2d_array &x, const real_1d_array &y, const real_1d_array &w, const real_1d_array &c, const ae_int_t n, const ae_int_t m, const ae_int_t k, const bool cheapfg, lsfitstate &state);
void lsfitcreatewfg(const real_2d_array &x, const real_1d_array &y, const real_1d_array &w, const real_1d_array &c, const bool cheapfg, lsfitstate &state);

// Nonlinear least squares fitting using gradient only, without individual
// weights.
//
// Nonlinear task min(F(c)) is solved, where
//
//     F(c) = ((f(c,x[0])-y[0]))^2 + ... + ((f(c,x[n-1])-y[n-1]))^2,
//
//     * N is a number of points,
//     * M is a dimension of a space points belong to,
//     * K is a dimension of a space of parameters being fitted,
//     * x is a set of N points, each of them is an M-dimensional vector,
//     * c is a K-dimensional vector of parameters being fitted
//
// This subroutine uses only f(c,x[i]) and its gradient.
//
// Inputs:
//     X       -   array[0..N-1,0..M-1], points (one row = one point)
//     Y       -   array[0..N-1], function values.
//     C       -   array[0..K-1], initial approximation to the solution,
//     N       -   number of points, N > 1
//     M       -   dimension of space
//     K       -   number of parameters being fitted
//     CheapFG -   boolean flag, which is:
//                 * True  if both function and gradient calculation complexity
//                         are less than O(M^2).  An improved  algorithm  can
//                         be  used  which corresponds  to  FGJ  scheme  from
//                         MINLM unit.
//                 * False otherwise.
//                         Standard Jacibian-bases  Levenberg-Marquardt  algo
//                         will be used (FJ scheme).
//
// Outputs:
//     State   -   structure which stores algorithm state
// ALGLIB: Copyright 17.08.2009 by Sergey Bochkanov
void lsfitcreatefg(const real_2d_array &x, const real_1d_array &y, const real_1d_array &c, const ae_int_t n, const ae_int_t m, const ae_int_t k, const bool cheapfg, lsfitstate &state);
void lsfitcreatefg(const real_2d_array &x, const real_1d_array &y, const real_1d_array &c, const bool cheapfg, lsfitstate &state);

// Weighted nonlinear least squares fitting using gradient/Hessian.
//
// Nonlinear task min(F(c)) is solved, where
//
//     F(c) = (w[0]*(f(c,x[0])-y[0]))^2 + ... + (w[n-1]*(f(c,x[n-1])-y[n-1]))^2,
//
//     * N is a number of points,
//     * M is a dimension of a space points belong to,
//     * K is a dimension of a space of parameters being fitted,
//     * w is an N-dimensional vector of weight coefficients,
//     * x is a set of N points, each of them is an M-dimensional vector,
//     * c is a K-dimensional vector of parameters being fitted
//
// This subroutine uses f(c,x[i]), its gradient and its Hessian.
//
// Inputs:
//     X       -   array[0..N-1,0..M-1], points (one row = one point)
//     Y       -   array[0..N-1], function values.
//     W       -   weights, array[0..N-1]
//     C       -   array[0..K-1], initial approximation to the solution,
//     N       -   number of points, N > 1
//     M       -   dimension of space
//     K       -   number of parameters being fitted
//
// Outputs:
//     State   -   structure which stores algorithm state
// ALGLIB: Copyright 17.08.2009 by Sergey Bochkanov
void lsfitcreatewfgh(const real_2d_array &x, const real_1d_array &y, const real_1d_array &w, const real_1d_array &c, const ae_int_t n, const ae_int_t m, const ae_int_t k, lsfitstate &state);
void lsfitcreatewfgh(const real_2d_array &x, const real_1d_array &y, const real_1d_array &w, const real_1d_array &c, lsfitstate &state);

// Nonlinear least squares fitting using gradient/Hessian, without individial
// weights.
//
// Nonlinear task min(F(c)) is solved, where
//
//     F(c) = ((f(c,x[0])-y[0]))^2 + ... + ((f(c,x[n-1])-y[n-1]))^2,
//
//     * N is a number of points,
//     * M is a dimension of a space points belong to,
//     * K is a dimension of a space of parameters being fitted,
//     * x is a set of N points, each of them is an M-dimensional vector,
//     * c is a K-dimensional vector of parameters being fitted
//
// This subroutine uses f(c,x[i]), its gradient and its Hessian.
//
// Inputs:
//     X       -   array[0..N-1,0..M-1], points (one row = one point)
//     Y       -   array[0..N-1], function values.
//     C       -   array[0..K-1], initial approximation to the solution,
//     N       -   number of points, N > 1
//     M       -   dimension of space
//     K       -   number of parameters being fitted
//
// Outputs:
//     State   -   structure which stores algorithm state
//
// ALGLIB: Copyright 17.08.2009 by Sergey Bochkanov
void lsfitcreatefgh(const real_2d_array &x, const real_1d_array &y, const real_1d_array &c, const ae_int_t n, const ae_int_t m, const ae_int_t k, lsfitstate &state);
void lsfitcreatefgh(const real_2d_array &x, const real_1d_array &y, const real_1d_array &c, lsfitstate &state);

// Stopping conditions for nonlinear least squares fitting.
//
// Inputs:
//     State   -   structure which stores algorithm state
//     EpsX    - >= 0
//                 The subroutine finishes its work if  on  k+1-th  iteration
//                 the condition |v| <= EpsX is fulfilled, where:
//                 * |.| means Euclidian norm
//                 * v - scaled step vector, v[i]=dx[i]/s[i]
//                 * dx - ste pvector, dx=X(k+1)-X(k)
//                 * s - scaling coefficients set by LSFitSetScale()
//     MaxIts  -   maximum number of iterations. If MaxIts=0, the  number  of
//                 iterations   is    unlimited.   Only   Levenberg-Marquardt
//                 iterations  are  counted  (L-BFGS/CG  iterations  are  NOT
//                 counted because their cost is very low compared to that of
//                 LM).
//
// NOTE
//
// Passing EpsX=0  and  MaxIts=0  (simultaneously)  will  lead  to  automatic
// stopping criterion selection (according to the scheme used by MINLM unit).
//
// ALGLIB: Copyright 17.08.2009 by Sergey Bochkanov
void lsfitsetcond(const lsfitstate &state, const double epsx, const ae_int_t maxits);

// This function sets maximum step length
//
// Inputs:
//     State   -   structure which stores algorithm state
//     StpMax  -   maximum step length, >= 0. Set StpMax to 0.0,  if you don't
//                 want to limit step length.
//
// Use this subroutine when you optimize target function which contains exp()
// or  other  fast  growing  functions,  and optimization algorithm makes too
// large  steps  which  leads  to overflow. This function allows us to reject
// steps  that  are  too  large  (and  therefore  expose  us  to the possible
// overflow) without actually calculating function value at the x+stp*d.
//
// NOTE: non-zero StpMax leads to moderate  performance  degradation  because
// intermediate  step  of  preconditioned L-BFGS optimization is incompatible
// with limits on step size.
// ALGLIB: Copyright 02.04.2010 by Sergey Bochkanov
void lsfitsetstpmax(const lsfitstate &state, const double stpmax);

// This function turns on/off reporting.
//
// Inputs:
//     State   -   structure which stores algorithm state
//     NeedXRep-   whether iteration reports are needed or not
//
// When reports are needed, State.C (current parameters) and State.F (current
// value of fitting function) are reported.
//
// ALGLIB: Copyright 15.08.2010 by Sergey Bochkanov
void lsfitsetxrep(const lsfitstate &state, const bool needxrep);

// This function sets scaling coefficients for underlying optimizer.
//
// ALGLIB optimizers use scaling matrices to test stopping  conditions  (step
// size and gradient are scaled before comparison with tolerances).  Scale of
// the I-th variable is a translation invariant measure of:
// a) "how large" the variable is
// b) how large the step should be to make significant changes in the function
//
// Generally, scale is NOT considered to be a form of preconditioner.  But LM
// optimizer is unique in that it uses scaling matrix both  in  the  stopping
// condition tests and as Marquardt damping factor.
//
// Proper scaling is very important for the algorithm performance. It is less
// important for the quality of results, but still has some influence (it  is
// easier  to  converge  when  variables  are  properly  scaled, so premature
// stopping is possible when very badly scalled variables are  combined  with
// relaxed stopping conditions).
//
// Inputs:
//     State   -   structure stores algorithm state
//     S       -   array[N], non-zero scaling coefficients
//                 S[i] may be negative, sign doesn't matter.
// ALGLIB: Copyright 14.01.2011 by Sergey Bochkanov
void lsfitsetscale(const lsfitstate &state, const real_1d_array &s);

// This function sets boundary constraints for underlying optimizer
//
// Boundary constraints are inactive by default (after initial creation).
// They are preserved until explicitly turned off with another SetBC() call.
//
// Inputs:
//     State   -   structure stores algorithm state
//     BndL    -   lower bounds, array[K].
//                 If some (all) variables are unbounded, you may specify
//                 very small number or -INF (latter is recommended because
//                 it will allow solver to use better algorithm).
//     BndU    -   upper bounds, array[K].
//                 If some (all) variables are unbounded, you may specify
//                 very large number or +INF (latter is recommended because
//                 it will allow solver to use better algorithm).
//
// NOTE 1: it is possible to specify BndL[i]=BndU[i]. In this case I-th
// variable will be "frozen" at X[i]=BndL[i]=BndU[i].
//
// NOTE 2: unlike other constrained optimization algorithms, this solver  has
// following useful properties:
// * bound constraints are always satisfied exactly
// * function is evaluated only INSIDE area specified by bound constraints
// ALGLIB: Copyright 14.01.2011 by Sergey Bochkanov
void lsfitsetbc(const lsfitstate &state, const real_1d_array &bndl, const real_1d_array &bndu);

// This function sets linear constraints for underlying optimizer
//
// Linear constraints are inactive by default (after initial creation).
// They are preserved until explicitly turned off with another SetLC() call.
//
// Inputs:
//     State   -   structure stores algorithm state
//     C       -   linear constraints, array[K,N+1].
//                 Each row of C represents one constraint, either equality
//                 or inequality (see below):
//                 * first N elements correspond to coefficients,
//                 * last element corresponds to the right part.
//                 All elements of C (including right part) must be finite.
//     CT      -   type of constraints, array[K]:
//                 * if CT[i] > 0, then I-th constraint is C[i,*]*x >= C[i,n+1]
//                 * if CT[i]=0, then I-th constraint is C[i,*]*x  = C[i,n+1]
//                 * if CT[i] < 0, then I-th constraint is C[i,*]*x <= C[i,n+1]
//     K       -   number of equality/inequality constraints, K >= 0:
//                 * if given, only leading K elements of C/CT are used
//                 * if not given, automatically determined from sizes of C/CT
//
// IMPORTANT: if you have linear constraints, it is strongly  recommended  to
//            set scale of variables with lsfitsetscale(). QP solver which is
//            used to calculate linearly constrained steps heavily relies  on
//            good scaling of input problems.
//
// NOTE: linear  (non-box)  constraints  are  satisfied only approximately  -
//       there  always  exists some violation due  to  numerical  errors  and
//       algorithmic limitations.
//
// NOTE: general linear constraints  add  significant  overhead  to  solution
//       process. Although solver performs roughly same amount of  iterations
//       (when compared  with  similar  box-only  constrained  problem), each
//       iteration   now    involves  solution  of  linearly  constrained  QP
//       subproblem, which requires ~3-5 times more Cholesky  decompositions.
//       Thus, if you can reformulate your problem in such way  this  it  has
//       only box constraints, it may be beneficial to do so.
// ALGLIB: Copyright 29.04.2017 by Sergey Bochkanov
void lsfitsetlc(const lsfitstate &state, const real_2d_array &c, const integer_1d_array &ct, const ae_int_t k);
void lsfitsetlc(const lsfitstate &state, const real_2d_array &c, const integer_1d_array &ct);

// This function provides reverse communication interface
// Reverse communication interface is not documented or recommended for use.
// See below for functions which provide better documented API
bool lsfititeration(const lsfitstate &state);

// This family of functions is used to launch iterations of nonlinear fitter
//
// These functions accept following parameters:
//     state   -   algorithm state
//     func    -   callback which calculates function (or merit function)
//                 value func at given point x
//     grad    -   callback which calculates function (or merit function)
//                 value func and gradient grad at given point x
//     hess    -   callback which calculates function (or merit function)
//                 value func, gradient grad and Hessian hess at given point x
//     rep     -   optional callback which is called after each iteration
//                 can be NULL
//     ptr     -   optional pointer which is passed to func/grad/hess/jac/rep
//                 can be NULL
//
// NOTES:
//
// 1. this algorithm is somewhat unusual because it works with  parameterized
//    function f(C,X), where X is a function argument (we  have  many  points
//    which are characterized by different  argument  values),  and  C  is  a
//    parameter to fit.
//
//    For example, if we want to do linear fit by f(c0,c1,x) = c0*x+c1,  then
//    x will be argument, and {c0,c1} will be parameters.
//
//    It is important to understand that this algorithm finds minimum in  the
//    space of function PARAMETERS (not arguments), so it  needs  derivatives
//    of f() with respect to C, not X.
//
//    In the example above it will need f=c0*x+c1 and {df/dc0,df/dc1} = {x,1}
//    instead of {df/dx} = {c0}.
//
// 2. Callback functions accept C as the first parameter, and X as the second
//
// 3. If  state  was  created  with  LSFitCreateFG(),  algorithm  needs  just
//    function   and   its   gradient,   but   if   state   was  created with
//    LSFitCreateFGH(), algorithm will need function, gradient and Hessian.
//
//    According  to  the  said  above,  there  ase  several  versions of this
//    function, which accept different sets of callbacks.
//
//    This flexibility opens way to subtle errors - you may create state with
//    LSFitCreateFGH() (optimization using Hessian), but call function  which
//    does not accept Hessian. So when algorithm will request Hessian,  there
//    will be no callback to call. In this case exception will be thrown.
//
//    Be careful to avoid such errors because there is no way to find them at
//    compile time - you can see them at runtime only.
//
// ALGLIB: Copyright 17.08.2009 by Sergey Bochkanov
void lsfitfit(lsfitstate &state, void (*func)(const real_1d_array &c, const real_1d_array &x, double &func, void *ptr), void (*rep)(const real_1d_array &c, double func, void *ptr) = NULL, void *ptr = NULL);
void lsfitfit(lsfitstate &state, void (*func)(const real_1d_array &c, const real_1d_array &x, double &func, void *ptr), void (*grad)(const real_1d_array &c, const real_1d_array &x, double &func, real_1d_array &grad, void *ptr), void (*rep)(const real_1d_array &c, double func, void *ptr) = NULL, void *ptr = NULL);
void lsfitfit(lsfitstate &state, void (*func)(const real_1d_array &c, const real_1d_array &x, double &func, void *ptr), void (*grad)(const real_1d_array &c, const real_1d_array &x, double &func, real_1d_array &grad, void *ptr), void (*hess)(const real_1d_array &c, const real_1d_array &x, double &func, real_1d_array &grad, real_2d_array &hess, void *ptr), void (*rep)(const real_1d_array &c, double func, void *ptr) = NULL, void *ptr = NULL);

// Nonlinear least squares fitting results.
//
// Called after return from LSFitFit().
//
// Inputs:
//     State   -   algorithm state
//
// Outputs:
//     Info    -   completion code:
//                     * -8    optimizer   detected  NAN/INF  in  the  target
//                             function and/or gradient
//                     * -7    gradient verification failed.
//                             See LSFitSetGradientCheck() for more information.
//                     * -3    inconsistent constraints
//                     *  2    relative step is no more than EpsX.
//                     *  5    MaxIts steps was taken
//                     *  7    stopping conditions are too stringent,
//                             further improvement is impossible
//     C       -   array[0..K-1], solution
//     Rep     -   optimization report. On success following fields are set:
//                 * R2                non-adjusted coefficient of determination
//                                     (non-weighted)
//                 * RMSError          rms error on the (X,Y).
//                 * AvgError          average error on the (X,Y).
//                 * AvgRelError       average relative error on the non-zero Y
//                 * MaxError          maximum error
//                                     NON-WEIGHTED ERRORS ARE CALCULATED
//                 * WRMSError         weighted rms error on the (X,Y).
//
// ERRORS IN PARAMETERS
//
// This  solver  also  calculates different kinds of errors in parameters and
// fills corresponding fields of report:
// * Rep.CovPar        covariance matrix for parameters, array[K,K].
// * Rep.ErrPar        errors in parameters, array[K],
//                     errpar = sqrt(diag(CovPar))
// * Rep.ErrCurve      vector of fit errors - standard deviations of empirical
//                     best-fit curve from "ideal" best-fit curve built  with
//                     infinite number of samples, array[N].
//                     errcurve = sqrt(diag(J*CovPar*J')),
//                     where J is Jacobian matrix.
// * Rep.Noise         vector of per-point estimates of noise, array[N]
//
// IMPORTANT:  errors  in  parameters  are  calculated  without  taking  into
//             account boundary/linear constraints! Presence  of  constraints
//             changes distribution of errors, but there is no  easy  way  to
//             account for constraints when you calculate covariance matrix.
//
// NOTE:       noise in the data is estimated as follows:
//             * for fitting without user-supplied  weights  all  points  are
//               assumed to have same level of noise, which is estimated from
//               the data
//             * for fitting with user-supplied weights we assume that  noise
//               level in I-th point is inversely proportional to Ith weight.
//               Coefficient of proportionality is estimated from the data.
//
// NOTE:       we apply small amount of regularization when we invert squared
//             Jacobian and calculate covariance matrix. It  guarantees  that
//             algorithm won't divide by zero  during  inversion,  but  skews
//             error estimates a bit (fractional error is about 10^-9).
//
//             However, we believe that this difference is insignificant  for
//             all practical purposes except for the situation when you  want
//             to compare ALGLIB results with "reference"  implementation  up
//             to the last significant digit.
//
// NOTE:       covariance matrix is estimated using  correction  for  degrees
//             of freedom (covariances are divided by N-M instead of dividing
//             by N).
// ALGLIB: Copyright 17.08.2009 by Sergey Bochkanov
void lsfitresults(const lsfitstate &state, ae_int_t &info, real_1d_array &c, lsfitreport &rep);

// This  subroutine  turns  on  verification  of  the  user-supplied analytic
// gradient:
// * user calls this subroutine before fitting begins
// * LSFitFit() is called
// * prior to actual fitting, for  each  point  in  data  set  X_i  and  each
//   component  of  parameters  being  fited C_j algorithm performs following
//   steps:
//   * two trial steps are made to C_j-TestStep*S[j] and C_j+TestStep*S[j],
//     where C_j is j-th parameter and S[j] is a scale of j-th parameter
//   * if needed, steps are bounded with respect to constraints on C[]
//   * F(X_i|C) is evaluated at these trial points
//   * we perform one more evaluation in the middle point of the interval
//   * we  build  cubic  model using function values and derivatives at trial
//     points and we compare its prediction with actual value in  the  middle
//     point
//   * in case difference between prediction and actual value is higher  than
//     some predetermined threshold, algorithm stops with completion code -7;
//     Rep.VarIdx is set to index of the parameter with incorrect derivative.
// * after verification is over, algorithm proceeds to the actual optimization.
//
// NOTE 1: verification needs N*K (points count * parameters count)  gradient
//         evaluations. It is very costly and you should use it only for  low
//         dimensional  problems,  when  you  want  to  be  sure  that you've
//         correctly calculated analytic derivatives. You should not  use  it
//         in the production code  (unless  you  want  to  check  derivatives
//         provided by some third party).
//
// NOTE 2: you  should  carefully  choose  TestStep. Value which is too large
//         (so large that function behaviour is significantly non-cubic) will
//         lead to false alarms. You may use  different  step  for  different
//         parameters by means of setting scale with LSFitSetScale().
//
// NOTE 3: this function may lead to false positives. In case it reports that
//         I-th  derivative was calculated incorrectly, you may decrease test
//         step  and  try  one  more  time  - maybe your function changes too
//         sharply  and  your  step  is  too  large for such rapidly chanding
//         function.
//
// NOTE 4: this function works only for optimizers created with LSFitCreateWFG()
//         or LSFitCreateFG() constructors.
//
// Inputs:
//     State       -   structure used to store algorithm state
//     TestStep    -   verification step:
//                     * TestStep=0 turns verification off
//                     * TestStep > 0 activates verification
// ALGLIB: Copyright 15.06.2012 by Sergey Bochkanov
void lsfitsetgradientcheck(const lsfitstate &state, const double teststep);
} // end of namespace alglib

// === RBFV2 Package ===
// Depends on: (AlgLibMisc) NEARESTNEIGHBOR
// Depends on: LSFIT
namespace alglib_impl {
struct rbfv2calcbuffer {
   ae_vector x;
   ae_vector curboxmin;
   ae_vector curboxmax;
   double curdist2;
   ae_vector x123;
   ae_vector y123;
};
void rbfv2calcbuffer_init(void *_p, bool make_automatic);
void rbfv2calcbuffer_copy(void *_dst, void *_src, bool make_automatic);
void rbfv2calcbuffer_free(void *_p, bool make_automatic);

struct rbfv2model {
   ae_int_t ny;
   ae_int_t nx;
   ae_int_t bf;
   ae_int_t nh;
   ae_vector ri;
   ae_vector s;
   ae_vector kdroots;
   ae_vector kdnodes;
   ae_vector kdsplits;
   ae_vector kdboxmin;
   ae_vector kdboxmax;
   ae_vector cw;
   ae_matrix v;
   double lambdareg;
   ae_int_t maxits;
   double supportr;
   ae_int_t basisfunction;
   rbfv2calcbuffer calcbuf;
};
void rbfv2model_init(void *_p, bool make_automatic);
void rbfv2model_copy(void *_dst, void *_src, bool make_automatic);
void rbfv2model_free(void *_p, bool make_automatic);

struct rbfv2gridcalcbuffer {
   rbfv2calcbuffer calcbuf;
   ae_vector cx;
   ae_vector rx;
   ae_vector ry;
   ae_vector tx;
   ae_vector ty;
   ae_vector rf;
};
void rbfv2gridcalcbuffer_init(void *_p, bool make_automatic);
void rbfv2gridcalcbuffer_copy(void *_dst, void *_src, bool make_automatic);
void rbfv2gridcalcbuffer_free(void *_p, bool make_automatic);

struct rbfv2report {
   ae_int_t terminationtype;
   double maxerror;
   double rmserror;
};
void rbfv2report_init(void *_p, bool make_automatic);
void rbfv2report_copy(void *_dst, void *_src, bool make_automatic);
void rbfv2report_free(void *_p, bool make_automatic);
void rbfv2alloc(ae_serializer *s, rbfv2model *model);
void rbfv2serialize(ae_serializer *s, rbfv2model *model);
void rbfv2unserialize(ae_serializer *s, rbfv2model *model);

void rbfv2create(ae_int_t nx, ae_int_t ny, rbfv2model *s);
void rbfv2createcalcbuffer(rbfv2model *s, rbfv2calcbuffer *buf);
void rbfv2buildhierarchical(RMatrix *x, RMatrix *y, ae_int_t n, RVector *scalevec, ae_int_t aterm, ae_int_t nh, double rbase, double lambdans, rbfv2model *s, ae_int_t *progress10000, bool *terminationrequest, rbfv2report *rep);
double rbfv2farradius(ae_int_t bf);
double rbfv2nearradius(ae_int_t bf);
double rbfv2basisfunc(ae_int_t bf, double d2);
void rbfv2basisfuncdiff2(ae_int_t bf, double d2, double *f, double *df, double *d2f);
double rbfv2calc1(rbfv2model *s, double x0);
double rbfv2calc2(rbfv2model *s, double x0, double x1);
double rbfv2calc3(rbfv2model *s, double x0, double x1, double x2);
void rbfv2calcbuf(rbfv2model *s, RVector *x, RVector *y);
void rbfv2tscalcbuf(rbfv2model *s, rbfv2calcbuffer *buf, RVector *x, RVector *y);
void rbfv2gridcalc2(rbfv2model *s, RVector *x0, ae_int_t n0, RVector *x1, ae_int_t n1, RMatrix *y);
void rbfv2gridcalcvx(rbfv2model *s, RVector *x0, ae_int_t n0, RVector *x1, ae_int_t n1, RVector *x2, ae_int_t n2, RVector *x3, ae_int_t n3, BVector *flagy, bool sparsey, RVector *y);
void rbfv2partialgridcalcrec(rbfv2model *s, RVector *x0, ae_int_t n0, RVector *x1, ae_int_t n1, RVector *x2, ae_int_t n2, RVector *x3, ae_int_t n3, ZVector *blocks0, ae_int_t block0a, ae_int_t block0b, ZVector *blocks1, ae_int_t block1a, ae_int_t block1b, ZVector *blocks2, ae_int_t block2a, ae_int_t block2b, ZVector *blocks3, ae_int_t block3a, ae_int_t block3b, BVector *flagy, bool sparsey, ae_int_t levelidx, double avgfuncpernode, ae_shared_pool *bufpool, RVector *y);
void rbfv2unpack(rbfv2model *s, ae_int_t *nx, ae_int_t *ny, RMatrix *xwr, ae_int_t *nc, RMatrix *v);
} // end of namespace alglib_impl

// === SPLINE2D Package ===
// Depends on: (AlgLibInternal) SCODES
// Depends on: SPLINE1D
namespace alglib_impl {
struct spline2dinterpolant {
   ae_int_t stype;
   ae_int_t n;
   ae_int_t m;
   ae_int_t d;
   ae_vector x;
   ae_vector y;
   ae_vector f;
};
void spline2dinterpolant_init(void *_p, bool make_automatic);
void spline2dinterpolant_copy(void *_dst, void *_src, bool make_automatic);
void spline2dinterpolant_free(void *_p, bool make_automatic);

struct spline2dbuilder {
   ae_int_t priorterm;
   double priortermval;
   ae_int_t areatype;
   double xa;
   double xb;
   double ya;
   double yb;
   ae_int_t gridtype;
   ae_int_t kx;
   ae_int_t ky;
   double smoothing;
   ae_int_t nlayers;
   ae_int_t solvertype;
   double lambdabase;
   ae_vector xy;
   ae_int_t npoints;
   ae_int_t d;
   double sx;
   double sy;
   bool adddegreeoffreedom;
   ae_int_t interfacesize;
   ae_int_t lsqrcnt;
   ae_int_t maxcoresize;
};
void spline2dbuilder_init(void *_p, bool make_automatic);
void spline2dbuilder_copy(void *_dst, void *_src, bool make_automatic);
void spline2dbuilder_free(void *_p, bool make_automatic);

struct spline2dfitreport {
   double rmserror;
   double avgerror;
   double maxerror;
   double r2;
};
void spline2dfitreport_init(void *_p, bool make_automatic);
void spline2dfitreport_copy(void *_dst, void *_src, bool make_automatic);
void spline2dfitreport_free(void *_p, bool make_automatic);

struct spline2dxdesignmatrix {
   ae_int_t blockwidth;
   ae_int_t kx;
   ae_int_t ky;
   ae_int_t npoints;
   ae_int_t nrows;
   ae_int_t ndenserows;
   ae_int_t ndensebatches;
   ae_int_t d;
   ae_int_t maxbatch;
   ae_matrix vals;
   ae_vector batches;
   ae_vector batchbases;
   double lambdareg;
   ae_vector tmp0;
   ae_vector tmp1;
   ae_matrix tmp2;
};
void spline2dxdesignmatrix_init(void *_p, bool make_automatic);
void spline2dxdesignmatrix_copy(void *_dst, void *_src, bool make_automatic);
void spline2dxdesignmatrix_free(void *_p, bool make_automatic);

struct spline2dblockllsbuf {
   linlsqrstate solver;
   linlsqrreport solverrep;
   ae_matrix blockata;
   ae_matrix trsmbuf2;
   ae_matrix cholbuf2;
   ae_vector cholbuf1;
   ae_vector tmp0;
   ae_vector tmp1;
};
void spline2dblockllsbuf_init(void *_p, bool make_automatic);
void spline2dblockllsbuf_copy(void *_dst, void *_src, bool make_automatic);
void spline2dblockllsbuf_free(void *_p, bool make_automatic);

struct spline2dfastddmbuf {
   spline2dxdesignmatrix xdesignmatrix;
   ae_vector tmp0;
   ae_vector tmpz;
   spline2dfitreport dummyrep;
   spline2dinterpolant localmodel;
   spline2dblockllsbuf blockllsbuf;
};
void spline2dfastddmbuf_init(void *_p, bool make_automatic);
void spline2dfastddmbuf_copy(void *_dst, void *_src, bool make_automatic);
void spline2dfastddmbuf_free(void *_p, bool make_automatic);
void spline2dalloc(ae_serializer *s, spline2dinterpolant *spline);
void spline2dserialize(ae_serializer *s, spline2dinterpolant *spline);
void spline2dunserialize(ae_serializer *s, spline2dinterpolant *spline);

double spline2dcalc(spline2dinterpolant *c, double x, double y);
void spline2ddiff(spline2dinterpolant *c, double x, double y, double *f, double *fx, double *fy, double *fxy);
void spline2dcalcvbuf(spline2dinterpolant *c, double x, double y, RVector *f);
double spline2dcalcvi(spline2dinterpolant *c, double x, double y, ae_int_t i);
void spline2dcalcv(spline2dinterpolant *c, double x, double y, RVector *f);
void spline2ddiffvi(spline2dinterpolant *c, double x, double y, ae_int_t i, double *f, double *fx, double *fy, double *fxy);
void spline2dlintransxy(spline2dinterpolant *c, double ax, double bx, double ay, double by);
void spline2dlintransf(spline2dinterpolant *c, double a, double b);
void spline2dcopy(spline2dinterpolant *c, spline2dinterpolant *cc);
void spline2dresamplebicubic(RMatrix *a, ae_int_t oldheight, ae_int_t oldwidth, RMatrix *b, ae_int_t newheight, ae_int_t newwidth);
void spline2dresamplebilinear(RMatrix *a, ae_int_t oldheight, ae_int_t oldwidth, RMatrix *b, ae_int_t newheight, ae_int_t newwidth);
void spline2dbuildbilinearv(RVector *x, ae_int_t n, RVector *y, ae_int_t m, RVector *f, ae_int_t d, spline2dinterpolant *c);
void spline2dbuildbicubicv(RVector *x, ae_int_t n, RVector *y, ae_int_t m, RVector *f, ae_int_t d, spline2dinterpolant *c);
void spline2dunpackv(spline2dinterpolant *c, ae_int_t *m, ae_int_t *n, ae_int_t *d, RMatrix *tbl);
void spline2dbuildbilinear(RVector *x, RVector *y, RMatrix *f, ae_int_t m, ae_int_t n, spline2dinterpolant *c);
void spline2dbuildbicubic(RVector *x, RVector *y, RMatrix *f, ae_int_t m, ae_int_t n, spline2dinterpolant *c);
void spline2dunpack(spline2dinterpolant *c, ae_int_t *m, ae_int_t *n, RMatrix *tbl);
void spline2dbuildercreate(ae_int_t d, spline2dbuilder *state);
void spline2dbuildersetuserterm(spline2dbuilder *state, double v);
void spline2dbuildersetlinterm(spline2dbuilder *state);
void spline2dbuildersetconstterm(spline2dbuilder *state);
void spline2dbuildersetzeroterm(spline2dbuilder *state);
void spline2dbuildersetpoints(spline2dbuilder *state, RMatrix *xy, ae_int_t n);
void spline2dbuildersetareaauto(spline2dbuilder *state);
void spline2dbuildersetarea(spline2dbuilder *state, double xa, double xb, double ya, double yb);
void spline2dbuildersetgrid(spline2dbuilder *state, ae_int_t kx, ae_int_t ky);
void spline2dbuildersetalgofastddm(spline2dbuilder *state, ae_int_t nlayers, double lambdav);
void spline2dbuildersetalgoblocklls(spline2dbuilder *state, double lambdans);
void spline2dbuildersetalgonaivells(spline2dbuilder *state, double lambdans);
void spline2dfit(spline2dbuilder *state, spline2dinterpolant *s, spline2dfitreport *rep);
} // end of namespace alglib_impl

namespace alglib {
// 2-dimensional spline inteprolant
DecClass(spline2dinterpolant, EndD);

// Nonlinear least squares solver used to fit 2D splines to data
DecClass(spline2dbuilder, EndD);

// Spline 2D fitting report:
//     rmserror        RMS error
//     avgerror        average error
//     maxerror        maximum error
//     r2              coefficient of determination,  R-squared, 1-RSS/TSS
DecClass(spline2dfitreport, double &rmserror; double &avgerror; double &maxerror; double &r2;);

// These functions serialize a data structure to a C++ string or stream.
// * serialization can be freely moved across 32-bit and 64-bit systems,
//   and different byte orders. For example, you can serialize a string
//   on a SPARC and unserialize it on an x86.
// * ALGLIB++ serialization is compatible with serialization in ALGLIB,
//   in both directions.
// Important properties of s_out:
// * it contains alphanumeric characters, dots, underscores, minus signs
// * these symbols are grouped into words, which are separated by spaces
//   and Windows-style (CR+LF) newlines
void spline2dserialize(spline2dinterpolant &obj, std::string &s_out);
void spline2dserialize(spline2dinterpolant &obj, std::ostream &s_out);

// These functions unserialize a data structure from a C++ string or stream.
// Important properties of s_in:
// * any combination of spaces, tabs, Windows or Unix stype newlines can
//   be used as separators, so as to allow flexible reformatting of the
//   stream or string from text or XML files.
// * But you should not insert separators into the middle of the "words"
//   nor you should change case of letters.
void spline2dunserialize(const std::string &s_in, spline2dinterpolant &obj);
void spline2dunserialize(const std::istream &s_in, spline2dinterpolant &obj);

// This subroutine calculates the value of the bilinear or bicubic spline  at
// the given point X.
//
// Inputs:
//     C   -   2D spline object.
//             Built by spline2dbuildbilinearv or spline2dbuildbicubicv.
//     X, Y-   point
//
// Result:
//     S(x,y)
//
// ALGLIB Project: Copyright 05.07.2007 by Sergey Bochkanov
double spline2dcalc(const spline2dinterpolant &c, const double x, const double y);

// This subroutine calculates the value of the bilinear or bicubic spline  at
// the given point X and its derivatives.
//
// Inputs:
//     C   -   spline interpolant.
//     X, Y-   point
//
// Outputs:
//     F   -   S(x,y)
//     FX  -   dS(x,y)/dX
//     FY  -   dS(x,y)/dY
//     FXY -   d2S(x,y)/dXdY
//
// ALGLIB Project: Copyright 05.07.2007 by Sergey Bochkanov
void spline2ddiff(const spline2dinterpolant &c, const double x, const double y, double &f, double &fx, double &fy, double &fxy);

// This subroutine calculates bilinear or bicubic vector-valued spline at the
// given point (X,Y).
//
// If you need just some specific component of vector-valued spline, you  can
// use spline2dcalcvi() function.
//
// Inputs:
//     C   -   spline interpolant.
//     X, Y-   point
//     F   -   output buffer, possibly preallocated array. In case array size
//             is large enough to store result, it is not reallocated.  Array
//             which is too short will be reallocated
//
// Outputs:
//     F   -   array[D] (or larger) which stores function values
//
// ALGLIB Project: Copyright 01.02.2018 by Sergey Bochkanov
void spline2dcalcvbuf(const spline2dinterpolant &c, const double x, const double y, real_1d_array &f);

// This subroutine calculates specific component of vector-valued bilinear or
// bicubic spline at the given point (X,Y).
//
// Inputs:
//     C   -   spline interpolant.
//     X, Y-   point
//     I   -   component index, in [0,D). An exception is generated for out
//             of range values.
//
// Result:
//     value of I-th component
//
// ALGLIB Project: Copyright 01.02.2018 by Sergey Bochkanov
double spline2dcalcvi(const spline2dinterpolant &c, const double x, const double y, const ae_int_t i);

// This subroutine calculates bilinear or bicubic vector-valued spline at the
// given point (X,Y).
//
// Inputs:
//     C   -   spline interpolant.
//     X, Y-   point
//
// Outputs:
//     F   -   array[D] which stores function values.  F is out-parameter and
//             it  is  reallocated  after  call to this function. In case you
//             want  to    reuse  previously  allocated  F,   you   may   use
//             Spline2DCalcVBuf(),  which  reallocates  F only when it is too
//             small.
//
// ALGLIB Project: Copyright 16.04.2012 by Sergey Bochkanov
void spline2dcalcv(const spline2dinterpolant &c, const double x, const double y, real_1d_array &f);

// This subroutine calculates value of  specific  component  of  bilinear  or
// bicubic vector-valued spline and its derivatives.
//
// Inputs:
//     C   -   spline interpolant.
//     X, Y-   point
//     I   -   component index, in [0,D)
//
// Outputs:
//     F   -   S(x,y)
//     FX  -   dS(x,y)/dX
//     FY  -   dS(x,y)/dY
//     FXY -   d2S(x,y)/dXdY
//
// ALGLIB Project: Copyright 05.07.2007 by Sergey Bochkanov
void spline2ddiffvi(const spline2dinterpolant &c, const double x, const double y, const ae_int_t i, double &f, double &fx, double &fy, double &fxy);

// This subroutine performs linear transformation of the spline argument.
//
// Inputs:
//     C       -   spline interpolant
//     AX, BX  -   transformation coefficients: x = A*t + B
//     AY, BY  -   transformation coefficients: y = A*u + B
// Result:
//     C   -   transformed spline
//
// ALGLIB Project: Copyright 30.06.2007 by Sergey Bochkanov
void spline2dlintransxy(const spline2dinterpolant &c, const double ax, const double bx, const double ay, const double by);

// This subroutine performs linear transformation of the spline.
//
// Inputs:
//     C   -   spline interpolant.
//     A, B-   transformation coefficients: S2(x,y) = A*S(x,y) + B
//
// Outputs:
//     C   -   transformed spline
//
// ALGLIB Project: Copyright 30.06.2007 by Sergey Bochkanov
void spline2dlintransf(const spline2dinterpolant &c, const double a, const double b);

// This subroutine makes the copy of the spline model.
//
// Inputs:
//     C   -   spline interpolant
//
// Outputs:
//     CC  -   spline copy
//
// ALGLIB Project: Copyright 29.06.2007 by Sergey Bochkanov
void spline2dcopy(const spline2dinterpolant &c, spline2dinterpolant &cc);

// Bicubic spline resampling
//
// Inputs:
//     A           -   function values at the old grid,
//                     array[0..OldHeight-1, 0..OldWidth-1]
//     OldHeight   -   old grid height, OldHeight > 1
//     OldWidth    -   old grid width, OldWidth > 1
//     NewHeight   -   new grid height, NewHeight > 1
//     NewWidth    -   new grid width, NewWidth > 1
//
// Outputs:
//     B           -   function values at the new grid,
//                     array[0..NewHeight-1, 0..NewWidth-1]
//
// ALGLIB Routine: Copyright 2007 May 15 by Sergey Bochkanov
void spline2dresamplebicubic(const real_2d_array &a, const ae_int_t oldheight, const ae_int_t oldwidth, real_2d_array &b, const ae_int_t newheight, const ae_int_t newwidth);

// Bilinear spline resampling
//
// Inputs:
//     A           -   function values at the old grid,
//                     array[0..OldHeight-1, 0..OldWidth-1]
//     OldHeight   -   old grid height, OldHeight > 1
//     OldWidth    -   old grid width, OldWidth > 1
//     NewHeight   -   new grid height, NewHeight > 1
//     NewWidth    -   new grid width, NewWidth > 1
//
// Outputs:
//     B           -   function values at the new grid,
//                     array[0..NewHeight-1, 0..NewWidth-1]
//
// ALGLIB Routine: Copyright 09.07.2007 by Sergey Bochkanov
void spline2dresamplebilinear(const real_2d_array &a, const ae_int_t oldheight, const ae_int_t oldwidth, real_2d_array &b, const ae_int_t newheight, const ae_int_t newwidth);

// This subroutine builds bilinear vector-valued spline.
//
// Inputs:
//     X   -   spline abscissas, array[0..N-1]
//     Y   -   spline ordinates, array[0..M-1]
//     F   -   function values, array[0..M*N*D-1]:
//             * first D elements store D values at (X[0],Y[0])
//             * next D elements store D values at (X[1],Y[0])
//             * general form - D function values at (X[i],Y[j]) are stored
//               at F[D*(J*N+I)...D*(J*N+I)+D-1].
//     M,N -   grid size, M >= 2, N >= 2
//     D   -   vector dimension, D >= 1
//
// Outputs:
//     C   -   spline interpolant
//
// ALGLIB Project: Copyright 16.04.2012 by Sergey Bochkanov
void spline2dbuildbilinearv(const real_1d_array &x, const ae_int_t n, const real_1d_array &y, const ae_int_t m, const real_1d_array &f, const ae_int_t d, spline2dinterpolant &c);

// This subroutine builds bicubic vector-valued spline.
//
// Inputs:
//     X   -   spline abscissas, array[0..N-1]
//     Y   -   spline ordinates, array[0..M-1]
//     F   -   function values, array[0..M*N*D-1]:
//             * first D elements store D values at (X[0],Y[0])
//             * next D elements store D values at (X[1],Y[0])
//             * general form - D function values at (X[i],Y[j]) are stored
//               at F[D*(J*N+I)...D*(J*N+I)+D-1].
//     M,N -   grid size, M >= 2, N >= 2
//     D   -   vector dimension, D >= 1
//
// Outputs:
//     C   -   spline interpolant
//
// ALGLIB Project: Copyright 16.04.2012 by Sergey Bochkanov
void spline2dbuildbicubicv(const real_1d_array &x, const ae_int_t n, const real_1d_array &y, const ae_int_t m, const real_1d_array &f, const ae_int_t d, spline2dinterpolant &c);

// This subroutine unpacks two-dimensional spline into the coefficients table
//
// Inputs:
//     C   -   spline interpolant.
//
// Result:
//     M, N-   grid size (x-axis and y-axis)
//     D   -   number of components
//     Tbl -   coefficients table, unpacked format,
//             D - components: [0..(N-1)*(M-1)*D-1, 0..19].
//             For T=0..D-1 (component index), I = 0...N-2 (x index),
//             J=0..M-2 (y index):
//                 K :=  T + I*D + J*D*(N-1)
//
//                 K-th row stores decomposition for T-th component of the
//                 vector-valued function
//
//                 Tbl[K,0] = X[i]
//                 Tbl[K,1] = X[i+1]
//                 Tbl[K,2] = Y[j]
//                 Tbl[K,3] = Y[j+1]
//                 Tbl[K,4] = C00
//                 Tbl[K,5] = C01
//                 Tbl[K,6] = C02
//                 Tbl[K,7] = C03
//                 Tbl[K,8] = C10
//                 Tbl[K,9] = C11
//                 ...
//                 Tbl[K,19] = C33
//             On each grid square spline is equals to:
//                 S(x) = SUM(c[i,j]*(t^i)*(u^j), i=0..3, j=0..3)
//                 t = x-x[j]
//                 u = y-y[i]
//
// ALGLIB Project: Copyright 16.04.2012 by Sergey Bochkanov
void spline2dunpackv(const spline2dinterpolant &c, ae_int_t &m, ae_int_t &n, ae_int_t &d, real_2d_array &tbl);

// This subroutine was deprecated in ALGLIB 3.6.0
//
// We recommend you to switch  to  Spline2DBuildBilinearV(),  which  is  more
// flexible and accepts its arguments in more convenient order.
//
// ALGLIB Project: Copyright 05.07.2007 by Sergey Bochkanov
void spline2dbuildbilinear(const real_1d_array &x, const real_1d_array &y, const real_2d_array &f, const ae_int_t m, const ae_int_t n, spline2dinterpolant &c);

// This subroutine was deprecated in ALGLIB 3.6.0
//
// We recommend you to switch  to  Spline2DBuildBicubicV(),  which  is  more
// flexible and accepts its arguments in more convenient order.
//
// ALGLIB Project: Copyright 05.07.2007 by Sergey Bochkanov
void spline2dbuildbicubic(const real_1d_array &x, const real_1d_array &y, const real_2d_array &f, const ae_int_t m, const ae_int_t n, spline2dinterpolant &c);

// This subroutine was deprecated in ALGLIB 3.6.0
//
// We recommend you to switch  to  Spline2DUnpackV(),  which is more flexible
// and accepts its arguments in more convenient order.
//
// ALGLIB Project: Copyright 29.06.2007 by Sergey Bochkanov
void spline2dunpack(const spline2dinterpolant &c, ae_int_t &m, ae_int_t &n, real_2d_array &tbl);

// This subroutine creates least squares solver used to  fit  2D  splines  to
// irregularly sampled (scattered) data.
//
// Solver object is used to perform spline fits as follows:
// * solver object is created with spline2dbuildercreate() function
// * dataset is added with spline2dbuildersetpoints() function
// * fit area is chosen:
//   * spline2dbuildersetarea()     - for user-defined area
//   * spline2dbuildersetareaauto() - for automatically chosen area
// * number of grid nodes is chosen with spline2dbuildersetgrid()
// * prior term is chosen with one of the following functions:
//   * spline2dbuildersetlinterm()   to set linear prior
//   * spline2dbuildersetconstterm() to set constant prior
//   * spline2dbuildersetzeroterm()  to set zero prior
//   * spline2dbuildersetuserterm()  to set user-defined constant prior
// * solver algorithm is chosen with either:
//   * spline2dbuildersetalgoblocklls() - BlockLLS algorithm, medium-scale problems
//   * spline2dbuildersetalgofastddm()  - FastDDM algorithm, large-scale problems
// * finally, fitting itself is performed with spline2dfit() function.
//
// Most of the steps above can be omitted,  solver  is  configured with  good
// defaults. The minimum is to call:
// * spline2dbuildercreate() to create solver object
// * spline2dbuildersetpoints() to specify dataset
// * spline2dbuildersetgrid() to tell how many nodes you need
// * spline2dfit() to perform fit
//
// Inputs:
//     D   -   positive number, number of Y-components: D=1 for simple scalar
//             fit, D > 1 for vector-valued spline fitting.
//
// Outputs:
//     S   -   solver object
//
// ALGLIB Project: Copyright 29.01.2018 by Sergey Bochkanov
void spline2dbuildercreate(const ae_int_t d, spline2dbuilder &state);

// This function sets constant prior term (model is a sum of  bicubic  spline
// and global prior, which can be linear, constant, user-defined  constant or
// zero).
//
// Constant prior term is determined by least squares fitting.
//
// Inputs:
//     S       -   spline builder
//     V       -   value for user-defined prior
// ALGLIB: Copyright 01.02.2018 by Sergey Bochkanov
void spline2dbuildersetuserterm(const spline2dbuilder &state, const double v);

// This function sets linear prior term (model is a sum of bicubic spline and
// global  prior,  which  can  be  linear, constant, user-defined constant or
// zero).
//
// Linear prior term is determined by least squares fitting.
//
// Inputs:
//     S       -   spline builder
// ALGLIB: Copyright 01.02.2018 by Sergey Bochkanov
void spline2dbuildersetlinterm(const spline2dbuilder &state);

// This function sets constant prior term (model is a sum of  bicubic  spline
// and global prior, which can be linear, constant, user-defined  constant or
// zero).
//
// Constant prior term is determined by least squares fitting.
//
// Inputs:
//     S       -   spline builder
// ALGLIB: Copyright 01.02.2018 by Sergey Bochkanov
void spline2dbuildersetconstterm(const spline2dbuilder &state);

// This function sets zero prior term (model is a sum of bicubic  spline  and
// global  prior,  which  can  be  linear, constant, user-defined constant or
// zero).
//
// Inputs:
//     S       -   spline builder
// ALGLIB: Copyright 01.02.2018 by Sergey Bochkanov
void spline2dbuildersetzeroterm(const spline2dbuilder &state);

// This function adds dataset to the builder object.
//
// This function overrides results of the previous calls, i.e. multiple calls
// of this function will result in only the last set being added.
//
// Inputs:
//     S       -   spline 2D builder object
//     XY      -   points, array[N,2+D]. One  row  corresponds to  one  point
//                 in the dataset. First 2  elements  are  coordinates,  next
//                 D  elements are function values. Array may  be larger than
//                 specified, in  this  case  only leading [N,NX+NY] elements
//                 will be used.
//     N       -   number of points in the dataset
// ALGLIB: Copyright 05.02.2018 by Sergey Bochkanov
void spline2dbuildersetpoints(const spline2dbuilder &state, const real_2d_array &xy, const ae_int_t n);

// This function sets area where 2D spline interpolant is built. "Auto" means
// that area extent is determined automatically from dataset extent.
//
// Inputs:
//     S       -   spline 2D builder object
// ALGLIB: Copyright 05.02.2018 by Sergey Bochkanov
void spline2dbuildersetareaauto(const spline2dbuilder &state);

// This  function  sets  area  where  2D  spline  interpolant  is   built  to
// user-defined one: [XA,XB]*[YA,YB]
//
// Inputs:
//     S       -   spline 2D builder object
//     XA,XB   -   spatial extent in the first (X) dimension, XA < XB
//     YA,YB   -   spatial extent in the second (Y) dimension, YA < YB
// ALGLIB: Copyright 05.02.2018 by Sergey Bochkanov
void spline2dbuildersetarea(const spline2dbuilder &state, const double xa, const double xb, const double ya, const double yb);

// This  function  sets  nodes  count  for  2D spline interpolant. Fitting is
// performed on area defined with one of the "setarea"  functions;  this  one
// sets number of nodes placed upon the fitting area.
//
// Inputs:
//     S       -   spline 2D builder object
//     KX      -   nodes count for the first (X) dimension; fitting  interval
//                 [XA,XB] is separated into KX-1 subintervals, with KX nodes
//                 created at the boundaries.
//     KY      -   nodes count for the first (Y) dimension; fitting  interval
//                 [YA,YB] is separated into KY-1 subintervals, with KY nodes
//                 created at the boundaries.
//
// NOTE: at  least  4  nodes  is  created in each dimension, so KX and KY are
//       silently increased if needed.
// ALGLIB: Copyright 05.02.2018 by Sergey Bochkanov
void spline2dbuildersetgrid(const spline2dbuilder &state, const ae_int_t kx, const ae_int_t ky);

// This  function  allows  you to choose least squares solver used to perform
// fitting. This function sets solver algorithm to "FastDDM", which  performs
// fast parallel fitting by splitting problem into smaller chunks and merging
// results together.
//
// This solver is optimized for large-scale problems, starting  from  256x256
// grids, and up to 10000x10000 grids. Of course, it will  work  for  smaller
// grids too.
//
// More detailed description of the algorithm is given below:
// * algorithm generates hierarchy  of  nested  grids,  ranging  from  ~16x16
//   (topmost "layer" of the model) to ~KX*KY one (final layer). Upper layers
//   model global behavior of the function, lower layers are  used  to  model
//   fine details. Moving from layer to layer doubles grid density.
// * fitting  is  started  from  topmost  layer, subsequent layers are fitted
//   using residuals from previous ones.
// * user may choose to skip generation of upper layers and generate  only  a
//   few bottom ones, which  will  result  in  much  better  performance  and
//   parallelization efficiency, at the cost of algorithm inability to "patch"
//   large holes in the dataset.
// * every layer is regularized using progressively increasing regularization
//   coefficient; thus, increasing  LambdaV  penalizes  fine  details  first,
//   leaving lower frequencies almost intact for a while.
// * after fitting is done, all layers are merged together into  one  bicubic
//   spline
//
// IMPORTANT: regularization coefficient used by  this  solver  is  different
//            from the one used by  BlockLLS.  Latter  utilizes  nonlinearity
//            penalty,  which  is  global  in  nature  (large  regularization
//            results in global linear trend being  extracted);  this  solver
//            uses another, localized form of penalty, which is suitable  for
//            parallel processing.
//
// Notes on memory and performance:
// * memory requirements: most memory is consumed  during  modeling   of  the
//   higher layers; ~[512*NPoints] bytes is required for a  model  with  full
//   hierarchy of grids being generated. However, if you skip a  few  topmost
//   layers, you will get nearly constant (wrt. points count and  grid  size)
//   memory consumption.
// * serial running time: O(K*K)+O(NPoints) for a KxK grid
// * parallelism potential: good. You may get  nearly  linear  speed-up  when
//   performing fitting with just a few layers. Adding more layers results in
//   model becoming more global, which somewhat  reduces  efficiency  of  the
//   parallel code.
//
// Inputs:
//     S       -   spline 2D builder object
//     NLayers -   number of layers in the model:
//                 * NLayers >= 1 means that up  to  chosen  number  of  bottom
//                   layers is fitted
//                 * NLayers=0 means that maximum number of layers is  chosen
//                   (according to current grid size)
//                 * NLayers <= -1 means that up to |NLayers| topmost layers is
//                   skipped
//                 Recommendations:
//                 * good "default" value is 2 layers
//                 * you may need  more  layers,  if  your  dataset  is  very
//                   irregular and you want to "patch"  large  holes.  For  a
//                   grid step H (equal to AreaWidth/GridSize) you may expect
//                   that last layer reproduces variations at distance H (and
//                   can patch holes that wide); that higher  layers  operate
//                   at distances 2*H, 4*H, 8*H and so on.
//                 * good value for "bullletproof" mode is  NLayers=0,  which
//                   results in complete hierarchy of layers being generated.
//     LambdaV -   regularization coefficient, chosen in such a way  that  it
//                 penalizes bottom layers (fine details) first.
//                 LambdaV >= 0, zero value means that no penalty is applied.
// ALGLIB: Copyright 05.02.2018 by Sergey Bochkanov
void spline2dbuildersetalgofastddm(const spline2dbuilder &state, const ae_int_t nlayers, const double lambdav);

// This  function  allows  you to choose least squares solver used to perform
// fitting. This function sets solver algorithm to "BlockLLS", which performs
// least squares fitting  with  fast  sparse  direct  solver,  with  optional
// nonsmoothness penalty being applied.
//
// Nonlinearity penalty has the following form:
//
//                           [                                            ]
//     P() ~ Lambda* integral[ (d2S/dx2)^2 + 2*(d2S/dxdy)^2 + (d2S/dy2)^2 ]dxdy
//                           [                                            ]
//
// here integral is calculated over entire grid, and "~" means "proportional"
// because integral is normalized after calcilation. Extremely  large  values
// of Lambda result in linear fit being performed.
//
// NOTE: this algorithm is the most robust and controllable one,  but  it  is
//       limited by 512x512 grids and (say) up to 1.000.000 points.  However,
//       ALGLIB has one more  spline  solver:  FastDDM  algorithm,  which  is
//       intended for really large-scale problems (in 10M-100M range). FastDDM
//       algorithm also has better parallelism properties.
//
// More information on BlockLLS solver:
// * memory requirements: ~[32*K^3+256*NPoints]  bytes  for  KxK  grid   with
//   NPoints-sized dataset
// * serial running time: O(K^4+NPoints)
// * parallelism potential: limited. You may get some sublinear gain when
//   working with large grids (K's in 256..512 range)
//
// Inputs:
//     S       -   spline 2D builder object
//     LambdaNS-   non-negative value:
//                 * positive value means that some smoothing is applied
//                 * zero value means  that  no  smoothing  is  applied,  and
//                   corresponding entries of design matrix  are  numerically
//                   zero and dropped from consideration.
// ALGLIB: Copyright 05.02.2018 by Sergey Bochkanov
void spline2dbuildersetalgoblocklls(const spline2dbuilder &state, const double lambdans);

// This  function  allows  you to choose least squares solver used to perform
// fitting. This function sets solver algorithm to "NaiveLLS".
//
// IMPORTANT: NaiveLLS is NOT intended to be used in  real  life  code!  This
//            algorithm solves problem by generated dense (K^2)x(K^2+NPoints)
//            matrix and solves  linear  least  squares  problem  with  dense
//            solver.
//
//            It is here just  to  test  BlockLLS  against  reference  solver
//            (and maybe for someone trying to compare well optimized  solver
//            against straightforward approach to the LLS problem).
//
// More information on naive LLS solver:
// * memory requirements: ~[8*K^4+256*NPoints] bytes for KxK grid.
// * serial running time: O(K^6+NPoints) for KxK grid
// * when compared with BlockLLS,  NaiveLLS  has ~K  larger memory demand and
//   ~K^2  larger running time.
//
// Inputs:
//     S       -   spline 2D builder object
//     LambdaNS-   nonsmoothness penalty
// ALGLIB: Copyright 05.02.2018 by Sergey Bochkanov
void spline2dbuildersetalgonaivells(const spline2dbuilder &state, const double lambdans);

// This function fits bicubic spline to current dataset, using current  area/
// grid and current LLS solver.
//
// Inputs:
//     State   -   spline 2D builder object
//
// Outputs:
//     S       -   2D spline, fit result
//     Rep     -   fitting report, which provides some additional info  about
//                 errors, R2 coefficient and so on.
// ALGLIB: Copyright 05.02.2018 by Sergey Bochkanov
void spline2dfit(const spline2dbuilder &state, spline2dinterpolant &s, spline2dfitreport &rep);
} // end of namespace alglib

// === RBFV1 Package ===
// Depends on: (AlgLibMisc) NEARESTNEIGHBOR
// Depends on: LSFIT
namespace alglib_impl {
struct rbfv1calcbuffer {
   ae_vector calcbufxcx;
   ae_matrix calcbufx;
   ae_vector calcbuftags;
   kdtreerequestbuffer requestbuffer;
};
void rbfv1calcbuffer_init(void *_p, bool make_automatic);
void rbfv1calcbuffer_copy(void *_dst, void *_src, bool make_automatic);
void rbfv1calcbuffer_free(void *_p, bool make_automatic);

struct rbfv1model {
   ae_int_t ny;
   ae_int_t nx;
   ae_int_t nc;
   ae_int_t nl;
   kdtree tree;
   ae_matrix xc;
   ae_matrix wr;
   double rmax;
   ae_matrix v;
   ae_vector calcbufxcx;
   ae_matrix calcbufx;
   ae_vector calcbuftags;
};
void rbfv1model_init(void *_p, bool make_automatic);
void rbfv1model_copy(void *_dst, void *_src, bool make_automatic);
void rbfv1model_free(void *_p, bool make_automatic);

struct gridcalc3v1buf {
   ae_vector tx;
   ae_vector cx;
   ae_vector ty;
   ae_vector flag0;
   ae_vector flag1;
   ae_vector flag2;
   ae_vector flag12;
   ae_vector expbuf0;
   ae_vector expbuf1;
   ae_vector expbuf2;
   kdtreerequestbuffer requestbuf;
   ae_matrix calcbufx;
   ae_vector calcbuftags;
};
void gridcalc3v1buf_init(void *_p, bool make_automatic);
void gridcalc3v1buf_copy(void *_dst, void *_src, bool make_automatic);
void gridcalc3v1buf_free(void *_p, bool make_automatic);

struct rbfv1report {
   ae_int_t arows;
   ae_int_t acols;
   ae_int_t annz;
   ae_int_t iterationscount;
   ae_int_t nmv;
   ae_int_t terminationtype;
};
void rbfv1report_init(void *_p, bool make_automatic);
void rbfv1report_copy(void *_dst, void *_src, bool make_automatic);
void rbfv1report_free(void *_p, bool make_automatic);
void rbfv1alloc(ae_serializer *s, rbfv1model *model);
void rbfv1serialize(ae_serializer *s, rbfv1model *model);
void rbfv1unserialize(ae_serializer *s, rbfv1model *model);

void rbfv1create(ae_int_t nx, ae_int_t ny, rbfv1model *s);
void rbfv1createcalcbuffer(rbfv1model *s, rbfv1calcbuffer *buf);
void rbfv1buildmodel(RMatrix *x, RMatrix *y, ae_int_t n, ae_int_t aterm, ae_int_t algorithmtype, ae_int_t nlayers, double radvalue, double radzvalue, double lambdav, double epsort, double epserr, ae_int_t maxits, rbfv1model *s, rbfv1report *rep);
double rbfv1calc2(rbfv1model *s, double x0, double x1);
double rbfv1calc3(rbfv1model *s, double x0, double x1, double x2);
void rbfv1calcbuf(rbfv1model *s, RVector *x, RVector *y);
void rbfv1tscalcbuf(rbfv1model *s, rbfv1calcbuffer *buf, RVector *x, RVector *y);
void rbfv1gridcalc2(rbfv1model *s, RVector *x0, ae_int_t n0, RVector *x1, ae_int_t n1, RMatrix *y);
void rbfv1gridcalc3vrec(rbfv1model *s, RVector *x0, ae_int_t n0, RVector *x1, ae_int_t n1, RVector *x2, ae_int_t n2, ZVector *blocks0, ae_int_t block0a, ae_int_t block0b, ZVector *blocks1, ae_int_t block1a, ae_int_t block1b, ZVector *blocks2, ae_int_t block2a, ae_int_t block2b, BVector *flagy, bool sparsey, double searchradius, double avgfuncpernode, ae_shared_pool *bufpool, RVector *y);
void rbfv1unpack(rbfv1model *s, ae_int_t *nx, ae_int_t *ny, RMatrix *xwr, ae_int_t *nc, RMatrix *v);
} // end of namespace alglib_impl

// === RBF Package ===
// Depends on: RBFV2, RBFV1
namespace alglib_impl {
struct rbfcalcbuffer {
   ae_int_t modelversion;
   rbfv1calcbuffer bufv1;
   rbfv2calcbuffer bufv2;
};
void rbfcalcbuffer_init(void *_p, bool make_automatic);
void rbfcalcbuffer_copy(void *_dst, void *_src, bool make_automatic);
void rbfcalcbuffer_free(void *_p, bool make_automatic);

struct rbfmodel {
   ae_int_t nx;
   ae_int_t ny;
   ae_int_t modelversion;
   rbfv1model model1;
   rbfv2model model2;
   double lambdav;
   double radvalue;
   double radzvalue;
   ae_int_t nlayers;
   ae_int_t aterm;
   ae_int_t algorithmtype;
   double epsort;
   double epserr;
   ae_int_t maxits;
   ae_int_t nnmaxits;
   ae_int_t n;
   ae_matrix x;
   ae_matrix y;
   bool hasscale;
   ae_vector s;
   ae_int_t progress10000;
   bool terminationrequest;
};
void rbfmodel_init(void *_p, bool make_automatic);
void rbfmodel_copy(void *_dst, void *_src, bool make_automatic);
void rbfmodel_free(void *_p, bool make_automatic);

struct rbfreport {
   double rmserror;
   double maxerror;
   ae_int_t arows;
   ae_int_t acols;
   ae_int_t annz;
   ae_int_t iterationscount;
   ae_int_t nmv;
   ae_int_t terminationtype;
};
void rbfreport_init(void *_p, bool make_automatic);
void rbfreport_copy(void *_dst, void *_src, bool make_automatic);
void rbfreport_free(void *_p, bool make_automatic);
void rbfalloc(ae_serializer *s, rbfmodel *model);
void rbfserialize(ae_serializer *s, rbfmodel *model);
void rbfunserialize(ae_serializer *s, rbfmodel *model);

void rbfcreate(ae_int_t nx, ae_int_t ny, rbfmodel *s);
void rbfcreatecalcbuffer(rbfmodel *s, rbfcalcbuffer *buf);
void rbfsetpoints(rbfmodel *s, RMatrix *xy, ae_int_t n);
void rbfsetpointsandscales(rbfmodel *r, RMatrix *xy, ae_int_t n, RVector *s);
void rbfsetalgoqnn(rbfmodel *s, double q, double z);
void rbfsetalgomultilayer(rbfmodel *s, double rbase, ae_int_t nlayers, double lambdav);
void rbfsetalgohierarchical(rbfmodel *s, double rbase, ae_int_t nlayers, double lambdans);
void rbfsetlinterm(rbfmodel *s);
void rbfsetconstterm(rbfmodel *s);
void rbfsetzeroterm(rbfmodel *s);
void rbfsetv2bf(rbfmodel *s, ae_int_t bf);
void rbfsetv2its(rbfmodel *s, ae_int_t maxits);
void rbfsetv2supportr(rbfmodel *s, double r);
void rbfsetcond(rbfmodel *s, double epsort, double epserr, ae_int_t maxits);
void rbfbuildmodel(rbfmodel *s, rbfreport *rep);
double rbfcalc1(rbfmodel *s, double x0);
double rbfcalc2(rbfmodel *s, double x0, double x1);
double rbfcalc3(rbfmodel *s, double x0, double x1, double x2);
void rbfcalc(rbfmodel *s, RVector *x, RVector *y);
void rbfcalcbuf(rbfmodel *s, RVector *x, RVector *y);
void rbftscalcbuf(rbfmodel *s, rbfcalcbuffer *buf, RVector *x, RVector *y);
void rbfgridcalc2(rbfmodel *s, RVector *x0, ae_int_t n0, RVector *x1, ae_int_t n1, RMatrix *y);
void rbfgridcalc2v(rbfmodel *s, RVector *x0, ae_int_t n0, RVector *x1, ae_int_t n1, RVector *y);
void rbfgridcalc2vsubset(rbfmodel *s, RVector *x0, ae_int_t n0, RVector *x1, ae_int_t n1, BVector *flagy, RVector *y);
void rbfgridcalc3v(rbfmodel *s, RVector *x0, ae_int_t n0, RVector *x1, ae_int_t n1, RVector *x2, ae_int_t n2, RVector *y);
void rbfgridcalc3vsubset(rbfmodel *s, RVector *x0, ae_int_t n0, RVector *x1, ae_int_t n1, RVector *x2, ae_int_t n2, BVector *flagy, RVector *y);
void rbfgridcalc2vx(rbfmodel *s, RVector *x0, ae_int_t n0, RVector *x1, ae_int_t n1, BVector *flagy, bool sparsey, RVector *y);
void rbfgridcalc3vx(rbfmodel *s, RVector *x0, ae_int_t n0, RVector *x1, ae_int_t n1, RVector *x2, ae_int_t n2, BVector *flagy, bool sparsey, RVector *y);
void rbfunpack(rbfmodel *s, ae_int_t *nx, ae_int_t *ny, RMatrix *xwr, ae_int_t *nc, RMatrix *v, ae_int_t *modelversion);
ae_int_t rbfgetmodelversion(rbfmodel *s);
double rbfpeekprogress(rbfmodel *s);
void rbfrequesttermination(rbfmodel *s);
} // end of namespace alglib_impl

namespace alglib {
// Buffer object which is used to perform nearest neighbor  requests  in  the
// multithreaded mode (multiple threads working with same KD-tree object).
//
// This object should be created with KDTreeCreateBuffer().
DecClass(rbfcalcbuffer, EndD);

// RBF model.
//
// Never try to directly work with fields of this object - always use  ALGLIB
// functions to use this object.
DecClass(rbfmodel, EndD);

// RBF solution report:
// * TerminationType   -   termination type, positive values - success,
//                         non-positive - failure.
//
// Fields which are set by modern RBF solvers (hierarchical):
// * RMSError          -   root-mean-square error; NAN for old solvers (ML, QNN)
// * MaxError          -   maximum error; NAN for old solvers (ML, QNN)
DecClass(rbfreport, double &rmserror; double &maxerror; ae_int_t &arows; ae_int_t &acols; ae_int_t &annz; ae_int_t &iterationscount; ae_int_t &nmv; ae_int_t &terminationtype;);

// These functions serialize a data structure to a C++ string or stream.
// * serialization can be freely moved across 32-bit and 64-bit systems,
//   and different byte orders. For example, you can serialize a string
//   on a SPARC and unserialize it on an x86.
// * ALGLIB++ serialization is compatible with serialization in ALGLIB,
//   in both directions.
// Important properties of s_out:
// * it contains alphanumeric characters, dots, underscores, minus signs
// * these symbols are grouped into words, which are separated by spaces
//   and Windows-style (CR+LF) newlines
void rbfserialize(rbfmodel &obj, std::string &s_out);
void rbfserialize(rbfmodel &obj, std::ostream &s_out);

// These functions unserialize a data structure from a C++ string or stream.
// Important properties of s_in:
// * any combination of spaces, tabs, Windows or Unix stype newlines can
//   be used as separators, so as to allow flexible reformatting of the
//   stream or string from text or XML files.
// * But you should not insert separators into the middle of the "words"
//   nor you should change case of letters.
void rbfunserialize(const std::string &s_in, rbfmodel &obj);
void rbfunserialize(const std::istream &s_in, rbfmodel &obj);

// This function creates RBF  model  for  a  scalar (NY=1)  or  vector (NY > 1)
// function in a NX-dimensional space (NX >= 1).
//
// Newly created model is empty. It can be used for interpolation right after
// creation, but it just returns zeros. You have to add points to the  model,
// tune interpolation settings, and then  call  model  construction  function
// rbfbuildmodel() which will update model according to your specification.
//
// USAGE:
// 1. User creates model with rbfcreate()
// 2. User adds dataset with rbfsetpoints() (points do NOT have to  be  on  a
//    regular grid) or rbfsetpointsandscales().
// 3. (OPTIONAL) User chooses polynomial term by calling:
//    * rbflinterm() to set linear term
//    * rbfconstterm() to set constant term
//    * rbfzeroterm() to set zero term
//    By default, linear term is used.
// 4. User tweaks algorithm properties with  rbfsetalgohierarchical()  method
//    (or chooses one of the legacy algorithms - QNN  (rbfsetalgoqnn)  or  ML
//    (rbfsetalgomultilayer)).
// 5. User calls rbfbuildmodel() function which rebuilds model  according  to
//    the specification
// 6. User may call rbfcalc() to calculate model value at the specified point,
//    rbfgridcalc() to  calculate   model  values at the points of the regular
//    grid. User may extract model coefficients with rbfunpack() call.
//
// IMPORTANT: we recommend you to use latest model construction  algorithm  -
//            hierarchical RBFs, which is activated by rbfsetalgohierarchical()
//            function. This algorithm is the fastest one, and  most  memory-
//            efficient.
//            However,  it  is  incompatible  with older versions  of  ALGLIB
//            (pre-3.11). So, if you serialize hierarchical model,  you  will
//            be unable to load it in pre-3.11 ALGLIB. Other model types (QNN
//            and RBF-ML) are still backward-compatible.
//
// Inputs:
//     NX      -   dimension of the space, NX >= 1
//     NY      -   function dimension, NY >= 1
//
// Outputs:
//     S       -   RBF model (initially equals to zero)
//
// NOTE 1: memory requirements. RBF models require amount of memory  which is
//         proportional  to the number of data points. Some additional memory
//         is allocated during model construction, but most of this memory is
//         freed after model coefficients  are  calculated.  Amount  of  this
//         additional memory depends on model  construction  algorithm  being
//         used.
//
// NOTE 2: prior to ALGLIB version 3.11, RBF models supported  only  NX=2  or
//         NX=3. Any  attempt  to  create  single-dimensional  or  more  than
//         3-dimensional RBF model resulted in exception.
//
//         ALGLIB 3.11 supports any NX > 0, but models created with  NX != 2  and
//         NX != 3 are incompatible with (a) older versions of ALGLIB, (b)  old
//         model construction algorithms (QNN or RBF-ML).
//
//         So, if you create a model with NX=2 or NX=3,  then,  depending  on
//         specific  model construction algorithm being chosen, you will (QNN
//         and RBF-ML) or will not (HierarchicalRBF) get backward compatibility
//         with older versions of ALGLIB. You have a choice here.
//
//         However, if you create a model with NX neither 2 nor 3,  you  have
//         no backward compatibility from the start, and you  are  forced  to
//         use hierarchical RBFs and ALGLIB 3.11 or later.
// ALGLIB: Copyright 13.12.2011, 20.06.2016 by Sergey Bochkanov
void rbfcreate(const ae_int_t nx, const ae_int_t ny, rbfmodel &s);

// This function creates buffer  structure  which  can  be  used  to  perform
// parallel  RBF  model  evaluations  (with  one  RBF  model  instance  being
// used from multiple threads, as long as  different  threads  use  different
// instances of buffer).
//
// This buffer object can be used with  rbftscalcbuf()  function  (here  "ts"
// stands for "thread-safe", "buf" is a suffix which denotes  function  which
// reuses previously allocated output space).
//
// How to use it:
// * create RBF model structure with rbfcreate()
// * load data, tune parameters
// * call rbfbuildmodel()
// * call rbfcreatecalcbuffer(), once per thread working with RBF model  (you
//   should call this function only AFTER call to rbfbuildmodel(), see  below
//   for more information)
// * call rbftscalcbuf() from different threads,  with  each  thread  working
//   with its own copy of buffer object.
//
// Inputs:
//     S           -   RBF model
//
// Outputs:
//     Buf         -   external buffer.
//
//
// IMPORTANT: buffer object should be used only with  RBF model object  which
//            was used to initialize buffer. Any attempt to use buffer   with
//            different object is dangerous - you may  get  memory  violation
//            error because sizes of internal arrays do not fit to dimensions
//            of RBF structure.
//
// IMPORTANT: you  should  call  this function only for model which was built
//            with rbfbuildmodel() function, after successful  invocation  of
//            rbfbuildmodel().  Sizes   of   some   internal  structures  are
//            determined only after model is built, so buffer object  created
//            before model  construction  stage  will  be  useless  (and  any
//            attempt to use it will result in exception).
// ALGLIB: Copyright 02.04.2016 by Sergey Bochkanov
void rbfcreatecalcbuffer(const rbfmodel &s, rbfcalcbuffer &buf);

// This function adds dataset.
//
// This function overrides results of the previous calls, i.e. multiple calls
// of this function will result in only the last set being added.
//
// IMPORTANT: ALGLIB version 3.11 and later allows you to specify  a  set  of
//            per-dimension scales. Interpolation radii are multiplied by the
//            scale vector. It may be useful if you have mixed spatio-temporal
//            data (say, a set of 3D slices recorded at different times).
//            You should call rbfsetpointsandscales() function  to  use  this
//            feature.
//
// Inputs:
//     S       -   RBF model, initialized by rbfcreate() call.
//     XY      -   points, array[N,NX+NY]. One row corresponds to  one  point
//                 in the dataset. First NX elements  are  coordinates,  next
//                 NY elements are function values. Array may  be larger than
//                 specified, in  this  case  only leading [N,NX+NY] elements
//                 will be used.
//     N       -   number of points in the dataset
//
// After you've added dataset and (optionally) tuned algorithm  settings  you
// should call rbfbuildmodel() in order to build a model for you.
//
// NOTE: dataset added by this function is not saved during model serialization.
//       MODEL ITSELF is serialized, but data used to build it are not.
//
//       So, if you 1) add dataset to  empty  RBF  model,  2)  serialize  and
//       unserialize it, then you will get an empty RBF model with no dataset
//       being attached.
//
//       From the other side, if you call rbfbuildmodel() between (1) and (2),
//       then after (2) you will get your fully constructed RBF model  -  but
//       again with no dataset attached, so subsequent calls to rbfbuildmodel()
//       will produce empty model.
//
// ALGLIB: Copyright 13.12.2011 by Sergey Bochkanov
void rbfsetpoints(const rbfmodel &s, const real_2d_array &xy, const ae_int_t n);
void rbfsetpoints(const rbfmodel &s, const real_2d_array &xy);

// This function adds dataset and a vector of per-dimension scales.
//
// It may be useful if you have mixed spatio-temporal data - say, a set of 3D
// slices recorded at different times. Such data typically require  different
// RBF radii for spatial and temporal dimensions. ALGLIB solves this  problem
// by specifying single RBF radius, which is (optionally) multiplied  by  the
// scale vector.
//
// This function overrides results of the previous calls, i.e. multiple calls
// of this function will result in only the last set being added.
//
// IMPORTANT: only HierarchicalRBF algorithm can work with scaled points. So,
//            using this function results in RBF models which can be used  in
//            ALGLIB 3.11 or later. Previous versions of the library will  be
//            unable  to unserialize models produced by HierarchicalRBF algo.
//
//            Any attempt to use this function with RBF-ML or QNN  algorithms
//            will result  in  -3  error  code   being   returned  (incorrect
//            algorithm).
//
// Inputs:
//     R       -   RBF model, initialized by rbfcreate() call.
//     XY      -   points, array[N,NX+NY]. One row corresponds to  one  point
//                 in the dataset. First NX elements  are  coordinates,  next
//                 NY elements are function values. Array may  be larger than
//                 specified, in  this  case  only leading [N,NX+NY] elements
//                 will be used.
//     N       -   number of points in the dataset
//     S       -   array[NX], scale vector, S[i] > 0.
//
// After you've added dataset and (optionally) tuned algorithm  settings  you
// should call rbfbuildmodel() in order to build a model for you.
//
// NOTE: dataset added by this function is not saved during model serialization.
//       MODEL ITSELF is serialized, but data used to build it are not.
//
//       So, if you 1) add dataset to  empty  RBF  model,  2)  serialize  and
//       unserialize it, then you will get an empty RBF model with no dataset
//       being attached.
//
//       From the other side, if you call rbfbuildmodel() between (1) and (2),
//       then after (2) you will get your fully constructed RBF model  -  but
//       again with no dataset attached, so subsequent calls to rbfbuildmodel()
//       will produce empty model.
//
// ALGLIB: Copyright 20.06.2016 by Sergey Bochkanov
void rbfsetpointsandscales(const rbfmodel &r, const real_2d_array &xy, const ae_int_t n, const real_1d_array &s);
void rbfsetpointsandscales(const rbfmodel &r, const real_2d_array &xy, const real_1d_array &s);

// DEPRECATED:since version 3.11 ALGLIB includes new RBF  model  construction
//            algorithm, Hierarchical  RBF.  This  algorithm  is  faster  and
//            requires less memory than QNN and RBF-ML. It is especially good
//            for large-scale interpolation problems. So, we recommend you to
//            consider Hierarchical RBF as default option.
//
// This  function  sets  RBF interpolation algorithm. ALGLIB supports several
// RBF algorithms with different properties.
//
// This algorithm is called RBF-QNN and  it  is  good  for  point  sets  with
// following properties:
// a) all points are distinct
// b) all points are well separated.
// c) points  distribution  is  approximately  uniform.  There is no "contour
//    lines", clusters of points, or other small-scale structures.
//
// Algorithm description:
// 1) interpolation centers are allocated to data points
// 2) interpolation radii are calculated as distances to the  nearest centers
//    times Q coefficient (where Q is a value from [0.75,1.50]).
// 3) after  performing (2) radii are transformed in order to avoid situation
//    when single outlier has very large radius and  influences  many  points
//    across all dataset. Transformation has following form:
//        new_r[i] = min(r[i],Z*median(r[]))
//    where r[i] is I-th radius, median()  is a median  radius across  entire
//    dataset, Z is user-specified value which controls amount  of  deviation
//    from median radius.
//
// When (a) is violated,  we  will  be unable to build RBF model. When (b) or
// (c) are violated, model will be built, but interpolation quality  will  be
// low. See http://www.alglib.net/interpolation/ for more information on this
// subject.
//
// This algorithm is used by default.
//
// Additional Q parameter controls smoothness properties of the RBF basis:
// * Q < 0.75 will give perfectly conditioned basis,  but  terrible  smoothness
//   properties (RBF interpolant will have sharp peaks around function values)
// * Q around 1.0 gives good balance between smoothness and condition number
// * Q > 1.5 will lead to badly conditioned systems and slow convergence of the
//   underlying linear solver (although smoothness will be very good)
// * Q > 2.0 will effectively make optimizer useless because it won't  converge
//   within reasonable amount of iterations. It is possible to set such large
//   Q, but it is advised not to do so.
//
// Inputs:
//     S       -   RBF model, initialized by RBFCreate() call
//     Q       -   Q parameter, Q > 0, recommended value - 1.0
//     Z       -   Z parameter, Z > 0, recommended value - 5.0
//
// NOTE: this   function  has   some   serialization-related  subtleties.  We
//       recommend you to study serialization examples from ALGLIB  Reference
//       Manual if you want to perform serialization of your models.
//
// ALGLIB: Copyright 13.12.2011 by Sergey Bochkanov
void rbfsetalgoqnn(const rbfmodel &s, const double q, const double z);
void rbfsetalgoqnn(const rbfmodel &s);

// DEPRECATED:since version 3.11 ALGLIB includes new RBF  model  construction
//            algorithm, Hierarchical  RBF.  This  algorithm  is  faster  and
//            requires less memory than QNN and RBF-ML. It is especially good
//            for large-scale interpolation problems. So, we recommend you to
//            consider Hierarchical RBF as default option.
//
// This  function  sets  RBF interpolation algorithm. ALGLIB supports several
// RBF algorithms with different properties.
//
// This  algorithm is called RBF-ML. It builds  multilayer  RBF  model,  i.e.
// model with subsequently decreasing  radii,  which  allows  us  to  combine
// smoothness (due to  large radii of  the first layers) with  exactness (due
// to small radii of the last layers) and fast convergence.
//
// Internally RBF-ML uses many different  means  of acceleration, from sparse
// matrices  to  KD-trees,  which  results in algorithm whose working time is
// roughly proportional to N*log(N)*Density*RBase^2*NLayers,  where  N  is  a
// number of points, Density is an average density if points per unit of  the
// interpolation space, RBase is an initial radius, NLayers is  a  number  of
// layers.
//
// RBF-ML is good for following kinds of interpolation problems:
// 1. "exact" problems (perfect fit) with well separated points
// 2. least squares problems with arbitrary distribution of points (algorithm
//    gives  perfect  fit  where it is possible, and resorts to least squares
//    fit in the hard areas).
// 3. noisy problems where  we  want  to  apply  some  controlled  amount  of
//    smoothing.
//
// Inputs:
//     S       -   RBF model, initialized by RBFCreate() call
//     RBase   -   RBase parameter, RBase > 0
//     NLayers -   NLayers parameter, NLayers > 0, recommended value  to  start
//                 with - about 5.
//     LambdaV -   regularization value, can be useful when  solving  problem
//                 in the least squares sense.  Optimal  lambda  is  problem-
//                 dependent and require trial and error. In our  experience,
//                 good lambda can be as large as 0.1, and you can use  0.001
//                 as initial guess.
//                 Default  value  - 0.01, which is used when LambdaV is  not
//                 given.  You  can  specify  zero  value,  but  it  is   not
//                 recommended to do so.
//
// TUNING ALGORITHM
//
// In order to use this algorithm you have to choose three parameters:
// * initial radius RBase
// * number of layers in the model NLayers
// * regularization coefficient LambdaV
//
// Initial radius is easy to choose - you can pick any number  several  times
// larger  than  the  average  distance between points. Algorithm won't break
// down if you choose radius which is too large (model construction time will
// increase, but model will be built correctly).
//
// Choose such number of layers that RLast=RBase/2^(NLayers-1)  (radius  used
// by  the  last  layer)  will  be  smaller than the typical distance between
// points.  In  case  model  error  is  too large, you can increase number of
// layers.  Having  more  layers  will make model construction and evaluation
// proportionally slower, but it will allow you to have model which precisely
// fits your data. From the other side, if you want to  suppress  noise,  you
// can DECREASE number of layers to make your model less flexible.
//
// Regularization coefficient LambdaV controls smoothness of  the  individual
// models built for each layer. We recommend you to use default value in case
// you don't want to tune this parameter,  because  having  non-zero  LambdaV
// accelerates and stabilizes internal iterative algorithm. In case you  want
// to suppress noise you can use  LambdaV  as  additional  parameter  (larger
// value = more smoothness) to tune.
//
// TYPICAL ERRORS
//
// 1. Using  initial  radius  which is too large. Memory requirements  of the
//    RBF-ML are roughly proportional to N*Density*RBase^2 (where Density  is
//    an average density of points per unit of the interpolation  space).  In
//    the extreme case of the very large RBase we will need O(N^2)  units  of
//    memory - and many layers in order to decrease radius to some reasonably
//    small value.
//
// 2. Using too small number of layers - RBF models with large radius are not
//    flexible enough to reproduce small variations in the  target  function.
//    You  need  many  layers  with  different radii, from large to small, in
//    order to have good model.
//
// 3. Using  initial  radius  which  is  too  small.  You will get model with
//    "holes" in the areas which are too far away from interpolation centers.
//    However, algorithm will work correctly (and quickly) in this case.
//
// 4. Using too many layers - you will get too large and too slow model. This
//    model  will  perfectly  reproduce  your function, but maybe you will be
//    able to achieve similar results with less layers (and less memory).
// ALGLIB: Copyright 02.03.2012 by Sergey Bochkanov
void rbfsetalgomultilayer(const rbfmodel &s, const double rbase, const ae_int_t nlayers, const double lambdav);
void rbfsetalgomultilayer(const rbfmodel &s, const double rbase, const ae_int_t nlayers);

// This  function  sets  RBF interpolation algorithm. ALGLIB supports several
// RBF algorithms with different properties.
//
// This  algorithm is called Hierarchical RBF. It  similar  to  its  previous
// incarnation, RBF-ML, i.e.  it  also  builds  a  sequence  of  models  with
// decreasing radii. However, it uses more economical way of  building  upper
// layers (ones with large radii), which results in faster model construction
// and evaluation, as well as smaller memory footprint during construction.
//
// This algorithm has following important features:
// * ability to handle millions of points
// * controllable smoothing via nonlinearity penalization
// * support for NX-dimensional models with NX=1 or NX > 3 (unlike QNN or RBF-ML)
// * support for specification of per-dimensional  radii  via  scale  vector,
//   which is set by means of rbfsetpointsandscales() function. This  feature
//   is useful if you solve  spatio-temporal  interpolation  problems,  where
//   different radii are required for spatial and temporal dimensions.
//
// Running times are roughly proportional to:
// * N*log(N)*NLayers - for model construction
// * N*NLayers - for model evaluation
// You may see that running time does not depend on search radius  or  points
// density, just on number of layers in the hierarchy.
//
// IMPORTANT: this model construction algorithm was introduced in ALGLIB 3.11
//            and  produces  models  which  are  INCOMPATIBLE  with  previous
//            versions of ALGLIB. You can  not  unserialize  models  produced
//            with this function in ALGLIB 3.10 or earlier.
//
// Inputs:
//     S       -   RBF model, initialized by rbfcreate() call
//     RBase   -   RBase parameter, RBase > 0
//     NLayers -   NLayers parameter, NLayers > 0, recommended value  to  start
//                 with - about 5.
//     LambdaNS- >= 0, nonlinearity penalty coefficient, negative values are
//                 not allowed. This parameter adds controllable smoothing to
//                 the problem, which may reduce noise. Specification of non-
//                 zero lambda means that in addition to fitting error solver
//                 will  also  minimize   LambdaNS*|S''(x)|^2  (appropriately
//                 generalized to multiple dimensions.
//
//                 Specification of exactly zero value means that no  penalty
//                 is added  (we  do  not  even  evaluate  matrix  of  second
//                 derivatives which is necessary for smoothing).
//
//                 Calculation of nonlinearity penalty is costly - it results
//                 in  several-fold  increase  of  model  construction  time.
//                 Evaluation time remains the same.
//
//                 Optimal  lambda  is  problem-dependent and requires  trial
//                 and  error.  Good  value to  start  from  is  1e-5...1e-6,
//                 which corresponds to slightly noticeable smoothing  of the
//                 function.  Value  1e-2  usually  means  that  quite  heavy
//                 smoothing is applied.
//
// TUNING ALGORITHM
//
// In order to use this algorithm you have to choose three parameters:
// * initial radius RBase
// * number of layers in the model NLayers
// * penalty coefficient LambdaNS
//
// Initial radius is easy to choose - you can pick any number  several  times
// larger  than  the  average  distance between points. Algorithm won't break
// down if you choose radius which is too large (model construction time will
// increase, but model will be built correctly).
//
// Choose such number of layers that RLast=RBase/2^(NLayers-1)  (radius  used
// by  the  last  layer)  will  be  smaller than the typical distance between
// points.  In  case  model  error  is  too large, you can increase number of
// layers.  Having  more  layers  will make model construction and evaluation
// proportionally slower, but it will allow you to have model which precisely
// fits your data. From the other side, if you want to  suppress  noise,  you
// can DECREASE number of layers to make your model less flexible (or specify
// non-zero LambdaNS).
//
// TYPICAL ERRORS
//
// 1. Using too small number of layers - RBF models with large radius are not
//    flexible enough to reproduce small variations in the  target  function.
//    You  need  many  layers  with  different radii, from large to small, in
//    order to have good model.
//
// 2. Using  initial  radius  which  is  too  small.  You will get model with
//    "holes" in the areas which are too far away from interpolation centers.
//    However, algorithm will work correctly (and quickly) in this case.
// ALGLIB: Copyright 20.06.2016 by Sergey Bochkanov
void rbfsetalgohierarchical(const rbfmodel &s, const double rbase, const ae_int_t nlayers, const double lambdans);

// This function sets linear term (model is a sum of radial  basis  functions
// plus linear polynomial). This function won't have effect until  next  call
// to RBFBuildModel().
//
// Inputs:
//     S       -   RBF model, initialized by RBFCreate() call
//
// NOTE: this   function  has   some   serialization-related  subtleties.  We
//       recommend you to study serialization examples from ALGLIB  Reference
//       Manual if you want to perform serialization of your models.
// ALGLIB: Copyright 13.12.2011 by Sergey Bochkanov
void rbfsetlinterm(const rbfmodel &s);

// This function sets constant term (model is a sum of radial basis functions
// plus constant).  This  function  won't  have  effect  until  next  call to
// RBFBuildModel().
//
// Inputs:
//     S       -   RBF model, initialized by RBFCreate() call
//
// NOTE: this   function  has   some   serialization-related  subtleties.  We
//       recommend you to study serialization examples from ALGLIB  Reference
//       Manual if you want to perform serialization of your models.
// ALGLIB: Copyright 13.12.2011 by Sergey Bochkanov
void rbfsetconstterm(const rbfmodel &s);

// This  function  sets  zero  term (model is a sum of radial basis functions
// without polynomial term). This function won't have effect until next  call
// to RBFBuildModel().
//
// Inputs:
//     S       -   RBF model, initialized by RBFCreate() call
//
// NOTE: this   function  has   some   serialization-related  subtleties.  We
//       recommend you to study serialization examples from ALGLIB  Reference
//       Manual if you want to perform serialization of your models.
// ALGLIB: Copyright 13.12.2011 by Sergey Bochkanov
void rbfsetzeroterm(const rbfmodel &s);

// This function sets basis function type, which can be:
// * 0 for classic Gaussian
// * 1 for fast and compact bell-like basis function, which  becomes  exactly
//   zero at distance equal to 3*R (default option).
//
// Inputs:
//     S       -   RBF model, initialized by RBFCreate() call
//     BF      -   basis function type:
//                 * 0 - classic Gaussian
//                 * 1 - fast and compact one
// ALGLIB: Copyright 01.02.2017 by Sergey Bochkanov
void rbfsetv2bf(const rbfmodel &s, const ae_int_t bf);

// This function sets stopping criteria of the underlying linear  solver  for
// hierarchical (version 2) RBF constructor.
//
// Inputs:
//     S       -   RBF model, initialized by RBFCreate() call
//     MaxIts  -   this criterion will stop algorithm after MaxIts iterations.
//                 Typically a few hundreds iterations is required,  with 400
//                 being a good default value to start experimentation.
//                 Zero value means that default value will be selected.
// ALGLIB: Copyright 01.02.2017 by Sergey Bochkanov
void rbfsetv2its(const rbfmodel &s, const ae_int_t maxits);

// This function sets support radius parameter  of  hierarchical  (version 2)
// RBF constructor.
//
// Hierarchical RBF model achieves great speed-up  by removing from the model
// excessive (too dense) nodes. Say, if you have RBF radius equal to 1 meter,
// and two nodes are just 1 millimeter apart, you  may  remove  one  of  them
// without reducing model quality.
//
// Support radius parameter is used to justify which points need removal, and
// which do not. If two points are less than  SUPPORT_R*CUR_RADIUS  units  of
// distance apart, one of them is removed from the model. The larger  support
// radius  is, the faster model  construction  AND  evaluation are.  However,
// too large values result in "bumpy" models.
//
// Inputs:
//     S       -   RBF model, initialized by RBFCreate() call
//     R       -   support radius coefficient, >= 0.
//                 Recommended values are [0.1,0.4] range, with 0.1 being
//                 default value.
// ALGLIB: Copyright 01.02.2017 by Sergey Bochkanov
void rbfsetv2supportr(const rbfmodel &s, const double r);

// This   function  builds  RBF  model  and  returns  report  (contains  some
// information which can be used for evaluation of the algorithm properties).
//
// Call to this function modifies RBF model by calculating its centers/radii/
// weights  and  saving  them  into  RBFModel  structure.  Initially RBFModel
// contain zero coefficients, but after call to this function  we  will  have
// coefficients which were calculated in order to fit our dataset.
//
// After you called this function you can call RBFCalc(),  RBFGridCalc()  and
// other model calculation functions.
//
// Inputs:
//     S       -   RBF model, initialized by RBFCreate() call
//     Rep     -   report:
//                 * Rep.TerminationType:
//                   * -5 - non-distinct basis function centers were detected,
//                          interpolation  aborted;  only  QNN  returns  this
//                          error   code, other  algorithms  can  handle non-
//                          distinct nodes.
//                   * -4 - nonconvergence of the internal SVD solver
//                   * -3   incorrect model construction algorithm was chosen:
//                          QNN or RBF-ML, combined with one of the incompatible
//                          features - NX=1 or NX > 3; points with per-dimension
//                          scales.
//                   *  1 - successful termination
//                   *  8 - a termination request was submitted via
//                          rbfrequesttermination() function.
//
//                 Fields which are set only by modern RBF solvers (hierarchical
//                 or nonnegative; older solvers like QNN and ML initialize these
//                 fields by NANs):
//                 * rep.rmserror - root-mean-square error at nodes
//                 * rep.maxerror - maximum error at nodes
//
//                 Fields are used for debugging purposes:
//                 * Rep.IterationsCount - iterations count of the LSQR solver
//                 * Rep.NMV - number of matrix-vector products
//                 * Rep.ARows - rows count for the system matrix
//                 * Rep.ACols - columns count for the system matrix
//                 * Rep.ANNZ - number of significantly non-zero elements
//                   (elements above some algorithm-determined threshold)
//
// NOTE:  failure  to  build  model will leave current state of the structure
// unchanged.
// ALGLIB: Copyright 13.12.2011 by Sergey Bochkanov
void rbfbuildmodel(const rbfmodel &s, rbfreport &rep);

// This function calculates values of the RBF model in the given point.
//
// IMPORTANT: this function works only with modern  (hierarchical)  RBFs.  It
//            can not be used with legacy (version 1) RBFs because older  RBF
//            code does not support 1-dimensional models.
//
// This function should be used when we have NY=1 (scalar function) and  NX=1
// (1-dimensional space). If you have 3-dimensional space, use rbfcalc3(). If
// you  have  2-dimensional  space,  use  rbfcalc3().  If  you  have  general
// situation (NX-dimensional space, NY-dimensional function)  you  should use
// generic rbfcalc().
//
// If you want to perform parallel model evaluation  from  multiple  threads,
// use rbftscalcbuf() with per-thread buffer object.
//
// This function returns 0.0 when:
// * model is not initialized
// * NX != 1
// * NY != 1
//
// Inputs:
//     S       -   RBF model
//     X0      -   X-coordinate, finite number
//
// Result:
//     value of the model or 0.0 (as defined above)
// ALGLIB: Copyright 13.12.2011 by Sergey Bochkanov
double rbfcalc1(const rbfmodel &s, const double x0);

// This function calculates values of the RBF model in the given point.
//
// This function should be used when we have NY=1 (scalar function) and  NX=2
// (2-dimensional space). If you have 3-dimensional space, use rbfcalc3(). If
// you have general situation (NX-dimensional space, NY-dimensional function)
// you should use generic rbfcalc().
//
// If  you  want  to  calculate  function  values  many times, consider using
// rbfgridcalc2v(), which is far more efficient than many subsequent calls to
// rbfcalc2().
//
// If you want to perform parallel model evaluation  from  multiple  threads,
// use rbftscalcbuf() with per-thread buffer object.
//
// This function returns 0.0 when:
// * model is not initialized
// * NX != 2
//  *NY != 1
//
// Inputs:
//     S       -   RBF model
//     X0      -   first coordinate, finite number
//     X1      -   second coordinate, finite number
//
// Result:
//     value of the model or 0.0 (as defined above)
// ALGLIB: Copyright 13.12.2011 by Sergey Bochkanov
double rbfcalc2(const rbfmodel &s, const double x0, const double x1);

// This function calculates value of the RBF model in the given point.
//
// This function should be used when we have NY=1 (scalar function) and  NX=3
// (3-dimensional space). If you have 2-dimensional space, use rbfcalc2(). If
// you have general situation (NX-dimensional space, NY-dimensional function)
// you should use generic rbfcalc().
//
// If  you  want  to  calculate  function  values  many times, consider using
// rbfgridcalc3v(), which is far more efficient than many subsequent calls to
// rbfcalc3().
//
// If you want to perform parallel model evaluation  from  multiple  threads,
// use rbftscalcbuf() with per-thread buffer object.
//
// This function returns 0.0 when:
// * model is not initialized
// * NX != 3
//  *NY != 1
//
// Inputs:
//     S       -   RBF model
//     X0      -   first coordinate, finite number
//     X1      -   second coordinate, finite number
//     X2      -   third coordinate, finite number
//
// Result:
//     value of the model or 0.0 (as defined above)
// ALGLIB: Copyright 13.12.2011 by Sergey Bochkanov
double rbfcalc3(const rbfmodel &s, const double x0, const double x1, const double x2);

// This function calculates values of the RBF model at the given point.
//
// This is general function which can be used for arbitrary NX (dimension  of
// the space of arguments) and NY (dimension of the function itself). However
// when  you  have  NY=1  you  may  find more convenient to use rbfcalc2() or
// rbfcalc3().
//
// If you want to perform parallel model evaluation  from  multiple  threads,
// use rbftscalcbuf() with per-thread buffer object.
//
// This function returns 0.0 when model is not initialized.
//
// Inputs:
//     S       -   RBF model
//     X       -   coordinates, array[NX].
//                 X may have more than NX elements, in this case only
//                 leading NX will be used.
//
// Outputs:
//     Y       -   function value, array[NY]. Y is out-parameter and
//                 reallocated after call to this function. In case you  want
//                 to reuse previously allocated Y, you may use RBFCalcBuf(),
//                 which reallocates Y only when it is too small.
// ALGLIB: Copyright 13.12.2011 by Sergey Bochkanov
void rbfcalc(const rbfmodel &s, const real_1d_array &x, real_1d_array &y);

// This function calculates values of the RBF model at the given point.
//
// Same as rbfcalc(), but does not reallocate Y when in is large enough to
// store function values.
//
// If you want to perform parallel model evaluation  from  multiple  threads,
// use rbftscalcbuf() with per-thread buffer object.
//
// Inputs:
//     S       -   RBF model
//     X       -   coordinates, array[NX].
//                 X may have more than NX elements, in this case only
//                 leading NX will be used.
//     Y       -   possibly preallocated array
//
// Outputs:
//     Y       -   function value, array[NY]. Y is not reallocated when it
//                 is larger than NY.
// ALGLIB: Copyright 13.12.2011 by Sergey Bochkanov
void rbfcalcbuf(const rbfmodel &s, const real_1d_array &x, real_1d_array &y);

// This function calculates values of the RBF model at the given point, using
// external  buffer  object  (internal  temporaries  of  RBF  model  are  not
// modified).
//
// This function allows to use same RBF model object  in  different  threads,
// assuming  that  different   threads  use  different  instances  of  buffer
// structure.
//
// Inputs:
//     S       -   RBF model, may be shared between different threads
//     Buf     -   buffer object created for this particular instance of  RBF
//                 model with rbfcreatecalcbuffer().
//     X       -   coordinates, array[NX].
//                 X may have more than NX elements, in this case only
//                 leading NX will be used.
//     Y       -   possibly preallocated array
//
// Outputs:
//     Y       -   function value, array[NY]. Y is not reallocated when it
//                 is larger than NY.
// ALGLIB: Copyright 13.12.2011 by Sergey Bochkanov
void rbftscalcbuf(const rbfmodel &s, const rbfcalcbuffer &buf, const real_1d_array &x, real_1d_array &y);

// This is legacy function for gridded calculation of RBF model.
//
// It is superseded by rbfgridcalc2v() and  rbfgridcalc2vsubset()  functions.
// ALGLIB: Copyright 13.12.2011 by Sergey Bochkanov
void rbfgridcalc2(const rbfmodel &s, const real_1d_array &x0, const ae_int_t n0, const real_1d_array &x1, const ae_int_t n1, real_2d_array &y);

// This function calculates values of the RBF  model  at  the  regular  grid,
// which  has  N0*N1 points, with Point[I,J] = (X0[I], X1[J]).  Vector-valued
// RBF models are supported.
//
// This function returns 0.0 when:
// * model is not initialized
// * NX != 2
//
// NOTE: Parallel  processing  is  implemented only for modern (hierarchical)
//       RBFs. Legacy version 1 RBFs (created  by  QNN  or  RBF-ML) are still
//       processed serially.
//
// Inputs:
//     S       -   RBF model, used in read-only mode, can be  shared  between
//                 multiple   invocations  of  this  function  from  multiple
//                 threads.
//
//     X0      -   array of grid nodes, first coordinates, array[N0].
//                 Must be ordered by ascending. Exception is generated
//                 if the array is not correctly ordered.
//     N0      -   grid size (number of nodes) in the first dimension
//
//     X1      -   array of grid nodes, second coordinates, array[N1]
//                 Must be ordered by ascending. Exception is generated
//                 if the array is not correctly ordered.
//     N1      -   grid size (number of nodes) in the second dimension
//
// Outputs:
//     Y       -   function values, array[NY*N0*N1], where NY is a  number of
//                 "output" vector values (this  function   supports  vector-
//                 valued RBF models). Y is out-variable and  is  reallocated
//                 by this function.
//                 Y[K+NY*(I0+I1*N0)]=F_k(X0[I0],X1[I1]), for:
//                 *  K=0...NY-1
//                 * I0=0...N0-1
//                 * I1=0...N1-1
//
// NOTE: this function supports weakly ordered grid nodes, i.e. you may  have
//       X[i]=X[i+1] for some i. It does  not  provide  you  any  performance
//       benefits  due  to   duplication  of  points,  just  convenience  and
//       flexibility.
//
// NOTE: this  function  is  re-entrant,  i.e.  you  may  use  same  rbfmodel
//       structure in multiple threads calling  this function  for  different
//       grids.
//
// NOTE: if you need function values on some subset  of  regular  grid, which
//       may be described as "several compact and  dense  islands",  you  may
//       use rbfgridcalc2vsubset().
// ALGLIB: Copyright 27.01.2017 by Sergey Bochkanov
void rbfgridcalc2v(const rbfmodel &s, const real_1d_array &x0, const ae_int_t n0, const real_1d_array &x1, const ae_int_t n1, real_1d_array &y);

// This function calculates values of the RBF model at some subset of regular
// grid:
// * grid has N0*N1 points, with Point[I,J] = (X0[I], X1[J])
// * only values at some subset of this grid are required
// Vector-valued RBF models are supported.
//
// This function returns 0.0 when:
// * model is not initialized
// * NX != 2
//
// NOTE: Parallel  processing  is  implemented only for modern (hierarchical)
//       RBFs. Legacy version 1 RBFs (created  by  QNN  or  RBF-ML) are still
//       processed serially.
//
// Inputs:
//     S       -   RBF model, used in read-only mode, can be  shared  between
//                 multiple   invocations  of  this  function  from  multiple
//                 threads.
//
//     X0      -   array of grid nodes, first coordinates, array[N0].
//                 Must be ordered by ascending. Exception is generated
//                 if the array is not correctly ordered.
//     N0      -   grid size (number of nodes) in the first dimension
//
//     X1      -   array of grid nodes, second coordinates, array[N1]
//                 Must be ordered by ascending. Exception is generated
//                 if the array is not correctly ordered.
//     N1      -   grid size (number of nodes) in the second dimension
//
//     FlagY   -   array[N0*N1]:
//                 * Y[I0+I1*N0] corresponds to node (X0[I0],X1[I1])
//                 * it is a "bitmap" array which contains  False  for  nodes
//                   which are NOT calculated, and True for nodes  which  are
//                   required.
//
// Outputs:
//     Y       -   function values, array[NY*N0*N1*N2], where NY is a  number
//                 of "output" vector values (this function  supports vector-
//                 valued RBF models):
//                 * Y[K+NY*(I0+I1*N0)]=F_k(X0[I0],X1[I1]),
//                   for K=0...NY-1, I0=0...N0-1, I1=0...N1-1.
//                 * elements of Y[] which correspond  to  FlagY[]=True   are
//                   loaded by model values (which may be  exactly  zero  for
//                   some nodes).
//                 * elements of Y[] which correspond to FlagY[]=False MAY be
//                   initialized by zeros OR may be calculated. This function
//                   processes  grid  as  a  hierarchy  of  nested blocks and
//                   micro-rows. If just one element of micro-row is required,
//                   entire micro-row (up to 8 nodes in the current  version,
//                   but no promises) is calculated.
//
// NOTE: this function supports weakly ordered grid nodes, i.e. you may  have
//       X[i]=X[i+1] for some i. It does  not  provide  you  any  performance
//       benefits  due  to   duplication  of  points,  just  convenience  and
//       flexibility.
//
// NOTE: this  function  is  re-entrant,  i.e.  you  may  use  same  rbfmodel
//       structure in multiple threads calling  this function  for  different
//       grids.
// ALGLIB: Copyright 04.03.2016 by Sergey Bochkanov
void rbfgridcalc2vsubset(const rbfmodel &s, const real_1d_array &x0, const ae_int_t n0, const real_1d_array &x1, const ae_int_t n1, const boolean_1d_array &flagy, real_1d_array &y);

// This function calculates values of the RBF  model  at  the  regular  grid,
// which  has  N0*N1*N2  points,  with  Point[I,J,K] = (X0[I], X1[J], X2[K]).
// Vector-valued RBF models are supported.
//
// This function returns 0.0 when:
// * model is not initialized
// * NX != 3
//
// NOTE: Parallel  processing  is  implemented only for modern (hierarchical)
//       RBFs. Legacy version 1 RBFs (created  by  QNN  or  RBF-ML) are still
//       processed serially.
//
// Inputs:
//     S       -   RBF model, used in read-only mode, can be  shared  between
//                 multiple   invocations  of  this  function  from  multiple
//                 threads.
//
//     X0      -   array of grid nodes, first coordinates, array[N0].
//                 Must be ordered by ascending. Exception is generated
//                 if the array is not correctly ordered.
//     N0      -   grid size (number of nodes) in the first dimension
//
//     X1      -   array of grid nodes, second coordinates, array[N1]
//                 Must be ordered by ascending. Exception is generated
//                 if the array is not correctly ordered.
//     N1      -   grid size (number of nodes) in the second dimension
//
//     X2      -   array of grid nodes, third coordinates, array[N2]
//                 Must be ordered by ascending. Exception is generated
//                 if the array is not correctly ordered.
//     N2      -   grid size (number of nodes) in the third dimension
//
// Outputs:
//     Y       -   function values, array[NY*N0*N1*N2], where NY is a  number
//                 of "output" vector values (this function  supports vector-
//                 valued RBF models). Y is out-variable and  is  reallocated
//                 by this function.
//                 Y[K+NY*(I0+I1*N0+I2*N0*N1)]=F_k(X0[I0],X1[I1],X2[I2]), for:
//                 *  K=0...NY-1
//                 * I0=0...N0-1
//                 * I1=0...N1-1
//                 * I2=0...N2-1
//
// NOTE: this function supports weakly ordered grid nodes, i.e. you may  have
//       X[i]=X[i+1] for some i. It does  not  provide  you  any  performance
//       benefits  due  to   duplication  of  points,  just  convenience  and
//       flexibility.
//
// NOTE: this  function  is  re-entrant,  i.e.  you  may  use  same  rbfmodel
//       structure in multiple threads calling  this function  for  different
//       grids.
//
// NOTE: if you need function values on some subset  of  regular  grid, which
//       may be described as "several compact and  dense  islands",  you  may
//       use rbfgridcalc3vsubset().
// ALGLIB: Copyright 04.03.2016 by Sergey Bochkanov
void rbfgridcalc3v(const rbfmodel &s, const real_1d_array &x0, const ae_int_t n0, const real_1d_array &x1, const ae_int_t n1, const real_1d_array &x2, const ae_int_t n2, real_1d_array &y);

// This function calculates values of the RBF model at some subset of regular
// grid:
// * grid has N0*N1*N2 points, with Point[I,J,K] = (X0[I], X1[J], X2[K])
// * only values at some subset of this grid are required
// Vector-valued RBF models are supported.
//
// This function returns 0.0 when:
// * model is not initialized
// * NX != 3
//
// NOTE: Parallel  processing  is  implemented only for modern (hierarchical)
//       RBFs. Legacy version 1 RBFs (created  by  QNN  or  RBF-ML) are still
//       processed serially.
//
// Inputs:
//     S       -   RBF model, used in read-only mode, can be  shared  between
//                 multiple   invocations  of  this  function  from  multiple
//                 threads.
//
//     X0      -   array of grid nodes, first coordinates, array[N0].
//                 Must be ordered by ascending. Exception is generated
//                 if the array is not correctly ordered.
//     N0      -   grid size (number of nodes) in the first dimension
//
//     X1      -   array of grid nodes, second coordinates, array[N1]
//                 Must be ordered by ascending. Exception is generated
//                 if the array is not correctly ordered.
//     N1      -   grid size (number of nodes) in the second dimension
//
//     X2      -   array of grid nodes, third coordinates, array[N2]
//                 Must be ordered by ascending. Exception is generated
//                 if the array is not correctly ordered.
//     N2      -   grid size (number of nodes) in the third dimension
//
//     FlagY   -   array[N0*N1*N2]:
//                 * Y[I0+I1*N0+I2*N0*N1] corresponds to node (X0[I0],X1[I1],X2[I2])
//                 * it is a "bitmap" array which contains  False  for  nodes
//                   which are NOT calculated, and True for nodes  which  are
//                   required.
//
// Outputs:
//     Y       -   function values, array[NY*N0*N1*N2], where NY is a  number
//                 of "output" vector values (this function  supports vector-
//                 valued RBF models):
//                 * Y[K+NY*(I0+I1*N0+I2*N0*N1)]=F_k(X0[I0],X1[I1],X2[I2]),
//                   for K=0...NY-1, I0=0...N0-1, I1=0...N1-1, I2=0...N2-1.
//                 * elements of Y[] which correspond  to  FlagY[]=True   are
//                   loaded by model values (which may be  exactly  zero  for
//                   some nodes).
//                 * elements of Y[] which correspond to FlagY[]=False MAY be
//                   initialized by zeros OR may be calculated. This function
//                   processes  grid  as  a  hierarchy  of  nested blocks and
//                   micro-rows. If just one element of micro-row is required,
//                   entire micro-row (up to 8 nodes in the current  version,
//                   but no promises) is calculated.
//
// NOTE: this function supports weakly ordered grid nodes, i.e. you may  have
//       X[i]=X[i+1] for some i. It does  not  provide  you  any  performance
//       benefits  due  to   duplication  of  points,  just  convenience  and
//       flexibility.
//
// NOTE: this  function  is  re-entrant,  i.e.  you  may  use  same  rbfmodel
//       structure in multiple threads calling  this function  for  different
//       grids.
// ALGLIB: Copyright 04.03.2016 by Sergey Bochkanov
void rbfgridcalc3vsubset(const rbfmodel &s, const real_1d_array &x0, const ae_int_t n0, const real_1d_array &x1, const ae_int_t n1, const real_1d_array &x2, const ae_int_t n2, const boolean_1d_array &flagy, real_1d_array &y);

// This function "unpacks" RBF model by extracting its coefficients.
//
// Inputs:
//     S       -   RBF model
//
// Outputs:
//     NX      -   dimensionality of argument
//     NY      -   dimensionality of the target function
//     XWR     -   model information, array[NC,NX+NY+1].
//                 One row of the array corresponds to one basis function:
//                 * first NX columns  - coordinates of the center
//                 * next NY columns   - weights, one per dimension of the
//                                       function being modelled
//                 For ModelVersion=1:
//                 * last column       - radius, same for all dimensions of
//                                       the function being modelled
//                 For ModelVersion=2:
//                 * last NX columns   - radii, one per dimension
//     NC      -   number of the centers
//     V       -   polynomial  term , array[NY,NX+1]. One row per one
//                 dimension of the function being modelled. First NX
//                 elements are linear coefficients, V[NX] is equal to the
//                 constant part.
//     ModelVersion-version of the RBF model:
//                 * 1 - for models created by QNN and RBF-ML algorithms,
//                   compatible with ALGLIB 3.10 or earlier.
//                 * 2 - for models created by HierarchicalRBF, requires
//                   ALGLIB 3.11 or later
// ALGLIB: Copyright 13.12.2011 by Sergey Bochkanov
void rbfunpack(const rbfmodel &s, ae_int_t &nx, ae_int_t &ny, real_2d_array &xwr, ae_int_t &nc, real_2d_array &v, ae_int_t &modelversion);

// This function returns model version.
//
// Inputs:
//     S       -   RBF model
//
// Result:
//     * 1 - for models created by QNN and RBF-ML algorithms,
//       compatible with ALGLIB 3.10 or earlier.
//     * 2 - for models created by HierarchicalRBF, requires
//       ALGLIB 3.11 or later
// ALGLIB: Copyright 06.07.2016 by Sergey Bochkanov
ae_int_t rbfgetmodelversion(const rbfmodel &s);

// This function is used to peek into hierarchical RBF  construction  process
// from  some  other  thread  and  get current progress indicator. It returns
// value in [0,1].
//
// IMPORTANT: only HRBFs (hierarchical RBFs) support  peeking  into  progress
//            indicator. Legacy RBF-ML and RBF-QNN do  not  support  it.  You
//            will always get 0 value.
//
// Inputs:
//     S           -   RBF model object
//
// Result:
//     progress value, in [0,1]
// ALGLIB: Copyright 17.11.2018 by Sergey Bochkanov
double rbfpeekprogress(const rbfmodel &s);

// This function  is  used  to  submit  a  request  for  termination  of  the
// hierarchical RBF construction process from some other thread.  As  result,
// RBF construction is terminated smoothly (with proper deallocation  of  all
// necessary resources) and resultant model is filled by zeros.
//
// A rep.terminationtype=8 will be returned upon receiving such request.
//
// IMPORTANT: only  HRBFs  (hierarchical  RBFs) support termination requests.
//            Legacy RBF-ML and RBF-QNN do not  support  it.  An  attempt  to
//            terminate their construction will be ignored.
//
// IMPORTANT: termination request flag is cleared when the model construction
//            starts. Thus, any pre-construction termination requests will be
//            silently ignored - only ones submitted AFTER  construction  has
//            actually began will be handled.
//
// Inputs:
//     S           -   RBF model object
// ALGLIB: Copyright 17.11.2018 by Sergey Bochkanov
void rbfrequesttermination(const rbfmodel &s);
} // end of namespace alglib

// === INTCOMP Package ===
// Depends on: FITSPHERE SPLINE1D
namespace alglib_impl {
void nsfitspheremcc(RMatrix *xy, ae_int_t npoints, ae_int_t nx, RVector *cx, double *rhi);
void nsfitspheremic(RMatrix *xy, ae_int_t npoints, ae_int_t nx, RVector *cx, double *rlo);
void nsfitspheremzc(RMatrix *xy, ae_int_t npoints, ae_int_t nx, RVector *cx, double *rlo, double *rhi);
void nsfitspherex(RMatrix *xy, ae_int_t npoints, ae_int_t nx, ae_int_t problemtype, double epsx, ae_int_t aulits, double penalty, RVector *cx, double *rlo, double *rhi);
} // end of namespace alglib_impl

namespace alglib {
// This function is left for backward compatibility.
// Use fitspheremc() instead.
//
// ALGLIB: Copyright 14.04.2017 by Sergey Bochkanov
void nsfitspheremcc(const real_2d_array &xy, const ae_int_t npoints, const ae_int_t nx, real_1d_array &cx, double &rhi);

// This function is left for backward compatibility.
// Use fitspheremi() instead.
// ALGLIB: Copyright 14.04.2017 by Sergey Bochkanov
void nsfitspheremic(const real_2d_array &xy, const ae_int_t npoints, const ae_int_t nx, real_1d_array &cx, double &rlo);

// This function is left for backward compatibility.
// Use fitspheremz() instead.
// ALGLIB: Copyright 14.04.2017 by Sergey Bochkanov
void nsfitspheremzc(const real_2d_array &xy, const ae_int_t npoints, const ae_int_t nx, real_1d_array &cx, double &rlo, double &rhi);

// This function is left for backward compatibility.
// Use fitspherex() instead.
// ALGLIB: Copyright 14.04.2017 by Sergey Bochkanov
void nsfitspherex(const real_2d_array &xy, const ae_int_t npoints, const ae_int_t nx, const ae_int_t problemtype, const double epsx, const ae_int_t aulits, const double penalty, real_1d_array &cx, double &rlo, double &rhi);
} // end of namespace alglib

#endif // OnceOnly
