/* ANSI-C code produced by gperf version 3.0.4 */
/* Command-line: gperf -m 10 ./unictype/scripts_byname.gperf  */
/* Computed positions: -k'1,3' */

#if !((' ' == 32) && ('!' == 33) && ('"' == 34) && ('#' == 35) \
      && ('%' == 37) && ('&' == 38) && ('\'' == 39) && ('(' == 40) \
      && (')' == 41) && ('*' == 42) && ('+' == 43) && (',' == 44) \
      && ('-' == 45) && ('.' == 46) && ('/' == 47) && ('0' == 48) \
      && ('1' == 49) && ('2' == 50) && ('3' == 51) && ('4' == 52) \
      && ('5' == 53) && ('6' == 54) && ('7' == 55) && ('8' == 56) \
      && ('9' == 57) && (':' == 58) && (';' == 59) && ('<' == 60) \
      && ('=' == 61) && ('>' == 62) && ('?' == 63) && ('A' == 65) \
      && ('B' == 66) && ('C' == 67) && ('D' == 68) && ('E' == 69) \
      && ('F' == 70) && ('G' == 71) && ('H' == 72) && ('I' == 73) \
      && ('J' == 74) && ('K' == 75) && ('L' == 76) && ('M' == 77) \
      && ('N' == 78) && ('O' == 79) && ('P' == 80) && ('Q' == 81) \
      && ('R' == 82) && ('S' == 83) && ('T' == 84) && ('U' == 85) \
      && ('V' == 86) && ('W' == 87) && ('X' == 88) && ('Y' == 89) \
      && ('Z' == 90) && ('[' == 91) && ('\\' == 92) && (']' == 93) \
      && ('^' == 94) && ('_' == 95) && ('a' == 97) && ('b' == 98) \
      && ('c' == 99) && ('d' == 100) && ('e' == 101) && ('f' == 102) \
      && ('g' == 103) && ('h' == 104) && ('i' == 105) && ('j' == 106) \
      && ('k' == 107) && ('l' == 108) && ('m' == 109) && ('n' == 110) \
      && ('o' == 111) && ('p' == 112) && ('q' == 113) && ('r' == 114) \
      && ('s' == 115) && ('t' == 116) && ('u' == 117) && ('v' == 118) \
      && ('w' == 119) && ('x' == 120) && ('y' == 121) && ('z' == 122) \
      && ('{' == 123) && ('|' == 124) && ('}' == 125) && ('~' == 126))
/* The character set is not based on ISO-646.  */
#error "gperf generated tables don't work with this execution character set. Please report a bug to <bug-gnu-gperf@gnu.org>."
#endif

#line 4 "./unictype/scripts_byname.gperf"
struct named_script { const char *name; unsigned int index; };

#define TOTAL_KEYWORDS 77
#define MIN_WORD_LENGTH 2
#define MAX_WORD_LENGTH 19
#define MIN_HASH_VALUE 2
#define MAX_HASH_VALUE 92
/* maximum key range = 91, duplicates = 0 */

#ifdef __GNUC__
__inline
#else
#ifdef __cplusplus
inline
#endif
#endif
static unsigned int
scripts_hash (register const char *str, register unsigned int len)
{
  static const unsigned char asso_values[] =
    {
      93, 93, 93, 93, 93, 93, 93, 93, 93, 93,
      93, 93, 93, 93, 93, 93, 93, 93, 93, 93,
      93, 93, 93, 93, 93, 93, 93, 93, 93, 93,
      93, 93, 93, 93, 93, 93, 93, 93, 93, 93,
      93, 93, 93, 93, 93, 93, 93, 93, 93, 93,
      93, 93, 93, 93, 93, 93, 93, 93, 93, 93,
      93, 93, 93, 93, 93, 53, 14,  3, 29, 27,
      93, 25,  0, 25, 93, 24,  7, 36, 28,  8,
      49, 93, 54,  7, 11, 64, 32, 93, 93,  0,
      93, 93, 93, 93, 93, 57, 93,  3, 52, 59,
      29, 39, 52, 22, 42, 39, 24, 93,  6, 20,
       0, 33, 17, 93,  0, 32, 22,  2, 28, 26,
      93, 31, 93, 93, 93, 93, 93, 93, 93, 93,
      93, 93, 93, 93, 93, 93, 93, 93, 93, 93,
      93, 93, 93, 93, 93, 93, 93, 93, 93, 93,
      93, 93, 93, 93, 93, 93, 93, 93, 93, 93,
      93, 93, 93, 93, 93, 93, 93, 93, 93, 93,
      93, 93, 93, 93, 93, 93, 93, 93, 93, 93,
      93, 93, 93, 93, 93, 93, 93, 93, 93, 93,
      93, 93, 93, 93, 93, 93, 93, 93, 93, 93,
      93, 93, 93, 93, 93, 93, 93, 93, 93, 93,
      93, 93, 93, 93, 93, 93, 93, 93, 93, 93,
      93, 93, 93, 93, 93, 93, 93, 93, 93, 93,
      93, 93, 93, 93, 93, 93, 93, 93, 93, 93,
      93, 93, 93, 93, 93, 93, 93, 93, 93, 93,
      93, 93, 93, 93, 93, 93
    };
  register int hval = len;

  switch (hval)
    {
      default:
        hval += asso_values[(unsigned char)str[2]];
      /*FALLTHROUGH*/
      case 2:
      case 1:
        hval += asso_values[(unsigned char)str[0]];
        break;
    }
  return hval;
}

static const struct named_script script_names[] =
  {
    {""}, {""},
#line 49 "./unictype/scripts_byname.gperf"
    {"Yi", 36},
#line 48 "./unictype/scripts_byname.gperf"
    {"Han", 35},
    {""}, {""},
#line 37 "./unictype/scripts_byname.gperf"
    {"Hangul", 24},
#line 55 "./unictype/scripts_byname.gperf"
    {"Hanunoo", 42},
#line 45 "./unictype/scripts_byname.gperf"
    {"Hiragana", 32},
#line 87 "./unictype/scripts_byname.gperf"
    {"Carian", 74},
#line 89 "./unictype/scripts_byname.gperf"
    {"Cham", 76},
#line 16 "./unictype/scripts_byname.gperf"
    {"Cyrillic", 3},
#line 75 "./unictype/scripts_byname.gperf"
    {"Cuneiform", 62},
#line 20 "./unictype/scripts_byname.gperf"
    {"Syriac", 7},
#line 31 "./unictype/scripts_byname.gperf"
    {"Sinhala", 18},
#line 60 "./unictype/scripts_byname.gperf"
    {"Linear_B", 47},
#line 79 "./unictype/scripts_byname.gperf"
    {"Sundanese", 66},
#line 62 "./unictype/scripts_byname.gperf"
    {"Shavian", 49},
#line 32 "./unictype/scripts_byname.gperf"
    {"Thai", 19},
#line 83 "./unictype/scripts_byname.gperf"
    {"Saurashtra", 70},
#line 21 "./unictype/scripts_byname.gperf"
    {"Thaana", 8},
#line 23 "./unictype/scripts_byname.gperf"
    {"Bengali", 10},
#line 40 "./unictype/scripts_byname.gperf"
    {"Canadian_Aboriginal", 27},
#line 28 "./unictype/scripts_byname.gperf"
    {"Telugu", 15},
#line 65 "./unictype/scripts_byname.gperf"
    {"Braille", 52},
#line 71 "./unictype/scripts_byname.gperf"
    {"Syloti_Nagri", 58},
#line 67 "./unictype/scripts_byname.gperf"
    {"Coptic", 54},
#line 64 "./unictype/scripts_byname.gperf"
    {"Cypriot", 51},
#line 74 "./unictype/scripts_byname.gperf"
    {"Balinese", 61},
#line 13 "./unictype/scripts_byname.gperf"
    {"Common", 0},
#line 80 "./unictype/scripts_byname.gperf"
    {"Lepcha", 67},
#line 29 "./unictype/scripts_byname.gperf"
    {"Kannada", 16},
#line 58 "./unictype/scripts_byname.gperf"
    {"Limbu", 45},
#line 24 "./unictype/scripts_byname.gperf"
    {"Gurmukhi", 11},
#line 14 "./unictype/scripts_byname.gperf"
    {"Latin", 1},
#line 63 "./unictype/scripts_byname.gperf"
    {"Osmanya", 50},
#line 27 "./unictype/scripts_byname.gperf"
    {"Tamil", 14},
#line 73 "./unictype/scripts_byname.gperf"
    {"Kharoshthi", 60},
#line 69 "./unictype/scripts_byname.gperf"
    {"Glagolitic", 56},
#line 47 "./unictype/scripts_byname.gperf"
    {"Bopomofo", 34},
#line 54 "./unictype/scripts_byname.gperf"
    {"Tagalog", 41},
#line 57 "./unictype/scripts_byname.gperf"
    {"Tagbanwa", 44},
#line 88 "./unictype/scripts_byname.gperf"
    {"Lydian", 75},
#line 33 "./unictype/scripts_byname.gperf"
    {"Lao", 20},
#line 66 "./unictype/scripts_byname.gperf"
    {"Buginese", 53},
#line 44 "./unictype/scripts_byname.gperf"
    {"Mongolian", 31},
#line 35 "./unictype/scripts_byname.gperf"
    {"Myanmar", 22},
#line 50 "./unictype/scripts_byname.gperf"
    {"Old_Italic", 37},
#line 72 "./unictype/scripts_byname.gperf"
    {"Old_Persian", 59},
#line 43 "./unictype/scripts_byname.gperf"
    {"Khmer", 30},
#line 39 "./unictype/scripts_byname.gperf"
    {"Cherokee", 26},
#line 30 "./unictype/scripts_byname.gperf"
    {"Malayalam", 17},
#line 26 "./unictype/scripts_byname.gperf"
    {"Oriya", 13},
#line 51 "./unictype/scripts_byname.gperf"
    {"Gothic", 38},
#line 46 "./unictype/scripts_byname.gperf"
    {"Katakana", 33},
#line 41 "./unictype/scripts_byname.gperf"
    {"Ogham", 28},
#line 59 "./unictype/scripts_byname.gperf"
    {"Tai_Le", 46},
#line 25 "./unictype/scripts_byname.gperf"
    {"Gujarati", 12},
#line 18 "./unictype/scripts_byname.gperf"
    {"Hebrew", 5},
#line 42 "./unictype/scripts_byname.gperf"
    {"Runic", 29},
#line 77 "./unictype/scripts_byname.gperf"
    {"Phags_Pa", 64},
#line 56 "./unictype/scripts_byname.gperf"
    {"Buhid", 43},
#line 19 "./unictype/scripts_byname.gperf"
    {"Arabic", 6},
#line 84 "./unictype/scripts_byname.gperf"
    {"Kayah_Li", 71},
#line 78 "./unictype/scripts_byname.gperf"
    {"Nko", 65},
#line 68 "./unictype/scripts_byname.gperf"
    {"New_Tai_Lue", 55},
#line 36 "./unictype/scripts_byname.gperf"
    {"Georgian", 23},
#line 22 "./unictype/scripts_byname.gperf"
    {"Devanagari", 9},
#line 52 "./unictype/scripts_byname.gperf"
    {"Deseret", 39},
#line 15 "./unictype/scripts_byname.gperf"
    {"Greek", 2},
#line 34 "./unictype/scripts_byname.gperf"
    {"Tibetan", 21},
#line 70 "./unictype/scripts_byname.gperf"
    {"Tifinagh", 57},
#line 86 "./unictype/scripts_byname.gperf"
    {"Lycian", 73},
#line 81 "./unictype/scripts_byname.gperf"
    {"Ol_Chiki", 68},
#line 82 "./unictype/scripts_byname.gperf"
    {"Vai", 69},
#line 61 "./unictype/scripts_byname.gperf"
    {"Ugaritic", 48},
#line 53 "./unictype/scripts_byname.gperf"
    {"Inherited", 40},
#line 38 "./unictype/scripts_byname.gperf"
    {"Ethiopic", 25},
    {""}, {""}, {""},
#line 17 "./unictype/scripts_byname.gperf"
    {"Armenian", 4},
    {""}, {""},
#line 85 "./unictype/scripts_byname.gperf"
    {"Rejang", 72},
    {""}, {""}, {""}, {""}, {""}, {""}, {""},
#line 76 "./unictype/scripts_byname.gperf"
    {"Phoenician", 63}
  };

#ifdef __GNUC__
__inline
#if defined __GNUC_STDC_INLINE__ || defined __GNUC_GNU_INLINE__
__attribute__ ((__gnu_inline__))
#endif
#endif
const struct named_script *
uc_script_lookup (register const char *str, register unsigned int len)
{
  if (len <= MAX_WORD_LENGTH && len >= MIN_WORD_LENGTH)
    {
      register int key = scripts_hash (str, len);

      if (key <= MAX_HASH_VALUE && key >= 0)
        {
          register const char *s = script_names[key].name;

          if (*str == *s && !strcmp (str + 1, s + 1))
            return &script_names[key];
        }
    }
  return 0;
}
