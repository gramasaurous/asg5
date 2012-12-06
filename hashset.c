//Graham Greving
//ggreving
//Joe Rowley
//jrowley

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "debugf.h"
#include "hashset.h"
#include "strhash.h"

#define HASH_NEW_SIZE 15

struct hashset {
   size_t length;
   int load;
   char **array;
};

void check_hashset(hashset_ref hashset) {
   printf("checking hashset\n");
   int j=0;
   printf ("Hashset Length: %zu \n", hashset->length); 
   for (int i = 0; i < hashset->length; i++){
      if (hashset->array[i] != NULL) {
        // printf ("%10d = Check (\"%s\")\n", i, hashset->array[i]);  
         printf ("%s\n", hashset->array[i]);
         j++;
      }
   }
   printf ("Words Present in Hash: %d \n", j);  
   printf ("Done Checking\n");  
}

void doublearray(hashset_ref hashset) {
   printf("attempting to double the array\n");
   int oldlength = hashset->length;
   hashset->length = (oldlength * 2) + 1;
   char **newarray = malloc (hashset->length * sizeof (char*));
   for (int i = 0; i < hashset-> length; i++) {
      newarray[i] = NULL;
   }
   for (int i = 0; i < oldlength; i++) {
      if (hashset->array[i] == NULL) continue;
      int newindex = strhash(hashset->array[i]) % hashset->length;
      newarray[newindex] = hashset->array[i];
   }
   char **tmp = hashset->array;
   hashset->array = newarray;
   free(tmp);
}

hashset_ref new_hashset (void) {
   hashset_ref new = malloc (sizeof (struct hashset));
   assert (new != NULL);
   new->length = HASH_NEW_SIZE;
   new->load = 0;
   new->array = malloc (new->length * sizeof (char*));
   assert (new->array != NULL);
   for (size_t index = 0; index < new->length; ++index) {
      new->array[index] = NULL;
   }
   DEBUGF ('h', "%p -> struct hashset {length = %d, array=%p}\n",
                new, new->length, new->array);
   return new;
}

void free_hashset (hashset_ref hashset) {
   DEBUGF ('h', "free (%p), free (%p)\n", hashset->array, hashset);
   memset (hashset->array, 0, hashset->length * sizeof (char*));
   free (hashset->array);
   memset (hashset, 0, sizeof (struct hashset));
   free (hashset);
}

void put_hashset (hashset_ref hashset, char *item) {
   //STUBPRINTF ("hashset=%p, item=%s\n", hashset, item);
   if ((hashset->load * 4) > hashset->length) doublearray(hashset);
   hashcode_t newhash = strhash(item);
   int start = (newhash % hashset->length);
   int i = start;
   char **a = hashset->array;
   while(1) {
      if (i == hashset->length) i = 0;
      if (i == start-1) return;
      if (a[i] == NULL) {
   	   a[i] = strdup(item);
   	   //printf ("%10u = strhash (\"%s\")\n", newhash, item);
   	   printf ("%s\n", item);
   	   
   	   hashset->load++;
   	   return;
   	} else {
   	   int cmp = strcmp(item, a[i]);
   	   if (cmp == 0) return;
   	}
   	i++;
   }
   
   //printf("Index: %d\n", start);
   //printf ("%10u = strhash (\"%s\")\n", newhash, item);
}

bool has_hashset (hashset_ref hashset, char *item) {
   STUBPRINTF ("hashset=%p, item=%s\n", hashset, item);
   return true;
}

