#ifndef COLORX_H_
#define COLORX_H_

/* aux math functions */
#define MAX2(a, b) (((a) > (b)) ? (a) : (b))
#define MIN2(a, b) (((a) > (b)) ? (b) : (a))
#define MAX3(a, b, c) MAX2((a), MAX2((b), (c)))
#define MIN3(a, b, c) MIN2((a), MIN2((b), (c)))

#define LINE_LEN 70
/* max color operations permited, really a random number */
#define MAXCLOPS 24
#define EXIT_ON_FAILURE(args...)                                               \
  {                                                                            \
    printf("color: ");                                                         \
    printf(args);                                                              \
    exit(1);                                                                   \
  }

/* predefined colors */
#define RGB_BLACK ((color_t){.model = RGB, {0, 0, 0, 255}})
#define RGB_SILVER ((color_t){.model = RGB, {192, 192, 192, 255}})
#define RGB_GRAY ((color_t){.model = RGB, {128, 128, 128, 255}})
#define RGB_WHITE ((color_t){.model = RGB, {255, 255, 255, 255}})
#define RGB_MAROON ((color_t){.model = RGB, {128, 0, 0}})
#define RGB_RED ((color_t){.model = RGB, {255, 0, 0}})
#define RGB_PURPLE ((color_t){.model = RGB, {128, 0, 128}})
#define RGB_FUCHSIA ((color_t){.model = RGB, {255, 0, 255}})
#define RGB_GREEN ((color_t){.model = RGB, {0, 128, 0}})
#define RGB_LIME ((color_t){.model = RGB, {0, 255, 0}})
#define RGB_OLIVE ((color_t){.model = RGB, {128, 128, 0}})
#define RGB_YELLOW ((color_t){.model = RGB, {255, 255, 0}})
#define RGB_NAVY ((color_t){.model = RGB, {0, 0, 128}})
#define RGB_BLUE ((color_t){.model = RGB, {0, 0, 255}})
#define RGB_TEAL ((color_t){.model = RGB, {0, 128, 128}})
#define RGB_AQUA ((color_t){.model = RGB, {0, 255, 255}})
#define RGB_ALICEBLUE ((color_t){.model = RGB, {240, 248, 255}})
#define RGB_ANTIQUEWHITE ((color_t){.model = RGB, {250, 235, 215}})
#define RGB_AQUAMARINE ((color_t){.model = RGB, {127, 255, 212}})
#define RGB_AZURE ((color_t){.model = RGB, {240, 255, 255}})
#define RGB_BEIGE ((color_t){.model = RGB, {245, 245, 220}})
#define RGB_BISQUE ((color_t){.model = RGB, {255, 228, 196}})
#define RGB_BLANCHEDALMOND ((color_t){.model = RGB, {255, 235, 205}})
#define RGB_BLUE ((color_t){.model = RGB, {0, 0, 255}})
#define RGB_BLUEVIOLET ((color_t){.model = RGB, {138, 43, 226}})
#define RGB_BROWN ((color_t){.model = RGB, {165, 42, 42}})
#define RGB_BURLYWOOD ((color_t){.model = RGB, {222, 184, 135}})
#define RGB_CADETBLUE ((color_t){.model = RGB, {95, 158, 160}})
#define RGB_CHARTREUSE ((color_t){.model = RGB, {127, 255, 0}})
#define RGB_CHOCOLATE ((color_t){.model = RGB, {210, 105, 30}})
#define RGB_CORAL ((color_t){.model = RGB, {255, 127, 80}})
#define RGB_CORNFLOWERBLUE ((color_t){.model = RGB, {100, 149, 237}})
#define RGB_CORNSILK ((color_t){.model = RGB, {255, 248, 220}})
#define RGB_CRIMSON ((color_t){.model = RGB, {220, 20, 60}})
#define RGB_CYAN ((color_t){.model = RGB, {0, 255, 255}})
#define RGB_DARKBLUE ((color_t){.model = RGB, {0, 0, 139}})
#define RGB_DARKCYAN ((color_t){.model = RGB, {0, 139, 139}})
#define RGB_DARKGOLDENROD ((color_t){.model = RGB, {184, 134, 11}})
#define RGB_DARKGRAY ((color_t){.model = RGB, {169, 169, 169}})
#define RGB_DARKGREEN ((color_t){.model = RGB, {0, 100, 0}})
#define RGB_DARKGREY ((color_t){.model = RGB, {169, 169, 169}})
#define RGB_DARKKHAKI ((color_t){.model = RGB, {189, 183, 107}})
#define RGB_DARKMAGENTA ((color_t){.model = RGB, {139, 0, 139}})
#define RGB_DARKOLIVEGREEN ((color_t){.model = RGB, {85, 107, 47}})
#define RGB_DARKORANGE ((color_t){.model = RGB, {255, 140, 0}})
#define RGB_DARKORCHID ((color_t){.model = RGB, {153, 50, 204}})
#define RGB_DARKRED ((color_t){.model = RGB, {139, 0, 0}})
#define RGB_DARKSALMON ((color_t){.model = RGB, {233, 150, 122}})
#define RGB_DARKSEAGREEN ((color_t){.model = RGB, {143, 188, 143}})
#define RGB_DARKSLATEBLUE ((color_t){.model = RGB, {72, 61, 139}})
#define RGB_DARKSLATEGRAY ((color_t){.model = RGB, {47, 79, 79}})
#define RGB_DARKSLATEGREY ((color_t){.model = RGB, {47, 79, 79}})
#define RGB_DARKTURQUOISE ((color_t){.model = RGB, {0, 206, 209}})
#define RGB_DARKVIOLET ((color_t){.model = RGB, {148, 0, 211}})
#define RGB_DEEPPINK ((color_t){.model = RGB, {255, 20, 147}})
#define RGB_DEEPSKYBLUE ((color_t){.model = RGB, {0, 191, 255}})
#define RGB_DIMGRAY ((color_t){.model = RGB, {105, 105, 105}})
#define RGB_DIMGREY ((color_t){.model = RGB, {105, 105, 105}})
#define RGB_DODGERBLUE ((color_t){.model = RGB, {30, 144, 255}})
#define RGB_FIREBRICK ((color_t){.model = RGB, {178, 34, 34}})
#define RGB_FLORALWHITE ((color_t){.model = RGB, {255, 250, 240}})
#define RGB_FORESTGREEN ((color_t){.model = RGB, {34, 139, 34}})
#define RGB_GAINSBORO ((color_t){.model = RGB, {220, 220, 220}})
#define RGB_GHOSTWHITE ((color_t){.model = RGB, {248, 248, 255}})
#define RGB_GOLD ((color_t){.model = RGB, {255, 215, 0}})
#define RGB_GOLDENROD ((color_t){.model = RGB, {218, 165, 32}})
#define RGB_GREEN ((color_t){.model = RGB, {0, 128, 0}})
#define RGB_GREENYELLOW ((color_t){.model = RGB, {173, 255, 47}})
#define RGB_GREY ((color_t){.model = RGB, {128, 128, 128}})
#define RGB_HONEYDEW ((color_t){.model = RGB, {240, 255, 240}})
#define RGB_HOTPINK ((color_t){.model = RGB, {255, 105, 180}})
#define RGB_INDIANRED ((color_t){.model = RGB, {205, 92, 92}})
#define RGB_INDIGO ((color_t){.model = RGB, {75, 0, 130}})
#define RGB_IVORY ((color_t){.model = RGB, {255, 255, 240}})
#define RGB_KHAKI ((color_t){.model = RGB, {240, 230, 140}})
#define RGB_LAVENDER ((color_t){.model = RGB, {230, 230, 250}})
#define RGB_LAVENDERBLUSH ((color_t){.model = RGB, {255, 240, 245}})
#define RGB_LAWNGREEN ((color_t){.model = RGB, {124, 252, 0}})
#define RGB_LEMONCHIFFON ((color_t){.model = RGB, {255, 250, 205}})
#define RGB_LIGHTBLUE ((color_t){.model = RGB, {173, 216, 230}})
#define RGB_LIGHTCORAL ((color_t){.model = RGB, {240, 128, 128}})
#define RGB_LIGHTCYAN ((color_t){.model = RGB, {224, 255, 255}})
#define RGB_LIGHTGOLDENRODYELLOW ((color_t){.model = RGB, {250, 250, 210}})
#define RGB_LIGHTGRAY ((color_t){.model = RGB, {211, 211, 211}})
#define RGB_LIGHTGREEN ((color_t){.model = RGB, {144, 238, 144}})
#define RGB_LIGHTGREY ((color_t){.model = RGB, {211, 211, 211}})
#define RGB_LIGHTPINK ((color_t){.model = RGB, {255, 182, 193}})
#define RGB_LIGHTSALMON ((color_t){.model = RGB, {255, 160, 122}})
#define RGB_LIGHTSEAGREEN ((color_t){.model = RGB, {32, 178, 170}})
#define RGB_LIGHTSKYBLUE ((color_t){.model = RGB, {135, 206, 250}})
#define RGB_LIGHTSLATEGRAY ((color_t){.model = RGB, {119, 136, 153}})
#define RGB_LIGHTSLATEGREY ((color_t){.model = RGB, {119, 136, 153}})
#define RGB_LIGHTSTEELBLUE ((color_t){.model = RGB, {176, 196, 222}})
#define RGB_LIGHTYELLOW ((color_t){.model = RGB, {255, 255, 224}})
#define RGB_LIME ((color_t){.model = RGB, {0, 255, 0}})
#define RGB_LIMEGREEN ((color_t){.model = RGB, {50, 205, 50}})
#define RGB_LINEN ((color_t){.model = RGB, {250, 240, 230}})
#define RGB_MAGENTA ((color_t){.model = RGB, {255, 0, 255}})
#define RGB_MEDIUMAQUAMARINE ((color_t){.model = RGB, {102, 205, 170}})
#define RGB_MEDIUMBLUE ((color_t){.model = RGB, {0, 0, 205}})
#define RGB_MEDIUMORCHID ((color_t){.model = RGB, {186, 85, 211}})
#define RGB_MEDIUMPURPLE ((color_t){.model = RGB, {147, 112, 219}})
#define RGB_MEDIUMSEAGREEN ((color_t){.model = RGB, {60, 179, 113}})
#define RGB_MEDIUMSLATEBLUE ((color_t){.model = RGB, {123, 104, 238}})
#define RGB_MEDIUMSPRINGGREEN ((color_t){.model = RGB, {0, 250, 154}})
#define RGB_MEDIUMTURQUOISE ((color_t){.model = RGB, {72, 209, 204}})
#define RGB_MEDIUMVIOLETRED ((color_t){.model = RGB, {199, 21, 133}})
#define RGB_MIDNIGHTBLUE ((color_t){.model = RGB, {25, 25, 112}})
#define RGB_MINTCREAM ((color_t){.model = RGB, {245, 255, 250}})
#define RGB_MISTYROSE ((color_t){.model = RGB, {255, 228, 225}})
#define RGB_MOCCASIN ((color_t){.model = RGB, {255, 228, 181}})
#define RGB_NAVAJOWHITE ((color_t){.model = RGB, {255, 222, 173}})
#define RGB_NAVY ((color_t){.model = RGB, {0, 0, 128}})
#define RGB_OLDLACE ((color_t){.model = RGB, {253, 245, 230}})
#define RGB_OLIVE ((color_t){.model = RGB, {128, 128, 0}})
#define RGB_OLIVEDRAB ((color_t){.model = RGB, {107, 142, 35}})
#define RGB_ORANGE ((color_t){.model = RGB, {255, 165, 0}})
#define RGB_ORANGERED ((color_t){.model = RGB, {255, 69, 0}})
#define RGB_ORCHID ((color_t){.model = RGB, {218, 112, 214}})
#define RGB_PALEGOLDENROD ((color_t){.model = RGB, {238, 232, 170}})
#define RGB_PALEGREEN ((color_t){.model = RGB, {152, 251, 152}})
#define RGB_PALETURQUOISE ((color_t){.model = RGB, {175, 238, 238}})
#define RGB_PALEVIOLETRED ((color_t){.model = RGB, {219, 112, 147}})
#define RGB_PAPAYAWHIP ((color_t){.model = RGB, {255, 239, 213}})
#define RGB_PEACHPUFF ((color_t){.model = RGB, {255, 218, 185}})
#define RGB_PERU ((color_t){.model = RGB, {205, 133, 63}})
#define RGB_PINK ((color_t){.model = RGB, {255, 192, 203}})
#define RGB_PLUM ((color_t){.model = RGB, {221, 160, 221}})
#define RGB_POWDERBLUE ((color_t){.model = RGB, {176, 224, 230}})
#define RGB_ROSYBROWN ((color_t){.model = RGB, {188, 143, 143}})
#define RGB_ROYALBLUE ((color_t){.model = RGB, {65, 105, 225}})
#define RGB_SADDLEBROWN ((color_t){.model = RGB, {139, 69, 19}})
#define RGB_SALMON ((color_t){.model = RGB, {250, 128, 114}})
#define RGB_SANDYBROWN ((color_t){.model = RGB, {244, 164, 96}})
#define RGB_SEAGREEN ((color_t){.model = RGB, {46, 139, 87}})
#define RGB_SEASHELL ((color_t){.model = RGB, {255, 245, 238}})
#define RGB_SIENNA ((color_t){.model = RGB, {160, 82, 45}})
#define RGB_SKYBLUE ((color_t){.model = RGB, {135, 206, 235}})
#define RGB_SLATEBLUE ((color_t){.model = RGB, {106, 90, 205}})
#define RGB_SLATEGRAY ((color_t){.model = RGB, {112, 128, 144}})
#define RGB_SLATEGREY ((color_t){.model = RGB, {112, 128, 144}})
#define RGB_SNOW ((color_t){.model = RGB, {255, 250, 250}})
#define RGB_SPRINGGREEN ((color_t){.model = RGB, {0, 255, 127}})
#define RGB_STEELBLUE ((color_t){.model = RGB, {70, 130, 180}})
#define RGB_TAN ((color_t){.model = RGB, {210, 180, 140}})
#define RGB_TEAL ((color_t){.model = RGB, {0, 128, 128}})
#define RGB_THISTLE ((color_t){.model = RGB, {216, 191, 216}})
#define RGB_TOMATO ((color_t){.model = RGB, {255, 99, 71}})
#define RGB_TURQUOISE ((color_t){.model = RGB, {64, 224, 208}})
#define RGB_VIOLET ((color_t){.model = RGB, {238, 130, 238}})
#define RGB_WHEAT ((color_t){.model = RGB, {245, 222, 179}})
#define RGB_WHITESMOKE ((color_t){.model = RGB, {245, 245, 245}})
#define RGB_YELLOW ((color_t){.model = RGB, {255, 255, 0}})
#define RGB_YELLOWGREEN ((color_t){.model = RGB, {154, 205, 50}})


enum MODEL_E {
  RGB = 2,
  HEX = 4,
  HSV = 8,
  HSL = 16,
};

enum CLOP_E {
  NEGATE = 128,
  CONVERSION = 256,
  SATURATE = 512,
  ROTATE = 1024,
  LIGHTEN = 4096,
  BRIGHTEN = 8192,
};


typedef struct {
  int model;
  float values[4];
} color_t;

/* max 4 colors are available for gradient */
typedef struct {
  int n, steps;
  color_t colors[4];
} gradient_t;

typedef struct {
  int op;
  int has_param;
  float param;
} clop_t;


clop_t createclop(int op, int requires_param, char *value);
color_t createcolor(int color_model, int value1, int value2, int value3, int value4);
color_t createrandom(void);
color_t creatergb(char *red, char *green, char *blue);
color_t createhex(char *hex);
color_t createhsv(char *hue, char *saturation, char *value);
color_t createhsl(char *hue, char *saturation, char *lightness);
int createpredefinedcolor(const char *arg, color_t *color);

color_t copy(color_t color);
color_t convert(color_t color, int convert_model);
color_t rgb2hex(color_t rgb);
color_t rgb2hsv(color_t rgb);
color_t rgb2hsl(color_t rgb);
color_t hex2rgb(color_t hex);
color_t hex2hsv(color_t hex);
color_t hex2hsl(color_t hex);
color_t hsv2rgb(color_t hsv);
color_t hsv2hex(color_t hsv);
color_t hsv2hsl(color_t hsv);
color_t hsl2rgb(color_t hsl);
color_t hsl2hex(color_t hsl);
color_t hsl2hsv(color_t hsl);

color_t negate(color_t color);
color_t negatergb(color_t rgb);
color_t negatehex(color_t hex);
color_t negatehsv(color_t hsv);
color_t negatehsl(color_t hsl);

color_t saturate(color_t color, float value);
color_t rotate(color_t color, float value);
color_t lighten(color_t color, float value);
color_t brighten(color_t color, float value);

void displaycolor(color_t color);
char *getcolorstr(color_t color);
void displaygradient(color_t *color, int color_n, int *percents);
void displaycomplementarycolor(color_t color);
void displaytriadiccolor(color_t color);

void usage(void);

#endif // COLORX_H_