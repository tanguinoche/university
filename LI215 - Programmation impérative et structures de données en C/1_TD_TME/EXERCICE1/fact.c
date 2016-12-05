int fact_iteratif(unsigned int a) {
  int i;
  for(i = a-1 ; i > 0 ; i--)
    a *= i;
  return a;
}

int fact_recursif(unsigned int a) {
  if(a <= 2)
    return a;

  return a*fact_recursif(a-1);
}
