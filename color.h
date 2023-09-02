#ifndef COLOR_COLOR_H
#define COLOR_COLOR_H

/* extra math functions */
#define MAX2(a, b)      (((a) > (b)) ? (a) : (b))
#define MIN2(a, b)      (((a) > (b)) ? (b) : (a))
#define MAX3(a, b, c)   MAX2((a), MAX2((b), (c)))
#define MIN3(a, b, c)   MIN2((a), MIN2((b), (c)))

#define EXIT_ON_FAILURE(args...) { \
      printf("color: "); \
      printf(args); \
      exit(1); \
    }
#define RGB_PREFIX(rgb) \
    int r = (int) round(rgb.values[0]), g = (int) round(rgb.values[1]), b = (int) round(rgb.values[2]); \
    printf("\033[38;2;%d;%d;%dm", 255 - r, 255 - g, 255 - b); /* fg */\
    printf("\033[48;2;%d;%d;%dm", r, g, b) /* bg */
#define RGB_SUFFIX printf("\033[0m\n")

enum MODEL_E {
    RGB = 2,
    HEX = 4,
    HSV = 8,
    HSL = 16,
};

enum CLOP_E {
    NEGATE      = 128,
    CONVERSION  = 256,
    SATURATE    = 512,
    ROTATE      = 1024,
    LIGHTEN     = 4096,
    BRIGHTEN    = 8192,
};

typedef struct {
    int model;
    float values[4];
} color_t;

typedef struct {
    int op;
    int has_param;
    float param;
} clop_t;

clop_t createclop(int op, int requires_param, char *value);

color_t creatergb(char *red, char *green, char *blue);
color_t createhex(char *hex);
color_t createhsv(char *hue, char *saturation, char *value);
color_t createhsl(char *hue, char *saturation, char *lightness);

int createpredefinedcolor(const char *arg, color_t *color);

color_t copy(color_t color);

color_t convert(color_t color, int convert_model);
static color_t rgb2hex(color_t rgb);
static color_t rgb2hsv(color_t rgb);
static color_t rgb2hsl(color_t rgb);
static color_t hex2rgb(color_t hex);
static color_t hex2hsv(color_t hex);
static color_t hex2hsl(color_t hex);
static color_t hsv2rgb(color_t hsv);
static color_t hsv2hex(color_t hsv);
static color_t hsv2hsl(color_t hsv);
static color_t hsl2rgb(color_t hsl);
static color_t hsl2hex(color_t hsl);
static color_t hsl2hsv(color_t hsl);

color_t negate(color_t color);
static color_t negatergb(color_t rgb);
static color_t negatehex(color_t hex);
static color_t negatehsv(color_t hsv);
static color_t negatehsl(color_t hsl);

color_t saturate(color_t color, float value);
color_t rotate(color_t color, float value);
color_t lighten(color_t color, float value);
color_t brighten(color_t color, float value);

void displaycolor(color_t color);
static void displayrgb(color_t rgb);
static void displayhex(color_t hex);
static void displayhsv(color_t hsv);
static void displayhsl(color_t hsv);

void usage(void);

#define MAXCLOPS                20
#define ANSI_BLACK              ((color_t) { .model = RGB, { 0, 0, 0, 255 } })
#define ANSI_SILVER             ((color_t) { .model = RGB, { 192, 192, 192, 255 } })
#define ANSI_GRAY               ((color_t) { .model = RGB, { 128, 128, 128, 255 } })
#define ANSI_WHITE              ((color_t) { .model = RGB, { 255, 255, 255, 255 } })
#define ANSI_MAROON             ((color_t) { .model = RGB, { 128, 0, 0 }})
#define ANSI_RED                ((color_t) { .model = RGB, { 128, 0, 128 }})
#define ANSI_PURPLE             ((color_t) { .model = RGB, { 128, 0, 128 } })
#define ANSI_FUCHSIA            ((color_t) { .model = RGB, { 255, 0, 255 } })
#define ANSI_GREEN              ((color_t) { .model = RGB, { 0, 128, 0 } })
#define ANSI_LIME               ((color_t) { .model = RGB, { 0, 255, 0 } })
#define ANSI_OLIVE              ((color_t) { .model = RGB, { 128, 128, 0 } })
#define ANSI_YELLOW             ((color_t) { .model = RGB, { 255, 255, 0 } })
#define ANSI_NAVY               ((color_t) { .model = RGB, { 0, 0, 128 } })
#define ANSI_BLUE               ((color_t) { .model = RGB, { 0, 0, 255 } })
#define ANSI_TEAL               ((color_t) { .model = RGB, { 0, 128, 128 } })
#define ANSI_AQUA               ((color_t) { .model = RGB, { 0, 255, 255 } })
#define ANSI_ALICEBLUE          ((color_t) { .model = RGB, { 240, 248, 255 } })
#define ANSI_ANTIQUEWHITE       ((color_t) { .model = RGB, { 250, 235, 215 } })
#define ANSI_AQUAMARINE         ((color_t) { .model = RGB, { 127, 255, 212 } })
#define ANSI_AZURE              ((color_t) { .model = RGB, { 240, 255, 255 } })
#define ANSI_BEIGE              ((color_t) { .model = RGB, { 245, 245, 220 } })
#define ANSI_BISQUE             ((color_t) { .model = RGB, { 255, 228, 196 } })
#define ANSI_BLANCHEDALMOND     ((color_t) { .model = RGB, { 255, 235, 205 } })
#define ANSI_BLUE               ((color_t) { .model = RGB, { 0, 0, 255 } })
#define ANSI_BLUEVIOLET         ((color_t) { .model = RGB, { 138, 43, 226 } })
#define ANSI_BROWN              ((color_t) { .model = RGB, { 165, 42, 42 } })
#define ANSI_BURLYWOOD          ((color_t) { .model = RGB, { 222, 184, 135 } })
#define ANSI_CADETBLUE          ((color_t) { .model = RGB, { 95, 158, 160 } })
#define ANSI_CHARTREUSE         ((color_t) { .model = RGB, { 127, 255, 0 } })
#define ANSI_CHOCOLATE          ((color_t) { .model = RGB, { 210, 105, 30 } })
#define ANSI_CORAL              ((color_t) { .model = RGB, { 255, 127, 80 } })
#define ANSI_CORNFLOWERBLUE     ((color_t) { .model = RGB, { 100, 149, 237 } })
#define ANSI_CORNSILK           ((color_t) { .model = RGB, { 255, 248, 220 } })
#define ANSI_CRIMSON            ((color_t) { .model = RGB, { 220, 20, 60 } })
#define ANSI_CYAN               ((color_t) { .model = RGB, { 0, 255, 255 } })
#define ANSI_DARKBLUE           ((color_t) { .model = RGB, { 0, 0, 139 } })
#define ANSI_DARKCYAN           ((color_t) { .model = RGB, { 0, 139, 139 } })
#define ANSI_DARKGOLDENROD      ((color_t) { .model = RGB, { 184, 134, 11 } })
#define ANSI_DARKGRAY           ((color_t) { .model = RGB, { 169, 169, 169 } })
#define ANSI_DARKGREEN          ((color_t) { .model = RGB, { 0, 100, 0 } })
#define ANSI_DARKGREY           ((color_t) { .model = RGB, { 169, 169, 169 } })
#define ANSI_DARKKHAKI          ((color_t) { .model = RGB, { 189, 183, 107 } })
#define ANSI_DARKMAGENTA        ((color_t) { .model = RGB, { 139, 0, 139 } })
#define ANSI_DARKOLIVEGREEN     ((color_t) { .model = RGB, { 85, 107, 47 } })
#define ANSI_DARKORANGE         ((color_t) { .model = RGB, { 255, 140, 0 } })
#define ANSI_DARKORCHID         ((color_t) { .model = RGB, { 153, 50, 204 } })
#define ANSI_DARKRED            ((color_t) { .model = RGB, { 139, 0, 0 } })
#define ANSI_DARKSALMON         ((color_t) { .model = RGB, { 233, 150, 122 } })
#define ANSI_DARKSEAGREEN       ((color_t) { .model = RGB, { 143, 188, 143 } })
#define ANSI_DARKSLATEBLUE      ((color_t) { .model = RGB, { 72, 61, 139 } })
#define ANSI_DARKSLATEGRAY      ((color_t) { .model = RGB, { 47, 79, 79 } })
#define ANSI_DARKSLATEGREY      ((color_t) { .model = RGB, { 47, 79, 79 } })
#define ANSI_DARKTURQUOISE      ((color_t) { .model = RGB, { 0, 206, 209 } })
#define ANSI_DARKVIOLET         ((color_t) { .model = RGB, { 148, 0, 211 } })
#define ANSI_DEEPPINK           ((color_t) { .model = RGB, { 255, 20, 147 } })
#define ANSI_DEEPSKYBLUE        ((color_t) { .model = RGB, { 0, 191, 255 } })
#define ANSI_DIMGRAY            ((color_t) { .model = RGB, { 105, 105, 105 } })
#define ANSI_DIMGREY            ((color_t) { .model = RGB, { 105, 105, 105 } })
#define ANSI_DODGERBLUE         ((color_t) { .model = RGB, { 30, 144, 255 } })
#define ANSI_FIREBRICK          ((color_t) { .model = RGB, { 178, 34, 34 } })
#define ANSI_FLORALWHITE        ((color_t) { .model = RGB, { 255, 250, 240 } })
#define ANSI_FORESTGREEN        ((color_t) { .model = RGB, { 34, 139, 34 } })
#define ANSI_GAINSBORO          ((color_t) { .model = RGB, { 220, 220, 220 } })
#define ANSI_GHOSTWHITE         ((color_t) { .model = RGB, { 248, 248, 255 } })
#define ANSI_GOLD               ((color_t) { .model = RGB, { 255, 215, 0 } })
#define ANSI_GOLDENROD          ((color_t) { .model = RGB, { 218, 165, 32 } })
#define ANSI_GREEN              ((color_t) { .model = RGB, { 0, 128, 0 } })
#define ANSI_GREENYELLOW        ((color_t) { .model = RGB, { 173, 255, 47 } })
#define ANSI_GREY               ((color_t) { .model = RGB, { 128, 128, 128 } })
#define ANSI_HONEYDEW           ((color_t) { .model = RGB, { 240, 255, 240 } })
#define ANSI_HOTPINK            ((color_t) { .model = RGB, { 255, 105, 180 } })
#define ANSI_INDIANRED          ((color_t) { .model = RGB, { 205, 92, 92 } })
#define ANSI_INDIGO             ((color_t) { .model = RGB, { 75, 0, 130 } })
#define ANSI_IVORY              ((color_t) { .model = RGB, { 255, 255, 240 } })
#define ANSI_KHAKI              ((color_t) { .model = RGB, { 240, 230, 140 } })
#define ANSI_LAVENDER           ((color_t) { .model = RGB, { 230, 230, 250 } })
#define ANSI_LAVENDERBLUSH      ((color_t) { .model = RGB, { 255, 240, 245 } })
#define ANSI_LAWNGREEN          ((color_t) { .model = RGB, { 124, 252, 0 } })
#define ANSI_LEMONCHIFFON       ((color_t) { .model = RGB, { 255, 250, 205 } })
#define ANSI_LIGHTBLUE          ((color_t) { .model = RGB, { 173, 216, 230 } })
#define ANSI_LIGHTCORAL         ((color_t) { .model = RGB, { 240, 128, 128 } })
#define ANSI_LIGHTCYAN          ((color_t) { .model = RGB, { 224, 255, 255 } })
#define ANSI_LIGHTGOLDENRODYELLOW  ((color_t) { .model = RGB, { 250, 250, 210 } })
#define ANSI_LIGHTGRAY          ((color_t) { .model = RGB, { 211, 211, 211 } })
#define ANSI_LIGHTGREEN         ((color_t) { .model = RGB, { 144, 238, 144 } })
#define ANSI_LIGHTGREY          ((color_t) { .model = RGB, { 211, 211, 211 } })
#define ANSI_LIGHTPINK          ((color_t) { .model = RGB, { 255, 182, 193 } })
#define ANSI_LIGHTSALMON        ((color_t) { .model = RGB, { 255, 160, 122 } })
#define ANSI_LIGHTSEAGREEN      ((color_t) { .model = RGB, { 32, 178, 170 } })
#define ANSI_LIGHTSKYBLUE       ((color_t) { .model = RGB, { 135, 206, 250 } })
#define ANSI_LIGHTSLATEGRAY     ((color_t) { .model = RGB, { 119, 136, 153 } })
#define ANSI_LIGHTSLATEGREY     ((color_t) { .model = RGB, { 119, 136, 153 } })
#define ANSI_LIGHTSTEELBLUE     ((color_t) { .model = RGB, { 176, 196, 222 } })
#define ANSI_LIGHTYELLOW        ((color_t) { .model = RGB, { 255, 255, 224 } })
#define ANSI_LIME               ((color_t) { .model = RGB, { 0, 255, 0 } })
#define ANSI_LIMEGREEN          ((color_t) { .model = RGB, { 50, 205, 50 } })
#define ANSI_LINEN              ((color_t) { .model = RGB, { 250, 240, 230 } })
#define ANSI_MAGENTA            ((color_t) { .model = RGB, { 255, 0, 255 } })
#define ANSI_MEDIUMAQUAMARINE   ((color_t) { .model = RGB, { 102, 205, 170 } })
#define ANSI_MEDIUMBLUE         ((color_t) { .model = RGB, { 0, 0, 205 } })
#define ANSI_MEDIUMORCHID       ((color_t) { .model = RGB, { 186, 85, 211 } })
#define ANSI_MEDIUMPURPLE       ((color_t) { .model = RGB, { 147, 112, 219 } })
#define ANSI_MEDIUMSEAGREEN     ((color_t) { .model = RGB, { 60, 179, 113 } })
#define ANSI_MEDIUMSLATEBLUE    ((color_t) { .model = RGB, { 123, 104, 238 } })
#define ANSI_MEDIUMSPRINGGREEN  ((color_t) { .model = RGB, { 0, 250, 154 } })
#define ANSI_MEDIUMTURQUOISE    ((color_t) { .model = RGB, { 72, 209, 204 } })
#define ANSI_MEDIUMVIOLETRED    ((color_t) { .model = RGB, { 199, 21, 133 } })
#define ANSI_MIDNIGHTBLUE       ((color_t) { .model = RGB, { 25, 25, 112 } })
#define ANSI_MINTCREAM          ((color_t) { .model = RGB, { 245, 255, 250 } })
#define ANSI_MISTYROSE          ((color_t) { .model = RGB, { 255, 228, 225 } })
#define ANSI_MOCCASIN           ((color_t) { .model = RGB, { 255, 228, 181 } })
#define ANSI_NAVAJOWHITE        ((color_t) { .model = RGB, { 255, 222, 173 } })
#define ANSI_NAVY               ((color_t) { .model = RGB, { 0, 0, 128 } })
#define ANSI_OLDLACE            ((color_t) { .model = RGB, { 253, 245, 230 } })
#define ANSI_OLIVE              ((color_t) { .model = RGB, { 128, 128, 0 } })
#define ANSI_OLIVEDRAB          ((color_t) { .model = RGB, { 107, 142, 35 } })
#define ANSI_ORANGE             ((color_t) { .model = RGB, { 255, 165, 0 } })
#define ANSI_ORANGERED          ((color_t) { .model = RGB, { 255, 69, 0 } })
#define ANSI_ORCHID             ((color_t) { .model = RGB, { 218, 112, 214 } })
#define ANSI_PALEGOLDENROD      ((color_t) { .model = RGB, { 238, 232, 170 } })
#define ANSI_PALEGREEN          ((color_t) { .model = RGB, { 152, 251, 152 } })
#define ANSI_PALETURQUOISE      ((color_t) { .model = RGB, { 175, 238, 238 } })
#define ANSI_PALEVIOLETRED      ((color_t) { .model = RGB, { 219, 112, 147 } })
#define ANSI_PAPAYAWHIP         ((color_t) { .model = RGB, { 255, 239, 213 } })
#define ANSI_PEACHPUFF          ((color_t) { .model = RGB, { 255, 218, 185 } })
#define ANSI_PERU               ((color_t) { .model = RGB, { 205, 133, 63 } })
#define ANSI_PINK               ((color_t) { .model = RGB, { 255, 192, 203 } })
#define ANSI_PLUM               ((color_t) { .model = RGB, { 221, 160, 221 } })
#define ANSI_POWDERBLUE         ((color_t) { .model = RGB, { 176, 224, 230 } })
#define ANSI_ROSYBROWN          ((color_t) { .model = RGB, { 188, 143, 143 } })
#define ANSI_ROYALBLUE          ((color_t) { .model = RGB, { 65, 105, 225 } })
#define ANSI_SADDLEBROWN        ((color_t) { .model = RGB, { 139, 69, 19 } })
#define ANSI_SALMON             ((color_t) { .model = RGB, { 250, 128, 114 } })
#define ANSI_SANDYBROWN         ((color_t) { .model = RGB, { 244, 164, 96 } })
#define ANSI_SEAGREEN           ((color_t) { .model = RGB, { 46, 139, 87 } })
#define ANSI_SEASHELL           ((color_t) { .model = RGB, { 255, 245, 238 } })
#define ANSI_SIENNA             ((color_t) { .model = RGB, { 160, 82, 45 } })
#define ANSI_SKYBLUE            ((color_t) { .model = RGB, { 135, 206, 235 } })
#define ANSI_SLATEBLUE          ((color_t) { .model = RGB, { 106, 90, 205 } })
#define ANSI_SLATEGRAY          ((color_t) { .model = RGB, { 112, 128, 144 } })
#define ANSI_SLATEGREY          ((color_t) { .model = RGB, { 112, 128, 144 } })
#define ANSI_SNOW               ((color_t) { .model = RGB, { 255, 250, 250 } })
#define ANSI_SPRINGGREEN        ((color_t) { .model = RGB, { 0, 255, 127 } })
#define ANSI_STEELBLUE          ((color_t) { .model = RGB, { 70, 130, 180 } })
#define ANSI_TAN                ((color_t) { .model = RGB, { 210, 180, 140 } })
#define ANSI_TEAL               ((color_t) { .model = RGB, { 0, 128, 128 } })
#define ANSI_THISTLE            ((color_t) { .model = RGB, { 216, 191, 216 } })
#define ANSI_TOMATO             ((color_t) { .model = RGB, { 255, 99, 71 } })
#define ANSI_TURQUOISE          ((color_t) { .model = RGB, { 64, 224, 208 } })
#define ANSI_VIOLET             ((color_t) { .model = RGB, { 238, 130, 238 } })
#define ANSI_WHEAT              ((color_t) { .model = RGB, { 245, 222, 179 } })
#define ANSI_WHITESMOKE         ((color_t) { .model = RGB, { 245, 245, 245 } })
#define ANSI_YELLOW             ((color_t) { .model = RGB, { 255, 255, 0 } })
#define ANSI_YELLOWGREEN        ((color_t) { .model = RGB, { 154, 205, 50 } })


#endif //COLOR_COLOR_H
