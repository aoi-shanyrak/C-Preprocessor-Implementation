
int main() {
  int array[100];
  float area = 3.14159 * SQUARE(5);

#ifdef DEBUG
  printf("Area: %f\n", area);
#endif

  return 0;
}