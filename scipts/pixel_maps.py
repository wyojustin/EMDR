from pylab import *
from numpy import *

def vflip(m):
    return m[::-1]

U88 = arange(8 * 8).reshape((8, 8))
U88[1::2] = U88[1::2,::-1]
U88 = vflip(U88.T)

n = 12
emdr = []
for i in range(n):
    emdr.append(U88 + i * 8 * 8)

emdr = hstack(emdr)

print('''
#ifndef MATRIX_MAP_H
#define MATRIX_MAP_H

#define MatrixWidth %d
#define MatrixHeight 8
#define NUM_LEDS (MatrixWidth * MatrixHeight)
uint16_t MatrixMap[MatrixHeight][MatrixWidth] = {''' % (8 * n))
for row in emdr:
    print('    {', ','.join(map(str, row)), '},')
print('};')
print('''
uint16_t XY(int x, int y){
  uint16_t out;
  x = MatrixWidth - x - 1;
  y = MatrixHeight - y - 1;
  if(0 <= x && x < MatrixWidth &&
     0 <= y && y < MatrixHeight){
    out = MatrixMap[y][x];
  }
  else{
    out = NUM_LEDS + 1;
  }
  return out;
}

#endif
''')
pixel_maps = open(__file__).read()
print(chr(47) + '*')
print(pixel_maps)
print('*' + chr(47))
