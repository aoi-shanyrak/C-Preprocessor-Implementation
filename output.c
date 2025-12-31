
int main() {
  int array[MAX];
  float area = PI * SQUARE(5);

#ifdef DEBUG
  printf("Area: %f\n", area);
#endif

  return 0;
}