#define _GNU_SOURCE
#include <getopt.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "cachelab.h"

const int address_size = 64;
int set_bit_count;
int lines_per_set;
int block_bit_count;
char trace_filename[100];
int address_bit_count;
int verbose;

int hit_count;
int miss_count;
int eviction_count;

void getOptions(int argc, char **argv)
{
  int c;
  while ((c = getopt (argc, argv, "s:E:b:t:v")) != -1)
    switch (c)
    {
      case 's':
        set_bit_count = atoi(optarg);
        break;
      case 'E':
        lines_per_set = atoi(optarg);
        break;
      case 'b':
        block_bit_count = atoi(optarg);
        break;
      case 't':
        strcpy(trace_filename, optarg);
        break;
      case 'v':
        verbose = 1;
        break;
      case '?':
        if (optopt == 'c')
          fprintf (stderr, "Option -%c requires an argument.\n", optopt);
        else if (isprint (optopt))
          fprintf (stderr, "Unknown option `-%c'.\n", optopt);
        else
          fprintf (stderr,
              "Unknown option character `\\x%x'.\n",
              optopt);
        exit(1);
      default:
        abort ();
    }

  if (!set_bit_count || !lines_per_set || !block_bit_count || trace_filename[0] == '\0') {
    const char *usage = "Missing required command line argument\n"
      "Usage: ./csim-ref [-hv] -s <num> -E <num> -b <num> -t <file>\n"
      "Options:\n"
      "  -h         Print this help message.\n"
      "  -v         Optional verbose flag.\n"
      "  -s <num>   Number of set index bits.\n"
      "  -E <num>   Number of lines per set.\n"
      "  -b <num>   Number of block offset bits.\n"
      "  -t <file>  Trace file.\n"
      "\n"
      "Examples:\n"
      "  linux>  ./csim -s 4 -E 1 -b 4 -t traces/yi.trace\n"
      "  linux>  ./csim -v -s 8 -E 2 -b 4 -t traces/yi.trace\n";
    fprintf (stderr, "%s: %s", argv[0], usage);
    exit(1);
  }
}

struct line_s {
  int valid;
  unsigned long tag;
  unsigned int least_usage;
};

struct set_s {
  struct line_s *plines;
};

struct cache_s {
  struct set_s *psets;
  int set_count;
} cache;


void decodeAddress(unsigned long address, unsigned *pset, unsigned long *ptag, unsigned *poffset)
{
  *ptag = address >> (block_bit_count + set_bit_count);
  unsigned int set_mask = (1 << set_bit_count) - 1;
  *pset = (address >> block_bit_count) & set_mask;
  unsigned int offset_mask = (1 << block_bit_count) - 1;
  *poffset = address & offset_mask;

  assert(*ptag < (1l << (address_bit_count - set_bit_count - block_bit_count)));
  assert(*pset < (1 << set_bit_count));
  assert(*poffset < (1 << block_bit_count));
}

int processLine(char *line)
{
  if (line[0] == 'I')
    return 0;
  char type;
  unsigned long address;
  int size;
  if (sscanf(line, " %c %lx,%d", &type, &address, &size) != 3)
    return 1;

  unsigned set;
  unsigned long tag;
  unsigned offset;
  decodeAddress(address, &set, &tag, &offset);

  /* Check that access does not cross the block boundries */
  unsigned set_last, offset_last;
  unsigned long tag_last;
  decodeAddress(address + size - 1, &set_last, &tag_last, &offset_last);
  assert(set == set_last);
  assert(tag == tag_last);

  char verbose_str[100] = {};
  sprintf(verbose_str, "%c %lx,%d", type, address, size);

  int hit_line = -1;
  for (int line = 0; line < lines_per_set; line++) {  
    if (cache.psets[set].plines[line].tag == tag && cache.psets[set].plines[line].valid) {
      hit_line = line;
      hit_count++;
      strcat(verbose_str, " hit");
      break;
    }
  }
  if (hit_line == -1) {
    miss_count++;
    strcat(verbose_str, " miss");
  }

  switch(type) {
    case 'M':
      hit_count++;  /* falltrough */
    case 'S':
    case 'L':
      if (hit_line == -1)
        for (int line = 0; line < lines_per_set; line++) {
          if (!cache.psets[set].plines[line].valid) {
            cache.psets[set].plines[line].tag = tag;
            cache.psets[set].plines[line].valid = 1;
            hit_line = line;
            break;
          }
        }
      if (hit_line != -1) {
        cache.psets[set].plines[hit_line].least_usage = 0;
        for (int line = 0; line < lines_per_set; line++)
          if (line != hit_line && cache.psets[set].plines[line].valid)
            cache.psets[set].plines[line].least_usage++;
      } else {
        hit_line = 0;
        assert(cache.psets[set].plines[hit_line].valid);
        for (int line = 1; line < lines_per_set; line++) {
          assert(cache.psets[set].plines[line].valid);
          assert(cache.psets[set].plines[line].least_usage != cache.psets[set].plines[hit_line].least_usage);
          if (cache.psets[set].plines[line].least_usage > cache.psets[set].plines[hit_line].least_usage)
            hit_line = line;
        }
        cache.psets[set].plines[hit_line].tag = tag;
        cache.psets[set].plines[hit_line].least_usage = 0;
        for (int line = 0; line < lines_per_set; line++)
          if (line != hit_line)
            cache.psets[set].plines[line].least_usage++;
        eviction_count++;
        strcat(verbose_str, " eviction");
      }
      break;
    default:
      return 1;
  }
  if (type == 'M')
    strcat(verbose_str, " hit");

  if (verbose)
    printf("%s\n", verbose_str);

  return 0;
}

int main(int argc, char **argv)
{
  /* Get the command line options */
  getOptions(argc, argv);  

  /* Initialize data structures */
  cache.set_count = 1 << set_bit_count;
  cache.psets = (struct set_s*)malloc(sizeof(struct set_s) * cache.set_count);

  for (int ii = 0; ii < cache.set_count; ii++) {
    cache.psets[ii].plines = (struct line_s*)malloc(sizeof(struct line_s) * lines_per_set);
    for (int jj = 0; jj < lines_per_set; jj++) {
      cache.psets[ii].plines[jj].valid = 0;
      cache.psets[ii].plines[jj].tag = 0;
      cache.psets[ii].plines[jj].least_usage = 0;
    }
  }

  /* Open the file */
  FILE * fp;
  char * line = NULL;
  size_t len = 0;
  ssize_t read;

  fp = fopen(trace_filename, "r");
  if (fp == NULL) {
    fprintf (stderr, "%s: %s", trace_filename, "No such file or directory\n");
    exit(2);
  }

  /* Process each line */
  while ((read = getline(&line, &len, fp)) != -1) {
    if (processLine(line) == 1) {
      fprintf (stderr, "%s: %s: %s\n", trace_filename, "Invalid line", line);
      exit(3);
    }
  }

  fclose(fp);
  if (line)
    free(line);

  printSummary(hit_count, miss_count, eviction_count);

  return 0;
}
