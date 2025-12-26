#include <assert.h>
#include <list.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  long a;
  long b;
} Range;

long min(long a, long b) { return a <= b ? a : b; }
long max(long a, long b) { return a >= b ? a : b; }

bool disjoint(Range *range1, Range *range2) {
  return range1->b < range2->a || range1->a > range2->b;
}

void merge_ranges(Range *range1, Range *range2) {
  range1->a = min(range1->a, range2->a);
  range1->b = max(range1->b, range2->b);
  return;
}

int main(int argc, char **argv) {
  FILE *file = fopen(argv[1], "r");
  List *ranges = List_create(sizeof(Range), 0, 0, 0);
  List *ingredients = List_create(sizeof(long), 0, 0, 0);
  long a;
  long b;
  while (fscanf(file, "%ld-%ld\n", &a, &b) == 2) {
    List_append(ranges, &(Range){a, b});
  }
  long c;
  while (fscanf(file, "%ld\n", &c) == 1) {
    List_append(ingredients, &c);
  }

  long counter1 = 0;
  for (int i = 0; i < ingredients->len; i++) {
    long ingredient = *(long *)List_get(ingredients, i);
    for (int j = 0; j < ranges->len; j++) {
      Range *range = List_get(ranges, j);
      if (ingredient >= range->a && ingredient <= range->b) {
        counter1++;
        break;
      }
    }
  }
  printf("%ld\n", counter1);

  bool stop = false;
  while (!stop) {
    bool *removed = malloc(sizeof(bool) * ingredients->len);
    for (int i = 0; i < ranges->len; i++) {
      removed[i] = false;
    }
    List *merged_ranges = List_create(sizeof(Range), 0, 0, 0);
    for (int i = 0; i < ranges->len; i++) {
      if (removed[i]) {
        continue;
      }
      Range *range1 = List_get(ranges, i);
      for (int j = i + 1; j < ranges->len; j++) {
        if (removed[j]) {
          continue;
        }
        Range *range2 = List_get(ranges, j);
        if (!disjoint(range1, range2)) {
          merge_ranges(range1, range2);
          removed[j] = true;
        }
      }
      List_append(merged_ranges, range1);
    }
    if (ranges->len == merged_ranges->len) {
      stop = true;
    }
    List_free(ranges);
    free(removed);
    ranges = merged_ranges;
  }

  long counter2 = 0;
  for (int i = 0; i < ranges->len; i++) {
    Range *range = List_get(ranges, i);
    counter2 += range->b - range->a + 1;
  }
  printf("%ld\n", counter2);

  List_free(ranges);
  List_free(ingredients);
  fclose(file);
  return 0;
}