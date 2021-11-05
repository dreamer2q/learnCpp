#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

#define len(arr) (sizeof(arr) / sizeof(arr[0]))

struct Student {
  struct list_head list;

  int age;
  char no[8];
  char name[12];
  char class[8];
};

const char *names[] = {
    "Jack Li", "Jack Chen", "Tom Wang", "Micheal", "Jane Wu", "Jenny",
};

struct Student *pstu;
struct Student student;
struct list_head *pos, *next;

void dropline() {
  while (getchar() != '\n')
    ;
}

void goback() {
  dropline();
  printf("\npress ENTER to go back home.");
  dropline();
}

void printList() {
  printf("No. \t Name \t\t Age \t Class \n");
  list_for_each(pos, &student.list) {
    pstu = list_entry(pos, struct Student, list);

    printf("%s \t %s \t %d \t %s\n", pstu->no, pstu->name, pstu->age,
           pstu->class);
  }
}

void doQuery() {
  printf("Student No.> ");
  char queryno[20];
  scanf("%s", queryno);
  struct Student *i = NULL;
  list_for_each(pos, &student.list) {
    pstu = list_entry(pos, struct Student, list);

    if (strncmp(pstu->no, queryno, 8) == 0) {
      i = pstu;
      break;
    }
  }
  if (i) {
    printf("Found: \n");
    printf("No. \t Name \t\t Age \t Class \n");
    printf("%s \t %s \t %d \t %s\n", pstu->no, pstu->name, pstu->age,
           pstu->class);
  } else {
    printf("NOT FOUND\n");
  }
}

void doAdd() {
  printf("Add New Student:\n");
  printf("No. \t Name \t\t Age \t Class \n");

  pstu = (struct Student *)malloc(sizeof(struct Student));
  scanf("%s %s %d %s", pstu->no, pstu->name, &pstu->age, pstu->class);
  list_add_tail(&(pstu->list), &(student.list));

  printf("Done.\n");
}

void doEdit() {
  printf("Student No.> ");
  char queryno[20];
  scanf("%s", queryno);
  struct Student *i = NULL;
  list_for_each(pos, &student.list) {
    pstu = list_entry(pos, struct Student, list);

    if (strncmp(pstu->no, queryno, 8) == 0) {
      i = pstu;
      break;
    }
  }
  if (i) {
    printf("Found: \n");
    printf("No. \t Name \t\t Age \t Class \n");
    printf("%s \t %s \t %d \t %s\n", pstu->no, pstu->name, pstu->age,
           pstu->class);

    printf("Edit Student:\n");
    printf("No. \t Name \t\t Age \t Class \n");
    pstu = (struct Student *)malloc(sizeof(struct Student));
    scanf("%s %s %d %s", pstu->no, pstu->name, &pstu->age, pstu->class);
    list_replace(pos, pstu);
    free(pos);

    printf("Done.\n");
  } else {
    printf("NOT FOUND\n");
  }
}

void doDelete() {
  printf("Student No.> ");
  char queryno[20];
  scanf("%s", queryno);
  struct Student *i = NULL;
  list_for_each(pos, &student.list) {
    pstu = list_entry(pos, struct Student, list);

    if (strncmp(pstu->no, queryno, 8) == 0) {
      i = pstu;
      break;
    }
  }
  if (i) {
    printf("Delete: \n");
    printf("No. \t Name \t\t Age \t Class \n");
    printf("%s \t %s \t %d \t %s\n", pstu->no, pstu->name, pstu->age,
           pstu->class);
    pstu = list_entry(pos, struct Student, list);
    list_del_init(pos);
    free(pstu);
  } else {
    printf("NOT FOUND\n");
  }
}

const char *home =
    "\nStudent Management System v0.1 (by Jack Li)\n\n"
    "1. Query A Student By No.\n"
    "2. Print Students order by No.\n"
    "3. Add A Student\n"
    "4. Edit A Student By No.\n"
    "5. Delete A Student By No.\n"
    "q. Quit. \n\n"
    "admin> ";

int main() {
  INIT_LIST_HEAD(&student.list);

  /**
   * 初始化数据
   */
  for (int i = 0; i < 5; i++) {
    pstu = (struct Student *)malloc(sizeof(struct Student));
    pstu->age = i + 10;
    sprintf(pstu->name, names[i % len(names)]);
    sprintf(pstu->no, "%02d", i);
    sprintf(pstu->class, "class01");

    list_add_tail(&(pstu->list), &(student.list));
  }

  printf(home);
  char cmd;
  while ((cmd = getchar()) != 'q') {
    switch (cmd) {
      case '\n':
        printf("admin> ");
        continue;
      case '1':
        doQuery();
        break;
      case '2':
        printList();
        break;
      case '3':
        doAdd();
        break;
      case '4':
        doEdit();
        break;
      case '5':
        doDelete();
        break;
      default:
        continue;
    }
    goback();
    printf(home);
  }

  return 0;
}
