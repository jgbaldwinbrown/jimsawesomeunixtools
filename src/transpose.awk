#!/usr/bin/awk -f

{
     if (max_nf < NF)
          max_nf = NF
     max_nr = NR
     for (x = 1; x <= NF; x++)
          vector[x, NR] = $x
}

END {
     for (x = 1; x <= max_nf; x++) {
          for (y = 1; y <= max_nr; y++)
               printf("%s%s", vector[x, y],OFS)
          printf("%s",ORS)
     }
}
