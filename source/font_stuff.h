// values taken from bigFont-hd.fnt
struct glyph {
    int id, x, y, width, height, xoffset, yoffset, xadvance;
};

struct charset {
    struct glyph *chars;
    int char_num;
};

#include "bigFont_png.h"
#include "gjFont01_png.h"
#include "gjFont02_png.h"
#include "gjFont03_png.h"
#include "gjFont04_png.h"
#include "gjFont05_png.h"
#include "gjFont07_png.h"
#include "gjFont06_png.h"
#include "gjFont08_png.h"
#include "gjFont09_png.h"
#include "gjFont10_png.h"
#include "gjFont11_png.h"
#include "gjFont12_png.h"

#define NUM_LEVEL_FONTS 13

extern const unsigned char *font_text[NUM_LEVEL_FONTS];
extern struct charset *font_charsets[NUM_LEVEL_FONTS];

extern struct glyph big_font_chars[96];
extern struct charset big_font;

extern struct glyph chat_font_chars[95];
extern struct charset chat_font;

extern struct glyph gold_font_chars[96];
extern struct charset gold_font;

extern struct glyph gjFont01_chars[67];
extern struct charset gjFont01;

extern struct glyph gjFont02_chars[83];
extern struct charset gjFont02;

extern struct glyph gjFont03_chars[88];
extern struct charset gjFont03;

extern struct glyph gjFont04_chars[89];
extern struct charset gjFont04;

extern struct glyph gjFont05_chars[96];
extern struct charset gjFont05;

extern struct glyph gjFont06_chars[93];
extern struct charset gjFont06;

extern struct glyph gjFont07_chars[93];
extern struct charset gjFont07;

extern struct glyph gjFont08_chars[93];
extern struct charset gjFont08;

extern struct glyph gjFont09_chars[87];
extern struct charset gjFont09;

extern struct glyph gjFont10_chars[69];
extern struct charset gjFont10;

extern struct glyph gjFont11_chars[80];
extern struct charset gjFont11;

extern struct glyph gjFont12_chars[96];
extern struct charset gjFont12;