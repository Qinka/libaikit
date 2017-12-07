
#define _AIKIT_KPRINT_C_
#include <aikit/kprint.h>
#include <string.h>
#include <stdint.h>

extern void put_char(char);
extern void put_unix_time();
void put_str(char *);
void put_hex_u32(uint32_t i);
void put_hex_u8(uint8_t i);
extern void __enter();
extern void __exit();

#define _DIGIT_HEX(x) (x += x > 9 ? '7' : '0')

/**
 * kprint
 * 
 * format:
 * %% => %
 * %u => hex unsigned int
 * %c => char
 * %s => string
 */
void kprint(const char* format, ...) {
  __enter();
  va_list argp;
  va_start(argp, format);
  put_unix_time(); put_str(": ");  
LOOP_BEGIN:
  if (*format == '\0')
    goto LOOP_END;
  else if(*format == '%') { // format
    ++format;
    switch(*format) {
      case '%':
        put_char('%');
        break;
      case 'u':
        put_hex_u32(va_arg(argp, unsigned int));
        break;
      case 'b':
        put_hex_u8(va_arg(argp, uint8_t));
        break;
      case 'c':
        put_char(va_arg(argp, char));
        break;
      case 's':
        put_str(va_arg(argp, char *));
        break;
      default:
        put_str("%?");
    }
  }
  else {
    put_char(*format);
    if (*format == '\n') {
      put_char('\r');
      put_unix_time();
      put_str(": ");
    }
  }
FORMAT_PLUS:
  ++format;
  goto LOOP_BEGIN;
LOOP_END:
  put_char('\n');
  put_char('\r');
  va_end(argp);
  __exit();
}

/**
 * put_str
 */
void put_str(char *str) {
  while (*str) put_char(*str++);
}

void put_hex_u32(uint32_t i) {
  put_hex_u8(0xFF & i);
  i >>= 8;
  put_hex_u8(0xFF & i);
  i >>= 8;
  put_hex_u8(0xFF & i);
  i >>= 8;
  put_hex_u8(0xFF & i);
}

void put_hex_u8(uint8_t i) {
  char high = 0xF & (i >> 4);
  char low = 0xF & i;
  _DIGIT_HEX(high);
  _DIGIT_HEX(low);
  put_char(high);
  put_char(low);
}