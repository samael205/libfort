/*
libfort

MIT License

Copyright (c) 2017 - 2018 Seleznev Anton

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

/**
 * @file fort.h
 * @brief Main header file describing libfort API.
 *
 * This file contains declarations of all libfort functions and macro
 * definitions.
 */

#ifndef LIBFORT_H
#define LIBFORT_H

#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>

/*****************************************************************************
 *               Configuration
 *****************************************************************************/
/**
 * libfort configuration macros
 * (to enable/disable some options this macros should be defined/undefined)
 */
/** #define FT_CONGIG_HAVE_WCHAR */

#if defined(FT_CONGIG_HAVE_WCHAR)
#define FT_HAVE_WCHAR
#endif


/*****************************************************************************
 *               RETURN CODES
 *****************************************************************************/
typedef int fort_status_t;
#define FT_SUCCESS        0
#define FT_MEMORY_ERROR   -1
#define FT_ERROR          -2
#define FT_EINVAL         -3
#define FT_IS_SUCCESS(arg) ((arg) >= 0)
#define FT_IS_ERROR(arg) ((arg) < 0)




/**
 * @cond HELPER_MACROS
 */

/*****************************************************************************
 *               Determine compiler
 *****************************************************************************/

#if defined(__clang__)
#define FT_CLANG_COMPILER
#elif defined(__GNUC__)
#define FT_GCC_COMPILER
#elif defined(_MSC_VER)
#define FT_MICROSOFT_COMPILER
#else
#define FT_UNDEFINED_COMPILER
#endif


/*****************************************************************************
 *               Declare inline
 *****************************************************************************/

#if defined(__cplusplus)
#define FT_INLINE inline
#else
#define FT_INLINE __inline
#endif /* if defined(__cplusplus) */


/*****************************************************************************
 *    C++ needs to know that types and declarations are C, not C++.
 *****************************************************************************/

#ifdef __cplusplus
# define FT_BEGIN_DECLS extern "C" {
# define FT_END_DECLS }
#else
# define FT_BEGIN_DECLS
# define FT_END_DECLS
#endif


/*****************************************************************************
 *               Helper macros
 *****************************************************************************/

#define FT_STR_2_CAT_(arg1, arg2) \
    arg1##arg2
#define FT_STR_2_CAT(arg1, arg2) \
    FT_STR_2_CAT_(arg1, arg2)

/**
 * @interanl
 */
static FT_INLINE int ft_check_if_string_helper(const char *str)
{
    (void)str;
    return 0;
}

/**
 * @interanl
 */
static FT_INLINE int ft_check_if_wstring_helper(const wchar_t *str)
{
    (void)str;
    return 0;
}

#define FT_NARGS_IMPL_(x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15,N,...) N
#define FT_EXPAND_(x) x
#define FT_PP_NARG_(...) \
    FT_EXPAND_(FT_NARGS_IMPL_(__VA_ARGS__,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0))

#define FT_CHECK_IF_STR_32(checker,arg,...) (checker(arg),FT_EXPAND_(FT_CHECK_IF_STR_31(checker,__VA_ARGS__)))
#define FT_CHECK_IF_STR_31(checker,arg,...) (checker(arg),FT_EXPAND_(FT_CHECK_IF_STR_30(checker,__VA_ARGS__)))
#define FT_CHECK_IF_STR_30(checker,arg,...) (checker(arg),FT_EXPAND_(FT_CHECK_IF_STR_29(checker,__VA_ARGS__)))
#define FT_CHECK_IF_STR_29(checker,arg,...) (checker(arg),FT_EXPAND_(FT_CHECK_IF_STR_28(checker,__VA_ARGS__)))
#define FT_CHECK_IF_STR_28(checker,arg,...) (checker(arg),FT_EXPAND_(FT_CHECK_IF_STR_27(checker,__VA_ARGS__)))
#define FT_CHECK_IF_STR_27(checker,arg,...) (checker(arg),FT_EXPAND_(FT_CHECK_IF_STR_26(checker,__VA_ARGS__)))
#define FT_CHECK_IF_STR_26(checker,arg,...) (checker(arg),FT_EXPAND_(FT_CHECK_IF_STR_25(checker,__VA_ARGS__)))
#define FT_CHECK_IF_STR_25(checker,arg,...) (checker(arg),FT_EXPAND_(FT_CHECK_IF_STR_24(checker,__VA_ARGS__)))
#define FT_CHECK_IF_STR_24(checker,arg,...) (checker(arg),FT_EXPAND_(FT_CHECK_IF_STR_23(checker,__VA_ARGS__)))
#define FT_CHECK_IF_STR_23(checker,arg,...) (checker(arg),FT_EXPAND_(FT_CHECK_IF_STR_22(checker,__VA_ARGS__)))
#define FT_CHECK_IF_STR_22(checker,arg,...) (checker(arg),FT_EXPAND_(FT_CHECK_IF_STR_21(checker,__VA_ARGS__)))
#define FT_CHECK_IF_STR_21(checker,arg,...) (checker(arg),FT_EXPAND_(FT_CHECK_IF_STR_20(checker,__VA_ARGS__)))
#define FT_CHECK_IF_STR_20(checker,arg,...) (checker(arg),FT_EXPAND_(FT_CHECK_IF_STR_19(checker,__VA_ARGS__)))
#define FT_CHECK_IF_STR_19(checker,arg,...) (checker(arg),FT_EXPAND_(FT_CHECK_IF_STR_18(checker,__VA_ARGS__)))
#define FT_CHECK_IF_STR_18(checker,arg,...) (checker(arg),FT_EXPAND_(FT_CHECK_IF_STR_17(checker,__VA_ARGS__)))
#define FT_CHECK_IF_STR_17(checker,arg,...) (checker(arg),FT_EXPAND_(FT_CHECK_IF_STR_16(checker,__VA_ARGS__)))
#define FT_CHECK_IF_STR_16(checker,arg,...) (checker(arg),FT_EXPAND_(FT_CHECK_IF_STR_15(checker,__VA_ARGS__)))
#define FT_CHECK_IF_STR_15(checker,arg,...) (checker(arg),FT_EXPAND_(FT_CHECK_IF_STR_14(checker,__VA_ARGS__)))
#define FT_CHECK_IF_STR_14(checker,arg,...) (checker(arg),FT_EXPAND_(FT_CHECK_IF_STR_13(checker,__VA_ARGS__)))
#define FT_CHECK_IF_STR_13(checker,arg,...) (checker(arg),FT_EXPAND_(FT_CHECK_IF_STR_12(checker,__VA_ARGS__)))
#define FT_CHECK_IF_STR_12(checker,arg,...) (checker(arg),FT_EXPAND_(FT_CHECK_IF_STR_11(checker,__VA_ARGS__)))
#define FT_CHECK_IF_STR_11(checker,arg,...) (checker(arg),FT_EXPAND_(FT_CHECK_IF_STR_10(checker,__VA_ARGS__)))
#define FT_CHECK_IF_STR_10(checker,arg,...) (checker(arg),FT_EXPAND_(FT_CHECK_IF_STR_9(checker,__VA_ARGS__)))
#define FT_CHECK_IF_STR_9(checker,arg,...) (checker(arg),FT_EXPAND_(FT_CHECK_IF_STR_8(checker,__VA_ARGS__)))
#define FT_CHECK_IF_STR_8(checker,arg,...) (checker(arg),FT_EXPAND_(FT_CHECK_IF_STR_7(checker,__VA_ARGS__)))
#define FT_CHECK_IF_STR_7(checker,arg,...) (checker(arg),FT_EXPAND_(FT_CHECK_IF_STR_6(checker,__VA_ARGS__)))
#define FT_CHECK_IF_STR_6(checker,arg,...) (checker(arg),FT_EXPAND_(FT_CHECK_IF_STR_5(checker,__VA_ARGS__)))
#define FT_CHECK_IF_STR_5(checker,arg,...) (checker(arg),FT_EXPAND_(FT_CHECK_IF_STR_4(checker,__VA_ARGS__)))
#define FT_CHECK_IF_STR_4(checker,arg,...) (checker(arg),FT_EXPAND_(FT_CHECK_IF_STR_3(checker,__VA_ARGS__)))
#define FT_CHECK_IF_STR_3(checker,arg,...) (checker(arg),FT_EXPAND_(FT_CHECK_IF_STR_2(checker,__VA_ARGS__)))
#define FT_CHECK_IF_STR_2(checker,arg,...) (checker(arg),FT_EXPAND_(FT_CHECK_IF_STR_1(checker,__VA_ARGS__)))
#define FT_CHECK_IF_STR_1(checker,arg) (checker(arg))

#define FT_CHECK_IF_ARGS_ARE_STRINGS__(checker,func, ...) \
    FT_EXPAND_(func(checker,__VA_ARGS__))
#define FT_CHECK_IF_ARGS_ARE_STRINGS_(checker,basis, n, ...) \
    FT_CHECK_IF_ARGS_ARE_STRINGS__(checker,FT_STR_2_CAT_(basis, n), __VA_ARGS__)
#define FT_CHECK_IF_ARGS_ARE_STRINGS(...) \
    FT_CHECK_IF_ARGS_ARE_STRINGS_(ft_check_if_string_helper,FT_CHECK_IF_STR_,FT_PP_NARG_(__VA_ARGS__), __VA_ARGS__)

#ifdef FT_HAVE_WCHAR
#define CHECK_IF_ARGS_ARE_WSTRINGS(...) \
    FT_CHECK_IF_ARGS_ARE_STRINGS_(ft_check_if_wstring_helper,FT_CHECK_IF_STR_,FT_PP_NARG_(__VA_ARGS__), __VA_ARGS__)
#endif

/**
 * @endcond
 */


/*****************************************************************************
 *               Attribute format for argument checking
 *****************************************************************************/

#if defined(FT_CLANG_COMPILER) || defined(FT_GCC_COMPILER)
#define FT_PRINTF_ATTRIBUTE_FORMAT(string_index, first_to_check) \
    __attribute__ ((format (printf, string_index, first_to_check)))
#else
#define FT_PRINTF_ATTRIBUTE_FORMAT(string_index, first_to_check)
#endif /* defined(FT_CLANG_COMPILER) || defined(FT_GCC_COMPILER) */


/*****************************************************************************
 *                   libfort API
 *****************************************************************************/

FT_BEGIN_DECLS

/**
 * The main structure of libfort containing information about formatted table.
 */
struct ft_table;

/**
 * The main structure of libfort containing information about formatted table.
 *
 * ft_table_t objects should be created by a call to ft_create_table and
 * destroyed with ft_destroy_table.
 */
typedef struct ft_table ft_table_t;

/**
 * Create formatted table.
 *
 * @return
 *   The pointer to the new allocated ft_table_t, on success. NULL on error.
 */
ft_table_t *ft_create_table(void);

/**
 * Destroy formatted table.
 *
 * Destroy formatted table and free all resources allocated during table creation
 * and work with it.
 *
 * @param table
 *   Pointer to formatted table previousley created with ft_create_table. If
 *   table is a null pointer, the function does nothing.
 */
void ft_destroy_table(ft_table_t *table);

/**
 * Move current position to the first cell of the next line(row).
 *
 * @param table
 *   Pointer to formatted table.
 */
void ft_ln(ft_table_t *table);

/**
 * Get row number of the current cell.
 *
 * @param table
 *   Pointer to formatted table.
 * @return
 *   Row number of the current cell.
 */
size_t ft_cur_row(ft_table_t *table);

/**
 * Get column number of the current cell.
 *
 * @param table
 *   Pointer to formatted table.
 * @return
 *   Column number of the current cell.
 */
size_t ft_cur_col(ft_table_t *table);

/**
 * Set current cell position.
 *
 * Current cell - cell that will be edited with all modifiing functions
 * (ft_printf, ft_write ...).
 *
 * @param table
 *   Pointer to formatted table.
 * @param row
 *   New row number for the current cell.
 * @param col
 *   New row number for the current cell.
 */
void ft_set_cur_cell(ft_table_t *table, size_t row, size_t col);



#if defined(FT_CLANG_COMPILER) || defined(FT_GCC_COMPILER)

/**
 * Write data formatted acording to the format string to a variety of table
 * cells.
 *
 * @param table
 *   Pointer to formatted table.
 * @param fmt
 *   Pointer to a null-terminated multibyte string specifying how to interpret
 *   the data. The format string consists of ordinary characters (except % and |),
 *   which are copied unchanged into the output stream, and conversion
 *   specifications. Conversion specifications are the same as for standard
 *   printf function. Character '|' in the format string is treated as a cell
 *   separator.
 * @param ...
 *   Arguments specifying data to print. Similarly to standard printf-like
 *   functions if any argument after default conversions is not the type
 *   expected by the corresponding conversion specifier, or if there are fewer
 *   arguments than required by format, the behavior is undefined. If there are
 *   more arguments than required by format, the extraneous arguments are
 *   evaluated and ignored.
 * @return
 *   - Number of printed cells
 *   - (<0): In case of error
 */
int ft_printf(ft_table_t *table, const char *fmt, ...) FT_PRINTF_ATTRIBUTE_FORMAT(2, 3);

/**
 * Write data formatted acording to the format string to a variety of table
 * cells and move current position to the first cell of the next line(row).
 *
 * @param table
 *   Pointer to formatted table.
 * @param fmt
 *   Pointer to a null-terminated multibyte string specifying how to interpret
 *   the data. The format string consists of ordinary characters (except % and |),
 *   which are copied unchanged into the output stream, and conversion
 *   specifications. Conversion specifications are the same as for standard
 *   printf function. Character '|' in the format string is treated as a cell
 *   separator.
 * @param ...
 *   Arguments specifying data to print. Similarly to standard printf-like
 *   functions if any argument after default conversions is not the type
 *   expected by the corresponding conversion specifier, or if there are fewer
 *   arguments than required by format, the behavior is undefined. If there are
 *   more arguments than required by format, the extraneous arguments are
 *   evaluated and ignored.
 * @return
 *   - Number of printed cells.
 *   - (<0): In case of error.
 */
int ft_printf_ln(ft_table_t *table, const char *fmt, ...) FT_PRINTF_ATTRIBUTE_FORMAT(2, 3);

#else

/**
 * @cond IGNORE_DOC
 */

int ft_printf_impl(ft_table_t *table, const char *fmt, ...) FT_PRINTF_ATTRIBUTE_FORMAT(2, 3);
int ft_printf_ln_impl(ft_table_t *table, const char *fmt, ...) FT_PRINTF_ATTRIBUTE_FORMAT(2, 3);

#define ft_printf(table, ...) \
    (( 0 ? fprintf(stderr, __VA_ARGS__) : 1), ft_printf_impl(table, __VA_ARGS__))
#define ft_printf_ln(table, ...) \
    (( 0 ? fprintf(stderr, __VA_ARGS__) : 1), ft_printf_ln_impl(table, __VA_ARGS__))

/**
 * @endcond
 */
#endif


/**
 * Write strings to the the table.
 *
 * Write specified strings to the same number of consecutive cells in the
 * current row.
 *
 * @param table
 *   Pointer to formatted table.
 * @param ...
 *   Strings to write.
 * @return
 *   - 0: Success; data were written
 *   - (<0): In case of error
 */
#define ft_write(table, ...)\
    (0 ? FT_CHECK_IF_ARGS_ARE_STRINGS(__VA_ARGS__) : ft_nwrite(table, FT_PP_NARG_(__VA_ARGS__), __VA_ARGS__))

/**
 * Write strings to the the table and go to the next line.
 *
 * Write specified strings to the same number of consecutive cells in the
 * current row and move current position to the first cell of the next
 * line(row).
 *
 * @param table
 *   Pointer to formatted table.
 * @param ...
 *   Strings to write.
 * @return
 *   - 0: Success; data were written
 *   - (<0): In case of error
 */
#define ft_write_ln(table, ...)\
    (0 ? FT_CHECK_IF_ARGS_ARE_STRINGS(__VA_ARGS__) : ft_nwrite_ln(table, FT_PP_NARG_(__VA_ARGS__), __VA_ARGS__))

/**
 * Write specified number of strings to the the table.
 *
 * Write specified number of strings to the same number of consecutive cells in
 * the current row.
 *
 * @note In most cases it is more preferable to use MACRO @ref ft_write instead
 * of @ref ft_nwrite, which is more safe (@ref ft_write automatically counts the
 * number of string arguments and at compile check that all passed arguments are
 * strings).
 *
 * @param table
 *   Pointer to formatted table.
 * @param count
 *   Number of strings to write.
 * @param cell_content
 *   First string to write.
 * @param ...
 *   Other strings to write.
 * @return
 *   - 0: Success; data were written
 *   - (<0): In case of error
 */
int ft_nwrite(ft_table_t *table, size_t count, const char *cell_content, ...);

/**
 * Write specified number of strings to the the table and go to the next line.
 *
 * Write specified number of strings to the same number of consecutive cells
 * in the current row and move current position to the first cell of the next
 * line(row).
 *
 * @note In most cases it is more preferable to use MACRO @ref ft_write instead
 * of @ref ft_nwrite, which is more safe (@ref ft_write automatically counts the
 * number of string arguments and at compile check that all passed arguments are
 * strings).
 *
 * @param table
 *   Pointer to formatted table.
 * @param count
 *   Number of strings to write.
 * @param cell_content
 *   First string to write.
 * @param ...
 *   Other strings to write.
 * @return
 *   - 0: Success; data were written
 *   - (<0): In case of error
 */
int ft_nwrite_ln(ft_table_t *table, size_t count, const char *cell_content, ...);





/**
 * Write strings from the array to the table.
 *
 * Write specified number of strings from the array to the same number of
 * consecutive cells in the current row.
 *
 * @param table
 *   Pointer to formatted table.
 * @param cols
 *   Number of elements in row_cells.
 * @param row_cells
 *   Array of strings to write.
 * @return
 *   - 0: Success; data were written
 *   - (<0): In case of error
 */
int ft_row_write(ft_table_t *table, size_t cols, const char *row_cells[]);

/**
 * Write strings from the array to the table and go to the next line.
 *
 * Write specified number of strings from the array to the same number of
 * consecutive cells in the current row and move current position to the first
 * cell of the next line(row).
 *
 * @param table
 *   Pointer to formatted table.
 * @param cols
 *   Number of elements in row_cells.
 * @param row_cells
 *   Array of strings to write.
 * @return
 *   - 0: Success; data were written
 *   - (<0): In case of error
 */
int ft_row_write_ln(ft_table_t *table, size_t cols, const char *row_cells[]);


/**
 * Write strings from the 2D array to the table.
 *
 * Write specified number of strings from the 2D array to the formatted table.
 *
 * @param table
 *   Pointer to formatted table.
 * @param rows
 *   Number of rows in the 2D array.
 * @param cols
 *   Number of columns in the 2D array.
 * @param table_cells
 *   2D array of strings to write.
 * @return
 *   - 0: Success; data were written
 *   - (<0): In case of error
 */
int ft_table_write(ft_table_t *table, size_t rows, size_t cols, const char *table_cells[]);

/**
 * Write strings from the 2D array to the table and go to the next line.
 *
 * Write specified number of strings from the 2D array to the formatted table
 * and move current position to the first cell of the next line(row).
 *
 * @param table
 *   Pointer to formatted table.
 * @param rows
 *   Number of rows in the 2D array.
 * @param cols
 *   Number of columns in the 2D array.
 * @param table_cells
 *   2D array of strings to write.
 * @return
 *   - 0: Success; data were written
 *   - (<0): In case of error
 */
int ft_table_write_ln(ft_table_t *table, size_t rows, size_t cols, const char *table_cells[]);





/**
 * Add separator after the current row.
 *
 * @param table
 *   Formatted table.
 * @return
 *   - 0: Success; separator was added.
 *   - (<0): In case of error
 */
int ft_add_separator(ft_table_t *table);




/**
 * Convert table to string representation.
 *
 * ft_table_t has ownership of the returned pointer. So there is no need to
 * free it. To take ownership user should explicitly copy the returned
 * string with strdup or similar functions.
 *
 * Returned pointer may be later invalidated by:
 * - Calling ft_destroy_table;
 * - Other invocations of ft_to_string.
 *
 * @param table
 *   Formatted table.
 * @return
 *   - The pointer to the string representation of formatted table, on success.
 *   - NULL on error.
 */
const char *ft_to_string(const ft_table_t *table);













/**
 * Structure describing border appearance.
 */
struct ft_border_chars {
    const char *top_border_ch;
    const char *separator_ch;
    const char *bottom_border_ch;
    const char *side_border_ch;
    const char *out_intersect_ch;
    const char *in_intersect_ch;
};

/**
 * Structure describing border style.
 */
struct ft_border_style {
    struct ft_border_chars border_chs;
    struct ft_border_chars header_border_chs;
    const char *hor_separator_char;
};

/**
 * @defgroup BasicStyles
 * @name Built-in table border styles.
 * @{
 */
extern struct ft_border_style *FT_BASIC_STYLE;
extern struct ft_border_style *FT_BASIC2_STYLE;
extern struct ft_border_style *FT_SIMPLE_STYLE;
extern struct ft_border_style *FT_PLAIN_STYLE;
extern struct ft_border_style *FT_DOT_STYLE;
extern struct ft_border_style *FT_EMPTY_STYLE;
extern struct ft_border_style *FT_SOLID_STYLE;
extern struct ft_border_style *FT_SOLID_ROUND_STYLE;
extern struct ft_border_style *FT_DOUBLE_STYLE;
extern struct ft_border_style *FT_DOUBLE2_STYLE;
extern struct ft_border_style *FT_BOLD_STYLE;
extern struct ft_border_style *FT_BOLD2_STYLE;
extern struct ft_border_style *FT_FRAME_STYLE;
/** @} */



/**
 * Set default border style for all new formatted tables.
 *
 * @param style
 *   Pointer to border style.
 * @return
 *   - 0: Success; default border style was changed.
 *   - (<0): In case of error
 */
int ft_set_default_border_style(const struct ft_border_style *style);

/**
 * Set border style for the table.
 *
 * @param table
 *   A pointer to the ft_table_t structure.
 * @param style
 *   Pointer to border style.
 * @return
 *   - 0: Success; table border style was changed.
 *   - (<0): In case of error
 */
int ft_set_border_style(ft_table_t *table, const struct ft_border_style *style);



/**
 * @name Special macros to define cell position (row and column).
 * @{
 */
#define FT_ANY_COLUMN (UINT_MAX)     /**< Any column (can be used to refer to all cells in a row)*/
#define FT_CUR_COLUMN (UINT_MAX - 1) /**< Current column */
#define FT_ANY_ROW    (UINT_MAX)     /**< Any row (can be used to refer to all cells in a column)*/
#define FT_CUR_ROW    (UINT_MAX - 1) /**< Current row */
/** @} */



/**
 * @name Cell options identifiers.
 * @{
 */
#define FT_COPT_MIN_WIDTH        (0x01U << 0) /**< Minimum width */
#define FT_COPT_TEXT_ALIGN       (0x01U << 1) /**< Text alignmemnt */
#define FT_COPT_TOP_PADDING      (0x01U << 2) /**< Top padding for cell content */
#define FT_COPT_BOTTOM_PADDING   (0x01U << 3) /**< Bottom padding for cell content */
#define FT_COPT_LEFT_PADDING     (0x01U << 4) /**< Left padding for cell content */
#define FT_COPT_RIGHT_PADDING    (0x01U << 5) /**< Right padding for cell content */
#define FT_COPT_EMPTY_STR_HEIGHT (0x01U << 6) /**< Height of empty cell */
#define FT_COPT_ROW_TYPE         (0x01U << 7) /**< Row type */
/** @} */



/**
 * Alignment of cell content.
 */
enum ft_text_alignment {
    FT_ALIGNED_LEFT = 0,     /**< Align left */
    FT_ALIGNED_CENTER,       /**< Align center */
    FT_ALIGNED_RIGHT         /**< Align right */
};

/**
 * Type of table row. Determines appearance of row.
 */
enum ft_row_type {
    FT_ROW_COMMON = 0,      /**< Common row */
    FT_ROW_HEADER           /**< Header row */
};

/**
 * Set default cell option for all new formatted tables.
 *
 * @param option
 *   Cell option identifier.
 * @param value
 *   Cell option value.
 * @return
 *   - 0: Success; default cell option was changed.
 *   - (<0): In case of error
 */
int ft_set_default_cell_option(uint32_t option, int value);

/**
 * Set option for the specified cell of the table.
 *
 * @param table
 *   A pointer to the ft_table_t structure.
 * @param row
 *   Cell row.
 * @param col
 *   Cell column.
 * @param option
 *   Cell option identifier.
 * @param value
 *   Cell option value.
 * @return
 *   - 0: Success; cell option was changed.
 *   - (<0): In case of error
 */
int ft_set_cell_option(ft_table_t *table, size_t row, size_t col, uint32_t option, int value);


/**
 * @name Table options identifiers.
 * @{
 */
#define FT_TOPT_LEFT_MARGIN   (0x01U << 0)
#define FT_TOPT_TOP_MARGIN    (0x01U << 1)
#define FT_TOPT_RIGHT_MARGIN  (0x01U << 2)
#define FT_TOPT_BOTTOM_MARGIN (0x01U << 3)
/** @} */



/**
 * Set default table option.
 *
 * @param option
 *   Table option identifier.
 * @param value
 *   Table option value.
 * @return
 *   - 0: Success; default table option was changed.
 *   - (<0): In case of error
 */
int ft_set_default_tbl_option(uint32_t option, int value);

/**
 * Set table option.
 *
 * @param table
 *   A pointer to the ft_table_t structure.
 * @param option
 *   Table option identifier.
 * @param value
 *   Table option value.
 * @return
 *   - 0: Success; default table option was changed.
 *   - (<0): In case of error
 */
int ft_set_tbl_option(ft_table_t *table, uint32_t option, int value);


/**
 * Set column span for the specified cell of the table.
 *
 * @param table
 *   A pointer to the ft_table_t structure.
 * @param row
 *   Cell row.
 * @param col
 *   Cell column.
 * @param hor_span
 *   Column span.
 * @return
 *   - 0: Success; default table option was changed.
 *   - (<0): In case of error
 */
int ft_set_cell_span(ft_table_t *table, size_t row, size_t col, size_t hor_span);


/**
 * Set functions for memory allocation and deallocation to be used instead of
 * standard ones.
 *
 * @param f_malloc
 *   Pointer to a function for memory allocation that should be used instead of
 *   malloc.
 * @param f_free
 *   Pointer to a function for memory deallocation that should be used instead
 *   of free.
 * @note
 *   To return memory allocation/deallocation functions to their standard values
 *   set f_malloc and f_free to NULL.
 */
void ft_set_memory_funcs(void *(*f_malloc)(size_t size), void (*f_free)(void *ptr));




#ifdef FT_HAVE_WCHAR


int ft_wprintf(ft_table_t *table, const wchar_t *fmt, ...);
int ft_wprintf_ln(ft_table_t *table, const wchar_t *fmt, ...);


#define ft_wwrite(table, ...)\
    (0 ? CHECK_IF_ARGS_ARE_WSTRINGS(__VA_ARGS__) : ft_nwwrite(table, FT_PP_NARG_(__VA_ARGS__), __VA_ARGS__))
#define ft_wwrite_ln(table, ...)\
    (0 ? CHECK_IF_ARGS_ARE_WSTRINGS(__VA_ARGS__) : ft_nwwrite_ln(table, FT_PP_NARG_(__VA_ARGS__), __VA_ARGS__))
int ft_nwwrite(ft_table_t *table, size_t n, const wchar_t *cell_content, ...);
int ft_nwwrite_ln(ft_table_t *table, size_t n, const wchar_t *cell_content, ...);

int ft_row_wwrite(ft_table_t *table, size_t cols, const wchar_t *row_cells[]);
int ft_row_wwrite_ln(ft_table_t *table, size_t cols, const wchar_t *row_cells[]);

int ft_table_wwrite(ft_table_t *table, size_t rows, size_t cols, const wchar_t *table_cells[]);
int ft_table_wwrite_ln(ft_table_t *table, size_t rows, size_t cols, const wchar_t *table_cells[]);

const wchar_t *ft_to_wstring(const ft_table_t *table);
#endif



FT_END_DECLS

#endif /* LIBFORT_H */
