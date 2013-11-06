/* ANSI-C code produced by gperf version 3.0.4 */
/* Command-line: gperf -m 1 ./uninorm/composition-table.gperf  */
/* Computed positions: -k'1-2,4' */


#define TOTAL_KEYWORDS 928
#define MIN_WORD_LENGTH 4
#define MAX_WORD_LENGTH 4
#define MIN_HASH_VALUE 1
#define MAX_HASH_VALUE 1527
/* maximum key range = 1527, duplicates = 0 */

#ifdef __GNUC__
__inline
#else
#ifdef __cplusplus
inline
#endif
#endif
/*ARGSUSED*/
static unsigned int
gl_uninorm_compose_hash (register const char *str, register unsigned int len)
{
  static const unsigned short asso_values[] =
    {
         7,    1,    0,    3,   58,  132,  240,   62,    4,   33,
       117,  268,  485,  135,  601,  599,  103,  770,  249,  284,
        59,  337,  685,  524,  711,  106,  498,  569,  712, 1528,
        91,   13,  841,  752,  322,  487,  192,  604,  817,   13,
       337,   65,  137,  147,   45,  144,  255,  588,  133,  342,
       172,   15, 1528,  794,   60,   95,  606,   50,   18, 1528,
       239,   67,  198,  362,   75,   89,  324,    2,  531,  167,
        12,  375,  289,   61,  397,  314,  431,  452,  395,  180,
       821,  736,  362,  561,  456,  202,  536,  360,  645,  300,
       592,  700, 1528,  361, 1528,  358,  796,   26,  783,  653,
       270,   98,  253,  415,  323,   42,  747,  575,  542,  691,
       262,  124,  792, 1528,  251,  559,  236,  133,   12,  406,
       460,  219,  627,    9,  158,  168, 1528,    1, 1528, 1528,
       161,  153, 1528, 1528,  129,  123, 1528, 1528, 1528, 1528,
      1528, 1528, 1528, 1528,   23,  493,  109, 1528,   10,  676,
      1528,  725, 1528,  650,   59,  384, 1528,  291, 1528,   50,
       589,  518,   79, 1528, 1528,  672,  235, 1528,  466,  628,
      1528,   62,   27,  229,   20,  668,  778,  531,   37,    5,
        16,  416,    5,  560,   34,  482, 1528,  147, 1528,  138,
      1528,  476, 1528,  530,  839,    1,  329,  524,  675,  342,
       136,  684,  580,  211,   31,   19,    9,   87,   21, 1528,
       356, 1528,  725,  313,   14,    0,  555,   65, 1528,  256,
        37, 1528, 1528, 1528,  105, 1528,  833, 1528,   16,    4,
         0,    3,   19,    1,  755,    4, 1528, 1528, 1528,   54,
       100,   76,   27, 1528,  811,   20,   56, 1528,    1, 1528,
      1528, 1528,  706,   14,   71, 1528, 1528
    };
  return asso_values[(unsigned char)str[3]+1] + asso_values[(unsigned char)str[1]] + asso_values[(unsigned char)str[0]];
}

#ifdef __GNUC__
__inline
#if defined __GNUC_STDC_INLINE__ || defined __GNUC_GNU_INLINE__
__attribute__ ((__gnu_inline__))
#endif
#endif
const struct composition_rule *
gl_uninorm_compose_lookup (register const char *str, register unsigned int len)
{
  static const unsigned char lengthtable[] =
    {
       0,  4,  4,  0,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,
       4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,
       4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,
       4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,
       4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,
       4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,
       4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,
       4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,
       4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,
       4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,
       4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,
       4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,
       4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,
       4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,
       4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,
       4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,
       4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,
       4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,
       4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,
       4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,
       4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,
       4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,
       4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,
       4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,
       4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,
       4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,
       4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,
       4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,
       4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,
       4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,
       4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,
       4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,
       4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,
       4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,
       4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,
       4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,
       4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,
       4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,
       4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,
       4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,
       4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,
       4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,
       4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,
       4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,
       4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,
       4,  4,  4,  4,  4,  4,  4,  4,  4,  0,  4,  4,  4,  4,
       4,  4,  4,  4,  4,  0,  4,  4,  4,  4,  4,  4,  4,  4,
       4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,
       4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,
       4,  4,  4,  4,  4,  4,  0,  4,  4,  0,  4,  4,  4,  4,
       4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,
       4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,
       4,  4,  4,  4,  4,  4,  4,  4,  0,  4,  4,  4,  4,  4,
       4,  0,  4,  0,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,
       4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,
       4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,
       4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  0,
       4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,
       4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,
       4,  4,  4,  0,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,
       4,  4,  4,  4,  0,  4,  4,  4,  4,  4,  4,  4,  4,  4,
       4,  4,  4,  4,  4,  4,  4,  4,  0,  0,  4,  4,  4,  4,
       4,  0,  4,  4,  4,  4,  0,  4,  4,  0,  4,  4,  0,  0,
       0,  0,  4,  4,  4,  0,  4,  4,  4,  0,  4,  0,  0,  0,
       4,  4,  4,  4,  4,  4,  0,  4,  4,  4,  0,  0,  0,  0,
       0,  4,  0,  4,  4,  0,  0,  0,  4,  4,  0,  4,  0,  4,
       0,  0,  0,  0,  4,  0,  4,  4,  4,  0,  0,  4,  0,  0,
       0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  4,  0,  0,
       0,  4,  0,  0,  0,  4,  0,  0,  0,  0,  4,  4,  0,  0,
       0,  0,  4,  0,  0,  4,  4,  0,  0,  4,  4,  4,  0,  0,
       0,  0,  4,  0,  0,  0,  0,  0,  0,  0,  4,  4,  0,  0,
       0,  0,  0,  4,  0,  4,  4,  0,  0,  4,  0,  4,  0,  0,
       0,  0,  0,  0,  4,  0,  0,  0,  4,  0,  0,  0,  0,  0,
       0,  0,  4,  0,  0,  0,  0,  0,  4,  0,  0,  0,  0,  0,
       0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
       0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
       0,  4,  0,  0,  0,  0,  0,  0,  4,  0,  0,  0,  0,  0,
       0,  4,  0,  0,  0,  0,  0,  0,  4,  0,  0,  0,  0,  0,
       0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
       0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
       0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
       0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
       0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  4,  0,  4,  4,
       0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  4,  0,
       0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
       0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
       0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
       0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
       0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
       0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
       0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
       0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
       4,  0,  0,  0,  0,  0,  0,  4,  0,  0,  0,  0,  0,  0,
       0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
       0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
       0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
       0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
       0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
       0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
       0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  4,
       0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
       0,  0,  0,  0,  0,  4,  0,  0,  0,  0,  0,  0,  0,  0,
       0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
       0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
       0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
       0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
       0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
       4,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
       0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
       0,  4
    };
  static const struct composition_rule wordlist[] =
    {
      {""},
#line 572 "./uninorm/composition-table.gperf"
      {"\001\002\003\001", 0x1eae},
#line 574 "./uninorm/composition-table.gperf"
      {"\001\002\003\000", 0x1eb0},
      {""},
#line 573 "./uninorm/composition-table.gperf"
      {"\001\003\003\001", 0x1eaf},
#line 575 "./uninorm/composition-table.gperf"
      {"\001\003\003\000", 0x1eb1},
#line 557 "./uninorm/composition-table.gperf"
      {"\001\177\003\007", 0x1e9b},
#line 236 "./uninorm/composition-table.gperf"
      {"\000\346\003\001", 0x01fd},
#line 238 "./uninorm/composition-table.gperf"
      {"\000\370\003\001", 0x01ff},
#line 90 "./uninorm/composition-table.gperf"
      {"\000C\003\001", 0x0106},
#line 412 "./uninorm/composition-table.gperf"
      {"\000\347\003\001", 0x1e09},
#line 234 "./uninorm/composition-table.gperf"
      {"\000\345\003\001", 0x01fb},
#line 92 "./uninorm/composition-table.gperf"
      {"\000C\003\002", 0x0108},
#line 94 "./uninorm/composition-table.gperf"
      {"\000C\003\007", 0x010a},
#line 653 "./uninorm/composition-table.gperf"
      {"\037\001\003\001", 0x1f05},
#line 651 "./uninorm/composition-table.gperf"
      {"\037\001\003\000", 0x1f03},
#line 655 "./uninorm/composition-table.gperf"
      {"\037\001\003B", 0x1f07},
#line 660 "./uninorm/composition-table.gperf"
      {"\037\010\003\001", 0x1f0c},
#line 658 "./uninorm/composition-table.gperf"
      {"\037\010\003\000", 0x1f0a},
#line 662 "./uninorm/composition-table.gperf"
      {"\037\010\003B", 0x1f0e},
#line 652 "./uninorm/composition-table.gperf"
      {"\037\000\003\001", 0x1f04},
#line 650 "./uninorm/composition-table.gperf"
      {"\037\000\003\000", 0x1f02},
#line 654 "./uninorm/composition-table.gperf"
      {"\037\000\003B", 0x1f06},
#line 433 "./uninorm/composition-table.gperf"
      {"\000F\003\007", 0x1e1e},
#line 851 "./uninorm/composition-table.gperf"
      {"\003\316\003E", 0x1ff4},
#line 757 "./uninorm/composition-table.gperf"
      {"\037\002\003E", 0x1f82},
#line 756 "./uninorm/composition-table.gperf"
      {"\037\001\003E", 0x1f81},
#line 480 "./uninorm/composition-table.gperf"
      {"\000\365\003\001", 0x1e4d},
#line 758 "./uninorm/composition-table.gperf"
      {"\037\003\003E", 0x1f83},
#line 763 "./uninorm/composition-table.gperf"
      {"\037\010\003E", 0x1f88},
#line 809 "./uninorm/composition-table.gperf"
      {"\037\266\003E", 0x1fb7},
#line 506 "./uninorm/composition-table.gperf"
      {"\001a\003\007", 0x1e67},
#line 755 "./uninorm/composition-table.gperf"
      {"\037\000\003E", 0x1f80},
#line 58 "./uninorm/composition-table.gperf"
      {"\000a\003\001", 0x00e1},
#line 57 "./uninorm/composition-table.gperf"
      {"\000a\003\000", 0x00e0},
#line 817 "./uninorm/composition-table.gperf"
      {"\003\256\003E", 0x1fc4},
#line 59 "./uninorm/composition-table.gperf"
      {"\000a\003\002", 0x00e2},
#line 270 "./uninorm/composition-table.gperf"
      {"\000a\003\007", 0x0227},
#line 778 "./uninorm/composition-table.gperf"
      {"\037'\003E", 0x1f97},
#line 737 "./uninorm/composition-table.gperf"
      {"\037a\003\001", 0x1f65},
#line 735 "./uninorm/composition-table.gperf"
      {"\037a\003\000", 0x1f63},
#line 739 "./uninorm/composition-table.gperf"
      {"\037a\003B", 0x1f67},
#line 807 "./uninorm/composition-table.gperf"
      {"\003\254\003E", 0x1fb4},
#line 524 "./uninorm/composition-table.gperf"
      {"\001i\003\001", 0x1e79},
#line 206 "./uninorm/composition-table.gperf"
      {"\000\334\003\001", 0x01d7},
#line 210 "./uninorm/composition-table.gperf"
      {"\000\334\003\000", 0x01db},
#line 661 "./uninorm/composition-table.gperf"
      {"\037\011\003\001", 0x1f0d},
#line 659 "./uninorm/composition-table.gperf"
      {"\037\011\003\000", 0x1f0b},
#line 663 "./uninorm/composition-table.gperf"
      {"\037\011\003B", 0x1f0f},
#line 69 "./uninorm/composition-table.gperf"
      {"\000i\003\001", 0x00ed},
#line 68 "./uninorm/composition-table.gperf"
      {"\000i\003\000", 0x00ec},
#line 788 "./uninorm/composition-table.gperf"
      {"\037a\003E", 0x1fa1},
#line 70 "./uninorm/composition-table.gperf"
      {"\000i\003\002", 0x00ee},
#line 288 "./uninorm/composition-table.gperf"
      {"\003\237\003\001", 0x038c},
#line 854 "./uninorm/composition-table.gperf"
      {"\003\237\003\000", 0x1ff8},
#line 745 "./uninorm/composition-table.gperf"
      {"\037i\003\001", 0x1f6d},
#line 743 "./uninorm/composition-table.gperf"
      {"\037i\003\000", 0x1f6b},
#line 747 "./uninorm/composition-table.gperf"
      {"\037i\003B", 0x1f6f},
#line 764 "./uninorm/composition-table.gperf"
      {"\037\011\003E", 0x1f89},
#line 578 "./uninorm/composition-table.gperf"
      {"\001\002\003\003", 0x1eb4},
#line 482 "./uninorm/composition-table.gperf"
      {"\000\365\003\010", 0x1e4f},
#line 450 "./uninorm/composition-table.gperf"
      {"\000\357\003\001", 0x1e2f},
#line 579 "./uninorm/composition-table.gperf"
      {"\001\003\003\003", 0x1eb5},
#line 705 "./uninorm/composition-table.gperf"
      {"\0379\003\001", 0x1f3d},
#line 703 "./uninorm/composition-table.gperf"
      {"\0379\003\000", 0x1f3b},
#line 707 "./uninorm/composition-table.gperf"
      {"\0379\003B", 0x1f3f},
#line 61 "./uninorm/composition-table.gperf"
      {"\000a\003\010", 0x00e4},
#line 796 "./uninorm/composition-table.gperf"
      {"\037i\003E", 0x1fa9},
#line 43 "./uninorm/composition-table.gperf"
      {"\000I\003\001", 0x00cd},
#line 42 "./uninorm/composition-table.gperf"
      {"\000I\003\000", 0x00cc},
#line 783 "./uninorm/composition-table.gperf"
      {"\037,\003E", 0x1f9c},
#line 44 "./uninorm/composition-table.gperf"
      {"\000I\003\002", 0x00ce},
#line 128 "./uninorm/composition-table.gperf"
      {"\000I\003\007", 0x0130},
#line 317 "./uninorm/composition-table.gperf"
      {"\0043\003\001", 0x0453},
#line 719 "./uninorm/composition-table.gperf"
      {"\037I\003\001", 0x1f4d},
#line 717 "./uninorm/composition-table.gperf"
      {"\037I\003\000", 0x1f4b},
#line 319 "./uninorm/composition-table.gperf"
      {"\004:\003\001", 0x045c},
#line 528 "./uninorm/composition-table.gperf"
      {"\000v\003\003", 0x1e7d},
#line 689 "./uninorm/composition-table.gperf"
      {"\037)\003\001", 0x1f2d},
#line 687 "./uninorm/composition-table.gperf"
      {"\037)\003\000", 0x1f2b},
#line 691 "./uninorm/composition-table.gperf"
      {"\037)\003B", 0x1f2f},
#line 853 "./uninorm/composition-table.gperf"
      {"\037\366\003E", 0x1ff7},
#line 71 "./uninorm/composition-table.gperf"
      {"\000i\003\010", 0x00ef},
#line 759 "./uninorm/composition-table.gperf"
      {"\037\004\003E", 0x1f84},
#line 835 "./uninorm/composition-table.gperf"
      {"\037\376\003\001", 0x1fde},
#line 834 "./uninorm/composition-table.gperf"
      {"\037\376\003\000", 0x1fdd},
#line 836 "./uninorm/composition-table.gperf"
      {"\037\376\003B", 0x1fdf},
#line 762 "./uninorm/composition-table.gperf"
      {"\037\007\003E", 0x1f87},
#line 712 "./uninorm/composition-table.gperf"
      {"\037@\003\001", 0x1f44},
#line 710 "./uninorm/composition-table.gperf"
      {"\037@\003\000", 0x1f42},
#line 780 "./uninorm/composition-table.gperf"
      {"\037)\003E", 0x1f99},
#line 60 "./uninorm/composition-table.gperf"
      {"\000a\003\003", 0x00e3},
#line 345 "./uninorm/composition-table.gperf"
      {"\004\351\003\010", 0x04eb},
#line 351 "./uninorm/composition-table.gperf"
      {"\004C\003\010", 0x04f1},
#line 449 "./uninorm/composition-table.gperf"
      {"\000\317\003\001", 0x1e2e},
#line 87 "./uninorm/composition-table.gperf"
      {"\000a\003\006", 0x0103},
#line 32 "./uninorm/composition-table.gperf"
      {"\000A\003\001", 0x00c1},
#line 31 "./uninorm/composition-table.gperf"
      {"\000A\003\000", 0x00c0},
#line 89 "./uninorm/composition-table.gperf"
      {"\000a\003(", 0x0105},
#line 33 "./uninorm/composition-table.gperf"
      {"\000A\003\002", 0x00c2},
#line 269 "./uninorm/composition-table.gperf"
      {"\000A\003\007", 0x0226},
#line 45 "./uninorm/composition-table.gperf"
      {"\000I\003\010", 0x00cf},
#line 713 "./uninorm/composition-table.gperf"
      {"\037A\003\001", 0x1f45},
#line 711 "./uninorm/composition-table.gperf"
      {"\037A\003\000", 0x1f43},
#line 354 "./uninorm/composition-table.gperf"
      {"\004'\003\010", 0x04f4},
#line 65 "./uninorm/composition-table.gperf"
      {"\000e\003\001", 0x00e9},
#line 64 "./uninorm/composition-table.gperf"
      {"\000e\003\000", 0x00e8},
#line 121 "./uninorm/composition-table.gperf"
      {"\000i\003\003", 0x0129},
#line 66 "./uninorm/composition-table.gperf"
      {"\000e\003\002", 0x00ea},
#line 105 "./uninorm/composition-table.gperf"
      {"\000e\003\007", 0x0117},
#line 344 "./uninorm/composition-table.gperf"
      {"\004\350\003\010", 0x04ea},
#line 125 "./uninorm/composition-table.gperf"
      {"\000i\003\006", 0x012d},
#line 714 "./uninorm/composition-table.gperf"
      {"\003\237\003\023", 0x1f48},
#line 615 "./uninorm/composition-table.gperf"
      {"\036\315\003\002", 0x1ed9},
#line 127 "./uninorm/composition-table.gperf"
      {"\000i\003(", 0x012f},
#line 368 "./uninorm/composition-table.gperf"
      {"\0113\011<", 0x0934},
#line 668 "./uninorm/composition-table.gperf"
      {"\037\020\003\001", 0x1f14},
#line 666 "./uninorm/composition-table.gperf"
      {"\037\020\003\000", 0x1f12},
#line 576 "./uninorm/composition-table.gperf"
      {"\001\002\003\011", 0x1eb2},
#line 675 "./uninorm/composition-table.gperf"
      {"\037\031\003\001", 0x1f1d},
#line 673 "./uninorm/composition-table.gperf"
      {"\037\031\003\000", 0x1f1b},
#line 577 "./uninorm/composition-table.gperf"
      {"\001\003\003\011", 0x1eb3},
#line 321 "./uninorm/composition-table.gperf"
      {"\004C\003\006", 0x045e},
#line 792 "./uninorm/composition-table.gperf"
      {"\037e\003E", 0x1fa5},
#line 872 "./uninorm/composition-table.gperf"
      {"\000=\0038", 0x2260},
#line 614 "./uninorm/composition-table.gperf"
      {"\036\314\003\002", 0x1ed8},
#line 120 "./uninorm/composition-table.gperf"
      {"\000I\003\003", 0x0128},
#line 432 "./uninorm/composition-table.gperf"
      {"\002)\003\006", 0x1e1d},
#line 596 "./uninorm/composition-table.gperf"
      {"\036\270\003\002", 0x1ec6},
#line 35 "./uninorm/composition-table.gperf"
      {"\000A\003\010", 0x00c4},
#line 124 "./uninorm/composition-table.gperf"
      {"\000I\003\006", 0x012c},
#line 74 "./uninorm/composition-table.gperf"
      {"\000o\003\001", 0x00f3},
#line 73 "./uninorm/composition-table.gperf"
      {"\000o\003\000", 0x00f2},
#line 126 "./uninorm/composition-table.gperf"
      {"\000I\003(", 0x012e},
#line 75 "./uninorm/composition-table.gperf"
      {"\000o\003\002", 0x00f4},
#line 278 "./uninorm/composition-table.gperf"
      {"\000o\003\007", 0x022f},
#line 240 "./uninorm/composition-table.gperf"
      {"\000a\003\017", 0x0201},
#line 225 "./uninorm/composition-table.gperf"
      {"\001\353\003\004", 0x01ed},
#line 67 "./uninorm/composition-table.gperf"
      {"\000e\003\010", 0x00eb},
#line 217 "./uninorm/composition-table.gperf"
      {"\000\346\003\004", 0x01e3},
#line 79 "./uninorm/composition-table.gperf"
      {"\000u\003\001", 0x00fa},
#line 78 "./uninorm/composition-table.gperf"
      {"\000u\003\000", 0x00f9},
#line 765 "./uninorm/composition-table.gperf"
      {"\037\012\003E", 0x1f8a},
#line 80 "./uninorm/composition-table.gperf"
      {"\000u\003\002", 0x00fb},
#line 96 "./uninorm/composition-table.gperf"
      {"\000C\003\014", 0x010c},
#line 215 "./uninorm/composition-table.gperf"
      {"\002'\003\004", 0x01e1},
#line 696 "./uninorm/composition-table.gperf"
      {"\0370\003\001", 0x1f34},
#line 694 "./uninorm/composition-table.gperf"
      {"\0370\003\000", 0x1f32},
#line 698 "./uninorm/composition-table.gperf"
      {"\0370\003B", 0x1f36},
#line 802 "./uninorm/composition-table.gperf"
      {"\037o\003E", 0x1faf},
#line 561 "./uninorm/composition-table.gperf"
      {"\000a\003\011", 0x1ea3},
#line 335 "./uninorm/composition-table.gperf"
      {"\0046\003\010", 0x04dd},
#line 248 "./uninorm/composition-table.gperf"
      {"\000i\003\017", 0x0209},
#line 273 "./uninorm/composition-table.gperf"
      {"\000\326\003\004", 0x022a},
#line 34 "./uninorm/composition-table.gperf"
      {"\000A\003\003", 0x00c3},
#line 213 "./uninorm/composition-table.gperf"
      {"\000\344\003\004", 0x01df},
#line 333 "./uninorm/composition-table.gperf"
      {"\004\331\003\010", 0x04db},
#line 760 "./uninorm/composition-table.gperf"
      {"\037\005\003E", 0x1f85},
#line 86 "./uninorm/composition-table.gperf"
      {"\000A\003\006", 0x0102},
#line 276 "./uninorm/composition-table.gperf"
      {"\000\365\003\004", 0x022d},
#line 768 "./uninorm/composition-table.gperf"
      {"\037\015\003E", 0x1f8d},
#line 88 "./uninorm/composition-table.gperf"
      {"\000A\003(", 0x0104},
#line 781 "./uninorm/composition-table.gperf"
      {"\037*\003E", 0x1f9a},
#line 587 "./uninorm/composition-table.gperf"
      {"\000e\003\003", 0x1ebd},
#line 77 "./uninorm/composition-table.gperf"
      {"\000o\003\010", 0x00f6},
#line 85 "./uninorm/composition-table.gperf"
      {"\000a\003\004", 0x0101},
#line 599 "./uninorm/composition-table.gperf"
      {"\000i\003\011", 0x1ec9},
#line 103 "./uninorm/composition-table.gperf"
      {"\000e\003\006", 0x0115},
#line 197 "./uninorm/composition-table.gperf"
      {"\000a\003\014", 0x01ce},
#line 784 "./uninorm/composition-table.gperf"
      {"\037-\003E", 0x1f9d},
#line 107 "./uninorm/composition-table.gperf"
      {"\000e\003(", 0x0119},
#line 247 "./uninorm/composition-table.gperf"
      {"\000I\003\017", 0x0208},
#line 782 "./uninorm/composition-table.gperf"
      {"\037+\003E", 0x1f9b},
#line 81 "./uninorm/composition-table.gperf"
      {"\000u\003\010", 0x00fc},
#line 39 "./uninorm/composition-table.gperf"
      {"\000E\003\001", 0x00c9},
#line 38 "./uninorm/composition-table.gperf"
      {"\000E\003\000", 0x00c8},
#line 204 "./uninorm/composition-table.gperf"
      {"\000\334\003\004", 0x01d5},
#line 40 "./uninorm/composition-table.gperf"
      {"\000E\003\002", 0x00ca},
#line 104 "./uninorm/composition-table.gperf"
      {"\000E\003\007", 0x0116},
#line 208 "./uninorm/composition-table.gperf"
      {"\000\334\003\014", 0x01d9},
#line 325 "./uninorm/composition-table.gperf"
      {"\0046\003\006", 0x04c2},
#line 123 "./uninorm/composition-table.gperf"
      {"\000i\003\004", 0x012b},
#line 342 "./uninorm/composition-table.gperf"
      {"\004\036\003\010", 0x04e6},
#line 849 "./uninorm/composition-table.gperf"
      {"\037|\003E", 0x1ff2},
#line 199 "./uninorm/composition-table.gperf"
      {"\000i\003\014", 0x01d0},
#line 598 "./uninorm/composition-table.gperf"
      {"\000I\003\011", 0x1ec8},
#line 337 "./uninorm/composition-table.gperf"
      {"\0047\003\010", 0x04df},
#line 48 "./uninorm/composition-table.gperf"
      {"\000O\003\001", 0x00d3},
#line 47 "./uninorm/composition-table.gperf"
      {"\000O\003\000", 0x00d2},
#line 76 "./uninorm/composition-table.gperf"
      {"\000o\003\003", 0x00f5},
#line 49 "./uninorm/composition-table.gperf"
      {"\000O\003\002", 0x00d4},
#line 277 "./uninorm/composition-table.gperf"
      {"\000O\003\007", 0x022e},
#line 349 "./uninorm/composition-table.gperf"
      {"\004C\003\004", 0x04ef},
#line 148 "./uninorm/composition-table.gperf"
      {"\000o\003\006", 0x014f},
#line 328 "./uninorm/composition-table.gperf"
      {"\004\020\003\010", 0x04d2},
#line 274 "./uninorm/composition-table.gperf"
      {"\000\366\003\004", 0x022b},
#line 223 "./uninorm/composition-table.gperf"
      {"\000o\003(", 0x01eb},
#line 932 "./uninorm/composition-table.gperf"
      {"0\2630\231", 0x30b4},
#line 170 "./uninorm/composition-table.gperf"
      {"\000u\003\003", 0x0169},
#line 239 "./uninorm/composition-table.gperf"
      {"\000A\003\017", 0x0200},
#line 122 "./uninorm/composition-table.gperf"
      {"\000I\003\004", 0x012a},
#line 924 "./uninorm/composition-table.gperf"
      {"0{0\231", 0x307c},
#line 174 "./uninorm/composition-table.gperf"
      {"\000u\003\006", 0x016d},
#line 198 "./uninorm/composition-table.gperf"
      {"\000I\003\014", 0x01cf},
#line 926 "./uninorm/composition-table.gperf"
      {"0F0\231", 0x3094},
#line 180 "./uninorm/composition-table.gperf"
      {"\000u\003(", 0x0173},
#line 958 "./uninorm/composition-table.gperf"
      {"0\3750\231", 0x30fe},
#line 41 "./uninorm/composition-table.gperf"
      {"\000E\003\010", 0x00cb},
#line 244 "./uninorm/composition-table.gperf"
      {"\000e\003\017", 0x0205},
#line 53 "./uninorm/composition-table.gperf"
      {"\000U\003\001", 0x00da},
#line 52 "./uninorm/composition-table.gperf"
      {"\000U\003\000", 0x00d9},
#line 530 "./uninorm/composition-table.gperf"
      {"\000v\003#", 0x1e7f},
#line 54 "./uninorm/composition-table.gperf"
      {"\000U\003\002", 0x00db},
#line 560 "./uninorm/composition-table.gperf"
      {"\000A\003\011", 0x1ea2},
#line 298 "./uninorm/composition-table.gperf"
      {"\003\313\003\001", 0x03b0},
#line 839 "./uninorm/composition-table.gperf"
      {"\003\313\003\000", 0x1fe2},
#line 843 "./uninorm/composition-table.gperf"
      {"\003\313\003B", 0x1fe7},
#line 775 "./uninorm/composition-table.gperf"
      {"\037$\003E", 0x1f94},
#line 912 "./uninorm/composition-table.gperf"
      {"0a0\231", 0x3062},
#line 957 "./uninorm/composition-table.gperf"
      {"0\3620\231", 0x30fa},
#line 51 "./uninorm/composition-table.gperf"
      {"\000O\003\010", 0x00d6},
#line 388 "./uninorm/composition-table.gperf"
      {"\015\331\015\317", 0x0ddc},
#line 585 "./uninorm/composition-table.gperf"
      {"\000e\003\011", 0x1ebb},
#line 326 "./uninorm/composition-table.gperf"
      {"\004\020\003\006", 0x04d0},
#line 329 "./uninorm/composition-table.gperf"
      {"\0040\003\010", 0x04d3},
#line 559 "./uninorm/composition-table.gperf"
      {"\000a\003#", 0x1ea1},
#line 82 "./uninorm/composition-table.gperf"
      {"\000y\003\001", 0x00fd},
#line 641 "./uninorm/composition-table.gperf"
      {"\000y\003\000", 0x1ef3},
#line 84 "./uninorm/composition-table.gperf"
      {"\000A\003\004", 0x0100},
#line 184 "./uninorm/composition-table.gperf"
      {"\000y\003\002", 0x0177},
#line 546 "./uninorm/composition-table.gperf"
      {"\000y\003\007", 0x1e8f},
#line 196 "./uninorm/composition-table.gperf"
      {"\000A\003\014", 0x01cd},
#line 586 "./uninorm/composition-table.gperf"
      {"\000E\003\003", 0x1ebc},
#line 367 "./uninorm/composition-table.gperf"
      {"\0110\011<", 0x0931},
#line 252 "./uninorm/composition-table.gperf"
      {"\000o\003\017", 0x020d},
#line 346 "./uninorm/composition-table.gperf"
      {"\004-\003\010", 0x04ec},
#line 102 "./uninorm/composition-table.gperf"
      {"\000E\003\006", 0x0114},
#line 101 "./uninorm/composition-table.gperf"
      {"\000e\003\004", 0x0113},
#line 356 "./uninorm/composition-table.gperf"
      {"\004+\003\010", 0x04f8},
#line 106 "./uninorm/composition-table.gperf"
      {"\000E\003(", 0x0118},
#line 109 "./uninorm/composition-table.gperf"
      {"\000e\003\014", 0x011b},
#line 601 "./uninorm/composition-table.gperf"
      {"\000i\003#", 0x1ecb},
#line 55 "./uninorm/composition-table.gperf"
      {"\000U\003\010", 0x00dc},
#line 260 "./uninorm/composition-table.gperf"
      {"\000u\003\017", 0x0215},
#line 227 "./uninorm/composition-table.gperf"
      {"\002\222\003\014", 0x01ef},
#line 50 "./uninorm/composition-table.gperf"
      {"\000O\003\003", 0x00d5},
#line 954 "./uninorm/composition-table.gperf"
      {"0\3570\231", 0x30f7},
#line 510 "./uninorm/composition-table.gperf"
      {"\000t\003\007", 0x1e6b},
#line 605 "./uninorm/composition-table.gperf"
      {"\000o\003\011", 0x1ecf},
#line 147 "./uninorm/composition-table.gperf"
      {"\000O\003\006", 0x014e},
#line 425 "./uninorm/composition-table.gperf"
      {"\001\022\003\001", 0x1e16},
#line 423 "./uninorm/composition-table.gperf"
      {"\001\022\003\000", 0x1e14},
#line 222 "./uninorm/composition-table.gperf"
      {"\000O\003(", 0x01ea},
#line 327 "./uninorm/composition-table.gperf"
      {"\0040\003\006", 0x04d1},
#line 928 "./uninorm/composition-table.gperf"
      {"0\2530\231", 0x30ac},
#line 876 "./uninorm/composition-table.gperf"
      {"\000>\0038", 0x226f},
#line 266 "./uninorm/composition-table.gperf"
      {"\000t\003&", 0x021b},
#line 629 "./uninorm/composition-table.gperf"
      {"\000u\003\011", 0x1ee7},
#line 152 "./uninorm/composition-table.gperf"
      {"\000r\003\001", 0x0155},
#line 83 "./uninorm/composition-table.gperf"
      {"\000y\003\010", 0x00ff},
#line 600 "./uninorm/composition-table.gperf"
      {"\000I\003#", 0x1eca},
#line 815 "./uninorm/composition-table.gperf"
      {"\037t\003E", 0x1fc2},
#line 492 "./uninorm/composition-table.gperf"
      {"\000r\003\007", 0x1e59},
#line 146 "./uninorm/composition-table.gperf"
      {"\000o\003\004", 0x014d},
#line 434 "./uninorm/composition-table.gperf"
      {"\000f\003\007", 0x1e1f},
#line 761 "./uninorm/composition-table.gperf"
      {"\037\006\003E", 0x1f86},
#line 201 "./uninorm/composition-table.gperf"
      {"\000o\003\014", 0x01d2},
#line 169 "./uninorm/composition-table.gperf"
      {"\000U\003\003", 0x0168},
#line 956 "./uninorm/composition-table.gperf"
      {"0\3610\231", 0x30f9},
#line 140 "./uninorm/composition-table.gperf"
      {"\000n\003\001", 0x0144},
#line 232 "./uninorm/composition-table.gperf"
      {"\000n\003\000", 0x01f9},
#line 173 "./uninorm/composition-table.gperf"
      {"\000U\003\006", 0x016c},
#line 172 "./uninorm/composition-table.gperf"
      {"\000u\003\004", 0x016b},
#line 472 "./uninorm/composition-table.gperf"
      {"\000n\003\007", 0x1e45},
#line 179 "./uninorm/composition-table.gperf"
      {"\000U\003(", 0x0172},
#line 203 "./uninorm/composition-table.gperf"
      {"\000u\003\014", 0x01d4},
#line 554 "./uninorm/composition-table.gperf"
      {"\000t\003\010", 0x1e97},
#line 243 "./uninorm/composition-table.gperf"
      {"\000E\003\017", 0x0204},
#line 793 "./uninorm/composition-table.gperf"
      {"\037f\003E", 0x1fa6},
#line 943 "./uninorm/composition-table.gperf"
      {"0\3170\231", 0x30d0},
#line 785 "./uninorm/composition-table.gperf"
      {"\037.\003E", 0x1f9e},
#line 414 "./uninorm/composition-table.gperf"
      {"\000d\003\007", 0x1e0b},
#line 242 "./uninorm/composition-table.gperf"
      {"\000a\003\021", 0x0203},
#line 459 "./uninorm/composition-table.gperf"
      {"\0366\003\004", 0x1e38},
#line 647 "./uninorm/composition-table.gperf"
      {"\000y\003\003", 0x1ef9},
#line 426 "./uninorm/composition-table.gperf"
      {"\001\023\003\001", 0x1e17},
#line 424 "./uninorm/composition-table.gperf"
      {"\001\023\003\000", 0x1e15},
#line 801 "./uninorm/composition-table.gperf"
      {"\037n\003E", 0x1fae},
#line 558 "./uninorm/composition-table.gperf"
      {"\000A\003#", 0x1ea0},
#line 343 "./uninorm/composition-table.gperf"
      {"\004>\003\010", 0x04e7},
#line 251 "./uninorm/composition-table.gperf"
      {"\000O\003\017", 0x020c},
#line 584 "./uninorm/composition-table.gperf"
      {"\000E\003\011", 0x1eba},
#line 955 "./uninorm/composition-table.gperf"
      {"0\3600\231", 0x30f8},
#line 766 "./uninorm/composition-table.gperf"
      {"\037\013\003E", 0x1f8b},
#line 323 "./uninorm/composition-table.gperf"
      {"\004u\003\017", 0x0477},
#line 791 "./uninorm/composition-table.gperf"
      {"\037d\003E", 0x1fa4},
#line 875 "./uninorm/composition-table.gperf"
      {"\000<\0038", 0x226e},
#line 583 "./uninorm/composition-table.gperf"
      {"\000e\003#", 0x1eb9},
#line 250 "./uninorm/composition-table.gperf"
      {"\000i\003\021", 0x020b},
#line 118 "./uninorm/composition-table.gperf"
      {"\000H\003\002", 0x0124},
#line 437 "./uninorm/composition-table.gperf"
      {"\000H\003\007", 0x1e22},
#line 62 "./uninorm/composition-table.gperf"
      {"\000a\003\012", 0x00e5},
#line 718 "./uninorm/composition-table.gperf"
      {"\037H\003\001", 0x1f4c},
#line 716 "./uninorm/composition-table.gperf"
      {"\037H\003\000", 0x1f4a},
#line 604 "./uninorm/composition-table.gperf"
      {"\000O\003\011", 0x1ece},
#line 390 "./uninorm/composition-table.gperf"
      {"\015\331\015\337", 0x0dde},
#line 100 "./uninorm/composition-table.gperf"
      {"\000E\003\004", 0x0112},
#line 56 "./uninorm/composition-table.gperf"
      {"\000Y\003\001", 0x00dd},
#line 640 "./uninorm/composition-table.gperf"
      {"\000Y\003\000", 0x1ef2},
#line 108 "./uninorm/composition-table.gperf"
      {"\000E\003\014", 0x011a},
#line 183 "./uninorm/composition-table.gperf"
      {"\000Y\003\002", 0x0176},
#line 545 "./uninorm/composition-table.gperf"
      {"\000Y\003\007", 0x1e8e},
#line 259 "./uninorm/composition-table.gperf"
      {"\000U\003\017", 0x0214},
#line 730 "./uninorm/composition-table.gperf"
      {"\037Y\003\001", 0x1f5d},
#line 729 "./uninorm/composition-table.gperf"
      {"\037Y\003\000", 0x1f5b},
#line 731 "./uninorm/composition-table.gperf"
      {"\037Y\003B", 0x1f5f},
#line 916 "./uninorm/composition-table.gperf"
      {"0o0\231", 0x3070},
#line 249 "./uninorm/composition-table.gperf"
      {"\000I\003\021", 0x020a},
#line 460 "./uninorm/composition-table.gperf"
      {"\0367\003\004", 0x1e39},
#line 145 "./uninorm/composition-table.gperf"
      {"\000O\003\004", 0x014c},
#line 479 "./uninorm/composition-table.gperf"
      {"\000\325\003\001", 0x1e4c},
#line 451 "./uninorm/composition-table.gperf"
      {"\000K\003\001", 0x1e30},
#line 200 "./uninorm/composition-table.gperf"
      {"\000O\003\014", 0x01d1},
#line 603 "./uninorm/composition-table.gperf"
      {"\000o\003#", 0x1ecd},
#line 523 "./uninorm/composition-table.gperf"
      {"\001h\003\001", 0x1e78},
#line 920 "./uninorm/composition-table.gperf"
      {"0u0\231", 0x3076},
#line 628 "./uninorm/composition-table.gperf"
      {"\000U\003\011", 0x1ee6},
#line 72 "./uninorm/composition-table.gperf"
      {"\000n\003\003", 0x00f1},
#line 942 "./uninorm/composition-table.gperf"
      {"0\3100\231", 0x30c9},
#line 441 "./uninorm/composition-table.gperf"
      {"\000H\003\010", 0x1e26},
#line 937 "./uninorm/composition-table.gperf"
      {"0\2750\231", 0x30be},
#line 309 "./uninorm/composition-table.gperf"
      {"\004\006\003\010", 0x0407},
#line 627 "./uninorm/composition-table.gperf"
      {"\000u\003#", 0x1ee5},
#line 119 "./uninorm/composition-table.gperf"
      {"\000h\003\002", 0x0125},
#line 438 "./uninorm/composition-table.gperf"
      {"\000h\003\007", 0x1e23},
#line 405 "./uninorm/composition-table.gperf"
      {"\000B\003\007", 0x1e02},
#line 744 "./uninorm/composition-table.gperf"
      {"\037h\003\001", 0x1f6c},
#line 742 "./uninorm/composition-table.gperf"
      {"\037h\003\000", 0x1f6a},
#line 746 "./uninorm/composition-table.gperf"
      {"\037h\003B", 0x1f6e},
#line 936 "./uninorm/composition-table.gperf"
      {"0\2730\231", 0x30bc},
#line 185 "./uninorm/composition-table.gperf"
      {"\000Y\003\010", 0x0178},
#line 171 "./uninorm/composition-table.gperf"
      {"\000U\003\004", 0x016a},
#line 308 "./uninorm/composition-table.gperf"
      {"\004\023\003\001", 0x0403},
#line 645 "./uninorm/composition-table.gperf"
      {"\000y\003\011", 0x1ef7},
#line 202 "./uninorm/composition-table.gperf"
      {"\000U\003\014", 0x01d3},
#line 241 "./uninorm/composition-table.gperf"
      {"\000A\003\021", 0x0202},
#line 37 "./uninorm/composition-table.gperf"
      {"\000C\003'", 0x00c7},
#line 773 "./uninorm/composition-table.gperf"
      {"\037\"\003E", 0x1f92},
#line 795 "./uninorm/composition-table.gperf"
      {"\037h\003E", 0x1fa8},
#line 411 "./uninorm/composition-table.gperf"
      {"\000\307\003\001", 0x1e08},
#line 688 "./uninorm/composition-table.gperf"
      {"\037(\003\001", 0x1f2c},
#line 686 "./uninorm/composition-table.gperf"
      {"\037(\003\000", 0x1f2a},
#line 690 "./uninorm/composition-table.gperf"
      {"\037(\003B", 0x1f2e},
#line 481 "./uninorm/composition-table.gperf"
      {"\000\325\003\010", 0x1e4e},
#line 246 "./uninorm/composition-table.gperf"
      {"\000e\003\021", 0x0207},
#line 697 "./uninorm/composition-table.gperf"
      {"\0371\003\001", 0x1f35},
#line 695 "./uninorm/composition-table.gperf"
      {"\0371\003\000", 0x1f33},
#line 699 "./uninorm/composition-table.gperf"
      {"\0371\003B", 0x1f37},
#line 282 "./uninorm/composition-table.gperf"
      {"\000y\003\004", 0x0233},
#line 304 "./uninorm/composition-table.gperf"
      {"\003\322\003\001", 0x03d3},
#line 428 "./uninorm/composition-table.gperf"
      {"\000e\003-", 0x1e19},
#line 256 "./uninorm/composition-table.gperf"
      {"\000r\003\017", 0x0211},
#line 779 "./uninorm/composition-table.gperf"
      {"\037(\003E", 0x1f98},
#line 442 "./uninorm/composition-table.gperf"
      {"\000h\003\010", 0x1e27},
#line 36 "./uninorm/composition-table.gperf"
      {"\000A\003\012", 0x00c5},
#line 646 "./uninorm/composition-table.gperf"
      {"\000Y\003\003", 0x1ef8},
#line 582 "./uninorm/composition-table.gperf"
      {"\000E\003#", 0x1eb8},
#line 533 "./uninorm/composition-table.gperf"
      {"\000W\003\001", 0x1e82},
#line 531 "./uninorm/composition-table.gperf"
      {"\000W\003\000", 0x1e80},
#line 151 "./uninorm/composition-table.gperf"
      {"\000R\003\001", 0x0154},
#line 181 "./uninorm/composition-table.gperf"
      {"\000W\003\002", 0x0174},
#line 537 "./uninorm/composition-table.gperf"
      {"\000W\003\007", 0x1e86},
#line 903 "./uninorm/composition-table.gperf"
      {"0O0\231", 0x3050},
#line 491 "./uninorm/composition-table.gperf"
      {"\000R\003\007", 0x1e58},
#line 869 "./uninorm/composition-table.gperf"
      {"\"C\0038", 0x2244},
#line 863 "./uninorm/composition-table.gperf"
      {"\"\003\0038", 0x2204},
#line 864 "./uninorm/composition-table.gperf"
      {"\"\010\0038", 0x2209},
#line 898 "./uninorm/composition-table.gperf"
      {"\"\263\0038", 0x22eb},
#line 168 "./uninorm/composition-table.gperf"
      {"\000t\003\014", 0x0165},
#line 602 "./uninorm/composition-table.gperf"
      {"\000O\003#", 0x1ecc},
#line 254 "./uninorm/composition-table.gperf"
      {"\000o\003\021", 0x020f},
#line 884 "./uninorm/composition-table.gperf"
      {"\"{\0038", 0x2281},
#line 229 "./uninorm/composition-table.gperf"
      {"\000G\003\001", 0x01f4},
#line 389 "./uninorm/composition-table.gperf"
      {"\015\334\015\312", 0x0ddd},
#line 881 "./uninorm/composition-table.gperf"
      {"\"v\0038", 0x2278},
#line 110 "./uninorm/composition-table.gperf"
      {"\000G\003\002", 0x011c},
#line 114 "./uninorm/composition-table.gperf"
      {"\000G\003\007", 0x0120},
#line 279 "./uninorm/composition-table.gperf"
      {"\002.\003\004", 0x0230},
#line 899 "./uninorm/composition-table.gperf"
      {"\"\264\0038", 0x22ec},
#line 262 "./uninorm/composition-table.gperf"
      {"\000u\003\021", 0x0217},
#line 715 "./uninorm/composition-table.gperf"
      {"\003\237\003\024", 0x1f49},
#line 448 "./uninorm/composition-table.gperf"
      {"\000i\0030", 0x1e2d},
#line 305 "./uninorm/composition-table.gperf"
      {"\003\322\003\010", 0x03d4},
#line 156 "./uninorm/composition-table.gperf"
      {"\000r\003\014", 0x0159},
#line 906 "./uninorm/composition-table.gperf"
      {"0U0\231", 0x3056},
#line 522 "./uninorm/composition-table.gperf"
      {"\000u\003-", 0x1e77},
#line 306 "./uninorm/composition-table.gperf"
      {"\004\025\003\000", 0x0400},
#line 322 "./uninorm/composition-table.gperf"
      {"\004t\003\017", 0x0476},
#line 873 "./uninorm/composition-table.gperf"
      {"\"a\0038", 0x2262},
#line 431 "./uninorm/composition-table.gperf"
      {"\002(\003\006", 0x1e1c},
#line 535 "./uninorm/composition-table.gperf"
      {"\000W\003\010", 0x1e84},
#line 626 "./uninorm/composition-table.gperf"
      {"\000U\003#", 0x1ee4},
#line 139 "./uninorm/composition-table.gperf"
      {"\000N\003\001", 0x0143},
#line 231 "./uninorm/composition-table.gperf"
      {"\000N\003\000", 0x01f8},
#line 144 "./uninorm/composition-table.gperf"
      {"\000n\003\014", 0x0148},
#line 357 "./uninorm/composition-table.gperf"
      {"\004K\003\010", 0x04f9},
#line 471 "./uninorm/composition-table.gperf"
      {"\000N\003\007", 0x1e44},
#line 129 "./uninorm/composition-table.gperf"
      {"\000J\003\002", 0x0134},
#line 176 "./uninorm/composition-table.gperf"
      {"\000u\003\012", 0x016f},
#line 897 "./uninorm/composition-table.gperf"
      {"\"\262\0038", 0x22ea},
#line 447 "./uninorm/composition-table.gperf"
      {"\000I\0030", 0x1e2c},
#line 387 "./uninorm/composition-table.gperf"
      {"\015\331\015\312", 0x0dda},
#line 99 "./uninorm/composition-table.gperf"
      {"\000d\003\014", 0x010f},
#line 534 "./uninorm/composition-table.gperf"
      {"\000w\003\001", 0x1e83},
#line 532 "./uninorm/composition-table.gperf"
      {"\000w\003\000", 0x1e81},
#line 514 "./uninorm/composition-table.gperf"
      {"\000t\0031", 0x1e6f},
#line 182 "./uninorm/composition-table.gperf"
      {"\000w\003\002", 0x0175},
#line 538 "./uninorm/composition-table.gperf"
      {"\000w\003\007", 0x1e87},
#line 643 "./uninorm/composition-table.gperf"
      {"\000y\003#", 0x1ef5},
#line 295 "./uninorm/composition-table.gperf"
      {"\003\265\003\001", 0x03ad},
#line 749 "./uninorm/composition-table.gperf"
      {"\003\265\003\000", 0x1f72},
#line 929 "./uninorm/composition-table.gperf"
      {"0\2550\231", 0x30ae},
#line 230 "./uninorm/composition-table.gperf"
      {"\000g\003\001", 0x01f5},
#line 245 "./uninorm/composition-table.gperf"
      {"\000E\003\021", 0x0206},
#line 644 "./uninorm/composition-table.gperf"
      {"\000Y\003\011", 0x1ef6},
#line 111 "./uninorm/composition-table.gperf"
      {"\000g\003\002", 0x011d},
#line 115 "./uninorm/composition-table.gperf"
      {"\000g\003\007", 0x0121},
#line 953 "./uninorm/composition-table.gperf"
      {"0\2460\231", 0x30f4},
#line 307 "./uninorm/composition-table.gperf"
      {"\004\025\003\010", 0x0401},
#line 427 "./uninorm/composition-table.gperf"
      {"\000E\003-", 0x1e18},
#line 498 "./uninorm/composition-table.gperf"
      {"\000r\0031", 0x1e5f},
#line 267 "./uninorm/composition-table.gperf"
      {"\000H\003\014", 0x021e},
#line 485 "./uninorm/composition-table.gperf"
      {"\001L\003\001", 0x1e52},
#line 483 "./uninorm/composition-table.gperf"
      {"\001L\003\000", 0x1e50},
#line 892 "./uninorm/composition-table.gperf"
      {"\"\253\0038", 0x22af},
#line 512 "./uninorm/composition-table.gperf"
      {"\000t\003#", 0x1e6d},
#line 253 "./uninorm/composition-table.gperf"
      {"\000O\003\021", 0x020e},
#line 366 "./uninorm/composition-table.gperf"
      {"\011(\011<", 0x0929},
#line 133 "./uninorm/composition-table.gperf"
      {"\000L\003\001", 0x0139},
#line 281 "./uninorm/composition-table.gperf"
      {"\000Y\003\004", 0x0232},
#line 794 "./uninorm/composition-table.gperf"
      {"\037g\003E", 0x1fa7},
#line 476 "./uninorm/composition-table.gperf"
      {"\000n\0031", 0x1e49},
#line 272 "./uninorm/composition-table.gperf"
      {"\000e\003'", 0x0229},
#line 918 "./uninorm/composition-table.gperf"
      {"0r0\231", 0x3073},
#line 112 "./uninorm/composition-table.gperf"
      {"\000G\003\006", 0x011e},
#line 914 "./uninorm/composition-table.gperf"
      {"0f0\231", 0x3067},
#line 536 "./uninorm/composition-table.gperf"
      {"\000w\003\010", 0x1e85},
#line 430 "./uninorm/composition-table.gperf"
      {"\000e\0030", 0x1e1b},
#line 951 "./uninorm/composition-table.gperf"
      {"0\3330\231", 0x30dc},
#line 418 "./uninorm/composition-table.gperf"
      {"\000d\0031", 0x1e0f},
#line 494 "./uninorm/composition-table.gperf"
      {"\000r\003#", 0x1e5b},
#line 889 "./uninorm/composition-table.gperf"
      {"\"\242\0038", 0x22ac},
#line 275 "./uninorm/composition-table.gperf"
      {"\000\325\003\004", 0x022c},
#line 486 "./uninorm/composition-table.gperf"
      {"\001M\003\001", 0x1e53},
#line 484 "./uninorm/composition-table.gperf"
      {"\001M\003\000", 0x1e51},
#line 359 "./uninorm/composition-table.gperf"
      {"\006'\006T", 0x0623},
#line 220 "./uninorm/composition-table.gperf"
      {"\000K\003\014", 0x01e8},
#line 330 "./uninorm/composition-table.gperf"
      {"\004\025\003\006", 0x04d6},
#line 261 "./uninorm/composition-table.gperf"
      {"\000U\003\021", 0x0216},
#line 465 "./uninorm/composition-table.gperf"
      {"\000M\003\001", 0x1e3e},
#line 46 "./uninorm/composition-table.gperf"
      {"\000N\003\003", 0x00d1},
#line 474 "./uninorm/composition-table.gperf"
      {"\000n\003#", 0x1e47},
#line 913 "./uninorm/composition-table.gperf"
      {"0d0\231", 0x3065},
#line 467 "./uninorm/composition-table.gperf"
      {"\000M\003\007", 0x1e40},
#line 521 "./uninorm/composition-table.gperf"
      {"\000U\003-", 0x1e76},
#line 268 "./uninorm/composition-table.gperf"
      {"\000h\003\014", 0x021f},
#line 355 "./uninorm/composition-table.gperf"
      {"\004G\003\010", 0x04f5},
#line 509 "./uninorm/composition-table.gperf"
      {"\000T\003\007", 0x1e6a},
#line 212 "./uninorm/composition-table.gperf"
      {"\000\304\003\004", 0x01de},
#line 416 "./uninorm/composition-table.gperf"
      {"\000d\003#", 0x1e0d},
#line 878 "./uninorm/composition-table.gperf"
      {"\"e\0038", 0x2271},
#line 542 "./uninorm/composition-table.gperf"
      {"\000x\003\007", 0x1e8b},
#line 255 "./uninorm/composition-table.gperf"
      {"\000R\003\017", 0x0210},
#line 283 "./uninorm/composition-table.gperf"
      {"\000\250\003\001", 0x0385},
#line 848 "./uninorm/composition-table.gperf"
      {"\000\250\003\000", 0x1fed},
#line 814 "./uninorm/composition-table.gperf"
      {"\000\250\003B", 0x1fc1},
#line 265 "./uninorm/composition-table.gperf"
      {"\000T\003&", 0x021a},
#line 175 "./uninorm/composition-table.gperf"
      {"\000U\003\012", 0x016e},
#line 664 "./uninorm/composition-table.gperf"
      {"\003\265\003\023", 0x1f10},
#line 301 "./uninorm/composition-table.gperf"
      {"\003\277\003\001", 0x03cc},
#line 752 "./uninorm/composition-table.gperf"
      {"\003\277\003\000", 0x1f78},
#line 896 "./uninorm/composition-table.gperf"
      {"\"\222\0038", 0x22e3},
#line 520 "./uninorm/composition-table.gperf"
      {"\000u\0030", 0x1e75},
#line 927 "./uninorm/composition-table.gperf"
      {"0\2350\231", 0x309e},
#line 113 "./uninorm/composition-table.gperf"
      {"\000g\003\006", 0x011f},
#line 297 "./uninorm/composition-table.gperf"
      {"\003\271\003\001", 0x03af},
#line 751 "./uninorm/composition-table.gperf"
      {"\003\271\003\000", 0x1f76},
#line 829 "./uninorm/composition-table.gperf"
      {"\003\271\003B", 0x1fd6},
#line 439 "./uninorm/composition-table.gperf"
      {"\000H\003#", 0x1e24},
#line 824 "./uninorm/composition-table.gperf"
      {"\037\277\003\001", 0x1fce},
#line 823 "./uninorm/composition-table.gperf"
      {"\037\277\003\000", 0x1fcd},
#line 825 "./uninorm/composition-table.gperf"
      {"\037\277\003B", 0x1fcf},
#line 908 "./uninorm/composition-table.gperf"
      {"0Y0\231", 0x305a},
#line 455 "./uninorm/composition-table.gperf"
      {"\000K\0031", 0x1e34},
#line 556 "./uninorm/composition-table.gperf"
      {"\000y\003\012", 0x1e99},
#line 888 "./uninorm/composition-table.gperf"
      {"\"\207\0038", 0x2289},
#line 284 "./uninorm/composition-table.gperf"
      {"\003\221\003\001", 0x0386},
#line 812 "./uninorm/composition-table.gperf"
      {"\003\221\003\000", 0x1fba},
#line 516 "./uninorm/composition-table.gperf"
      {"\000t\003-", 0x1e71},
#line 642 "./uninorm/composition-table.gperf"
      {"\000Y\003#", 0x1ef4},
#line 544 "./uninorm/composition-table.gperf"
      {"\000x\003\010", 0x1e8d},
#line 887 "./uninorm/composition-table.gperf"
      {"\"\206\0038", 0x2288},
#line 553 "./uninorm/composition-table.gperf"
      {"\000h\0031", 0x1e96},
#line 409 "./uninorm/composition-table.gperf"
      {"\000B\0031", 0x1e06},
#line 155 "./uninorm/composition-table.gperf"
      {"\000R\003\014", 0x0158},
#line 947 "./uninorm/composition-table.gperf"
      {"0\3250\231", 0x30d6},
#line 901 "./uninorm/composition-table.gperf"
      {"0K0\231", 0x304c},
#line 258 "./uninorm/composition-table.gperf"
      {"\000r\003\021", 0x0213},
#line 813 "./uninorm/composition-table.gperf"
      {"\003\221\003E", 0x1fbc},
#line 384 "./uninorm/composition-table.gperf"
      {"\015F\015>", 0x0d4a},
#line 767 "./uninorm/composition-table.gperf"
      {"\037\014\003E", 0x1f8c},
#line 271 "./uninorm/composition-table.gperf"
      {"\000E\003'", 0x0228},
#line 774 "./uninorm/composition-table.gperf"
      {"\037#\003E", 0x1f93},
#line 453 "./uninorm/composition-table.gperf"
      {"\000K\003#", 0x1e32},
#line 435 "./uninorm/composition-table.gperf"
      {"\000G\003\004", 0x1e20},
#line 915 "./uninorm/composition-table.gperf"
      {"0h0\231", 0x3069},
#line 429 "./uninorm/composition-table.gperf"
      {"\000E\0030", 0x1e1a},
#line 218 "./uninorm/composition-table.gperf"
      {"\000G\003\014", 0x01e6},
#line 299 "./uninorm/composition-table.gperf"
      {"\003\271\003\010", 0x03ca},
#line 617 "./uninorm/composition-table.gperf"
      {"\001\241\003\001", 0x1edb},
#line 619 "./uninorm/composition-table.gperf"
      {"\001\241\003\000", 0x1edd},
#line 940 "./uninorm/composition-table.gperf"
      {"0\3040\231", 0x30c5},
#line 440 "./uninorm/composition-table.gperf"
      {"\000h\003#", 0x1e25},
#line 407 "./uninorm/composition-table.gperf"
      {"\000B\003#", 0x1e04},
#line 478 "./uninorm/composition-table.gperf"
      {"\000n\003-", 0x1e4b},
#line 886 "./uninorm/composition-table.gperf"
      {"\"\203\0038", 0x2285},
#line 925 "./uninorm/composition-table.gperf"
      {"0{0\232", 0x307d},
#line 302 "./uninorm/composition-table.gperf"
      {"\003\305\003\001", 0x03cd},
#line 753 "./uninorm/composition-table.gperf"
      {"\003\305\003\000", 0x1f7a},
#line 842 "./uninorm/composition-table.gperf"
      {"\003\305\003B", 0x1fe6},
#line 893 "./uninorm/composition-table.gperf"
      {"\"|\0038", 0x22e0},
#line 233 "./uninorm/composition-table.gperf"
      {"\000\305\003\001", 0x01fa},
#line 422 "./uninorm/composition-table.gperf"
      {"\000d\003-", 0x1e13},
#line 885 "./uninorm/composition-table.gperf"
      {"\"\202\0038", 0x2284},
#line 294 "./uninorm/composition-table.gperf"
      {"\003\261\003\001", 0x03ac},
#line 748 "./uninorm/composition-table.gperf"
      {"\003\261\003\000", 0x1f70},
#line 808 "./uninorm/composition-table.gperf"
      {"\003\261\003B", 0x1fb6},
#line 143 "./uninorm/composition-table.gperf"
      {"\000N\003\014", 0x0147},
#line 708 "./uninorm/composition-table.gperf"
      {"\003\277\003\023", 0x1f40},
#line 870 "./uninorm/composition-table.gperf"
      {"\"E\0038", 0x2247},
#line 894 "./uninorm/composition-table.gperf"
      {"\"}\0038", 0x22e1},
#line 497 "./uninorm/composition-table.gperf"
      {"\000R\0031", 0x1e5e},
#line 413 "./uninorm/composition-table.gperf"
      {"\000D\003\007", 0x1e0a},
#line 347 "./uninorm/composition-table.gperf"
      {"\004M\003\010", 0x04ed},
#line 692 "./uninorm/composition-table.gperf"
      {"\003\271\003\023", 0x1f30},
#line 353 "./uninorm/composition-table.gperf"
      {"\004C\003\013", 0x04f3},
#line 806 "./uninorm/composition-table.gperf"
      {"\003\261\003E", 0x1fb3},
#line 826 "./uninorm/composition-table.gperf"
      {"\003\271\003\006", 0x1fd0},
#line 945 "./uninorm/composition-table.gperf"
      {"0\3220\231", 0x30d3},
#line 134 "./uninorm/composition-table.gperf"
      {"\000l\003\001", 0x013a},
#line 911 "./uninorm/composition-table.gperf"
      {"0_0\231", 0x3060},
#line 519 "./uninorm/composition-table.gperf"
      {"\000U\0030", 0x1e74},
#line 907 "./uninorm/composition-table.gperf"
      {"0W0\231", 0x3058},
#line 910 "./uninorm/composition-table.gperf"
      {"0]0\231", 0x305e},
#line 436 "./uninorm/composition-table.gperf"
      {"\000g\003\004", 0x1e21},
#line 656 "./uninorm/composition-table.gperf"
      {"\003\221\003\023", 0x1f08},
#line 310 "./uninorm/composition-table.gperf"
      {"\004\032\003\001", 0x040c},
#line 219 "./uninorm/composition-table.gperf"
      {"\000g\003\014", 0x01e7},
#line 810 "./uninorm/composition-table.gperf"
      {"\003\221\003\006", 0x1fb8},
#line 539 "./uninorm/composition-table.gperf"
      {"\000W\003#", 0x1e88},
#line 300 "./uninorm/composition-table.gperf"
      {"\003\305\003\010", 0x03cb},
#line 493 "./uninorm/composition-table.gperf"
      {"\000R\003#", 0x1e5a},
#line 237 "./uninorm/composition-table.gperf"
      {"\000\330\003\001", 0x01fe},
#line 296 "./uninorm/composition-table.gperf"
      {"\003\267\003\001", 0x03ae},
#line 750 "./uninorm/composition-table.gperf"
      {"\003\267\003\000", 0x1f74},
#line 818 "./uninorm/composition-table.gperf"
      {"\003\267\003B", 0x1fc6},
#line 158 "./uninorm/composition-table.gperf"
      {"\000s\003\001", 0x015b},
#line 799 "./uninorm/composition-table.gperf"
      {"\037l\003E", 0x1fac},
#line 157 "./uninorm/composition-table.gperf"
      {"\000S\003\001", 0x015a},
#line 160 "./uninorm/composition-table.gperf"
      {"\000s\003\002", 0x015d},
#line 500 "./uninorm/composition-table.gperf"
      {"\000s\003\007", 0x1e61},
#line 159 "./uninorm/composition-table.gperf"
      {"\000S\003\002", 0x015c},
#line 499 "./uninorm/composition-table.gperf"
      {"\000S\003\007", 0x1e60},
#line 137 "./uninorm/composition-table.gperf"
      {"\000L\003\014", 0x013d},
#line 475 "./uninorm/composition-table.gperf"
      {"\000N\0031", 0x1e48},
#line 816 "./uninorm/composition-table.gperf"
      {"\003\267\003E", 0x1fc3},
#line 597 "./uninorm/composition-table.gperf"
      {"\036\271\003\002", 0x1ec7},
#line 623 "./uninorm/composition-table.gperf"
      {"\001\241\003\003", 0x1ee1},
#line 350 "./uninorm/composition-table.gperf"
      {"\004#\003\010", 0x04f0},
#line 264 "./uninorm/composition-table.gperf"
      {"\000s\003&", 0x0219},
#line 166 "./uninorm/composition-table.gperf"
      {"\000t\003'", 0x0163},
#line 263 "./uninorm/composition-table.gperf"
      {"\000S\003&", 0x0218},
#line 452 "./uninorm/composition-table.gperf"
      {"\000k\003\001", 0x1e31},
#line 291 "./uninorm/composition-table.gperf"
      {"\003\312\003\001", 0x0390},
#line 828 "./uninorm/composition-table.gperf"
      {"\003\312\003\000", 0x1fd2},
#line 830 "./uninorm/composition-table.gperf"
      {"\003\312\003B", 0x1fd7},
#line 720 "./uninorm/composition-table.gperf"
      {"\003\305\003\023", 0x1f50},
#line 588 "./uninorm/composition-table.gperf"
      {"\000\312\003\001", 0x1ebe},
#line 590 "./uninorm/composition-table.gperf"
      {"\000\312\003\000", 0x1ec0},
#line 837 "./uninorm/composition-table.gperf"
      {"\003\305\003\006", 0x1fe0},
#line 616 "./uninorm/composition-table.gperf"
      {"\001\240\003\001", 0x1eda},
#line 618 "./uninorm/composition-table.gperf"
      {"\001\240\003\000", 0x1edc},
#line 840 "./uninorm/composition-table.gperf"
      {"\003\301\003\023", 0x1fe4},
#line 648 "./uninorm/composition-table.gperf"
      {"\003\261\003\023", 0x1f00},
#line 473 "./uninorm/composition-table.gperf"
      {"\000N\003#", 0x1e46},
#line 154 "./uninorm/composition-table.gperf"
      {"\000r\003'", 0x0157},
#line 803 "./uninorm/composition-table.gperf"
      {"\003\261\003\006", 0x1fb0},
#line 503 "./uninorm/composition-table.gperf"
      {"\001Z\003\007", 0x1e64},
#line 167 "./uninorm/composition-table.gperf"
      {"\000T\003\014", 0x0164},
#line 186 "./uninorm/composition-table.gperf"
      {"\000Z\003\001", 0x0179},
#line 798 "./uninorm/composition-table.gperf"
      {"\037k\003E", 0x1fab},
#line 527 "./uninorm/composition-table.gperf"
      {"\000V\003\003", 0x1e7c},
#line 547 "./uninorm/composition-table.gperf"
      {"\000Z\003\002", 0x1e90},
#line 188 "./uninorm/composition-table.gperf"
      {"\000Z\003\007", 0x017b},
#line 944 "./uninorm/composition-table.gperf"
      {"0\3170\232", 0x30d1},
#line 540 "./uninorm/composition-table.gperf"
      {"\000w\003#", 0x1e89},
#line 142 "./uninorm/composition-table.gperf"
      {"\000n\003'", 0x0146},
#line 312 "./uninorm/composition-table.gperf"
      {"\004#\003\006", 0x040e},
#line 933 "./uninorm/composition-table.gperf"
      {"0\2650\231", 0x30b6},
#line 526 "./uninorm/composition-table.gperf"
      {"\001k\003\010", 0x1e7b},
#line 461 "./uninorm/composition-table.gperf"
      {"\000L\0031", 0x1e3a},
#line 868 "./uninorm/composition-table.gperf"
      {"\"<\0038", 0x2241},
#line 571 "./uninorm/composition-table.gperf"
      {"\036\241\003\002", 0x1ead},
#line 786 "./uninorm/composition-table.gperf"
      {"\037/\003E", 0x1f9f},
#line 420 "./uninorm/composition-table.gperf"
      {"\000d\003'", 0x1e11},
#line 336 "./uninorm/composition-table.gperf"
      {"\004\027\003\010", 0x04de},
#line 150 "./uninorm/composition-table.gperf"
      {"\000o\003\013", 0x0151},
#line 827 "./uninorm/composition-table.gperf"
      {"\003\271\003\004", 0x1fd1},
#line 257 "./uninorm/composition-table.gperf"
      {"\000R\003\021", 0x0212},
#line 704 "./uninorm/composition-table.gperf"
      {"\0378\003\001", 0x1f3c},
#line 702 "./uninorm/composition-table.gperf"
      {"\0378\003\000", 0x1f3a},
#line 706 "./uninorm/composition-table.gperf"
      {"\0378\003B", 0x1f3e},
#line 676 "./uninorm/composition-table.gperf"
      {"\003\267\003\023", 0x1f20},
#line 879 "./uninorm/composition-table.gperf"
      {"\"r\0038", 0x2274},
#line 770 "./uninorm/composition-table.gperf"
      {"\037\017\003E", 0x1f8f},
#line 178 "./uninorm/composition-table.gperf"
      {"\000u\003\013", 0x0171},
#line 769 "./uninorm/composition-table.gperf"
      {"\037\016\003E", 0x1f8e},
#line 318 "./uninorm/composition-table.gperf"
      {"\004V\003\010", 0x0457},
#line 811 "./uninorm/composition-table.gperf"
      {"\003\221\003\004", 0x1fb9},
#line 776 "./uninorm/composition-table.gperf"
      {"\037%\003E", 0x1f95},
#line 457 "./uninorm/composition-table.gperf"
      {"\000L\003#", 0x1e36},
#line 290 "./uninorm/composition-table.gperf"
      {"\003\251\003\001", 0x038f},
#line 855 "./uninorm/composition-table.gperf"
      {"\003\251\003\000", 0x1ffa},
#line 443 "./uninorm/composition-table.gperf"
      {"\000H\003'", 0x1e28},
#line 187 "./uninorm/composition-table.gperf"
      {"\000z\003\001", 0x017a},
#line 513 "./uninorm/composition-table.gperf"
      {"\000T\0031", 0x1e6e},
#line 621 "./uninorm/composition-table.gperf"
      {"\001\241\003\011", 0x1edf},
#line 548 "./uninorm/composition-table.gperf"
      {"\000z\003\002", 0x1e91},
#line 189 "./uninorm/composition-table.gperf"
      {"\000z\003\007", 0x017c},
      {""},
#line 865 "./uninorm/composition-table.gperf"
      {"\"\013\0038", 0x220c},
#line 917 "./uninorm/composition-table.gperf"
      {"0o0\232", 0x3071},
#line 877 "./uninorm/composition-table.gperf"
      {"\"d\0038", 0x2270},
#line 856 "./uninorm/composition-table.gperf"
      {"\003\251\003E", 0x1ffc},
#line 902 "./uninorm/composition-table.gperf"
      {"0M0\231", 0x304e},
#line 594 "./uninorm/composition-table.gperf"
      {"\000\312\003\003", 0x1ec4},
#line 332 "./uninorm/composition-table.gperf"
      {"\004\330\003\010", 0x04da},
#line 398 "./uninorm/composition-table.gperf"
      {"\033:\0335", 0x1b3b},
#line 622 "./uninorm/composition-table.gperf"
      {"\001\240\003\003", 0x1ee0},
      {""},
#line 921 "./uninorm/composition-table.gperf"
      {"0u0\232", 0x3077},
#line 469 "./uninorm/composition-table.gperf"
      {"\000M\003#", 0x1e42},
#line 922 "./uninorm/composition-table.gperf"
      {"0x0\231", 0x3079},
#line 287 "./uninorm/composition-table.gperf"
      {"\003\231\003\001", 0x038a},
#line 833 "./uninorm/composition-table.gperf"
      {"\003\231\003\000", 0x1fda},
#line 511 "./uninorm/composition-table.gperf"
      {"\000T\003#", 0x1e6c},
#line 541 "./uninorm/composition-table.gperf"
      {"\000X\003\007", 0x1e8a},
#line 477 "./uninorm/composition-table.gperf"
      {"\000N\003-", 0x1e4a},
#line 131 "./uninorm/composition-table.gperf"
      {"\000K\003'", 0x0136},
#line 838 "./uninorm/composition-table.gperf"
      {"\003\305\003\004", 0x1fe1},
#line 91 "./uninorm/composition-table.gperf"
      {"\000c\003\001", 0x0107},
#line 871 "./uninorm/composition-table.gperf"
      {"\"H\0038", 0x2249},
#line 394 "./uninorm/composition-table.gperf"
      {"\033\011\0335", 0x1b0a},
#line 93 "./uninorm/composition-table.gperf"
      {"\000c\003\002", 0x0109},
#line 95 "./uninorm/composition-table.gperf"
      {"\000c\003\007", 0x010b},
#line 320 "./uninorm/composition-table.gperf"
      {"\0048\003\000", 0x045d},
#line 804 "./uninorm/composition-table.gperf"
      {"\003\261\003\004", 0x1fb1},
#line 444 "./uninorm/composition-table.gperf"
      {"\000h\003'", 0x1e29},
#line 938 "./uninorm/composition-table.gperf"
      {"0\2770\231", 0x30c0},
#line 630 "./uninorm/composition-table.gperf"
      {"\001\257\003\001", 0x1ee8},
#line 632 "./uninorm/composition-table.gperf"
      {"\001\257\003\000", 0x1eea},
#line 581 "./uninorm/composition-table.gperf"
      {"\036\241\003\006", 0x1eb7},
#line 149 "./uninorm/composition-table.gperf"
      {"\000O\003\013", 0x0150},
#line 98 "./uninorm/composition-table.gperf"
      {"\000D\003\014", 0x010e},
#line 935 "./uninorm/composition-table.gperf"
      {"0\2710\231", 0x30ba},
#line 289 "./uninorm/composition-table.gperf"
      {"\003\245\003\001", 0x038e},
#line 846 "./uninorm/composition-table.gperf"
      {"\003\245\003\000", 0x1fea},
#line 348 "./uninorm/composition-table.gperf"
      {"\004#\003\004", 0x04ee},
#line 790 "./uninorm/composition-table.gperf"
      {"\037c\003E", 0x1fa3},
#line 285 "./uninorm/composition-table.gperf"
      {"\003\225\003\001", 0x0388},
#line 820 "./uninorm/composition-table.gperf"
      {"\003\225\003\000", 0x1fc8},
#line 555 "./uninorm/composition-table.gperf"
      {"\000w\003\012", 0x1e98},
#line 235 "./uninorm/composition-table.gperf"
      {"\000\306\003\001", 0x01fc},
#line 570 "./uninorm/composition-table.gperf"
      {"\036\240\003\002", 0x1eac},
#line 138 "./uninorm/composition-table.gperf"
      {"\000l\003\014", 0x013e},
#line 543 "./uninorm/composition-table.gperf"
      {"\000X\003\010", 0x1e8c},
#line 292 "./uninorm/composition-table.gperf"
      {"\003\231\003\010", 0x03aa},
#line 303 "./uninorm/composition-table.gperf"
      {"\003\311\003\001", 0x03ce},
#line 754 "./uninorm/composition-table.gperf"
      {"\003\311\003\000", 0x1f7c},
#line 852 "./uninorm/composition-table.gperf"
      {"\003\311\003B", 0x1ff6},
#line 740 "./uninorm/composition-table.gperf"
      {"\003\251\003\023", 0x1f68},
#line 393 "./uninorm/composition-table.gperf"
      {"\033\007\0335", 0x1b08},
      {""},
#line 463 "./uninorm/composition-table.gperf"
      {"\000L\003-", 0x1e3c},
#line 177 "./uninorm/composition-table.gperf"
      {"\000U\003\013", 0x0170},
      {""},
#line 226 "./uninorm/composition-table.gperf"
      {"\001\267\003\014", 0x01ee},
#line 341 "./uninorm/composition-table.gperf"
      {"\0048\003\010", 0x04e5},
#line 466 "./uninorm/composition-table.gperf"
      {"\000m\003\001", 0x1e3f},
#line 850 "./uninorm/composition-table.gperf"
      {"\003\311\003E", 0x1ff3},
#line 819 "./uninorm/composition-table.gperf"
      {"\037\306\003E", 0x1fc7},
#line 164 "./uninorm/composition-table.gperf"
      {"\000s\003\014", 0x0161},
#line 468 "./uninorm/composition-table.gperf"
      {"\000m\003\007", 0x1e41},
#line 163 "./uninorm/composition-table.gperf"
      {"\000S\003\014", 0x0160},
#line 592 "./uninorm/composition-table.gperf"
      {"\000\312\003\011", 0x1ec2},
#line 504 "./uninorm/composition-table.gperf"
      {"\001[\003\007", 0x1e65},
#line 153 "./uninorm/composition-table.gperf"
      {"\000R\003'", 0x0156},
#line 620 "./uninorm/composition-table.gperf"
      {"\001\240\003\011", 0x1ede},
#line 293 "./uninorm/composition-table.gperf"
      {"\003\245\003\010", 0x03ab},
#line 358 "./uninorm/composition-table.gperf"
      {"\006'\006S", 0x0622},
#line 417 "./uninorm/composition-table.gperf"
      {"\000D\0031", 0x1e0e},
#line 625 "./uninorm/composition-table.gperf"
      {"\001\241\003#", 0x1ee3},
#line 700 "./uninorm/composition-table.gperf"
      {"\003\231\003\023", 0x1f38},
#line 207 "./uninorm/composition-table.gperf"
      {"\000\374\003\001", 0x01d8},
#line 211 "./uninorm/composition-table.gperf"
      {"\000\374\003\000", 0x01dc},
#line 831 "./uninorm/composition-table.gperf"
      {"\003\231\003\006", 0x1fd8},
#line 800 "./uninorm/composition-table.gperf"
      {"\037m\003E", 0x1fad},
#line 221 "./uninorm/composition-table.gperf"
      {"\000k\003\014", 0x01e9},
#line 515 "./uninorm/composition-table.gperf"
      {"\000T\003-", 0x1e70},
#line 116 "./uninorm/composition-table.gperf"
      {"\000G\003'", 0x0122},
#line 280 "./uninorm/composition-table.gperf"
      {"\002/\003\004", 0x0231},
#line 462 "./uninorm/composition-table.gperf"
      {"\000l\0031", 0x1e3b},
#line 939 "./uninorm/composition-table.gperf"
      {"0\3010\231", 0x30c2},
#line 931 "./uninorm/composition-table.gperf"
      {"0\2610\231", 0x30b2},
#line 674 "./uninorm/composition-table.gperf"
      {"\037\030\003\001", 0x1f1c},
#line 672 "./uninorm/composition-table.gperf"
      {"\037\030\003\000", 0x1f1a},
#line 314 "./uninorm/composition-table.gperf"
      {"\0048\003\006", 0x0439},
#line 636 "./uninorm/composition-table.gperf"
      {"\001\257\003\003", 0x1eee},
#line 286 "./uninorm/composition-table.gperf"
      {"\003\227\003\001", 0x0389},
#line 821 "./uninorm/composition-table.gperf"
      {"\003\227\003\000", 0x1fca},
#line 415 "./uninorm/composition-table.gperf"
      {"\000D\003#", 0x1e0c},
#line 360 "./uninorm/composition-table.gperf"
      {"\006H\006T", 0x0624},
#line 606 "./uninorm/composition-table.gperf"
      {"\000\324\003\001", 0x1ed0},
#line 608 "./uninorm/composition-table.gperf"
      {"\000\324\003\000", 0x1ed2},
#line 190 "./uninorm/composition-table.gperf"
      {"\000Z\003\014", 0x017d},
#line 529 "./uninorm/composition-table.gperf"
      {"\000V\003#", 0x1e7e},
      {""},
#line 844 "./uninorm/composition-table.gperf"
      {"\003\245\003\006", 0x1fe8},
#line 670 "./uninorm/composition-table.gperf"
      {"\003\225\003\023", 0x1f18},
#line 141 "./uninorm/composition-table.gperf"
      {"\000N\003'", 0x0145},
#line 822 "./uninorm/composition-table.gperf"
      {"\003\227\003E", 0x1fcc},
#line 458 "./uninorm/composition-table.gperf"
      {"\000l\003#", 0x1e37},
#line 580 "./uninorm/composition-table.gperf"
      {"\036\240\003\006", 0x1eb6},
      {""},
#line 518 "./uninorm/composition-table.gperf"
      {"\000u\003$", 0x1e73},
      {""},
#line 732 "./uninorm/composition-table.gperf"
      {"\003\311\003\023", 0x1f60},
#line 949 "./uninorm/composition-table.gperf"
      {"0\3300\231", 0x30d9},
#line 508 "./uninorm/composition-table.gperf"
      {"\036c\003\007", 0x1e69},
#line 725 "./uninorm/composition-table.gperf"
      {"\037Q\003\001", 0x1f55},
#line 723 "./uninorm/composition-table.gperf"
      {"\037Q\003\000", 0x1f53},
#line 727 "./uninorm/composition-table.gperf"
      {"\037Q\003B", 0x1f57},
#line 934 "./uninorm/composition-table.gperf"
      {"0\2670\231", 0x30b8},
#line 905 "./uninorm/composition-table.gperf"
      {"0S0\231", 0x3054},
#line 456 "./uninorm/composition-table.gperf"
      {"\000k\0031", 0x1e35},
#line 363 "./uninorm/composition-table.gperf"
      {"\006\325\006T", 0x06c0},
#line 665 "./uninorm/composition-table.gperf"
      {"\003\265\003\024", 0x1f11},
#line 130 "./uninorm/composition-table.gperf"
      {"\000j\003\002", 0x0135},
#line 502 "./uninorm/composition-table.gperf"
      {"\000s\003#", 0x1e63},
#line 117 "./uninorm/composition-table.gperf"
      {"\000g\003'", 0x0123},
#line 501 "./uninorm/composition-table.gperf"
      {"\000S\003#", 0x1e62},
#line 392 "./uninorm/composition-table.gperf"
      {"\033\005\0335", 0x1b06},
#line 589 "./uninorm/composition-table.gperf"
      {"\000\352\003\001", 0x1ebf},
#line 591 "./uninorm/composition-table.gperf"
      {"\000\352\003\000", 0x1ec1},
#line 396 "./uninorm/composition-table.gperf"
      {"\033\015\0335", 0x1b0e},
#line 681 "./uninorm/composition-table.gperf"
      {"\037!\003\001", 0x1f25},
#line 679 "./uninorm/composition-table.gperf"
      {"\037!\003\000", 0x1f23},
#line 683 "./uninorm/composition-table.gperf"
      {"\037!\003B", 0x1f27},
#line 919 "./uninorm/composition-table.gperf"
      {"0r0\232", 0x3074},
#line 191 "./uninorm/composition-table.gperf"
      {"\000z\003\014", 0x017e},
#line 311 "./uninorm/composition-table.gperf"
      {"\004\030\003\000", 0x040d},
#line 551 "./uninorm/composition-table.gperf"
      {"\000Z\0031", 0x1e94},
#line 797 "./uninorm/composition-table.gperf"
      {"\037j\003E", 0x1faa},
#line 952 "./uninorm/composition-table.gperf"
      {"0\3330\232", 0x30dd},
#line 454 "./uninorm/composition-table.gperf"
      {"\000k\003#", 0x1e33},
#line 135 "./uninorm/composition-table.gperf"
      {"\000L\003'", 0x013b},
#line 334 "./uninorm/composition-table.gperf"
      {"\004\026\003\010", 0x04dc},
#line 772 "./uninorm/composition-table.gperf"
      {"\037!\003E", 0x1f91},
#line 882 "./uninorm/composition-table.gperf"
      {"\"w\0038", 0x2279},
#line 631 "./uninorm/composition-table.gperf"
      {"\001\260\003\001", 0x1ee9},
#line 633 "./uninorm/composition-table.gperf"
      {"\001\260\003\000", 0x1eeb},
#line 525 "./uninorm/composition-table.gperf"
      {"\001j\003\010", 0x1e7a},
#line 624 "./uninorm/composition-table.gperf"
      {"\001\240\003#", 0x1ee2},
#line 669 "./uninorm/composition-table.gperf"
      {"\037\021\003\001", 0x1f15},
#line 667 "./uninorm/composition-table.gperf"
      {"\037\021\003\000", 0x1f13},
#line 832 "./uninorm/composition-table.gperf"
      {"\003\231\003\004", 0x1fd9},
#line 634 "./uninorm/composition-table.gperf"
      {"\001\257\003\011", 0x1eec},
#line 684 "./uninorm/composition-table.gperf"
      {"\003\227\003\023", 0x1f28},
#line 900 "./uninorm/composition-table.gperf"
      {"\"\265\0038", 0x22ed},
#line 361 "./uninorm/composition-table.gperf"
      {"\006'\006U", 0x0625},
#line 612 "./uninorm/composition-table.gperf"
      {"\000\324\003\003", 0x1ed6},
#line 549 "./uninorm/composition-table.gperf"
      {"\000Z\003#", 0x1e92},
#line 386 "./uninorm/composition-table.gperf"
      {"\015F\015W", 0x0d4c},
#line 421 "./uninorm/composition-table.gperf"
      {"\000D\003-", 0x1e12},
#line 406 "./uninorm/composition-table.gperf"
      {"\000b\003\007", 0x1e03},
#line 97 "./uninorm/composition-table.gperf"
      {"\000c\003\014", 0x010d},
#line 339 "./uninorm/composition-table.gperf"
      {"\0048\003\004", 0x04e3},
      {""},
#line 365 "./uninorm/composition-table.gperf"
      {"\006\322\006T", 0x06d3},
#line 488 "./uninorm/composition-table.gperf"
      {"\000p\003\001", 0x1e55},
#line 165 "./uninorm/composition-table.gperf"
      {"\000T\003'", 0x0162},
#line 505 "./uninorm/composition-table.gperf"
      {"\001`\003\007", 0x1e66},
#line 340 "./uninorm/composition-table.gperf"
      {"\004\030\003\010", 0x04e4},
#line 490 "./uninorm/composition-table.gperf"
      {"\000p\003\007", 0x1e57},
#line 464 "./uninorm/composition-table.gperf"
      {"\000l\003-", 0x1e3d},
#line 324 "./uninorm/composition-table.gperf"
      {"\004\026\003\006", 0x04c1},
#line 552 "./uninorm/composition-table.gperf"
      {"\000z\0031", 0x1e95},
#line 845 "./uninorm/composition-table.gperf"
      {"\003\245\003\004", 0x1fe9},
#line 789 "./uninorm/composition-table.gperf"
      {"\037b\003E", 0x1fa2},
#line 736 "./uninorm/composition-table.gperf"
      {"\037`\003\001", 0x1f64},
#line 734 "./uninorm/composition-table.gperf"
      {"\037`\003\000", 0x1f62},
#line 738 "./uninorm/composition-table.gperf"
      {"\037`\003B", 0x1f66},
#line 859 "./uninorm/composition-table.gperf"
      {"!\224\0038", 0x21ae},
#line 517 "./uninorm/composition-table.gperf"
      {"\000U\003$", 0x1e72},
#line 216 "./uninorm/composition-table.gperf"
      {"\000\306\003\004", 0x01e2},
#line 495 "./uninorm/composition-table.gperf"
      {"\036Z\003\004", 0x1e5c},
#line 709 "./uninorm/composition-table.gperf"
      {"\003\277\003\024", 0x1f41},
#line 805 "./uninorm/composition-table.gperf"
      {"\037p\003E", 0x1fb2},
#line 607 "./uninorm/composition-table.gperf"
      {"\000\364\003\001", 0x1ed1},
#line 609 "./uninorm/composition-table.gperf"
      {"\000\364\003\000", 0x1ed3},
#line 595 "./uninorm/composition-table.gperf"
      {"\000\352\003\003", 0x1ec5},
#line 787 "./uninorm/composition-table.gperf"
      {"\037`\003E", 0x1fa0},
#line 693 "./uninorm/composition-table.gperf"
      {"\003\271\003\024", 0x1f31},
#line 860 "./uninorm/composition-table.gperf"
      {"!\320\0038", 0x21cd},
#line 874 "./uninorm/composition-table.gperf"
      {"\"M\0038", 0x226d},
#line 857 "./uninorm/composition-table.gperf"
      {"!\220\0038", 0x219a},
#line 550 "./uninorm/composition-table.gperf"
      {"\000z\003#", 0x1e93},
#line 400 "./uninorm/composition-table.gperf"
      {"\033>\0335", 0x1b40},
#line 487 "./uninorm/composition-table.gperf"
      {"\000P\003\001", 0x1e54},
      {""},
#line 948 "./uninorm/composition-table.gperf"
      {"0\3250\232", 0x30d7},
#line 313 "./uninorm/composition-table.gperf"
      {"\004\030\003\006", 0x0419},
#line 489 "./uninorm/composition-table.gperf"
      {"\000P\003\007", 0x1e56},
#line 657 "./uninorm/composition-table.gperf"
      {"\003\221\003\024", 0x1f09},
#line 724 "./uninorm/composition-table.gperf"
      {"\037P\003\001", 0x1f54},
#line 722 "./uninorm/composition-table.gperf"
      {"\037P\003\000", 0x1f52},
#line 726 "./uninorm/composition-table.gperf"
      {"\037P\003B", 0x1f56},
#line 637 "./uninorm/composition-table.gperf"
      {"\001\260\003\003", 0x1eef},
#line 890 "./uninorm/composition-table.gperf"
      {"\"\250\0038", 0x22ad},
#line 362 "./uninorm/composition-table.gperf"
      {"\006J\006T", 0x0626},
#line 563 "./uninorm/composition-table.gperf"
      {"\000\342\003\001", 0x1ea5},
#line 565 "./uninorm/composition-table.gperf"
      {"\000\342\003\000", 0x1ea7},
#line 777 "./uninorm/composition-table.gperf"
      {"\037&\003E", 0x1f96},
#line 193 "./uninorm/composition-table.gperf"
      {"\000o\003\033", 0x01a1},
      {""},
#line 205 "./uninorm/composition-table.gperf"
      {"\000\374\003\004", 0x01d6},
#line 562 "./uninorm/composition-table.gperf"
      {"\000\302\003\001", 0x1ea4},
#line 564 "./uninorm/composition-table.gperf"
      {"\000\302\003\000", 0x1ea6},
#line 209 "./uninorm/composition-table.gperf"
      {"\000\374\003\014", 0x01da},
#line 610 "./uninorm/composition-table.gperf"
      {"\000\324\003\011", 0x1ed4},
#line 404 "./uninorm/composition-table.gperf"
      {"\000a\003%", 0x1e01},
#line 369 "./uninorm/composition-table.gperf"
      {"\011\307\011\276", 0x09cb},
#line 195 "./uninorm/composition-table.gperf"
      {"\000u\003\033", 0x01b0},
#line 315 "./uninorm/composition-table.gperf"
      {"\0045\003\000", 0x0450},
#line 680 "./uninorm/composition-table.gperf"
      {"\037 \003\001", 0x1f24},
#line 678 "./uninorm/composition-table.gperf"
      {"\037 \003\000", 0x1f22},
#line 682 "./uninorm/composition-table.gperf"
      {"\037 \003B", 0x1f26},
#line 378 "./uninorm/composition-table.gperf"
      {"\014F\014V", 0x0c48},
#line 847 "./uninorm/composition-table.gperf"
      {"\003\241\003\024", 0x1fec},
#line 866 "./uninorm/composition-table.gperf"
      {"\"#\0038", 0x2224},
#line 930 "./uninorm/composition-table.gperf"
      {"0\2570\231", 0x30b0},
#line 638 "./uninorm/composition-table.gperf"
      {"\001\257\003#", 0x1ef0},
      {""}, {""},
#line 721 "./uninorm/composition-table.gperf"
      {"\003\305\003\024", 0x1f51},
#line 895 "./uninorm/composition-table.gperf"
      {"\"\221\0038", 0x22e2},
#line 771 "./uninorm/composition-table.gperf"
      {"\037 \003E", 0x1f90},
#line 941 "./uninorm/composition-table.gperf"
      {"0\3060\231", 0x30c7},
#line 399 "./uninorm/composition-table.gperf"
      {"\033<\0335", 0x1b3d},
      {""},
#line 841 "./uninorm/composition-table.gperf"
      {"\003\301\003\024", 0x1fe5},
#line 649 "./uninorm/composition-table.gperf"
      {"\003\261\003\024", 0x1f01},
#line 385 "./uninorm/composition-table.gperf"
      {"\015G\015>", 0x0d4b},
#line 946 "./uninorm/composition-table.gperf"
      {"0\3220\232", 0x30d4},
      {""},
#line 419 "./uninorm/composition-table.gperf"
      {"\000D\003'", 0x1e10},
#line 613 "./uninorm/composition-table.gperf"
      {"\000\364\003\003", 0x1ed7},
      {""},
#line 507 "./uninorm/composition-table.gperf"
      {"\036b\003\007", 0x1e68},
#line 593 "./uninorm/composition-table.gperf"
      {"\000\352\003\011", 0x1ec3},
      {""}, {""}, {""}, {""},
#line 445 "./uninorm/composition-table.gperf"
      {"\000H\003.", 0x1e2a},
#line 316 "./uninorm/composition-table.gperf"
      {"\0045\003\010", 0x0451},
#line 136 "./uninorm/composition-table.gperf"
      {"\000l\003'", 0x013c},
      {""},
#line 224 "./uninorm/composition-table.gperf"
      {"\001\352\003\004", 0x01ec},
#line 228 "./uninorm/composition-table.gperf"
      {"\000j\003\014", 0x01f0},
#line 470 "./uninorm/composition-table.gperf"
      {"\000m\003#", 0x1e43},
      {""},
#line 909 "./uninorm/composition-table.gperf"
      {"0[0\231", 0x305c},
      {""}, {""}, {""},
#line 635 "./uninorm/composition-table.gperf"
      {"\001\260\003\011", 0x1eed},
#line 395 "./uninorm/composition-table.gperf"
      {"\033\013\0335", 0x1b0c},
#line 569 "./uninorm/composition-table.gperf"
      {"\000\342\003\003", 0x1eab},
#line 192 "./uninorm/composition-table.gperf"
      {"\000O\003\033", 0x01a0},
#line 677 "./uninorm/composition-table.gperf"
      {"\003\267\003\024", 0x1f21},
#line 338 "./uninorm/composition-table.gperf"
      {"\004\030\003\004", 0x04e2},
      {""},
#line 162 "./uninorm/composition-table.gperf"
      {"\000s\003'", 0x015f},
#line 568 "./uninorm/composition-table.gperf"
      {"\000\302\003\003", 0x1eaa},
#line 161 "./uninorm/composition-table.gperf"
      {"\000S\003'", 0x015e},
      {""}, {""}, {""}, {""}, {""},
#line 858 "./uninorm/composition-table.gperf"
      {"!\222\0038", 0x219b},
      {""},
#line 403 "./uninorm/composition-table.gperf"
      {"\000A\003%", 0x1e00},
#line 331 "./uninorm/composition-table.gperf"
      {"\0045\003\006", 0x04d7},
      {""}, {""}, {""},
#line 446 "./uninorm/composition-table.gperf"
      {"\000h\003.", 0x1e2b},
#line 132 "./uninorm/composition-table.gperf"
      {"\000k\003'", 0x0137},
      {""},
#line 194 "./uninorm/composition-table.gperf"
      {"\000U\003\033", 0x01af},
      {""},
#line 496 "./uninorm/composition-table.gperf"
      {"\036[\003\004", 0x1e5d},
      {""}, {""}, {""}, {""},
#line 904 "./uninorm/composition-table.gperf"
      {"0Q0\231", 0x3052},
      {""},
#line 370 "./uninorm/composition-table.gperf"
      {"\011\307\011\327", 0x09cc},
#line 880 "./uninorm/composition-table.gperf"
      {"\"s\0038", 0x2275},
#line 374 "./uninorm/composition-table.gperf"
      {"\013\222\013\327", 0x0b94},
      {""}, {""},
#line 611 "./uninorm/composition-table.gperf"
      {"\000\364\003\011", 0x1ed5},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""},
#line 214 "./uninorm/composition-table.gperf"
      {"\002&\003\004", 0x01e0},
      {""}, {""}, {""},
#line 402 "./uninorm/composition-table.gperf"
      {"\033B\0335", 0x1b43},
      {""}, {""}, {""},
#line 567 "./uninorm/composition-table.gperf"
      {"\000\342\003\011", 0x1ea9},
      {""}, {""}, {""}, {""},
#line 410 "./uninorm/composition-table.gperf"
      {"\000b\0031", 0x1e07},
#line 566 "./uninorm/composition-table.gperf"
      {"\000\302\003\011", 0x1ea8},
      {""}, {""}, {""}, {""},
#line 741 "./uninorm/composition-table.gperf"
      {"\003\251\003\024", 0x1f69},
      {""}, {""},
#line 639 "./uninorm/composition-table.gperf"
      {"\001\260\003#", 0x1ef1},
#line 364 "./uninorm/composition-table.gperf"
      {"\006\301\006T", 0x06c2},
      {""}, {""},
#line 379 "./uninorm/composition-table.gperf"
      {"\014\277\014\325", 0x0cc0},
#line 867 "./uninorm/composition-table.gperf"
      {"\"%\0038", 0x2226},
#line 923 "./uninorm/composition-table.gperf"
      {"0x0\232", 0x307a},
      {""}, {""}, {""}, {""},
#line 408 "./uninorm/composition-table.gperf"
      {"\000b\003#", 0x1e05},
      {""}, {""}, {""}, {""}, {""}, {""}, {""},
#line 701 "./uninorm/composition-table.gperf"
      {"\003\231\003\024", 0x1f39},
#line 401 "./uninorm/composition-table.gperf"
      {"\033?\0335", 0x1b41},
      {""}, {""}, {""}, {""}, {""},
#line 63 "./uninorm/composition-table.gperf"
      {"\000c\003'", 0x00e7},
      {""},
#line 883 "./uninorm/composition-table.gperf"
      {"\"z\0038", 0x2280},
#line 891 "./uninorm/composition-table.gperf"
      {"\"\251\0038", 0x22ae},
      {""}, {""},
#line 371 "./uninorm/composition-table.gperf"
      {"\013G\013V", 0x0b48},
      {""},
#line 372 "./uninorm/composition-table.gperf"
      {"\013G\013>", 0x0b4b},
      {""}, {""}, {""}, {""}, {""}, {""},
#line 728 "./uninorm/composition-table.gperf"
      {"\003\245\003\024", 0x1f59},
      {""}, {""}, {""},
#line 671 "./uninorm/composition-table.gperf"
      {"\003\225\003\024", 0x1f19},
      {""}, {""}, {""}, {""}, {""}, {""}, {""},
#line 733 "./uninorm/composition-table.gperf"
      {"\003\311\003\024", 0x1f61},
      {""}, {""}, {""}, {""}, {""},
#line 352 "./uninorm/composition-table.gperf"
      {"\004#\003\013", 0x04f2},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""},
#line 685 "./uninorm/composition-table.gperf"
      {"\003\227\003\024", 0x1f29},
      {""}, {""}, {""}, {""}, {""}, {""},
#line 950 "./uninorm/composition-table.gperf"
      {"0\3300\232", 0x30da},
      {""}, {""}, {""}, {""}, {""}, {""},
#line 383 "./uninorm/composition-table.gperf"
      {"\014\312\014\325", 0x0ccb},
      {""}, {""}, {""}, {""}, {""}, {""},
#line 376 "./uninorm/composition-table.gperf"
      {"\013\307\013\276", 0x0bcb},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
#line 862 "./uninorm/composition-table.gperf"
      {"!\322\0038", 0x21cf},
      {""},
#line 381 "./uninorm/composition-table.gperf"
      {"\014\306\014\326", 0x0cc8},
#line 382 "./uninorm/composition-table.gperf"
      {"\014\306\014\302", 0x0cca},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""},
#line 380 "./uninorm/composition-table.gperf"
      {"\014\306\014\325", 0x0cc7},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""},
#line 373 "./uninorm/composition-table.gperf"
      {"\013G\013W", 0x0b4c},
      {""}, {""}, {""}, {""}, {""}, {""},
#line 391 "./uninorm/composition-table.gperf"
      {"\020%\020.", 0x1026},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""},
#line 397 "./uninorm/composition-table.gperf"
      {"\033\021\0335", 0x1b12},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""},
#line 375 "./uninorm/composition-table.gperf"
      {"\013\306\013\276", 0x0bca},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""},
#line 377 "./uninorm/composition-table.gperf"
      {"\013\306\013\327", 0x0bcc},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""},
#line 861 "./uninorm/composition-table.gperf"
      {"!\324\0038", 0x21ce}
    };

  if (len <= MAX_WORD_LENGTH && len >= MIN_WORD_LENGTH)
    {
      register int key = gl_uninorm_compose_hash (str, len);

      if (key <= MAX_HASH_VALUE && key >= 0)
        if (len == lengthtable[key])
          {
            register const char *s = wordlist[key].codes;

            if (*str == *s && !memcmp (str + 1, s + 1, len - 1))
              return &wordlist[key];
          }
    }
  return 0;
}
