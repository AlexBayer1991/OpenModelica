//
// Copyright (c) 2002--2010
// Toon Knapen, Karl Meerbergen, Kresimir Fresl,
// Thomas Klimpel and Rutger ter Borg
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// THIS FILE IS AUTOMATICALLY GENERATED
// PLEASE DO NOT EDIT!
//

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_UPGTR_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_COMPUTATIONAL_UPGTR_HPP

#include <boost/assert.hpp>
#include <Core/Utils/numeric/bindings/begin.hpp>
#include <Core/Utils/numeric/bindings/detail/array.hpp>
#include <Core/Utils/numeric/bindings/is_column_major.hpp>
#include <Core/Utils/numeric/bindings/is_complex.hpp>
#include <Core/Utils/numeric/bindings/is_mutable.hpp>
#include <Core/Utils/numeric/bindings/is_real.hpp>
#include <Core/Utils/numeric/bindings/lapack/workspace.hpp>
#include <Core/Utils/numeric/bindings/remove_imaginary.hpp>
#include <Core/Utils/numeric/bindings/size.hpp>
#include <Core/Utils/numeric/bindings/stride.hpp>
#include <Core/Utils/numeric/bindings/uplo_tag.hpp>
#include <Core/Utils/numeric/bindings/value_type.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/utility/enable_if.hpp>

//
// The LAPACK-backend for upgtr is the netlib-compatible backend.
//
#include <Core/Utils/numeric/bindings/lapack/detail/lapack.h>
#include <Core/Utils/numeric/bindings/lapack/detail/lapack_option.hpp>

namespace boost {
namespace numeric {
namespace bindings {
namespace lapack {

//
// The detail namespace contains value-type-overloaded functions that
// dispatch to the appropriate back-end LAPACK-routine.
//
namespace detail {

//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * float value-type.
//
inline std::ptrdiff_t upgtr( const char uplo, const fortran_int_t n,
        const float* ap, const float* tau, float* q, const fortran_int_t ldq,
        float* work ) {
    fortran_int_t info(0);
    LAPACK_SOPGTR( &uplo, &n, ap, tau, q, &ldq, work, &info );
    return info;
}

//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * double value-type.
//
inline std::ptrdiff_t upgtr( const char uplo, const fortran_int_t n,
        const double* ap, const double* tau, double* q,
        const fortran_int_t ldq, double* work ) {
    fortran_int_t info(0);
    LAPACK_DOPGTR( &uplo, &n, ap, tau, q, &ldq, work, &info );
    return info;
}

//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * complex<float> value-type.
//
inline std::ptrdiff_t upgtr( const char uplo, const fortran_int_t n,
        const std::complex<float>* ap, const std::complex<float>* tau,
        std::complex<float>* q, const fortran_int_t ldq,
        std::complex<float>* work ) {
    fortran_int_t info(0);
    LAPACK_CUPGTR( &uplo, &n, ap, tau, q, &ldq, work, &info );
    return info;
}

//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * complex<double> value-type.
//
inline std::ptrdiff_t upgtr( const char uplo, const fortran_int_t n,
        const std::complex<double>* ap, const std::complex<double>* tau,
        std::complex<double>* q, const fortran_int_t ldq,
        std::complex<double>* work ) {
    fortran_int_t info(0);
    LAPACK_ZUPGTR( &uplo, &n, ap, tau, q, &ldq, work, &info );
    return info;
}

} // namespace detail

//
// Value-type based template class. Use this class if you need a type
// for dispatching to upgtr.
//
template< typename Value, typename Enable = void >
struct upgtr_impl {};

//
// This implementation is enabled if Value is a real type.
//
template< typename Value >
struct upgtr_impl< Value, typename boost::enable_if< is_real< Value > >::type > {

    typedef Value value_type;
    typedef typename remove_imaginary< Value >::type real_type;

    //
    // Static member function for user-defined workspaces, that
    // * Deduces the required arguments for dispatching to LAPACK, and
    // * Asserts that most arguments make sense.
    //
    template< typename VectorAP, typename VectorTAU, typename MatrixQ,
            typename WORK >
    static std::ptrdiff_t invoke( const char uplo, const VectorAP& ap,
            const VectorTAU& tau, MatrixQ& q, detail::workspace1<
            WORK > work ) {
        namespace bindings = ::boost::numeric::bindings;
        BOOST_STATIC_ASSERT( (bindings::is_column_major< MatrixQ >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename bindings::value_type< VectorAP >::type >::type,
                typename remove_const< typename bindings::value_type<
                VectorTAU >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename bindings::value_type< VectorAP >::type >::type,
                typename remove_const< typename bindings::value_type<
                MatrixQ >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< MatrixQ >::value) );
        BOOST_ASSERT( bindings::size(ap) >=
                bindings::size_column(q)*(bindings::size_column(q)+1)/2 );
        BOOST_ASSERT( bindings::size(tau) >= bindings::size_column(q)-1 );
        BOOST_ASSERT( bindings::size(work.select(real_type())) >=
                min_size_work( bindings::size_column(q) ));
        BOOST_ASSERT( bindings::size_column(q) >= 0 );
        BOOST_ASSERT( bindings::size_minor(q) == 1 ||
                bindings::stride_minor(q) == 1 );
        BOOST_ASSERT( bindings::stride_major(q) >= std::max< std::ptrdiff_t >(1,
                bindings::size_column(q)) );
        return detail::upgtr( uplo, bindings::size_column(q),
                bindings::begin_value(ap), bindings::begin_value(tau),
                bindings::begin_value(q), bindings::stride_major(q),
                bindings::begin_value(work.select(real_type())) );
    }

    //
    // Static member function that
    // * Figures out the minimal workspace requirements, and passes
    //   the results to the user-defined workspace overload of the
    //   invoke static member function
    // * Enables the unblocked algorithm (BLAS level 2)
    //
    template< typename VectorAP, typename VectorTAU, typename MatrixQ >
    static std::ptrdiff_t invoke( const char uplo, const VectorAP& ap,
            const VectorTAU& tau, MatrixQ& q, minimal_workspace ) {
        namespace bindings = ::boost::numeric::bindings;
        bindings::detail::array< real_type > tmp_work( min_size_work(
                bindings::size_column(q) ) );
        return invoke( uplo, ap, tau, q, workspace( tmp_work ) );
    }

    //
    // Static member function that
    // * Figures out the optimal workspace requirements, and passes
    //   the results to the user-defined workspace overload of the
    //   invoke static member
    // * Enables the blocked algorithm (BLAS level 3)
    //
    template< typename VectorAP, typename VectorTAU, typename MatrixQ >
    static std::ptrdiff_t invoke( const char uplo, const VectorAP& ap,
            const VectorTAU& tau, MatrixQ& q, optimal_workspace ) {
        namespace bindings = ::boost::numeric::bindings;
        return invoke( uplo, ap, tau, q, minimal_workspace() );
    }

    //
    // Static member function that returns the minimum size of
    // workspace-array work.
    //
    static std::ptrdiff_t min_size_work( const std::ptrdiff_t n ) {
        return n-1;
    }
};

//
// This implementation is enabled if Value is a complex type.
//
template< typename Value >
struct upgtr_impl< Value, typename boost::enable_if< is_complex< Value > >::type > {

    typedef Value value_type;
    typedef typename remove_imaginary< Value >::type real_type;

    //
    // Static member function for user-defined workspaces, that
    // * Deduces the required arguments for dispatching to LAPACK, and
    // * Asserts that most arguments make sense.
    //
    template< typename VectorAP, typename VectorTAU, typename MatrixQ,
            typename WORK >
    static std::ptrdiff_t invoke( const char uplo, const VectorAP& ap,
            const VectorTAU& tau, MatrixQ& q, detail::workspace1<
            WORK > work ) {
        namespace bindings = ::boost::numeric::bindings;
        BOOST_STATIC_ASSERT( (bindings::is_column_major< MatrixQ >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename bindings::value_type< VectorAP >::type >::type,
                typename remove_const< typename bindings::value_type<
                VectorTAU >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename bindings::value_type< VectorAP >::type >::type,
                typename remove_const< typename bindings::value_type<
                MatrixQ >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< MatrixQ >::value) );
        BOOST_ASSERT( bindings::size(ap) >=
                bindings::size_column(q)*(bindings::size_column(q)+1)/2 );
        BOOST_ASSERT( bindings::size(tau) >= bindings::size_column(q)-1 );
        BOOST_ASSERT( bindings::size(work.select(value_type())) >=
                min_size_work( bindings::size_column(q) ));
        BOOST_ASSERT( bindings::size_column(q) >= 0 );
        BOOST_ASSERT( bindings::size_minor(q) == 1 ||
                bindings::stride_minor(q) == 1 );
        BOOST_ASSERT( bindings::stride_major(q) >= std::max< std::ptrdiff_t >(1,
                bindings::size_column(q)) );
        return detail::upgtr( uplo, bindings::size_column(q),
                bindings::begin_value(ap), bindings::begin_value(tau),
                bindings::begin_value(q), bindings::stride_major(q),
                bindings::begin_value(work.select(value_type())) );
    }

    //
    // Static member function that
    // * Figures out the minimal workspace requirements, and passes
    //   the results to the user-defined workspace overload of the
    //   invoke static member function
    // * Enables the unblocked algorithm (BLAS level 2)
    //
    template< typename VectorAP, typename VectorTAU, typename MatrixQ >
    static std::ptrdiff_t invoke( const char uplo, const VectorAP& ap,
            const VectorTAU& tau, MatrixQ& q, minimal_workspace ) {
        namespace bindings = ::boost::numeric::bindings;
        bindings::detail::array< value_type > tmp_work( min_size_work(
                bindings::size_column(q) ) );
        return invoke( uplo, ap, tau, q, workspace( tmp_work ) );
    }

    //
    // Static member function that
    // * Figures out the optimal workspace requirements, and passes
    //   the results to the user-defined workspace overload of the
    //   invoke static member
    // * Enables the blocked algorithm (BLAS level 3)
    //
    template< typename VectorAP, typename VectorTAU, typename MatrixQ >
    static std::ptrdiff_t invoke( const char uplo, const VectorAP& ap,
            const VectorTAU& tau, MatrixQ& q, optimal_workspace ) {
        namespace bindings = ::boost::numeric::bindings;
        return invoke( uplo, ap, tau, q, minimal_workspace() );
    }

    //
    // Static member function that returns the minimum size of
    // workspace-array work.
    //
    static std::ptrdiff_t min_size_work( const std::ptrdiff_t n ) {
        return n-1;
    }
};


//
// Functions for direct use. These functions are overloaded for temporaries,
// so that wrapped types can still be passed and used for write-access. In
// addition, if applicable, they are overloaded for user-defined workspaces.
// Calls to these functions are passed to the upgtr_impl classes. In the
// documentation, most overloads are collapsed to avoid a large number of
// prototypes which are very similar.
//

//
// Overloaded function for upgtr. Its overload differs for
// * User-defined workspace
//
template< typename VectorAP, typename VectorTAU, typename MatrixQ,
        typename Workspace >
inline typename boost::enable_if< detail::is_workspace< Workspace >,
        std::ptrdiff_t >::type
upgtr( const char uplo, const VectorAP& ap, const VectorTAU& tau,
        MatrixQ& q, Workspace work ) {
    return upgtr_impl< typename bindings::value_type<
            VectorAP >::type >::invoke( uplo, ap, tau, q, work );
}

//
// Overloaded function for upgtr. Its overload differs for
// * Default workspace-type (optimal)
//
template< typename VectorAP, typename VectorTAU, typename MatrixQ >
inline typename boost::disable_if< detail::is_workspace< MatrixQ >,
        std::ptrdiff_t >::type
upgtr( const char uplo, const VectorAP& ap, const VectorTAU& tau,
        MatrixQ& q ) {
    return upgtr_impl< typename bindings::value_type<
            VectorAP >::type >::invoke( uplo, ap, tau, q,
            optimal_workspace() );
}

} // namespace lapack
} // namespace bindings
} // namespace numeric
} // namespace boost

#endif