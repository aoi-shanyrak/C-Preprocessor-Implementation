#define MAX 100
#define PI 3.14159
#define SQUARE(x) ((x) * (x))
#define DEBUG

int main() {
  int array[MAX];
  float area = PI * SQUARE(5);

#ifdef DEBUG
  printf("Area: %f\n", area);
#endif

  return 0;
}