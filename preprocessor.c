#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct nlist {
  struct nlist* next;
  char* name;
  char* defn;
};

#define HASHSIZE 101

static struct nlist* hashtab[HASHSIZE];

unsigned hash(char* s) {
  unsigned hashval;

  for (hashval = 0; *s != '\0'; s++)
    hashval = *s + 31 * hashval;
  return hashval % HASHSIZE;
}

struct nlist* lookup(char* s) {
  struct nlist* np;

  for (np = hashtab[hash(s)]; np != NULL; np = np->next) {
    if (strcmp(s, np->name) == 0)
      return np;
  }
  return NULL;
}

char* strduplicate(char*);

struct nlist* install(char* name, char* defn) {
  struct nlist* np;
  unsigned hashval;

  if ((np = lookup(name)) == NULL) {
    np = (struct nlist*) malloc(sizeof(*np));
    if (np == NULL)
      return NULL;
    hashval = hash(name);
    np->name = strduplicate(name);
    if (np->name == NULL) {
      free(np);
      return NULL;
    }
    np->next = hashtab[hashval];
    hashtab[hashval] = np;
  } else {
    free(np->defn);
  }
  np->defn = strduplicate(defn);
  if (np->defn == NULL)
    return NULL;

  return np;
}

void uninstall(char* name) {
  struct nlist* np = lookup(name);
  if (np != NULL) {
    unsigned hashval = hash(name);
    struct nlist* prev = NULL;
    struct nlist* cur = hashtab[hashval];

    while (cur != NULL && cur != np) {
      prev = cur;
      cur = cur->next;
    }
    if (prev == NULL) {
      hashtab[hashval] = np->next;
    } else {
      prev->next = np->next;
    }
    free(np->name);
    free(np->defn);
    free(np);
  }
}

void free_hashtab() {
  struct nlist *np, *tmp;

  for (int i = 0; i < HASHSIZE; i++) {
    np = hashtab[i];
    while (np != NULL) {
      tmp = np->next;
      free(np->name);
      free(np->defn);
      free(np);
      np = tmp;
    }
    hashtab[i] = NULL;
  }
}

// ----------------------

char* strduplicate(char* s) {
  char* p = (char*) malloc(strlen(s) + 1);

  if (p != NULL)
    strcpy(p, s);
  return p;
}

int isidentchar(int c) {
  return isalnum(c) || c == '_';
}

void handle_define(char* line) {
  char name[256], defn[1024];
  int i = 6; // skip define

  while (isspace(line[i]))
    i++;

  int j = 0;
  while (!isspace(line[i]) && line[i] != '\0')
    name[j++] = line[i++];
  name[j] = '\0';

  while (isspace(line[i]))
    i++;

  j = 0;
  while (line[i] != '\n' && line[i] != '\0')
    defn[j++] = line[i++];
  defn[j] = '\0';

  if (name[0] != '\0')
    install(name, defn);
}

void handle_undef(char* line) {
  char name[256];
  int i = 6; // skip undef

  while (isspace(line[i]))
    i++;
  int j = 0;
  while (!isspace(line[i]) && line[i] != '\n' && line[i] != '\0')
    name[j++] = line[i++];
  name[j] = '\0';

  if (name[0] != '\0')
    uninstall(name);
}

void process_line(char* line) {
  char output[4096], ident[256];
  int i = 0, j = 0, k;

  while (line[i] != '\0') {
    if (isidentchar(line[i]) && (i == 0 || !isidentchar(line[i - 1]))) {
      k = 0;
      while (isidentchar(line[i]))
        ident[k++] = line[i++];
      ident[k] = '\0';

      struct nlist* np = lookup(ident);
      if (np != NULL) {
        strcpy(&output[j], np->defn);
        j += strlen(np->defn);
      } else {
        strcpy(&output[j], ident);
        j += strlen(ident);
      }
    } else {
      output[j++] = line[i++];
    }
  }
  output[j] = '\0';

  printf("%s", output);
}

int main(int argc, char* argv[]) {
  char line[4096];
  int in_multiline_comment = 0;

  while (fgets(line, sizeof(line), stdin)) {
    int i = 0;
    while (isspace(line[i]))
      i++;

    if (strncmp(&line[i], "#define", 7) == 0 && isspace(line[i + 7])) {
      handle_define(&line[i]);
      continue;
    }
    if (strncmp(&line[i], "#undef", 6) == 0 && isspace(line[i + 6])) {
      handle_undef(&line[i]);
      continue;
    }
    process_line(line);
  }
  free_hashtab();

  return 0;
}
