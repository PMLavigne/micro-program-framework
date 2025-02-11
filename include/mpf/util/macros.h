/**
 * macros.h
 *
 * @author Patrick Lavigne
 */

#pragma once

#if defined(__has_cpp_attribute)
    #if defined(__has_c_attribute)
        #define MPF_HAS_ATTRIBUTE(name) __has_cpp_attribute(name) || __has_c_attribute(name)
    #else
        #define MPF_HAS_ATTRIBUTE(name) __has_cpp_attribute(name)
    #endif
#elif defined(__has_c_attribute)
    #define MPF_HAS_ATTRIBUTE(name) __has_c_attribute(name)
#else
    #define MPF_HAS_ATTRIBUTE(name) 0
#endif

#if MPF_HAS_ATTRIBUTE(gnu::packed)
#define MPF_ATTR_PACKED gnu::packed
#define MPF_HAS_ATTR_PACKED 1
#elif MPF_HAS_ATTRIBUTE(packed)
#define MPF_ATTR_PACKED packed
#define MPF_HAS_ATTR_PACKED 1
#else
#define MPF_ATTR_PACKED
#endif

#if MPF_HAS_ATTRIBUTE(gnu::nonstring)
#define MPF_ATTR_NONSTRING gnu::nonstring
#define MPF_HAS_ATTR_NONSTRING 1
#elif MPF_HAS_ATTRIBUTE(nonstring)
#define MPF_ATTR_NONSTRING nonstring
#define MPF_HAS_ATTR_NONSTRING 1
#else
#define MPF_ATTR_NONSTRING
#endif

#ifndef PACKED
#ifdef MPF_HAS_ATTR_PACKED
#define PACKED [[MPF_ATTR_PACKED]]
#else
#define PACKED
#endif
#endif

#ifndef NONSTRING
#ifdef MPF_HAS_ATTR_NONSTRING
#define NONSTRING [[MPF_ATTR_NONSTRING]]
#else
#define NONSTRING
#endif
#endif
