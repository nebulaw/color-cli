#include <assert.h>
#include <getopt.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <time.h>


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
char *getcolorstr(color_t color);
void displaygradient(color_t *color, int color_n, int *percents);
void displaycomplementarycolor(color_t color);
void displaytriadiccolor(color_t color);

void usage(void);

static struct option arg_options[] = {{ "negate", no_argument, 0, 'n' },
                                      { "to", required_argument, 0, 't' },
                                      { "saturate", required_argument, 0, 's' },
                                      { "rotate", required_argument, 0, 'r' },
                                      { "lighten", required_argument, 0, 'l' },
                                      { "brighten", required_argument, 0, 'b' },
                                      { 0, 0, 0, 0 }};

int main(int argc, char **argv)
{
  char **argv_ptr = argv;
  assert(*argv++ != NULL);
  clop_t CLOPS[MAXCLOPS];
  int COLOR_MODEL = RGB, clp = 0;
  color_t color;
  char *var1, *var2, *var3;
  int is_complement = 0;
  srand(time(0));

  /* no argument error */
  if (*argv == NULL) {
    usage();
    exit(-1);
  }
  if (strcmp(*argv, "--help") == 0) {
    usage();
    exit(0);
  }

  /* check if user wants complement */
  if (strcmp(*argv, "complement") == 0) {
    is_complement = 1;
    argv++;
  }

  /* parse color model */
  COLOR_MODEL = strcmp(*argv, "rgb") == 0 ? RGB
    : strcmp(*argv, "hex") == 0 ? HEX
      : strcmp(*argv, "hsv") == 0 ? HSV
        : strcmp(*argv, "hsl") == 0 ? HSL : 0;

  /* parse color values from arguments and create color */
  if (COLOR_MODEL == HEX) {
    if (*(++argv) == NULL) {
      fprintf(stderr, "color: invalid %s color format.\n", *(--argv));
      fprintf(stderr, "Try 'color --help' for more options.\n");
      exit(-1);
    } else {
      color = createhex(*argv);
    }
  } else if ((COLOR_MODEL == RGB || COLOR_MODEL == HSV || COLOR_MODEL == HSL)) {
    if (argc > 4) {
      var1 = *(++argv);
      var2 = *(++argv);
      var3 = *(++argv);
    } else {
      fprintf(stderr, "color: invalid %s color format.\n", *argv);
      fprintf(stderr, "Try 'color --help' for more options.\n");
      exit(-1);
    }
    /* create color */
    switch (COLOR_MODEL) {
    case RGB:color = creatergb(var1, var2, var3);
      break;
    case HSV:color = createhsv(var1, var2, var3);
      break;
    case HSL:color = createhsl(var1, var2, var3);
      break;
    }
  } else if (createpredefinedcolor(*argv, &color)) {
    /* ignored line */
  } else if (!strcmp(*argv, "random")) {
    color = createrandom();
  } else {
    fprintf(stderr, "color: invalid command %s.\n", *argv);
    fprintf(stderr, "Try 'color --help' for more options.\n");
    exit(1);
  }

  /* parse options */
  int op;
  while ((op = getopt_long(argc, argv_ptr, "ns:r:l:b:t:", arg_options, NULL)) != -1) {
    switch (op) {
    case 'n': CLOPS[clp++] = createclop(NEGATE, 0, "");
      break;
    case 's': CLOPS[clp++] = createclop(SATURATE, 1, optarg);
      break;
    case 'r': CLOPS[clp++] = createclop(ROTATE, 1, optarg);
      break;
    case 'l': CLOPS[clp++] = createclop(LIGHTEN, 1, optarg);
      break;
    case 'b': CLOPS[clp++] = createclop(BRIGHTEN, 1, optarg);
      break;
    case 't': CLOPS[clp++] = createclop(CONVERSION, 1, optarg);
      break;
    case '?':exit(-1);
    default:break;
    }
  }

  /* apply clops */
  int i;
  for (i = 0; i < clp; i++) {
    switch (CLOPS[i].op) {
    case NEGATE: color = negate(color);
      break;
    case CONVERSION: color = convert(color, (int)CLOPS[i].param);
      break;
    case SATURATE: color = saturate(color, CLOPS[i].param);
      break;
    case ROTATE: color = rotate(color, CLOPS[i].param);
      break;
    case LIGHTEN: color = lighten(color, CLOPS[i].param);
      break;
    case BRIGHTEN: color = brighten(color, CLOPS[i].param);
      break;
    }
  }

  /* display the result*/
  if (is_complement) {
    displaycomplementarycolor(color);
  } else {
    displaycolor(color);
  }

  return 0;
}

clop_t createclop(int op, int has_param, char *value)
{
  float val = RGB;
  if (has_param && op != CONVERSION) {
    val = strspn(value, "+-.0123456789") == strlen(value) ? atof(value) : -101;
    if ((val < -100 || 100 < val) && op != ROTATE) EXIT_ON_FAILURE("invalid value: %s", value)
  } else if (has_param && op == CONVERSION) {
    if (strcmp(value, "rgb") == 0) {
      val = RGB;
    } else if (strcmp(value, "hex") == 0) {
      val = HEX;
    } else if (strcmp(value, "hsv") == 0) {
      val = HSV;
    } else if (strcmp(value, "hsl") == 0) {
      val = HSL;
    } else {
      fprintf(stderr, "color: invalid convert type %s.\n", optarg);
      fprintf(stderr, "Try 'color --help' for more options.\n");
      exit(-1);
    }
  }
  clop_t clop;
  clop.op = op;
  clop.has_param = has_param;
  clop.param = val;
  return clop;
}

color_t createcolor(int color_model, int value1, int value2, int value3, int value4)
{
  color_t color;
  color.model = color_model;
  color.values[0] = value1;
  color.values[1] = value2;
  color.values[2] = value3;
  color.values[3] = value4;
  return color;
}

color_t createrandom(void)
{
  color_t color = createcolor(HSL, rand() % 360, rand() % 101, rand() % 101, 255);
  color = hsl2rgb(color);
  return color;
}

color_t creatergb(char *red, char *green, char *blue)
{
  /* checking if arguments are numbers */
  float r = strspn(red, ".0123456789") == strlen(red) ? atof(red) : -1;
  float g = strspn(green, ".0123456789") == strlen(green) ? atof(green) : -1;
  float b = strspn(blue, ".0123456789") == strlen(blue) ? atof(blue) : -1;
  /* range validation */
  if (!(0 <= r && r < 256)) EXIT_ON_FAILURE("invalid red value: %s\n", red)
  if (!(0 <= g && g < 256)) EXIT_ON_FAILURE("invalid green value: %s\n", green)
  if (!(0 <= b && b < 256)) EXIT_ON_FAILURE("invalid blue value: %s\n", blue)
  color_t rgb_color = createcolor(RGB, r, g, b, 255);
  return rgb_color;
}

color_t createhex(char *hex)
{
  if (strlen(hex) < 4 || strlen(hex) > 8) EXIT_ON_FAILURE("invalid hex format: %s\n", hex)
  /* extract prefix from hex value */
  int offset = 0;
  switch (*hex) {
  case '#': offset += 1;
    break;
  case '0':
    switch (*(hex + 1)) {
    case 'x':
    case 'X': offset += 2;
      break;
    default: EXIT_ON_FAILURE("invalid hex format: %s\n", hex)
    }
    break;
  default: EXIT_ON_FAILURE("invalid hex format: %s\n", hex)
  }
  /* validate actual value */
  if (strspn(hex + offset, "0123456789abcdefABCDEF") != strlen(hex + offset) || strlen(hex + offset) != 6) {
    EXIT_ON_FAILURE("invalid hex format: %s\n", hex)
  }
  int r, g, b;
  sscanf(hex + offset, "%02x%02x%02x", &r, &g, &b);
  color_t hex_color = createcolor(HEX, ((r & 0xFF) << 16) | ((g & 0xFF) << 8) | ((b & 0xFF)), 0, 0, 255);
  return hex_color;
}

color_t createhsv(char *hue, char *saturation, char *value)
{
  float h = strspn(hue, ".0123456789") == strlen(hue) ? atof(hue) : -1;
  float s = strspn(saturation, ".0123456789") == strlen(saturation) ? atof(saturation) : -1;
  float v = strspn(value, ".0123456789") == strlen(value) ? atof(value) : -1;
  /* range validation */
  if (h < 0) EXIT_ON_FAILURE("invalid hue value: %s\n", hue)
  if (!(0 <= s && s <= 100)) EXIT_ON_FAILURE("invalid saturation value: %s\n", saturation)
  if (!(0 <= v && v <= 100)) EXIT_ON_FAILURE("invalid brightness value: %s\n", value)
  color_t hsv_color = createcolor(HSV, fmodf(h, 360.f), s, v, 255);
  return hsv_color;
}

color_t createhsl(char *hue, char *saturation, char *lightness)
{
  /* validate values are numbers */
  float h = strspn(hue, ".0123456789") == strlen(hue) ? atof(hue) : -1;
  float s = strspn(saturation, ".0123456789") == strlen(saturation) ? atof(saturation) : -1;
  float l = strspn(lightness, ".0123456789") == strlen(lightness) ? atof(lightness) : -1;
  /* range validation */
  if (h < 0) EXIT_ON_FAILURE("invalid hue value: %s\n", hue)
  if (!(0 <= s && s <= 100)) EXIT_ON_FAILURE("invalid saturation value: %s\n", saturation)
  if (!(0 <= l && l <= 100)) EXIT_ON_FAILURE("invalid lightness value: %s\n", lightness)
  color_t hsl_color = createcolor(HSL, fmodf(h, 360.f), s, l, 255);
  return hsl_color;
}

color_t copy(color_t color)
{
  color_t copy;
  copy.model = color.model;
  for (int i = 0; i < (int)(sizeof(color.values) / sizeof(color.values[0])); i++) {
    copy.values[i] = color.values[i];
  }
  return copy;
}

color_t convert(color_t color, int convert_model)
{
  switch (color.model) {
  case RGB:
    switch (convert_model) {
    case RGB:return copy(color);
    case HEX:return rgb2hex(color);
    case HSV:return rgb2hsv(color);
    case HSL:return rgb2hsl(color);
    default: EXIT_ON_FAILURE("invalid convert model\n")
    }
    break;
  case HEX:
    switch (convert_model) {
    case RGB:return hex2rgb(color);
    case HEX:return copy(color);
    case HSV:return hex2hsv(color);
    case HSL:return hex2hsl(color);
    default: EXIT_ON_FAILURE("invalid convert model\n")
    }
  case HSV:
    switch (convert_model) {
    case RGB:return hsv2rgb(color);
    case HEX:return hsv2hex(color);
    case HSV:return copy(color);
    case HSL:return hsv2hsl(color);
    default: EXIT_ON_FAILURE("invalid convert model\n")
    }
    break;
  case HSL:
    switch (convert_model) {
    case RGB:return hsl2rgb(color);
    case HEX:return hsl2hex(color);
    case HSV:return hsl2hsv(color);
    case HSL:return copy(color);
    default: EXIT_ON_FAILURE("invalid convert model\n")
    }
    break;
  }
  return (color_t){};
}

static color_t rgb2hex(color_t rgb)
{
  color_t hex;
  hex.model = HEX;
  hex.values[0] = (((int)roundf((rgb.values[0])) & 0xFF) << 16)
    | (((int)roundf((rgb.values[1])) & 0xFF) << 8)
    | (((int)roundf(rgb.values[2])) & 0xFF);
  return hex;
}

static color_t rgb2hsv(color_t rgb)
{
  float r = rgb.values[0] / 255.f, g = rgb.values[1] / 255.f, b = rgb.values[2] / 255.f;
  float max = MAX3(r, g, b), min = MIN3(r, g, b);
  float hue = fmodf(
    (hue = max == min
      ? 0.f
      : max == r
        ? 60.f * (fmodf((g - b), 6.f) / (max - min))
        : max == g
          ? 60.f * (2.f + (b - r) / (max - min))
          : 60.f * (4.f + (r - g) / (max - min))
    ) < 0.f
      ? hue + 360
      : hue,
    360.f
  );
  float value = max;
  float saturation = max == 0 ? 0 : (max - min) / max;
  color_t hsv_color = createcolor(HSV, hue, saturation * 100.f, value * 100.f, 255);
  return hsv_color;
}

static color_t rgb2hsl(color_t rgb)
{
  float r = rgb.values[0] / 255.f, g = rgb.values[1] / 255.f, b = rgb.values[2] / 255.f;
  float max = MAX3(r, g, b), min = MIN3(r, g, b);
  float hue = fmodf(
    (hue = max == min
      ? 0.f
      : max == r
        ? 60.f * (fmodf((g - b), 6.f) / (max - min))
        : max == g
          ? 60.f * (2.f + (b - r) / (max - min))
          : 60.f * (4.f + (r - g) / (max - min))
    ) < 0.f
      ? hue + 360
      : hue,
    360.f
  );
  float luminosity = (max + min) / 2;
  float saturation = (max == min) ? 0 : ((max - min) / (1 - fabsf(2 * luminosity - 1)));
  color_t hsl_color = createcolor(HSL, hue, saturation * 100.f, luminosity * 100.f, 255);
  return hsl_color;
}

static color_t hex2rgb(color_t hex)
{
  color_t rgb_color = createcolor(
    RGB,
    ((int)roundf(hex.values[0]) >> 16) & 0xFF,
    ((int)roundf(hex.values[0]) >> 8) & 0xFF,
    (int)roundf(hex.values[0]) & 0xFF,
    255
  );
  return rgb_color;
}

static color_t hex2hsv(color_t hex)
{
  return rgb2hsv(hex2rgb(hex));
}

static color_t hex2hsl(color_t hex)
{
  return rgb2hsl(hex2rgb(hex));
}

static color_t hsv2rgb(color_t hsv)
{
  float h = hsv.values[0], s = hsv.values[1] / 100.f, v = hsv.values[2] / 100.f;
  float c = v * s, x = c * (1 - fabsf(fmodf(h / 60.f, 2) - 1)), m = v - c;
  float r = 0, g = 0, b = 0;
  if (0 <= h && h < 60) {
    r = c, g = x, b = 0;
  } else if (60 <= h && h < 120) {
    r = x, g = c, b = 0;
  } else if (120 <= h && h < 180) {
    r = 0, g = c, b = x;
  } else if (180 <= h && h < 240) {
    r = 0, g = x, b = c;
  } else if (240 <= h && h < 300) {
    r = x, g = 0, b = c;
  } else if (300 <= h && h < 360) {
    r = c, g = 0, b = x;
  }
  color_t rgb_color = createcolor(RGB, (r + m) * 255.f, (g + m) * 255.f, (b + m) * 255.f, 255);
  return rgb_color;
}

static color_t hsv2hex(color_t hsv)
{
  return rgb2hex(hsv2rgb(hsv));
}

static color_t hsv2hsl(color_t hsv)
{
  float h = hsv.values[0];
  float s_hsv = hsv.values[1] / 100.f;
  float v_hsv = hsv.values[2] / 100.f;
  float l = v_hsv - v_hsv * s_hsv / 2;
  float s = l == 0 || l == 1 ? 0 : (v_hsv - l) / MIN2(l, 1 - l);
  color_t hsl_color = createcolor(HSL, h, s * 100.f, l * 100.f, 255);
  return hsl_color;
}

static color_t hsl2rgb(color_t hsl)
{
  float h = hsl.values[0], s = hsl.values[1] / 100.f, l = hsl.values[2] / 100.f;
  float c = (1.f - fabsf(2.f * l - 1.f)) * s;
  float x = c * (1 - fabsf(fmodf(h / 60.f, 2.f) - 1.f));
  float m = l - c / 2.f;
  float r = 0, g = 0, b = 0;
  if (0 <= h && h < 60) {
    r = c, g = x, b = 0;
  } else if (60 <= h && h < 120) {
    r = x, g = c, b = 0;
  } else if (120 <= h && h < 180) {
    r = 0, g = c, b = x;
  } else if (180 <= h && h < 240) {
    r = 0, g = x, b = c;
  } else if (240 <= h && h < 300) {
    r = x, g = 0, b = c;
  } else if (300 <= h && h < 360) {
    r = c, g = 0, b = x;
  }
  color_t rgb_color = createcolor(RGB, (r + m) * 255.f, (g + m) * 255.f, (b + m) * 255.f, 255);
  return rgb_color;
}

static color_t hsl2hex(color_t hsl)
{
  return rgb2hex(hsl2rgb(hsl));
}

static color_t hsl2hsv(color_t hsl)
{
  float h = hsl.values[0];
  float s = hsl.values[1] / 100.f;
  float l = hsl.values[2] / 100.f;
  float v = l + s * MIN2(l, 1 - l);
  s = v == 0.f ? 0.f : (2.f - 2.f * l / v);
  color_t hsv_color = createcolor(HSV, h, s * 100.f, v * 100.f, 255);
  return hsv_color;
}

color_t negate(color_t color)
{
  switch (color.model) {
  case RGB: return negatergb(color);
  case HEX: return negatehex(color);
  case HSV: return negatehsv(color);
  case HSL: return negatehsl(color);
  default: EXIT_ON_FAILURE("invalid color model\n")
  }
}

static color_t negatergb(color_t rgb)
{
  color_t negated_rgb = copy(rgb);
  negated_rgb.values[0] = fmodf(255 - negated_rgb.values[0], 256);
  negated_rgb.values[1] = fmodf(255 - negated_rgb.values[1], 256);
  negated_rgb.values[2] = fmodf(255 - negated_rgb.values[2], 256);
  return negated_rgb;
}

static color_t negatehex(color_t hex)
{
  return convert(negate(convert(hex, RGB)), HEX);
}

static color_t negatehsv(color_t hsv)
{
  return convert(negate(convert(hsv, RGB)), HSV);
}

static color_t negatehsl(color_t hsl)
{
  return convert(negate(convert(hsl, RGB)), HSL);
}

color_t saturate(color_t color, float value)
{
  int color_model = color.model;
  color = convert(color, HSL);
  color.values[1] =
    value >= 0
      ? color.values[1] + (100.0f - color.values[1]) * (value / 100.0f)
      : color.values[1] + color.values[1] * (value / 100.f);
  color = convert(color, color_model);
  return color;
}

color_t rotate(color_t color, float value)
{
  int color_model = color.model;
  color = convert(color, HSL);
  float new_hue =
    (new_hue = color.values[0] + value) < 0
      ? (float)(((float)(int)(-new_hue) / 360 + 1) * 360 + new_hue)
      : new_hue;
  color.values[0] = fmodf(new_hue, 360);
  color = convert(color, color_model);
  return color;
}

color_t lighten(color_t color, float value)
{
  int color_model = color.model;
  color = convert(color, HSL);
  color.values[2] =
    value >= 0
      ? color.values[2] + (100.0f - color.values[2]) * (value / 100.0f)
      : color.values[2] + color.values[2] * (value / 100.f);
  color = convert(color, color_model);
  return color;
}

color_t brighten(color_t color, float value)
{
  int color_model = color.model;
  color = convert(color, HSV);
  color.values[2] =
    value >= 0
      ? color.values[2] + (100.0f - color.values[2]) * (value / 100.0f)
      : color.values[2] + color.values[2] * (value / 100.f);
  color = convert(color, color_model);
  return color;
}

void displaycolor(color_t color)
{
  printf("%s\n", getcolorstr(color));
}

char *getcolorstr(color_t color)
{
  // alloc mem for ret string
  char *colorstr = (char *)malloc(sizeof(char) * LINE_LEN);
  // fill foreground and background color
  color_t rgbrepr = color.model == RGB ? color : convert(color, RGB);
  int r = (int)round(rgbrepr.values[0]), g = (int)round(rgbrepr.values[1]), b = (int)round(rgbrepr.values[2]);
  int length = 0;
  length += sprintf(colorstr, "\033[38;2;%d;%d;%dm", 255 - r, 255 - g, 255 - b);
  length += sprintf(colorstr + length, "\033[48;2;%d;%d;%dm", r, g, b);
  // concatenate color model values
  switch (color.model) {
  case RGB:length += sprintf(colorstr + length, "rgb(%.0f, %.0f, %.0f)", color.values[0], color.values[1], color.values[2]);
    break;
  case HEX: length += sprintf(colorstr + length, "#%06X", (int)round(color.values[0]));
    break;
  case HSV:
    length += sprintf(colorstr + length, "hsv(%.2f, %.2f%%, %.2f%%)", color.values[0], color.values[1], color.values[2]);
    break;
  case HSL:
    length += sprintf(colorstr + length, "hsl(%.2f, %.2f%%, %.2f%%)", color.values[0], color.values[1], color.values[2]);
    break;
  }
  // reset color
  sprintf(colorstr + length, "\033[0m");
  return colorstr;
}

void displaycomplementarycolor(color_t color)
{
  printf("%s\n", getcolorstr(color));
  printf("%s\n", getcolorstr(negate(color)));
}

void usage(void)
{
  puts("Usage: color [complement] [model] [values] [options]");
  puts("   or: color [predefined-color] [options]");
  puts("   or: color random [options]\n");

  puts("Examples:");
  puts("    color rgb 244 180 220 -nt hex");
  puts("    color hex 0xA122FF -r -20 --saturate 23");
  puts("    color lightcyan --to hsv\n");

  puts("Models:");
  puts("    rgb             RGB values are between 0-255.");
  puts("    hex             HEX is a 6-bit integer. valid prefixes: 0x, 0X, #.");
  puts("    hsv             Hue is 0-359deg, S, V are between 0-100%.");
  puts("    hsl             Same specifications as HSV color model.\n");

  puts("Predefined Colors:");
  puts("    Are all CSS colors such as: antiquewhite, darkgray... . They are NOT");
  puts("    case sensitive so gold and gOLd both refer to the same color.\n");
  puts("Options:");
  puts("    -n, --negate    Output negative value.");
  puts("    -t, --to        Convert to the specific color model.");
  puts("    -r, --rotate    Rotate the hue value of color, parameter can be");
  puts("                        negative or positive float.");
  puts("    -s, --saturate  Saturate color, parameter is between -100 and 100.");
  puts("    -l, --lighten   Increase or decrease luminosity of color. Range is");
  puts("                        between -100 and 100.");
  puts("    -b, --brighten  Control brightness. Range is between -100 and 100");
}

int createpredefinedcolor(const char *arg, color_t *color)
{
  if (!strcasecmp(arg, "white")) { *color = RGB_WHITE; }
  else if (!strcasecmp(arg, "black")) { *color = RGB_BLACK; }
  else if (!strcasecmp(arg, "aliceblue")) { *color = RGB_ALICEBLUE; }
  else if (!strcasecmp(arg, "antiquewhite")) { *color = RGB_ANTIQUEWHITE; }
  else if (!strcasecmp(arg, "aqua")) { *color = RGB_AQUA; }
  else if (!strcasecmp(arg, "aquamarine")) { *color = RGB_AQUAMARINE; }
  else if (!strcasecmp(arg, "azure")) { *color = RGB_AZURE; }
  else if (!strcasecmp(arg, "beige")) { *color = RGB_BEIGE; }
  else if (!strcasecmp(arg, "bisque")) { *color = RGB_BISQUE; }
  else if (!strcasecmp(arg, "black")) { *color = RGB_BLACK; }
  else if (!strcasecmp(arg, "blanchedalmond")) { *color = RGB_BLANCHEDALMOND; }
  else if (!strcasecmp(arg, "blue")) { *color = RGB_BLUE; }
  else if (!strcasecmp(arg, "blueviolet")) { *color = RGB_BLUEVIOLET; }
  else if (!strcasecmp(arg, "brown")) { *color = RGB_BROWN; }
  else if (!strcasecmp(arg, "burlywood")) { *color = RGB_BURLYWOOD; }
  else if (!strcasecmp(arg, "cadetblue")) { *color = RGB_CADETBLUE; }
  else if (!strcasecmp(arg, "chartreuse")) { *color = RGB_CHARTREUSE; }
  else if (!strcasecmp(arg, "chocolate")) { *color = RGB_CHOCOLATE; }
  else if (!strcasecmp(arg, "coral")) { *color = RGB_CORAL; }
  else if (!strcasecmp(arg, "cornflowerblue")) { *color = RGB_CORNFLOWERBLUE; }
  else if (!strcasecmp(arg, "cornsilk")) { *color = RGB_CORNSILK; }
  else if (!strcasecmp(arg, "crimson")) { *color = RGB_CRIMSON; }
  else if (!strcasecmp(arg, "cyan")) { *color = RGB_CYAN; }
  else if (!strcasecmp(arg, "darkblue")) { *color = RGB_DARKBLUE; }
  else if (!strcasecmp(arg, "darkcyan")) { *color = RGB_DARKCYAN; }
  else if (!strcasecmp(arg, "darkgoldenrod")) { *color = RGB_DARKGOLDENROD; }
  else if (!strcasecmp(arg, "darkgray")) { *color = RGB_DARKGRAY; }
  else if (!strcasecmp(arg, "darkgreen")) { *color = RGB_DARKGREEN; }
  else if (!strcasecmp(arg, "darkgrey")) { *color = RGB_DARKGREY; }
  else if (!strcasecmp(arg, "darkkhaki")) { *color = RGB_DARKKHAKI; }
  else if (!strcasecmp(arg, "darkmagenta")) { *color = RGB_DARKMAGENTA; }
  else if (!strcasecmp(arg, "darkolivegreen")) { *color = RGB_DARKOLIVEGREEN; }
  else if (!strcasecmp(arg, "darkorange")) { *color = RGB_DARKORANGE; }
  else if (!strcasecmp(arg, "darkorchid")) { *color = RGB_DARKORCHID; }
  else if (!strcasecmp(arg, "darkred")) { *color = RGB_DARKRED; }
  else if (!strcasecmp(arg, "darksalmon")) { *color = RGB_DARKSALMON; }
  else if (!strcasecmp(arg, "darkseagreen")) { *color = RGB_DARKSEAGREEN; }
  else if (!strcasecmp(arg, "darkslateblue")) { *color = RGB_DARKSLATEBLUE; }
  else if (!strcasecmp(arg, "darkslategray")) { *color = RGB_DARKSLATEGRAY; }
  else if (!strcasecmp(arg, "darkslategrey")) { *color = RGB_DARKSLATEGREY; }
  else if (!strcasecmp(arg, "darkturquoise")) { *color = RGB_DARKTURQUOISE; }
  else if (!strcasecmp(arg, "darkviolet")) { *color = RGB_DARKVIOLET; }
  else if (!strcasecmp(arg, "deeppink")) { *color = RGB_DEEPPINK; }
  else if (!strcasecmp(arg, "deepskyblue")) { *color = RGB_DEEPSKYBLUE; }
  else if (!strcasecmp(arg, "dimgray")) { *color = RGB_DIMGRAY; }
  else if (!strcasecmp(arg, "dimgrey")) { *color = RGB_DIMGREY; }
  else if (!strcasecmp(arg, "dodgerblue")) { *color = RGB_DODGERBLUE; }
  else if (!strcasecmp(arg, "firebrick")) { *color = RGB_FIREBRICK; }
  else if (!strcasecmp(arg, "floralwhite")) { *color = RGB_FLORALWHITE; }
  else if (!strcasecmp(arg, "forestgreen")) { *color = RGB_FORESTGREEN; }
  else if (!strcasecmp(arg, "fuchsia")) { *color = RGB_FUCHSIA; }
  else if (!strcasecmp(arg, "gainsboro")) { *color = RGB_GAINSBORO; }
  else if (!strcasecmp(arg, "ghostwhite")) { *color = RGB_GHOSTWHITE; }
  else if (!strcasecmp(arg, "gold")) { *color = RGB_GOLD; }
  else if (!strcasecmp(arg, "goldenrod")) { *color = RGB_GOLDENROD; }
  else if (!strcasecmp(arg, "gray")) { *color = RGB_GRAY; }
  else if (!strcasecmp(arg, "green")) { *color = RGB_GREEN; }
  else if (!strcasecmp(arg, "greenyellow")) { *color = RGB_GREENYELLOW; }
  else if (!strcasecmp(arg, "grey")) { *color = RGB_GREY; }
  else if (!strcasecmp(arg, "honeydew")) { *color = RGB_HONEYDEW; }
  else if (!strcasecmp(arg, "hotpink")) { *color = RGB_HOTPINK; }
  else if (!strcasecmp(arg, "indianred")) { *color = RGB_INDIANRED; }
  else if (!strcasecmp(arg, "indigo")) { *color = RGB_INDIGO; }
  else if (!strcasecmp(arg, "ivory")) { *color = RGB_IVORY; }
  else if (!strcasecmp(arg, "khaki")) { *color = RGB_KHAKI; }
  else if (!strcasecmp(arg, "lavender")) { *color = RGB_LAVENDER; }
  else if (!strcasecmp(arg, "lavenderblush")) { *color = RGB_LAVENDERBLUSH; }
  else if (!strcasecmp(arg, "lawngreen")) { *color = RGB_LAWNGREEN; }
  else if (!strcasecmp(arg, "lemonchiffon")) { *color = RGB_LEMONCHIFFON; }
  else if (!strcasecmp(arg, "lightblue")) { *color = RGB_LIGHTBLUE; }
  else if (!strcasecmp(arg, "lightcoral")) { *color = RGB_LIGHTCORAL; }
  else if (!strcasecmp(arg, "lightcyan")) { *color = RGB_LIGHTCYAN; }
  else if (!strcasecmp(arg, "lightgoldenrodyellow")) { *color = RGB_LIGHTGOLDENRODYELLOW; }
  else if (!strcasecmp(arg, "lightgray")) { *color = RGB_LIGHTGRAY; }
  else if (!strcasecmp(arg, "lightgreen")) { *color = RGB_LIGHTGREEN; }
  else if (!strcasecmp(arg, "lightgrey")) { *color = RGB_LIGHTGREY; }
  else if (!strcasecmp(arg, "lightpink")) { *color = RGB_LIGHTPINK; }
  else if (!strcasecmp(arg, "lightsalmon")) { *color = RGB_LIGHTSALMON; }
  else if (!strcasecmp(arg, "lightseagreen")) { *color = RGB_LIGHTSEAGREEN; }
  else if (!strcasecmp(arg, "lightskyblue")) { *color = RGB_LIGHTSKYBLUE; }
  else if (!strcasecmp(arg, "lightslategray")) { *color = RGB_LIGHTSLATEGRAY; }
  else if (!strcasecmp(arg, "lightslategrey")) { *color = RGB_LIGHTSLATEGREY; }
  else if (!strcasecmp(arg, "lightsteelblue")) { *color = RGB_LIGHTSTEELBLUE; }
  else if (!strcasecmp(arg, "lightyellow")) { *color = RGB_LIGHTYELLOW; }
  else if (!strcasecmp(arg, "lime")) { *color = RGB_LIME; }
  else if (!strcasecmp(arg, "limegreen")) { *color = RGB_LIMEGREEN; }
  else if (!strcasecmp(arg, "linen")) { *color = RGB_LINEN; }
  else if (!strcasecmp(arg, "magenta")) { *color = RGB_MAGENTA; }
  else if (!strcasecmp(arg, "maroon")) { *color = RGB_MAROON; }
  else if (!strcasecmp(arg, "mediumaquamarine")) { *color = RGB_MEDIUMAQUAMARINE; }
  else if (!strcasecmp(arg, "mediumblue")) { *color = RGB_MEDIUMBLUE; }
  else if (!strcasecmp(arg, "mediumorchid")) { *color = RGB_MEDIUMORCHID; }
  else if (!strcasecmp(arg, "mediumpurple")) { *color = RGB_MEDIUMPURPLE; }
  else if (!strcasecmp(arg, "mediumseagreen")) { *color = RGB_MEDIUMSEAGREEN; }
  else if (!strcasecmp(arg, "mediumslateblue")) { *color = RGB_MEDIUMSLATEBLUE; }
  else if (!strcasecmp(arg, "mediumspringgreen")) { *color = RGB_MEDIUMSPRINGGREEN; }
  else if (!strcasecmp(arg, "mediumturquoise")) { *color = RGB_MEDIUMTURQUOISE; }
  else if (!strcasecmp(arg, "mediumvioletred")) { *color = RGB_MEDIUMVIOLETRED; }
  else if (!strcasecmp(arg, "midnightblue")) { *color = RGB_MIDNIGHTBLUE; }
  else if (!strcasecmp(arg, "mintcream")) { *color = RGB_MINTCREAM; }
  else if (!strcasecmp(arg, "mistyrose")) { *color = RGB_MISTYROSE; }
  else if (!strcasecmp(arg, "moccasin")) { *color = RGB_MOCCASIN; }
  else if (!strcasecmp(arg, "navajowhite")) { *color = RGB_NAVAJOWHITE; }
  else if (!strcasecmp(arg, "navy")) { *color = RGB_NAVY; }
  else if (!strcasecmp(arg, "oldlace")) { *color = RGB_OLDLACE; }
  else if (!strcasecmp(arg, "olive")) { *color = RGB_OLIVE; }
  else if (!strcasecmp(arg, "olivedrab")) { *color = RGB_OLIVEDRAB; }
  else if (!strcasecmp(arg, "orange")) { *color = RGB_ORANGE; }
  else if (!strcasecmp(arg, "orangered")) { *color = RGB_ORANGERED; }
  else if (!strcasecmp(arg, "orchid")) { *color = RGB_ORCHID; }
  else if (!strcasecmp(arg, "palegoldenrod")) { *color = RGB_PALEGOLDENROD; }
  else if (!strcasecmp(arg, "palegreen")) { *color = RGB_PALEGREEN; }
  else if (!strcasecmp(arg, "paleturquoise")) { *color = RGB_PALETURQUOISE; }
  else if (!strcasecmp(arg, "palevioletred")) { *color = RGB_PALEVIOLETRED; }
  else if (!strcasecmp(arg, "papayawhip")) { *color = RGB_PAPAYAWHIP; }
  else if (!strcasecmp(arg, "peachpuff")) { *color = RGB_PEACHPUFF; }
  else if (!strcasecmp(arg, "peru")) { *color = RGB_PERU; }
  else if (!strcasecmp(arg, "pink")) { *color = RGB_PINK; }
  else if (!strcasecmp(arg, "plum")) { *color = RGB_PLUM; }
  else if (!strcasecmp(arg, "powderblue")) { *color = RGB_POWDERBLUE; }
  else if (!strcasecmp(arg, "purple")) { *color = RGB_PURPLE; }
  else if (!strcasecmp(arg, "red")) { *color = RGB_RED; }
  else if (!strcasecmp(arg, "rosybrown")) { *color = RGB_ROSYBROWN; }
  else if (!strcasecmp(arg, "royalblue")) { *color = RGB_ROYALBLUE; }
  else if (!strcasecmp(arg, "saddlebrown")) { *color = RGB_SADDLEBROWN; }
  else if (!strcasecmp(arg, "salmon")) { *color = RGB_SALMON; }
  else if (!strcasecmp(arg, "sandybrown")) { *color = RGB_SANDYBROWN; }
  else if (!strcasecmp(arg, "seagreen")) { *color = RGB_SEAGREEN; }
  else if (!strcasecmp(arg, "seashell")) { *color = RGB_SEASHELL; }
  else if (!strcasecmp(arg, "sienna")) { *color = RGB_SIENNA; }
  else if (!strcasecmp(arg, "silver")) { *color = RGB_SILVER; }
  else if (!strcasecmp(arg, "skyblue")) { *color = RGB_SKYBLUE; }
  else if (!strcasecmp(arg, "slateblue")) { *color = RGB_SLATEBLUE; }
  else if (!strcasecmp(arg, "slategray")) { *color = RGB_SLATEGRAY; }
  else if (!strcasecmp(arg, "slategrey")) { *color = RGB_SLATEGREY; }
  else if (!strcasecmp(arg, "snow")) { *color = RGB_SNOW; }
  else if (!strcasecmp(arg, "springgreen")) { *color = RGB_SPRINGGREEN; }
  else if (!strcasecmp(arg, "steelblue")) { *color = RGB_STEELBLUE; }
  else if (!strcasecmp(arg, "tan")) { *color = RGB_TAN; }
  else if (!strcasecmp(arg, "teal")) { *color = RGB_TEAL; }
  else if (!strcasecmp(arg, "thistle")) { *color = RGB_THISTLE; }
  else if (!strcasecmp(arg, "tomato")) { *color = RGB_TOMATO; }
  else if (!strcasecmp(arg, "turquoise")) { *color = RGB_TURQUOISE; }
  else if (!strcasecmp(arg, "violet")) { *color = RGB_VIOLET; }
  else if (!strcasecmp(arg, "wheat")) { *color = RGB_WHEAT; }
  else if (!strcasecmp(arg, "white")) { *color = RGB_WHITE; }
  else if (!strcasecmp(arg, "whitesmoke")) { *color = RGB_WHITESMOKE; }
  else if (!strcasecmp(arg, "yellow")) { *color = RGB_YELLOW; }
  else if (!strcasecmp(arg, "yellowgreen")) { *color = RGB_YELLOWGREEN; }
  else if (!strcasecmp(arg, "purple")) { *color = RGB_PURPLE; }
  else if (!strcasecmp(arg, "fuchsia")) { *color = RGB_FUCHSIA; }
  else if (!strcasecmp(arg, "green")) { *color = RGB_GREEN; }
  else if (!strcasecmp(arg, "lime")) { *color = RGB_LIME; }
  else if (!strcasecmp(arg, "olive")) { *color = RGB_OLIVE; }
  else if (!strcasecmp(arg, "yellow")) { *color = RGB_YELLOW; }
  else if (!strcasecmp(arg, "navy")) { *color = RGB_NAVY; }
  else if (!strcasecmp(arg, "blue")) { *color = RGB_BLUE; }
  else if (!strcasecmp(arg, "teal")) { *color = RGB_TEAL; }
  else if (!strcasecmp(arg, "aqua")) { *color = RGB_AQUA; }
  return 0;
}

/* EOF */