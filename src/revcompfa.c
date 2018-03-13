#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*################################################################################
  ################################################################################

/*
  basemap[] works by storing a very small array that maps a base to 
  its complement, by dereferencing the array with the ASCII char's 
  decimal value as the index
  (int) 'A' = 65;
  (int) 'C' = 67;
  (int) 'G' = 71;
  (int) 'T' = 84;
  (int) 'a' = 97;
  (int) 'c' = 99;
  (int) 'g' = 103;
  (int) 't' = 116;
  (int) 'N' = 78;
  (int) 'U' = 85;
  (int) 'u' = 117;
  for example: basemap['A'] => basemap[65] => 'T' etc.
*/

static const char basemap[255] =
    {
        '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', /*   0 -   9 */
        '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', /*  10 -  19 */
        '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', /*  20 -  29 */
        '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', /*  30 -  39 */
        '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', /*  40 -  49 */
        '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', /*  50 -  59 */
        '\0', '\0', '\0', '\0', '\0',  'T', '\0',  'G', '\0', '\0', /*  60 -  69 */
        '\0',  'C', '\0', '\0', '\0', '\0', '\0', '\0',  'N', '\0', /*  70 -  79 */
        '\0', '\0', '\0', '\0',  'A',  'A', '\0', '\0', '\0', '\0', /*  80 -  89 */
        '\0', '\0', '\0', '\0', '\0', '\0', '\0',  't', '\0',  'g', /*  90 -  99 */
        '\0', '\0', '\0',  'c', '\0', '\0', '\0', '\0', '\0', '\0', /* 100 - 109 */
        '\0', '\0', '\0', '\0', '\0', '\0',  'a',  'a', '\0', '\0', /* 110 - 119 */
        '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', /* 120 - 129 */
        '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', /* 130 - 139 */
        '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', /* 140 - 149 */
        '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', /* 150 - 159 */
        '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', /* 160 - 169 */
        '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', /* 170 - 179 */
        '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', /* 180 - 189 */
        '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', /* 190 - 199 */
        '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', /* 200 - 209 */
        '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', /* 210 - 219 */
        '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', /* 220 - 229 */
        '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', /* 230 - 239 */
        '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', /* 240 - 249 */
        '\0', '\0', '\0', '\0', '\0'                                /* 250 - 254 */
    };

int
main(int argc, const char** argv)
{
    char* line = NULL;
    char* seq = NULL;
    char* seqtemp = NULL;
    size_t seqlen = 0;
    size_t seqtemplen = 0;
    size_t len = 0;
    size_t lindex = 0;
    ssize_t read;
    
    while ((read = getline(&line, &len, stdin)) != -1) {
        if (line[0] == ">"[0]) {
            if (lindex > 0) {
                for (int idx = seqlen - 2; idx >= 0; idx--) {
                    fprintf(stdout, "%c", basemap[(int)seq[idx]]);
                }
                fprintf(stdout, "\n");
            }
            seqlen = 0;
            seq = malloc(seqlen);
            seqtemplen = 0;
            seqtemp = malloc(seqtemplen);
            fprintf(stdout, "%s", line);
        } else {
            /*allocate memory for snprintf:*/
            seqtemplen = (size_t)snprintf(NULL, 0, "%s%s", seq, line);
            seqtemp = malloc(seqtemplen);
            /* Safely write to mystr with known length 'len' */
            snprintf(seqtemp, seqtemplen, "%s%s", seq,line);
            /*allocate memory for snprintf:*/
            seqlen = (size_t)snprintf(NULL, 0, "%s", seqtemp)+1;
            seq = malloc(seqlen);
            /* Safely write to mystr with known length 'len' */
            snprintf(seq, seqlen, "%s", seqtemp);
        }
        lindex++;
    }

    for (int idx = seqlen - 2; idx >= 0; idx--) {
        fprintf(stdout, "%c", basemap[(int)seq[idx]]);
    }
    fprintf(stdout, "\n");

    if (line) {
        free(line); 
        line = NULL;
    }
    if (seq) {
        free(seq); 
        seq = NULL;
    }
    if (seqtemp) {
        free(seqtemp); 
        seqtemp = NULL;
    }
    
    return EXIT_SUCCESS;
}
